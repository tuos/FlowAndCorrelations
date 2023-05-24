import FWCore.ParameterSet.Config as cms

process = cms.Process("AnaTwoPC")
process.load('Configuration.Geometry.GeometryDB_cff')
process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

# __________________ General _________________

# Configure the logger
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

# Configure the number of maximum event the analyser run on in interactive mode
# -1 == ALL
process.maxEvents = cms.untracked.PSet( 
    input = cms.untracked.int32(-1) 
#    input = cms.untracked.int32(5000) 
    )


# __________________ I/O files _________________

# Define the input file to run on in interactive mode
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        #'/store/user/subehera/Hydjet_5360GeV_GEN_SIM/MB_Hydjet_Run3_recodebug_step4/221101_175550/0000/recodebug_hydjet_100.root'
#        "/store/hidata/HIRun2022A/HITestRaw5/AOD/PromptReco-v1/000/362/294/00000/e3a81eb4-6ae1-44f8-842f-f2ed9c38c9b8.root"
        '/store/hidata/HIRun2018A/HIMinimumBias19/MINIAOD/PbPb18_MiniAODv1-v1/00000/1ec5bb45-0783-41c2-a6ca-705c71a02eaf.root'
    ),
   skipBadFiles=cms.untracked.bool(True),
   duplicateCheckMode = cms.untracked.string('noDuplicateCheck')
)

# Define output file name
import os
process.TFileService = cms.Service("TFileService",
     #fileName = cms.string(os.getenv('CMSSW_BASE') + '/src/Analyzers/ChargeDepAndPtCorr/test/chargeptdepcorr.root')
      fileName = cms.string('higherHarmonics_PbPb_2pc.root')
)

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool( True ),
)

runOnDATA = True ###IMPORTANT: please, to run in MC set to "False"
# Set the global tag
from Configuration.AlCa.GlobalTag import GlobalTag
if runOnDATA :
   process.GlobalTag = GlobalTag(process.GlobalTag, '112X_dataRun2_PromptLike_HI_v3', '') #centrality table information from this GT for DATA
else :
   process.GlobalTag = GlobalTag(process.GlobalTag, '112X_upgrade2018_realistic_HI_v9', '') #centrality table information from this GT for MC

process.load("HLTrigger.HLTfilters.hltHighLevel_cfi")
process.hltMB = process.hltHighLevel.clone()
process.hltMB.HLTPaths = [
               #"HLT_HIL1MinimumBiasHF1AND*",
               "HLT_HIMinimumBias_*"
              ]
process.hltMB.andOr = cms.bool(True)
process.hltMB.throw = cms.bool(False)

# Add PbPb collision event selection 
process.load('HeavyIonsAnalysis.EventAnalysis.skimanalysis_cfi')
process.load('HeavyIonsAnalysis.EventAnalysis.collisionEventSelection_cff')

# Define the event selection sequence
process.eventFilter_MB = cms.Sequence(
    process.phfCoincFilter2Th4 *
    process.primaryVertexFilter *
    process.clusterCompatibilityFilter
)

# Load you analyzer with initial configuration
process.load("AnaTwoPC.AnaTwoPC.chargedepptcorr_cff")
process.defaultAnalysis_010   = process.CPDC010.clone()
process.defaultAnalysis_1030   = process.CPDC1030.clone()
process.defaultAnalysis_3050   = process.CPDC3050.clone()
process.defaultAnalysis_5080   = process.CPDC5080.clone()
process.defaultAnalysis_05   = process.CPDC05.clone()
process.defaultAnalysis_510   = process.CPDC510.clone()
process.defaultAnalysis_1015   = process.CPDC1015.clone()
process.defaultAnalysis_1520   = process.CPDC1520.clone()
process.defaultAnalysis_2025   = process.CPDC2025.clone()
process.defaultAnalysis_2530   = process.CPDC2530.clone()
process.defaultAnalysis_3035   = process.CPDC3035.clone()
process.defaultAnalysis_3540   = process.CPDC3540.clone()
process.defaultAnalysis_4050   = process.CPDC4050.clone()
process.defaultAnalysis_5060   = process.CPDC5060.clone()
process.defaultAnalysis_6070   = process.CPDC6070.clone()
process.defaultAnalysis_70100   = process.CPDC70100.clone()
process.defaultAnalysis_0100   = process.CPDC0100.clone()


process.p = cms.Path(
    #process.centralityBin*   
    process.hltMB*
    process.eventFilter_MB*
    # Compute centrality
    #process.defaultAnalysis_010 *
    #process.defaultAnalysis_1030 *
    #process.defaultAnalysis_3050 *
    #process.defaultAnalysis_5080 
    process.defaultAnalysis_05   *
    process.defaultAnalysis_510  *
    process.defaultAnalysis_1015 *
    process.defaultAnalysis_1520 *
    process.defaultAnalysis_2025 *
    process.defaultAnalysis_2530 *
    process.defaultAnalysis_3035 *
    process.defaultAnalysis_3540 * 
    process.defaultAnalysis_4050 *
    process.defaultAnalysis_5060 *
    process.defaultAnalysis_6070 
    #process.defaultAnalysis_70100 
    #process.defaultAnalysis_0100
)
