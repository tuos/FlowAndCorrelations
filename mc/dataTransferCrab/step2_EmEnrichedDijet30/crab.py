from CRABClient.UserUtilities import config
config = config()

config.General.requestName = '2023_Aug_18_step2_DIGI2RAW_Pythia8_Embedded_EmEnrichedDijet30_TuneCP5_BPix_masked'
config.General.workArea = 'project_2023_Aug_18_step2_DIGI2RAW_Pythia8_Embedded_EmEnrichedDijet30_TuneCP5_BPix_masked'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'copy_cfg.py'

config.Data.inputDataset = '/Pythia8_EmEnrichedDijet30_HydjetEmbedded_TuneCP5_13_0_12/phys_heavyions-2023_Aug_18_step2_DIGI2RAW_Pythia8_Embedded_EmEnrichedDijet30_TuneCP5_BPix_masked-a5bfb106497b71b099008d4be1348ef7/USER'
config.Data.inputDBS = 'phys03'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
config.Data.outLFNDirBase = '/store/user/tuos/Run3MC_PbPb/DIGI2RAW/Pythia8_EmEnrichedDijet30_HydjetEmbedded_TuneCP5_13_2_0_DIGI2RAW_BPix_masked'
config.Data.publication = True
config.Data.outputDatasetTag = '2023_Aug_18_step2_DIGI2RAW_Pythia8_Embedded_EmEnrichedDijet30_TuneCP5_BPix_masked'

config.Site.storageSite = 'T2_US_Vanderbilt'



