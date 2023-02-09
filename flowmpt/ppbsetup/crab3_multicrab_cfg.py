from CRABClient.UserUtilities import config
config = config()

config.General.transferOutputs = True
config.General.transferLogs = False
config.JobType.allowUndistributedCMSSW = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'Config_pPbMB_AOD_cfg.py'
config.Data.inputDataset = '/PAMinimumBias1/PARun2016C-PromptReco-v1/AOD'
config.Data.inputDBS = 'global'
config.Data.lumiMask = 'Cert_285479-285832_HI8TeV_PromptReco_pPb_Collisions16_JSON_NoL1T.txt'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 10
config.Data.outLFNDirBase = '/store/user/tuos/i_ana2021/trees/pPbMB/pPbMB1_v2mptTree_Nov05'
config.Data.publication = False
config.Data.outputDatasetTag = 'pPbMB1_v2mptTree_Nov05'

#config.Site.whitelist = ['T2_US_Vanderbilt']
config.Site.storageSite = 'T2_US_Vanderbilt'

if __name__ == '__main__':
   from CRABAPI.RawCommand import crabCommand
   from CRABClient.ClientExceptions import ClientException
   from httplib import HTTPException

   config.General.workArea = 'pPbMB_v2mptTree_Nov05'

   def submit(config):
      try:
           crabCommand('submit', config = config)
      except HTTPException as hte:
           print "Failed submitting task: %s" % (hte.headers)
      except ClientException as cle:
          print "Failed submitting task: %s" % (cle)
   
   for num in range(1,21):

       print "Submitting Data Set %d " % (num+0)

       if num == 1:
           RequestName = 'pPbMB1_v2mptTree_Nov05'
           DataSetName = '/PAMinimumBias1/PARun2016C-PromptReco-v1/AOD'
           LumiMasks = 'Cert_285479-285832_HI8TeV_PromptReco_pPb_Collisions16_JSON_NoL1T.txt'
           OutDirBase = '/store/user/tuos/i_ana2021/trees/pPbMB/pPbMB1_v2mptTree_Nov05'
       if num == 2:
           RequestName = 'pPbMB2_v2mptTree_Nov05'
           DataSetName = '/PAMinimumBias2/PARun2016C-PromptReco-v1/AOD'
           LumiMasks = 'Cert_285479-285832_HI8TeV_PromptReco_pPb_Collisions16_JSON_NoL1T.txt'
           OutDirBase = '/store/user/tuos/i_ana2021/trees/pPbMB/pPbMB2_v2mptTree_Nov05'
       if num == 3:
           RequestName = 'pPbMB3_v2mptTree_Nov05'
           DataSetName = '/PAMinimumBias3/PARun2016C-PromptReco-v1/AOD'
           LumiMasks = 'Cert_285479-285832_HI8TeV_PromptReco_pPb_Collisions16_JSON_NoL1T.txt'
           OutDirBase = '/store/user/tuos/i_ana2021/trees/pPbMB/pPbMB3_v2mptTree_Nov05'
       if num == 4:
           RequestName = 'pPbMB4_v2mptTree_Nov05'
           DataSetName = '/PAMinimumBias4/PARun2016C-PromptReco-v1/AOD'
           LumiMasks = 'Cert_285479-285832_HI8TeV_PromptReco_pPb_Collisions16_JSON_NoL1T.txt'
           OutDirBase = '/store/user/tuos/i_ana2021/trees/pPbMB/pPbMB4_v2mptTree_Nov05'
       if num == 5:
           RequestName = 'pPbMB5_v2mptTree_Nov05'
           DataSetName = '/PAMinimumBias5/PARun2016C-PromptReco-v1/AOD'
           LumiMasks = 'Cert_285479-285832_HI8TeV_PromptReco_pPb_Collisions16_JSON_NoL1T.txt'
           OutDirBase = '/store/user/tuos/i_ana2021/trees/pPbMB/pPbMB5_v2mptTree_Nov05'
       if num == 6:
           RequestName = 'pPbMB6_v2mptTree_Nov05'
           DataSetName = '/PAMinimumBias6/PARun2016C-PromptReco-v1/AOD'
           LumiMasks = 'Cert_285479-285832_HI8TeV_PromptReco_pPb_Collisions16_JSON_NoL1T.txt'
           OutDirBase = '/store/user/tuos/i_ana2021/trees/pPbMB/pPbMB6_v2mptTree_Nov05'
       if num == 7:
           RequestName = 'pPbMB7_v2mptTree_Nov05'
           DataSetName = '/PAMinimumBias7/PARun2016C-PromptReco-v1/AOD'
           LumiMasks = 'Cert_285479-285832_HI8TeV_PromptReco_pPb_Collisions16_JSON_NoL1T.txt'
           OutDirBase = '/store/user/tuos/i_ana2021/trees/pPbMB/pPbMB7_v2mptTree_Nov05'
       if num == 8:
           RequestName = 'pPbMB8_v2mptTree_Nov05'
           DataSetName = '/PAMinimumBias8/PARun2016C-PromptReco-v1/AOD'
           LumiMasks = 'Cert_285479-285832_HI8TeV_PromptReco_pPb_Collisions16_JSON_NoL1T.txt'
           OutDirBase = '/store/user/tuos/i_ana2021/trees/pPbMB/pPbMB8_v2mptTree_Nov05'
       if num == 9:
           RequestName = 'pPbMB9_v2mptTree_Nov05'
           DataSetName = '/PAMinimumBias9/PARun2016C-PromptReco-v1/AOD'
           LumiMasks = 'Cert_285479-285832_HI8TeV_PromptReco_pPb_Collisions16_JSON_NoL1T.txt'
           OutDirBase = '/store/user/tuos/i_ana2021/trees/pPbMB/pPbMB9_v2mptTree_Nov05'
       if num == 10:
           RequestName = 'pPbMB10_v2mptTree_Nov05'
           DataSetName = '/PAMinimumBias10/PARun2016C-PromptReco-v1/AOD'
           LumiMasks = 'Cert_285479-285832_HI8TeV_PromptReco_pPb_Collisions16_JSON_NoL1T.txt'
           OutDirBase = '/store/user/tuos/i_ana2021/trees/pPbMB/pPbMB10_v2mptTree_Nov05'
       if num == 11:
           RequestName = 'pPbMB11_v2mptTree_Nov05'
           DataSetName = '/PAMinimumBias11/PARun2016C-PromptReco-v1/AOD'
           LumiMasks = 'Cert_285479-285832_HI8TeV_PromptReco_pPb_Collisions16_JSON_NoL1T.txt'
           OutDirBase = '/store/user/tuos/i_ana2021/trees/pPbMB/pPbMB11_v2mptTree_Nov05'
       if num == 12:
           RequestName = 'pPbMB12_v2mptTree_Nov05'
           DataSetName = '/PAMinimumBias12/PARun2016C-PromptReco-v1/AOD'
           LumiMasks = 'Cert_285479-285832_HI8TeV_PromptReco_pPb_Collisions16_JSON_NoL1T.txt'
           OutDirBase = '/store/user/tuos/i_ana2021/trees/pPbMB/pPbMB12_v2mptTree_Nov05'
       if num == 13:
           RequestName = 'pPbMB13_v2mptTree_Nov05'
           DataSetName = '/PAMinimumBias13/PARun2016C-PromptReco-v1/AOD'
           LumiMasks = 'Cert_285479-285832_HI8TeV_PromptReco_pPb_Collisions16_JSON_NoL1T.txt'
           OutDirBase = '/store/user/tuos/i_ana2021/trees/pPbMB/pPbMB13_v2mptTree_Nov05'
       if num == 14:
           RequestName = 'pPbMB14_v2mptTree_Nov05'
           DataSetName = '/PAMinimumBias14/PARun2016C-PromptReco-v1/AOD'
           LumiMasks = 'Cert_285479-285832_HI8TeV_PromptReco_pPb_Collisions16_JSON_NoL1T.txt'
           OutDirBase = '/store/user/tuos/i_ana2021/trees/pPbMB/pPbMB14_v2mptTree_Nov05'
       if num == 15:
           RequestName = 'pPbMB15_v2mptTree_Nov05'
           DataSetName = '/PAMinimumBias15/PARun2016C-PromptReco-v1/AOD'
           LumiMasks = 'Cert_285479-285832_HI8TeV_PromptReco_pPb_Collisions16_JSON_NoL1T.txt'
           OutDirBase = '/store/user/tuos/i_ana2021/trees/pPbMB/pPbMB15_v2mptTree_Nov05'
       if num == 16:
           RequestName = 'pPbMB16_v2mptTree_Nov05'
           DataSetName = '/PAMinimumBias16/PARun2016C-PromptReco-v1/AOD'
           LumiMasks = 'Cert_285479-285832_HI8TeV_PromptReco_pPb_Collisions16_JSON_NoL1T.txt'
           OutDirBase = '/store/user/tuos/i_ana2021/trees/pPbMB/pPbMB16_v2mptTree_Nov05'
       if num == 17:
           RequestName = 'pPbMB17_v2mptTree_Nov05'
           DataSetName = '/PAMinimumBias17/PARun2016C-PromptReco-v1/AOD'
           LumiMasks = 'Cert_285479-285832_HI8TeV_PromptReco_pPb_Collisions16_JSON_NoL1T.txt'
           OutDirBase = '/store/user/tuos/i_ana2021/trees/pPbMB/pPbMB17_v2mptTree_Nov05'
       if num == 18:
           RequestName = 'pPbMB18_v2mptTree_Nov05'
           DataSetName = '/PAMinimumBias18/PARun2016C-PromptReco-v1/AOD'
           LumiMasks = 'Cert_285479-285832_HI8TeV_PromptReco_pPb_Collisions16_JSON_NoL1T.txt'
           OutDirBase = '/store/user/tuos/i_ana2021/trees/pPbMB/pPbMB18_v2mptTree_Nov05'
       if num == 19:
           RequestName = 'pPbMB19_v2mptTree_Nov05'
           DataSetName = '/PAMinimumBias19/PARun2016C-PromptReco-v1/AOD'
           LumiMasks = 'Cert_285479-285832_HI8TeV_PromptReco_pPb_Collisions16_JSON_NoL1T.txt'
           OutDirBase = '/store/user/tuos/i_ana2021/trees/pPbMB/pPbMB19_v2mptTree_Nov05'
       if num == 20:
           RequestName = 'pPbMB20_v2mptTree_Nov05'
           DataSetName = '/PAMinimumBias20/PARun2016C-PromptReco-v1/AOD'
           LumiMasks = 'Cert_285479-285832_HI8TeV_PromptReco_pPb_Collisions16_JSON_NoL1T.txt'
           OutDirBase = '/store/user/tuos/i_ana2021/trees/pPbMB/pPbMB20_v2mptTree_Nov05' 
          
       config.General.requestName = RequestName
       config.Data.inputDataset = DataSetName
       config.Data.lumiMask = LumiMasks
       config.Data.outLFNDirBase = OutDirBase
       submit(config)

# python crab3_multicrab_cfg.py to execute 
# ./multicrab -c status -w crab_projects/ to check status 
