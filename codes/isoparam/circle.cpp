// -*- coding: utf-8; mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- vim:fenc=utf-8:ft=tcl:et:sw=4:ts=4:sts=4
#include <feel/feel.hpp>

int main(int argc, char**argv )
{
	using namespace Feel;
	Environment env( _argc=argc, _argv=argv,
                     _desc=feel_options(),
                     _about=about(_name="mymesh",
                                  _author="Christophe Prud'homme",
                                  _email="christophe.prudhomme@feelpp.org"));

    // tag::isoparam[]
    // genere le maillage $\Omega^1_h$ associe une transformation affine
    auto mesh1 = unitCircle<1>();
    auto area1 = integrate( _range=elements(mesh1),
                            _expr=cst(1.)).evaluate().norm();
    std::cout << "|pi-surface<1>| = " << math::abs(pi-area1)
              << "\n";

    // genere le maillage $\Omega^2_h$ associe une transformation d'ordre 2
    auto mesh2 = unitCircle<2>();
    auto area2 = integrate( _range=elements(mesh2),
                            _expr=cst(1.)).evaluate().norm();
    std::cout << "|pi-surface<2>| = " << math::abs(pi-area2)
              << "\n";
    // end::isoparam[]

    std::ofstream ofs;
    if ( fs::exists( fs::path("circle.dat") ) )
        ofs.open( "circle.dat", std::ios::app );
    else
    {
        ofs.open( "circle.dat" );
        ofs << std::right << std::setw( 10 ) << "h"
            << std::right << std::setw( 10 ) << "error1"
            << std::right << std::setw( 10 ) << "error2" << "\n";
    }
    ofs
        << std::right << std::setw( 10 ) << std::fixed  << std::setprecision( 4 ) << Environment::vm(_name="mesh2d.hsize").as<double>()
        << " "
        << std::right << std::setw( 10 ) << std::scientific  << std::setprecision( 5 ) << math::abs(pi-area1)
        << " "
        << std::right << std::setw( 10 ) << std::scientific  << std::setprecision( 5 ) << math::abs(pi-area2) << "\n";

}
