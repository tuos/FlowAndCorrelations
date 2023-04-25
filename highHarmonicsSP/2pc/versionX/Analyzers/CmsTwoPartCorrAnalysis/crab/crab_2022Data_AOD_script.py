if __name__ == '__main__':

    from CRABAPI.RawCommand import crabCommand
    #from CRABClient.ClientExceptions import ClientException
    #from httplib import HTTPException
    
    from CRABClient.UserUtilities import config
    config = config()

    config.General.workArea = '2022_AOD_JSON_newEventSelection_script'
    config.General.transferOutputs = True
    config.General.transferLogs = False
    config.JobType.pluginName = 'Analysis'
    config.JobType.maxMemoryMB = 3500
    config.Data.unitsPerJob = 10
    config.Data.totalUnits = -1
    config.Data.inputDBS = 'global'
    config.Data.splitting = 'LumiBased'

    config.Data.outLFNDirBase = '/store/user/rpradhan/'
    config.Data.publication = False
    #config.Site.storageSite = 'T2_IN_TIFR'
    config.Site.storageSite = 'T3_CH_CERNBOX'
    
    config.JobType.allowUndistributedCMSSW = True #Done due to new CMSSW version 
    
    config.General.requestName = 'PbPb_AllCent_Raw23_MB_JSON_newEventSelections_GeneralTrack_vnpT_Feb19_script'
    #config.JobType.psetName = '../cfg/chargedepptcorr_MC_central_cfg_Run3_AOD.py'
    config.JobType.psetName = '../cfg/chargedepptcorr_MC_central_cfg_Run3_AOD_newEventSelection.py'
    #config.JobType.psetName = '../cfg/chargedepptcorr_MC_central_cfg_Run3_AOD_MergedTrack.py'
    config.Data.inputDataset = '/HITestRaw23/HIRun2022A-PromptReco-v1/AOD'
    config.Data.lumiMask = '/eos/user/c/cmsdqm/www/CAF/certification/Collisions22/Collisions2022HISpecial/Cert_Collisions2022HISpecial_362293_362323_Golden.json'
    config.Data.outputDatasetTag = 'PbPb_AllCent_Raw23_MB_JSON_newEventSelections_GeneralTrack_vnpT_Feb19_script'

    def submit(config):
        try:
            crabCommand('submit', config = config)
    submit(config)
