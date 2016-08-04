import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )
#process.MessageLogger.cerr.FwkReport.reportEvery = 100

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        'file:/afs/cern.ch/user/t/tuos/work/private/hin1600x/flowPbPb/CMSSW_5_3_20/src/hiMB_1001_1_irY.root'
    )
)

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = 'GR_R_53_LV6::All'

from HeavyIonsAnalysis.Configuration.CommonFunctions_cff import *
overrideCentrality(process)
process.HeavyIonGlobalParameters = cms.PSet(
        centralityVariable = cms.string("HFtowers"),
#       nonDefaultGlauberModel = cms.string("Hydjet_2760GeV"),
        centralitySrc = cms.InputTag("hiCentrality")
        )

import HLTrigger.HLTfilters.hltHighLevel_cfi
process.hltHIMB = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.hltHIMB.HLTPaths = ['HLT_HIMinBiasHfOrBSC_*'] # for allphysics
process.hltHIMB.andOr = cms.bool(True)
process.hltHIMB.throw = cms.bool(False)

process.TFileService = cms.Service("TFileService",
                                  fileName=cms.string("flowCorr2760_data.root")
                                  )


process.flowCorr = cms.EDAnalyzer('FlowCorr',
   EvtPlane         = cms.InputTag("hiEvtPlane"),
   EvtPlaneFlat     = cms.InputTag("hiEvtPlaneFlat",""),  
   HiMC             = cms.InputTag("heavyIon"),                            
   Vertex           = cms.InputTag("hiSelectedVertex"),
   #Track            = cms.InputTag("hiGeneralTracks"), 
   Track            = cms.InputTag("hiGeneralAndPixelTracks"), 
   TrackQuality     = cms.string('highPurity'),
   Tower            = cms.InputTag("towerMaker"),
   trackPtMinCut = cms.double(0.3),
   trackPtMaxCut = cms.double(5.0),
   trackEtaCut = cms.double(2.4),
   trackEtaMinCut = cms.double(0.6),
   ptErrCut = cms.double(0.1),
   dzRelCut = cms.double(3.0),
   dxyRelCut = cms.double(3.0)
)


process.p = cms.Path(process.flowCorr)



