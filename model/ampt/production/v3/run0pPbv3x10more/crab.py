from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'AMPTstring_July2015_generation_run0pPb5020GeVv3x10more'
#config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'PrivateMC'
config.JobType.psetName = 'ampt_StringMelting_pPb5020GeV_cfg.py'

config.Data.primaryDataset = 'MinBias'
config.Data.splitting = 'EventBased'
config.Data.unitsPerJob = 200
NJOBS = 10000  # This is not a configuration parameter, but an auxiliary variable that we use in the next line.
config.Data.totalUnits = config.Data.unitsPerJob * NJOBS
config.Data.outLFNDirBase = '/store/user/tuos/MC_AMPT/PbPb5TeV/StringMelting/v3/July09/run0pPbv3x10more'
config.Data.publication = True
config.Data.publishDataName = 'CRAB3_AMPTstring_July2015_generation_run0pPb5020GeVv3x10more'

config.Site.storageSite = 'T2_US_Vanderbilt'
