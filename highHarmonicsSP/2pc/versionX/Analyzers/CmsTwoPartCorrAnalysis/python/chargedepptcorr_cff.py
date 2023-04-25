import FWCore.ParameterSet.Config as cms

from Analyzers.CmsTwoPartCorrAnalysis.chargedepptcorr_cfi import *

#### Standard analysis for pixel Rereco PbPb 2015 ####

#### centrality 0-5% ####
CPDC05 = defaultCPDC.clone()
CPDC05.centmin = cms.untracked.int32(0)
CPDC05.centmax = cms.untracked.int32(5) ##5

#### centrality 0-5% ####                                                                                                 
CPDC020 = defaultCPDC.clone()
CPDC020.centmin = cms.untracked.int32(0)
CPDC020.centmax = cms.untracked.int32(20) ##

#### centrality 5-10% ####
CPDC510 = defaultCPDC.clone()
CPDC510.centmin = cms.untracked.int32(5)
CPDC510.centmax = cms.untracked.int32(10)
#### centrality 10-15% ####
CPDC1015 = defaultCPDC.clone()
CPDC1015.centmin = cms.untracked.int32(10)
CPDC1015.centmax = cms.untracked.int32(15)

CPDC010 = defaultCPDC.clone()
CPDC010.centmin = cms.untracked.int32(0)
CPDC010.centmax = cms.untracked.int32(10)

CPDC1030 = defaultCPDC.clone()
CPDC1030.centmin = cms.untracked.int32(10)
CPDC1030.centmax = cms.untracked.int32(30)

CPDC3050 = defaultCPDC.clone()
CPDC3050.centmin = cms.untracked.int32(30)
CPDC3050.centmax = cms.untracked.int32(50)

CPDC5080 = defaultCPDC.clone()
CPDC5080.centmin = cms.untracked.int32(50)
CPDC5080.centmax = cms.untracked.int32(80)

CPDC1020 = defaultCPDC.clone()
CPDC1020.centmin = cms.untracked.int32(10)
CPDC1020.centmax = cms.untracked.int32(20)

#### centrality 15-20% ####
CPDC1520 = defaultCPDC.clone()
CPDC1520.centmin = cms.untracked.int32(15)
CPDC1520.centmax = cms.untracked.int32(20)
#### centrality 20-25% ####
CPDC2025 = defaultCPDC.clone()
CPDC2025.centmin = cms.untracked.int32(20)
CPDC2025.centmax = cms.untracked.int32(25)
#### centrality 25-30% ####
CPDC2530 = defaultCPDC.clone()
CPDC2530.centmin = cms.untracked.int32(25)
CPDC2530.centmax = cms.untracked.int32(30)
#### centrality 30-35% ####

CPDC2030 = defaultCPDC.clone()
CPDC2030.centmin = cms.untracked.int32(20)
CPDC2030.centmax = cms.untracked.int32(30)

CPDC3035 = defaultCPDC.clone()
CPDC3035.centmin = cms.untracked.int32(30)
CPDC3035.centmax = cms.untracked.int32(35)
#### centrality 35-40% ####
CPDC3540 = defaultCPDC.clone()
CPDC3540.centmin = cms.untracked.int32(35)
CPDC3540.centmax = cms.untracked.int32(40)

CPDC3040 = defaultCPDC.clone()
CPDC3040.centmin = cms.untracked.int32(30)
CPDC3040.centmax = cms.untracked.int32(40)

#### centrality 40-45% ####
CPDC4045 = defaultCPDC.clone()
CPDC4045.centmin = cms.untracked.int32(40)
CPDC4045.centmax = cms.untracked.int32(45)
#### centrality 45-50% ####
CPDC4550 = defaultCPDC.clone()
CPDC4550.centmin = cms.untracked.int32(45)
CPDC4550.centmax = cms.untracked.int32(50)

CPDC4050 = defaultCPDC.clone()
CPDC4050.centmin = cms.untracked.int32(40)
CPDC4050.centmax = cms.untracked.int32(50)

#### centrality 50-55% ####
CPDC5055 = defaultCPDC.clone()
CPDC5055.centmin = cms.untracked.int32(50)
CPDC5055.centmax = cms.untracked.int32(55)
#### centrality 55-60% ####
CPDC5560 = defaultCPDC.clone()
CPDC5560.centmin = cms.untracked.int32(55)
CPDC5560.centmax = cms.untracked.int32(60)

CPDC5060 = defaultCPDC.clone()
CPDC5060.centmin = cms.untracked.int32(50)
CPDC5060.centmax = cms.untracked.int32(60)

#### centrality 60-65% ####
CPDC6065 = defaultCPDC.clone()
CPDC6065.centmin = cms.untracked.int32(60)
CPDC6065.centmax = cms.untracked.int32(65)
#### centrality 65-70% ####
CPDC6570 = defaultCPDC.clone()
CPDC6570.centmin = cms.untracked.int32(65)
CPDC6570.centmax = cms.untracked.int32(70)

CPDC6070 = defaultCPDC.clone()
CPDC6070.centmin = cms.untracked.int32(60)
CPDC6070.centmax = cms.untracked.int32(70)

CPDC70100 = defaultCPDC.clone()
CPDC70100.centmin = cms.untracked.int32(70)
CPDC70100.centmax = cms.untracked.int32(100)

#### centrality 70-75% ####
CPDC7075 = defaultCPDC.clone()
CPDC7075.centmin = cms.untracked.int32(70)
CPDC7075.centmax = cms.untracked.int32(75)
#### centrality 75-80% ####
CPDC7580 = defaultCPDC.clone()
CPDC7580.centmin = cms.untracked.int32(75)
CPDC7580.centmax = cms.untracked.int32(80)
#### centrality 80-85% ####
CPDC8085 = defaultCPDC.clone()
CPDC8085.centmin = cms.untracked.int32(80)
CPDC8085.centmax = cms.untracked.int32(85)
#### centrality 85-90% ####
CPDC8590 = defaultCPDC.clone()
CPDC8590.centmin = cms.untracked.int32(85)
CPDC8590.centmax = cms.untracked.int32(90)

CPDC7080 = defaultCPDC.clone()
CPDC7080.centmin = cms.untracked.int32(70)
CPDC7080.centmax = cms.untracked.int32(80)

CPDC6080 = defaultCPDC.clone()
CPDC6080.centmin = cms.untracked.int32(60)
CPDC6080.centmax = cms.untracked.int32(80)


CPDC0100 = defaultCPDC.clone()
CPDC0100.centmin = cms.untracked.int32(0)
CPDC0100.centmax = cms.untracked.int32(100)


CPDC02 = defaultCPDC.clone()
CPDC02.centmin = cms.untracked.int32(0)
CPDC02.centmax = cms.untracked.int32(2)

CPDC24 = defaultCPDC.clone()
CPDC24.centmin = cms.untracked.int32(2)
CPDC24.centmax = cms.untracked.int32(4)

CPDC46 = defaultCPDC.clone()
CPDC46.centmin = cms.untracked.int32(4)
CPDC46.centmax = cms.untracked.int32(6)

CPDC68 = defaultCPDC.clone()
CPDC68.centmin = cms.untracked.int32(6)
CPDC68.centmax = cms.untracked.int32(8)

CPDC810 = defaultCPDC.clone()
CPDC810.centmin = cms.untracked.int32(8)
CPDC810.centmax = cms.untracked.int32(10)

CPDC1012 = defaultCPDC.clone()
CPDC1012.centmin = cms.untracked.int32(10)
CPDC1012.centmax = cms.untracked.int32(12)

CPDC1214 = defaultCPDC.clone()
CPDC1214.centmin = cms.untracked.int32(12)
CPDC1214.centmax = cms.untracked.int32(14)

CPDC1416 = defaultCPDC.clone()
CPDC1416.centmin = cms.untracked.int32(14)
CPDC1416.centmax = cms.untracked.int32(16)

CPDC1618 = defaultCPDC.clone()
CPDC1618.centmin = cms.untracked.int32(16)
CPDC1618.centmax = cms.untracked.int32(18)

CPDC1820 = defaultCPDC.clone()
CPDC1820.centmin = cms.untracked.int32(18)
CPDC1820.centmax = cms.untracked.int32(20)

CPDC2022 = defaultCPDC.clone()
CPDC2022.centmin = cms.untracked.int32(20)
CPDC2022.centmax = cms.untracked.int32(22)

CPDC2224 = defaultCPDC.clone()
CPDC2224.centmin = cms.untracked.int32(22)
CPDC2224.centmax = cms.untracked.int32(24)

CPDC3032 = defaultCPDC.clone()
CPDC3032.centmin = cms.untracked.int32(30)
CPDC3032.centmax = cms.untracked.int32(32)

CPDC3234 = defaultCPDC.clone()
CPDC3234.centmin = cms.untracked.int32(32)
CPDC3234.centmax = cms.untracked.int32(34)

CPDC5052 = defaultCPDC.clone()
CPDC5052.centmin = cms.untracked.int32(50)
CPDC5052.centmax = cms.untracked.int32(52)

CPDC5254 = defaultCPDC.clone()
CPDC5254.centmin = cms.untracked.int32(52)
CPDC5254.centmax = cms.untracked.int32(54)


CPDC7072 = defaultCPDC.clone()
CPDC7072.centmin = cms.untracked.int32(70)
CPDC7072.centmax = cms.untracked.int32(72)

CPDC7274 = defaultCPDC.clone()
CPDC7274.centmin = cms.untracked.int32(72)
CPDC7274.centmax = cms.untracked.int32(74)

CPDC7476 = defaultCPDC.clone()
CPDC7476.centmin = cms.untracked.int32(74)
CPDC7476.centmax = cms.untracked.int32(76)

CPDC7678 = defaultCPDC.clone()
CPDC7678.centmin = cms.untracked.int32(76)
CPDC7678.centmax = cms.untracked.int32(78)

CPDC7880 = defaultCPDC.clone()
CPDC7880.centmin = cms.untracked.int32(78)
CPDC7880.centmax = cms.untracked.int32(80)



CPDCSUBASH = defaultCPDC.clone()
CPDCSUBASH.noffmin = cms.untracked.int32(0)
CPDCSUBASH.noffmax = cms.untracked.int32(200)

