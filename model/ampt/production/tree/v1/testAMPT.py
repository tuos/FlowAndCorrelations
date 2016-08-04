import FWCore.ParameterSet.Config as cms

process = cms.Process("ANA")

process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
process.load("Configuration.StandardSequences.Services_cff")
process.load("GeneratorInterface.HydjetInterface.hydjetDefault_cfi")

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1)
                                       )

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

#process.SimpleMemoryCheck = cms.Service('SimpleMemoryCheck',
#                                        ignoreTotal=cms.untracked.int32(0),
#                                        oncePerEventMode = cms.untracked.bool(False)
#                                        )

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(),
                            duplicateCheckMode = cms.untracked.string("noDuplicateCheck")
)
import FWCore.Utilities.FileUtils as FileUtils
mylist = FileUtils.loadListFromFile ('filelist.txt')
for fname in mylist:
 process.source.fileNames.append('file:%s' % (fname))
 

process.ana = cms.EDAnalyzer('AMPTAnalyzer'
                             )

process.TFileService = cms.Service('TFileService',
                                   fileName = cms.string('outtreefile_ampt.root')
                                   )
process.p = cms.Path(process.ana)




