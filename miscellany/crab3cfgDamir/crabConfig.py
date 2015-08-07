from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = 'OUT'
#config.General.workArea = 'crab_projects'

############################

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'step2_RAW2DIGI_L1Reco_MB_AOD.py'
config.JobType.maxJobRuntimeMin = 60*48 #minutes
config.JobType.disableAutomaticOutputCollection = False #recognizes automatically output string from python file
config.JobType.outputFiles = ['step2_RAW2DIGI_L1Reco_MB_AOD.root']

############################

config.section_("Data")
config.Data.inputDBS = 'global'
config.Data.inputDataset = '/HIMinBiasUPC/HIRun2011-v1/RAW'
config.Data.lumiMask = 'lumiInputMB.json'
#config.Data.inputDataset = '/VBF_HToTauTau_M-125_13TeV-powheg-pythia6/Phys14DR-PU20bx25_tsg_PHYS14_25_V1-v2/MINIAODSIM'
#VBF_HToTauTau_M-125_13TeV-powheg-pythia6
#config.Data.dbsUrl = 'global'
config.Data.splitting = 'LumiBased'
#config.Data.splitting = 'LumiBased'
#config.Data.publication = True
config.Data.unitsPerJob = 1
config.Data.publication = False
config.Data.outLFNDirBase = '/store/user/tuos/tmp'
#config.Data.totalUnits = -1
#config.Data.publishDbsUrl = 'test'
#config.Data.publishDataName = 'NeutrinoL1FlatPU_CRAB3'
config.section_("Site")
config.Site.storageSite = 'T2_US_Vanderbilt'
#config.Site.whitelist = ['T2_US_MIT']
config.Site.whitelist = ['T2_US_Vanderbilt']

