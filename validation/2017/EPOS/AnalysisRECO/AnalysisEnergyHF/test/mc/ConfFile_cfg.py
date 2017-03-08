import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(11000) )
#process.MessageLogger.cerr.FwkReport.reportEvery = 10

process.source = cms.Source("PoolSource",
                            duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
                fileNames = cms.untracked.vstring(
#'file:/home/tuos/CMSSW_7_5_5_patch3/src/step3_Debug_pPb_8TeV_RAW2DIGI_L1Reco_RECO_EI_VALIDATION_DQM_1.root'
'/store/user/gsfs/EPOSpPb_MinBias4080_4080_DataBS_/EPOS_RECODEBUG_20170206/170206_152334/0000/step3_Debug_pPb_8TeV_RAW2DIGI_L1Reco_RECO_EI_VALIDATION_DQM_1.root',
'/store/user/gsfs/EPOSpPb_MinBias4080_4080_DataBS_/EPOS_RECODEBUG_20170206/170206_152334/0000/step3_Debug_pPb_8TeV_RAW2DIGI_L1Reco_RECO_EI_VALIDATION_DQM_10.root',
'/store/user/gsfs/EPOSpPb_MinBias4080_4080_DataBS_/EPOS_RECODEBUG_20170206/170206_152334/0000/step3_Debug_pPb_8TeV_RAW2DIGI_L1Reco_RECO_EI_VALIDATION_DQM_100.root',
'/store/user/gsfs/EPOSpPb_MinBias4080_4080_DataBS_/EPOS_RECODEBUG_20170206/170206_152334/0000/step3_Debug_pPb_8TeV_RAW2DIGI_L1Reco_RECO_EI_VALIDATION_DQM_101.root',
'/store/user/gsfs/EPOSpPb_MinBias4080_4080_DataBS_/EPOS_RECODEBUG_20170206/170206_152334/0000/step3_Debug_pPb_8TeV_RAW2DIGI_L1Reco_RECO_EI_VALIDATION_DQM_102.root',
'/store/user/gsfs/EPOSpPb_MinBias4080_4080_DataBS_/EPOS_RECODEBUG_20170206/170206_152334/0000/step3_Debug_pPb_8TeV_RAW2DIGI_L1Reco_RECO_EI_VALIDATION_DQM_103.root',
'/store/user/gsfs/EPOSpPb_MinBias4080_4080_DataBS_/EPOS_RECODEBUG_20170206/170206_152334/0000/step3_Debug_pPb_8TeV_RAW2DIGI_L1Reco_RECO_EI_VALIDATION_DQM_104.root',
'/store/user/gsfs/EPOSpPb_MinBias4080_4080_DataBS_/EPOS_RECODEBUG_20170206/170206_152334/0000/step3_Debug_pPb_8TeV_RAW2DIGI_L1Reco_RECO_EI_VALIDATION_DQM_105.root',
'/store/user/gsfs/EPOSpPb_MinBias4080_4080_DataBS_/EPOS_RECODEBUG_20170206/170206_152334/0000/step3_Debug_pPb_8TeV_RAW2DIGI_L1Reco_RECO_EI_VALIDATION_DQM_106.root',
'/store/user/gsfs/EPOSpPb_MinBias4080_4080_DataBS_/EPOS_RECODEBUG_20170206/170206_152334/0000/step3_Debug_pPb_8TeV_RAW2DIGI_L1Reco_RECO_EI_VALIDATION_DQM_107.root',
'/store/user/gsfs/EPOSpPb_MinBias4080_4080_DataBS_/EPOS_RECODEBUG_20170206/170206_152334/0000/step3_Debug_pPb_8TeV_RAW2DIGI_L1Reco_RECO_EI_VALIDATION_DQM_108.root'
),
)

process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '80X_mcRun2_pA_v4', '')

process.load("HLTrigger.HLTfilters.hltHighLevel_cfi")
process.hltPAL1MinimumBiasHF_OR_SinglePixelTrack = process.hltHighLevel.clone()
process.hltPAL1MinimumBiasHF_OR_SinglePixelTrack.HLTPaths = ["HLT_PAL1MinimumBiasHF_OR_SinglePixelTrack_part1_v*"]

process.TFileService = cms.Service("TFileService",
                                  fileName=cms.string("flow_Validation_EPOS_pPb_10k.root"))

process.demo = cms.EDAnalyzer('AnalysisEnergyHF',
   srcTracks = cms.InputTag("generalTracks"),
   srcVertex= cms.InputTag("offlinePrimaryVertices"),
   srcTower= cms.InputTag("towerMaker"),
   UseQuality = cms.bool(True),
   TrackQuality = cms.string('highPurity')
)

#process.p = cms.Path(process.demo)
process.p = cms.Path(process.hltPAL1MinimumBiasHF_OR_SinglePixelTrack * process.demo)
