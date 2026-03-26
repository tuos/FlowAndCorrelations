import FWCore.ParameterSet.Config as cms
from Configuration.Generator.Pythia8CommonSettings_cfi import *
from Configuration.Generator.MCTunes2017.PythiaCP5Settings_cfi import *

generator = cms.EDFilter("Pythia8ConcurrentGeneratorFilter",
    maxEventsToPrint = cms.untracked.int32(1),
    pythiaPylistVerbosity = cms.untracked.int32(1),
    filterEfficiency = cms.untracked.double(1.0),
    pythiaHepMCVerbosity = cms.untracked.bool(False),
    comEnergy = cms.double(5362.),
    HeavyIonInitialState = cms.PSet( ),
    PythiaParameters = cms.PSet(
        pythia8CommonSettingsBlock,
        pythia8CP5SettingsBlock,
        processParameters = cms.vstring(
            'Beams:idA = 1000080160', # Oxygen
            'Beams:idB = 1000080160', # Oxygen
            'Beams:frameType = 1',
            'Beams:eCM = 5362.',
            
            # --- Switch from MinBias to Hard QCD ---
#            'SoftQCD:inelastic = off',           # Turn off MinBias
            'HardQCD:all = on',                  # Turn on Hard Scattering
            'PhaseSpace:pTHatMin = 15.',         # Minimum pt hat
#            'PhaseSpace:pTHatMax = 30.',         # Optional: Upper bound for binning
            
            # --- HI Angantyr setup ---
            'HeavyIon:mode = 1', 
            'HeavyIon:SigFitNGen = 0',
            'HeavyIon:SigFitDefPar = 2.18,17.55,0.32', 
            'Angantyr:NucleusModelA = 3',
            'Angantyr:NucleusModelB = 3',
        ),
        parameterSets = cms.vstring(
            'pythia8CommonSettings',
            'pythia8CP5Settings',
            'processParameters'
        )
    )
)
