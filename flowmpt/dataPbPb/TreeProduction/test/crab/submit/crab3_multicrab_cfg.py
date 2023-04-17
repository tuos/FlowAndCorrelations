from CRABClient.UserUtilities import config
config = config()

config.General.transferOutputs = True
config.General.transferLogs = False
config.JobType.allowUndistributedCMSSW = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'Config_pbpbMB_MiniAOD_cfg.py'
config.Data.inputDataset = '/HIMinimumBias0/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
config.Data.inputDBS = 'global'
config.Data.lumiMask = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 10
config.Data.outLFNDirBase = '/store/user/tuos/i_ana2021/trees/PbPbMB/PbPbMB0_v2mptTree_Oct22'
config.Data.publication = False
config.Data.outputDatasetTag = 'PbPbMB0_v2mptTree_Oct22'

#config.Site.whitelist = ['T2_US_Vanderbilt']
config.Site.storageSite = 'T2_US_Vanderbilt'

if __name__ == '__main__':
   from CRABAPI.RawCommand import crabCommand
   from CRABClient.ClientExceptions import ClientException
   from httplib import HTTPException

   config.General.workArea = 'PbPbMB_v2mptTree_Oct22'

   def submit(config):
      try:
           crabCommand('submit', config = config)
      except HTTPException as hte:
           print "Failed submitting task: %s" % (hte.headers)
      except ClientException as cle:
          print "Failed submitting task: %s" % (cle)
   
   for num in range(0,20):

       print "Submitting Data Set %d " % (num+1)

       if num == 0:
           RequestName = 'PbPbMB0_v2mptTree_Oct22'
           DataSetName = '/HIMinimumBias0/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/i_ana2021/trees/PbPbMB/PbPbMB0_v2mptTree_Oct22'
       if num == 1:
           RequestName = 'PbPbMB1_v2mptTree_Oct22'
           DataSetName = '/HIMinimumBias1/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/i_ana2021/trees/PbPbMB/PbPbMB1_v2mptTree_Oct22'
       if num == 2:
           RequestName = 'PbPbMB2_v2mptTree_Oct22'
           DataSetName = '/HIMinimumBias2/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/i_ana2021/trees/PbPbMB/PbPbMB2_v2mptTree_Oct22'
       if num == 3:
           RequestName = 'PbPbMB3_v2mptTree_Oct22'
           DataSetName = '/HIMinimumBias3/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/i_ana2021/trees/PbPbMB/PbPbMB3_v2mptTree_Oct22'
       if num == 4:
           RequestName = 'PbPbMB4_v2mptTree_Oct22'
           DataSetName = '/HIMinimumBias4/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/i_ana2021/trees/PbPbMB/PbPbMB4_v2mptTree_Oct22'
       if num == 5:
           RequestName = 'PbPbMB5_v2mptTree_Oct22'
           DataSetName = '/HIMinimumBias5/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/i_ana2021/trees/PbPbMB/PbPbMB5_v2mptTree_Oct22'
       if num == 6:
           RequestName = 'PbPbMB6_v2mptTree_Oct22'
           DataSetName = '/HIMinimumBias6/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/i_ana2021/trees/PbPbMB/PbPbMB6_v2mptTree_Oct22'
       if num == 7:
           RequestName = 'PbPbMB7_v2mptTree_Oct22'
           DataSetName = '/HIMinimumBias7/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/i_ana2021/trees/PbPbMB/PbPbMB7_v2mptTree_Oct22'
       if num == 8:
           RequestName = 'PbPbMB8_v2mptTree_Oct22'
           DataSetName = '/HIMinimumBias8/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/i_ana2021/trees/PbPbMB/PbPbMB8_v2mptTree_Oct22'
       if num == 9:
           RequestName = 'PbPbMB9_v2mptTree_Oct22'
           DataSetName = '/HIMinimumBias9/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/i_ana2021/trees/PbPbMB/PbPbMB9_v2mptTree_Oct22'
       if num == 10:
           RequestName = 'PbPbMB10_v2mptTree_Oct22'
           DataSetName = '/HIMinimumBias10/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/i_ana2021/trees/PbPbMB/PbPbMB10_v2mptTree_Oct22'
       if num == 11:
           RequestName = 'PbPbMB11_v2mptTree_Oct22'
           DataSetName = '/HIMinimumBias11/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/i_ana2021/trees/PbPbMB/PbPbMB11_v2mptTree_Oct22'
       if num == 12:
           RequestName = 'PbPbMB12_v2mptTree_Oct22'
           DataSetName = '/HIMinimumBias12/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/i_ana2021/trees/PbPbMB/PbPbMB12_v2mptTree_Oct22'
       if num == 13:
           RequestName = 'PbPbMB13_v2mptTree_Oct22'
           DataSetName = '/HIMinimumBias13/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/i_ana2021/trees/PbPbMB/PbPbMB13_v2mptTree_Oct22'
       if num == 14:
           RequestName = 'PbPbMB14_v2mptTree_Oct22'
           DataSetName = '/HIMinimumBias14/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/i_ana2021/trees/PbPbMB/PbPbMB14_v2mptTree_Oct22'
       if num == 15:
           RequestName = 'PbPbMB15_v2mptTree_Oct22'
           DataSetName = '/HIMinimumBias15/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/i_ana2021/trees/PbPbMB/PbPbMB15_v2mptTree_Oct22'
       if num == 16:
           RequestName = 'PbPbMB16_v2mptTree_Oct22'
           DataSetName = '/HIMinimumBias16/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/i_ana2021/trees/PbPbMB/PbPbMB16_v2mptTree_Oct22'
       if num == 17:
           RequestName = 'PbPbMB17_v2mptTree_Oct22'
           DataSetName = '/HIMinimumBias17/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/i_ana2021/trees/PbPbMB/PbPbMB17_v2mptTree_Oct22'
       if num == 18:
           RequestName = 'PbPbMB18_v2mptTree_Oct22'
           DataSetName = '/HIMinimumBias18/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/i_ana2021/trees/PbPbMB/PbPbMB18_v2mptTree_Oct22'
       if num == 19:
           RequestName = 'PbPbMB19_v2mptTree_Oct22'
           DataSetName = '/HIMinimumBias19/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/i_ana2021/trees/PbPbMB/PbPbMB19_v2mptTree_Oct22'
           
       config.General.requestName = RequestName
       config.Data.inputDataset = DataSetName
       config.Data.lumiMask = LumiMasks
       config.Data.outLFNDirBase = OutDirBase
       submit(config)

# python crab3_multicrab_cfg.py to execute 
# ./multicrab -c status -w crab_projects/ to check status 
