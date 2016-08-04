# EXTRA reconstruction and matching
#
# Started from:
#
# Auto generated configuration file
# using: 
# Revision: 1.381.2.28 
# Source: /local/reps/CMSSW/CMSSW/Configuration/PyReleaseValidation/python/ConfigBuilder.py,v 
# with command line options: step1 --filein dbs:/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/HiFall13-STARTHI53_V28-v2/GEN-SIM --fileout file:step1.root --mc --eventcontent RECODEBUG --datatier GEN-SIM-RECO --conditions STARTHI53_LV1::All --step DIGI,L1,DIGI2RAW,HLT:HIon,RAW2DIGI,L1Reco,RECO --scenario HeavyIons -n 3 --no_exec
import FWCore.ParameterSet.Config as cms

process = cms.Process('HLT')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContentHeavyIons_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.Digi_cff')
process.load('Configuration.StandardSequences.SimL1Emulator_cff')
process.load('Configuration.StandardSequences.DigiToRaw_cff')
process.load('HLTrigger.Configuration.HLT_HIon_cff')
process.load('Configuration.StandardSequences.RawToDigi_cff')
process.load('Configuration.StandardSequences.L1Reco_cff')
process.load('Configuration.StandardSequences.ReconstructionHeavyIons_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(4)
)

process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

# Input source
process.source = cms.Source("PoolSource",
    secondaryFileNames = cms.untracked.vstring(),
    fileNames = cms.untracked.vstring('/store/himc/HiFall13/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM/STARTHI53_V28-v2/00000/00699AE5-5A5E-E311-83B4-008CFA007B98.root', 
        '/store/himc/HiFall13/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM/STARTHI53_V28-v2/00000/02B3F103-995E-E311-BD92-003048C9AC48.root', 
        '/store/himc/HiFall13/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM/STARTHI53_V28-v2/00000/02F3428A-B35E-E311-8A73-848F69FD4553.root', 
        '/store/himc/HiFall13/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM/STARTHI53_V28-v2/00000/0444BD90-995E-E311-924E-02163E00B749.root', 
        '/store/himc/HiFall13/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM/STARTHI53_V28-v2/00000/0486ABC5-985E-E311-8E54-02163E008CDD.root', 
        '/store/himc/HiFall13/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM/STARTHI53_V28-v2/00000/0806398C-985E-E311-BF1C-003048FEAEF0.root', 
        '/store/himc/HiFall13/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM/STARTHI53_V28-v2/00000/0889A20B-C35E-E311-9A53-008CFA001D7C.root', 
        '/store/himc/HiFall13/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM/STARTHI53_V28-v2/00000/0A9BD954-985E-E311-AF53-003048FEB9F6.root', 
        '/store/himc/HiFall13/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM/STARTHI53_V28-v2/00000/0E02A540-FF5C-E311-9950-848F69FD298E.root', 
        '/store/himc/HiFall13/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM/STARTHI53_V28-v2/00000/0E142734-995E-E311-8698-02163E00B50F.root')
)


# Production Info
process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.381.2.28 $'),
    annotation = cms.untracked.string('step1 nevts:3'),
    name = cms.untracked.string('PyReleaseValidation')
)

# Output definition

#process.RECODEBUGoutput = cms.OutputModule("PoolOutputModule",
#    splitLevel = cms.untracked.int32(0),
#    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
#    outputCommands = process.RECODEBUGEventContent.outputCommands,
#    fileName = cms.untracked.string('file:step1.root'),
#    SelectEvents = cms.untracked.PSet(SelectEvents = cms.vstring('filter_step')),
#    dataset = cms.untracked.PSet(
#        filterName = cms.untracked.string(''),
#        dataTier = cms.untracked.string('GEN-SIM-RECO')
#    )
#)

# Additional output definition
#process.RECODEBUGoutput.outputCommands += ['keep *_hiLowPtPixelTracks_*_*']
#process.RECODEBUGoutput.outputCommands += ['keep *_tpRecoAssocHiLowPtPixelTracks_*_*']

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'STARTHI53_LV1::All', '')

# Impact Parameter Filtering
process.load('Appeltel.ImpactParameterFilter.ImpactParameterFilter_cfi')
process.ipf = process.impactParameterFilter.clone(
  bMin = -1.0,
  bMax = 4.0
#  bMin = 11.0,
#  bMax = 20.0
)

# Track Association
process.load("SimTracker.TrackAssociation.trackingParticleRecoTrackAsssociation_cfi")

process.tpRecoAssocHiLowPtPixelTracks = process.trackingParticleRecoTrackAsssociation.clone()
process.tpRecoAssocHiLowPtPixelTracks.label_tr = cms.InputTag("hiGeneralAndPixelTracks")
#process.tpRecoAssocHiLowPtPixelTracks.associator = cms.string('TrackAssociatorByHits')
#process.tpRecoAssocHiLowPtPixelTracks.associator = cms.string('TrackAssociatorByChi2')
process.tpRecoAssocHiLowPtPixelTracks.associator = cms.string('quickTrackAssociatorByHits')

process.tpRecoAssocHiGeneralTracks = process.trackingParticleRecoTrackAsssociation.clone()
process.tpRecoAssocHiGeneralTracks.label_tr = cms.InputTag("hiGeneralTracks")
#process.tpRecoAssocHiGeneralTracks.associator = cms.string('TrackAssociatorByChi2')

#process.load("SimTracker.TrackAssociation.TrackAssociatorByHits_cfi")
#process.TrackAssociatorByHits.SimToRecoDenominator = cms.string('reco')
#process.load("SimTracker.TrackAssociation.TrackAssociatorByChi2_cfi")
#process.TrackAssociatorByChi2ESProducer.chi2cut = cms.double(100.0)
process.load("SimTracker.TrackAssociation.quickTrackAssociatorByHits_cfi")
process.quickTrackAssociatorByHits.SimToRecoDenominator = cms.string('reco')

# Centrality
from CommonFunctions_cff import *
overrideCentrality(process)
process.HeavyIonGlobalParameters = cms.PSet(
    centralityVariable = cms.string("HFtowers"),
    nonDefaultGlauberModel = cms.string("Hydjet_Drum"),
    centralitySrc = cms.InputTag("hiCentrality")
)

# Analysis

etabins = []
eta = -2.5
for i in range(0,51):
    eta  = -2.5 + i*0.1
    etabins.append(eta)

process.load('Appeltel.RpPbAnalysis.RpPbTrackingCorrections_cfi')
process.trkCorr_merged = process.pPbTrkCorr.clone(
    trackSrc = cms.InputTag("hiGeneralAndPixelTracks"),
    vertexSrc = cms.InputTag("hiSelectedVertex"),
    tpEffSrc = cms.InputTag('mergedtruth','MergedTrackTruth'),
    tpFakSrc = cms.InputTag('mergedtruth','MergedTrackTruth'),
    associatorMap = cms.InputTag('tpRecoAssocHiLowPtPixelTracks'),
    qualityString = cms.string("highPurity"),
    dxyErrMax = cms.double(999.0),
    dzErrMax = cms.double(999.0),
    ptErrMax = cms.double(999.0),
    occByPhi =  cms.bool(False),
    occByCentrality = cms.bool(True),
#    occBins = cms.vdouble(-3.2, -3.0, -2.8, -2.6, -2.4, -2.2, -2.0, -1.8, 
#                          -1.6, -1.4, -1.2, -1.0, -0.8, -0.6, -0.4, -0.2, 0.0, 
#                          0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0, 
#                          2.2, 2.4, 2.6, 2.8, 3.0, 3.2),
    occBins = cms.vdouble(0,20,40,60,80,100,200),
    etaBins = cms.vdouble(-0.8,-0.48,-0.16,0.16,0.48,0.8),
#    etaBins = cms.vdouble( 
#        -2.4, -2.2, -2.0, -1.8, -1.6, -1.4, 
#        -1.2, -1.0, -0.8, -0.6, -0.4, -0.2, 0.0,
#        0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 
#        1.6, 1.8, 2.0, 2.2,  2.4
#    ),
#    ptBins = cms.vdouble(
#        0.0, 0.05, 0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45,
#        0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95,
#        1.0, 1.05, 1.1, 1.15, 1.2,
#        
#        1.25, 1.3, 1.35, 1.4, 1.45, 1.5, 1.55,
#        1.6, 1.65, 1.7, 1.75, 1.8, 1.85, 1.9, 1.95,
#       2.0, 2.05,
#        2.1, 2.15, 2.2, 2.25, 2.3, 2.35, 2.4, 2.45, 
#       2.5, 2.6, 2.7, 2.8, 2.9, 
#        3.0, 3.2, 3.4, 3.6, 3.8, 4.0, 4.5, 5.0, 7.5, 10.0, 12.0, 15.0,
#        20.0, 25.0, 30.0, 45.0, 60.0, 90.0, 120.0, 
#        180.0, 300.0, 500.0
#    ),
    ptBins = cms.vdouble( 0.2,0.3,0.4,0.5,0.6,0.8,1.0,1.2,
                      1.4,1.6,1.8,2.0,2.2,
                      2.4,2.6,2.8,3.0,3.5,
                      4.0,4.5,5.0,6.0,7.0,
                      8.0,9.0,10.0,12,14,
                      16,18,20 ),
    fillTrkPerfHistos = cms.bool(False),
    fillTrkPerfHistosRF = cms.bool(False)
)

process.trkCorr_general = process.trkCorr_merged.clone(
    trackSrc = cms.InputTag("hiGeneralTracks"),
    associatorMap = cms.InputTag('tpRecoAssocHiGeneralTracks')
)
# TFile Output
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('trackCorrections.root')
)

# Path and EndPath definitions
process.filter_step = cms.Path(process.ipf)
process.digitisation_step = cms.Path(process.pdigi)
process.L1simulation_step = cms.Path(process.SimL1Emulator)
process.digi2raw_step = cms.Path(process.DigiToRaw)
process.raw2digi_step = cms.Path(process.RawToDigi)
process.L1Reco_step = cms.Path(process.L1Reco)
process.reconstruction_step = cms.Path(process.reconstructionHeavyIons)
process.pixelTracking_step = cms.Path(process.hiConformalPixelTracks*process.hiPixelOnlyStepSelector*process.hiHighPtStepSelector*process.hiGeneralAndPixelTracks)
process.association_step = cms.Path(process.tpRecoAssocHiLowPtPixelTracks*process.tpRecoAssocHiGeneralTracks)
process.ana_step = cms.Path(process.trkCorr_merged*process.trkCorr_general)
#process.endjob_step = cms.EndPath(process.endOfProcess)
#process.RECODEBUGoutput_step = cms.EndPath(process.RECODEBUGoutput)

# Schedule definition
#process.schedule = cms.Schedule(process.filter_step,process.digitisation_step,process.L1simulation_step,process.digi2raw_step)
#process.schedule.extend(process.HLTSchedule)
#process.schedule.extend([process.raw2digi_step,process.L1Reco_step,process.reconstruction_step,process.pixelTracking_step,process.association_step,process.endjob_step,process.RECODEBUGoutput_step])

process.schedule = cms.Schedule(process.filter_step,process.digitisation_step,process.L1simulation_step,process.digi2raw_step)
#process.schedule.extend(process.HLTSchedule)
#process.schedule.extend([process.raw2digi_step,process.reconstruction_step,process.pixelTracking_step,process.association_step,process.ana_step,process.endjob_step,process.RECODEBUGoutput_step])
process.schedule.extend([process.raw2digi_step,process.reconstruction_step,process.pixelTracking_step,process.association_step,process.ana_step])

# customisation of the process.

# Automatic addition of the customisation function from HLTrigger.Configuration.customizeHLTforMC
from HLTrigger.Configuration.customizeHLTforMC import customizeHLTforMC 

#call to customisation function customizeHLTforMC imported from HLTrigger.Configuration.customizeHLTforMC
process = customizeHLTforMC(process)

# End of customisation functions
