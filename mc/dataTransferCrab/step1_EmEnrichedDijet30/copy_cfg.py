import FWCore.ParameterSet.Config as cms

# Give the process a name
process = cms.Process("SaveEvent")

# Tell the process which files to use as the source
process.source = cms.Source ("PoolSource",
          fileNames = cms.untracked.vstring (
'/store/group/phys_heavyions/bharikri/Run3MC_PbPb/GENSIM/Pythia8_EmEnrichedDijet30_HydjetEmbedded_TuneCP5_13_0_12/Pythia8_EmEnrichedDijet30_HydjetEmbedded_TuneCP5_13_0_12/2023_Aug_18_step1_GENSIM_Pythia8_Embedded_EmEnrichedDijet30_TuneCP5/230818_203642/0000/step1_1.root'
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

