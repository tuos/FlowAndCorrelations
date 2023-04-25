import FWCore.ParameterSet.Config as cms

process = cms.Process("CmsTwoPartCorrAnalysis")


# __________________ General _________________

# Configure the logger
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 100

# Configure the number of maximum event the analyser run on in interactive mode
# -1 == ALL
process.maxEvents = cms.untracked.PSet( 
    #input = cms.untracked.int32(-1) 
    input = cms.untracked.int32(-1) 
    )


# __________________ I/O files _________________

# Define the input file to run on in interactive mode
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        #'/store/user/subehera/Hydjet_5360GeV_GEN_SIM/MB_Hydjet_Run3_recodebug_step4/221101_175550/0000/recodebug_hydjet_100.root'
        #'/store/hidata/HIRun2022A/HITestRaw10/AOD/PromptReco-v1/000/362/294/00000/2c44c97b-9e23-4d9e-8cbc-849d2efb4f6f.root'
        #"/store/hidata/HIRun2022A/HITestRaw5/AOD/PromptReco-v1/000/362/243/00000/abb52089-3a72-43dd-97d7-004736e9cc58.root"
        "/store/hidata/HIRun2022A/HITestRaw5/AOD/PromptReco-v1/000/362/294/00000/e3a81eb4-6ae1-44f8-842f-f2ed9c38c9b8.root"
        #"/store/hidata/HIRun2022A/HITestRaw5/AOD/PromptReco-v1/000/362/290/00000/37218c16-bcf8-463d-91a6-b9c1bc542187.root"
        #"/store/hidata/HIRun2022A/HITestRaw5/AOD/PromptReco-v1/000/362/290/00000/6e56422b-41c3-4d08-a0a7-bd1080622561.root"
    )
)

# Define output file name
import os
process.TFileService = cms.Service("TFileService",
     #fileName = cms.string(os.getenv('CMSSW_BASE') + '/src/Analyzers/ChargeDepAndPtCorr/test/chargeptdepcorr.root')
      fileName = cms.string('HI_testRun3_RAWDATA_JSON_newEventSelection_cent0100_Feb22_2023.root')
)


# __________________ Detector conditions _________________
#process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

#from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(
    process.GlobalTag,
    'auto:run3_data_prompt',
    ''
)



# __________________ Event selection _________________
import HLTrigger.HLTfilters.hltHighLevel_cfi
process.hltSelect = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.hltSelect.HLTPaths = ["HLT_HIMinimumBias_v2"]
#process.hltSelect.andOr = cms.bool(True)
#process.hltSelect.throw = cms.bool(False)
# Load HI event selection modules
#process.load('HeavyIonsAnalysis.Configuration.collisionEventSelection_cff')
# __________________ Analyse Sequence _________________
process.primaryVertexFilter = cms.EDFilter("VertexSelector",
           src = cms.InputTag("offlinePrimaryVertices"),
           cut = cms.string("!isFake && abs(z) <= 25 && position.Rho <= 2"),
           #cut = cms.string("!isFake && abs(z) <= 25"),
           filter = cms.bool(True),   # otherwise it won't filter the events
)
# Load you analyzer with initial configuration
process.load("Analyzers.CmsTwoPartCorrAnalysis.chargedepptcorr_cff")
process.defaultAnalysis_010   = process.CPDC010.clone()
process.defaultAnalysis_1030   = process.CPDC1030.clone()
process.defaultAnalysis_3050   = process.CPDC3050.clone()
process.defaultAnalysis_5080   = process.CPDC5080.clone()
process.defaultAnalysis_05   = process.CPDC05.clone()
process.defaultAnalysis_510   = process.CPDC510.clone()
process.defaultAnalysis_1015   = process.CPDC1015.clone()
process.defaultAnalysis_1520   = process.CPDC1520.clone()
process.defaultAnalysis_2025   = process.CPDC2025.clone()
process.defaultAnalysis_2530   = process.CPDC2530.clone()
process.defaultAnalysis_3035   = process.CPDC3035.clone()
process.defaultAnalysis_3540   = process.CPDC3540.clone()
process.defaultAnalysis_4050   = process.CPDC4050.clone()
process.defaultAnalysis_5060   = process.CPDC5060.clone()
process.defaultAnalysis_6070   = process.CPDC6070.clone()
process.defaultAnalysis_70100   = process.CPDC70100.clone()
process.defaultAnalysis_0100   = process.CPDC0100.clone()


process.p = cms.Path(
    #process.centralityBin*   
    process.hltSelect*
    process.primaryVertexFilter*
    # Compute centrality
    #process.defaultAnalysis_010 *
    #process.defaultAnalysis_1030 *
    #process.defaultAnalysis_3050 *
    #process.defaultAnalysis_5080 
    process.defaultAnalysis_05   *
    process.defaultAnalysis_510  *
    process.defaultAnalysis_1015 *
    process.defaultAnalysis_1520 *
    process.defaultAnalysis_2025 *
    process.defaultAnalysis_2530 *
    process.defaultAnalysis_3035 *
    process.defaultAnalysis_3540 * 
    process.defaultAnalysis_4050 *
    process.defaultAnalysis_5060 *
    process.defaultAnalysis_6070 *
    process.defaultAnalysis_70100 
    #process.defaultAnalysis_0100
)
