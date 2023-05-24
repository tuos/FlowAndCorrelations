import FWCore.ParameterSet.Config as cms

defaultCPDC = cms.EDAnalyzer('AnaTwoPC', #Analyzer named: Correspond to the class name in 'plugin' folder
                             #Track collection
                             #tracks    = cms.InputTag('hiConformalPixelTracks'),
#                             tracks    = cms.InputTag('generalTracks'),
                             #tracks    = cms.InputTag('generalAndHiPixelTracks'),
#                             mvaSrc = cms.InputTag('generalTracks','MVAValues'),
                             # MiniAOD setup
                             tracks   = cms.InputTag("packedPFCandidates"), ###for general tracks - IMPORTANT: TO USE THIS, PLEASE SET "isPixelTracks=False"
                             #tracks   = cms.InputTag("hiPixelTracks"), ###for pixel tracks - IMPORTANT: TO USE THIS, PLEASE SET "isPixelTracks=True"
                             isPixelTracks = cms.bool(False), ###to switch to proper track selection
                             trackschi2 = cms.InputTag("packedPFCandidateTrackChi2"),
                             trackMC  = cms.InputTag("genParticles"), #for Gen. particles only
                             #Vertex collection
                             #vertex    = cms.InputTag('offlinePrimaryVertices'),
                             vertex  = cms.InputTag("offlineSlimmedPrimaryVerticesRecovery"),
                             #Calorimeter tower collection
                             #caloTower = cms.InputTag('towerMaker'),
                             #Centrality
                             #centralitySrc    = cms.InputTag("hiCentrality"),
                             centralityBinSrc = cms.InputTag("centralityBin","HFtowers"),
                             #Event classifier # 0 == centrality, 1 == n_trk^offline
                             evtclassifier = cms.untracked.int32(0), 
                             centmin = cms.untracked.int32(0), 
                             centmax = cms.untracked.int32(200), 
                             noffmin = cms.untracked.int32(0), 
                             noffmax = cms.untracked.int32(40), 
                             
                             #Efficiency/Fake correction
                             #cweight = cms.untracked.bool(True), 
                             cweight = cms.untracked.bool(False), 
                             fname   = cms.untracked.InputTag("2018PbPb_Efficiency_GeneralTracks_MB.root"),
                             fhpt   = cms.untracked.InputTag("2018PbPb_Efficiency_GeneralTracks_highPt.root"),
                             fmb   = cms.untracked.InputTag("2018PbPb_Efficiency_GeneralTracks_MB.root"),
                             #fmb   = cms.untracked.InputTag("alltrk_Run3.root"),
                             fpix   = cms.untracked.InputTag("2018PbPb_Efficiency_PixelTracks.root"),
                             fplus   = cms.untracked.InputTag("2018PbPb_Efficiency_GeneralTracks_MB_ChargePlus.root"),
                             fminus   = cms.untracked.InputTag("2018PbPb_Efficiency_GeneralTracks_MB_ChargeMinus.root"),

                             #fmb = cms.untracked.InputTag("newEffv1_ptetamvacuts_noalgoparameters_alltrk_Oct29_2021.root"),
                             #fplus = cms.untracked.InputTag("newEffv1_ptetamvacuts_noalgoparameters_postrk_Oct29_2021.root"),
                             #fminus = cms.untracked.InputTag("newEffv1_ptetamvacuts_noalgoparameters_negtrk_Oct29_2021.root"),


                             IsEffCorrection = cms.untracked.bool(True), 
                             #IsEffCorrection = cms.untracked.bool(False), 
                             isQAhisto = cms.untracked.bool(True), 
                             #IsMC = cms.untracked.bool(True), 
                             IsMC = cms.untracked.bool(False), 
                             effCorrBinMin = cms.untracked.vint32(0,5,10,30,50),
                             effCorrBinMax = cms.untracked.vint32(5,10,30,50,100),
                             
                             #Phiweight new
                             cweight2 = cms.untracked.bool(False), #Checking with phiweights correction
                             fname2   = cms.untracked.InputTag("EtaPhiWeights.root"),
                             phiCorrBinMin = cms.untracked.vint32(0,5,10,15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85),
                             phiCorrBinMax = cms.untracked.vint32(5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90),

                             #Vertex selection
                             nTrkAssoToVtx = cms.untracked.uint32(2),
                             selectVtxByMult = cms.untracked.bool(False),
                             zminVtx = cms.untracked.double(-15.0), #-15 original
                             zmaxVtx = cms.untracked.double(15.0),  #15 original
                             rhomaxVtx = cms.untracked.double(0.2),
                             #Track selection
                             
                             pTminTrk_trg = cms.untracked.double(0.5),
                             pTmaxTrk_trg = cms.untracked.double(10.0), #3.0 original
                             pTminTrk_ass = cms.untracked.double(1.0),
                             pTmaxTrk_ass = cms.untracked.double(3.0),
                             etaminTrk_trg = cms.untracked.double(-2.4), #-2.4
                             etamaxTrk_trg = cms.untracked.double(2.4),  #2.4
                             etaminTrk_ass = cms.untracked.double(-2.4),
                             etamaxTrk_ass = cms.untracked.double(2.4),
                             #Histogram binning
                             nEtaBins = cms.untracked.int32(32), #32 original
                             nPhiBins = cms.untracked.int32(32), #32 original
                             #Mixing factor
                             #bkgFactor = cms.untracked.uint32(10)
                             bkgFactor = cms.untracked.uint32(10)
)
