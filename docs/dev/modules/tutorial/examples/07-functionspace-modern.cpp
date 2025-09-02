#include <feel/feel.hpp>

int main( int argc, char** argv )
{
    using namespace Feel;
    using namespace Feel::vf;

    // Initialize Feel++ Environment with command line options
    po::options_description myoptions( "Function space tutorial options" );
    myoptions.add_options()
        ( "order", po::value<int>()->default_value( 2 ), "polynomial order" )
        ( "hsize", po::value<double>()->default_value( 0.1 ), "mesh size" );

    Environment env( _argc=argc, _argv=argv,
                     _desc=myoptions,
                     _about=about( _name="functionspace",
                                   _author="Feel++ Consortium",
                                   _email="feelpp-devel@feelpp.org" ) );

    // Create mesh
    auto mesh = loadMesh(_mesh=new Mesh<Simplex<2>>);
    
    // Get polynomial order from command line
    int order = ioption(_name="order");
    LOG(INFO) << "Using polynomial order: " << order;

    // Create function spaces of different types
    // Scalar function space (temperature, pressure, etc.)
    auto Vh_scalar = Pch<1>( mesh );           // P1 elements
    auto Vh_scalar_ho = Pch<2>( mesh );        // P2 elements
    
    // Vector function space (velocity, displacement, etc.)
    auto Vh_vector = Pchv<1>( mesh );          // Vector P1 elements
    auto Vh_vector_ho = Pchv<2>( mesh );       // Vector P2 elements
    
    // Mixed function space (Stokes: velocity + pressure)
    auto Vh_mixed = Pchv<2>( mesh ) * Pch<1>( mesh );
    
    LOG(INFO) << "Scalar P1 space has " << Vh_scalar->nDof() << " degrees of freedom";
    LOG(INFO) << "Scalar P2 space has " << Vh_scalar_ho->nDof() << " degrees of freedom";
    LOG(INFO) << "Vector P1 space has " << Vh_vector->nDof() << " degrees of freedom";
    LOG(INFO) << "Vector P2 space has " << Vh_vector_ho->nDof() << " degrees of freedom";
    LOG(INFO) << "Mixed space has " << Vh_mixed->nDof() << " degrees of freedom";

    // Create elements (functions) in these spaces
    auto u_scalar = Vh_scalar->element("u_scalar");
    auto u_vector = Vh_vector->element("u_vector");
    
    // Initialize with expressions
    u_scalar.on( _range=elements(mesh), _expr=sin(pi*Px())*cos(pi*Py()) );
    u_vector.on( _range=elements(mesh), _expr=vec(cos(Px()), sin(Py())) );
    
    // Demonstrate projections
    auto proj_scalar = vf::project( _space=Vh_scalar_ho, 
                                   _range=elements(mesh), 
                                   _expr=exp(-((Px()-0.5)*(Px()-0.5) + (Py()-0.5)*(Py()-0.5))/0.1) );
    
    // Compute norms
    double l2_norm_scalar = normL2( _range=elements(mesh), _expr=idv(u_scalar) );
    double h1_norm_scalar = normH1( _range=elements(mesh), _expr=idv(u_scalar), _grad_expr=gradv(u_scalar) );
    
    LOG(INFO) << "L2 norm of scalar function: " << l2_norm_scalar;
    LOG(INFO) << "H1 norm of scalar function: " << h1_norm_scalar;
    
    // Export results
    auto e = exporter( _mesh=mesh, _name="functionspace" );
    e->add( "u_scalar", u_scalar );
    e->add( "u_vector", u_vector );
    e->add( "projected", proj_scalar );
    e->save();
    
    return 0;
}
