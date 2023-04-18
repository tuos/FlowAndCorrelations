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
config.Data.outLFNDirBase = '/store/user/tuos/qm2023/anaApr17/PbPbMB0_vnSP_Apr17'
config.Data.publication = False
config.Data.outputDatasetTag = 'PbPbMB0_vnSP_Apr17'

#config.Site.whitelist = ['T2_US_Vanderbilt']
config.Site.storageSite = 'T2_US_Vanderbilt'

if __name__ == '__main__':
   from CRABAPI.RawCommand import crabCommand
   from CRABClient.ClientExceptions import ClientException
   from httplib import HTTPException

   config.General.workArea = 'PbPbMB_vnSP_Apr17'

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
           RequestName = 'PbPbMB0_vnSP_Apr17'
           DataSetName = '/HIMinimumBias0/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/qm2023/anaApr17/PbPbMB0_vnSP_Apr17'
       if num == 1:
           RequestName = 'PbPbMB1_vnSP_Apr17'
           DataSetName = '/HIMinimumBias1/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/qm2023/anaApr17/PbPbMB1_vnSP_Apr17'
       if num == 2:
           RequestName = 'PbPbMB2_vnSP_Apr17'
           DataSetName = '/HIMinimumBias2/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/qm2023/anaApr17/PbPbMB2_vnSP_Apr17'
       if num == 3:
           RequestName = 'PbPbMB3_vnSP_Apr17'
           DataSetName = '/HIMinimumBias3/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/qm2023/anaApr17/PbPbMB3_vnSP_Apr17'
       if num == 4:
           RequestName = 'PbPbMB4_vnSP_Apr17'
           DataSetName = '/HIMinimumBias4/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/qm2023/anaApr17/PbPbMB4_vnSP_Apr17'
       if num == 5:
           RequestName = 'PbPbMB5_vnSP_Apr17'
           DataSetName = '/HIMinimumBias5/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/qm2023/anaApr17/PbPbMB5_vnSP_Apr17'
       if num == 6:
           RequestName = 'PbPbMB6_vnSP_Apr17'
           DataSetName = '/HIMinimumBias6/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/qm2023/anaApr17/PbPbMB6_vnSP_Apr17'
       if num == 7:
           RequestName = 'PbPbMB7_vnSP_Apr17'
           DataSetName = '/HIMinimumBias7/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/qm2023/anaApr17/PbPbMB7_vnSP_Apr17'
       if num == 8:
           RequestName = 'PbPbMB8_vnSP_Apr17'
           DataSetName = '/HIMinimumBias8/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/qm2023/anaApr17/PbPbMB8_vnSP_Apr17'
       if num == 9:
           RequestName = 'PbPbMB9_vnSP_Apr17'
           DataSetName = '/HIMinimumBias9/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/qm2023/anaApr17/PbPbMB9_vnSP_Apr17'
       if num == 10:
           RequestName = 'PbPbMB10_vnSP_Apr17'
           DataSetName = '/HIMinimumBias10/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/qm2023/anaApr17/PbPbMB10_vnSP_Apr17'
       if num == 11:
           RequestName = 'PbPbMB11_vnSP_Apr17'
           DataSetName = '/HIMinimumBias11/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/qm2023/anaApr17/PbPbMB11_vnSP_Apr17'
       if num == 12:
           RequestName = 'PbPbMB12_vnSP_Apr17'
           DataSetName = '/HIMinimumBias12/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/qm2023/anaApr17/PbPbMB12_vnSP_Apr17'
       if num == 13:
           RequestName = 'PbPbMB13_vnSP_Apr17'
           DataSetName = '/HIMinimumBias13/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/qm2023/anaApr17/PbPbMB13_vnSP_Apr17'
       if num == 14:
           RequestName = 'PbPbMB14_vnSP_Apr17'
           DataSetName = '/HIMinimumBias14/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/qm2023/anaApr17/PbPbMB14_vnSP_Apr17'
       if num == 15:
           RequestName = 'PbPbMB15_vnSP_Apr17'
           DataSetName = '/HIMinimumBias15/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/qm2023/anaApr17/PbPbMB15_vnSP_Apr17'
       if num == 16:
           RequestName = 'PbPbMB16_vnSP_Apr17'
           DataSetName = '/HIMinimumBias16/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/qm2023/anaApr17/PbPbMB16_vnSP_Apr17'
       if num == 17:
           RequestName = 'PbPbMB17_vnSP_Apr17'
           DataSetName = '/HIMinimumBias17/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/qm2023/anaApr17/PbPbMB17_vnSP_Apr17'
       if num == 18:
           RequestName = 'PbPbMB18_vnSP_Apr17'
           DataSetName = '/HIMinimumBias18/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/qm2023/anaApr17/PbPbMB18_vnSP_Apr17'
       if num == 19:
           RequestName = 'PbPbMB19_vnSP_Apr17'
           DataSetName = '/HIMinimumBias19/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/qm2023/anaApr17/PbPbMB19_vnSP_Apr17'
           
       config.General.requestName = RequestName
       config.Data.inputDataset = DataSetName
       config.Data.lumiMask = LumiMasks
       config.Data.outLFNDirBase = OutDirBase
       submit(config)

# python crab3_multicrab_cfg.py to execute 
# ./multicrab -c status -w crab_projects/ to check status 
