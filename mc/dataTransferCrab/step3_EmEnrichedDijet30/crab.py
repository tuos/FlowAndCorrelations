from CRABClient.UserUtilities import config
config = config()

config.General.requestName = '2023_Aug_18_step3_RAW2DIGI_MINIAODSIM_Pythia8_Embedded_EmEnrichedDijet30_TuneCP5_BPix_masked'
config.General.workArea = 'project_2023_Aug_18_step3_RAW2DIGI_MINIAODSIM_Pythia8_Embedded_EmEnrichedDijet30_TuneCP5_BPix_masked'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'copy_cfg.py'

config.Data.inputDataset = '/Pythia8_EmEnrichedDijet30_HydjetEmbedded_TuneCP5_13_0_12/phys_heavyions-2023_Aug_18_step3_RAW2DIGI_MINIAODSIM_Pythia8_Embedded_EmEnrichedDijet30_TuneCP5_BPix_masked-d49791fa1e1bd5c123115cd5fc62f9a8/USER'
config.Data.inputDBS = 'phys03'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
config.Data.outLFNDirBase = '/store/user/tuos/Run3MC_PbPb/MiniAOD/Pythia8_Embedded_EmEnrichedDijet30_TuneCP5_13_2_0_MINIAODSIM_BPix_masked'
config.Data.publication = True
config.Data.outputDatasetTag = '2023_Aug_18_step3_RAW2DIGI_MINIAODSIM_Pythia8_Embedded_EmEnrichedDijet30_TuneCP5_BPix_masked'

config.Site.storageSite = 'T2_US_Vanderbilt'



