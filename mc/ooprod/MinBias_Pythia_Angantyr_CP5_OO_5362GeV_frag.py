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
            'Beams:idA = 1000080160',
            'Beams:idB = 1000080160',
            'Beams:frameType = 1',
            'Beams:eCM = 5362.',
            
            # MinBias events
            'SoftQCD:inelastic = on',
            
            # HI Angatyr setup https://pythia.org/latest-manual/HeavyIons.html
            'HeavyIon:mode = 1',
            # HeavyIon fitting of SubCollisionModel to cross sections
            'HeavyIon:SigFitNGen = 0',
            'HeavyIon:SigFitDefPar = 2.18,17.55,0.32',
            
            # Harmonic Oscillator Shell model (light ion geometry)
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
