from CRABClient.UserUtilities import config
config = config()

config.General.requestName = 'HydjetCymb5Ev8_XeXeMinBias5p44TeV_Mar182024_GENSIM_v0'
#config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'PrivateMC'
config.JobType.psetName = 'HIN-HINXeXeFall17GS-00005-fragment_py_GEN_SIM.py'

config.Data.outputPrimaryDataset = 'MinBias'
config.Data.splitting = 'EventBased'
config.Data.unitsPerJob = 50
NJOBS = 10000  # This is not a configuration parameter, but an auxiliary variable that we use in the next line.
config.Data.totalUnits = config.Data.unitsPerJob * NJOBS
config.Data.outLFNDirBase = '/store/user/tuos/MC_HYDJET/XeXe'
config.Data.publication = True
config.Data.outputDatasetTag = 'CRAB3_HydjetCymb5Ev8_XeXeMinBias5p44TeV_Mar182024_GENSIM_v0'

config.Site.storageSite = 'T2_US_Vanderbilt'

# crab submit -c crab.py
# crab status -d project_/xxx

