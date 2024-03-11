
# set up
cmssw-el6
export SCRAM_ARCH=slc6_amd64_gcc630
cmsrel CMSSW_9_4_3
cd CMSSW_9_4_3/src/
cmsenv

# get gen fragment
curl -s -k https://cms-pdmv-prod.web.cern.ch/mcm/public/restapi/requests/get_fragment/HIN-HINXeXeFall17GS-00005 --retry 3 --create-dirs -o Configuration/GenProduction/python/HIN-HINXeXeFall17GS-00005-fragment.py

# compile
scram b

#cmsDriver for GEN-SIM:
cmsDriver.py Configuration/GenProduction/python/HIN-HINXeXeFall17GS-00005-fragment.py --mc --eventcontent RAWSIM --datatier GEN-SIM --conditions 93X_mc2017_realistic_v3 --beamspot RealisticXeXeCollision2017 --step GEN,SIM --nThreads 1 --scenario HeavyIons --geometry DB:Extended --era Run2_2017

#cmsDriver for DIGI:
cmsDriver.py step1 --mc --eventcontent RAWSIM --pileup HiMixNoPU --datatier GEN-SIM-DIGI-RAW --conditions 94X_mc2017_realistic_ForXeXe_v7 --step DIGI:pdigi_valid,L1,DIGI2RAW,HLT:XeXe --nThreads 8 --geometry DB:Extended --era Run2_2017_pp_on_XeXe --filein file:HIN-HINXeXeFall17GS-00005-fragment_py_GEN_SIM.root

#cmsDriver for RECO:
cmsDriver.py step2 --mc --eventcontent AODSIM --datatier GEN-SIM-RECO --conditions 94X_mc2017_realistic_ForXeXe_v7 --step RAW2DIGI,L1Reco,RECO --nThreads 8 --geometry DB:Extended --era Run2_2017_pp_on_XeXe --filein file:step1_DIGI_L1_DIGI2RAW_HLT_PU.root



