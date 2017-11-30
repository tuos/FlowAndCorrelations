from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'EPOSLHC_Nov2017_PbPb5020GeV_200kv1_step2'
config.General.workArea = 'project_EPOSLHC_Nov2017_PbPb5020GeV_200kv1_step2'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'step2_DIGI_L1_DIGI2RAW_HLT_RAW2DIGI_L1Reco.py'

config.Data.inputDataset = '/MinBias/tuos-CRAB3_EPOSLHC_Nov2017_PbPb5020GeV_accre200kv1-4f575002e197e545b83aa7c136fcb1f8/USER'
config.Data.inputDBS = 'phys03'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 5
config.Data.outLFNDirBase = '/store/user/tuos/EPOSLHC/crab/Nov2017PbPb5020GeV/200kv1_step2'
config.Data.publication = True
config.Data.outputDatasetTag = 'EPOSLHC_Nov2017_PbPb5020GeV_200kv1_step2'

config.Site.storageSite = 'T2_US_Vanderbilt'
