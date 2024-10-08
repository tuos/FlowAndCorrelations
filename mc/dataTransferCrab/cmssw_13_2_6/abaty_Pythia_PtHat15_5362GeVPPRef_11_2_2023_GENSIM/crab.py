from CRABClient.UserUtilities import config
config = config()

config.General.requestName = 'PythiaProductionPtHat15'
config.General.workArea = 'project_PythiaProductionPtHat15'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'copy_cfg.py'

config.Data.inputDataset = '/Pythia_PtHat15_5362GeVPPRef_11_2_2023_GENSIM/phys_heavyions-crab_PythiaProductionPtHat15-595a6d36bd65354a977ff08c48cb281a/USER'
config.Data.inputDBS = 'phys03'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
config.Data.outLFNDirBase = '/store/user/tuos/EOStransfer2024/2023_ppRef_JetCalibrations'
config.Data.publication = True
config.Data.outputDatasetTag = 'PythiaProductionPtHat15'

config.Site.storageSite = 'T2_US_Vanderbilt'



