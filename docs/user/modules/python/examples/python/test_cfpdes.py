import feelpp
from feelpp.toolboxes.core import *
from feelpp.toolboxes.cfpdes import *

app = feelpp.Environment(["myapp"], opts= toolboxes_options("coefficient-form-pdes", "cfpdes"),config=feelpp.localRepository(""))

case=feelpp.download( "github:{repo:feelpp,path:toolboxes/coefficientformpdes/cases/heat/ThermalBridgesENISO10211/", worldComm=app.worldCommPtr() )[0]
casedfile=case+'/thermo2dCase2.cfg'
feelpp.Environment.setConfigFile(casefile) 
f = cfpdes(dim=2)
if not f.isStationary():
    f.setTimeFinal(10*f.timeStep())
[ok,meas]=simulate(f)
f.checkResults()

if ok: # <1>
    meas = f.postProcessMeasures().values()

    try:
        import pandas as pd
        df=pd.DataFrame([meas])
        print(df)
    except ImportError:
        print("cannot import pandas, no problem it was just a test")
else:
    print("error during simulation, cannot proceed with data analysis")
