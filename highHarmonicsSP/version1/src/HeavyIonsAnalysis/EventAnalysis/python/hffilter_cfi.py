import FWCore.ParameterSet.Config as cms

phfCoincFilter2Th4  = cms.EDFilter('HFFilter',
   HFfilters      = cms.InputTag("hiHFfilters","hiHFfilters","PAT"),
   threshold      = cms.int32(4),
   minnumtowers  = cms.int32(2)
)

phfCoincFilter1Th3  = cms.EDFilter('HFFilter',
   HFfilters      = cms.InputTag("hiHFfilters","hiHFfilters","PAT"),
   threshold      = cms.int32(3),
   minnumtowers  = cms.int32(1)
)

