import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.MessageLogger.cerr.FwkReport.reportEvery = 200

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
#        '/store/user/qwang/HIMinimumBias3/HIMinBias_v2/160128_201904/0000/HIMinBias_101.root'
'/store/hidata/HIRun2015/HIFlowCorr/AOD/25Aug2016-v1/80001/48346A01-3974-E611-A0C4-782BCB3BC981.root',
'/store/hidata/HIRun2015/HIFlowCorr/AOD/25Aug2016-v1/80001/48CCA229-6D74-E611-92CF-90B11C44432D.root',
'/store/hidata/HIRun2015/HIFlowCorr/AOD/25Aug2016-v1/80001/4ED76997-4574-E611-A1F8-F01FAFE15A5B.root',
'/store/hidata/HIRun2015/HIFlowCorr/AOD/25Aug2016-v1/80001/60A9D59A-6074-E611-AA5F-F01FAFD69911.root'
    )
)

process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
from Configuration.AlCa.GlobalTag import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, '103X_dataRun2_Prompt_fixEcalADCToGeV_v1', '')
process.GlobalTag = GlobalTag(process.GlobalTag, '103X_dataRun2_HLT_v1', '')

process.load("HLTrigger.HLTfilters.hltHighLevel_cfi")
process.hltMB = process.hltHighLevel.clone()
process.hltMB.HLTPaths = [
               "HLT_HIUCC020_v*"
#               "HLT_HIL1MinimumBiasHF1AND*",
#               "HLT_HIL1MinimumBiasHF2AND*"
              ]
process.hltMB.andOr = cms.bool(True)
process.hltMB.throw = cms.bool(False)

process.load("RecoHI.HiCentralityAlgos.CentralityBin_cfi") 

process.TFileService = cms.Service("TFileService",
                                  fileName=cms.string("aps_ucc_analyzer_data.root")
                                  )

#process.load('HeavyIonsAnalysis.Configuration.collisionEventSelection_cff')

process.flowCorr = cms.EDAnalyzer('MConeAnalyzer',
   CentralitySrc    = cms.InputTag("hiCentrality"),
   CentralityBinSrc = cms.InputTag("centralityBin","HFtowers"),
   EvtPlane         = cms.InputTag("hiEvtPlane"),
   EvtPlaneFlat     = cms.InputTag("hiEvtPlaneFlat",""),
   HiMC             = cms.InputTag("heavyIon"),
   Vertex           = cms.InputTag("hiSelectedVertex"),
   #Track            = cms.InputTag("hiGeneralTracks"), 
   Track            = cms.InputTag("hiGeneralAndPixelTracks"),
   TrackQuality     = cms.untracked.string('highPurity'),
   Tower            = cms.InputTag("towerMaker"),
   trackPtMinCut = cms.double(0.3),
   trackPtMaxCut = cms.double(2000.0),
   trackEtaCut = cms.double(2.4),
   trackEtaMinCut = cms.double(0.0),
   ptErrCut = cms.double(0.05),
   dzRelCut = cms.double(2.0),
   dxyRelCut = cms.double(2.0),
   chi2nMax = cms.double(0.15),
   chi2nPixelMax = cms.double(9.0),
   dzRelPixelCut = cms.double(6.0),
   nhitsMin = cms.int32(11),
   algoParameters = cms.vint32(4,5,6,7),
   vertexZMin = cms.double(0.0),
   vertexZMax = cms.double(15.0),
   hfEtaMin = cms.double(3.0),
   hfEtaMax = cms.double(5.0),
   evtPlaneLevel    = cms.int32(0)
)

#process.p = cms.Path(process.hltMB * process.collisionEventSelectionAOD * process.flowCorr)
process.p = cms.Path(process.hltMB * process.flowCorr)

