from CRABClient.UserUtilities import config
config = config()

config.General.requestName = 'PythiaProductionMinBiasPileup'
config.General.workArea = 'project_PythiaProductionMinBiasPileup'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'copy_cfg.py'

config.Data.inputDataset = '/Pythia_MinBiasCP5_5362GeVPPRef_11_3_2023_GENSIM/phys_heavyions-crab_PythiaProductionMinBiasPileup-3c4e4de8459f2b2c3fb639ae015f3a0f/USER'
config.Data.inputDBS = 'phys03'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
config.Data.outLFNDirBase = '/store/user/tuos/EOStransfer2024/2023_ppRef_JetCalibrations'
config.Data.publication = True
config.Data.outputDatasetTag = 'PythiaProductionMinBiasPileup'

config.Site.storageSite = 'T2_US_Vanderbilt'



