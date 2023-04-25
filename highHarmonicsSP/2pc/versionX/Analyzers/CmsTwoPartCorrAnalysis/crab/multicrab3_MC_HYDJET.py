#from WMCore.Configuration import Configuration
from CRABClient.UserUtilities import config
config = config()

#config.General.workArea = 'MC_comparison_GEN_Reco_2p0pttrg3p0_1p0ptass2p0_eta2p4_cent010_3040_6080_Sep25_2022_subashcode'
config.General.workArea = 'MC_HINtestRun3_0p3pttrg3p0_0p3ptass3p0_eta2p4_genpix_cent3070_Nov26_2022'
config.General.transferOutputs = True
config.General.transferLogs = False
config.JobType.pluginName = 'Analysis'
config.Data.unitsPerJob = 5 #For MC Jobs
config.Data.totalUnits = -1
#config.Data.inputDBS = 'global'
config.Data.inputDBS = 'phys03'
#config.Data.splitting = 'LumiBased'
config.Data.splitting = 'FileBased'
config.JobType.allowUndistributedCMSSW = True 
config.Data.outLFNDirBase = '/store/user/kpanja/'
config.Data.publication = False
config.Site.storageSite = 'T2_IN_TIFR'
#config.Site.storageSite = 'T3_CH_CERNBOX'
#config.Site.storageSite = 'T2_US_Nebraska'

#############################################################################################
## From now on that's what users should modify: this is the a-la-CRAB2 configuration part. ##
#############################################################################################

###############################
#    Standard analysis        #
###############################  
#central 0-5

config.General.requestName = 'MC_HINtestRun3_0p3pttrg3p0_0p3ptass3p0_eta2p4_genpix_cent3070_Nov26_2022'
#config.JobType.psetName = '../cfg/chargedepptcorr_MC_central_cfg_Run3_AOD.py'
config.JobType.psetName = '../cfg/chargedepptcorr_MC_central_cfg_Run3_AOD_genpix.py'
config.Data.inputDataset ='/Hydjet_5360GeV_GEN_SIM/subehera-MB_Hydjet_Run3_recodebug_step4-625ffd2ccfcbfe30cf75ced0ae60f7d8/USER'
config.Data.outputDatasetTag = 'MC_HINtestRun3_0p3pttrg3p0_0p3ptass3p0_eta2p4_genpix_cent3070_Nov26_2022'
