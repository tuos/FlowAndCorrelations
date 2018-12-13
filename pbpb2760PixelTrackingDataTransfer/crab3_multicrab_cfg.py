from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.transferOutputs = True
config.General.transferLogs = False
config.JobType.allowUndistributedCMSSW = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'ConfFile_cfg.py'
config.Data.inputDataset = '/HIMinBiasUPC/davidlw-Skim_rereco_MB_pixeltracks_final_v2-9c1b4b9b6b9ff3e493a474ba7d01bc76/USER'
config.Data.inputDBS = 'phys03'
config.Data.lumiMask = 'cert_181530_183126_PromptReco_HICollisions11_JSON.txt'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
config.Data.outLFNDirBase = '/store/user/tuos/PbPb2760/pixelTrackingMB/CopyFromWei'
config.Data.publication = True
config.Data.outputDatasetTag = 'Skim_rereco_2760PbPbMB_pixeltracksCopyFromWei_v3'

config.Site.storageSite = 'T2_US_Vanderbilt'

if __name__ == '__main__':
   from CRABAPI.RawCommand import crabCommand
   from CRABClient.ClientExceptions import ClientException
   from httplib import HTTPException

   config.General.workArea = 'Skim_rereco_2760PbPbMB_pixeltracksCopyFromWei_v3'

   def submit(config):
      try:
           crabCommand('submit', config = config)
      except HTTPException as hte:
           print "Failed submitting task: %s" % (hte.headers)
      except ClientException as cle:
          print "Failed submitting task: %s" % (cle)
   
   for num in range(0,1):

       print "Submitting Data Set %d " % (num+1)

       if num == 0:
           RequestName = 'Skim_rereco_2760PbPbMB_pixeltracksCopyFromWei_v3'
           DataSetName = '/HIMinBiasUPC/davidlw-Skim_rereco_MB_pixeltracks_final_v2-9c1b4b9b6b9ff3e493a474ba7d01bc76/USER'
           LumiMasks = 'cert_181530_183126_PromptReco_HICollisions11_JSON.txt'
           OutDirBase = '/store/user/tuos/PbPb2760/pixelTrackingMB/CopyFromWei'
           
       config.General.requestName = RequestName
       config.Data.inputDataset = DataSetName
       config.Data.lumiMask = LumiMasks
       config.Data.outLFNDirBase = OutDirBase
       submit(config)

# python crab3_multicrab_cfg.py to execute 
# ./multicrab -c status -w crab_projects/ to check status
