from CRABClient.UserUtilities import config
config = config()

config.General.requestName = 'Pythia8TuneCP5_JPsiMMpThat20_July292024_GEN-SIM-RECO_v0'
#config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'step3_RAW2DIGI_L1Reco_RECO.py'
config.JobType.maxMemoryMB = 2500

config.Data.inputDataset = '/JPsiMMpThat20/tuos-CRAB3_Pythia8TuneCP5_JPsiMMpThat20_July252024_DIGIRAW_v0-4849815c3882d444a04aefb30303bf4e/USER'
config.Data.inputDBS = 'phys03'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
config.Data.outLFNDirBase = '/store/user/tuos/PYTHIA8/JpsiMM'
config.Data.publication = True
config.Data.outputDatasetTag = 'CRAB3_Pythia8TuneCP5_JPsiMMpThat20_July292024maxRAM2500_GEN-SIM-RECO_v0'

config.Site.storageSite = 'T2_US_Vanderbilt'

# crab submit -c crab.py
# crab status -d project_/xxx

