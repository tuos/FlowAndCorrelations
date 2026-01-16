import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.Types as CfgTypes

process = cms.Process("Demo")

process.load('Configuration.Geometry.GeometryDB_cff')
process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000000) )
#process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool( True ),
)

runOnDATA = True ###IMPORTANT: please, to run in MC set to "False"

process.source = cms.Source("PoolSource",
                fileNames = cms.untracked.vstring(
'/store/hidata/OORun2025/IonPhysics0/MINIAOD/PromptReco-v1/000/394/175/00000/057e03f0-0fa4-4042-b334-3b16176479c2.root'
),
                skipBadFiles=cms.untracked.bool(True),
            duplicateCheckMode = cms.untracked.string('noDuplicateCheck')
)

import FWCore.Utilities.FileUtils as FileUtils
mylist = FileUtils.loadListFromFile ('filelist394175.txt')
for fname in mylist:
 #process.source.fileNames.append('file:%s' % (fname))
 process.source.fileNames.append('%s' % (fname))

# Set the global tag
from Configuration.AlCa.GlobalTag import GlobalTag
if runOnDATA :
   process.GlobalTag = GlobalTag(process.GlobalTag, '150X_dataRun3_Prompt_v1', '') #centrality table information from this GT for DATA
else :
   process.GlobalTag = GlobalTag(process.GlobalTag, '150X_dataRun3_Prompt_v1', '') #centrality table information from this GT for MC

# Add OO collision event selection 
process.load('HeavyIonsAnalysis.EventAnalysis.skimanalysis_cfi')
process.load('HeavyIonsAnalysis.EventAnalysis.collisionEventSelection_cff')
process.load('HeavyIonsAnalysis.EventAnalysis.hffilterPF_cfi')

# Define the event selection sequence
process.eventFilter_HM = cms.Sequence(
    #process.phfCoincFilter2Th4 *
    process.phfCoincFilterPF2Th4 *
    process.primaryVertexFilter *
    process.clusterCompatibilityFilter
)

import FWCore.PythonUtilities.LumiList as LumiList
process.source.lumisToProcess = LumiList.LumiList(filename = 'pre_oo_goodlumis.json').getVLuminosityBlockRange()

from HLTrigger.HLTfilters.hltHighLevel_cfi import hltHighLevel
process.hltfilter = hltHighLevel.clone(
    HLTPaths = [
       # "HLT_HIMinimumBiasHF1ANDZDC1nOR_v*",
#"HLT_HIMinimumBiasHF1AND*"
       "HLT_MinimumBiasHF_OR_BptxAND_v1"
        #"HLT_HIMinimumBiasHF1AND_v*"
#        "HLT_HIL1_UCC_0_1_v3"

    ]
)

# Define the output
process.TFileService = cms.Service("TFileService",fileName = cms.string('oo_miniAOD_sp_gotable.root'))

process.demo = cms.EDAnalyzer('SPAnalysis',
   vertices  = cms.InputTag("offlineSlimmedPrimaryVertices"),
   tracks   = cms.InputTag("packedPFCandidates"), ###for general tracks - IMPORTANT: TO USE THIS, PLEASE SET "isPixelTracks=False"
   pfCands  = cms.InputTag("packedPFCandidates"),
   genTracks = cms.InputTag('genParticles'),
#   srcTracks = cms.InputTag("generalTracks")#,
   etaCut = cms.untracked.double(3.0),
#Vertex selection
   minvz         = cms.untracked.double(-15.0),
   maxvz         = cms.untracked.double(15.0),

#Track selection
   qualityString = cms.string("highPurity"),
   etamin    = cms.untracked.double(-2.4),
   etamax    = cms.untracked.double(2.4),
   ptmin     = cms.untracked.double(0.3),
   ptmax     = cms.untracked.double(100.0),
   dzdzerror = cms.untracked.double(3.0),
   d0d0error = cms.untracked.double(3.0),
   pterrorpt = cms.untracked.double(999.0),
#Acc X Eff
   cweight    = cms.untracked.bool(True),
   #fname = cms.untracked.InputTag('OO_Hijing_5p36_ppreco_efftables.root'),
   fname = cms.untracked.InputTag('Eff_OO_2025_Hijing_NopU_Nominal.root'),

   runreco    = cms.untracked.bool(True),
   rungen     = cms.untracked.bool(False)

#   UseQuality = cms.bool(True),
#   TrackQuality = cms.string('highPurity')
)

#process.eventSelection = cms.Sequence(process.hltPAL1MinimumBiasHF_OR_SinglePixelTrack * process.PAprimaryVertexFilter * process.NoScraping * process.hfCoincFilter * process.pileUpFilter_pPb8TeV_vtx1)

process.p = cms.Path(process.eventFilter_HM*process.hltfilter*process.demo) # with selection
process.schedule = cms.Schedule(process.p)

