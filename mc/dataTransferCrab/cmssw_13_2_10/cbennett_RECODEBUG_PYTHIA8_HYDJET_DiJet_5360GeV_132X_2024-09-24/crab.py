from CRABClient.UserUtilities import config
config = config()

config.General.requestName = 'PYTHIA8_HYDJET_DiJet_5360GeV_RECODEBUG_132X_2024-09-24'
config.General.workArea = 'project_PYTHIA8_HYDJET_DiJet_5360GeV_RECODEBUG_132X_2024-09-24'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'copy_cfg.py'

config.Data.inputDataset = '/PYTHIA8_HYDJET_DiJet_5360GeV_130X/phys_heavyions-PYTHIA8_HYDJET_DiJet_5360GeV_RECODEBUG_132X_2024-09-24-a4f3197616c97ebefacf948d7154db3b/USER'
config.Data.inputDBS = 'phys03'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
config.Data.outLFNDirBase = '/store/user/tuos/EOStransfer2024/crabSubmit_RECODEBUG_PYTHIA8_HYDJET_DiJet_5360GeV_132X_2024-09-24'
config.Data.publication = True
config.Data.outputDatasetTag = 'PYTHIA8_HYDJET_DiJet_5360GeV_RECODEBUG_132X_2024-09-24'

config.Site.storageSite = 'T2_US_Vanderbilt'



