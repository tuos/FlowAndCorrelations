from CRABClient.UserUtilities import config
config = config()

config.General.requestName = 'Pythia8TuneCP5_JPsiMMpThat02_July182024_generation_v0'
#config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'PrivateMC'
config.JobType.psetName = 'JpsiMM_13TeV_TuneCP5_cfi_py_GEN_SIM.py'

config.Data.outputPrimaryDataset = 'JPsiMMpThat02'
#config.Data.primaryDataset = 'MinBias'
config.Data.splitting = 'EventBased'
config.Data.unitsPerJob = 5000
NJOBS = 2000  # This is not a configuration parameter, but an auxiliary variable that we use in the next line.
config.Data.totalUnits = config.Data.unitsPerJob * NJOBS
config.Data.outLFNDirBase = '/store/user/tuos/PYTHIA8/JpsiMM'
config.Data.publication = True
config.Data.outputDatasetTag = 'CRAB3_Pythia8TuneCP5_JPsiMMpThat02_July182024_generation_v0'

config.Site.storageSite = 'T2_US_Vanderbilt'

# crab submit -c crab.py
# crab status -d project_/xxx

