import FWCore.ParameterSet.Config as cms

process = cms.Process("CmsTwoPartCorrAnalysis")
process.load('Configuration.StandardSequences.Services_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
#process.load('Configuration.StandardSequences.MagneticField_38T_PostLS1_cff')                                                               
process.load('Configuration.StandardSequences.ReconstructionHeavyIons_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load("HeavyIonsAnalysis.Configuration.hfCoincFilter_cff")
process.load("RecoVertex.PrimaryVertexProducer.OfflinePrimaryVerticesRecovery_cfi")
# __________________ General _________________

# Configure the logger
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 10    

# Configure the number of maximum event the analyser run on in interactive mode
# -1 == ALL
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1) 
    #input = cms.untracked.int32(100) 
    #input = cms.untracked.int32(1000) 
)

process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))



# __________________ I/O files _________________

#----- Testing one One file -------------------
process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
                                #'/store/hidata/HIRun2018A/HIMinimumBias11/AOD/04Apr2019-v1/610000/54E9C8CE-C886-194D-8B7E-5A2017D83DF8.root'
                                
                                '/store/hidata/HIRun2018A/HIMinimumBias2/AOD/04Apr2019-v1/610012/FE8E3163-9424-6843-BF99-68581F91C7A3.root'
                                

),


)
#----------------------------------------------

# Define output file name
import os
process.TFileService = cms.Service("TFileService",
     #fileName = cms.string(os.getenv('CMSSW_BASE') + '/src/Analyzers/ChargeDepAndPtCorr/test/chargeptdepcorr.root')
     fileName = cms.string('chargeptdepcorr_central.root')
                                   
     #fileName = cms .string('cmssw/PhysicsTools/Utilities/scripts/edmPickEvents.py')
      
)


# __________________ Event selection _________________
process.load('HeavyIonsAnalysis.Configuration.collisionEventSelection_cff')



process.ana_step = cms.Path(
process.offlinePrimaryVerticesRecovery )
#process.HiForest )






process.eventSelections = cms.Sequence(
    process.clusterCompatibilityFilter
    + process.primaryVertexFilter
    + process.hfCoincFilter2Th4
    )

# trigger selection                                                                                                                    

import HLTrigger.HLTfilters.hltHighLevel_cfi
process.hltSelect = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.hltSelect.HLTPaths = [
 "HLT_HIMinimumBias_*",
 ]
process.hltSelect.andOr = cms.bool(True)
process.hltSelect.throw = cms.bool(False)
###                                                                                                 

process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.Geometry.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')

from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '103X_dataRun2_Prompt_v2', '')
#process.HiForest.GlobalTagLabel = process.GlobalTag.globaltag                                                                         

print('\n\033[31m~*~ USING CENTRALITY TABLE FOR PbPb 2018 ~*~\033[0m\n')
process.GlobalTag.snapshotTime = cms.string("9999-12-31 23:59:59.000")
process.GlobalTag.toGet.extend([
    cms.PSet(record = cms.string("HeavyIonRcd"),
        tag = cms.string("CentralityTable_HFtowers200_DataPbPb_periHYDJETshape_run2v1031x02_offline"),
        connect = cms.string("frontier://FrontierProd/CMS_CONDITIONS"),
        label = cms.untracked.string("HFtowers")
        ),
    ])

#-----------------------
# new centrality object with ZDC
#-----------------------
process.load('QWAna.QWZDC2018RecHit.QWZDC2018Producer_cfi')
process.load('QWAna.QWZDC2018RecHit.QWZDC2018RecHit_cfi')

process.newCent = cms.EDProducer("CentralityProducer",
    produceHFhits = cms.bool(False),
    produceHFtowers = cms.bool(False),
    produceEcalhits = cms.bool(False),
    produceZDChits = cms.bool(True),
    produceETmidRapidity = cms.bool(False),
    producePixelhits = cms.bool(False),
    produceTracks = cms.bool(False),
    producePixelTracks = cms.bool(False),
    reUseCentrality = cms.bool(True),
    srcZDChits = cms.InputTag("QWzdcreco"),
    lowGainZDC = cms.bool(True),

    doPixelCut = cms.bool(True),
    UseQuality = cms.bool(True),
    TrackQuality = cms.string('highPurity'),
    trackEtaCut = cms.double(2),
    trackPtCut = cms.double(1),
    hfEtaCut = cms.double(4), #hf above the absolute value of this cut is used
    midRapidityRange = cms.double(1),
    srcReUse = cms.InputTag("hiCentrality")
    )

#--------------------------------
#==================================================================
process.zdcPUfilter = cms.EDFilter('QWZDCPUFilter',
    src = cms.untracked.InputTag("newCent"),
    posPars = cms.untracked.vdouble(1098914.0, -174.),
    negPars = cms.untracked.vdouble(1322071.0, -193.),
    mode = cms.untracked.int32(3)
)


# __________________ Analyse Sequence _________________

# Load you analyzer with initial configuration
process.load("Analyzers.CmsTwoPartCorrAnalysis.chargedepptcorr_cff")
#process.defaultAnalysis_510   = process.CPDC510.clone()
process.defaultAnalysis_010   = process.CPDC010.clone()
process.defaultAnalysis_1020   = process.CPDC1020.clone()
#process.defaultAnalysis   = process.CPDCSUBASH.clone()

process.p = cms.Path(process.hltSelect *             # Requier HF coincidence with 3 GeV  
                     process.eventSelections *       # Clean up on vertices
                     process.centralityBin *        
                     #process.zdcdigi *
                     #process.QWzdcreco *
                     #process.newCent *
                     #process.zdcPUfilter *        # Clean up on pileup
                     process.defaultAnalysis_010 )
                     #process.defaultAnalysis_1020 )
                     
                     
from HLTrigger.Configuration.CustomConfigs import MassReplaceInputTag
process = MassReplaceInputTag(process,"offlinePrimaryVertices","offlinePrimaryVerticesRecovery")
process.offlinePrimaryVerticesRecovery.oldVertexLabel = "offlinePrimaryVertices"                     


