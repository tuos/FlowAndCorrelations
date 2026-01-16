###Adapted from: https://github.com/denerslemos/MiniAOD_examplecode

import FWCore.ParameterSet.Config as cms
process = cms.Process('Demo')

process.load('Configuration.Geometry.GeometryDB_cff')
process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')

# Limit the output messages
process.load('FWCore.MessageService.MessageLogger_cfi')
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool( True ),
)

runOnDATA = True ###IMPORTANT: please, to run in MC set to "False"

process.source = cms.Source("PoolSource",
                fileNames = cms.untracked.vstring(
'/store/hidata/NeNeRun2025/IonPhysics0/MINIAOD/PromptReco-v1/000/394/269/00000/9b8c0e8b-354b-4bfa-afaa-f7e7a4c41956.root'
#'/store/hidata/OORun2025/IonPhysics0/MINIAOD/PromptReco-v1/000/394/175/00000/057e03f0-0fa4-4042-b334-3b16176479c2.root'
#'/store/hidata/OORun2025/IonPhysics0/MINIAOD/PromptReco-v1/000/394/184/00000/d77dc00b-6a4f-469d-a9ac-6ecd86cb2052.root'
#'/store/hidata/OORun2025/IonPhysics0/MINIAOD/PromptReco-v1/000/394/184/00000/dee79b6c-5835-4aa0-99c8-87533705ea01.root'
#'file:/home/tuos/oopo/pubcheck/06282a76-5a7c-4511-b2f1-85889a66fd8d.root',
#'file:/home/tuos/oopo/pubcheck/11b73de7-8834-48df-9097-90228e37a1b5.root',
#'file:/home/tuos/oopo/pubcheck/1ec5bb45-0783-41c2-a6ca-705c71a02eaf.root'
#'/store/hidata/HIRun2018A/HIMinimumBias19/MINIAOD/PbPb18_MiniAODv1-v1/00000/06282a76-5a7c-4511-b2f1-85889a66fd8d.root',
#'/store/hidata/HIRun2018A/HIMinimumBias19/MINIAOD/PbPb18_MiniAODv1-v1/00000/11b73de7-8834-48df-9097-90228e37a1b5.root',
#'/store/hidata/HIRun2018A/HIMinimumBias19/MINIAOD/PbPb18_MiniAODv1-v1/00000/1ec5bb45-0783-41c2-a6ca-705c71a02eaf.root'
),
                skipBadFiles=cms.untracked.bool(True),
	        duplicateCheckMode = cms.untracked.string('noDuplicateCheck')
)

#define number of events to be processed (-1 means all)
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))

#import FWCore.Utilities.FileUtils as FileUtils
#mylist = FileUtils.loadListFromFile ('output_job0.txt')
#for fname in mylist:
 #process.source.fileNames.append('file:%s' % (fname))
# process.source.fileNames.append('%s' % (fname))

# Set the global tag
from Configuration.AlCa.GlobalTag import GlobalTag
if runOnDATA :
   process.GlobalTag = GlobalTag(process.GlobalTag, '150X_dataRun3_Prompt_v1', '') #centrality table information from this GT for DATA
else :
   process.GlobalTag = GlobalTag(process.GlobalTag, '150X_dataRun3_Prompt_v1', '') #centrality table information from this GT for MC

# Add OO collision event selection 
process.load('HeavyIonsAnalysis.EventAnalysis.skimanalysis_cfi')
process.load('HeavyIonsAnalysis.EventAnalysis.collisionEventSelection_cff')
process.load('HeavyIonsAnalysis.EventAnalysis.hffilterPF_cfi')

# Define the event selection sequence
process.eventFilter_HM = cms.Sequence(
    #process.phfCoincFilter2Th4 *
    process.phfCoincFilterPF2Th4 *
    process.primaryVertexFilter *
    process.clusterCompatibilityFilter
)

#import FWCore.PythonUtilities.LumiList as LumiList
#process.source.lumisToProcess = LumiList.LumiList(filename = '/home/tuos/oopo/data/CMSSW_15_0_9_patch3/src/OOAnalysisFlow/QCAnalysisVn/test/test/hfcoin/nene/slurm/pre_nene_goodlumis.json').getVLuminosityBlockRange()

from HLTrigger.HLTfilters.hltHighLevel_cfi import hltHighLevel  
process.hltfilter = hltHighLevel.clone(                         
    HLTPaths = [                                                
       # "HLT_HIMinimumBiasHF1ANDZDC1nOR_v*",
#"HLT_HIMinimumBiasHF1AND*"
       "HLT_MinimumBiasHF_OR_BptxAND_v1" 
        #"HLT_HIMinimumBiasHF1AND_v*"
#        "HLT_HIL1_UCC_0_1_v3"

    ]                                                           
)      

# Define the output
process.TFileService = cms.Service("TFileService",fileName = cms.string('nene_miniAOD_qc.root'))

process.demo = cms.EDAnalyzer('QCAnalysisVn',
                        vertices  = cms.InputTag("offlineSlimmedPrimaryVertices"),
                        tracks   = cms.InputTag("packedPFCandidates"), ###for general tracks - IMPORTANT: TO USE THIS, PLEASE SET "isPixelTracks=False"
                        pfCands  = cms.InputTag("packedPFCandidates"),
                        #tracks   = cms.InputTag("hiPixelTracks"), ###for pixel tracks - IMPORTANT: TO USE THIS, PLEASE SET "isPixelTracks=True"
                        isPixelTracks = cms.bool(False), ###to switch to proper track selection
                        trackschi2 = cms.InputTag("packedPFCandidateTrackChi2"),
                        centrality    = cms.InputTag("hiCentrality","","reRECO"),
                        centralityBin = cms.InputTag("centralityBin","HFtowers"),
                        #eventPlane = cms.InputTag("hiEvtPlaneFlat"), ##calibrated event planes with recentering and flattening applied 

#Vertex selection
   minvz         = cms.untracked.double(-15.0),
   maxvz         = cms.untracked.double(15.0),

#Track selection
   etamin    = cms.untracked.double(-2.4),
   etamax    = cms.untracked.double(2.4),
   ptmin     = cms.untracked.double(0.3),
   ptmax     = cms.untracked.double(3.0),
   dzdzerror = cms.untracked.double(3.0),
   d0d0error = cms.untracked.double(3.0),
   pterrorpt = cms.untracked.double(0.1),
#Acc X Eff
   cweight    = cms.untracked.bool(True),
   #fname = cms.untracked.InputTag('OO_Hijing_5p36_ppreco_efftables.root'),
   fname = cms.untracked.InputTag('Eff_OO_2025_Hijing_NopU_Nominal.root'),

   runreco    = cms.untracked.bool(True),
   rungen     = cms.untracked.bool(False)
)

process.p = cms.Path(process.eventFilter_HM*process.hltfilter*process.demo) # with selection
process.schedule = cms.Schedule(process.p)

