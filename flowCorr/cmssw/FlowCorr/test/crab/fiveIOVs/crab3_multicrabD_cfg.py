from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.transferOutputs = True
config.General.transferLogs = True
config.JobType.allowUndistributedCMSSW = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'ConfFile_cfg.py'
config.Data.inputDataset = '/HIMinimumBias2/HIRun2015-25Aug2016-v1/AOD'
config.Data.inputDBS = 'global'
config.Data.lumiMask = 'cert_263360_263379_PromptReco_HICollisions15_JSON_v2.txt'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 20
config.Data.outLFNDirBase = '/store/user/tuos/mixedHarmonics/v03Ana_5TevCentPar_sep25D'
config.Data.publication = False
config.Data.outputDatasetTag = 'pbpb2015_flowcorr_v03Ana_5TevCentPar_sep25D'

config.Site.storageSite = 'T2_US_Vanderbilt'

if __name__ == '__main__':
   from CRABAPI.RawCommand import crabCommand
   from CRABClient.ClientExceptions import ClientException
   from httplib import HTTPException

   config.General.workArea = 'pbpb2015_flowcorr_v03Ana_5TevCentPar_sep25D'

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
           RequestName = 'pbpb2015_flowcorr_v03Ana_5TevCentPar_sep25D'
           DataSetName = '/HIMinimumBias2/HIRun2015-25Aug2016-v1/AOD'
           LumiMasks = 'cert_263360_263379_PromptReco_HICollisions15_JSON_v2.txt'
           OutDirBase = '/store/user/tuos/mixedHarmonics/v03Ana_5TevCentPar_sep25D'
           
       config.General.requestName = RequestName
       config.Data.inputDataset = DataSetName
       config.Data.lumiMask = LumiMasks
       config.Data.outLFNDirBase = OutDirBase
       submit(config)

# python crab3_multicrab_cfg.py to execute 
# ./multicrab -c status -w crab_projects/ to check status 
