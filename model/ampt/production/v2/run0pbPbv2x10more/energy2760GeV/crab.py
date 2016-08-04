from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'AMPTstring_June2015_generation_run0pbPb2760GeVv2x10more'
#config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'PrivateMC'
config.JobType.psetName = 'ampt_StringMelting_pbPb2760GeV_cfg.py'

config.Data.primaryDataset = 'MinBias'
config.Data.splitting = 'EventBased'
config.Data.unitsPerJob = 50
NJOBS = 10000  # This is not a configuration parameter, but an auxiliary variable that we use in the next line.
config.Data.totalUnits = config.Data.unitsPerJob * NJOBS
config.Data.outLFNDirBase = '/store/user/tuos/MC_AMPT/PbPb5TeV/StringMelting/v2/June26/run0pbPbv2x10more/energy2760GeV'
config.Data.publication = True
config.Data.publishDataName = 'CRAB3_AMPTstring_June2015_generation_run0pbPb2760GeVv2x10more'

config.Site.storageSite = 'T2_US_Vanderbilt'
