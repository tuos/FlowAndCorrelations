import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.MessageLogger.cerr.FwkReport.reportEvery = 100

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        #'/store/user/qwang/HIMinimumBias3/HIMinBias_v2/160128_201904/0000/HIMinBias_101.root'
        #'file:/afs/cern.ch/user/t/tuos/work/private/hin1600x/flowPbPb/CMSSW_7_5_8_patch4/src/HIMinBias_101.root'
        #'/store/hidata/HIRun2015/HIMinimumBias2/AOD/25Aug2016-v1/00000/02645A37-E274-E611-AE31-D4AE528E309D.root'
        'file:/afs/cern.ch/user/t/tuos/work/private/hin1600x/flowPbPb/CMSSW_7_5_8_patch4/src/pixeltracking_101.root'
    )
)

process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '75X_dataRun2_v13', '')

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
process.clusterCompatibilityFilter.clusterPars = cms.vdouble(0.0,0.006)

process.flowCorr = cms.EDAnalyzer('FlowCorr',
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
   trackPtMaxCut = cms.double(20.0),
   trackEtaCut = cms.double(0.8),
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

process.p = cms.Path(process.hltMB * process.collisionEventSelectionAOD * process.flowCorr)


