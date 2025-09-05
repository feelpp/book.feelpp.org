#include <feel/feel.hpp>

int main( int argc, char* argv[] )
{
    using namespace Feel;

    // Modern Environment initialization with named arguments
    Environment env( _argc=argc, _argv=argv,
                     _about=about( _name="env",
                                   _author="Feel++ Consortium",
                                   _email="feelpp-devel@feelpp.org") );
    
    std::cout << "proc " << Environment::rank()
              << " of " << Environment::numberOfProcessors()
              << std::endl;

    // Print some environment information
    std::cout << "Feel++ version: " << Feel::Info::version() << std::endl;
    std::cout << "Git revision: " << Feel::Info::revision() << std::endl;
    std::cout << "Build id: " << Feel::Info::buildId() << std::endl;
    
    // Display parallel information
    if ( Environment::numberOfProcessors() > 1 )
    {
        std::cout << "Running in parallel with " 
                  << Environment::numberOfProcessors() 
                  << " processes" << std::endl;
    }
    else
    {
        std::cout << "Running in sequential mode" << std::endl;
    }

    // Display repository information
    std::cout << "Repository: " << Environment::repository() << std::endl;
    std::cout << "Config: " << Environment::config() << std::endl;

    return 0;
}

