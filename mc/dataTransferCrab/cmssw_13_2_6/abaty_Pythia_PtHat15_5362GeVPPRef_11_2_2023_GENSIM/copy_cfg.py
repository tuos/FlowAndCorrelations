import FWCore.ParameterSet.Config as cms

# Give the process a name
process = cms.Process("SaveEvent")

# Tell the process which files to use as the source
process.source = cms.Source ("PoolSource",
          fileNames = cms.untracked.vstring (
'/store/group/phys_heavyions/abaty/2023_ppRef_JetCalibrations/Pythia_PtHat15_5362GeVPPRef_11_2_2023_GENSIM/crab_PythiaProductionPtHat15/231103_003111/0000/step1_1.root'
)
)

# tell the process to only run over 100 events (-1 would mean run over
#  everything
process.maxEvents = cms.untracked.PSet(
            input = cms.untracked.int32 (-1)

)

# Tell the process what filename to use to save the output
process.Out = cms.OutputModule("PoolOutputModule",
         fileName = cms.untracked.string ("step1.root")
)

# make sure everything is hooked up
process.end = cms.EndPath(process.Out)

