from WMCore.Configuration import Configuration
config = Configuration()

config.section_('General')
config.General.transferOutputs = True
config.General.requestName = 'HydjetMB_trackCorrections_recoMatchv01'

config.section_('JobType')
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'recoMatch_cfg.py'
config.JobType.outputFiles = ['trackCorrections.root']

config.section_('Data')
config.Data.inputDBS = 'global'
config.Data.inputDataset = '/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/HiFall13-STARTHI53_V28-v2/GEN-SIM'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
config.Data.totalUnits = 100000
config.Data.publishDBS = 'https://cmsweb.cern.ch/dbs/prod/phys03/DBSWriter/'
config.Data.publication = True
config.Data.publishDataName = 'HydjetMB_trackCorrections_cmssw5319_recoMatchv01'
config.Data.outLFNDirBase = '/store/user/tuos/tmp/eff/june20/v01'

config.section_('Site')
#config.Site.whitelist = ['T2_US_MIT']
config.Site.storageSite = 'T2_US_Vanderbilt'
