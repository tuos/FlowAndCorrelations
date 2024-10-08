from CRABClient.UserUtilities import config
config = config()

config.General.requestName = 'PYTHIA8_HYDJET_DiJet_5360GeV_RAWDEBUG_141X_2024-08-30'
config.General.workArea = 'project_PYTHIA8_HYDJET_DiJet_5360GeV_RAWDEBUG_141X_2024-08-30'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'copy_cfg.py'

config.Data.inputDataset = '/PYTHIA8_HYDJET_DiJet_5360GeV_141X/phys_heavyions-PYTHIA8_HYDJET_DiJet_5360GeV_RAWDEBUG_141X_2024-08-30-6cfe57b49168618248ca376c9e674e6d/USER'
config.Data.inputDBS = 'phys03'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
config.Data.outLFNDirBase = '/store/user/tuos/EOStransfer2024/crabSubmit_RAWDEBUG_PYTHIA8_HYDJET_DiJet_5360GeV_141X_2024-08-30'
config.Data.publication = True
config.Data.outputDatasetTag = 'PYTHIA8_HYDJET_DiJet_5360GeV_RAWDEBUG_141X_2024-08-30'

config.Site.storageSite = 'T2_US_Vanderbilt'



