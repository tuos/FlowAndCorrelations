from CRABClient.UserUtilities import config
config = config()

config.General.transferOutputs = True
config.General.transferLogs = False
config.JobType.allowUndistributedCMSSW = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'Config_analyzer_MiniAOD_cfg.py'
config.Data.inputDataset = '/IonPhysics0/OORun2025-PromptReco-v1/MINIAOD'
config.Data.inputDBS = 'global'
config.Data.lumiMask = 'dcs_preliminary.json'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 20
config.Data.outLFNDirBase = '/store/user/tuos/OO/data/OOIP_v2QC_July31NtrkOffline'
config.Data.publication = False
config.Data.outputDatasetTag = 'OOIP_v2QC_July31NtrkOffline'

#config.Site.whitelist = ['T2_US_Vanderbilt']
config.Site.storageSite = 'T2_US_Vanderbilt'

if __name__ == '__main__':
   from CRABAPI.RawCommand import crabCommand
   from CRABClient.ClientExceptions import ClientException
   #from httplib import HTTPException
   from http.client import HTTPException

   config.General.workArea = 'OOIP_v2QC_July31NtrkOffline'

   def submit(config):
      try:
           crabCommand('submit', config = config)
      except HTTPException as hte:
          print ("Failed submitting task: %s" % (hte.headers))
      except ClientException as cle:
          print ("Failed submitting task: %s" % (cle))
   
   for num in range(0,60):

       print ("Submitting Data Set %d " % (num+1))

       RequestName = f'OOIP{num}_v2QC_July31NtrkOffline'
       DataSetName = f'/IonPhysics{num}/OORun2025-PromptReco-v1/MINIAOD'
       LumiMasks = 'dcs_preliminary.json'
       OutDirBase = f'/store/user/tuos/OO/data/{RequestName}'


       config.General.requestName = RequestName
       config.Data.inputDataset = DataSetName
       config.Data.lumiMask = LumiMasks
       config.Data.outLFNDirBase = OutDirBase
       submit(config)

# python crab3_multicrab_cfg.py to execute 
# ./multicrab -c status -w crab_projects/ to check status 
