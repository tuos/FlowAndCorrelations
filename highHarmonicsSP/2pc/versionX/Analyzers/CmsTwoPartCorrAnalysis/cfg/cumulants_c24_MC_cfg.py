import FWCore.ParameterSet.Config as cms

process = cms.Process("Cumulants")


# __________________ General _________________

# Configure the logger
process.load('Configuration.StandardSequences.Services_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.Geometry.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
#process.load('Configuration.StandardSequences.ReconstructionHeavyIons_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
#process.load("HeavyIonsAnalysis.Configuration.hfCoincFilter_cff")
#process.load("RecoVertex.PrimaryVertexProducer.OfflinePrimaryVerticesRecovery_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 10000

# Configure the number of maximum event the analyser run on in interactive mode
# -1 == ALL
process.maxEvents = cms.untracked.PSet( 
    input = cms.untracked.int32(300) 
)

process.Timing = cms.Service("Timing",
  summaryOnly = cms.untracked.bool(True),
  useJobReport = cms.untracked.bool(False)
)

# __________________ I/O files _________________

# Define the input file to run on in interactive mode
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
       # '/store/hidata/HIRun2018A/HIMinimumBias11/AOD/04Apr2019-v1/610000/54E9C8CE-C886-194D-8B7E-5A2017D83DF8.root'
        #'/store/hidata/HIRun2018A/HIMinimumBias2/AOD/04Apr2019-v1/610012/FE8E3163-9424-6843-BF99-68581F91C7A3.root'
        #'/store/hidata/HIRun2018A/HIMinimumBias3/AOD/04Apr2019-v1/00000/076997E3-898C-7F46-97F4-BAAD3D2CF8D7.root'
'/store/user/subehera/Hydjet_5360GeV_GEN_SIM/MB_Hydjet_Run3_recodebug_step4/221101_175550/0000/recodebug_hydjet_100.root'
    )
)

# Define output file name
import os
process.TFileService = cms.Service("TFileService",
     fileName = cms.string('cumulants_std.root')
)


# __________________ Detector conditions _________________
#####~~~~~~~ centrality selection~~~~~~~~####
from Configuration.AlCa.GlobalTag import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, '103X_dataRun2_Prompt_v2', '')
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:phase1_2022_realistic_hi', '') 
#process.HiForest.GlobalTagLabel = process.GlobalTag.globaltag                                                                         

print('\n\033[31m~*~ USING CENTRALITY TABLE FOR PbPb 2018 ~*~\033[0m\n')
process.GlobalTag.snapshotTime = cms.string("9999-12-31 23:59:59.000")
process.GlobalTag.toGet.extend([
    cms.PSet(record = cms.string("HeavyIonRcd"),
        tag = cms.string("CentralityTable_HFtowers200_DataPbPb_periHYDJETshape_run2v1031x02_offline"),
        connect = cms.string("frontier://FrontierProd/CMS_CONDITIONS"),
        label = cms.untracked.string("HFtowers")
        ),
    ])
#==================================================================

# __________________ Event selection _________________
#process.load('HeavyIonsAnalysis.Configuration.collisionEventSelection_cff')
#process.ana_step = cms.Path(
#process.offlinePrimaryVerticesRecovery )
#process.eventSelections = cms.Sequence(
 #   process.clusterCompatibilityFilter
  #  + process.primaryVertexFilter
   # + process.hfCoincFilter2Th4)

import HLTrigger.HLTfilters.hltHighLevel_cfi
process.hltSelect = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.hltSelect.HLTPaths = [
 "HLT_HIMinimumBias_*",
 ]
process.hltSelect.andOr = cms.bool(True)
process.hltSelect.throw = cms.bool(False)


#Primary vertex re-fitter




# __________________ Analyzer _________________

# Load you analyzer with initial configuration
process.load("Analyzers.Cumulants.cumulants_cff")
process.anaV2 = process.stdAnalysis.clone()

process.p = cms.Path(
                   #  process.hltSelect *             # Requier HF coincidence with 3 GeV  
                   #  process.eventSelections *       # Clean up on vertices
                   #  process.centralityBin * 
                     process.anaV2)          # Run the analyzer


#from HLTrigger.Configuration.CustomConfigs import MassReplaceInputTag
#process = MassReplaceInputTag(process,"offlinePrimaryVertices","offlinePrimaryVerticesRecovery")
#process.offlinePrimaryVerticesRecovery.oldVertexLabel = "offlinePrimaryVertices"

