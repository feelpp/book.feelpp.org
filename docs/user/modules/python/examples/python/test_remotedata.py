import pyfeelpp.core as core
import sys
e=core.Environment(sys.argv)

readme=core.download( "github:{repo:feelpp,path:README.adoc}", worldComm=core.Environment.worldCommPtr() )[0]

print("downloaded Feel++ README.adoc from Github: ",readme)
