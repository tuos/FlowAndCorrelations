# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: Configuration/GenProduction/python/HIN-HINXeXeFall17GS-00005-fragment.py --mc --eventcontent RAWSIM --datatier GEN-SIM --conditions 93X_mc2017_realistic_v3 --beamspot RealisticXeXeCollision2017 --step GEN,SIM --nThreads 1 --scenario HeavyIons --geometry DB:Extended --era Run2_2017
import FWCore.ParameterSet.Config as cms

from Configuration.StandardSequences.Eras import eras

process = cms.Process('SIM',eras.Run2_2017)

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContentHeavyIons_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.GeometrySimDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.Generator_cff')
process.load('IOMC.EventVertexGenerators.VtxSmearedRealisticXeXeCollision2017_cfi')
process.load('Configuration.StandardSequences.GeneratorHI_cff')
process.load('GeneratorInterface.Core.genFilterSummary_cff')
process.load('Configuration.StandardSequences.SimIdeal_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100)
)

#process.Timing = cms.Service("Timing",
#  summaryOnly = cms.untracked.bool(False),
#  useJobReport = cms.untracked.bool(True)
#)

# Input source
process.source = cms.Source("EmptySource")

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('Configuration/GenProduction/python/HIN-HINXeXeFall17GS-00005-fragment.py nevts:1'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)

# Output definition

process.RAWSIMoutput = cms.OutputModule("PoolOutputModule",
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('generation_step')
    ),
    compressionAlgorithm = cms.untracked.string('LZMA'),
    compressionLevel = cms.untracked.int32(9),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('GEN-SIM'),
        filterName = cms.untracked.string('')
    ),
    eventAutoFlushCompressedSize = cms.untracked.int32(20971520),
    fileName = cms.untracked.string('HIN-HINXeXeFall17GS-00005-fragment_py_GEN_SIM.root'),
    outputCommands = process.RAWSIMEventContent.outputCommands,
    splitLevel = cms.untracked.int32(0)
)

# Additional output definition

# Other statements
process.XMLFromDBSource.label = cms.string("Extended")
process.genstepfilter.triggerConditions=cms.vstring("generation_step")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '93X_mc2017_realistic_v3', '')

process.generator = cms.EDFilter("HydjetGeneratorFilter",
    PythiaParameters = cms.PSet(
        hydjetPythiaDefault = cms.vstring('MSEL=0   ! user processes', 
            'CKIN(3)=8.15', 
            'MSTP(81)=1'),
        myParameters = cms.vstring('MDCY(310,1)=0'),
        parameterSets = cms.vstring('pythiaUESettings', 
            'hydjetPythiaDefault', 
            'myParameters', 
            'pythiaJets', 
            'pythiaPromptPhotons', 
            'pythiaZjets', 
            'pythiaBottomoniumNRQCD', 
            'pythiaCharmoniumNRQCD', 
            'pythiaQuarkoniaSettings', 
            'pythiaWeakBosons'),
        pythiaBottomoniumNRQCD = cms.vstring('MSUB(461) = 1', 
            'MSUB(462) = 1', 
            'MSUB(463) = 1', 
            'MSUB(464) = 1', 
            'MSUB(465) = 1', 
            'MSUB(466) = 1', 
            'MSUB(467) = 1', 
            'MSUB(468) = 1', 
            'MSUB(469) = 1', 
            'MSUB(470) = 1', 
            'MSUB(471) = 1', 
            'MSUB(472) = 1', 
            'MSUB(473) = 1', 
            'MSUB(474) = 1', 
            'MSUB(475) = 1', 
            'MSUB(476) = 1', 
            'MSUB(477) = 1', 
            'MSUB(478) = 1', 
            'MSUB(479) = 1'),
        pythiaCharmoniumNRQCD = cms.vstring('MSUB(421) = 1', 
            'MSUB(422) = 1', 
            'MSUB(423) = 1', 
            'MSUB(424) = 1', 
            'MSUB(425) = 1', 
            'MSUB(426) = 1', 
            'MSUB(427) = 1', 
            'MSUB(428) = 1', 
            'MSUB(429) = 1', 
            'MSUB(430) = 1', 
            'MSUB(431) = 1', 
            'MSUB(432) = 1', 
            'MSUB(433) = 1', 
            'MSUB(434) = 1', 
            'MSUB(435) = 1', 
            'MSUB(436) = 1', 
            'MSUB(437) = 1', 
            'MSUB(438) = 1', 
            'MSUB(439) = 1'),
        pythiaJets = cms.vstring('MSUB(11)=1', 
            'MSUB(12)=1', 
            'MSUB(13)=1', 
            'MSUB(28)=1', 
            'MSUB(53)=1', 
            'MSUB(68)=1'),
        pythiaPromptPhotons = cms.vstring('MSUB(14)=1', 
            'MSUB(18)=1', 
            'MSUB(29)=1', 
            'MSUB(114)=1', 
            'MSUB(115)=1'),
        pythiaQuarkoniaSettings = cms.vstring('PARP(141)=1.16', 
            'PARP(142)=0.0119', 
            'PARP(143)=0.01', 
            'PARP(144)=0.01', 
            'PARP(145)=0.05', 
            'PARP(146)=9.28', 
            'PARP(147)=0.15', 
            'PARP(148)=0.02', 
            'PARP(149)=0.02', 
            'PARP(150)=0.085', 
            'PARJ(13)=0.60', 
            'PARJ(14)=0.162', 
            'PARJ(15)=0.018', 
            'PARJ(16)=0.054', 
            'MSTP(145)=0', 
            'MSTP(146)=0', 
            'MSTP(147)=0', 
            'MSTP(148)=1', 
            'MSTP(149)=1', 
            'BRAT(861)=0.202', 
            'BRAT(862)=0.798', 
            'BRAT(1501)=0.013', 
            'BRAT(1502)=0.987', 
            'BRAT(1555)=0.356', 
            'BRAT(1556)=0.644'),
        pythiaUESettings = cms.vstring('MSTJ(11)=3     ! Choice of the fragmentation function', 
            'MSTJ(22)=2     ! Decay those unstable particles', 
            'PARJ(71)=10 .  ! for which ctau  10 mm', 
            'MSTP(2)=1      ! which order running alphaS', 
            'MSTP(33)=0     ! no K factors in hard cross sections', 
            'MSTP(51)=10042 ! structure function chosen (external PDF CTEQ6L1)', 
            'MSTP(52)=2     ! work with LHAPDF', 
            'MSTP(81)=1     ! multiple parton interactions 1 is Pythia default', 
            'MSTP(82)=4     ! Defines the multi-parton model', 
            'MSTU(21)=1     ! Check on possible errors during program execution', 
            'PARP(82)=1.8387   ! pt cutoff for multiparton interactions', 
            'PARP(89)=1960. ! sqrts for which PARP82 is set', 
            'PARP(83)=0.5   ! Multiple interactions: matter distrbn parameter', 
            'PARP(84)=0.4   ! Multiple interactions: matter distribution parameter', 
            'PARP(90)=0.16  ! Multiple interactions: rescaling power', 
            'PARP(67)=2.5    ! amount of initial-state radiation', 
            'PARP(85)=1.0  ! gluon prod. mechanism in MI', 
            'PARP(86)=1.0  ! gluon prod. mechanism in MI', 
            'PARP(62)=1.25   ! ', 
            'PARP(64)=0.2    ! ', 
            'MSTP(91)=1      !', 
            'PARP(91)=2.1   ! kt distribution', 
            'PARP(93)=15.0  ! '),
        pythiaWeakBosons = cms.vstring('MSUB(1)=1', 
            'MSUB(2)=1'),
        pythiaZjets = cms.vstring('MSUB(15)=1', 
            'MSUB(30)=1')
    ),
    aBeamTarget = cms.double(129.0),
    allowEmptyEvents = cms.bool(False),
    angularSpectrumSelector = cms.int32(1),
    bFixed = cms.double(0),
    bMax = cms.double(30),
    bMin = cms.double(0),
    cFlag = cms.int32(1),
    comEnergy = cms.double(5442.0),
    doCollisionalEnLoss = cms.bool(True),
    doRadiativeEnLoss = cms.bool(True),
    embeddingMode = cms.bool(False),
    fracSoftMultiplicity = cms.double(1.0),
    hadronFreezoutTemperature = cms.double(0.125),
    hydjetMode = cms.string('kHydroQJets'),
    maxLongitudinalRapidity = cms.double(2.3),
    maxTransverseRapidity = cms.double(1.15),
    nMultiplicity = cms.int32(9000),
    numQuarkFlavor = cms.int32(0),
    qgpInitialTemperature = cms.double(1.0),
    qgpNumQuarkFlavor = cms.int32(0),
    qgpProperTimeFormation = cms.double(0.1),
    rotateEventPlane = cms.bool(True),
    shadowingSwitch = cms.int32(1),
    sigmaInelNN = cms.double(70)
)


# Path and EndPath definitions
process.generation_step = cms.Path(process.pgen)
process.simulation_step = cms.Path(process.psim)
process.genfiltersummary_step = cms.EndPath(process.genFilterSummary)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.RAWSIMoutput_step = cms.EndPath(process.RAWSIMoutput)

# Schedule definition
process.schedule = cms.Schedule(process.generation_step,process.genfiltersummary_step,process.simulation_step,process.endjob_step,process.RAWSIMoutput_step)
from PhysicsTools.PatAlgos.tools.helpers import associatePatAlgosToolsTask
associatePatAlgosToolsTask(process)
# filter all path with the production filter sequence
for path in process.paths:
	getattr(process,path)._seq = process.generator * getattr(process,path)._seq 


from IOMC.RandomEngine.RandomServiceHelper import RandomNumberServiceHelper
randSvc = RandomNumberServiceHelper(process.RandomNumberGeneratorService)
randSvc.populate()

# Customisation from command line

# Add early deletion of temporary data products to reduce peak memory need
from Configuration.StandardSequences.earlyDeleteSettings_cff import customiseEarlyDelete
process = customiseEarlyDelete(process)
# End adding early deletion
