# Auto generated configuration file
# using: 
# Revision: 1.168 
# Source: /cvs_server/repositories/CMSSW/CMSSW/Configuration/PyReleaseValidation/python/ConfigBuilder.py,v 
# with command line options: GeneratorInterface/AMPTInterface/amptDefault_cfi.py -s GEN --conditions auto:mc --datatier GEN --eventcontent RAWSIM -n 1 --scenario HeavyIons --no_exec
import FWCore.ParameterSet.Config as cms

process = cms.Process('GEN')

# import of standard configurations
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.Geometry.GeometrySimDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.Generator_cff')
process.load('IOMC.EventVertexGenerators.VtxSmearedRealistic8TeVCollision_cfi')
process.load('GeneratorInterface.Core.genFilterSummary_cff')
process.load('Configuration.StandardSequences.SimIdeal_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContentHeavyIons_cff')

process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.2 $'),
    annotation = cms.untracked.string('AMPT generator'),
    name = cms.untracked.string('$Source: /cvs_server/repositories/CMSSW/CMSSW/GeneratorInterface/AMPTInterface/python/amptDefault_cfi.py,v $')
)
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(10)
)
process.options = cms.untracked.PSet(

)
# Input source
process.source = cms.Source("EmptySource")

# Output definition
process.output = cms.OutputModule("PoolOutputModule",
    splitLevel = cms.untracked.int32(0),
    outputCommands = process.RAWSIMEventContent.outputCommands,
    fileName = cms.untracked.string('ampt_StringMelting_pbPb2760GeV_GEN.root'),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('GEN'),
        filterName = cms.untracked.string('')
    ),
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('generation_step')
    )
)

# Additional output definition

# Other statements
process.GlobalTag.globaltag = 'STARTHI71_V2::All'
process.generator = cms.EDFilter("AMPTGeneratorFilter",
                                 comEnergy = cms.double(2760.0),
                                 frame = cms.string('CMS'),
                                 proj = cms.string('A'),
                                 targ = cms.string('A'),
                                 iap = cms.int32(208),
                                 izp = cms.int32(82),
                                 iat = cms.int32(208),
                                 izt = cms.int32(82),
                                 bMin = cms.double(0),
                                 bMax = cms.double(18),
                                 amptmode = cms.int32(4),
                                 ntmax = cms.int32(150),
                                 dt = cms.double(0.2),
                                 stringFragA = cms.double(0.5),
                                 stringFragB = cms.double(0.9),
                                 popcornmode = cms.bool(True),
                                 popcornpar = cms.double(1.0),
                                 shadowingmode = cms.bool(True),
                                 quenchingmode = cms.bool(False),
                                 quenchingpar = cms.double(1.0),
                                 pthard = cms.double(2.0),
                                 mu = cms.double(2.2814),
                                 izpc = cms.int32(0),
                                 alpha = cms.double(0.33333),
                                 dpcoal = cms.double(1000000.0),
                                 drcoal = cms.double(1000000.0),
                                 ks0decay = cms.bool(False),
                                 phidecay = cms.bool(True), ##no pi0 decay flag
                                 deuteronmode = cms.int32(0),
                                 deuteronfactor = cms.int32(1),
                                 deuteronxsec = cms.int32(1),
                                 minijetpt = cms.double(-7.0),
                                 maxmiss = cms.int32(1000),
                                 doInitialAndFinalRadiation = cms.int32(3),
                                 ktkick = cms.int32(1),
                                 diquarkembedding = cms.int32(0),
                                 diquarkpx = cms.double(7.0),
                                 diquarkpy = cms.double(0.0),
                                 diquarkx = cms.double(0.0),
                                 diquarky = cms.double(0.0),
                                 rotateEventPlane = cms.bool(True),
                                 firstRun = cms.untracked.uint32(1),
                                 firstEvent = cms.untracked.uint32(1)
                                 )

# Path and EndPath definitions
#process.generation_step = cms.Path(process.pgen_hi)
process.generation_step = cms.Path(process.generator)
process.endjob_step = cms.Path(process.endOfProcess)
process.out_step = cms.EndPath(process.output)

# Schedule definition
process.schedule = cms.Schedule(process.generation_step,process.endjob_step,process.out_step)


from IOMC.RandomEngine.RandomServiceHelper import RandomNumberServiceHelper
randSvc = RandomNumberServiceHelper(process.RandomNumberGeneratorService)
randSvc.populate()

# special treatment in case of production filter sequence  
for path in process.paths: 
    getattr(process,path)._seq = process.generator*getattr(process,path)._seq
