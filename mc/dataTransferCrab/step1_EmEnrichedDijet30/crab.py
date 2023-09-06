from CRABClient.UserUtilities import config
config = config()

config.General.requestName = '2023_Aug_18_step1_GENSIM_Pythia8_Embedded_EmEnrichedDijet30_TuneCP5'
config.General.workArea = 'project_2023_Aug_18_step1_GENSIM_Pythia8_Embedded_EmEnrichedDijet30_TuneCP5'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'copy_cfg.py'

config.Data.inputDataset = '/Pythia8_EmEnrichedDijet30_HydjetEmbedded_TuneCP5_13_0_12/phys_heavyions-2023_Aug_18_step1_GENSIM_Pythia8_Embedded_EmEnrichedDijet30_TuneCP5-b7113c42b395bb3f751f47251c829036/USER'
config.Data.inputDBS = 'phys03'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
config.Data.outLFNDirBase = '/store/user/tuos/Run3MC_PbPb/GENSIM/Pythia8_EmEnrichedDijet30_HydjetEmbedded_TuneCP5_13_0_12'
config.Data.publication = True
config.Data.outputDatasetTag = '2023_Aug_18_step1_GENSIM_Pythia8_Embedded_EmEnrichedDijet30_TuneCP5'

config.Site.storageSite = 'T2_US_Vanderbilt'



