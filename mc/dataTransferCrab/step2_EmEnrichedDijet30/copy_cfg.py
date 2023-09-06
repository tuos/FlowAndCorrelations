import FWCore.ParameterSet.Config as cms

# Give the process a name
process = cms.Process("SaveEvent")

# Tell the process which files to use as the source
process.source = cms.Source ("PoolSource",
          fileNames = cms.untracked.vstring (
'/store/group/phys_heavyions/bharikri/Run3MC_PbPb/DIGI2RAW/Pythia8_EmEnrichedDijet30_HydjetEmbedded_TuneCP5_13_2_0_DIGI2RAW_BPix_masked/Pythia8_EmEnrichedDijet30_HydjetEmbedded_TuneCP5_13_0_12/2023_Aug_18_step2_DIGI2RAW_Pythia8_Embedded_EmEnrichedDijet30_TuneCP5_BPix_masked/230819_090839/0000/step2_1.root'
)
)

# tell the process to only run over 100 events (-1 would mean run over
#  everything
process.maxEvents = cms.untracked.PSet(
            input = cms.untracked.int32 (-1)

)

# Tell the process what filename to use to save the output
process.Out = cms.OutputModule("PoolOutputModule",
         fileName = cms.untracked.string ("step2.root")
)

# make sure everything is hooked up
process.end = cms.EndPath(process.Out)

