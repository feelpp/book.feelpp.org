#include <feel/feelfilters/loadmesh.hpp>
#include <feel/feelfilters/exporter.hpp>
#include <feel/feelvf/vf.hpp>

int main( int argc, char** argv )
{
    using namespace Feel;
    using namespace Feel::vf;
    
    // initialize Feel++ Environment
    Environment env( _argc=argc, _argv=argv,
                     _about=about( _name="mymesh" ,
                                   _author="Feel++ Consortium",
                                   _email="feelpp-devel@feelpp.org" ) );
    
    // tag::mesh[]
    // Create a mesh with GMSH using Feel++ geometry tool
    // Modern mesh loading with auto type deduction
    auto mesh = loadMesh(_mesh=new Mesh<Simplex<2>>);
    // end::mesh[]

    LOG(INFO) << "mesh " << soption(_name="gmsh.filename") << " loaded";
    LOG(INFO) << "mesh has " << mesh->numElements() << " elements";
    LOG(INFO) << "mesh has " << mesh->numPoints() << " vertices";

    // Compute geometric properties
    auto volume = integrate( _range=elements( mesh ), _expr=cst( 1. ) ).evaluate();
    auto surface = integrate( _range=boundaryfaces( mesh ), _expr=cst( 1. ) ).evaluate();
    
    LOG(INFO) << "volume = " << volume;
    LOG(INFO) << "surface = " << surface;

    // Advanced mesh information
    LOG(INFO) << "Mesh dimension: " << mesh->dimension();
    LOG(INFO) << "Real dimension: " << mesh->realDimension();
    
    // Check for markers
    if ( mesh->hasMarkers() )
    {
        auto markers = mesh->markerNames();
        LOG(INFO) << "Mesh has " << markers.size() << " markers:";
        for( auto const& marker : markers )
            LOG(INFO) << "  - " << marker.first << " (id: " << marker.second << ")";
    }
    
    // Export mesh for visualization
    auto e = exporter( _mesh=mesh, _name="mymesh" );
    e->addRegions();
    e->save();
    
    return 0;
}
