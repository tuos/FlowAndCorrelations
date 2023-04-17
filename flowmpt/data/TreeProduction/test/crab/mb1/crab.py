from CRABClient.UserUtilities import config
config = config()

config.General.requestName = 'PbPbMB1_v2mptTree_Oct22'
config.General.workArea = 'project_PbPbMB1_v2mptTree_Oct22'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'Config_pbpbMB_MiniAOD_cfg.py'
config.JobType.allowUndistributedCMSSW = True

config.Data.inputDataset = '/HIMinimumBias1/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
#config.Data.splitting = 'Automatic'
config.Data.unitsPerJob = 10
config.Data.outLFNDirBase = '/store/user/tuos/i_ana2021/trees/PbPbMB/PbPbMB1_v2mptTree_Oct22'
config.Data.publication = False
config.Data.outputDatasetTag = 'PbPbMB1_v2mptTree_Oct22'

config.Site.storageSite = 'T2_US_Vanderbilt'

# crab submit -c crab.py
# crab status -d project_/xxx

