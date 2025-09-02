#include <feel/feel.hpp>

int main( int argc, char** argv )
{
    using namespace Feel;
    using namespace Feel::vf;

    // Define command line options
    po::options_description laplacian_options( "Laplacian solver options" );
    laplacian_options.add_options()
        ( "order", po::value<int>()->default_value( 2 ), "polynomial order" )
        ( "penalbc", po::value<double>()->default_value( 100 ), "penalization parameter for Dirichlet BC" )
        ( "weak-bc", po::value<bool>()->default_value( false ), "use weak boundary conditions" )
        ( "mu", po::value<double>()->default_value( 1.0 ), "diffusion coefficient" );

    Environment env( _argc=argc, _argv=argv,
                     _desc=laplacian_options,
                     _about=about( _name="laplacian",
                                   _author="Feel++ Consortium",
                                   _email="feelpp-devel@feelpp.org" ) );

    // Load mesh
    auto mesh = loadMesh(_mesh=new Mesh<Simplex<2>>);
    
    // Create function space
    int order = ioption("order");
    auto Vh = Pch<2>( mesh );
    auto u = Vh->element("u");
    auto v = Vh->element("v");
    
    // Get parameters
    double mu = doption("mu");
    double penalbc = doption("penalbc");
    bool weak_bc = boption("weak-bc");
    
    LOG(INFO) << "Solving Laplacian equation with:";
    LOG(INFO) << "  - polynomial order: " << order;
    LOG(INFO) << "  - diffusion coefficient: " << mu;
    LOG(INFO) << "  - weak BC: " << (weak_bc ? "yes" : "no");
    
    // Define exact solution and right-hand side
    auto u_exact = sin(pi*Px())*sin(pi*Py());
    auto f = mu * 2*pi*pi*sin(pi*Px())*sin(pi*Py());  // -div(mu*grad(u)) = f
    auto g = u_exact;  // Dirichlet boundary condition
    
    // Assemble the bilinear form a(u,v) = ∫ μ ∇u·∇v
    auto a = form2( _trial=Vh, _test=Vh );
    a = integrate( _range=elements(mesh),
                   _expr=mu * gradt(u) * trans(grad(v)) );
    
    // Add boundary conditions
    if ( weak_bc )
    {
        // Weak Dirichlet boundary conditions using Nitsche's method
        a += integrate( _range=boundaryfaces(mesh),
                       _expr=-mu * gradt(u) * N() * id(v)
                            -mu * grad(v) * N() * idt(u)
                            + penalbc * idt(u) * id(v) / hFace() );
    }
    else
    {
        // Strong Dirichlet boundary conditions
        a += on( _range=boundaryfaces(mesh), _rhs=l, _element=u, _expr=g );
    }
    
    // Assemble the linear form l(v) = ∫ f·v
    auto l = form1( _test=Vh );
    l = integrate( _range=elements(mesh),
                   _expr=f * id(v) );
    
    if ( weak_bc )
    {
        // Add boundary terms for weak BC
        l += integrate( _range=boundaryfaces(mesh),
                       _expr=-mu * g * grad(v) * N() + penalbc * g * id(v) / hFace() );
    }
    
    // Solve the linear system
    a.solve( _rhs=l, _solution=u );
    
    // Compute error
    auto error_l2 = normL2( _range=elements(mesh), _expr=idv(u) - u_exact );
    auto error_h1 = normH1( _range=elements(mesh), 
                           _expr=idv(u) - u_exact,
                           _grad_expr=gradv(u) - grad<2>(u_exact) );
    
    LOG(INFO) << "L2 error: " << error_l2;
    LOG(INFO) << "H1 error: " << error_h1;
    
    // Export results
    auto e = exporter( _mesh=mesh, _name="laplacian" );
    e->add( "solution", u );
    e->add( "exact", vf::project(_space=Vh, _range=elements(mesh), _expr=u_exact) );
    e->add( "error", vf::project(_space=Vh, _range=elements(mesh), _expr=abs(idv(u) - u_exact)) );
    e->save();
    
    return 0;
}
