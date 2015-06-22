from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'AMPT7TeVstring_June2015_generation_run0pp13TeVv1v2'
#config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'PrivateMC'
config.JobType.psetName = 'ampt_StringMelting_pp13TeV_cfg.py'

config.Data.primaryDataset = 'MinBias'
config.Data.splitting = 'EventBased'
config.Data.unitsPerJob = 5000
NJOBS = 1000  # This is not a configuration parameter, but an auxiliary variable that we use in the next line.
config.Data.totalUnits = config.Data.unitsPerJob * NJOBS
config.Data.outLFNDirBase = '/store/user/tuos/MC_AMPT/PbPb5TeV/StringMelting/v1/June19/run0ppv1/energy13TeVv2'
config.Data.publication = True
config.Data.publishDataName = 'CRAB3_AMPT5TeVstring_June2015_generation_run0pp13TeVv1v2'

config.Site.storageSite = 'T2_US_Vanderbilt'
