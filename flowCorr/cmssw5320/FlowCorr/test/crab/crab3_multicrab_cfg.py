from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.transferOutputs = True
config.General.transferLogs = True
config.JobType.allowUndistributedCMSSW = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'ConfFile_cfg.py'
config.Data.inputDataset = '/HIMinBiasUPC/davidlw-Skim_rereco_MB_pixeltracks_final_v2-9c1b4b9b6b9ff3e493a474ba7d01bc76/USER'
config.Data.inputDBS = 'phys03'
config.Data.lumiMask = 'cert_181530_183126_PromptReco_HICollisions11_JSON.txt'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 2
config.Data.outLFNDirBase = '/store/user/tuos/mixedHarmonics/v08jan10_v1ReCentPt'
config.Data.publication = False
config.Data.outputDatasetTag = 'pbpb2760_flowcorr_v08jan10_v1ReCentPt'

config.Site.storageSite = 'T2_US_Vanderbilt'

if __name__ == '__main__':
   from CRABAPI.RawCommand import crabCommand
   from CRABClient.ClientExceptions import ClientException
   from httplib import HTTPException

   config.General.workArea = 'pbpb2760_flowcorr_v08jan10_v1ReCentPt'

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
           RequestName = 'pbpb2760_flowcorr_v08jan10_v1ReCentPt'
           DataSetName = '/HIMinBiasUPC/davidlw-Skim_rereco_MB_pixeltracks_final_v2-9c1b4b9b6b9ff3e493a474ba7d01bc76/USER'
           LumiMasks = 'cert_181530_183126_PromptReco_HICollisions11_JSON.txt'
           OutDirBase = '/store/user/tuos/mixedHarmonics/v08jan10_v1ReCentPt'
           
       config.General.requestName = RequestName
       config.Data.inputDataset = DataSetName
       config.Data.lumiMask = LumiMasks
       config.Data.outLFNDirBase = OutDirBase
       submit(config)

# python crab3_multicrab_cfg.py to execute 
# ./multicrab -c status -w crab_projects/ to check status 
