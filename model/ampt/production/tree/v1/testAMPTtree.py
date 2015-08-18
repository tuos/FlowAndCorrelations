import FWCore.ParameterSet.Config as cms

process = cms.Process("ANA")

process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
process.load("Configuration.StandardSequences.Services_cff")
process.load("GeneratorInterface.HydjetInterface.hydjetDefault_cfi")

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(200)
                                       )

process.load("FWCore.MessageService.MessageLogger_cfi")
#process.MessageLogger.cerr.FwkReport.reportEvery = 1000

#process.SimpleMemoryCheck = cms.Service('SimpleMemoryCheck',
#                                        ignoreTotal=cms.untracked.int32(0),
#                                        oncePerEventMode = cms.untracked.bool(False)
#                                        )

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
'/store/user/tuos/MC_AMPT/PbPb5TeV/StringMelting/v3/July09/run0pbPbv3x10more/energy2760GeVA/MinBias/CRAB3_AMPTstring_July2015_generation_run0pbPb2760GeVv3x10moreA/150709_175916/0000/ampt_StringMelting_pbPb2760GeV_GEN_1.root'
),
                            duplicateCheckMode = cms.untracked.string("noDuplicateCheck")
)
#import FWCore.Utilities.FileUtils as FileUtils
#mylist = FileUtils.loadListFromFile ('filelist.txt')
#for fname in mylist:
# process.source.fileNames.append('file:%s' % (fname))
 

process.ana = cms.EDAnalyzer('AMPTAnalyzer'
                             )

process.TFileService = cms.Service('TFileService',
                                   fileName = cms.string('outtreefile_ampt.root')
                                   )
process.p = cms.Path(process.ana)




