# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: Configuration/GenProduction/python/HI/2015/AMPT_PbPb_5020GeV_MinimumBias_stringMelting_cfi.py --mc --eventcontent RAWSIM --customise SLHCUpgradeSimulations/Configuration/postLS1Customs.customisePostLS1_HI,Configuration/DataProcessing/Utils.addMonitoring --datatier GEN-SIM --conditions 75X_mcRun2_HeavyIon_v1 --beamspot NominalHICollision2015 --step GEN,SIM --scenario HeavyIons --no_exec -n 5
import FWCore.ParameterSet.Config as cms

process = cms.Process('SIM')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContentHeavyIons_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.Geometry.GeometrySimDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.Generator_cff')
process.load('IOMC.EventVertexGenerators.VtxSmearedNominalHICollision2015_cfi')
process.load('Configuration.StandardSequences.GeneratorHI_cff')
process.load('GeneratorInterface.Core.genFilterSummary_cff')
process.load('Configuration.StandardSequences.SimIdeal_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(5)
)

# Input source
process.source = cms.Source("EmptySource")

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('AMPT PbPb 5020 GeV Minimum Bias'),
    name = cms.untracked.string('$Source: /cvs_server/repositories/CMSSW/CMSSW/GeneratorInterface/AMPTInterface/python/amptDefault_cfi.py,v $'),
    version = cms.untracked.string('$Revision: 1.1$')
)

# Output definition

process.RAWSIMoutput = cms.OutputModule("PoolOutputModule",
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('generation_step')
    ),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('GEN-SIM'),
        filterName = cms.untracked.string('')
    ),
    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    fileName = cms.untracked.string('AMPT_PbPb_5020GeV_MinimumBias_stringMelting_cfi_py_GEN_SIM.root'),
    outputCommands = process.RAWSIMEventContent.outputCommands,
    splitLevel = cms.untracked.int32(0)
)

# Additional output definition

# Other statements
process.genstepfilter.triggerConditions=cms.vstring("generation_step")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '75X_mcRun2_HeavyIon_v1', '')

process.generator = cms.EDFilter("AMPTGeneratorFilter",
    alpha = cms.double(0.47140452),
    amptmode = cms.int32(4),
    bMax = cms.double(30),
    bMin = cms.double(0),
    comEnergy = cms.double(5020.0),
    deuteronfactor = cms.int32(1),
    deuteronmode = cms.int32(0),
    deuteronxsec = cms.int32(1),
    diquarkembedding = cms.int32(0),
    diquarkpx = cms.double(7.0),
    diquarkpy = cms.double(0.0),
    diquarkx = cms.double(0.0),
    diquarky = cms.double(0.0),
    doInitialAndFinalRadiation = cms.int32(3),
    dpcoal = cms.double(1000000.0),
    drcoal = cms.double(1000000.0),
    dt = cms.double(0.2),
    firstEvent = cms.untracked.uint32(1),
    firstRun = cms.untracked.uint32(1),
    frame = cms.string('CMS'),
    iap = cms.int32(208),
    iat = cms.int32(208),
    izp = cms.int32(82),
    izpc = cms.int32(0),
    izt = cms.int32(82),
    ks0decay = cms.bool(False),
    ktkick = cms.int32(1),
    maxmiss = cms.int32(1000),
    minijetpt = cms.double(-7.0),
    mu = cms.double(3.2264),
    ntmax = cms.int32(150),
    phidecay = cms.bool(True),
    popcornmode = cms.bool(True),
    popcornpar = cms.double(1.0),
    proj = cms.string('A'),
    pthard = cms.double(2.0),
    quenchingmode = cms.bool(False),
    quenchingpar = cms.double(2.0),
    rotateEventPlane = cms.bool(True),
    shadowingmode = cms.bool(True),
    stringFragA = cms.double(2.2),
    stringFragB = cms.double(0.5),
    targ = cms.string('A')
)


# Path and EndPath definitions
process.generation_step = cms.Path(process.pgen)
process.simulation_step = cms.Path(process.psim)
process.genfiltersummary_step = cms.EndPath(process.genFilterSummary)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.RAWSIMoutput_step = cms.EndPath(process.RAWSIMoutput)

# Schedule definition
process.schedule = cms.Schedule(process.generation_step,process.genfiltersummary_step,process.simulation_step,process.endjob_step,process.RAWSIMoutput_step)
# filter all path with the production filter sequence
for path in process.paths:
	getattr(process,path)._seq = process.generator * getattr(process,path)._seq 

# customisation of the process.

# Automatic addition of the customisation function from SLHCUpgradeSimulations.Configuration.postLS1Customs
from SLHCUpgradeSimulations.Configuration.postLS1Customs import customisePostLS1_HI 

#call to customisation function customisePostLS1_HI imported from SLHCUpgradeSimulations.Configuration.postLS1Customs
process = customisePostLS1_HI(process)

# Automatic addition of the customisation function from Configuration.DataProcessing.Utils
from Configuration.DataProcessing.Utils import addMonitoring 

#call to customisation function addMonitoring imported from Configuration.DataProcessing.Utils
process = addMonitoring(process)

# End of customisation functions

