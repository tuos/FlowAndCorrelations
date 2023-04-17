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
'/store/hidata/HIRun2018A/HIMinimumBias19/MINIAOD/PbPb18_MiniAODv1-v1/00000/06282a76-5a7c-4511-b2f1-85889a66fd8d.root',
'/store/hidata/HIRun2018A/HIMinimumBias19/MINIAOD/PbPb18_MiniAODv1-v1/00000/11b73de7-8834-48df-9097-90228e37a1b5.root',
'/store/hidata/HIRun2018A/HIMinimumBias19/MINIAOD/PbPb18_MiniAODv1-v1/00000/12415df0-822d-4dc5-a7f6-97dd9e31d183.root',
'/store/hidata/HIRun2018A/HIMinimumBias19/MINIAOD/PbPb18_MiniAODv1-v1/00000/129e9a3a-cccb-4ca7-9ad8-49c1ff7a6c6b.root',
'/store/hidata/HIRun2018A/HIMinimumBias19/MINIAOD/PbPb18_MiniAODv1-v1/00000/145cf5b1-cf64-4779-9e74-ec2c49a0e350.root',
'/store/hidata/HIRun2018A/HIMinimumBias19/MINIAOD/PbPb18_MiniAODv1-v1/00000/14faf074-66a5-48c1-bde8-431a3820ac53.root',
'/store/hidata/HIRun2018A/HIMinimumBias19/MINIAOD/PbPb18_MiniAODv1-v1/00000/15243c84-9b7c-4aed-9cc4-ee7baf2da642.root',
'/store/hidata/HIRun2018A/HIMinimumBias19/MINIAOD/PbPb18_MiniAODv1-v1/00000/157c9341-e6c7-492e-b364-00a7243e1f69.root',
'/store/hidata/HIRun2018A/HIMinimumBias19/MINIAOD/PbPb18_MiniAODv1-v1/00000/15962c75-bd5b-44ca-a961-aaea7817b8c0.root',
'/store/hidata/HIRun2018A/HIMinimumBias19/MINIAOD/PbPb18_MiniAODv1-v1/00000/19a9650a-27dc-4e4c-92ca-e28dc601a078.root',
'/store/hidata/HIRun2018A/HIMinimumBias19/MINIAOD/PbPb18_MiniAODv1-v1/00000/1b58a4a0-ba4f-4efa-b313-cc0cf3f0bb58.root',
'/store/hidata/HIRun2018A/HIMinimumBias19/MINIAOD/PbPb18_MiniAODv1-v1/00000/1c75bd48-dd0f-4dc6-9970-9ad78b8bd0c1.root',
'/store/hidata/HIRun2018A/HIMinimumBias19/MINIAOD/PbPb18_MiniAODv1-v1/00000/1db1f208-2a5c-4737-927a-acf7bf4c419c.root',
'/store/hidata/HIRun2018A/HIMinimumBias19/MINIAOD/PbPb18_MiniAODv1-v1/00000/1ec5bb45-0783-41c2-a6ca-705c71a02eaf.root'
),
                skipBadFiles=cms.untracked.bool(True),
	        duplicateCheckMode = cms.untracked.string('noDuplicateCheck')
)

#define number of events to be processed (-1 means all)
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(1000000))

# Set the global tag
from Configuration.AlCa.GlobalTag import GlobalTag
if runOnDATA :
   process.GlobalTag = GlobalTag(process.GlobalTag, '112X_dataRun2_PromptLike_HI_v3', '') #centrality table information from this GT for DATA
else :
   process.GlobalTag = GlobalTag(process.GlobalTag, '112X_upgrade2018_realistic_HI_v9', '') #centrality table information from this GT for MC

# Add PbPb collision event selection 
process.load('HeavyIonsAnalysis.EventAnalysis.skimanalysis_cfi')
process.load('HeavyIonsAnalysis.EventAnalysis.collisionEventSelection_cff')

# Define the event selection sequence
process.eventFilter_HM = cms.Sequence(
    process.phfCoincFilter2Th4 *
    process.primaryVertexFilter *
    process.clusterCompatibilityFilter
)

# Define the output
process.TFileService = cms.Service("TFileService",fileName = cms.string('peripheral_pbpb_miniAOD_mpt_withevselec.root'))

process.demo = cms.EDAnalyzer('MeanPtAnalyzer',
                        vertices  = cms.InputTag("offlineSlimmedPrimaryVerticesRecovery"),
                        tracks   = cms.InputTag("packedPFCandidates"), ###for general tracks - IMPORTANT: TO USE THIS, PLEASE SET "isPixelTracks=False"
                        #tracks   = cms.InputTag("hiPixelTracks"), ###for pixel tracks - IMPORTANT: TO USE THIS, PLEASE SET "isPixelTracks=True"
                        isPixelTracks = cms.bool(False), ###to switch to proper track selection
                        trackschi2 = cms.InputTag("packedPFCandidateTrackChi2"),
                        centrality    = cms.InputTag("hiCentrality","","reRECO"),
                        centralityBin = cms.InputTag("centralityBin","HFtowers"),
                        eventPlane = cms.InputTag("hiEvtPlaneFlat") ##calibrated event planes with recentering and flattening applied 
)

process.p = cms.Path(process.eventFilter_HM*process.demo) # with selection
process.schedule = cms.Schedule(process.p)
