from CRABClient.UserUtilities import config
config = config()

config.General.transferOutputs = True
config.General.transferLogs = False
config.JobType.allowUndistributedCMSSW = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'Config_PbPb_MiniAOD.py'
config.Data.inputDataset = '/HIMinimumBias0/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
config.Data.inputDBS = 'global'
config.Data.lumiMask = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 10
config.Data.outLFNDirBase = '/store/user/tuos/qm2023/anaMay23/PbPbMB0_2pc_May23'
config.Data.publication = False
config.Data.outputDatasetTag = 'PbPbMB0_2pc_May23'

#config.Site.whitelist = ['T2_US_Vanderbilt']
config.Site.storageSite = 'T2_US_Vanderbilt'

if __name__ == '__main__':
   from CRABAPI.RawCommand import crabCommand
   from CRABClient.ClientExceptions import ClientException
   from httplib import HTTPException

   config.General.workArea = 'PbPbMB_2pc_May23'

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
           RequestName = 'PbPbMB0_2pc_May23'
           DataSetName = '/HIMinimumBias0/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/qm2023/anaMay23/PbPbMB0_2pc_May23'
       if num == 1:
           RequestName = 'PbPbMB1_2pc_May23'
           DataSetName = '/HIMinimumBias1/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/qm2023/anaMay23/PbPbMB1_2pc_May23'
       if num == 2:
           RequestName = 'PbPbMB2_2pc_May23'
           DataSetName = '/HIMinimumBias2/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/qm2023/anaMay23/PbPbMB2_2pc_May23'
       if num == 3:
           RequestName = 'PbPbMB3_2pc_May23'
           DataSetName = '/HIMinimumBias3/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/qm2023/anaMay23/PbPbMB3_2pc_May23'
       if num == 4:
           RequestName = 'PbPbMB4_2pc_May23'
           DataSetName = '/HIMinimumBias4/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/qm2023/anaMay23/PbPbMB4_2pc_May23'
       if num == 5:
           RequestName = 'PbPbMB5_2pc_May23'
           DataSetName = '/HIMinimumBias5/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/qm2023/anaMay23/PbPbMB5_2pc_May23'
       if num == 6:
           RequestName = 'PbPbMB6_2pc_May23'
           DataSetName = '/HIMinimumBias6/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/qm2023/anaMay23/PbPbMB6_2pc_May23'
       if num == 7:
           RequestName = 'PbPbMB7_2pc_May23'
           DataSetName = '/HIMinimumBias7/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/qm2023/anaMay23/PbPbMB7_2pc_May23'
       if num == 8:
           RequestName = 'PbPbMB8_2pc_May23'
           DataSetName = '/HIMinimumBias8/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/qm2023/anaMay23/PbPbMB8_2pc_May23'
       if num == 9:
           RequestName = 'PbPbMB9_2pc_May23'
           DataSetName = '/HIMinimumBias9/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/qm2023/anaMay23/PbPbMB9_2pc_May23'
       if num == 10:
           RequestName = 'PbPbMB10_2pc_May23'
           DataSetName = '/HIMinimumBias10/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/qm2023/anaMay23/PbPbMB10_2pc_May23'
       if num == 11:
           RequestName = 'PbPbMB11_2pc_May23'
           DataSetName = '/HIMinimumBias11/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/qm2023/anaMay23/PbPbMB11_2pc_May23'
       if num == 12:
           RequestName = 'PbPbMB12_2pc_May23'
           DataSetName = '/HIMinimumBias12/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/qm2023/anaMay23/PbPbMB12_2pc_May23'
       if num == 13:
           RequestName = 'PbPbMB13_2pc_May23'
           DataSetName = '/HIMinimumBias13/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/qm2023/anaMay23/PbPbMB13_2pc_May23'
       if num == 14:
           RequestName = 'PbPbMB14_2pc_May23'
           DataSetName = '/HIMinimumBias14/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/qm2023/anaMay23/PbPbMB14_2pc_May23'
       if num == 15:
           RequestName = 'PbPbMB15_2pc_May23'
           DataSetName = '/HIMinimumBias15/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/qm2023/anaMay23/PbPbMB15_2pc_May23'
       if num == 16:
           RequestName = 'PbPbMB16_2pc_May23'
           DataSetName = '/HIMinimumBias16/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/qm2023/anaMay23/PbPbMB16_2pc_May23'
       if num == 17:
           RequestName = 'PbPbMB17_2pc_May23'
           DataSetName = '/HIMinimumBias17/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/qm2023/anaMay23/PbPbMB17_2pc_May23'
       if num == 18:
           RequestName = 'PbPbMB18_2pc_May23'
           DataSetName = '/HIMinimumBias18/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/qm2023/anaMay23/PbPbMB18_2pc_May23'
       if num == 19:
           RequestName = 'PbPbMB19_2pc_May23'
           DataSetName = '/HIMinimumBias19/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/qm2023/anaMay23/PbPbMB19_2pc_May23'
           
       config.General.requestName = RequestName
       config.Data.inputDataset = DataSetName
       config.Data.lumiMask = LumiMasks
       config.Data.outLFNDirBase = OutDirBase
       submit(config)

# python crab3_multicrab_cfg.py to execute 
# ./multicrab -c status -w crab_projects/ to check status 
