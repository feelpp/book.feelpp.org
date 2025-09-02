#include <feel/feel.hpp>

int main( int argc, char** argv )
{
    using namespace Feel;
    using namespace Feel::vf;

    // Define options specific to Stokes problem
    po::options_description stokes_options( "Stokes solver options" );
    stokes_options.add_options()
        ( "nu", po::value<double>()->default_value( 1.0 ), "kinematic viscosity" )
        ( "penalbc", po::value<double>()->default_value( 100 ), "penalization for boundary conditions" );

    Environment env( _argc=argc, _argv=argv,
                     _desc=stokes_options,
                     _about=about( _name="stokes",
                                   _author="Feel++ Consortium",
                                   _email="feelpp-devel@feelpp.org" ) );

    // Load mesh
    auto mesh = loadMesh(_mesh=new Mesh<Simplex<2>>);
    
    // Create mixed function space: Velocity (P2) + Pressure (P1)
    auto Vh = Pchv<2>( mesh );     // Velocity space (vector-valued P2)
    auto Qh = Pch<1>( mesh );      // Pressure space (scalar P1) 
    auto Wh = Vh * Qh;             // Mixed space

    // Create elements
    auto U = Wh->element("(u,p)");
    auto u = U.template element<0>("u");  // velocity
    auto p = U.template element<1>("p");  // pressure
    auto V = Wh->element("(v,q)");
    auto v = V.template element<0>("v");  // test velocity
    auto q = V.template element<1>("q");  // test pressure
    
    // Problem parameters
    double nu = doption("nu");
    double penalbc = doption("penalbc");
    
    LOG(INFO) << "Solving Stokes equation with:";
    LOG(INFO) << "  - kinematic viscosity: " << nu;
    LOG(INFO) << "  - velocity DoFs: " << Vh->nDof();
    LOG(INFO) << "  - pressure DoFs: " << Qh->nDof();
    LOG(INFO) << "  - total DoFs: " << Wh->nDof();

    // Define manufactured solution for validation
    auto u1_exact = sin(pi*Px())*cos(pi*Py());
    auto u2_exact = -cos(pi*Px())*sin(pi*Py());
    auto p_exact = sin(pi*Px())*sin(pi*Py());
    
    // Compute corresponding body force
    auto f1 = -nu * (-2*pi*pi*sin(pi*Px())*cos(pi*Py())) + pi*cos(pi*Px())*sin(pi*Py());
    auto f2 = -nu * (2*pi*pi*cos(pi*Px())*sin(pi*Py())) + pi*sin(pi*Px())*cos(pi*Py());
    
    // Assemble Stokes system
    auto a = form2( _trial=Wh, _test=Wh );
    
    // Viscous term: ∫ ν ∇u : ∇v
    a += integrate( _range=elements(mesh),
                   _expr=nu * inner(gradt(u), grad(v)) );
    
    // Divergence of velocity (constraint): ∫ div(u) * q
    a += integrate( _range=elements(mesh),
                   _expr=divt(u) * id(q) );
    
    // Pressure gradient term: ∫ p * div(v)  
    a += integrate( _range=elements(mesh),
                   _expr=idt(p) * div(v) );
    
    // Right-hand side
    auto l = form1( _test=Wh );
    l += integrate( _range=elements(mesh),
                   _expr=f1*id(v).comp(X) + f2*id(v).comp(Y) );
    
    // Apply boundary conditions (no-slip walls)
    auto u_exact_vec = vec(u1_exact, u2_exact);
    a += on( _range=boundaryfaces(mesh), _rhs=l, _element=u, _expr=u_exact_vec );
    
    // Solve the system
    LOG(INFO) << "Assembling and solving Stokes system...";
    a.solve( _rhs=l, _solution=U );
    
    // Compute errors
    auto error_u_l2 = normL2( _range=elements(mesh), 
                             _expr=idv(u) - u_exact_vec );
    auto error_p_l2 = normL2( _range=elements(mesh),
                             _expr=idv(p) - p_exact );
    
    auto error_u_h1 = normH1( _range=elements(mesh),
                             _expr=idv(u) - u_exact_vec,
                             _grad_expr=gradv(u) - grad<2>(u_exact_vec) );
    
    LOG(INFO) << "Velocity L2 error: " << error_u_l2;
    LOG(INFO) << "Velocity H1 error: " << error_u_h1;
    LOG(INFO) << "Pressure L2 error: " << error_p_l2;
    
    // Check divergence-free condition
    auto div_error = normL2( _range=elements(mesh), _expr=divv(u) );
    LOG(INFO) << "Divergence error: " << div_error;
    
    // Export results
    auto e = exporter( _mesh=mesh, _name="stokes" );
    e->add( "velocity", u );
    e->add( "pressure", p );
    e->add( "velocity_exact", vf::project(_space=Vh, _range=elements(mesh), _expr=u_exact_vec) );
    e->add( "pressure_exact", vf::project(_space=Qh, _range=elements(mesh), _expr=p_exact) );
    e->add( "velocity_magnitude", vf::project(_space=Qh, _range=elements(mesh), _expr=sqrt(trans(idv(u))*idv(u))) );
    e->save();
    
    return 0;
}
