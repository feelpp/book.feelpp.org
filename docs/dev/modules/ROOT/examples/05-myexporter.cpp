// tag::all[]
#include <feel/feel.hpp>

// tag::main[]
int main(int argc, char**argv )
{
  using namespace Feel;
  Environment env( _argc=argc, _argv=argv,
      _about=about(_name="myexporter",
        _author="Christophe Prud'homme",
        _email="christophe.prudhomme@feelpp.org"));

  // tag::meshspace[]
  // circle - geometrical order: 2
  auto mesh = unitCircle<2>();

  // circle - geometrical order: 1
  auto meshp1 = unitCircle<1>();

  auto Xh = Pch<2>( mesh );
  // end::meshspace[]

  // tag::expr[]
  auto myExpr = sin(pi*Px());
  // end::expr[]

  // tag::project[]
  auto v = project( _space=Xh, _range=elements(mesh),
      _expr=myExpr);
  // end::project[]

  // tag::exporter[]
  auto exhi = exporter( _mesh=mesh, _name="exhi" );
  auto exlo = exporter( _mesh=meshp1, _name="exlo" );
  auto exhilo = exporter( _mesh=lagrangeP1(_space=Xh)->mesh(),_name="exhilo");

  int max = 10; double dt = 0.1;
  double time = 0;
  for (int i = 0; i<max; i++)
  {
    exhilo->step( time )->add( "vhilo", v );
    exlo->step( time )->add( "vlo", v );
    exhi->step( time )->add( "vhi", v );
    time += dt;
    // tag::save[]
    exhi->save();
    exlo->save();
    exhilo->save();
    // end::save[]
  }
  // end::exporter[]
}
// end::main[]
// end::all[]
