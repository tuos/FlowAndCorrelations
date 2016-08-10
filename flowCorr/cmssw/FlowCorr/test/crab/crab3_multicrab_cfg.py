from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.transferOutputs = True
config.General.transferLogs = True
config.JobType.allowUndistributedCMSSW = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'ConfFile_cfg.py'
config.Data.inputDataset = '/HIMinimumBias2/qwang-crab_HIMB2_PixelTracking_v3-f359806bdfa543922b20b1cc8503759a/USER'
config.Data.inputDBS = 'phys03'
config.Data.lumiMask = 'cert_262548_263757_PromptReco_HICollisions15_JSON_v2.txt'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 5
config.Data.outLFNDirBase = '/store/user/tuos/flowCorr/v01aug08_5tev'
config.Data.publication = False
config.Data.outputDatasetTag = 'pbpb2015_flowcorr_v01aug08_5tev'

config.Site.storageSite = 'T2_US_Vanderbilt'

if __name__ == '__main__':
   from CRABAPI.RawCommand import crabCommand
   from CRABClient.ClientExceptions import ClientException
   from httplib import HTTPException

   config.General.workArea = 'pbpb2015_flowcorr_v01aug08_5tev'

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
           RequestName = 'pbpb2015_flowcorr_v01aug08_5tev'
           DataSetName = '/HIMinimumBias2/qwang-crab_HIMB2_PixelTracking_v3-f359806bdfa543922b20b1cc8503759a/USER'
           LumiMasks = 'cert_262548_263757_PromptReco_HICollisions15_JSON_v2.txt'
           OutDirBase = '/store/user/tuos/flowCorr/v01aug08_5tev'
           
       config.General.requestName = RequestName
       config.Data.inputDataset = DataSetName
       config.Data.lumiMask = LumiMasks
       config.Data.outLFNDirBase = OutDirBase
       submit(config)

# python crab3_multicrab_cfg.py to execute 
# ./multicrab -c status -w crab_projects/ to check status 
