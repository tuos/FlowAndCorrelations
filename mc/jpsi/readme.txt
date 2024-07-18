Production page for lowPU pp at 13 TeV: 
https://twiki.cern.ch/twiki/bin/view/CMS/MCFor2018pp13TeVLowPU 

A better gen cff could be found here: https://github.com/CMS-HIN-dilepton/MCRequest/blob/master/LowPU/JpsiMM/JpsiMM_13TeV_TuneCP5_cfi.py 

Real work at lxplus on July 16:
/afs/cern.ch/work/t/tuos/private/dilepton/pythia/CMSSW_10_6_12/src/Configuration/GenProduction/python/JpsiMM_13TeV_TuneCP5_cfi.py
scram b

GEN-SIM:
cmsDriver.py Configuration/GenProduction/python/JpsiMM_13TeV_TuneCP5_cfi.py --conditions auto:phase1_2018_realistic -n 10 --era Run2_2018 --eventcontent RAWSIM  -s GEN,SIM --datatier GEN-SIM --beamspot Realistic25ns13TeVEarly2017Collision --geometry DB:Extended --fileout file:step1.root

Created cfg file copied to ACCRE: /nobackup/user/tuos/egamma/mc/CMSSW_10_6_12/src/JpsiMM_13TeV_TuneCP5_cfi_py_GEN_SIM.py 

Running the cfg: cmsRun JpsiMM_13TeV_TuneCP5_cfi_py_GEN_SIM.py , creating a ROOT file: step1.root


DIGI-RAW:
cmsDriver.py step2  --conditions auto:phase1_2018_realistic -s DIGI:pdigi_valid,L1,DIGI2RAW,HLT:@fake --datatier GEN-SIM-DIGI-RAW -n 10 --geometry DB:Extended --era Run2_2018 --eventcontent RAWSIM --filein file:step1.root  --fileout file:step2.root

Running the created cfg step2_DIGI_L1_DIGI2RAW_HLT.py with : cmsRun step2_DIGI_L1_DIGI2RAW_HLT.py, creating a new ROOT file: step2.root


GEN-SIM-RECO:
cmsDriver.py step3  --conditions auto:phase1_2018_realistic -n 10 --era Run2_2018 --eventcontent AODSIM  -s RAW2DIGI,L1Reco,RECO --datatier GEN-SIM-RECO --geometry DB:Extended --filein file:step2.root  --fileout file:step3.root

Running the created cfg step3_RAW2DIGI_L1Reco_RECO.py with: cmsRun step3_RAW2DIGI_L1Reco_RECO.py and create the final reco file step3.root

After the three steps, MC reco file is produced: /afs/cern.ch/work/t/tuos/private/dilepton/pythia/CMSSW_10_6_12/src/step3.root

=====
Working on 2k events at lxplus (/afs/cern.ch/work/t/tuos/private/dilepton/pythia/CMSSW_10_6_12/src/jobs):
Begin processing the 1st record. Run 1, Event 1, LumiSection 1 on stream 0 at 18-Jul-2024 16:57:36.372 CEST

Begin processing the 2000th record. Run 1, Event 2000, LumiSection 1 on stream 0 at 18-Jul-2024 17:45:18.137 CEST
=> (144+45*60+18)/2000 s/event = 1.431s/event; Actually only produced 374 events => 7.652s/evt?

More outputs from the run:
GenXsecAnalyzer:
------------------------------------
Before Filter: total cross section = 1.690e+07 +- 1.816e+05 pb
Filter efficiency (taking into account weights)= (39.86) / (319.737) = 1.247e-01 +- 7.678e-03
Filter efficiency (event-level)= (374) / (2000) = 1.870e-01 +- 8.719e-03    [TO BE USED IN MCM]

After filter: final cross section = 2.107e+06 +- 1.317e+05 pb
After filter: final fraction of events with negative weights = 0.000e+00 +- 0.000e+00
After filter: final equivalent lumi for 1M events (1/fb) = 4.746e-04 +- 2.968e-05

=============================================
More for the event size:
Singularity> ls -l step1.root 
-rw-r--r--. 1 tuos zh 174415941 Jul 18 17:45 step1.root
174415941/2000/1000=87.2 kB/event; If we count the actual number created event: 174415941/374/1000=466.35 kB/event




