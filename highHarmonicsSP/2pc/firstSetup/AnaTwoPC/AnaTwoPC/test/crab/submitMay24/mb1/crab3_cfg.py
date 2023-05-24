from CRABClient.UserUtilities import config
config = config()

config.General.requestName = 'PbPbMB1LumiBased_2pc_May24'
config.General.workArea = 'PbPbMB_2pc_May24'
config.General.transferOutputs = True
config.General.transferLogs = False
#config.JobType.allowUndistributedCMSSW = True

config.JobType.pluginName = 'Analysis'
config.JobType.maxMemoryMB = 3500
config.JobType.psetName = 'Config_PbPb_MiniAOD.py'
config.Data.inputDataset = '/HIMinimumBias1/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
config.Data.inputDBS = 'global'
config.Data.lumiMask = 'https://cms-service-dqmdc.web.cern.ch/CAF/certification/Collisions18/HI/PromptReco/Cert_326381-327564_HI_PromptReco_Collisions18_JSON.txt'
#config.Data.splitting = 'FileBased'
#config.Data.unitsPerJob = 1
#config.Data.splitting = 'Automatic'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 10
config.Data.totalUnits = -1
config.Data.partialDataset = True

config.Data.outLFNDirBase = '/store/user/tuos/qm2023/anaMay24/PbPbMB1LumiBased_2pc_May24'
config.Data.publication = False
config.Data.outputDatasetTag = 'PbPbMB1LumiBased_2pc_May24'

#config.Site.whitelist = ['T2_US_Vanderbilt']
config.Site.storageSite = 'T2_US_Vanderbilt'

