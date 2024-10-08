from CRABClient.UserUtilities import config
config = config()

config.General.requestName = 'PYTHIA8_HYDJET_DiJet_5360GeV_RAWDEBUG_132X_2024-09-15'
config.General.workArea = 'project_PYTHIA8_HYDJET_DiJet_5360GeV_RAWDEBUG_132X_2024-09-15'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'copy_cfg.py'

config.Data.inputDataset = '/PYTHIA8_HYDJET_DiJet_5360GeV_130X/phys_heavyions-PYTHIA8_HYDJET_DiJet_5360GeV_RAWDEBUG_132X_2024-09-15-cc118d95320c1c5d965f7d5e145c7fa5/USER'
config.Data.inputDBS = 'phys03'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
config.Data.outLFNDirBase = '/store/user/tuos/EOStransfer2024/crabSubmit_RAWDEBUG_PYTHIA8_HYDJET_DiJet_5360GeV_132X_2024-09-15'
config.Data.publication = True
config.Data.outputDatasetTag = 'PYTHIA8_HYDJET_DiJet_5360GeV_RAWDEBUG_132X_2024-09-15'

config.Site.storageSite = 'T2_US_Vanderbilt'



