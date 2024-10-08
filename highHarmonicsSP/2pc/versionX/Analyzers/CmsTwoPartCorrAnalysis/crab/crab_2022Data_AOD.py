#from CRABAPI.RawCommand import crabCommand
from CRABClient.UserUtilities import config
#from CRABClient.ClientExceptions import ClientException
#from httplib import HTTPException

config = config()

config.General.workArea = '2022_AOD_JSON_newEventSelection_Feb22_2023'
#config.General.requestName = 'PbPb_AllCent_RAW0_MB_JSON_GeneralTrack_vnpT_Jan30'
config.General.transferOutputs = True
config.General.transferLogs = False
config.JobType.pluginName = 'Analysis'
config.JobType.maxMemoryMB = 3500
config.Data.unitsPerJob = 10
config.Data.totalUnits = -1
config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
config.Data.partialDataset = True

config.Data.outLFNDirBase = '/store/user/rpradhan/'
config.Data.publication = False
#config.Site.storageSite = 'T2_IN_TIFR'
config.Site.storageSite = 'T3_CH_CERNBOX'


#RAW0
config.General.requestName = 'PbPb_AllCent_Raw23_MB_JSON_newEventSelections_GeneralTrack_vnpT_Feb22'
#config.JobType.psetName = '../cfg/chargedepptcorr_MC_central_cfg_Run3_AOD.py'
config.JobType.psetName = '../cfg/chargedepptcorr_MC_central_cfg_Run3_AOD_newEventSelection.py'
#config.JobType.psetName = '../cfg/chargedepptcorr_MC_central_cfg_Run3_AOD_MergedTrack.py'
config.Data.inputDataset = '/HITestRaw23/HIRun2022A-PromptReco-v1/AOD'
config.Data.lumiMask = '/eos/user/c/cmsdqm/www/CAF/certification/Collisions22/Collisions2022HISpecial/Cert_Collisions2022HISpecial_362293_362323_Golden.json'
config.Data.outputDatasetTag = 'PbPb_AllCent_Raw23_MB_JSON_newEventSelections_GeneralTrack_vnpT_Feb22'
'''
try:
    crabCommand('submit', config = config)
except HTTPException as hte:
    print "Failed submitting task: %s" % (hte.headers)
except ClientException as cle:
    print "Failed submitting task: %s" % (cle)


try:
    crabCommand('submit', config = config)
except HTTPException as hte:
    print "Failed submitting task: %s" % (hte.headers)
except ClientException as cle:
    print "Failed submitting task: %s" % (cle)


##RAW1
config.General.requestName = 'PbPb_AllCent_RAW1_MB_JSON_GeneralTrack_vnpT_Jan30'
config.JobType.psetName = '../cfg/chargedepptcorr_MC_central_cfg_Run3_AOD.py'
config.Data.inputDataset = '/HITestRaw1/HIRun2022A-PromptReco-v1/AOD'
config.Data.lumiMask = '/eos/user/c/cmsdqm/www/CAF/certification/Collisions22/Collisions2022HISpecial/Cert_Collisions2022HISpecial_362293_362323_Golden.json'
config.Data.outputDatasetTag = 'PbPb_AllCent_RAW1_MB_JSON_GeneralTrack_vnpT_Jan30'

try:
    crabCommand('submit', config = config)
except HTTPException as hte:
    print "Failed submitting task: %s" % (hte.headers)
except ClientException as cle:
    print "Failed submitting task: %s" % (cle)


##RAW2                                                                                                                                                                                                                                      
config.General.requestName = 'PbPb_AllCent_RAW2_MB_JSON_GeneralTrack_vnpT_Jan30'
config.JobType.psetName = '../cfg/chargedepptcorr_MC_central_cfg_Run3_AOD.py'
config.Data.inputDataset = '/HITestRaw2/HIRun2022A-PromptReco-v1/AOD'
config.Data.lumiMask = '/eos/user/c/cmsdqm/www/CAF/certification/Collisions22/Collisions2022HISpecial/Cert_Collisions2022HISpecial_362293_362323_Golden.json'
config.Data.outputDatasetTag = 'PbPb_AllCent_RAW2_MB_JSON_GeneralTrack_vnpT_Jan30'

try:
    crabCommand('submit', config = config)
except HTTPException as hte:
    print "Failed submitting task: %s" % (hte.headers)
except ClientException as cle:
    print "Failed submitting task: %s" % (cle)

##RAW3                                                                                                                                                                                              
config.General.requestName = 'PbPb_AllCent_RAW3_MB_JSON_GeneralTrack_vnpT_Jan30'
config.JobType.psetName = '../cfg/chargedepptcorr_MC_central_cfg_Run3_AOD.py'
config.Data.inputDataset = '/HITestRaw3/HIRun2022A-PromptReco-v1/AOD'
config.Data.lumiMask = '/eos/user/c/cmsdqm/www/CAF/certification/Collisions22/Collisions2022HISpecial/Cert_Collisions2022HISpecial_362293_362323_Golden.json'
config.Data.outputDatasetTag = 'PbPb_AllCent_RAW3_MB_JSON_GeneralTrack_vnpT_Jan30'


try:
    crabCommand('submit', config = config)
except HTTPException as hte:
    print "Failed submitting task: %s" % (hte.headers)
except ClientException as cle:
    print "Failed submitting task: %s" % (cle)


##RAW4                                                                                                                                                                                           
config.General.requestName = 'PbPb_AllCent_RAW4_MB_JSON_GeneralTrack_vnpT_Jan30'
config.JobType.psetName = '../cfg/chargedepptcorr_MC_central_cfg_Run3_AOD.py'
config.Data.inputDataset = '/HITestRaw4/HIRun2022A-PromptReco-v1/AOD'
config.Data.lumiMask = '/eos/user/c/cmsdqm/www/CAF/certification/Collisions22/Collisions2022HISpecial/Cert_Collisions2022HISpecial_362293_362323_Golden.json'
config.Data.outputDatasetTag = 'PbPb_AllCent_RAW4_MB_JSON_GeneralTrack_vnpT_Jan30'


try:
    crabCommand('submit', config = config)
except HTTPException as hte:
    print "Failed submitting task: %s" % (hte.headers)
except ClientException as cle:
    print "Failed submitting task: %s" % (cle)

##RAW5                                                                                                                                                                                                                                      
config.General.requestName = 'PbPb_AllCent_RAW5_MB_JSON_GeneralTrack_vnpT_Jan30'
config.JobType.psetName = '../cfg/chargedepptcorr_MC_central_cfg_Run3_AOD.py'
config.Data.inputDataset = '/HITestRaw5/HIRun2022A-PromptReco-v1/AOD'
config.Data.lumiMask = '/eos/user/c/cmsdqm/www/CAF/certification/Collisions22/Collisions2022HISpecial/Cert_Collisions2022HISpecial_362293_362323_Golden.json'
config.Data.outputDatasetTag = 'PbPb_AllCent_RAW5_MB_JSON_GeneralTrack_vnpT_Jan30'


try:
    crabCommand('submit', config = config)
except HTTPException as hte:
    print "Failed submitting task: %s" % (hte.headers)
except ClientException as cle:
    print "Failed submitting task: %s" % (cle)

##RAW6                                                                                                                                                                                                                                      
config.General.requestName = 'PbPb_AllCent_RAW6_MB_JSON_GeneralTrack_vnpT_Jan30'
config.JobType.psetName = '../cfg/chargedepptcorr_MC_central_cfg_Run3_AOD.py'
config.Data.inputDataset = '/HITestRaw6/HIRun2022A-PromptReco-v1/AOD'
config.Data.lumiMask = '/eos/user/c/cmsdqm/www/CAF/certification/Collisions22/Collisions2022HISpecial/Cert_Collisions2022HISpecial_362293_362323_Golden.json'
config.Data.outputDatasetTag = 'PbPb_AllCent_RAW6_MB_JSON_GeneralTrack_vnpT_Jan30'

try:
    crabCommand('submit', config = config)
except HTTPException as hte:
    print "Failed submitting task: %s" % (hte.headers)
except ClientException as cle:
    print "Failed submitting task: %s" % (cle)

##RAW7                                                                                                                                                                                                                                      
config.General.requestName = 'PbPb_AllCent_RAW7_MB_JSON_GeneralTrack_vnpT_Jan30'
config.JobType.psetName = '../cfg/chargedepptcorr_MC_central_cfg_Run3_AOD.py'
config.Data.inputDataset = '/HITestRaw7/HIRun2022A-PromptReco-v1/AOD'
config.Data.lumiMask = '/eos/user/c/cmsdqm/www/CAF/certification/Collisions22/Collisions2022HISpecial/Cert_Collisions2022HISpecial_362293_362323_Golden.json'
config.Data.outputDatasetTag = 'PbPb_AllCent_RAW7_MB_JSON_GeneralTrack_vnpT_Jan30'

try:
    crabCommand('submit', config = config)
except HTTPException as hte:
    print "Failed submitting task: %s" % (hte.headers)
except ClientException as cle:
    print "Failed submitting task: %s" % (cle)

##RAW8                                                                                                                                                                                                                                      
config.General.requestName = 'PbPb_AllCent_RAW8_MB_JSON_GeneralTrack_vnpT_Jan30'
config.JobType.psetName = '../cfg/chargedepptcorr_MC_central_cfg_Run3_AOD.py'
config.Data.inputDataset = '/HITestRaw8/HIRun2022A-PromptReco-v1/AOD'
config.Data.lumiMask = '/eos/user/c/cmsdqm/www/CAF/certification/Collisions22/Collisions2022HISpecial/Cert_Collisions2022HISpecial_362293_362323_Golden.json'
config.Data.outputDatasetTag = 'PbPb_AllCent_RAW8_MB_JSON_GeneralTrack_vnpT_Jan30'

try:
    crabCommand('submit', config = config)
except HTTPException as hte:
    print "Failed submitting task: %s" % (hte.headers)
except ClientException as cle:
    print "Failed submitting task: %s" % (cle)

##RAW9                                                                                                                                                                                                                                      
config.General.requestName = 'PbPb_AllCent_RAW9_MB_JSON_GeneralTrack_vnpT_Jan30'
config.JobType.psetName = '../cfg/chargedepptcorr_MC_central_cfg_Run3_AOD.py'
config.Data.inputDataset = '/HITestRaw9/HIRun2022A-PromptReco-v1/AOD'
config.Data.lumiMask = '/eos/user/c/cmsdqm/www/CAF/certification/Collisions22/Collisions2022HISpecial/Cert_Collisions2022HISpecial_362293_362323_Golden.json'
config.Data.outputDatasetTag = 'PbPb_AllCent_RAW9_MB_JSON_GeneralTrack_vnpT_Jan30'

try:
    crabCommand('submit', config = config)
except HTTPException as hte:
    print "Failed submitting task: %s" % (hte.headers)
except ClientException as cle:
    print "Failed submitting task: %s" % (cle)

##RAW10                                                                                                                                                                                                                                      
config.General.requestName = 'PbPb_AllCent_RAW10_MB_JSON_GeneralTrack_vnpT_Jan30'
config.JobType.psetName = '../cfg/chargedepptcorr_MC_central_cfg_Run3_AOD.py'
config.Data.inputDataset = '/HITestRaw10/HIRun2022A-PromptReco-v1/AOD'
config.Data.lumiMask = '/eos/user/c/cmsdqm/www/CAF/certification/Collisions22/Collisions2022HISpecial/Cert_Collisions2022HISpecial_362293_362323_Golden.json'
config.Data.outputDatasetTag = 'PbPb_AllCent_RAW10_MB_JSON_GeneralTrack_vnpT_Jan30'

try:
    crabCommand('submit', config = config)
except HTTPException as hte:
    print "Failed submitting task: %s" % (hte.headers)
except ClientException as cle:
    print "Failed submitting task: %s" % (cle)
'''
