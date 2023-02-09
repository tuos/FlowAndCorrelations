import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.Types as CfgTypes

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.source = cms.Source("PoolSource",
                            duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
                fileNames = cms.untracked.vstring(
#'/store/hidata/PARun2016C/PAMinimumBias1/AOD/PromptReco-v1/000/286/010/00000/4802EB65-42B7-E611-B0E1-02163E011E04.root'
'/store/hidata/PARun2016C/PAMinimumBias20/AOD/PromptReco-v1/000/285/975/00000/00CB2ACC-F9B5-E611-B5B5-FA163E38D1EC.root'
),
)


process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '80X_dataRun2_Prompt_v16', '')

process.load("HLTrigger.HLTfilters.hltHighLevel_cfi")
process.hltPAL1MinimumBiasHF_OR_SinglePixelTrack = process.hltHighLevel.clone()
process.hltPAL1MinimumBiasHF_OR_SinglePixelTrack.HLTPaths = ["HLT_PAL1MinimumBiasHF_OR_SinglePixelTrack_part*_v*"]
process.hltPAL1MinimumBiasHF_OR_SinglePixelTrack.andOr = cms.bool(True)
process.hltPAL1MinimumBiasHF_OR_SinglePixelTrack.throw = cms.bool(False)

process.PAprimaryVertexFilter = cms.EDFilter("VertexSelector",
    src = cms.InputTag("offlinePrimaryVertices"),
    cut = cms.string("!isFake && abs(z) <= 25 && position.Rho <= 2 && tracksSize >= 2"),
    filter = cms.bool(True), # otherwise it won't filter the events
)
process.NoScraping = cms.EDFilter("FilterOutScraping",
 applyfilter = cms.untracked.bool(True),
 debugOn = cms.untracked.bool(False),
 numtrack = cms.untracked.uint32(10),
 thresh = cms.untracked.double(0.25)
)
process.load("HeavyIonsAnalysis.Configuration.hfCoincFilter_cff")

process.load("HeavyIonsAnalysis.VertexAnalysis.pileUpFilter_cff")

process.TFileService = cms.Service("TFileService",
                                  fileName=cms.string("flow_data_pPb_tree.root"))

process.demo = cms.EDAnalyzer('AnalysisTrees',
   srcTracks = cms.InputTag("generalTracks"),
   srcVertex= cms.InputTag("offlinePrimaryVertices"),
   srcTower= cms.InputTag("towerMaker"),
   UseQuality = cms.bool(True),
   TrackQuality = cms.string('highPurity')
)

process.eventSelection = cms.Sequence(process.hltPAL1MinimumBiasHF_OR_SinglePixelTrack * process.PAprimaryVertexFilter * process.NoScraping * process.hfCoincFilter * process.pileUpFilter_pPb8TeV_vtx1)

#process.p = cms.Path(process.demo)
#process.p = cms.Path(process.hltPAL1MinimumBiasHF_OR_SinglePixelTrack * process.demo)
process.p = cms.Path(process.eventSelection * process.demo)

