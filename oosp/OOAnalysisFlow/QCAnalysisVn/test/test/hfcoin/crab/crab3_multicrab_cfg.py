from CRABClient.UserUtilities import config
config = config()

config.General.transferOutputs = True
config.General.transferLogs = False
config.JobType.allowUndistributedCMSSW = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'Config_analyzer_MiniAOD_cfg.py'
config.Data.inputDataset = '/IonPhysics0/OORun2025-PromptReco-v1/MINIAOD'
config.Data.inputDBS = 'global'
config.Data.lumiMask = 'pre_oo_goodlumis.json'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 6
config.Data.outLFNDirBase = '/store/user/tuos/OO/data/OOIP0_v2QC_July10'
config.Data.publication = False
config.Data.outputDatasetTag = 'OOIP0_v2QC_July10'

#config.Site.whitelist = ['T2_US_Vanderbilt']
config.Site.storageSite = 'T2_US_Vanderbilt'

if __name__ == '__main__':
   from CRABAPI.RawCommand import crabCommand
   from CRABClient.ClientExceptions import ClientException
   #from httplib import HTTPException
   from http.client import HTTPException

   config.General.workArea = 'OOIP0_v2QC_July10'

   def submit(config):
      try:
           crabCommand('submit', config = config)
      except HTTPException as hte:
          print ("Failed submitting task: %s" % (hte.headers))
      except ClientException as cle:
          print ("Failed submitting task: %s" % (cle))
   
   for num in range(0,10):

       print ("Submitting Data Set %d " % (num+1))

       if num == 0:
           RequestName = 'OOIP0_v2QC_July10'
           DataSetName = '/IonPhysics0/OORun2025-PromptReco-v1/MINIAOD'
           LumiMasks = 'pre_oo_goodlumis.json'
           OutDirBase = '/store/user/tuos/OO/pubvalidation/OOIP0_v2QC_July10'
       if num == 1:
           RequestName = 'OOIP1_v2QC_July10'
           DataSetName = '/IonPhysics1/OORun2025-PromptReco-v1/MINIAOD'
           LumiMasks = 'pre_oo_goodlumis.json'
           OutDirBase = '/store/user/tuos/OO/pubvalidation/OOIP1_v2QC_July10'
       if num == 2:
           RequestName = 'OOIP2_v2QC_July10'
           DataSetName = '/IonPhysics2/OORun2025-PromptReco-v1/MINIAOD'
           LumiMasks = 'pre_oo_goodlumis.json'
           OutDirBase = '/store/user/tuos/OO/pubvalidation/OOIP2_v2QC_July10'
       if num == 3:
           RequestName = 'OOIP3_v2QC_July10'
           DataSetName = '/IonPhysics3/OORun2025-PromptReco-v1/MINIAOD'
           LumiMasks = 'pre_oo_goodlumis.json'
           OutDirBase = '/store/user/tuos/OO/pubvalidation/OOIP3_v2QC_July10'
       if num == 4:
           RequestName = 'OOIP4_v2QC_July10'
           DataSetName = '/IonPhysics4/OORun2025-PromptReco-v1/MINIAOD'
           LumiMasks = 'pre_oo_goodlumis.json'
           OutDirBase = '/store/user/tuos/OO/pubvalidation/OOIP4_v2QC_July10'
       if num == 5:
           RequestName = 'OOIP5_v2QC_July10'
           DataSetName = '/IonPhysics5/OORun2025-PromptReco-v1/MINIAOD'
           LumiMasks = 'pre_oo_goodlumis.json'
           OutDirBase = '/store/user/tuos/OO/pubvalidation/OOIP5_v2QC_July10'
       if num == 6:
           RequestName = 'OOIP6_v2QC_July10'
           DataSetName = '/IonPhysics6/OORun2025-PromptReco-v1/MINIAOD'
           LumiMasks = 'pre_oo_goodlumis.json'
           OutDirBase = '/store/user/tuos/OO/pubvalidation/OOIP6_v2QC_July10'
       if num == 7:
           RequestName = 'OOIP7_v2QC_July10'
           DataSetName = '/IonPhysics7/OORun2025-PromptReco-v1/MINIAOD'
           LumiMasks = 'pre_oo_goodlumis.json'
           OutDirBase = '/store/user/tuos/OO/pubvalidation/OOIP7_v2QC_July10'
       if num == 8:
           RequestName = 'OOIP8_v2QC_July10'
           DataSetName = '/IonPhysics8/OORun2025-PromptReco-v1/MINIAOD'
           LumiMasks = 'pre_oo_goodlumis.json'
           OutDirBase = '/store/user/tuos/OO/pubvalidation/OOIP8_v2QC_July10'
       if num == 9:
           RequestName = 'OOIP9_v2QC_July10'
           DataSetName = '/IonPhysics9/OORun2025-PromptReco-v1/MINIAOD'
           LumiMasks = 'pre_oo_goodlumis.json'
           OutDirBase = '/store/user/tuos/OO/pubvalidation/OOIP9_v2QC_July10'

           
       config.General.requestName = RequestName
       config.Data.inputDataset = DataSetName
       config.Data.lumiMask = LumiMasks
       config.Data.outLFNDirBase = OutDirBase
       submit(config)

# python crab3_multicrab_cfg.py to execute 
# ./multicrab -c status -w crab_projects/ to check status 
