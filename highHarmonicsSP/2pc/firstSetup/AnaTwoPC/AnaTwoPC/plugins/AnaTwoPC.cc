//For TwoParticle correlation analysis--
//Clean version---
// system include files

//AnaTwoPC
// CMSSW include files
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"

// user include files
#include "AnaTwoPC/AnaTwoPC/interface/AnaTwoPC.h"
//#include "AnaTwoPC/AnaTwoPC/interface/cent_PbPb_2022.h"

//
// constructors and destructor
//
AnaTwoPC::AnaTwoPC(const edm::ParameterSet& iConfig) :

  //trackTags (consumes<reco::TrackCollection>(iConfig.getParameter<edm::InputTag>("tracks"))),
  tracksToken_( consumes< edm::View< pat::PackedCandidate > >( iConfig.         getParameter< edm::InputTag >( "tracks" ) ) ),
  isPixelTracks_( iConfig.getParameter< bool >( "isPixelTracks" ) ),
  chi2Map_( consumes< edm::ValueMap< float > >( iConfig.getParameter< edm::     InputTag >( "trackschi2" ) ) ),
  ftrackMC ( consumes<reco::GenParticleCollection>(iConfig.getParameter<edm::InputTag>("trackMC"))  ),
  vtxTags (consumes<reco::VertexCollection>(iConfig.getParameter<edm::InputTag>("vertex"))),
  //towers_(consumes<CaloTowerCollection>(iConfig.getParameter<edm::InputTag>("caloTower"))),
  //centralityTags (consumes<reco::Centrality>(iConfig.getParameter<edm::InputTag>("centralitySrc"))),
  centralityBinTags (consumes<int>(iConfig.getParameter<edm::InputTag>("centralityBinSrc"))),
  //mvaSrc (consumes<std::vector<float>>(iConfig.getParameter<edm::InputTag>("mvaSrc"))),
  evtclassifier (iConfig.getUntrackedParameter<int>("evtclassifier")),
  centmin (iConfig.getUntrackedParameter<int>("centmin")),
  centmax (iConfig.getUntrackedParameter<int>("centmax")),
  noffmin(iConfig.getUntrackedParameter<int>("noffmin")),
  noffmax(iConfig.getUntrackedParameter<int>("noffmax")),
  fIsMC (iConfig.getUntrackedParameter<bool>("IsMC") ),
  IsEffCorrection (iConfig.getUntrackedParameter<bool>("IsEffCorrection") ),
  isQAhisto(iConfig.getUntrackedParameter<bool>("isQAhisto")),
  cweight (iConfig.getUntrackedParameter<bool>("cweight")),
  fname (iConfig.getUntrackedParameter<edm::InputTag>("fname")),
  fhpt (iConfig.getUntrackedParameter<edm::InputTag>("fhpt")),
  fmb (iConfig.getUntrackedParameter<edm::InputTag>("fmb")),
  fpix (iConfig.getUntrackedParameter<edm::InputTag>("fpix")),
  fplus (iConfig.getUntrackedParameter<edm::InputTag>("fplus")),
  fminus (iConfig.getUntrackedParameter<edm::InputTag>("fminus")),
  effCorrBinMin(iConfig.getUntrackedParameter< std::vector< int > >("effCorrBinMin")),
  effCorrBinMax(iConfig.getUntrackedParameter< std::vector< int > >("effCorrBinMax")),
  zminVtx (iConfig.getUntrackedParameter<double>("zminVtx")),
  zmaxVtx (iConfig.getUntrackedParameter<double>("zmaxVtx")),
  rhomaxVtx (iConfig.getUntrackedParameter<double>("rhomaxVtx")),
  nTrkAssoToVtx (iConfig.getUntrackedParameter<unsigned int>("nTrkAssoToVtx")),
  selectVtxByMult (iConfig.getUntrackedParameter<bool>("selectVtxByMult")),
  pTmin_trg (iConfig.getUntrackedParameter<double>("pTminTrk_trg")),
  pTmax_trg (iConfig.getUntrackedParameter<double>("pTmaxTrk_trg")),
  pTmin_ass (iConfig.getUntrackedParameter<double>("pTminTrk_ass")),
  pTmax_ass (iConfig.getUntrackedParameter<double>("pTmaxTrk_ass")),
  etamin_trg (iConfig.getUntrackedParameter<double>("etaminTrk_trg")),
  etamax_trg (iConfig.getUntrackedParameter<double>("etamaxTrk_trg")),
  etamin_ass (iConfig.getUntrackedParameter<double>("etaminTrk_ass")),
  etamax_ass (iConfig.getUntrackedParameter<double>("etamaxTrk_ass")),
  bkgFactor(iConfig.getUntrackedParameter<unsigned int>("bkgFactor")),
  nEtaBins(iConfig.getUntrackedParameter<int>("nEtaBins")),
  nPhiBins(iConfig.getUntrackedParameter<int>("nPhiBins"))
{
  //file acc & eff
  TString filename(fname.label().c_str());
  feff = 0x0;
  
  if(cweight && !filename.IsNull())
    {
      edm::FileInPath fip(Form("AnaTwoPC/AnaTwoPC/data/EFF/gentrk/%s",filename.Data()));
      feff = new TFile(fip.fullPath().c_str(),"READ");
      heff.resize(feff->GetNkeys());
      for(unsigned int ik = 0; ik < heff.size(); ++ik)
	{
          heff[ik] = (TH2D*) feff->Get(feff->GetListOfKeys()->At(ik)->GetName());
	}
    }
  else
    {
      cweight = false;
      edm::LogWarning ("Cannot open file") <<"Invalid efficiency correction file!";
    }
  

  evt = new DiHadronCorrelationEvt(2, 2);
  //----------------------for gentrk------
  TString f_pt(fhpt.label().c_str());
  edm::FileInPath f1(Form("AnaTwoPC/AnaTwoPC/data/EFF/effHpT/%s",f_pt.Data()));
  
  TString f_mb(fmb.label().c_str());
  edm::FileInPath f2(Form("AnaTwoPC/AnaTwoPC/data/EFF/effMB/%s",f_mb.Data()));
  //edm::FileInPath f2(Form("AnaTwoPC/AnaTwoPC/data/EFF/run3_general/%s",f_mb.Data()));
  
  TString f_pix(fpix.label().c_str());
  edm::FileInPath f3(Form("AnaTwoPC/AnaTwoPC/data/EFF/effPix/%s",f_pix.Data()));
  
  TString f_plus(fplus.label().c_str());
  edm::FileInPath f4(Form("AnaTwoPC/AnaTwoPC/data/EFF/plus/%s",f_plus.Data()));
  
  TString f_minus(fminus.label().c_str());
  edm::FileInPath f5(Form("AnaTwoPC/AnaTwoPC/data/EFF/minus/%s",f_minus.Data()));

  //by Subas-------
  trkEFF1 = new TrkEff2018PbPb(  "generalMB+",  false , f1.fullPath(), f2.fullPath(), f4.fullPath(), f5.fullPath(), f3.fullPath());
  trkEFF2 = new TrkEff2018PbPb(  "generalMB-",  false , f1.fullPath(), f2.fullPath(), f4.fullPath(), f5.fullPath(), f3.fullPath());
  trkEFF = new TrkEff2018PbPb(  "general",  false , f1.fullPath(), f2.fullPath(), f4.fullPath(), f5.fullPath(), f3.fullPath());
  //trkEFF = new TrkEff2018PbPb(  "general",  false ,f2.fullPath(), f4.fullPath(), f5.fullPath(), f3.fullPath());
  
  
  //--------------------------------------
  TH1::SetDefaultSumw2();
  
  // Now do what ever initialization is needed
  usesResource("TFileService");
  edm::Service<TFileService> fs;
  // Histograms
  TFileDirectory fVtxHist  = fs->mkdir("Vertex");
  hZBestVtx   = fVtxHist.make<TH1F>("hZvtx", "", 600, -30., 30.);
  
  TFileDirectory fGlobalHist  = fs->mkdir("Global");
  
  const Int_t nptBin = 15;
  Double_t ptbining[nptBin+1] = {0.5, 0.6,  0.7, 0.8, 0.9,1.0, 1.1, 1.2, 1.30, 1.40, 1.50, 1.60, 1.70, 1.80, 1.90, 2.0};

  //const Int_t nptBin_ = 15;
  //Double_t ptbining_[nptBin+1] = {0.5, 0.6, 0.8, 1.0, 1.25, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 5.0, 6.0, 7.0, 8.0, 10.0};

  const Int_t nptBin_ = 17;
  Double_t ptbining_[nptBin_+1] = {0.3, 0.4, 0.5, 0.6, 0.8, 1.0, 1.25, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 5.0, 6.0, 7.0, 8.0, 10.0};

  //const Int_t nptBin_ = 1; //tuo-ptcut
  //Double_t ptbining_[nptBin_+1] = {1.0, 3.0}; //tuo-ptcut


  const Int_t nrapBin = 18;
  Double_t rapbining[nrapBin+1] = {-2.4, -2.0, -1.6, -1.4, -1.3, -1.2, -1.0, -0.8, -0.4, 0.0, 0.4, 0.8, 1.0, 1.2, 1.3, 1.4, 1.6, 2.0, 2.4};

  int Multbin = 10000;
  int nMultbin = 3;
  int multbinLow = -0.5;
  int multbinHigh = 9999.5;
  
  hCent               = fGlobalHist.make<TH1I>("hCent", "",  200, -0.5, 199.5);

  hNoff_          = fGlobalHist.make<TH1I>("hNoff", "p_{T} > 0.4 GeV/c", 10000, 0, 10000);
  if(fIsMC){
    hMultTrgGen            = fGlobalHist.make<TH1I>("hMult_trgGen",
						    Form("%1.1f < p_{T} < %1.1f GeV/c", pTmin_trg, pTmax_trg),
						    nMultbin, multbinLow, multbinHigh);
    hMultTrgGenPlus            = fGlobalHist.make<TH1I>("hMult_trgGenPlus",
                                                    Form("%1.1f < p_{T} < %1.1f GeV/c", pTmin_trg, pTmax_trg),
                                                    nMultbin, multbinLow, multbinHigh);

    hMultTrgGenMinus            = fGlobalHist.make<TH1I>("hMult_trgGenMinus",
                                                    Form("%1.1f < p_{T} < %1.1f GeV/c", pTmin_trg, pTmax_trg),
                                                    nMultbin, multbinLow, multbinHigh);

    
    hMultAssoGen           = fGlobalHist.make<TH1I>("hMultAssoGen",
						    Form("%1.1f < p_{T} < %1.1f GeV/c", pTmin_trg, pTmax_trg),
						    nMultbin, multbinLow, multbinHigh);
  }
  
  hMultTrg            = fGlobalHist.make<TH1I>("hMult_trg",
					     Form("%1.1f < p_{T} < %1.1f GeV/c", pTmin_trg, pTmax_trg),
					       nMultbin, multbinLow, multbinHigh);
  hMultTrgCorrtd      = fGlobalHist.make<TH1F>("hMultTrgCorrtd",
					       Form("%1.1f < p_{T} < %1.1f GeV/c", pTmin_trg, pTmax_trg),
					       nMultbin, multbinLow, multbinHigh);

  hMultTrgPlus      = fGlobalHist.make<TH1F>("hMultTrgPlus",
                                               Form("%1.1f < p_{T} < %1.1f GeV/c", pTmin_trg, pTmax_trg),
                                               Multbin, multbinLow, multbinHigh);

  hMultTrgMinus      = fGlobalHist.make<TH1F>("hMultTrgMinus",
                                               Form("%1.1f < p_{T} < %1.1f GeV/c", pTmin_trg, pTmax_trg),
                                               Multbin, multbinLow, multbinHigh);

  hMultTrgCorrtdPlus      = fGlobalHist.make<TH1F>("hMultTrgCorrtdPlus",
                                               Form("%1.1f < p_{T} < %1.1f GeV/c", pTmin_trg, pTmax_trg),
                                               Multbin, multbinLow, multbinHigh);

  hMultTrgCorrtdMinus      = fGlobalHist.make<TH1F>("hMultTrgCorrtdMinus",
                                               Form("%1.1f < p_{T} < %1.1f GeV/c", pTmin_trg, pTmax_trg),
                                               Multbin, multbinLow, multbinHigh);

  for(unsigned int i = 0; i<nptBin_; i++){
    hMultTrg_ptbin[i]            = fGlobalHist.make<TH1D>(Form("hMult_trg_ptbin%d",i),
							  Form("%1.1f < p_{T} < %1.1f GeV/c", pTmin_trg, pTmax_trg),
							  nMultbin, multbinLow, multbinHigh);
    
    hptTrg_ptbin[i]              = fGlobalHist.make<TH1D>(Form("hpT_trg_ptbin%d",i),
							  Form("%1.1f < p_{T} < %1.1f GeV/c", pTmin_trg, pTmax_trg),
							  97, 0.3, 10.0);
    
  }


  hMultAsso           = fGlobalHist.make<TH1I>("hMultAsso",
					     Form("%1.1f < p_{T} < %1.1f GeV/c", pTmin_trg, pTmax_trg),
					     nMultbin, multbinLow, multbinHigh);
  hMultAssoCorrtd     = fGlobalHist.make<TH1F>("hMultAssoCorrtd",
					       Form("%1.1f < p_{T} < %1.1f GeV/c", pTmin_trg, pTmax_trg),
					       nMultbin, multbinLow, multbinHigh);
  if(isQAhisto){
    
    if(fIsMC){     
      hPhidistGen          = fGlobalHist.make<TH1F>("hPhidistGen", "", nPhiBins, -TMath::Pi(),  TMath::Pi() );
      hEtadistGen          = fGlobalHist.make<TH1D>("hEtadistGen", "#eta all", nEtaBins, etamin_trg, etamax_trg );
      hPTdistGen           = fGlobalHist.make<TH1D>("hPTdistGen", "p_{T} all", nptBin, ptbining);
      hPTdistPlusGen       = fGlobalHist.make<TH1D>("hPTdistPlusGen", "p_{T}, h^{+}", nptBin, ptbining);
      hPTdistMinusGen      = fGlobalHist.make<TH1D>("hPTdistMinusGen", "p_{T}, h^{-}", nptBin, ptbining);
      hetadistPlusGen      = fGlobalHist.make<TH1D>("hetadistPlusGen", "#eta h^{+}", nrapBin, rapbining);
      hetadistMinusGen     = fGlobalHist.make<TH1D>("hetadistMinusGen", "#eta h^{-}", nrapBin, rapbining);
    }
    
    hPhidist          = fGlobalHist.make<TH1F>("hPhidist", "", nPhiBins, -TMath::Pi(),  TMath::Pi() );
    hEtadist          = fGlobalHist.make<TH1D>("hEtadist", "#eta all", nEtaBins, etamin_trg, etamax_trg );
    hPTdist           = fGlobalHist.make<TH1D>("hPTdist", "p_{T} all", nptBin, ptbining);
    hPTdistPlus       = fGlobalHist.make<TH1D>("hPTdistPlus", "p_{T}, h^{+}", nptBin, ptbining);
    hPTdistMinus      = fGlobalHist.make<TH1D>("hPTdistMinus", "p_{T}, h^{-}", nptBin, ptbining);
    hetadistPlus      = fGlobalHist.make<TH1D>("hetadistPlus", "#eta h^{+}", nEtaBins, etamin_trg, etamax_trg);
    hetadistMinus     = fGlobalHist.make<TH1D>("hetadistMinus", "#eta h^{-}", nEtaBins, etamin_trg, etamax_trg);
    
    hPTdistPlus_corr       = fGlobalHist.make<TH1D>("hPTdistPlus_corr", "p_{T}, corr h^{+}", nptBin, ptbining);
    hPTdistMinus_corr      = fGlobalHist.make<TH1D>("hPTdistMinus_corr", "p_{T},corr h^{-}", nptBin, ptbining);
    hetadistPlus_corr      = fGlobalHist.make<TH1D>("hetadistPlus_corr", "#etacorr h^{+}", nrapBin, rapbining);
    hetadistMinus_corr     = fGlobalHist.make<TH1D>("hetadistMinus_corr", "#etacorr h^{-}", nrapBin, rapbining);
    hcoszdptzPM = fGlobalHist.make<TH2D>("hcoszdptz_PM","",1000,0.,0.1,1000,0., .1);
    hcoszdptzPP = fGlobalHist.make<TH2D>("hcoszdptz_PP","",1000,0.,0.1,1000,0., .1);
    hcoszdptzMP = fGlobalHist.make<TH2D>("hcoszdptz_MP","",1000,0.,0.1,1000,0., .1);
    hcoszdptzMM = fGlobalHist.make<TH2D>("hcoszdptz_MM","",1000,0.,0.1,1000,0., .1);

    hPTdistAsso = fGlobalHist.make<TH1D>("hPTdistAsso", "p_{T} associated", 97, 0.3, 10.0);
    hPTdistTrg = fGlobalHist.make<TH1D>("hPTdistTrg", "p_{T} associated", 97, 0.3, 10.0);


    hPTdistAssobkg = fGlobalHist.make<TH1D>("hPTdistAssobkg", "p_{T} associated", 97, 0.3, 10.0);
    hPTdistTrgbkg = fGlobalHist.make<TH1D>("hPTdistTrgbkg", "p_{T} associated", 97, 0.3, 10.0);
    
    
    hpt_triggerbin    = fGlobalHist.make<TH1D>("hpt_triggerbin_reco", "", nptBin_, ptbining_ );
    hpt_triggerbin_gen    = fGlobalHist.make<TH1D>("hpt_triggerbin_gen", "", nptBin_, ptbining_ );
    hpt = fGlobalHist.make<TH1D>("pt check", "p_{T}", 100, 0.0, 10.0);
    //hpt_ass    = fGlobalHist.make<TH1D>("hpt_ass_reco", "", nptBin_, ptbining_ );
    
    //Ttrigger track raw histo--------------------------------------
    TFileDirectory fTrkTrgHist  = fs->mkdir("TrgTracksRaw");
    
    int nbins_trg = (pTmax_trg - pTmin_trg )/0.01;
    
    hEtaTrk_trg = fTrkTrgHist.make<TH1F>("hEtaTrk_trg", Form("%1.1f < p_{T} < %1.1f GeV/c", pTmin_trg, pTmax_trg),
					 300, -3., 3.);
    hPtTrk_trg  = fTrkTrgHist.make<TH1F>("hPtTrk_trg", Form("%1.1f<p_{T}<%1.1f GeV/c", pTmin_trg, pTmax_trg ),
					 nbins_trg,  pTmin_trg, pTmax_trg );
    hPhiTrk_trg  = fTrkTrgHist.make<TH1F>("hPhiTrk_trg",
					  Form("%1.1f<p_{T}<%1.1f GeV/c", pTmin_trg, pTmax_trg ),
					  640, -3.2, 3.2 );
    
    hPtTrk_trg_check  = fTrkTrgHist.make<TH1F>("hPtTrk_trg_check", Form("%1.1f<p_{T}<%1.1f GeV/c", pTmin_trg, pTmax_trg ),
					 nbins_trg/10.,  pTmin_trg, pTmax_trg );

    //Trigger track corrected histos-------------------------------
    TFileDirectory fTrkCorrTrgHist  = fs->mkdir("TrgTracksCorr");
    hEtaTrk_trgCorrtd = fTrkCorrTrgHist.make<TH1F>("hEtaTrk_trgCorrtd",
						   Form("%1.1f<p_{T}<%1.1f GeV/c", pTmin_trg, pTmax_trg ),
						   300, -3., 3.);
    hPtTrk_trgCorrtd  = fTrkCorrTrgHist.make<TH1F>("hPtTrk_trgCorrtd",
						   Form("%1.1f<p_{T}<%1.1f GeV/c", pTmin_trg, pTmax_trg ),
						   nbins_trg, pTmin_trg, pTmax_trg );
    hPhiTrk_trgCorrtd = fTrkCorrTrgHist.make<TH1F>("hPhiTrk_trgCorrtd",
						   Form("%1.1f<p_{T}<%1.1f GeV/c", pTmin_trg, pTmax_trg ),
						   640, -3.2, 3.2);

    
    hPtTrk_trgCorrtd_check  = fTrkCorrTrgHist.make<TH1F>("hPtTrk_trgCorrtd_check",
						   Form("%1.1f<p_{T}<%1.1f GeV/c", pTmin_trg, pTmax_trg ),
						   nbins_trg/10., pTmin_trg, pTmax_trg );


    //Associated track raw histos--------------------------------------
    TFileDirectory fTrkAssHist  = fs->mkdir("AssTracksRaw");
    int nbins_ass = (int) (pTmax_ass - pTmin_ass)/0.01;
    hEtaTrk_ass = fTrkAssHist.make<TH1F>("hEtaTrk_ass",
					 Form("%1.1f<$p_{T}<%1.1f GeV/c", pTmin_ass, pTmax_ass),
					 300, -3., 3.);
    hPtTrk_ass  = fTrkAssHist.make<TH1F>("hPtTrk_ass",
					 Form("%1.1f<$p_{T}<%1.1f GeV/c", pTmin_ass, pTmax_ass),
					 nbins_ass,  pTmin_ass, pTmax_ass);
    hPhiTrk_ass = fTrkAssHist.make<TH1F>("hPhiTrk_ass",
					 Form("%1.1f<$p_{T}<%1.1f GeV/c", pTmin_ass, pTmax_ass),
					 640, -3.2, 3.2);


    hPtTrk_ass_check  = fTrkAssHist.make<TH1F>("hPtTrk_ass_check",
					 Form("%1.1f<$p_{T}<%1.1f GeV/c", pTmin_ass, pTmax_ass),
					 nbins_ass/10.0,  pTmin_ass, pTmax_ass);

    //Associated track corrected histos--------------------------------------
    TFileDirectory fTrkCorrAssHist  = fs->mkdir("AssTracksCorr");
    hEtaTrk_assCorrtd = fTrkCorrAssHist.make<TH1F>("hEtaTrk_assCorrtd",
						   Form("%1.1f<$p_{T}<%1.1f GeV/c", pTmin_ass, pTmax_ass),
						   300, -3., 3.);
    hPtTrk_assCorrtd  = fTrkCorrAssHist.make<TH1F>("hPtTrk_assCorrtd",
						   Form("%1.1f<$p_{T}<%1.1f GeV/c", pTmin_ass, pTmax_ass),
						   nbins_ass, pTmin_ass, pTmax_ass);
    hPhiTrk_assCorrtd = fTrkCorrAssHist.make<TH1F>("hPhiTrk_assCorrtd",
						   Form("%1.1f<$p_{T}<%1.1f GeV/c", pTmin_ass, pTmax_ass),
						   640, -3.2, 3.2);

    hPtTrk_assCorrtd_check  = fTrkCorrAssHist.make<TH1F>("hPtTrk_assCorrtd_check",
						   Form("%1.1f<$p_{T}<%1.1f GeV/c", pTmin_ass, pTmax_ass),
						   nbins_ass/10.0, pTmin_ass, pTmax_ass);


  }//if(isQA)-------
  
  
  //Define eta and phi bin limits---
  double etaW = (etamax_trg - etamin_ass - etamin_trg + etamax_ass) / nEtaBins;
  double phiW = 2.0*(TMath::Pi())/nPhiBins;
  double minEta = etamin_trg - etamax_ass - etaW/2;
  double maxEta = etamax_trg - etamin_ass + etaW/2.;
  double minPhi = -(TMath::Pi() - phiW)/2.0;
  double maxPhi = (TMath::Pi() * 3.0 - phiW)/2.0;
  
  TFileDirectory fSignalHist      = fs->mkdir("Signal");
  
  if(fIsMC){

    
    hSignal_all_GEN = fSignalHist.make<TH2D>("signal_all_Gen",
					  Form("%1.1f<p_{T}^{trg}<%1.1f GeV/c, %1.1f<p_{T}^{ass}<%1.1f GeV/c;#Delta#eta;#Delta#phi",
					       pTmin_trg, pTmax_trg, pTmin_ass, pTmax_ass),
					  nEtaBins+1, minEta, maxEta, nPhiBins-1, minPhi, maxPhi);


    for(unsigned int i = 0; i<nptBin_; i++)
      {
	hSignal_all_ptbin_GEN[i] = fSignalHist.make<TH2D>(Form("signal_all_ptbin%d_Gen",i),
							  Form("%1.1f<p_{T}^{trg}<%1.1f GeV/c, %1.1f<p_{T}^{ass}<%1.1f GeV/c;#Delta#eta;#Delta#phi",
							       //pTmin_trg, pTmax_trg, pTmin_ass, pTmax_ass),
							       ptbining_[i], ptbining_[i+1], pTmin_ass, pTmax_ass),
							  nEtaBins + 1, minEta, maxEta, nPhiBins - 1, minPhi, maxPhi );
      }

    /*    
    hSignalPPGen = fSignalHist.make<TH2D>("signal_PP_Gen",
				       Form("%1.1f<p_{T}^{trg}<%1.1f GeV/c, %1.1f<p_{T}^{ass}<%1.1f GeV/c;#Delta#eta;#Delta#phi",
					    pTmin_trg, pTmax_trg, pTmin_ass, pTmax_ass),
				       nEtaBins+1, minEta, maxEta, nPhiBins-1, minPhi, maxPhi);
    
    hSignalPMGen = fSignalHist.make<TH2D>("signal_PM_Gen",
				       Form("%1.1f<p_{T}^{trg}<%1.1f GeV/c, %1.1f<p_{T}^{ass}<%1.1f GeV/c;#Delta#eta;#Delta#phi",
					    pTmin_trg, pTmax_trg, pTmin_ass, pTmax_ass),
				       nEtaBins + 1, minEta, maxEta, nPhiBins-1, minPhi, maxPhi);
    hSignalMPGen = fSignalHist.make<TH2D>("signal_MP_Gen",
				       Form("%1.1f<p_{T}^{trg}<%1.1f GeV/c, %1.1f<p_{T}^{ass}<%1.1f GeV/c;#Delta#eta;#Delta#phi",
					    pTmin_trg, pTmax_trg, pTmin_ass, pTmax_ass),
				       nEtaBins + 1, minEta, maxEta, nPhiBins - 1, minPhi, maxPhi);
    
    hSignalMMGen = fSignalHist.make<TH2D>("signal_MM_Gen",
				       Form("%1.1f<p_{T}^{trg}<%1.1f GeV/c, %1.1f<p_{T}^{ass}<%1.1f GeV/c;#Delta#eta;#Delta#phi",
					    pTmin_trg, pTmax_trg, pTmin_ass, pTmax_ass),
				       nEtaBins + 1, minEta, maxEta, nPhiBins - 1, minPhi, maxPhi);
    */
 }
  
  /*
  hSignalPP = fSignalHist.make<TH2D>("signal_PP_reco",
				     Form("%1.1f<p_{T}^{trg}<%1.1f GeV/c, %1.1f<p_{T}^{ass}<%1.1f GeV/c;#Delta#eta;#Delta#phi",
					  pTmin_trg, pTmax_trg, pTmin_ass, pTmax_ass),
				     nEtaBins+1, minEta, maxEta, nPhiBins-1, minPhi, maxPhi);
  
  hSignalPM = fSignalHist.make<TH2D>("signal_PM_reco",
				     Form("%1.1f<p_{T}^{trg}<%1.1f GeV/c, %1.1f<p_{T}^{ass}<%1.1f GeV/c;#Delta#eta;#Delta#phi",
					  pTmin_trg, pTmax_trg, pTmin_ass, pTmax_ass),
				     nEtaBins + 1, minEta, maxEta, nPhiBins-1, minPhi, maxPhi);
  hSignalMP = fSignalHist.make<TH2D>("signal_MP_reco",
				     Form("%1.1f<p_{T}^{trg}<%1.1f GeV/c, %1.1f<p_{T}^{ass}<%1.1f GeV/c;#Delta#eta;#Delta#phi",
					  pTmin_trg, pTmax_trg, pTmin_ass, pTmax_ass),
				     nEtaBins + 1, minEta, maxEta, nPhiBins - 1, minPhi, maxPhi);
  
  hSignalMM = fSignalHist.make<TH2D>("signal_MM_reco",
				     Form("%1.1f<p_{T}^{trg}<%1.1f GeV/c, %1.1f<p_{T}^{ass}<%1.1f GeV/c;#Delta#eta;#Delta#phi",
					  pTmin_trg, pTmax_trg, pTmin_ass, pTmax_ass),
				     nEtaBins + 1, minEta, maxEta, nPhiBins - 1, minPhi, maxPhi);
  */

  hSignal_all = fSignalHist.make<TH2D>("signal_all_reco",
					    Form("%1.1f<p_{T}^{trg}<%1.1f GeV/c, %1.1f<p_{T}^{ass}<%1.1f GeV/c;#Delta#eta;#Delta#phi",
						 pTmin_trg, pTmax_trg, pTmin_ass, pTmax_ass),
					    nEtaBins+1, minEta, maxEta, nPhiBins-1, minPhi, maxPhi);

  for(unsigned int i = 0; i<nptBin_; i++)
    {
      hSignal_all_ptbin[i] = fSignalHist.make<TH2D>(Form("signal_all_ptbin%d_reco",i),
							    Form("%1.1f<p_{T}^{trg}<%1.1f GeV/c, %1.1f<p_{T}^{ass}<%1.1f GeV/c;#Delta#eta;#Delta#phi",
								 //pTmin_trg, pTmax_trg, pTmin_ass, pTmax_ass),
								 ptbining_[i], ptbining_[i+1], pTmin_ass, pTmax_ass),
							    nEtaBins + 1, minEta, maxEta, nPhiBins - 1, minPhi, maxPhi );
    }


  /*
  //reco corrected
  hSignalPP_corr = fSignalHist.make<TH2D>("signal_PP_recocor",
				     Form("%1.1f<p_{T}^{trg}<%1.1f GeV/c, %1.1f<p_{T}^{ass}<%1.1f GeV/c;#Delta#eta;#Delta#phi",
					  pTmin_trg, pTmax_trg, pTmin_ass, pTmax_ass),
				     nEtaBins+1, minEta, maxEta, nPhiBins-1, minPhi, maxPhi);
  
  hSignalPM_corr = fSignalHist.make<TH2D>("signal_PM_recocor",
				     Form("%1.1f<p_{T}^{trg}<%1.1f GeV/c, %1.1f<p_{T}^{ass}<%1.1f GeV/c;#Delta#eta;#Delta#phi",
					  pTmin_trg, pTmax_trg, pTmin_ass, pTmax_ass),
				     nEtaBins + 1, minEta, maxEta, nPhiBins-1, minPhi, maxPhi);
  hSignalMP_corr = fSignalHist.make<TH2D>("signal_MP_recocor",
				     Form("%1.1f<p_{T}^{trg}<%1.1f GeV/c, %1.1f<p_{T}^{ass}<%1.1f GeV/c;#Delta#eta;#Delta#phi",
					  pTmin_trg, pTmax_trg, pTmin_ass, pTmax_ass),
				     nEtaBins + 1, minEta, maxEta, nPhiBins - 1, minPhi, maxPhi);
  
  hSignalMM_corr = fSignalHist.make<TH2D>("signal_MM_recocor",
				     Form("%1.1f<p_{T}^{trg}<%1.1f GeV/c, %1.1f<p_{T}^{ass}<%1.1f GeV/c;#Delta#eta;#Delta#phi",
					  pTmin_trg, pTmax_trg, pTmin_ass, pTmax_ass),
				     nEtaBins + 1, minEta, maxEta, nPhiBins - 1, minPhi, maxPhi);
  */

  hSignal_all_corr = fSignalHist.make<TH2D>("signal_all_recocor",
					    Form("%1.1f<p_{T}^{trg}<%1.1f GeV/c, %1.1f<p_{T}^{ass}<%1.1f GeV/c;#Delta#eta;#Delta#phi",
						 pTmin_trg, pTmax_trg, pTmin_ass, pTmax_ass),
					    nEtaBins+1, minEta, maxEta, nPhiBins-1, minPhi, maxPhi);


  for(unsigned int i = 0; i<nptBin_; i++)
    {
      hSignal_all_ptbin_corr[i] = fSignalHist.make<TH2D>(Form("signal_all_ptbin%d_recocor",i),
						    Form("%1.1f<p_{T}^{trg}<%1.1f GeV/c, %1.1f<p_{T}^{ass}<%1.1f GeV/c;#Delta#eta;#Delta#phi",
							 //pTmin_trg, pTmax_trg, pTmin_ass, pTmax_ass),
							 ptbining_[i], ptbining_[i+1], pTmin_ass, pTmax_ass),
						    nEtaBins + 1, minEta, maxEta, nPhiBins - 1, minPhi, maxPhi );
    }
  
  
  /*
  hsig_PM_dphi_eff = fSignalHist.make<TProfile>("hsig_PM_dphi_eff","", nPhiBins - 1, minPhi, maxPhi, 0., 2.);  
  hsig_MP_dphi_eff = fSignalHist.make<TProfile>("hsig_MP_dphi_eff","", nPhiBins - 1, minPhi, maxPhi,  0., 2.);  
  hsig_MM_dphi_eff = fSignalHist.make<TProfile>("hsig_MM_dphi_eff","", nPhiBins - 1, minPhi, maxPhi, 0., 2.);  
  hsig_PP_dphi_eff = fSignalHist.make<TProfile>("hsig_PP_dphi_eff","", nPhiBins - 1, minPhi, maxPhi, 0., 2.);  
  
  
  hsig_PM_dphi_eff = fSignalHist.make<TProfile2D>("hsig_PM_dphi_eff", " ", nEtaBins+1, minEta, maxEta, nPhiBins - 1, minPhi, maxPhi,  0.,  1.);  
  hsig_MP_dphi_eff = fSignalHist.make<TProfile2D>("hsig_MP_dphi_eff", " ", nEtaBins+1, minEta, maxEta, nPhiBins - 1, minPhi, maxPhi,  0.,  1.);  
  hsig_MM_dphi_eff = fSignalHist.make<TProfile2D>("hsig_MM_dphi_eff", " ", nEtaBins+1, minEta, maxEta, nPhiBins - 1, minPhi, maxPhi,  0.,  1.);  
  hsig_PP_dphi_eff = fSignalHist.make<TProfile2D>("hsig_PP_dphi_eff", " ", nEtaBins+1, minEta, maxEta, nPhiBins - 1, minPhi, maxPhi,  0.,  1.);  
  */

  //For Background-------------
  TFileDirectory fBackgroundHist  = fs->mkdir("Background");
  
  if(fIsMC){

    hBackground_allGen = fBackgroundHist.make<TH2D>("background_all_Gen",
                                                  Form("%1.1f<p_{T}^{trg}<%1.1f GeV/c, %1.1f<p_{T}^{ass}<%1.1f GeV/c;#Delta#eta;#Delta#phi",
                                                       pTmin_trg, pTmax_trg, pTmin_ass, pTmax_ass),
                                                  nEtaBins + 1, minEta, maxEta, nPhiBins - 1, minPhi, maxPhi );

    for(unsigned int i = 0; i<nptBin_; i++)
      {
	hBackground_all_ptbin_Gen[i] = fBackgroundHist.make<TH2D>(Form("background_all_ptbin%d_Gen",i),
								  Form("%1.1f<p_{T}^{trg}<%1.1f GeV/c, %1.1f<p_{T}^{ass}<%1.1f GeV/c;#Delta#eta;#Delta#phi",
								       ptbining_[i], ptbining_[i+1], pTmin_ass, pTmax_ass),
								  nEtaBins + 1, minEta, maxEta, nPhiBins - 1, minPhi, maxPhi );
      }

    /*
    hBackgroundPPGen = fBackgroundHist.make<TH2D>("background_PP_Gen",
						  Form("%1.1f<p_{T}^{trg}<%1.1f GeV/c, %1.1f<p_{T}^{ass}<%1.1f GeV/c;#Delta#eta;#Delta#phi",
						       pTmin_trg, pTmax_trg, pTmin_ass, pTmax_ass),
						  nEtaBins + 1, minEta, maxEta, nPhiBins - 1, minPhi, maxPhi );
    hBackgroundPMGen = fBackgroundHist.make<TH2D>("background_PM_Gen",
						  Form("%1.1f<p_{T}^{trg}<%1.1f GeV/c, %1.1f<p_{T}^{ass}<%1.1f GeV/c;#Delta#eta;#Delta#phi",
						       pTmin_trg, pTmax_trg, pTmin_ass, pTmax_ass),
						  nEtaBins + 1, minEta, maxEta, nPhiBins - 1, minPhi, maxPhi );
    hBackgroundMPGen = fBackgroundHist.make<TH2D>("background_MP_Gen",
						  Form("%1.1f<p_{T}^{trg}<%1.1f GeV/c, %1.1f<p_{T}^{ass}<%1.1f GeV/c;#Delta#eta;#Delta#phi",
						       pTmin_trg, pTmax_trg, pTmin_ass, pTmax_ass),
						  nEtaBins + 1, minEta, maxEta, nPhiBins - 1, minPhi, maxPhi );
    
    hBackgroundMMGen = fBackgroundHist.make<TH2D>("background_MM_Gen",
						  Form("%1.1f<p_{T}^{trg}<%1.1f GeV/c, %1.1f<p_{T}^{ass}<%1.1f GeV/c;#Delta#eta;#Delta#phi",
						       pTmin_trg, pTmax_trg, pTmin_ass, pTmax_ass),
						  nEtaBins + 1, minEta, maxEta, nPhiBins - 1, minPhi, maxPhi );
    */
    
  }
  /*
  hBackgroundPP = fBackgroundHist.make<TH2D>("background_PP_reco",
					     Form("%1.1f<p_{T}^{trg}<%1.1f GeV/c, %1.1f<p_{T}^{ass}<%1.1f GeV/c;#Delta#eta;#Delta#phi",
						  pTmin_trg, pTmax_trg, pTmin_ass, pTmax_ass),
					     nEtaBins + 1, minEta, maxEta, nPhiBins - 1, minPhi, maxPhi );
  hBackgroundPM = fBackgroundHist.make<TH2D>("background_PM_reco",
					     Form("%1.1f<p_{T}^{trg}<%1.1f GeV/c, %1.1f<p_{T}^{ass}<%1.1f GeV/c;#Delta#eta;#Delta#phi",
						  pTmin_trg, pTmax_trg, pTmin_ass, pTmax_ass),
					     nEtaBins + 1, minEta, maxEta, nPhiBins - 1, minPhi, maxPhi );
  hBackgroundMP = fBackgroundHist.make<TH2D>("background_MP_reco",
					     Form("%1.1f<p_{T}^{trg}<%1.1f GeV/c, %1.1f<p_{T}^{ass}<%1.1f GeV/c;#Delta#eta;#Delta#phi",
						  pTmin_trg, pTmax_trg, pTmin_ass, pTmax_ass),
					     nEtaBins + 1, minEta, maxEta, nPhiBins - 1, minPhi, maxPhi );
  
  hBackgroundMM = fBackgroundHist.make<TH2D>("background_MM_reco",
					     Form("%1.1f<p_{T}^{trg}<%1.1f GeV/c, %1.1f<p_{T}^{ass}<%1.1f GeV/c;#Delta#eta;#Delta#phi",
						  pTmin_trg, pTmax_trg, pTmin_ass, pTmax_ass),
					     nEtaBins + 1, minEta, maxEta, nPhiBins - 1, minPhi, maxPhi ); 
  */

  hBackground_all = fBackgroundHist.make<TH2D>("background_all_reco",
					       Form("%1.1f<p_{T}^{trg}<%1.1f GeV/c, %1.1f<p_{T}^{ass}<%1.1f GeV/c;#Delta#eta;#Delta#phi",
						    pTmin_trg, pTmax_trg, pTmin_ass, pTmax_ass),
					       nEtaBins + 1, minEta, maxEta, nPhiBins - 1, minPhi, maxPhi );


  for(unsigned int i = 0; i<nptBin_; i++)
    {
      hBackground_all_ptbin[i] = fBackgroundHist.make<TH2D>(Form("background_all_ptbin%d_reco",i),
							    Form("%1.1f<p_{T}^{trg}<%1.1f GeV/c, %1.1f<p_{T}^{ass}<%1.1f GeV/c;#Delta#eta;#Delta#phi",
								 ptbining_[i], ptbining_[i+1], pTmin_ass, pTmax_ass),
							    nEtaBins + 1, minEta, maxEta, nPhiBins - 1, minPhi, maxPhi );
    }

  /*
  //Reco corrected
  hBackgroundPP_corr = fBackgroundHist.make<TH2D>("background_PP_recocor",
					     Form("%1.1f<p_{T}^{trg}<%1.1f GeV/c, %1.1f<p_{T}^{ass}<%1.1f GeV/c;#Delta#eta;#Delta#phi",
						  pTmin_trg, pTmax_trg, pTmin_ass, pTmax_ass),
					     nEtaBins + 1, minEta, maxEta, nPhiBins - 1, minPhi, maxPhi );
  hBackgroundPM_corr = fBackgroundHist.make<TH2D>("background_PM_recocor",
					     Form("%1.1f<p_{T}^{trg}<%1.1f GeV/c, %1.1f<p_{T}^{ass}<%1.1f GeV/c;#Delta#eta;#Delta#phi",
						  pTmin_trg, pTmax_trg, pTmin_ass, pTmax_ass),
					     nEtaBins + 1, minEta, maxEta, nPhiBins - 1, minPhi, maxPhi );
  hBackgroundMP_corr = fBackgroundHist.make<TH2D>("background_MP_recocor",
					     Form("%1.1f<p_{T}^{trg}<%1.1f GeV/c, %1.1f<p_{T}^{ass}<%1.1f GeV/c;#Delta#eta;#Delta#phi",
						  pTmin_trg, pTmax_trg, pTmin_ass, pTmax_ass),
					     nEtaBins + 1, minEta, maxEta, nPhiBins - 1, minPhi, maxPhi );
  
  hBackgroundMM_corr = fBackgroundHist.make<TH2D>("background_MM_recocor",
					     Form("%1.1f<p_{T}^{trg}<%1.1f GeV/c, %1.1f<p_{T}^{ass}<%1.1f GeV/c;#Delta#eta;#Delta#phi",
						  pTmin_trg, pTmax_trg, pTmin_ass, pTmax_ass),
					     nEtaBins + 1, minEta, maxEta, nPhiBins - 1, minPhi, maxPhi ); 
  
  */

  hBackground_all_corr = fBackgroundHist.make<TH2D>("background_all_recocor",
						    Form("%1.1f<p_{T}^{trg}<%1.1f GeV/c, %1.1f<p_{T}^{ass}<%1.1f GeV/c;#Delta#eta;#Delta#phi",
							 pTmin_trg, pTmax_trg, pTmin_ass, pTmax_ass),
						    nEtaBins + 1, minEta, maxEta, nPhiBins - 1, minPhi, maxPhi );
  
  for(unsigned int i = 0; i<nptBin_; i++)
    {
      hBackground_all_ptbin_corr[i] = fBackgroundHist.make<TH2D>(Form("background_all_ptbin%d_recocor",i),
								Form("%1.1f<p_{T}^{trg}<%1.1f GeV/c, %1.1f<p_{T}^{ass}<%1.1f GeV/c;#Delta#eta;#Delta#phi",
								     ptbining_[i], ptbining_[i+1], pTmin_ass, pTmax_ass),
								nEtaBins + 1, minEta, maxEta, nPhiBins - 1, minPhi, maxPhi );

    }


  /*
  hbkg_PM_dphi_eff = fBackgroundHist.make<TProfile>("hbkg_PM_dphi_eff","", nPhiBins - 1, minPhi, maxPhi, 0., 2.);  
  hbkg_MP_dphi_eff = fBackgroundHist.make<TProfile>("hbkg_MP_dphi_eff","", nPhiBins - 1, minPhi, maxPhi, 0., 2.);  
  hbkg_MM_dphi_eff = fBackgroundHist.make<TProfile>("hbkg_MM_dphi_eff","", nPhiBins - 1, minPhi, maxPhi, 0., 2.);  
  hbkg_PP_dphi_eff = fBackgroundHist.make<TProfile>("hbkg_PP_dphi_eff","", nPhiBins - 1, minPhi, maxPhi, 0., 2.);    
  */
}

AnaTwoPC::~AnaTwoPC()
{
 
   delete evt;
}


//
// member functions
//

// ------------ method called for each event  ------------
void AnaTwoPC::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   // ----- centrality selection -----
   // Get calo centrality collection by token
   //edm::Handle< reco::Centrality > centrality;
   //iEvent.getByToken(centralityTags, centrality);
   // Get calo centrality bin by token
   
   //edm::Handle< int > cbin;
   //iEvent.getByToken(centralityBinTags, cbin);
   //int centBin = *cbin;
   //if(centBin < 0)
   //{
   //    edm::LogWarning ("Invalid value") <<"Invalid centrality value";
   //}

   //access centrality bins
   auto cbin = iEvent.getHandle( centralityBinTags );
   int centBin = -1;
   centBin = ( int ) (*cbin);   

   // ----- Vertex selection---------------------
   // Get vertex collection by token
   //edm::Handle< reco::VertexCollection > vertices;
   //iEvent.getByToken(vtxTags, vertices);
   //if( !vertices->size() )
   //{
   //   edm::LogWarning ("Missing Collection") <<"Invalid or empty vertex collection!";
   //   return;
   //}

   //---Loop over vertices--------------------------------------
   xBestVtx = -999.;
   yBestVtx = -999.;
   zBestVtx = -999.;
   rhoBestVtx = -999.;
   xBestVtxError = -999.;
   yBestVtxError = -999.;
   zBestVtxError = -999.;
   //cntbin = -999.;
   cntbin = centBin;

   LoopVertices(iEvent, iSetup);

   //std::cout<<" centBin = "<<centBin<<"   zBestVtx = "<<zBestVtx<<std::endl;
   
   if( zBestVtx < zminVtx || zBestVtx  > zmaxVtx ) return; //cut on vertex Z position

   //if( rhoBestVtx > rhomaxVtx ) return; //cut on vertex XY position
   
   // ----- Ntrk offline selection -----
   ///double noff = LoopNoff(iEvent, iSetup); //compute ntrk^offline
   double noff = 0;

   //hZBestVtx->Fill( zBestVtx );
   
   // ----- Define event classification (either centrality or Ntrk^off) -----
   int evtclass = -1;
   
   switch(evtclassifier)
     {
     case 0:
       evtclass = cntbin;
       if(evtclass < centmin*2 || evtclass >= centmax*2) return;
       break;
     case 1:
       evtclass = -999.0; //set by hand for now
       //if(evtclass < noffmin || evtclass >= noffmax)
       if(evtclass < 0 || evtclass >= 40)
	 return;
     default:
       evtclass = -1;
     }
   
   hZBestVtx->Fill( zBestVtx );

   //evtclass = -999.0; //set by hand for now                                                                          
   //(evtclass < centmin*2 || evtclass >= centmax*2) return;
   
   //if(centmax >= 160)return;
   //std::cout << "evtclass is :"<< centmax << std::endl; 
   //evtclass = noff;
   //if(evtclass < 0 || evtclass >= 40)
     // return;  //---- for ntrk choosen
   //std::cout << "evtclass is :"<< evtclass << std::endl;

   nTrkTot_trgGen    = 0;
   nTrkTot_trgGen_Plus    = 0;
   nTrkTot_trgGen_Minus    = 0;
   nTrkTot_assGen    = 0;
   
   nTrkTot_trg       = 0;
   nTrkTot_trgCorrtd = 0;
   nTrkTot_trg_Plus = 0;
   nTrkTot_trg_Minus = 0;
   nTrkTot_trgCorrtd_Plus = 0;
   nTrkTot_trgCorrtd_Minus = 0;
   nTrkTot_ass       = 0;
   nTrkTot_assCorrtd = 0;
   
   // ----- Track selection -----
   if(fIsMC){ //Only Gen level info---
     LoopTracksMC(iEvent, iSetup, true,  evtclass, fIsMC); //trigger tracks
     LoopTracksMC(iEvent, iSetup, false, evtclass, fIsMC); //associated tracks
   }
   //Either MC reco, reco+corr or data---
   LoopTracks(iEvent, iSetup, true,  evtclass); //trigger tracks
   LoopTracks(iEvent, iSetup, false, evtclass); //associated tracks
   // ----- Fill and push evt containers -----
   evt->run   = iEvent.id().run();
   evt->event = iEvent.id().event();
   evt->zvtx  = zBestVtx;

   evtVec.push_back(*evt);

   hCent->Fill(cntbin);
   hNoff_->Fill(noff);
   // ----- Reset evt container -----
   evt->reset();
}


// ------------ method called once each job just before starting event loop  ------------
void AnaTwoPC::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void AnaTwoPC::endJob()
{
   std::cout<< "Start sorting the events!" << std::endl;
   std::sort(evtVec.begin(), evtVec.end());
   std::cout<< "Finish sorting the events!" << std::endl;

   std::cout<< "Total of " << evtVec.size() << " events are selected!" << std::endl;

   std::cout<< "Start running correlation analysis!" << std::endl;
   for( unsigned int i = 0; i < evtVec.size(); i++ )
   {
     if( i % 100 == 0 ) std::cout << "Processing " << i << "th event" << std::endl;
     //std::cout<<"Signal event :  " << i << std::endl<<std::endl<<std::endl;
     ///std::cout<<"iEvt = "<<i<<"   Starting with Filling Signal Histogram"<<std::endl;
     if(fIsMC) FillHistsSignal( i, kTRUE );
     FillHistsSignal( i, kFALSE );
     ///std::cout<<"iEvt = "<<i<<"   Done with Filling Signal Histogram, Starting BKG"<<std::endl;
     /*
     unsigned int mixstart = i+1;                                                                                                                 
     unsigned int mixend   = evtVec.size();
     unsigned int nmix=0;
     */
     
     unsigned int mixstart = i - bkgFactor/2;
     unsigned int mixend   = i + bkgFactor/2 + 1;
     
     if(i < bkgFactor)
     {
       mixstart = 0;
       mixend   = 2*bkgFactor + 1;
     }
     else if(i > evtVec.size() - bkgFactor - 1)
     {
       mixstart = evtVec.size() - 2*bkgFactor - 1;
       mixend   = evtVec.size();
     }
     
     if( mixend > evtVec.size() )
       mixend = evtVec.size();
     
     
     
     //std::cout << mixstart << " : " << mixend << std::endl;
     for( unsigned int j = mixstart; j < mixend; j++ )
       {
	 if(i == j) continue;
          //if(Nmix >= 10) continue;
	  //if(Nmix >= 5) continue;
	 
	 
          //std::cout << i << " : " << j << std::endl;
          double deltazvtx = evtVec[i].zvtx - evtVec[j].zvtx;
          if(fabs(deltazvtx) > 2.0) continue;  //---- default cut
	  //if(fabs(deltazvtx) > 0.5) continue;
	  
	  //nmix++;
          //if (nmix > bkgFactor) break;

          ///std::cout<<" i, j = "<<i<<"  "<<j<< " Start filling bkg histograms" << std::endl;
	  if(fIsMC)FillHistsBackground( i, j, kTRUE ); //---- un comment if you want to use it
	  FillHistsBackground( i, j, kFALSE ); //--un comment if you want to use  background
          ///std::cout<<" i, j = "<<i<<"  "<<j<< " Finish filling bkg histograms" << std::endl;
	}
   }
   
   
   std::cout<< "Finish running correlation analysis!" << std::endl;
   
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void AnaTwoPC::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//=========================================================================================

void AnaTwoPC::LoopVertices(const edm::Event& iEvent,
                                 const edm::EventSetup& iSetup)
{
  
  
  
   //edm::Handle< reco::VertexCollection > vertices;
   //iEvent.getByToken(vtxTags, vertices);
   auto vertices = iEvent.getHandle( vtxTags );
/*
   if(!vertices->size())
   {
      std::cout<<"Invalid or empty vertex collection!"<<std::endl;
      return;
   }

   reco::VertexCollection recoVertices = *vertices;

   if( selectVtxByMult )
   {
       std::sort( recoVertices.begin(),
                  recoVertices.end(),
                  [](const reco::Vertex &a, const reco::Vertex &b)
                  {
                     if ( a.tracksSize() == b.tracksSize() ) return a.chi2() < b.chi2();
                          return a.tracksSize() > b.tracksSize();
                  }
                );
   }
*/
/*
   double etHFtowerSumPlus=0;
   double etHFtowerSumMinus=0;
   double etHFtowerSum=0;
   int poshf = 0;
   int neghf = 0;
   edm::Handle<CaloTowerCollection> towers;
   iEvent.getByToken(towers_,towers);
   for( size_t i = 0; i<towers->size(); ++ i){
     const CaloTower & tower = (*towers)[ i ];
     double zs = tower.zside();
     bool isHF = tower.ietaAbs() > 29;
     if(isHF && zs > 0)
       {
	 etHFtowerSumPlus += tower.pt();
	 if(tower.energy()>4.)
	   {
	     poshf++;
	   }
       }
     if(isHF && zs < 0)
       {
	 etHFtowerSumMinus += tower.pt();
	 if(tower.energy()>4.)
           {
	     neghf++;
	   }
       }
   }
   etHFtowerSum=etHFtowerSumPlus + etHFtowerSumMinus;

   double centbin = getHiBinFromhiHF(etHFtowerSum);
   //std::cout<<"centbin is: "<<centbin<<std::endl;

   if(poshf < 1 || neghf < 1) return;
   //if(centbin < centmin*2 || centbin >= centmax*2) return; 
*/
/*
   for( reco::VertexCollection::const_iterator itVtx = recoVertices.begin();
        itVtx != recoVertices.end();
        ++itVtx )
     {
       // Drop fake vertex and vertex with less than 2 tracks attached to it
       if( !itVtx->isFake() && itVtx->tracksSize() >= nTrkAssoToVtx )
	 {
	   // x,y,z vertex position
	   double xVtx = itVtx->x();
	   double yVtx = itVtx->y();
	   double zVtx = itVtx->z();
	   // x,y,z vertex position error
	   double xVtxError = itVtx->xError();
	   double yVtxError = itVtx->yError();
	   double zVtxError = itVtx->zError();
	   // Radial vertex position
	   double rho = sqrt(xVtx*xVtx + yVtx*yVtx);
            // Increase N valid vertex in the collection
	   ++nVtx;
	   
	   //Get the first vertex as the best one (greatest sum p_{T}^{2})
	   if( itVtx == recoVertices.begin() )
	     {
	       xBestVtx = xVtx;
	       yBestVtx = yVtx;
	       zBestVtx = zVtx;
	       rhoBestVtx = rho;
	       xBestVtxError = xVtxError;
	       yBestVtxError = yVtxError;
	       zBestVtxError = zVtxError;
	       //cntbin = centbin;
	     }
	 }
     }
*/

   if ( !vertices->empty() ) {
      const reco::Vertex& vtx = (*vertices)[0];
      zBestVtxError = vtx.zError();
      yBestVtxError = vtx.yError();
      xBestVtxError = vtx.xError();
      zBestVtx = vtx.position().z();
      yBestVtx = vtx.position().y();
      xBestVtx = vtx.position().x();
   }else { 
      return; 
   }

}
//=========================================================================================
/*
double
AnaTwoPC::LoopNoff(const edm::Event& iEvent,
                             const edm::EventSetup& iSetup)
{
  double noff = 0.;
  edm::Handle< reco::TrackCollection > tracks;
  iEvent.getByToken(trackTags, tracks);  

  // Get track collection by token
   
  if( !tracks->size() )
    {
      edm::LogWarning ("Missing Collection") <<"Invalid or empty track collection!";
      return -999.;
    }

  // Loop over tracks
  for( reco::TrackCollection::const_iterator itTrk = tracks->begin();
       itTrk != tracks->end();
       ++itTrk )
    {
      // Select tracks based on proximity to best vertex
      math::XYZPoint bestvtx(xBestVtx,yBestVtx,zBestVtx);
      double dzvtx    = itTrk->dz(bestvtx);
       double dxyvtx   = itTrk->dxy(bestvtx);
       double dzerror  = sqrt(itTrk->dzError()*itTrk->dzError() + zBestVtxError*zBestVtxError);
       double dxyerror = sqrt(itTrk->d0Error()*itTrk->d0Error() + xBestVtxError*yBestVtxError);
       double pterror  = itTrk->ptError();
       // Get eta, pt and charge of the track
       double eta    = itTrk->eta();
       double pt     = itTrk->pt();
       int charge = itTrk->charge(); 
       
            
       // Select track based on quality
       if( !itTrk->quality(reco::TrackBase::highPurity) ) continue;
       if( charge == 0 ) continue;
       if( fabs(dzvtx / dzerror)   > 3.0 ) continue;
       if( fabs(dxyvtx / dxyerror) > 3.0 ) continue;
       if((pterror)/ pt >= 0.1 ) continue;
       if( pt <= 0.4 ) continue;
       if( eta < -2.4 || eta > 2.4 ) continue;
       
      
      ++noff;
    }

  return noff;
}
*/
//=========================================================================================
void AnaTwoPC::LoopTracksMC(const edm::Event& iEvent, const edm::EventSetup& iSetup,
					  bool istrg, int evtclass, bool isMC )
{
  
  edm::Handle< reco::GenParticleCollection > tracksGen;
  iEvent.getByToken(ftrackMC, tracksGen);
  if( !tracksGen->size() )
    {
      edm::LogWarning ("Missing MC Gen Collection") <<"Invalid or empty MC-Gen track collection!";
      return;
    }
  
  // Loop over tracks
  for( reco::GenParticleCollection::const_iterator itTrk = tracksGen->begin();itTrk != tracksGen->end(); ++itTrk )
    {
      
      // Get eta, pt, phi and charge of the track
      if( itTrk->status() != 1 ) continue;
      if( itTrk->charge() == 0 ) continue;
      // Get eta, pt, phi and charge of the track
      double eta      = itTrk->eta();
      double pt       = itTrk->pt();
      double phi      = itTrk->phi();
      int charge      = itTrk->charge();
      
      float eff1 = 1., eff2 = 1.;
      
     
      
      if( istrg ){ //for trigger particle--
	if( pt < pTmin_trg || pt >= pTmax_trg ) continue;
	if( eta <= etamin_trg || eta >= etamax_trg ) continue;
	
	hPhidistGen->Fill(phi);
	hEtadistGen->Fill(eta);
	hPTdistGen->Fill(pt);
	
	hpt_triggerbin_gen->Fill(pt);
	//int kpttrig = (hpt_triggerbin->FindBin(pt)) - 1;
	//hMultTrg_ptbin[kpttrig]->AddBinContent(1,1.0);
	//if(charge < 0) hMultTrgGen_ptbin->AddBinContent(3,1.0);
	//if(charge > 0) hMultTrgGen_ptbin->AddBinContent(2,1.0);

      } //else asso.
      else{
	if( pt < pTmin_ass || pt >= pTmax_ass ) continue;
	if( eta <= etamin_ass || eta >= etamax_ass ) continue;
      }
      
      
      if(charge > 0){
	hPTdistPlusGen->Fill(pt);
	hetadistPlusGen->Fill(eta);
      }
      else if (charge < 0) {
	 hPTdistMinusGen->Fill(pt);
	 hetadistMinusGen->Fill(eta);
       }
      
      AssignpTbins(pt, eta, phi, charge, eff1, eff2,  istrg, isMC );
      
      //std::cout<<" pt is="<<pt<<std::endl;
    }
  
  //Fill trk histograms
  
  if(istrg)
    { 
      hMultTrgGen->AddBinContent(1,nTrkTot_trgGen);
      hMultTrgGen->AddBinContent(3,nTrkTot_trgGen_Minus);
      hMultTrgGen->AddBinContent(2,nTrkTot_trgGen_Plus);

      (evt->nMultCorrVect_trg)[0] = nTrkTot_trgGen;
    }
  else
    {
      hMultAssoGen->Fill(nTrkTot_assGen);
      (evt->nMultCorrVect_ass)[0] = nTrkTot_assGen;
    }
  
}
//==========================================================================================
  
//=========================================================================================
void AnaTwoPC::LoopTracks(const edm::Event& iEvent, const edm::EventSetup& iSetup,
                               bool istrg, int evtclass)
{

   //edm::Handle<std::vector<float>> mvaoutput;
   //iEvent.getByToken(mvaSrc, mvaoutput);

// Get track collection by token
   //edm::Handle< reco::TrackCollection > tracks;
   //iEvent.getByToken(trackTags, tracks);
   //if( !tracks->size() )
   //{
   //    edm::LogWarning ("Missing Collection") <<"Invalid or empty track collection!";
   //    return;
   //}

   //track collection
   auto trks = iEvent.getHandle( tracksToken_ );
   //access tracks chi2/ndf
   auto chi2Map = iEvent.getHandle( chi2Map_ );  

   // Loop over tracks-----------
   //int it =0;
   
   //for( reco::TrackCollection::const_iterator itTrk = tracks->begin(); itTrk != tracks->end(); ++itTrk ){
   
   math::XYZPoint bestvtx( xBestVtx, yBestVtx,zBestVtx ); 
   int trkIndx = -1;
   for (auto const& trk : *trks) {  

     // Select tracks based on proximity to best vertex
     //math::XYZPoint bestvtx( xBestVtx, yBestVtx,zBestVtx ); 
     //double dzvtx    = itTrk->dz(bestvtx);
     //double dxyvtx   = itTrk->dxy(bestvtx);
     //double dzerror  = sqrt(itTrk->dzError()*itTrk->dzError() + zBestVtxError*zBestVtxError);
     //double dxyerror = sqrt(itTrk->d0Error()*itTrk->d0Error() + xBestVtxError*yBestVtxError);
     //double pterror  = itTrk->ptError();
     // Get eta, pt, phi and charge of the track
     //double eta      = itTrk->eta();
     //double pt       = itTrk->pt();
     //double phi      = itTrk->phi();
     //int charge      = itTrk->charge();
     // HI specific cuts
     //double chi2n    = itTrk->normalizedChi2();
     //double nlayers  = itTrk->hitPattern().trackerLayersWithMeasurement();
     //chi2n           = chi2n/nlayers;
     //int nHits       = itTrk->numberOfValidHits();
     //int algo        = itTrk->originalAlgo();
     
     //float trkMVA = (*mvaoutput)[it];    
     //it++;  
     
     
     //general tracks
     // Select track based on quality
     //if( !itTrk->quality(reco::TrackBase::highPurity) ) continue;
     //if( charge == 0 ) continue;
     //if( nHits < 11) continue ;  
     //if((pterror)/ pt >= 0.1 ) continue;
     //if(chi2n >= 0.18 ) continue ;                                                                        
     //if(( fabs(dxyvtx / dxyerror)) >= 3.0) continue;
     //if(fabs(dzvtx / dzerror) >= 3.0 ) continue;
     //if( pt < 0.3 || pt >=10.0 ) continue;
     //if( eta < etamin_trg || eta > etamax_trg ) continue;
       //if(algo==6 && trkMVA < 0.98)continue; //comment out by default
     

     //const reco::HitPattern& hit_pattern = itTrk->hitPattern();
     //if(hit_pattern.pixelLayersWithMeasurement()==0)continue;

     //MiniAOD
      trkIndx++;      

      if ( !trk.hasTrackDetails() ) continue;
      auto iter_tk = trk.pseudoTrack(); 

      double pTcut = -1.;
      if( !isPixelTracks_ ) {
         pTcut = 0.5;
      } else {
         pTcut = 0.3;
      }

      if ( iter_tk.pt() <= pTcut || iter_tk.pt() >=10.0 ) continue;
      //if ( iter_tk.pt() <= pTcut || iter_tk.pt() <= 1.0  || iter_tk.pt() >=3.0 ) continue; //tuo-ptcut
      //if ( std::abs( iter_tk.eta() ) >= 2.4 ) continue;
      if( iter_tk.eta() < etamin_trg || iter_tk.eta() > etamax_trg ) continue;
      double dzvtx = iter_tk.dz( bestvtx );
      double dxyvtx = iter_tk.dxy( bestvtx );
      double dzerror = std::hypot( iter_tk.dzError(), zBestVtxError );
      //double dxyerror = iter_tk.dxyError( bestvtx, vtx_cov );     
      double dxyerror = sqrt(iter_tk.d0Error()*iter_tk.d0Error() + xBestVtxError*yBestVtxError);     
      auto hit_pattern = iter_tk.hitPattern();
     
      double chi2ndof = 999.9;

      if ( !isPixelTracks_ ) {
         //general tracks selection for 2018 PbPb data
         chi2ndof = ( double ) ( *chi2Map )[ trks->ptrAt( trkIndx ) ];
         if ( std::abs( iter_tk.ptError() ) / iter_tk.pt() >= 0.1 ) continue; //default 0.1/loose 0.15
         if ( std::abs( dzvtx / dzerror ) >= 3 ) continue; //default 3/loose 5
         if ( std::abs( dxyvtx / dxyerror ) >= 3 ) continue; //default 3/loose 5
         if ( ( chi2ndof / hit_pattern.trackerLayersWithMeasurement() ) >= 0.18 ) continue;
         if ( iter_tk.numberOfValidHits() < 11 ) continue;
         if ( iter_tk.charge() == 0 ) continue; //adding charge requirement
      } else {
         //pixel tracks selection for 2018 PbPb data
         chi2ndof = iter_tk.normalizedChi2(); 
         if ( std::abs( dzvtx / dzerror ) >= 7 ) continue;
         if ( std::abs( dxyvtx / dxyerror ) >= 7 ) continue;
      }   

     double eta      = iter_tk.eta();
     double pt       = iter_tk.pt();
     double phi      = iter_tk.phi();
     int charge      = iter_tk.charge();
     
     /*
     //merged tracks
     if( charge == 0 ) continue;
     if( pt < 0.3 || pt >= 10.0 ) continue;
     if( eta <= etamin_trg || eta >= etamax_trg ) continue;
     */
     hpt->Fill(pt);
     
     float eff1 = 1., eff2 = 1., eff = 1.;
     
     if(IsEffCorrection)
       {
	 eff   = trkEFF->getCorrection(pt, eta, evtclass);
	 eff1  = trkEFF1->getCorrection(pt, eta, evtclass);
	 eff2  = trkEFF2->getCorrection(pt, eta, evtclass);

	 //eff1  = trkEFF->getCorrection(pt, eta, evtclass);
	 //eff2  = trkEFF->getCorrection(pt, eta, evtclass);
       }//Is correction
     
     //-----
     
     if( istrg ){ //for trigger particle--
       if( pt < pTmin_trg || pt >= pTmax_trg ) continue;
       if( eta <= etamin_trg || eta >= etamax_trg ) continue;

       hPhidist->Fill(phi);
       hEtadist->Fill(eta);
       hPTdist->Fill(pt);

       hpt_triggerbin->Fill(pt);

       if(charge > 0){
	 hPTdistPlus->Fill(pt);
	 hetadistPlus->Fill(eta);
	 //hMultTrg_ptbin[kpttrig]->AddBinContent(3,eff1);
       }
       else {
	 hPTdistMinus->Fill(pt);
	 hetadistMinus->Fill(eta);
	 //hMultTrg_ptbin[kpttrig]->AddBinContent(3,eff2);
       }
     } //else asso.
     else{
       if( pt < pTmin_ass || pt >= pTmax_ass ) continue;
       if( eta <= etamin_ass || eta >= etamax_ass ) continue;
     }
     
     
     //-----for eff---
     if (charge > 0){
       hPTdistPlus_corr->Fill(pt, eff1);
       hetadistPlus_corr->Fill(eta, eff1);
     }
     else if (charge < 0){
       hPTdistMinus_corr->Fill(pt, eff2);
       hetadistMinus_corr->Fill(eta, eff2);
     }
     
     
     //AssignpTbins(pt, eta, phi, charge, eff1, eff2,  istrg, kFALSE );
     AssignpTbins(pt, eta, phi, charge, eff, eff,  istrg, kFALSE );
     
     
   }
   
   // Fill trk histograms
   if(istrg)
     {     
       //hMultTrg->Fill(nTrkTot_trg);
       hMultTrg->AddBinContent(1,nTrkTot_trg);
       hMultTrg->AddBinContent(2,nTrkTot_trg_Plus);
       hMultTrg->AddBinContent(3,nTrkTot_trg_Minus);
       //hMultTrgCorrtd->Fill(nTrkTot_trgCorrtd);
       hMultTrgCorrtd->AddBinContent(1,nTrkTot_trgCorrtd);
       hMultTrgCorrtd->AddBinContent(2,nTrkTot_trgCorrtd_Plus);
       hMultTrgCorrtd->AddBinContent(3,nTrkTot_trgCorrtd_Minus);
       //hMultTrgPlus->Fill(nTrkTot_trg_Plus);
       //hMultTrgMinus->Fill(nTrkTot_trg_Minus);
       hMultTrgCorrtdPlus->Fill(nTrkTot_trgCorrtd_Plus);
       hMultTrgCorrtdMinus->Fill(nTrkTot_trgCorrtd_Minus);
       (evt->nMultCorrVect_trg)[1] = nTrkTot_trgCorrtd;
     }
   else
     {
       hMultAsso->Fill(nTrkTot_ass);
       hMultAssoCorrtd->Fill(nTrkTot_assCorrtd);
       (evt->nMultCorrVect_ass)[1] = nTrkTot_assCorrtd;
     }
   
}
//=========================================================================================

//=========================================================================================
double AnaTwoPC::GetEffWeight(double eta, double pt, int evtclass)
{
  double effweight = 1.0;
  if(evtclass == -1)
    {
      effweight = heff[0]->GetBinContent(heff[0]->FindBin(eta,pt));
    }
  else
    {
      int centIdx = 0;
      for(int icent = 0; icent < static_cast<int>(effCorrBinMin.size()); ++icent)
	{
	  if(evtclass >= effCorrBinMin[icent]*2 && evtclass < effCorrBinMax[icent]*2)
	    {
	      centIdx = icent;
	      continue;
	    }
	}
      effweight = heff[centIdx]->GetBinContent(heff[centIdx]->GetXaxis()->FindBin(eta), heff[centIdx]->GetYaxis()->FindBin(pt));
    }
  return effweight;
}

//=========================================================================================
//
//=========================================================================================
void AnaTwoPC::AssignpTbins(double pt,  double eta, double phi, int charge, double eff1, double eff2, bool istrg, bool isGen )
{

  TLorentzVector pvector;
  pvector.SetPtEtaPhiM(pt, eta, phi, 0.140);
  
  double EffValue[2] = { eff1, eff2 };
  int idx;
  charge > 0 ? idx = 0 : idx = 1;  //give when exclusive

  int kpttrig = (hpt_triggerbin->FindBin(pt)) - 1;
  
  if(istrg)
    {
      if(isGen){
	(evt->pVect_trg[0]).push_back(pvector);
	(evt->chgVect_trg[0]).push_back(charge);
	(evt->effVect_trg[0]).push_back(1.0);
	nTrkTot_trgGen += 1.;
	if (charge > 0)
	  {
	    nTrkTot_trgGen_Plus += 1.;
	  }//----positive trigger
	if (charge < 0)
	  {
	    nTrkTot_trgGen_Minus += 1.;
	  }//----Negative trigger

	hMultTrg_ptbin[kpttrig]->AddBinContent(1,1.0);

      }
      else{
	if(isQAhisto){
	  hEtaTrk_trg->Fill(eta);
	  hPtTrk_trg->Fill(pt);
	  hPhiTrk_trg->Fill(phi);
	  hPtTrk_trg_check->Fill(pt);
	  //corrected----
	  hEtaTrk_trgCorrtd->Fill(eta, EffValue[idx]);
	  hPtTrk_trgCorrtd->Fill(pt, EffValue[idx]);
	  hPhiTrk_trgCorrtd->Fill(phi);
	  hPtTrk_trgCorrtd_check->Fill(pt, EffValue[idx]);
	}//QA--
	//std::cout<<" pt value=" << pt <<std::endl;
	(evt->pVect_trg[1]).push_back(pvector);
	(evt->chgVect_trg[1]).push_back(charge);
	(evt->effVect_trg[1]).push_back(1.0/EffValue[idx]);
	nTrkTot_trg       += 1.;
	nTrkTot_trgCorrtd += EffValue[idx];
		
	hMultTrg_ptbin[kpttrig]->AddBinContent(2, 1.0);
	hMultTrg_ptbin[kpttrig]->AddBinContent(3, EffValue[idx]);

	if (charge > 0)
	  {
	    nTrkTot_trg_Plus += 1.0;
	    nTrkTot_trgCorrtd_Plus += EffValue[idx];
	  }//--positive trigger
	if (charge < 0)
          {
	    nTrkTot_trg_Minus += 1.0;
            nTrkTot_trgCorrtd_Minus += EffValue[idx];
          }//--Negative trigger 
      }
      
    }//if trg---
  else  
    {
      if(isGen){
	(evt->pVect_ass[0]).push_back(pvector);
	(evt->chgVect_ass[0]).push_back(charge);
	(evt->effVect_ass[0]).push_back(1.0);
	nTrkTot_assGen  += 1.;
      }
      else{
	if(isQAhisto){
	  hPtTrk_ass->Fill(pt);
	  hEtaTrk_ass->Fill(eta);
	  hPhiTrk_ass->Fill(phi);
	  hPtTrk_ass_check->Fill(pt);


	  hPtTrk_assCorrtd->Fill(pt, EffValue[idx]);
	  hEtaTrk_assCorrtd->Fill(eta, EffValue[idx]);
	  hPhiTrk_assCorrtd->Fill(phi);
	  hPtTrk_assCorrtd_check->Fill(pt, EffValue[idx]);

	}
	
	(evt->pVect_ass[1]).push_back(pvector);
	(evt->chgVect_ass[1]).push_back(charge);
	(evt->effVect_ass[1]).push_back(1.0/EffValue[idx]);
	nTrkTot_ass       += 1.;
	nTrkTot_assCorrtd += EffValue[idx];
      }
      
    }//else asso--
  
}

//--------------------------------------------------------------------------------------
double AnaTwoPC::GetDeltaEta(double eta_trg, double eta_ass)
  
{
  double deltaEta = eta_ass - eta_trg;
  //double deltaEta = eta_trg - eta_ass;
  return deltaEta;
}

double AnaTwoPC::GetDeltaPhi(double phi_trg, double phi_ass)
{
  //double deltaPhi = phi_trg - phi_ass;
  double deltaPhi = phi_ass - phi_trg;
  
  if(deltaPhi > 1.5*TMath::Pi())
    deltaPhi = deltaPhi - 2.0*TMath::Pi();
  
  else if(deltaPhi < -1.0*TMath::Pi() / 2.0)
    deltaPhi = deltaPhi + 2.0*TMath::Pi();
  
  return deltaPhi;
  
  
}

double AnaTwoPC::GetDPhiStar(double phi1, double pt1, int charge1, double phi2, double pt2, int charge2, double radius, double bSign)
{
  // calculates dphistar
  double dphistar = phi1 - phi2 - charge1*bSign*TMath::ASin(0.003*radius / pt1) + charge2*bSign*TMath::ASin(0.003*radius / pt2);
  
  static const double kPi = TMath::Pi();
  
  
    
  
  if (dphistar > kPi)
    dphistar = kPi * 2.0 - dphistar;
  if (dphistar < -kPi)
    dphistar = -kPi * 2.0 - dphistar;
  if (dphistar > kPi) // might look funny but is needed
    dphistar = kPi * 2.0 - dphistar;
  
  return dphistar;
}


void AnaTwoPC::FillHistsSignal(int ievt, bool isGen)
{
  int jj;
  isGen ? jj = 0 : jj = 1;
  
  unsigned int ntrgsize = evtVec[ievt].pVect_trg[jj].size();
  unsigned int nasssize = evtVec[ievt].pVect_ass[jj].size();
  double nMult_corr_trg = evtVec[ievt].nMultCorrVect_trg[jj];
 
  for( unsigned int itrg = 0; itrg < ntrgsize; itrg++ )
    {
      TLorentzVector pvector_trg = (evtVec[ievt].pVect_trg[jj])[itrg];
      double effweight_trg       = (evtVec[ievt].effVect_trg[jj])[itrg];
      int chg_trg                = (evtVec[ievt].chgVect_trg[jj])[itrg];
      double eta_trg             = pvector_trg.Eta();
      double phi_trg             = pvector_trg.Phi();
      double pt_trg              = pvector_trg.Pt();
      double px_trg              = pvector_trg.Px();
      double py_trg              = pvector_trg.Py();
      double pz_trg              = pvector_trg.Pz();

      double p_trg = std::sqrt(px_trg*px_trg + py_trg*py_trg + pz_trg*pz_trg);
      
      

      hPTdistTrg ->Fill(pt_trg);
      double avgpTtrg = hPTdistTrg->GetMean();
      //std::cout <<"pt_trg :" << pt_trg << std::endl;
      double dpt1= pt_trg - avgpTtrg;
      //std::cout<<" pt_trg value=" << pt_trg <<std::endl;
      
      int kpttrig = (hpt_triggerbin->FindBin(pt_trg)) - 1;
      
      hptTrg_ptbin[kpttrig]->Fill(pt_trg);

      for( unsigned int jass = 0; jass < nasssize; jass++ )
	{
	  TLorentzVector pvector_ass = (evtVec[ievt].pVect_ass[jj])[jass];
	  double effweight_ass       = (evtVec[ievt].effVect_ass[jj])[jass];
	  int chg_ass                = (evtVec[ievt].chgVect_ass[jj])[jass];
	  double eta_ass             = pvector_ass.Eta();
	  double phi_ass             = pvector_ass.Phi();
	  double pt_ass              = pvector_ass.Pt();
	  double px_ass              = pvector_ass.Px();
	  double py_ass              = pvector_ass.Py();
	  double pz_ass              = pvector_ass.Pz();

	  double deltaPhi            = GetDeltaPhi(phi_trg, phi_ass);
	  double deltaPhi2           = GetDeltaPhi(phi_ass, phi_trg);
	  double deltaEta            = GetDeltaEta(eta_trg, eta_ass);
	  
	  hPTdistAsso->Fill(pt_ass);
	  double avgAsso = hPTdistAsso->GetMean();
	  //std::cout << "pt_ass :"<< pt_ass << std::endl;
	  double dpt2= pt_ass - avgAsso;
	  //Skip the loop when trg, ass particles are the same
	  if( deltaEta == 0.0  &&  deltaPhi == 0.0 && deltaPhi2 == 0.0 && pt_trg == pt_ass) continue;
	  //------------------------Just for checking---
	  
	  
	  /*
	  TLorentzVector vec1;
	  TLorentzVector vec2;
	  Double_t cosa = TMath::Abs(vec1.Px()*vec2.Px() + vec1.Py()*vec2.Py() + vec1.Pz()*vec2.Pz())/(vec1.P()*vec2.P());
	  Double_t deltapt = TMath::Abs(vec1.Pt() - vec2.Pt());
	  //if ((cosa > 0.99999) && (deltapt < 0.015)) continue;
	  */

	  double p_ass = std::sqrt(px_ass*px_ass + py_ass*py_ass + pz_ass*pz_ass);

	  //if (pt_trg <= pt_ass) continue;

	  //Track Splitting and Track Merging                                                                                                                                                                                                                                          
	  double cos_cut = 0.99999;
	  double dpt_cut = 0.015;
	  Double_t cosa = TMath::Abs(px_ass*px_trg + py_ass*py_trg + pz_ass*pz_trg)/(p_ass*p_trg);
	  Double_t deltapt = TMath::Abs(pt_ass - pt_trg);
	  //if((cosa > cos_cut) && (deltapt < dpt_cut))continue;

	  //double DptDpt = dpt1 * dpt2;
	  double DptDpt = 1.0;
	  //std::cout << "DptDpt: " << DptDpt << std::endl;
	  double effweight = effweight_trg * effweight_ass ;
	  double absDelEta = TMath::Abs(deltaEta);
	  
	  if(isGen){
	    hSignal_all_GEN->Fill( fabs(deltaEta),deltaPhi,  1.0*DptDpt/4.0 / effweight);
	    hSignal_all_GEN->Fill(-fabs(deltaEta),deltaPhi,  1.0*DptDpt/4.0 / effweight);
	    hSignal_all_GEN->Fill( fabs(deltaEta),deltaPhi2, 1.0*DptDpt/4.0 / effweight);
	    hSignal_all_GEN->Fill(-fabs(deltaEta),deltaPhi2, 1.0*DptDpt/4.0 / effweight);

	    hSignal_all_ptbin_GEN[kpttrig]->Fill( fabs(deltaEta),deltaPhi,  1.0*DptDpt/4.0 / effweight);
	    hSignal_all_ptbin_GEN[kpttrig]->Fill(-fabs(deltaEta),deltaPhi,  1.0*DptDpt/4.0 / effweight);
	    hSignal_all_ptbin_GEN[kpttrig]->Fill( fabs(deltaEta),deltaPhi2, 1.0*DptDpt/4.0 / effweight);
	    hSignal_all_ptbin_GEN[kpttrig]->Fill(-fabs(deltaEta),deltaPhi2, 1.0*DptDpt/4.0 / effweight);

	    
	  }
	  else{
	  hSignal_all->Fill( fabs(deltaEta),deltaPhi,  1.0*DptDpt/4.0);
	  hSignal_all->Fill(-fabs(deltaEta),deltaPhi,  1.0*DptDpt/4.0);
	  hSignal_all->Fill( fabs(deltaEta),deltaPhi2, 1.0*DptDpt/4.0);
	  hSignal_all->Fill(-fabs(deltaEta),deltaPhi2, 1.0*DptDpt/4.0);

	  hSignal_all_corr->Fill( fabs(deltaEta),deltaPhi,  1.0*DptDpt/4.0 / effweight);
	  hSignal_all_corr->Fill(-fabs(deltaEta),deltaPhi,  1.0*DptDpt/4.0 / effweight);
	  hSignal_all_corr->Fill( fabs(deltaEta),deltaPhi2, 1.0*DptDpt/4.0 / effweight);
	  hSignal_all_corr->Fill(-fabs(deltaEta),deltaPhi2, 1.0*DptDpt/4.0 / effweight);
	  
	  hSignal_all_ptbin[kpttrig]->Fill( fabs(deltaEta),deltaPhi,  1.0*DptDpt/4.0);
          hSignal_all_ptbin[kpttrig]->Fill(-fabs(deltaEta),deltaPhi,  1.0*DptDpt/4.0);
          hSignal_all_ptbin[kpttrig]->Fill( fabs(deltaEta),deltaPhi2, 1.0*DptDpt/4.0);
          hSignal_all_ptbin[kpttrig]->Fill(-fabs(deltaEta),deltaPhi2, 1.0*DptDpt/4.0);

          hSignal_all_ptbin_corr[kpttrig]->Fill( fabs(deltaEta),deltaPhi,  1.0*DptDpt/4.0 / effweight);
          hSignal_all_ptbin_corr[kpttrig]->Fill(-fabs(deltaEta),deltaPhi,  1.0*DptDpt/4.0 / effweight);
          hSignal_all_ptbin_corr[kpttrig]->Fill( fabs(deltaEta),deltaPhi2, 1.0*DptDpt/4.0 / effweight);
          hSignal_all_ptbin_corr[kpttrig]->Fill(-fabs(deltaEta),deltaPhi2, 1.0*DptDpt/4.0 / effweight);
	  
	  }



	  /*
	  //std::cout<<"deltaEta value=" << deltaEta <<std::endl;
	  //Fill and symmetrize the distribution	  
	  if( chg_trg > 0 && chg_ass > 0)
	  {
	  
	  if(isGen){
	  
	  
	  hSignalPPGen->Fill( absDelEta, deltaPhi, 1.0*DptDpt/4.0/effweight );
	  hSignalPPGen->Fill( -1.*absDelEta, deltaPhi, 1.0*DptDpt/4.0/effweight );
	  hSignalPPGen->Fill( absDelEta, deltaPhi2, 1.0*DptDpt/4.0/effweight);
	  hSignalPPGen->Fill( -1.*absDelEta, deltaPhi2, 1.0*DptDpt/4.0/effweight ); 
	  
	  }
	  else{
	  hSignalPP->Fill( absDelEta, deltaPhi, 1.0*DptDpt/4.0 );
	  hSignalPP->Fill( -1.*absDelEta, deltaPhi, 1.0*DptDpt/4.0 );
	  hSignalPP->Fill( absDelEta, deltaPhi2, 1.0*DptDpt/4.0 );
	  hSignalPP->Fill( -1.*absDelEta, deltaPhi2, 1.0*DptDpt/4.0 );

	  hSignalPP_corr->Fill( absDelEta, deltaPhi, 1.0*DptDpt/4.0/effweight );
	  hSignalPP_corr->Fill( -1.*absDelEta, deltaPhi, 1.0*DptDpt/4.0/effweight );
	  hSignalPP_corr->Fill( absDelEta, deltaPhi2, 1.0*DptDpt/4.0/effweight);
	  hSignalPP_corr->Fill( -1.*absDelEta, deltaPhi2, 1.0*DptDpt/4.0/effweight );

	  hsig_PP_dphi_eff ->Fill(deltaPhi, 1./effweight);
	  }
	  }//+ve, +ve particle only 
	  else if( chg_trg > 0 && chg_ass < 0){
	    if(isGen){
	      hSignalPMGen->Fill( absDelEta, deltaPhi, 1.0*DptDpt/4.0/effweight );
	      hSignalPMGen->Fill( -1.*absDelEta, deltaPhi, 1.0*DptDpt/4.0/effweight );
	      hSignalPMGen->Fill( absDelEta, deltaPhi2, 1.0*DptDpt/4.0/effweight);
	      hSignalPMGen->Fill( -1.*absDelEta, deltaPhi2, 1.0*DptDpt/4.0/effweight );
	    }
	    else{
	      //std::cout<<"plus minus trigger:"<<  nMult_corr_trg << std::endl;
	      hSignalPM->Fill( absDelEta, deltaPhi, 1.0*DptDpt/4.0 );
	      hSignalPM->Fill( -1.*absDelEta, deltaPhi, 1.0*DptDpt/4.0 );
	      hSignalPM->Fill( absDelEta, deltaPhi2, 1.0*DptDpt/4.0 );
	      hSignalPM->Fill( -1.*absDelEta, deltaPhi2, 1.0*DptDpt/4.0 );
	      //hsig_PM_dphi_eff ->Fill(deltaPhi, absDelEta, effweight);
	      // hcoszdptzPM->Fill(fabs(deltaEta), fabs(deltaPhi));
	     
	      hSignalPM_corr->Fill( absDelEta, deltaPhi, 1.0*DptDpt/4.0/effweight );
	      hSignalPM_corr->Fill( -1.*absDelEta, deltaPhi, 1.0*DptDpt/4.0/effweight );
	      hSignalPM_corr->Fill( absDelEta, deltaPhi2, 1.0*DptDpt/4.0/effweight);
	      hSignalPM_corr->Fill( -1.*absDelEta, deltaPhi2, 1.0*DptDpt/4.0/effweight );

	      hsig_PM_dphi_eff->Fill( deltaPhi, 1./effweight );
	      
	    }
	  }//+ve. -ve particle only
	  else if( chg_trg < 0 && chg_ass > 0){
	    if(isGen){
	      hSignalMPGen->Fill( absDelEta, deltaPhi, 1.0*DptDpt/4.0/effweight );
	      hSignalMPGen->Fill( -1.*absDelEta, deltaPhi, 1.0*DptDpt/4.0/effweight );
	      hSignalMPGen->Fill( absDelEta, deltaPhi2, 1.0*DptDpt/4.0/effweight);
	      hSignalMPGen->Fill( -1.*absDelEta, deltaPhi2, 1.0*DptDpt/4.0/effweight );
	    }
	    else
	      {
		//std::cout<<"minus plus trigger:"<<  nMult_corr_trg << std::endl;
		hSignalMP->Fill( absDelEta, deltaPhi, 1.0*DptDpt/4.0 );
		hSignalMP->Fill( -1.*absDelEta, deltaPhi, 1.0*DptDpt/4.0 );
		hSignalMP->Fill( absDelEta, deltaPhi2, 1.0*DptDpt/4.0 );
		hSignalMP->Fill( -1.*absDelEta, deltaPhi2, 1.0*DptDpt/4.0 );
		//hsig_MP_dphi_eff ->Fill(deltaPhi,  effweight);

		hSignalMP_corr->Fill( absDelEta, deltaPhi, 1.0*DptDpt/4.0/effweight );
		hSignalMP_corr->Fill( -1.*absDelEta, deltaPhi, 1.0*DptDpt/4.0/effweight );
		hSignalMP_corr->Fill( absDelEta, deltaPhi2, 1.0*DptDpt/4.0/effweight);
		hSignalMP_corr->Fill( -1.*absDelEta, deltaPhi2, 1.0*DptDpt/4.0/effweight );


		hcoszdptzMP->Fill(fabs(deltaEta), fabs(deltaPhi));
	      }
	  }//-ve, +ve particle only
	  else if(chg_trg < 0 && chg_ass < 0)
	    {
	      
	      if(isGen){
		
		hSignalMMGen->Fill( absDelEta, deltaPhi, 1.0*DptDpt/4.0/effweight );
		hSignalMMGen->Fill( -1.*absDelEta, deltaPhi, 1.0*DptDpt/4.0/effweight );
		hSignalMMGen->Fill( absDelEta, deltaPhi2, 1.0*DptDpt/4.0/effweight);
		hSignalMMGen->Fill( -1.*absDelEta, deltaPhi2, 1.0*DptDpt/4.0/effweight );
	      }
	      else{
		//std::cout<<"minus minus trigger:"<<  nMult_corr_trg << std::endl;
		hSignalMM->Fill( absDelEta, deltaPhi, 1.0*DptDpt/4.0 );
		hSignalMM->Fill( -1.*absDelEta, deltaPhi, 1.0*DptDpt/4.0 );
		hSignalMM->Fill( absDelEta, deltaPhi2, 1.0*DptDpt/4.0 );
		hSignalMM->Fill( -1.*absDelEta, deltaPhi2, 1.0*DptDpt/4.0 );


		hSignalMM_corr->Fill( absDelEta, deltaPhi, 1.0*DptDpt/4.0/effweight );
		hSignalMM_corr->Fill( -1.*absDelEta, deltaPhi, 1.0*DptDpt/4.0/effweight );
		hSignalMM_corr->Fill( absDelEta, deltaPhi2, 1.0*DptDpt/4.0/effweight);
		hSignalMM_corr->Fill( -1.*absDelEta, deltaPhi2, 1.0*DptDpt/4.0/effweight );

		//hsig_MM_dphi_eff ->Fill(deltaPhi, effweight);
		hcoszdptzMM->Fill(fabs(deltaEta), fabs(deltaPhi));
	      }
	      
	    }//-ve, -ve particle only
*/	  




	}//nass----
      
    }//ntrg----
}//--ievt

//======================================================================================
void AnaTwoPC::FillHistsBackground(int ievt_trg, int jevt_ass, bool isGen)
{
  
  if( evtVec[ievt_trg].run   ==  evtVec[jevt_ass].run &&
      evtVec[ievt_trg].event == evtVec[jevt_ass].event )
  {
      std::cout << "Event are the same. Skipping it" << std::endl;
      return;
  }

  int kk;
  isGen ? kk = 0 : kk = 1;
  
  unsigned int ntrgsize = evtVec[ievt_trg].pVect_trg[kk].size();
  unsigned int nasssize = evtVec[jevt_ass].pVect_ass[kk].size();
  double nMult_corr_trg = evtVec[ievt_trg].nMultCorrVect_trg[kk];
  //std::cout<<" ntrgsize value=" << ntrgsize <<std::endl;
  for( unsigned int itrg = 0; itrg < ntrgsize; itrg++ )
    {
      
      TLorentzVector pvector_trg = (evtVec[ievt_trg].pVect_trg[kk])[itrg];
      double effweight_trg       = (evtVec[ievt_trg].effVect_trg[kk])[itrg];
      int chg_trg                = (evtVec[ievt_trg].chgVect_trg[kk])[itrg];
      double eta_trg             = pvector_trg.Eta();
      double phi_trg             = pvector_trg.Phi();
      double pt_trg              = pvector_trg.Pt();
      double px_trg              = pvector_trg.Px();
      double py_trg              = pvector_trg.Py();
      double pz_trg              = pvector_trg.Pz();

      double p_trg = std::sqrt(px_trg*px_trg + py_trg*py_trg + pz_trg*pz_trg);
      
      hPTdistTrgbkg->Fill(pt_trg);
      double avgpTtrg = hPTdistTrg->GetMean();
      double dpt1= pt_trg - avgpTtrg;
      
      int kpttrig = (hpt_triggerbin->FindBin(pt_trg)) - 1;
      
      
      for( unsigned int jass = 0; jass < nasssize; jass++ )
	{
	  TLorentzVector pvector_ass = (evtVec[jevt_ass].pVect_ass[kk])[jass];
	  double effweight_ass       = (evtVec[jevt_ass].effVect_ass[kk])[jass];
	  int chg_ass                = (evtVec[jevt_ass].chgVect_ass[kk])[jass];
	  double eta_ass             = pvector_ass.Eta();
	  double phi_ass             = pvector_ass.Phi();
	  double pt_ass              = pvector_ass.Pt();
	  double px_ass              = pvector_ass.Px();
          double py_ass              = pvector_ass.Py();
          double pz_ass              = pvector_ass.Pz();


	  double deltaPhi            = GetDeltaPhi( phi_trg, phi_ass );
	  double deltaPhi2           = GetDeltaPhi( phi_ass, phi_trg);
	  double deltaEta            = GetDeltaEta( eta_trg, eta_ass );
	  
	  hPTdistAssobkg->Fill(pt_ass);
          double avgAsso = hPTdistAsso->GetMean();
	  double dpt2= pt_ass - avgAsso;


	  double p_ass = std::sqrt(px_ass*px_ass + py_ass*py_ass + pz_ass*pz_ass);

          //if (pt_trg <= pt_ass) continue;

          //Track Splitting and Track Merging                                                                                                                                                                                                                                              
          double cos_cut = 0.99999;
          double dpt_cut = 0.015;
          Double_t cosa = TMath::Abs(px_ass*px_trg + py_ass*py_trg + pz_ass*pz_trg)/(p_ass*p_trg);
          Double_t deltapt = TMath::Abs(pt_ass - pt_trg);
          //if((cosa > cos_cut) && (deltapt < dpt_cut))continue;


	  /*
	  TLorentzVector vec1;
          TLorentzVector vec2;
          Double_t cosa = TMath::Abs(vec1.Px()*vec2.Px() + vec1.Py()*vec2.Py() + vec1.Pz()*vec2.Pz())/(vec1.P()*vec2.P());
          Double_t deltapt = TMath::Abs(vec1.Pt() - vec2.Pt());
	  //if ((cosa > 0.99999) && (deltapt < 0.015)) continue;
	  */ //double DptDpt = dpt1 * dpt2;
	  double DptDpt = 1.0;

	  if( deltaEta == 0.0  &&  deltaPhi == 0.0 && deltaPhi2 == 0.0  && pt_trg == pt_ass) continue;
	
	  //Total weight
	  
	  double effweight = effweight_trg * effweight_ass;
	  
	  double absDelEta = TMath::Abs(deltaEta);
	  
	  
	  
	  if(isGen){

	    hBackground_allGen->Fill( absDelEta,     deltaPhi,   1.0/4.0/effweight );
	    hBackground_allGen->Fill( -1.*absDelEta, deltaPhi,   1.0/4.0/effweight );
	    hBackground_allGen->Fill( absDelEta,     deltaPhi2,  1.0/4.0/effweight );
	    hBackground_allGen->Fill( -1.*absDelEta, deltaPhi2,  1.0/4.0/effweight );

	    hBackground_all_ptbin_Gen[kpttrig]->Fill( absDelEta,     deltaPhi,   1.0/4.0/effweight );
	    hBackground_all_ptbin_Gen[kpttrig]->Fill( -1.*absDelEta, deltaPhi,   1.0/4.0/effweight );
	    hBackground_all_ptbin_Gen[kpttrig]->Fill( absDelEta,     deltaPhi2,  1.0/4.0/effweight );
	    hBackground_all_ptbin_Gen[kpttrig]->Fill( -1.*absDelEta, deltaPhi2,  1.0/4.0/effweight );

	  }
	  else{
	    hBackground_all->Fill( absDelEta, deltaPhi,      1.0/4.0 );
	    hBackground_all->Fill( -1.*absDelEta, deltaPhi,  1.0/4.0 );
	    hBackground_all->Fill( absDelEta, deltaPhi2,     1.0/4.0 );
	    hBackground_all->Fill( -1.*absDelEta, deltaPhi2, 1.0/4.0 );

	    hBackground_all_corr->Fill( absDelEta, deltaPhi,      1.0/4.0/effweight );
	    hBackground_all_corr->Fill( -1.*absDelEta, deltaPhi,  1.0/4.0/effweight );
	    hBackground_all_corr->Fill( absDelEta, deltaPhi2,     1.0/4.0/effweight );
	    hBackground_all_corr->Fill( -1.*absDelEta, deltaPhi2, 1.0/4.0/effweight );

	    hBackground_all_ptbin[kpttrig]->Fill( absDelEta, deltaPhi,      1.0/4.0 );
	    hBackground_all_ptbin[kpttrig]->Fill( -1.*absDelEta, deltaPhi,  1.0/4.0 );
	    hBackground_all_ptbin[kpttrig]->Fill( absDelEta, deltaPhi2,     1.0/4.0 );
	    hBackground_all_ptbin[kpttrig]->Fill( -1.*absDelEta, deltaPhi2, 1.0/4.0 );

	    hBackground_all_ptbin_corr[kpttrig]->Fill( absDelEta, deltaPhi,      1.0/4.0/effweight );
	    hBackground_all_ptbin_corr[kpttrig]->Fill( -1.*absDelEta, deltaPhi,  1.0/4.0/effweight );
	    hBackground_all_ptbin_corr[kpttrig]->Fill( absDelEta, deltaPhi2,     1.0/4.0/effweight );
	    hBackground_all_ptbin_corr[kpttrig]->Fill( -1.*absDelEta, deltaPhi2, 1.0/4.0/effweight );
	  }
	

	  /*
	  if( chg_trg > 0 && chg_ass > 0)
	    {
	      
	      if(isGen){
		hBackgroundPPGen->Fill( absDelEta, deltaPhi, 1.0/4.0/effweight );
		hBackgroundPPGen->Fill( -1.*absDelEta, deltaPhi, 1.0/4.0/effweight );
		hBackgroundPPGen->Fill( absDelEta, deltaPhi2, 1.0/4.0/effweight );
		hBackgroundPPGen->Fill( -1.*absDelEta, deltaPhi2, 1.0/4.0/effweight ); 
		  }
	      else{
		hBackgroundPP->Fill( absDelEta, deltaPhi, 1.0/4.0 );
		hBackgroundPP->Fill( -1.*absDelEta, deltaPhi, 1.0/4.0 );
		hBackgroundPP->Fill( absDelEta, deltaPhi2, 1.0/4.0 );
		hBackgroundPP->Fill( -1.*absDelEta, deltaPhi2, 1.0/4.0 ); 

		hBackgroundPP_corr->Fill( absDelEta, deltaPhi, 1.0/4.0/effweight );
		hBackgroundPP_corr->Fill( -1.*absDelEta, deltaPhi, 1.0/4.0/effweight );
		hBackgroundPP_corr->Fill( absDelEta, deltaPhi2, 1.0/4.0/effweight );
		hBackgroundPP_corr->Fill( -1.*absDelEta, deltaPhi2, 1.0/4.0/effweight ); 
		
		hbkg_PP_dphi_eff ->Fill(deltaPhi,  1.0/effweight);
	      }
	      
	    }
	  else if( chg_trg > 0 && chg_ass < 0){
	    if(isGen){
	      hBackgroundPMGen->Fill( absDelEta, deltaPhi, 1.0/4.0/effweight  );
	      hBackgroundPMGen->Fill( -1.*absDelEta, deltaPhi, 1.0/4.0/effweight );
	      hBackgroundPMGen->Fill( absDelEta, deltaPhi2, 1.0/4.0/effweight );
	      hBackgroundPMGen->Fill( -1.*absDelEta, deltaPhi2, 1.0/4.0/effweight ); 
	    }
	    else{
	      hBackgroundPM->Fill( absDelEta, deltaPhi, 1.0/4.0  );
	      hBackgroundPM->Fill( -1.*absDelEta, deltaPhi, 1.0/4.0 );
	      hBackgroundPM->Fill( absDelEta, deltaPhi2, 1.0/4.0 );
	      hBackgroundPM->Fill( -1.*absDelEta, deltaPhi2, 1.0/4.0 ); 

	      hBackgroundPM_corr->Fill( absDelEta, deltaPhi, 1.0/4.0/effweight  );
	      hBackgroundPM_corr->Fill( -1.*absDelEta, deltaPhi, 1.0/4.0/effweight );
	      hBackgroundPM_corr->Fill( absDelEta, deltaPhi2, 1.0/4.0/effweight );
	      hBackgroundPM_corr->Fill( -1.*absDelEta, deltaPhi2, 1.0/4.0/effweight ); 


	      hbkg_PM_dphi_eff ->Fill(deltaPhi, 1.0/effweight);
	    }
	  }
	  else if( chg_trg < 0 && chg_ass > 0){
	    if(isGen){
	      hBackgroundMPGen->Fill( absDelEta, deltaPhi, 1.0/4.0/effweight );
	      hBackgroundMPGen->Fill( -1.*absDelEta, deltaPhi, 1.0/4.0/effweight );
	      hBackgroundMPGen->Fill( absDelEta, deltaPhi2, 1.0/4.0/effweight );
	      hBackgroundMPGen->Fill( -1.*absDelEta, deltaPhi2, 1.0/4.0/effweight ); 
	    }
	    else{
	      hBackgroundMP->Fill( absDelEta, deltaPhi, 1.0/4.0 );
	      hBackgroundMP->Fill( -1.*absDelEta, deltaPhi, 1.0/4.0 );
	      hBackgroundMP->Fill( absDelEta, deltaPhi2, 1.0/4.0 );
	      hBackgroundMP->Fill( -1.*absDelEta, deltaPhi2, 1.0/4.0 ); 

	      hBackgroundMP_corr->Fill( absDelEta, deltaPhi, 1.0/4.0/effweight );
	      hBackgroundMP_corr->Fill( -1.*absDelEta, deltaPhi, 1.0/4.0/effweight );
	      hBackgroundMP_corr->Fill( absDelEta, deltaPhi2, 1.0/4.0/effweight );
	      hBackgroundMP_corr->Fill( -1.*absDelEta, deltaPhi2, 1.0/4.0/effweight ); 


	      hbkg_MP_dphi_eff ->Fill(deltaPhi, 1.0/effweight);
	    }
	  }
	  else if( chg_trg < 0 && chg_ass < 0){
	    
	    
	    if(isGen){
	      hBackgroundMMGen->Fill( absDelEta, deltaPhi, 1.0/4.0/effweight );
	      hBackgroundMMGen->Fill( -1.*absDelEta, deltaPhi, 1.0/4.0/effweight );
	      hBackgroundMMGen->Fill( absDelEta, deltaPhi2, 1.0/4.0/effweight );
	      hBackgroundMMGen->Fill( -1.*absDelEta, deltaPhi2, 1.0/4.0/effweight ); 
	    }
	    else{
	      hBackgroundMM->Fill( absDelEta, deltaPhi, 1.0/4.0 );
	      hBackgroundMM->Fill( -1.*absDelEta, deltaPhi, 1.0/4.0 );
	      hBackgroundMM->Fill( absDelEta, deltaPhi2, 1.0/4.0 );
	      hBackgroundMM->Fill( -1.*absDelEta, deltaPhi2, 1.0/4.0 ); 

	      hBackgroundMM_corr->Fill( absDelEta, deltaPhi, 1.0/4.0/effweight );
	      hBackgroundMM_corr->Fill( -1.*absDelEta, deltaPhi, 1.0/4.0/effweight );
	      hBackgroundMM_corr->Fill( absDelEta, deltaPhi2, 1.0/4.0/effweight );
	      hBackgroundMM_corr->Fill( -1.*absDelEta, deltaPhi2, 1.0/4.0/effweight ); 

	      hbkg_MM_dphi_eff ->Fill(deltaPhi, 1.0/effweight);
	    }
	    
	  }//--- -ve -ve only
	  
	  */


	}//jass--
    }//trg
}//----i,j event


//-------------------------------------------
double AnaTwoPC::getEff(const TLorentzVector pvector, int evtclass)
{
   double effweight = 1.0;
   for(int i_cf=0; i_cf < static_cast<int>(effCorrBinMin.size()); i_cf++) if(evtclass >= effCorrBinMin[i_cf] && evtclass < effCorrBinMax[i_cf]) {
       effweight = heff[i_cf]->GetBinContent(
					      heff[i_cf]->GetXaxis()->FindBin(pvector.Eta()),
					      heff[i_cf]->GetYaxis()->FindBin(pvector.Pt())
					      );
     }
   return effweight;
   }

 //------------------------------------------------

  
//}
//}

//define this as a plug-in
DEFINE_FWK_MODULE(AnaTwoPC);
