from CRABClient.UserUtilities import config
config = config()

#Do read the below link, for CRAB parameters:                                                                                                 
#https://twiki.cern.ch/twiki/bin/view/CMSPublic/CRAB3ConfigurationFile#CRAB_configuration_parameters                                          
config.General.transferOutputs = True
config.General.transferLogs = False
config.JobType.allowUndistributedCMSSW = True
config.JobType.pluginName = 'Analysis'
config.Data.inputDBS = 'global'
config.Data.unitsPerJob = 10
config.Data.totalUnits = -1
config.Data.splitting = 'LumiBased'
config.Data.ignoreLocality = False
config.Site.storageSite = 'T2_IN_TIFR'
#config.Site.storageSite = 'T2_CH_CERN'
config.General.requestName = 'DptDPt_Data_allchgarge_exclusive_eta1p2_witheff_central_sec'
config.JobType.psetName = '../cfg/chargedepptcorr_central_cfg.py'
config.Data.inputDataset = '/HIMinimumBias10/HIRun2018A-04Apr2019-v1/AOD'
config.Data.outputDatasetTag = 'DptDPt_Data_allchgarge_exclusive_eta1p2_witheff_central_sec'
config.Data.outLFNDirBase = '/store/user/prabhat/'
