from CRABClient.UserUtilities import config
config = config()

config.General.requestName = 'HydjetCymb5Ev8_XeXeMinBias5p44TeV_Mar182024maxRAM2500_DIGIRAW_v0'
#config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'step1_DIGI_L1_DIGI2RAW_HLT_PU.py'
#config.JobType.numCores = 8
config.JobType.maxMemoryMB = 2500

config.Data.inputDataset = '/MinBias/tuos-CRAB3_HydjetCymb5Ev8_XeXeMinBias5p44TeV_Mar182024_GENSIM_v0-cb19750de3b9eb42ce574a60a1a970bb/USER'
config.Data.inputDBS = 'phys03'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
config.Data.outLFNDirBase = '/store/user/tuos/MC_HYDJET/XeXe'
config.Data.publication = True
config.Data.outputDatasetTag = 'CRAB3_HydjetCymb5Ev8_XeXeMinBias5p44TeV_Mar182024maxRAM2500_DIGIRAW_v0'

config.Site.storageSite = 'T2_US_Vanderbilt'

# crab submit -c crab.py
# crab status -d project_/xxx

