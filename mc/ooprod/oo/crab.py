from CRABClient.UserUtilities import config
config = config()

config.General.requestName = 'AngantyrCP5_OOMinBias5362GeV_Mar262026_GEN_v1'
#config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'PrivateMC'
config.JobType.psetName = 'gemini_fragment_pthat15_py_GEN.py'

config.Data.outputPrimaryDataset = 'Pythia8_Angantyr_OO_pThat15_5p36TeV'
config.Data.splitting = 'EventBased'
config.Data.unitsPerJob = 10000
NJOBS = 5000  # This is not a configuration parameter, but an auxiliary variable that we use in the next line.
config.Data.totalUnits = config.Data.unitsPerJob * NJOBS
config.Data.outLFNDirBase = '/store/user/tuos/OO/mc/Angantyr/OOmar26'
config.Data.publication = True
config.Data.outputDatasetTag = 'CRAB3_AngantyrCP5_OOMinBias5362GeV_Mar262026_GEN_v1'

config.Site.storageSite = 'T2_US_Vanderbilt'

# crab submit -c crab.py
# crab status -d project_/xxx

