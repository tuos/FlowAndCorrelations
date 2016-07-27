import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
#process.MessageLogger.cerr.FwkReport.reportEvery = 100

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        '/store/user/qwang/HIMinimumBias3/HIMinBias_v2/160128_201904/0000/HIMinBias_101.root'
        #'file:/afs/cern.ch/user/t/tuos/work/private/hin1600x/flowPbPb/CMSSW_7_5_8_patch4/src/HIMinBias_101.root'
        #'file:/afs/cern.ch/user/t/tuos/work/private/hin1600x/flowPbPb/CMSSW_7_5_8_patch4/src/pixeltracking_101.root'
    )
)

process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '75X_dataRun2_v12', '')

process.load("HLTrigger.HLTfilters.hltHighLevel_cfi")
process.hltMB = process.hltHighLevel.clone()
process.hltMB.HLTPaths = [
               "HLT_HIL1MinimumBiasHF1AND*",
               "HLT_HIL1MinimumBiasHF2AND*"
              ]
process.hltMB.andOr = cms.bool(True)
process.hltMB.throw = cms.bool(False)

process.load("RecoHI.HiCentralityAlgos.CentralityBin_cfi") 

process.TFileService = cms.Service("TFileService",
                                  fileName=cms.string("flowCorr_data.root")
                                  )

process.load('HeavyIonsAnalysis.Configuration.collisionEventSelection_cff')

process.flowCorr = cms.EDAnalyzer('FlowCorr',
   CentralitySrc    = cms.InputTag("hiCentrality"),
   CentralityBinSrc = cms.InputTag("centralityBin","HFtowers"),
   EvtPlane         = cms.InputTag("hiEvtPlane"),
   EvtPlaneFlat     = cms.InputTag("hiEvtPlaneFlat",""),  
   HiMC             = cms.InputTag("heavyIon"),                            
   Vertex           = cms.InputTag("hiSelectedVertex"),
   Track            = cms.InputTag("hiGeneralTracks"), 
   #Track            = cms.InputTag("hiGeneralAndPixelTracks"), 
   TrackQuality     = cms.untracked.string('highPurity'),
   Tower            = cms.InputTag("towerMaker"),
   trackPtMinCut = cms.double(0.3),
   trackPtMaxCut = cms.double(5.0),
   trackEtaCut = cms.double(2.4),
   trackEtaMinCut = cms.double(0.6),
   ptErrCut = cms.double(0.1),
   dzRelCut = cms.double(3.0),
   dxyRelCut = cms.double(3.0),
   evtPlaneLevel    = cms.int32(0)
)

process.p = cms.Path(process.hltMB * process.collisionEventSelectionAOD * process.flowCorr)


