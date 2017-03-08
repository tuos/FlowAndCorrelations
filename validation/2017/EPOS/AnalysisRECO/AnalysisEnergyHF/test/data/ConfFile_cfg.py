import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10323) )
#process.MessageLogger.cerr.FwkReport.reportEvery = 10

process.source = cms.Source("PoolSource",
                            duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
                fileNames = cms.untracked.vstring(
'/store/hidata/PARun2016C/PAMinimumBias1/AOD/PromptReco-v1/000/286/010/00000/4083EE49-41B7-E611-816E-02163E0141A0.root',
'/store/hidata/PARun2016C/PAMinimumBias1/AOD/PromptReco-v1/000/286/010/00000/408724E8-40B7-E611-A05D-FA163EF22524.root',
'/store/hidata/PARun2016C/PAMinimumBias1/AOD/PromptReco-v1/000/286/010/00000/4238BD1E-3CB7-E611-9906-FA163E9304EA.root',
'/store/hidata/PARun2016C/PAMinimumBias1/AOD/PromptReco-v1/000/286/010/00000/42C4E2DB-45B7-E611-9AAF-FA163E1B4008.root',
'/store/hidata/PARun2016C/PAMinimumBias1/AOD/PromptReco-v1/000/286/010/00000/46071893-3FB7-E611-A0DA-02163E011E45.root',
'/store/hidata/PARun2016C/PAMinimumBias1/AOD/PromptReco-v1/000/286/010/00000/469AD8A0-3DB7-E611-AE95-FA163E12B039.root',
'/store/hidata/PARun2016C/PAMinimumBias1/AOD/PromptReco-v1/000/286/010/00000/46B88DDB-4DB7-E611-86B9-02163E0128BC.root',
'/store/hidata/PARun2016C/PAMinimumBias1/AOD/PromptReco-v1/000/286/010/00000/46CDC6AA-44B7-E611-BE4D-02163E0135FB.root',
'/store/hidata/PARun2016C/PAMinimumBias1/AOD/PromptReco-v1/000/286/010/00000/46F353AC-3FB7-E611-AE68-02163E014109.root',
'/store/hidata/PARun2016C/PAMinimumBias1/AOD/PromptReco-v1/000/286/010/00000/46F7AD08-44B7-E611-930D-02163E011BBE.root',
'/store/hidata/PARun2016C/PAMinimumBias1/AOD/PromptReco-v1/000/286/010/00000/4802EB65-42B7-E611-B0E1-02163E011E04.root'
),
)

process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '80X_dataRun2_Prompt_v15', '')

process.load("HLTrigger.HLTfilters.hltHighLevel_cfi")
process.hltPAL1MinimumBiasHF_OR_SinglePixelTrack = process.hltHighLevel.clone()
process.hltPAL1MinimumBiasHF_OR_SinglePixelTrack.HLTPaths = ["HLT_PAL1MinimumBiasHF_OR_SinglePixelTrack_part1_v*"]

process.TFileService = cms.Service("TFileService",
                                  fileName=cms.string("flow_Validation_data_pPb_10k.root"))

process.demo = cms.EDAnalyzer('AnalysisEnergyHF',
   srcTracks = cms.InputTag("generalTracks"),
   srcVertex= cms.InputTag("offlinePrimaryVertices"),
   srcTower= cms.InputTag("towerMaker"),
   UseQuality = cms.bool(True),
   TrackQuality = cms.string('highPurity')
)

#process.p = cms.Path(process.demo)
process.p = cms.Path(process.hltPAL1MinimumBiasHF_OR_SinglePixelTrack * process.demo)
