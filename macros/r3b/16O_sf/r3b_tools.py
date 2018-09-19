import os
import subprocess as sp

cwd = os.getcwd()


### geo files
os.chdir("../geo/")
print "Geo files"

## fi10
# print " Fi10"
# sp.call(["root", "-l", "-q", 'create_fi10_geo.C("16O")'])

## fi11
# print " Fi11"
# sp.call(["root", "-l", "-q", 'create_fi11_geo.C("16O")'])


# ## fi3a
# print " Fi3a"
# sp.call(["root", "-l", "-q", 'create_fi3a_geo.C("16O")'])

# ## fi3b
# print " Fi3b"
# sp.call(["root", "-l", "-q", 'create_fi3b_geo.C("16O")'])

# ## fi7
# print "Fi7"
# sp.call(["root", "-l", "-q", 'create_fi7_geo.C("16O")'])

# ## fi8
# print "Fi8"
# sp.call(["root", "-l", "-q", 'create_fi8_geo.C("16O")'])
# sp.call(["root", "-l", "-q", 'create_gfi_geo_test.C("16O")'])

## dToF
print "dToF"
sp.call(["root", "-l", "-q", 'create_dtof_geo.C("16O")'])

## target
# print "target"
# sp.call(["root", "-l", "-q", 'create_target_geo.C("LeadTarget_200mg")'])

### run sim
# os.chdir(cwd)
# sp.call(["root", "-l", "-q", "run_sim.C"])
