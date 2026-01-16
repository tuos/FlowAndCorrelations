from CRABClient.UserUtilities import config
config = config()

config.General.requestName = 'v2SP_Jan12_trk10hf40mb'
config.General.workArea = 'projects_crab'
config.General.transferOutputs = True
config.General.transferLogs = False
config.JobType.allowUndistributedCMSSW = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'Config_ppreco_SPdata_cfg.py'
config.Data.inputDataset = '/MinBias_OO_5p36TeV_hijing/HINOOSpring25MiniAOD-NoPU_150X_mcRun3_2025_forOO_realistic_v7-v2/MINIAODSIM'
config.Data.inputDBS = 'global'
#config.Data.lumiMask = 'golden_oo.json'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
config.Data.outLFNDirBase = '/store/user/tuos/OO/mc/SP/mbhijing'
config.Data.publication = False
config.Data.outputDatasetTag = 'v2SP_Jan12_trk10hf40mb'

#config.Site.whitelist = ['T2_US_Vanderbilt']
config.Site.storageSite = 'T2_US_Vanderbilt'

# crab submit -c crab3_multicrab_cfg.py to execute 
# crab status -d crab_projects/xxx to check status 
