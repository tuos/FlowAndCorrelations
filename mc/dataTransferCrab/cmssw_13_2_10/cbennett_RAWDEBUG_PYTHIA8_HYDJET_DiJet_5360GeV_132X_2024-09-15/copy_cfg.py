import FWCore.ParameterSet.Config as cms

# Give the process a name
process = cms.Process("SaveEvent")

# Tell the process which files to use as the source
process.source = cms.Source ("PoolSource",
          fileNames = cms.untracked.vstring (
'/store/group/phys_heavyions/cbennett/crabSubmit_RAWDEBUG_PYTHIA8_HYDJET_DiJet_5360GeV_132X_2024-09-15/PYTHIA8_HYDJET_DiJet_5360GeV_130X/PYTHIA8_HYDJET_DiJet_5360GeV_RAWDEBUG_132X_2024-09-15/240915_165428/0000/PYTHIA8_HYDJET_DiJet_5360GeV_RAWDEBUG_1.root'
)
)

# tell the process to only run over 100 events (-1 would mean run over
#  everything
process.maxEvents = cms.untracked.PSet(
            input = cms.untracked.int32 (-1)

)

# Tell the process what filename to use to save the output
process.Out = cms.OutputModule("PoolOutputModule",
         fileName = cms.untracked.string ("PYTHIA8_HYDJET_DiJet_5360GeV_RAWDEBUG.root")
)

# make sure everything is hooked up
process.end = cms.EndPath(process.Out)

