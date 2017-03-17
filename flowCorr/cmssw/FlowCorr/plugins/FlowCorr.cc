// -*- C++ -*-
//
// Package:    Analysis/FlowCorr
// Class:      FlowCorr
// 
/**\class FlowCorr FlowCorr.cc Analysis/FlowCorr/plugins/FlowCorr.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Shengquan Tuo
//         Created:  Fri, 22 Jul 2016 19:53:25 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "DataFormats/HeavyIonEvent/interface/Centrality.h"
#include "DataFormats/HeavyIonEvent/interface/EvtPlane.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "SimDataFormats/HiGenData/interface/GenHIEvent.h"
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/CaloTowers/interface/CaloTowerCollection.h"

#include "Analysis/FlowCorr/plugins/FlowCorr.h"

//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

class FlowCorr : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit FlowCorr(const edm::ParameterSet&);
      ~FlowCorr();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      // ----------member data ---------------------------
  edm::EDGetTokenT<reco::Centrality> CentralityTag_;
  edm::EDGetTokenT<int> CentralityBinTag_;
  edm::EDGetTokenT<reco::EvtPlaneCollection> EvtPlaneTag_;
  edm::EDGetTokenT<reco::EvtPlaneCollection> EvtPlaneFlatTag_;
  edm::EDGetTokenT<edm::GenHIEvent> HiMCTag_;
  edm::EDGetTokenT<std::vector<reco::Vertex>> VertexTag_;
  //edm::EDGetTokenT<std::vector<reco::Track> > TrackTag_;
  edm::EDGetTokenT<vector<Track> > TrackTag_;
  std::string TrackQualityTag_;
  edm::EDGetTokenT<CaloTowerCollection>  TowerTag_;

  edm::Service<TFileService> fs;

  double trackPtMinCut_;
  double trackPtMaxCut_;
  double trackEtaCut_;
  double trackEtaMinCut_;
  double ptErrCut_;
  double dzRelCut_;
  double dxyRelCut_;
  double chi2nMax_;
  int nhitsMin_;
  std::vector<int> algoParameters_;
  double vertexZMin_;
  double vertexZMax_;
  double hfEtaMin_;
  double hfEtaMax_;

  int evtPlaneLevel_;


};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
FlowCorr::FlowCorr(const edm::ParameterSet& iConfig) :
  CentralityTag_(consumes<reco::Centrality>(iConfig.getParameter<edm::InputTag>("CentralitySrc"))),
  CentralityBinTag_(consumes<int>(iConfig.getParameter<edm::InputTag>("CentralityBinSrc"))),
  EvtPlaneTag_(consumes<reco::EvtPlaneCollection>(iConfig.getParameter<edm::InputTag>("EvtPlane"))),
  EvtPlaneFlatTag_(consumes<reco::EvtPlaneCollection>(iConfig.getParameter<edm::InputTag>("EvtPlaneFlat"))),
  HiMCTag_(consumes<edm::GenHIEvent>(iConfig.getParameter<edm::InputTag>("HiMC"))),
  VertexTag_(consumes<std::vector<reco::Vertex>>(iConfig.getParameter<edm::InputTag>("Vertex"))),
  //TrackTag_(consumes<std::vector<reco::Track>>(iConfig.getParameter<edm::InputTag>("Track"))),
  TrackTag_(consumes<vector<Track>>(iConfig.getParameter<edm::InputTag>("Track"))),
  TrackQualityTag_(iConfig.getUntrackedParameter<std::string>("TrackQuality","highPurity")),
  TowerTag_(consumes<CaloTowerCollection>(iConfig.getParameter<edm::InputTag>("Tower"))),
  trackPtMinCut_(iConfig.getParameter<double>("trackPtMinCut")),
  trackPtMaxCut_(iConfig.getParameter<double>("trackPtMaxCut")),
  trackEtaCut_(iConfig.getParameter<double>("trackEtaCut")),
  trackEtaMinCut_(iConfig.getParameter<double>("trackEtaMinCut")),
  ptErrCut_(iConfig.getParameter<double>("ptErrCut")),
  dzRelCut_(iConfig.getParameter<double>("dzRelCut")),
  dxyRelCut_(iConfig.getParameter<double>("dxyRelCut")),
  chi2nMax_(iConfig.getParameter<double>("chi2nMax")),
  nhitsMin_(iConfig.getParameter<int>("nhitsMin")),
  algoParameters_(iConfig.getParameter<std::vector<int> >("algoParameters")),
  vertexZMin_(iConfig.getParameter<double>("vertexZMin")),
  vertexZMax_(iConfig.getParameter<double>("vertexZMax")),
  hfEtaMin_(iConfig.getParameter<double>("hfEtaMin")),
  hfEtaMax_(iConfig.getParameter<double>("hfEtaMax")),
  evtPlaneLevel_(iConfig.getParameter<int>("evtPlaneLevel"))
{
   //now do what ever initialization is needed
   usesResource("TFileService");

}


FlowCorr::~FlowCorr()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
FlowCorr::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

    edm::Handle<int> cbin_;
    iEvent.getByToken(CentralityBinTag_,cbin_);
    int hiBin = *cbin_;
    hCent->Fill(hiBin);
    edm::Handle<reco::Centrality> centrality;
    iEvent.getByToken(CentralityTag_, centrality);
    hHF->Fill(centrality->EtHFtowerSum());
       int ibin=-1;
       for(int j=0;j<nCentBin;j++)
       if(hiBin>=2*cBin[j]&&hiBin<2*cBin[j+1])
         ibin=j;
       if(ibin<0 || ibin==nCentBin) return;

    edm::Handle<reco::EvtPlaneCollection> evtPlanes;
    iEvent.getByToken(EvtPlaneTag_,evtPlanes);
    if(evtPlanes.isValid()){
      //6=HFm2, 7=HFp2, 8=HF2, 9=trackmid2
      //13=HFm3, 14=HFp3, 15=HF3, 16=trackmid3
      double anglem2 = (*evtPlanes)[6].angle(evtPlaneLevel_);
      hAngle->Fill(anglem2);        
    }
    edm::Handle<reco::EvtPlaneCollection> evtPlanesFlat;
    iEvent.getByToken(EvtPlaneFlatTag_,evtPlanesFlat);
    if(evtPlanesFlat.isValid()){
      double anglem2Flat = (*evtPlanesFlat)[6].angle();
      hAngleFlat->Fill(anglem2Flat);
    }

    edm::Handle<std::vector<reco::Vertex>> vertex;
    iEvent.getByToken(VertexTag_, vertex);
    double vx=vertex->begin()->x();
    double vy=vertex->begin()->y();
    double vz=vertex->begin()->z();
    double vxError=vertex->begin()->xError();
    double vyError=vertex->begin()->yError();
    double vzError=vertex->begin()->zError();
    if(fabs(vz)<vertexZMin_ || fabs(vz)>vertexZMax_) return;
    hvz->Fill(vz);
    hvx->Fill(vx);
    hvy->Fill(vy);
   

     //edm::Handle<std::vector<reco::Track> tracks;
     //iEvent.getByToken(TrackTag_,tracks);
     int nTracks = 0;
     pVect_trkEtaPlus = new vector<TVector3>;
     pVect_trkEtaMinus = new vector<TVector3>;
     Handle<vector<Track>> tracks;
     iEvent.getByToken(TrackTag_, tracks);
     for(unsigned int i = 0 ; i < tracks->size(); ++i){
       const Track& track = (*tracks)[i];
       if(!track.quality(reco::TrackBase::qualityByName(TrackQualityTag_))) continue;
       if(track.charge() == 0) continue;
       //if(track.numberOfValidHits() < 11 ) continue;
       //double algoOffline = track.algo();
       //if(!(algoOffline==4 || algoOffline==6 || algoOffline==7 || algoOffline==5 || algoOffline==11)) continue;
       //if(track.normalizedChi2() / track.hitPattern().trackerLayersWithMeasurement() > 0.15 ) continue;       

       math::XYZPoint v1(vx,vy,vz);
       double dz= track.dz(v1);
       double dzsigma2 = track.dzError()*track.dzError()+vzError*vzError;
       double dxy= track.dxy(v1);
       double dxysigma2 = track.dxyError()*track.dxyError()+vxError*vyError;

       //if(track.pt()>trackPtMinCut_ && track.pt()<trackPtMaxCut_ && 
       //track.eta()<trackEtaCut_ && track.eta()>-1.0*trackEtaCut_ &&
       //track.ptError()/track.pt() < ptErrCut_ &&
       //dz*dz < dzRelCut_*dzRelCut_ * dzsigma2 &&
       //dxy*dxy < dxyRelCut_*dxyRelCut_ * dxysigma2 )

       double chi2n = track.normalizedChi2();
       double nlayers = track.hitPattern().trackerLayersWithMeasurement();
       chi2n = chi2n/nlayers;
       int nhits = track.numberOfValidHits();
       //int algo  = track.originalAlgo(); 
       int algo  = track.algo();
       int count = 0;
       for(unsigned i = 0; i < algoParameters_.size(); i++){
         if( algo == algoParameters_[i] ) count++;
       }
       int passalgocut = 1;
       if(track.pt()>2.4 && count == 0) passalgocut = 0;

       int passpixeltrackcuts = 0;
       if(track.pt()<2.4 && ( nhits == 3 || nhits == 4 || nhits == 5 || nhits == 6)) passpixeltrackcuts = 1;
       int passgeneraltrackcuts = 0;
       if(
         track.pt()>trackPtMinCut_ && track.pt()<trackPtMaxCut_ &&
         track.eta()<trackEtaCut_ && track.eta()>-1.0*trackEtaCut_ &&
         track.ptError()/track.pt() < ptErrCut_ &&
         dz*dz < dzRelCut_*dzRelCut_ * dzsigma2 &&
         dxy*dxy < dxyRelCut_*dxyRelCut_ * dxysigma2 &&
         chi2n < chi2nMax_ &&
         nhits > nhitsMin_ &&
         passalgocut == 1
       ) passgeneraltrackcuts = 1;

       if(passpixeltrackcuts==1 || passgeneraltrackcuts==1){
         hpt->Fill(track.pt());
         heta->Fill(track.eta());
         hphi->Fill(track.phi());
         nTracks++;
         TVector3 pvectorTrack;
         pvectorTrack.SetPtEtaPhi(track.pt(),track.eta(),track.phi());
         if(track.eta()>=trackEtaMinCut_) pVect_trkEtaPlus->push_back(pvectorTrack);
         if(track.eta()<-1*trackEtaMinCut_) pVect_trkEtaMinus->push_back(pvectorTrack);
       }
     }
     hNtrks->Fill(nTracks);

    double etHFtowerSumPlus = 0;
    double etHFtowerSumMinus = 0;
    double etHFtowerSum = 0;
    pVect_hfEtaPlus = new vector<TVector3>;
    pVect_hfEtaMinus = new vector<TVector3>;
    Handle<CaloTowerCollection> towers;
    iEvent.getByToken(TowerTag_,towers);
    for( size_t i = 0; i<towers->size(); ++ i){
       const CaloTower & tower = (*towers)[ i ];
       double etahf = tower.eta();
       bool isHF = tower.ietaAbs() > 29;
       TVector3 pvectorHF;
       pvectorHF.SetPtEtaPhi(tower.pt(),tower.eta(),tower.phi());
          if(isHF && etahf > 1.0*hfEtaMin_ && etahf < 1.0*hfEtaMax_ && tower.pt()>0.005 && tower.pt()<30.0){
            etHFtowerSumPlus += tower.pt();
            pVect_hfEtaPlus->push_back(pvectorHF);
          }
          if(isHF && etahf < -1.0*hfEtaMin_ && etahf > -1.0*hfEtaMax_ && tower.pt()>0.005 && tower.pt()<30.0){
            etHFtowerSumMinus += tower.pt();
            pVect_hfEtaMinus->push_back(pvectorHF);
          }
    }
    etHFtowerSum = etHFtowerSumPlus + etHFtowerSumMinus;
    hHFcal->Fill(etHFtowerSum);

// START Flow Analysis
       for(int j=0;j<nCentBin;j++){
           Qhf2p2Plus[j]=0;
           Qhf2p2Minus[j]=0;
           Qhf2p3Plus[j]=0;
           Qhf2p3Minus[j]=0;
           Qhf3p3Plus[j]=0;
           Qhf3p3Minus[j]=0;
           Qhf2p2p2Plus[j]=0;
           Qhf2p2p2Minus[j]=0;
           Qhf2p2p3Plus[j]=0;
           Qhf2p2p3Minus[j]=0;
           sumWPlus[j]=0.0;
           sumW2Plus[j]=0.0;
           sumW3Plus[j]=0.0;
           sumWMinus[j]=0.0;
           sumW2Minus[j]=0.0;
           sumW3Minus[j]=0.0;
         for(int iH=0; iH<nHarmonics; iH++){
           QhfPlus[j][iH]=0;   
           QhfMinus[j][iH]=0;
           QtrkPlus[j][iH]=0;
           QtrkMinus[j][iH]=0;
           QtrkAll[j][iH]=0;   
           QtrkPlus1[j][iH]=0;
           QtrkMinus1[j][iH]=0;
           for(int iPt=0; iPt<nPtBin; iPt++){
             QtrkPt[j][iH][iPt]=0;
             QtrkPt[j][iH][iPt]=0;
           }
         }
       }
       nEvent[ibin]+=1;

       hMultTrkEtaPlus->Fill((int)pVect_trkEtaPlus->size());
       hMultTrkEtaMinus->Fill((int)pVect_trkEtaMinus->size());
       hMultHFEtaPlus->Fill((int)pVect_hfEtaPlus->size());  
       hMultHFEtaMinus->Fill((int)pVect_hfEtaMinus->size()); 

       for(int iplus=0;iplus<(int)pVect_hfEtaPlus->size();iplus++){
         TVector3 pvector_hfPlus = (*pVect_hfEtaPlus)[iplus];
         double phi_hfPlus = pvector_hfPlus.Phi();
         double pt_hfPlus_weight = pvector_hfPlus.Pt();
         //double pt_hfPlus_weight = 1.0;  // unit weight;
         sumWPlus[ibin]+= pt_hfPlus_weight;
         sumW2Plus[ibin]+= pt_hfPlus_weight*pt_hfPlus_weight;
         sumW3Plus[ibin]+= pt_hfPlus_weight*pt_hfPlus_weight*pt_hfPlus_weight;
         Qhf2p2Plus[ibin]+= pt_hfPlus_weight*pt_hfPlus_weight * TComplex::Exp(TComplex(0,(2+2)*phi_hfPlus));
         Qhf2p3Plus[ibin]+= pt_hfPlus_weight*pt_hfPlus_weight * TComplex::Exp(TComplex(0,(2+3)*phi_hfPlus));
         Qhf3p3Plus[ibin]+= pt_hfPlus_weight*pt_hfPlus_weight * TComplex::Exp(TComplex(0,(3+3)*phi_hfPlus));
         Qhf2p2p2Plus[ibin]+= pt_hfPlus_weight*pt_hfPlus_weight*pt_hfPlus_weight * TComplex::Exp(TComplex(0,(2+2+2)*phi_hfPlus));
         Qhf2p2p3Plus[ibin]+= pt_hfPlus_weight*pt_hfPlus_weight*pt_hfPlus_weight * TComplex::Exp(TComplex(0,(2+2+3)*phi_hfPlus));
       }
       if(sumWPlus[ibin]>0){
          Qhf2p2Plus[ibin]=Qhf2p2Plus[ibin]/sumWPlus[ibin]/sumWPlus[ibin];
          Qhf2p3Plus[ibin]=Qhf2p3Plus[ibin]/sumWPlus[ibin]/sumWPlus[ibin];
          Qhf3p3Plus[ibin]=Qhf3p3Plus[ibin]/sumWPlus[ibin]/sumWPlus[ibin];
          Qhf2p2p2Plus[ibin]=Qhf2p2p2Plus[ibin]/sumWPlus[ibin]/sumWPlus[ibin]/sumWPlus[ibin];
          Qhf2p2p3Plus[ibin]=Qhf2p2p3Plus[ibin]/sumWPlus[ibin]/sumWPlus[ibin]/sumWPlus[ibin];
       }
       else{
          Qhf2p2Plus[ibin]=0;
          Qhf2p3Plus[ibin]=0;
          Qhf3p3Plus[ibin]=0;
          Qhf2p2p2Plus[ibin]=0;
          Qhf2p2p3Plus[ibin]=0;
       }
       for(int iminus=0;iminus<(int)pVect_hfEtaMinus->size();iminus++){
         TVector3 pvector_hfMinus = (*pVect_hfEtaMinus)[iminus];
         double phi_hfMinus = pvector_hfMinus.Phi();
         double pt_hfMinus_weight = pvector_hfMinus.Pt();
         //double pt_hfMinus_weight = 1.0;  // unit weight;
         sumWMinus[ibin]+= pt_hfMinus_weight;
         sumW2Minus[ibin]+= pt_hfMinus_weight*pt_hfMinus_weight;
         sumW3Minus[ibin]+= pt_hfMinus_weight*pt_hfMinus_weight*pt_hfMinus_weight;
         Qhf2p2Minus[ibin]+= pt_hfMinus_weight*pt_hfMinus_weight * TComplex::Exp(TComplex(0,(2+2)*phi_hfMinus));
         Qhf2p3Minus[ibin]+= pt_hfMinus_weight*pt_hfMinus_weight * TComplex::Exp(TComplex(0,(2+3)*phi_hfMinus));
         Qhf3p3Minus[ibin]+= pt_hfMinus_weight*pt_hfMinus_weight * TComplex::Exp(TComplex(0,(3+3)*phi_hfMinus));
         Qhf2p2p2Minus[ibin]+= pt_hfMinus_weight*pt_hfMinus_weight*pt_hfMinus_weight * TComplex::Exp(TComplex(0,(2+2+2)*phi_hfMinus));
         Qhf2p2p3Minus[ibin]+= pt_hfMinus_weight*pt_hfMinus_weight*pt_hfMinus_weight * TComplex::Exp(TComplex(0,(2+2+3)*phi_hfMinus));
       }
       if(sumWMinus[ibin]>0){
          Qhf2p2Minus[ibin]=Qhf2p2Minus[ibin]/sumWMinus[ibin]/sumWMinus[ibin];
          Qhf2p3Minus[ibin]=Qhf2p3Minus[ibin]/sumWMinus[ibin]/sumWMinus[ibin];
          Qhf3p3Minus[ibin]=Qhf3p3Minus[ibin]/sumWMinus[ibin]/sumWMinus[ibin];
          Qhf2p2p2Minus[ibin]=Qhf2p2p2Minus[ibin]/sumWMinus[ibin]/sumWMinus[ibin]/sumWMinus[ibin];
          Qhf2p2p3Minus[ibin]=Qhf2p2p3Minus[ibin]/sumWMinus[ibin]/sumWMinus[ibin]/sumWMinus[ibin];
       }
       else{
          Qhf2p2Minus[ibin]=0;
          Qhf2p3Minus[ibin]=0;
          Qhf3p3Minus[ibin]=0;
          Qhf2p2p2Minus[ibin]=0;
          Qhf2p2p3Minus[ibin]=0;
       }
       for(int iH=0; iH<nHarmonics; iH++){
         double sumwPlus=0;
         double sumwMinus=0;
         // choose hf or trk here (two lines): pVect_hfEtaPlus vs pVect_trkEtaPlus;
         for(int iplus=0;iplus<(int)pVect_hfEtaPlus->size();iplus++){
           TVector3 pvector_hfPlus = (*pVect_hfEtaPlus)[iplus];
           double phi_hfPlus = pvector_hfPlus.Phi();
           double pt_hfPlus_weight = pvector_hfPlus.Pt();
           //double pt_hfPlus_weight = 1.0;  // unit weight;
           sumwPlus+= pt_hfPlus_weight;
           QhfPlus[ibin][iH]+= pt_hfPlus_weight * TComplex::Exp(TComplex(0,(iH+1)*phi_hfPlus));
         }
         //if(sumwPlus>0) QhfPlus[ibin][iH]=QhfPlus[ibin][iH]/sumwPlus - TComplex(meanQxPlus[ibin][iH], meanQyPlus[ibin][iH]); //re-centering
         if(sumwPlus>0) QhfPlus[ibin][iH]=QhfPlus[ibin][iH]/sumwPlus;
         else QhfPlus[ibin][iH]=0;

         // choose hf or trk here (two lines): pVect_hfEtaMinus vs pVect_trkEtaMinus;
         for(int iminus=0;iminus<(int)pVect_hfEtaMinus->size();iminus++){
           TVector3 pvector_hfMinus = (*pVect_hfEtaMinus)[iminus];
           double phi_hfMinus = pvector_hfMinus.Phi();
           double pt_hfMinus_weight = pvector_hfMinus.Pt();
           //double pt_hfMinus_weight = 1.0;  // unit weight;
           sumwMinus+= pt_hfMinus_weight;
           QhfMinus[ibin][iH]+= pt_hfMinus_weight * TComplex::Exp(TComplex(0,(iH+1)*phi_hfMinus));
         }
         //if(sumwMinus>0) QhfMinus[ibin][iH]=QhfMinus[ibin][iH]/sumwMinus - TComplex(meanQxMinus[ibin][iH], meanQyMinus[ibin][iH]); //re-centering;
         if(sumwMinus>0) QhfMinus[ibin][iH]=QhfMinus[ibin][iH]/sumwMinus;
         else QhfMinus[ibin][iH]=0;

         ////trk
         double sumwtrkPlus=0;
         double sumwtrkMinus=0;
         double sumwtrkPlus1=0;
         double sumwtrkMinus1=0;
         double effV=0;
         for(int iplus=0;iplus<(int)pVect_trkEtaPlus->size();iplus++){
           TVector3 pvector_trkPlus = (*pVect_trkEtaPlus)[iplus];
           double phi_trkPlus = pvector_trkPlus.Phi();
           //double pt_trkPlus_weight = pvector_trkPlus.Pt();
           double pt_trkPlus_weight = 1.0;  // unit weight;
           sumwtrkPlus+= pt_trkPlus_weight;
           QtrkPlus[ibin][iH]+= pt_trkPlus_weight * TComplex::Exp(TComplex(0,(iH+1)*phi_trkPlus));
           QtrkAll[ibin][iH]+= pt_trkPlus_weight * TComplex::Exp(TComplex(0,(iH+1)*phi_trkPlus));
           if(pvector_trkPlus.Eta()>1.0){
             effV=EffVsPtHist->GetBinContent(EffVsPtHist->FindBin(pvector_trkPlus.Pt()));
             sumwtrkPlus1+=1.0/effV;
             QtrkPlus1[ibin][iH]+= 1.0/effV * TComplex::Exp(TComplex(0,(iH+1)*phi_trkPlus));
           }
         }
         //if(sumwtrkPlus>0) QtrkPlus[ibin][iH]=QtrkPlus[ibin][iH]/sumwtrkPlus - TComplex(meanQxTrkPlus[ibin][iH], meanQyTrkPlus[ibin][iH]); // re-centering
         if(sumwtrkPlus>0) QtrkPlus[ibin][iH]=QtrkPlus[ibin][iH]/sumwtrkPlus; 
         else QtrkPlus[ibin][iH]=0;
         if(sumwtrkPlus1>0) QtrkPlus1[ibin][iH]=QtrkPlus1[ibin][iH]/sumwtrkPlus1;
         else QtrkPlus1[ibin][iH]=0;
         for(int iminus=0;iminus<(int)pVect_trkEtaMinus->size();iminus++){
           TVector3 pvector_trkMinus = (*pVect_trkEtaMinus)[iminus];
           double phi_trkMinus = pvector_trkMinus.Phi();
           //double pt_trkMinus_weight = pvector_trkMinus.Pt();
           double pt_trkMinus_weight = 1.0;  // unit weight;
           sumwtrkMinus+= pt_trkMinus_weight;
           QtrkMinus[ibin][iH]+= pt_trkMinus_weight * TComplex::Exp(TComplex(0,(iH+1)*phi_trkMinus));
           QtrkAll[ibin][iH]+= pt_trkMinus_weight * TComplex::Exp(TComplex(0,(iH+1)*phi_trkMinus));
           if(pvector_trkMinus.Eta()<-1.0){
             effV=EffVsPtHist->GetBinContent(EffVsPtHist->FindBin(pvector_trkMinus.Pt()));
             sumwtrkMinus1+=1.0/effV;
             QtrkMinus1[ibin][iH]+= 1.0/effV * TComplex::Exp(TComplex(0,(iH+1)*phi_trkMinus));
           }
         }
         //if(sumwtrkMinus>0) QtrkMinus[ibin][iH]=QtrkMinus[ibin][iH]/sumwtrkMinus - TComplex(meanQxTrkMinus[ibin][iH], meanQyTrkMinus[ibin][iH]); //re-centering;
         if(sumwtrkMinus>0) QtrkMinus[ibin][iH]=QtrkMinus[ibin][iH]/sumwtrkMinus;
         else QtrkMinus[ibin][iH]=0;  
         if((sumwtrkPlus+sumwtrkMinus)>0) QtrkAll[ibin][iH]=QtrkAll[ibin][iH]/(sumwtrkPlus+sumwtrkMinus);
         else QtrkAll[ibin][iH]=0;
         if(sumwtrkMinus1>0) QtrkMinus1[ibin][iH]=QtrkMinus1[ibin][iH]/sumwtrkMinus1;
         else QtrkMinus1[ibin][iH]=0;
       }

       TComplex temp;
       double tempReal;
       for(int iH=0; iH<nHarmonics; iH++){
         hQhfPlusX[ibin][iH]->Fill(QhfPlus[ibin][iH].Re());
         hQhfPlusY[ibin][iH]->Fill(QhfPlus[ibin][iH].Im());
         hQhfPlusQ[ibin][iH]->Fill(TComplex::Abs(QhfPlus[ibin][iH]));
         hQhfMinusX[ibin][iH]->Fill(QhfMinus[ibin][iH].Re());
         hQhfMinusY[ibin][iH]->Fill(QhfMinus[ibin][iH].Im());
         hQhfMinusQ[ibin][iH]->Fill(TComplex::Abs(QhfMinus[ibin][iH]));
         hQtrkPlusX[ibin][iH]->Fill(QtrkPlus[ibin][iH].Re());
         hQtrkPlusY[ibin][iH]->Fill(QtrkPlus[ibin][iH].Im());
         hQtrkMinusX[ibin][iH]->Fill(QtrkMinus[ibin][iH].Re());
         hQtrkMinusY[ibin][iH]->Fill(QtrkMinus[ibin][iH].Im());

         double vnabsmevt;
         temp=QhfPlus[ibin][iH]*TComplex::Conjugate(QhfMinus[ibin][iH]);
         if(useReDenominator) vnabsmevt=temp.Re();  // or use Abs(temp) ???
         else vnabsmevt=TComplex::Abs(temp);  // or use Abs(temp) ???
         VnAbs2[ibin][iH]+=vnabsmevt;
         hVnAbs2[ibin][iH]->Fill(vnabsmevt);
         temp=QhfPlus[ibin][iH]*TComplex::Conjugate(QhfMinus[ibin][iH]) * QhfPlus[ibin][iH]*TComplex::Conjugate(QhfMinus[ibin][iH]);
         if(useReDenominator) vnabsmevt=temp.Re();
         else vnabsmevt=TComplex::Abs(temp);
         VnAbs4[ibin][iH]+=vnabsmevt;
         hVnAbs4[ibin][iH]->Fill(vnabsmevt);
         temp=QhfPlus[ibin][iH]*TComplex::Conjugate(QhfMinus[ibin][iH]) * QhfPlus[ibin][iH]*TComplex::Conjugate(QhfMinus[ibin][iH]) * QhfPlus[ibin][iH]*TComplex::Conjugate(QhfMinus[ibin][iH]);
         if(useReDenominator) vnabsmevt=temp.Re();
         else vnabsmevt=TComplex::Abs(temp);
         VnAbs6[ibin][iH]+=vnabsmevt;
         hVnAbs6[ibin][iH]->Fill(vnabsmevt);
         temp=QhfPlus[ibin][iH]*TComplex::Conjugate(QhfMinus[ibin][iH]) * QhfPlus[ibin][iH]*TComplex::Conjugate(QhfMinus[ibin][iH]) * QhfPlus[ibin][iH]*TComplex::Conjugate(QhfMinus[ibin][iH]) * QhfPlus[ibin][iH]*TComplex::Conjugate(QhfMinus[ibin][iH]);
         if(useReDenominator) vnabsmevt=temp.Re();
         else vnabsmevt=TComplex::Abs(temp);
         hVnAbs8[ibin][iH]->Fill(vnabsmevt);
       }

       //temp=QhfPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1]) * QhfPlus[ibin][2]*TComplex::Conjugate(QhfMinus[ibin][2]);
       //if(useReDenominator) tempReal=(QhfPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1])).Re() * (QhfPlus[ibin][2]*TComplex::Conjugate(QhfMinus[ibin][2])).Re();
       if(useReDenominator) tempReal=(QhfPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1]) * QhfPlus[ibin][2]*TComplex::Conjugate(QhfMinus[ibin][2])).Re();
       else tempReal=TComplex::Abs(QhfPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1])) * TComplex::Abs(QhfPlus[ibin][2]*TComplex::Conjugate(QhfMinus[ibin][2]));
       V2Abs2V3Abs2[ibin]+=tempReal;
       hV2Abs2V3Abs2[ibin]->Fill(tempReal);
       //temp=QhfPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1]) * QhfPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1]) * QhfPlus[ibin][2]*TComplex::Conjugate(QhfMinus[ibin][2]);
       //if(useReDenominator) tempReal=(QhfPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1])).Re() * (QhfPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1])).Re() * (QhfPlus[ibin][2]*TComplex::Conjugate(QhfMinus[ibin][2])).Re();
       if(useReDenominator) tempReal=(QhfPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1]) * QhfPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1]) * QhfPlus[ibin][2]*TComplex::Conjugate(QhfMinus[ibin][2])).Re();
       else tempReal=TComplex::Abs(QhfPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1])) * TComplex::Abs(QhfPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1])) * TComplex::Abs(QhfPlus[ibin][2]*TComplex::Conjugate(QhfMinus[ibin][2]));
       V2Abs4V3Abs2[ibin]+=tempReal;
       hV2Abs4V3Abs2[ibin]->Fill(tempReal);
       //if(useReDenominator) tempReal=(QhfPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1])).Re() * (QhfPlus[ibin][2]*TComplex::Conjugate(QhfMinus[ibin][2])).Re() * (QhfPlus[ibin][2]*TComplex::Conjugate(QhfMinus[ibin][2])).Re();
       if(useReDenominator) tempReal=(QhfPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1]) * QhfPlus[ibin][2]*TComplex::Conjugate(QhfMinus[ibin][2]) * QhfPlus[ibin][2]*TComplex::Conjugate(QhfMinus[ibin][2])).Re();
       else tempReal=TComplex::Abs(QhfPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1])) * TComplex::Abs(QhfPlus[ibin][2]*TComplex::Conjugate(QhfMinus[ibin][2])) * TComplex::Abs(QhfPlus[ibin][2]*TComplex::Conjugate(QhfMinus[ibin][2]));
       hV2Abs2V3Abs4[ibin]->Fill(tempReal);

       //trk
       //if(useReDenominator) tempReal=(QtrkPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1])).Re() * (QtrkPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1])).Re();
       if(useReDenominator) tempReal=(QtrkPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1]) * QtrkPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1])).Re();
       else tempReal=TComplex::Abs(QtrkPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1])) * TComplex::Abs(QtrkPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1]));
       hV2Abs4trk1[ibin]->Fill(tempReal);
       hV2Abs4trk12[ibin]->Fill(tempReal);
       hV2Abs4trk12[ibin]->Fill((QtrkMinus[ibin][1]*TComplex::Conjugate(QhfPlus[ibin][1]) * QtrkMinus[ibin][1]*TComplex::Conjugate(QhfPlus[ibin][1])).Re());
       hV2Abs4trk2[ibin]->Fill((QtrkAll[ibin][1]*TComplex::Conjugate(QhfPlus[ibin][1]) * QtrkAll[ibin][1]*TComplex::Conjugate(QhfPlus[ibin][1])).Re());
       //if(useReDenominator) tempReal=(QtrkPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1])).Re() * (QtrkPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1])).Re() * (QtrkPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1])).Re();
       if(useReDenominator) tempReal=(QtrkPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1]) * QtrkPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1]) * QtrkPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1])).Re();
       else tempReal=TComplex::Abs(QtrkPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1])) * TComplex::Abs(QtrkPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1])) * (QtrkPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1])).Re();
       hV2Abs6trk1[ibin]->Fill(tempReal);
       hV2Abs6trk12[ibin]->Fill(tempReal);
       hV2Abs6trk12[ibin]->Fill((QtrkMinus[ibin][1]*TComplex::Conjugate(QhfPlus[ibin][1]) * QtrkMinus[ibin][1]*TComplex::Conjugate(QhfPlus[ibin][1]) * QtrkMinus[ibin][1]*TComplex::Conjugate(QhfPlus[ibin][1])).Re());
       hV2Abs6trk2[ibin]->Fill((QtrkAll[ibin][1]*TComplex::Conjugate(QhfPlus[ibin][1]) * QtrkAll[ibin][1]*TComplex::Conjugate(QhfPlus[ibin][1]) * QtrkAll[ibin][1]*TComplex::Conjugate(QhfPlus[ibin][1])).Re());
       //if(useReDenominator) tempReal=(QtrkPlus[ibin][2]*TComplex::Conjugate(QhfMinus[ibin][2])).Re() * (QtrkPlus[ibin][2]*TComplex::Conjugate(QhfMinus[ibin][2])).Re();
       if(useReDenominator) tempReal=(QtrkPlus[ibin][2]*TComplex::Conjugate(QhfMinus[ibin][2]) * QtrkPlus[ibin][2]*TComplex::Conjugate(QhfMinus[ibin][2])).Re();
       else tempReal=TComplex::Abs(QtrkPlus[ibin][2]*TComplex::Conjugate(QhfMinus[ibin][2])) * TComplex::Abs(QtrkPlus[ibin][2]*TComplex::Conjugate(QhfMinus[ibin][2]));
       hV3Abs4trk1[ibin]->Fill(tempReal);
       hV3Abs4trk12[ibin]->Fill(tempReal);
       hV3Abs4trk12[ibin]->Fill((QtrkMinus[ibin][2]*TComplex::Conjugate(QhfPlus[ibin][2]) * QtrkMinus[ibin][2]*TComplex::Conjugate(QhfPlus[ibin][2])).Re());
       hV3Abs4trk2[ibin]->Fill((QtrkAll[ibin][2]*TComplex::Conjugate(QhfPlus[ibin][2]) * QtrkAll[ibin][2]*TComplex::Conjugate(QhfPlus[ibin][2])).Re());
       //if(useReDenominator) tempReal=(QtrkPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1])).Re() * (QtrkPlus[ibin][2]*TComplex::Conjugate(QhfMinus[ibin][2])).Re();
       if(useReDenominator) tempReal=(QtrkPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1]) * QtrkPlus[ibin][2]*TComplex::Conjugate(QhfMinus[ibin][2])).Re();
       else tempReal=TComplex::Abs(QtrkPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1])) * TComplex::Abs(QtrkPlus[ibin][2]*TComplex::Conjugate(QhfMinus[ibin][2]));
       hV2Abs2V3Abs2trk1[ibin]->Fill(tempReal);
       hV2Abs2V3Abs2trk12[ibin]->Fill(tempReal);
       hV2Abs2V3Abs2trk12[ibin]->Fill((QtrkMinus[ibin][1]*TComplex::Conjugate(QhfPlus[ibin][1]) * QtrkMinus[ibin][2]*TComplex::Conjugate(QhfPlus[ibin][2])).Re());
       hV2Abs2V3Abs2trk2[ibin]->Fill((QtrkAll[ibin][1]*TComplex::Conjugate(QhfPlus[ibin][1]) * QtrkAll[ibin][2]*TComplex::Conjugate(QhfPlus[ibin][2])).Re());
       //if(useReDenominator) tempReal=(QtrkPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1])).Re() * (QtrkPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1])).Re() * (QtrkPlus[ibin][2]*TComplex::Conjugate(QhfMinus[ibin][2])).Re();
       if(useReDenominator) tempReal=(QtrkPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1]) * QtrkPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1]) * QtrkPlus[ibin][2]*TComplex::Conjugate(QhfMinus[ibin][2])).Re();
       else tempReal=TComplex::Abs(QtrkPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1])) * TComplex::Abs(QtrkPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1])) * TComplex::Abs(QtrkPlus[ibin][2]*TComplex::Conjugate(QhfMinus[ibin][2]));
       hV2Abs4V3Abs2trk1[ibin]->Fill(tempReal);
       hV2Abs4V3Abs2trk12[ibin]->Fill(tempReal);
       hV2Abs4V3Abs2trk12[ibin]->Fill((QtrkMinus[ibin][1]*TComplex::Conjugate(QhfPlus[ibin][1]) * QtrkMinus[ibin][1]*TComplex::Conjugate(QhfPlus[ibin][1]) * QtrkMinus[ibin][2]*TComplex::Conjugate(QhfPlus[ibin][2])).Re());
       hV2Abs4V3Abs2trk2[ibin]->Fill((QtrkAll[ibin][1]*TComplex::Conjugate(QhfPlus[ibin][1]) * QtrkAll[ibin][1]*TComplex::Conjugate(QhfPlus[ibin][1]) * QtrkAll[ibin][2]*TComplex::Conjugate(QhfPlus[ibin][2])).Re());

       //Only Qtrk
       tempReal=(QtrkPlus1[ibin][1]*TComplex::Conjugate(QtrkMinus1[ibin][1])).Re();
       hV2Abs2Qtrk[ibin]->Fill(tempReal);
       tempReal=(QtrkPlus1[ibin][1]*TComplex::Conjugate(QtrkMinus1[ibin][1]) * QtrkPlus1[ibin][1]*TComplex::Conjugate(QtrkMinus1[ibin][1])).Re();
       hV2Abs4Qtrk[ibin]->Fill(tempReal);
       tempReal=(QtrkPlus1[ibin][1]*TComplex::Conjugate(QtrkMinus1[ibin][1]) * QtrkPlus1[ibin][1]*TComplex::Conjugate(QtrkMinus1[ibin][1]) * QtrkPlus1[ibin][1]*TComplex::Conjugate(QtrkMinus1[ibin][1])).Re();
       hV2Abs6Qtrk[ibin]->Fill(tempReal);
       tempReal=(QtrkPlus1[ibin][2]*TComplex::Conjugate(QtrkMinus1[ibin][2]) * QtrkPlus1[ibin][2]*TComplex::Conjugate(QtrkMinus1[ibin][2])).Re();
       hV3Abs4Qtrk[ibin]->Fill(tempReal);
       tempReal=(QtrkPlus1[ibin][1]*TComplex::Conjugate(QtrkMinus1[ibin][1]) * QtrkPlus1[ibin][2]*TComplex::Conjugate(QtrkMinus1[ibin][2])).Re();
       hV2Abs2V3Abs2Qtrk[ibin]->Fill(tempReal);
       tempReal=(QtrkPlus1[ibin][1]*TComplex::Conjugate(QtrkMinus1[ibin][1]) * QtrkPlus1[ibin][1]*TComplex::Conjugate(QtrkMinus1[ibin][1]) * QtrkPlus1[ibin][2]*TComplex::Conjugate(QtrkMinus1[ibin][2])).Re();
       hV2Abs4V3Abs2Qtrk[ibin]->Fill(tempReal);
       //Only QtrkHF
       tempReal=(QtrkPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1])).Re();
       hV2Abs2QtrkHF[ibin]->Fill(tempReal);
       tempReal=(QtrkPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1]) * QtrkPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1])).Re();
       hV2Abs4QtrkHF[ibin]->Fill(tempReal);
       tempReal=(QtrkPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1]) * QtrkPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1]) * QtrkPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1])).Re();
       hV2Abs6QtrkHF[ibin]->Fill(tempReal);
       tempReal=(QtrkPlus[ibin][2]*TComplex::Conjugate(QhfMinus[ibin][2]) * QtrkPlus[ibin][2]*TComplex::Conjugate(QhfMinus[ibin][2])).Re();
       hV3Abs4QtrkHF[ibin]->Fill(tempReal);
       tempReal=(QtrkPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1]) * QtrkPlus[ibin][2]*TComplex::Conjugate(QhfMinus[ibin][2])).Re();
       hV2Abs2V3Abs2QtrkHF[ibin]->Fill(tempReal);
       tempReal=(QtrkPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1]) * QtrkPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1]) * QtrkPlus[ibin][2]*TComplex::Conjugate(QhfMinus[ibin][2])).Re();
       hV2Abs4V3Abs2QtrkHF[ibin]->Fill(tempReal);

//Numerators
       temp=QhfPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1]);
       if(useRe) tempReal=temp.Re();
       else tempReal=TComplex::Abs(temp);
       hV2V2star[ibin]->Fill(tempReal);
       temp=QhfPlus[ibin][3]*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][1]);
       if(useRe) tempReal=temp.Re();
       else tempReal=TComplex::Abs(temp);
       V4V2starV2star[ibin]+=tempReal;
       hV4V2starV2star[ibin]->Fill(tempReal);
       temp=QhfPlus[ibin][5]*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][1]);
       if(useRe) tempReal=temp.Re();
       else tempReal=TComplex::Abs(temp);
       V6V2starV2starV2star[ibin]+=tempReal;
       hV6V2starV2starV2star[ibin]->Fill(tempReal);
       temp=QhfPlus[ibin][5]*TComplex::Conjugate(QhfMinus[ibin][2])*TComplex::Conjugate(QhfMinus[ibin][2]);
       if(useRe) tempReal=temp.Re();
       else tempReal=TComplex::Abs(temp);
       V6V3starV3star[ibin]+=tempReal;
       hV6V3starV3star[ibin]->Fill(tempReal);
       temp=QhfPlus[ibin][4]*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][2]);
       if(useRe) tempReal=temp.Re();
       else tempReal=TComplex::Abs(temp);
       V5V2starV3star[ibin]+=tempReal;
       hV5V2starV3star[ibin]->Fill(tempReal);
       temp=QhfPlus[ibin][6]*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][2]);
       if(useRe) tempReal=temp.Re();
       else tempReal=TComplex::Abs(temp);
       V7V2starV2starV3star[ibin]+=tempReal;
       hV7V2starV2starV3star[ibin]->Fill(tempReal);

       //Only Qtrk
       temp=QtrkPlus1[ibin][1]*TComplex::Conjugate(QtrkMinus1[ibin][1]);
       hV2V2starQtrk[ibin]->Fill(temp.Re());
       temp=QtrkPlus1[ibin][3]*TComplex::Conjugate(QtrkMinus1[ibin][1])*TComplex::Conjugate(QtrkMinus1[ibin][1]);
       hV4V2starV2starQtrk[ibin]->Fill(temp.Re());
       temp=QtrkPlus1[ibin][5]*TComplex::Conjugate(QtrkMinus1[ibin][1])*TComplex::Conjugate(QtrkMinus1[ibin][1])*TComplex::Conjugate(QtrkMinus1[ibin][1]);
       hV6V2starV2starV2starQtrk[ibin]->Fill(temp.Re());
       temp=QtrkPlus1[ibin][5]*TComplex::Conjugate(QtrkMinus1[ibin][2])*TComplex::Conjugate(QtrkMinus1[ibin][2]);
       hV6V3starV3starQtrk[ibin]->Fill(temp.Re());
       temp=QtrkPlus1[ibin][4]*TComplex::Conjugate(QtrkMinus1[ibin][1])*TComplex::Conjugate(QtrkMinus1[ibin][2]);
       hV5V2starV3starQtrk[ibin]->Fill(temp.Re());
       temp=QtrkPlus1[ibin][6]*TComplex::Conjugate(QtrkMinus1[ibin][1])*TComplex::Conjugate(QtrkMinus1[ibin][1])*TComplex::Conjugate(QtrkMinus1[ibin][2]);
       hV7V2starV2starV3starQtrk[ibin]->Fill(temp.Re());
       //Only QtrkHF
       temp=QtrkPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1]);
       hV2V2starQtrkHF[ibin]->Fill(temp.Re());
       temp=QtrkPlus[ibin][3]*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][1]);
       hV4V2starV2starQtrkHF[ibin]->Fill(temp.Re());
       temp=QtrkPlus[ibin][5]*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][1]);
       hV6V2starV2starV2starQtrkHF[ibin]->Fill(temp.Re());
       temp=QtrkPlus[ibin][5]*TComplex::Conjugate(QhfMinus[ibin][2])*TComplex::Conjugate(QhfMinus[ibin][2]);
       hV6V3starV3starQtrkHF[ibin]->Fill(temp.Re());
       temp=QtrkPlus[ibin][4]*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][2]);
       hV5V2starV3starQtrkHF[ibin]->Fill(temp.Re());
       temp=QtrkPlus[ibin][6]*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][2]);
       hV7V2starV2starV3starQtrkHF[ibin]->Fill(temp.Re());

       double sumwtrkPt[nPtBin]; for(int ipt=0; ipt<nPtBin; ipt++) sumwtrkPt[ipt]=0.0;
       for(int iplus=0;iplus<(int)pVect_trkEtaPlus->size();iplus++){
         TVector3 pvector_trkPlus = (*pVect_trkEtaPlus)[iplus];
         double phi_trkPlus = pvector_trkPlus.Phi();
         double pt_trkPlus = pvector_trkPlus.Pt();
         int cpt=-1;
         for(int ipt=0; ipt<nPtBin; ipt++){
           if(pt_trkPlus>=ptBin[ipt] && pt_trkPlus<ptBin[ipt+1])
             cpt=ipt;
         }
         if(cpt<0) cpt=nPtBin-1;

         //double pt_trkPlus_weight = pvector_trkPlus.Pt();
         double pt_trkPlus_weight = 1.0;  // unit weight;
         sumwtrkPt[cpt]+= pt_trkPlus_weight;
         for(int iH=0; iH<nHarmonics; iH++){
           QtrkPt[ibin][iH][cpt]+= pt_trkPlus_weight * TComplex::Exp(TComplex(0,(iH+1)*phi_trkPlus));
         }

         temp = TComplex::Exp(TComplex(0,(2)*phi_trkPlus))*TComplex::Conjugate(QhfMinus[ibin][1]);
         if(useRe) tempReal=temp.Re();
         else tempReal=TComplex::Abs(temp);
         hv2V2star[ibin][cpt]->Fill(tempReal);
         temp = TComplex::Exp(TComplex(0,(3)*phi_trkPlus))*TComplex::Conjugate(QhfMinus[ibin][2]);
         if(useRe) tempReal=temp.Re();
         else tempReal=TComplex::Abs(temp);
         hv3V3star[ibin][cpt]->Fill(tempReal);
         temp = TComplex::Exp(TComplex(0,(4)*phi_trkPlus))*TComplex::Conjugate(QhfMinus[ibin][3]);
         if(useRe) tempReal=temp.Re();
         else tempReal=TComplex::Abs(temp);
         hv4V4star[ibin][cpt]->Fill(tempReal);
         temp = TComplex::Exp(TComplex(0,(5)*phi_trkPlus))*TComplex::Conjugate(QhfMinus[ibin][4]);
         if(useRe) tempReal=temp.Re();
         else tempReal=TComplex::Abs(temp);
         hv5V5star[ibin][cpt]->Fill(tempReal);
         temp = TComplex::Exp(TComplex(0,(6)*phi_trkPlus))*TComplex::Conjugate(QhfMinus[ibin][5]);
         if(useRe) tempReal=temp.Re();
         else tempReal=TComplex::Abs(temp);
         hv6V6star[ibin][cpt]->Fill(tempReal);
         temp = TComplex::Exp(TComplex(0,(7)*phi_trkPlus))*TComplex::Conjugate(QhfMinus[ibin][6]);
         if(useRe) tempReal=temp.Re();
         else tempReal=TComplex::Abs(temp);
         hv7V7star[ibin][cpt]->Fill(tempReal);
         temp = TComplex::Exp(TComplex(0,(8)*phi_trkPlus))*TComplex::Conjugate(QhfMinus[ibin][7]);
         if(useRe) tempReal=temp.Re();
         else tempReal=TComplex::Abs(temp);
         hv8V8star[ibin][cpt]->Fill(tempReal);

         temp = TComplex::Exp(TComplex(0,(4)*phi_trkPlus))*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][1]);
         if(useRe) tempReal=temp.Re();
         else tempReal=TComplex::Abs(temp);
         hv4V2starV2star[ibin][cpt]->Fill(tempReal);
         temp = TComplex::Exp(TComplex(0,(4)*phi_trkPlus))*TComplex::Conjugate(QhfPlus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][1]);
         if(useRe) tempReal=temp.Re();
         else tempReal=TComplex::Abs(temp);
         hv4V2starV2starAB[ibin][cpt]->Fill(tempReal);
         //temp = TComplex::Exp(TComplex(0,(4)*phi_trkPlus))*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][1]) - TComplex::Exp(TComplex(0,(5)*phi_trkPlus))*TComplex::Conjugate(Qhf2p2Minus[ibin]);
         temp = TComplex::Exp(TComplex(0,(2)*phi_trkPlus))*TComplex::Exp(TComplex(0,(2)*phi_trkPlus)) * TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][1]);
         if(useRe) tempReal=temp.Re();
         else tempReal=TComplex::Abs(temp);
         hv4V2starV2starSub[ibin][cpt]->Fill(tempReal);
         //if(fabs(sumWMinus[ibin]*sumWMinus[ibin]-sumW2Minus[ibin])>0.00001) hv4V2starV2starSub[ibin][cpt]->Fill(tempReal*sumWMinus[ibin]*sumWMinus[ibin]/(sumWMinus[ibin]*sumWMinus[ibin]-sumW2Minus[ibin]));
         //else hv4V2starV2starSub[ibin][cpt]->Fill(tempReal);
         temp=TComplex::Exp(TComplex(0,(6)*phi_trkPlus))*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][1]);
         if(useRe) tempReal=temp.Re();
         else tempReal=TComplex::Abs(temp);
         hv6V2starV2starV2star[ibin][cpt]->Fill(tempReal);
         temp=TComplex::Exp(TComplex(0,(6)*phi_trkPlus))*TComplex::Conjugate(QhfPlus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfPlus[ibin][1]);
         if(useRe) tempReal=temp.Re();
         else tempReal=TComplex::Abs(temp);
         hv6V2starV2starV2starAB[ibin][cpt]->Fill(tempReal);
         //temp=TComplex::Exp(TComplex(0,(6)*phi_trkPlus))*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][1]) - (2+1)*TComplex::Exp(TComplex(0,(6)*phi_trkPlus))*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(Qhf2p2Minus[ibin]) + 2*TComplex::Exp(TComplex(0,(6)*phi_trkPlus))*TComplex::Conjugate(Qhf2p2p2Minus[ibin]);
         temp=TComplex::Exp(TComplex(0,(2)*phi_trkPlus))*TComplex::Exp(TComplex(0,(2)*phi_trkPlus))*TComplex::Exp(TComplex(0,(2)*phi_trkPlus)) * TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][1]);
         if(useRe) tempReal=temp.Re();
         else tempReal=TComplex::Abs(temp);         
         hv6V2starV2starV2starSub[ibin][cpt]->Fill(tempReal);
         //if(fabs(sumWMinus[ibin]*sumWMinus[ibin]*sumWMinus[ibin]-3*sumW2Minus[ibin]*sumWMinus[ibin]+2*sumW3Minus[ibin])>0.00001) hv6V2starV2starV2starSub[ibin][cpt]->Fill(tempReal*sumWMinus[ibin]*sumWMinus[ibin]*sumWMinus[ibin]/(sumWMinus[ibin]*sumWMinus[ibin]*sumWMinus[ibin]-3*sumW2Minus[ibin]*sumWMinus[ibin]+2*sumW3Minus[ibin]));
         //else hv6V2starV2starV2starSub[ibin][cpt]->Fill(tempReal);
         temp=TComplex::Exp(TComplex(0,(6)*phi_trkPlus))*TComplex::Conjugate(QhfMinus[ibin][2])*TComplex::Conjugate(QhfMinus[ibin][2]);
         if(useRe) tempReal=temp.Re();
         else tempReal=TComplex::Abs(temp);
         hv6V3starV3star[ibin][cpt]->Fill(tempReal);
         temp=TComplex::Exp(TComplex(0,(6)*phi_trkPlus))*TComplex::Conjugate(QhfPlus[ibin][2])*TComplex::Conjugate(QhfMinus[ibin][2]);
         if(useRe) tempReal=temp.Re();
         else tempReal=TComplex::Abs(temp);
         hv6V3starV3starAB[ibin][cpt]->Fill(tempReal);
         //temp=TComplex::Exp(TComplex(0,(6)*phi_trkPlus))*TComplex::Conjugate(QhfMinus[ibin][2])*TComplex::Conjugate(QhfMinus[ibin][2]) - TComplex::Exp(TComplex(0,(6)*phi_trkPlus))*TComplex::Conjugate(Qhf3p3Minus[ibin]);
         temp=TComplex::Exp(TComplex(0,(3)*phi_trkPlus))*TComplex::Exp(TComplex(0,(3)*phi_trkPlus)) * TComplex::Conjugate(QhfMinus[ibin][2])*TComplex::Conjugate(QhfMinus[ibin][2]);
         if(useRe) tempReal=temp.Re();
         else tempReal=TComplex::Abs(temp);
         hv6V3starV3starSub[ibin][cpt]->Fill(tempReal);
         //if(fabs(sumWMinus[ibin]*sumWMinus[ibin]-sumW2Minus[ibin])>0.00001) hv6V3starV3starSub[ibin][cpt]->Fill(tempReal*sumWMinus[ibin]*sumWMinus[ibin]/(sumWMinus[ibin]*sumWMinus[ibin]-sumW2Minus[ibin]));
         //else hv6V3starV3starSub[ibin][cpt]->Fill(tempReal);
         temp=TComplex::Exp(TComplex(0,(5)*phi_trkPlus))*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][2]);
         if(useRe) tempReal=temp.Re();
         else tempReal=TComplex::Abs(temp);
         hv5V2starV3star[ibin][cpt]->Fill(tempReal);
         temp=TComplex::Exp(TComplex(0,(5)*phi_trkPlus))*TComplex::Conjugate(QhfPlus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][2]);
         if(useRe) tempReal=temp.Re();
         else tempReal=TComplex::Abs(temp);
         hv5V2starV3starAB[ibin][cpt]->Fill(tempReal);
         //temp=TComplex::Exp(TComplex(0,(5)*phi_trkPlus))*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][2]) - TComplex::Exp(TComplex(0,(5)*phi_trkPlus))*TComplex::Conjugate(Qhf2p3Minus[ibin]);
         temp=TComplex::Exp(TComplex(0,(2)*phi_trkPlus))*TComplex::Exp(TComplex(0,(3)*phi_trkPlus)) * TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][2]);
         if(useRe) tempReal=temp.Re();
         else tempReal=TComplex::Abs(temp);
         hv5V2starV3starSub[ibin][cpt]->Fill(tempReal);
         //if(fabs(sumWMinus[ibin]*sumWMinus[ibin]-sumW2Minus[ibin])>0.00001) hv5V2starV3starSub[ibin][cpt]->Fill(tempReal*sumWMinus[ibin]*sumWMinus[ibin]/(sumWMinus[ibin]*sumWMinus[ibin]-sumW2Minus[ibin]));
         //else hv5V2starV3starSub[ibin][cpt]->Fill(tempReal);
         temp=TComplex::Exp(TComplex(0,(7)*phi_trkPlus))*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][2]);
         if(useRe) tempReal=temp.Re();
         else tempReal=TComplex::Abs(temp);
         hv7V2starV2starV3star[ibin][cpt]->Fill(tempReal);
         temp=TComplex::Exp(TComplex(0,(7)*phi_trkPlus))*TComplex::Conjugate(QhfPlus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfPlus[ibin][2]);
         if(useRe) tempReal=temp.Re();
         else tempReal=TComplex::Abs(temp);
         hv7V2starV2starV3starAB[ibin][cpt]->Fill(tempReal);
         //temp=TComplex::Exp(TComplex(0,(7)*phi_trkPlus))*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][2]) - 2*TComplex::Exp(TComplex(0,(7)*phi_trkPlus))*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(Qhf2p3Minus[ibin]) - TComplex::Exp(TComplex(0,(7)*phi_trkPlus))*TComplex::Conjugate(QhfMinus[ibin][2])*TComplex::Conjugate(Qhf2p2Minus[ibin]) + 2*TComplex::Exp(TComplex(0,(7)*phi_trkPlus))*TComplex::Conjugate(Qhf2p2p3Minus[ibin]);
         temp=TComplex::Exp(TComplex(0,(2)*phi_trkPlus))*TComplex::Exp(TComplex(0,(2)*phi_trkPlus))*TComplex::Exp(TComplex(0,(3)*phi_trkPlus)) * TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][2]);
         if(useRe) tempReal=temp.Re();
         else tempReal=TComplex::Abs(temp);
         hv7V2starV2starV3starSub[ibin][cpt]->Fill(tempReal);
         //if(fabs(sumWMinus[ibin]*sumWMinus[ibin]*sumWMinus[ibin]-3*sumW2Minus[ibin]*sumWMinus[ibin]+2*sumW3Minus[ibin])>0.00001) hv7V2starV2starV3starSub[ibin][cpt]->Fill(tempReal*sumWMinus[ibin]*sumWMinus[ibin]*sumWMinus[ibin]/(sumWMinus[ibin]*sumWMinus[ibin]*sumWMinus[ibin]-3*sumW2Minus[ibin]*sumWMinus[ibin]+2*sumW3Minus[ibin]));
         //else hv7V2starV2starV3starSub[ibin][cpt]->Fill(tempReal);
         temp=TComplex::Exp(TComplex(0,(8)*phi_trkPlus))*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][1]);
         if(useRe) tempReal=temp.Re();
         else tempReal=TComplex::Abs(temp);
         hv8V2starV2starV2starV2star[ibin][cpt]->Fill(tempReal);
         temp=TComplex::Exp(TComplex(0,(8)*phi_trkPlus))*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][2])*TComplex::Conjugate(QhfMinus[ibin][2]);
         if(useRe) tempReal=temp.Re();
         else tempReal=TComplex::Abs(temp);
         hv8V2starV3starV3star[ibin][cpt]->Fill(tempReal);

         hMeanPt[ibin][cpt]->Fill(pt_trkPlus);
       }

       for(int iminus=0;iminus<(int)pVect_trkEtaMinus->size();iminus++){
         TVector3 pvector_trkMinus = (*pVect_trkEtaMinus)[iminus];
         double phi_trkMinus = pvector_trkMinus.Phi();
         double pt_trkMinus = pvector_trkMinus.Pt();
         int cpt=-1;
         for(int ipt=0; ipt<nPtBin; ipt++){
           if(pt_trkMinus>=ptBin[ipt] && pt_trkMinus<ptBin[ipt+1])
             cpt=ipt;
         }
         if(cpt<0) cpt=nPtBin-1;

         //double pt_trkMinus_weight = pvector_trkMinus.Pt();
         double pt_trkMinus_weight = 1.0;  // unit weight;
         sumwtrkPt[cpt]+= pt_trkMinus_weight;
         for(int iH=0; iH<nHarmonics; iH++){
           QtrkPt[ibin][iH][cpt]+= pt_trkMinus_weight * TComplex::Exp(TComplex(0,(iH+1)*phi_trkMinus));
         }

         temp = TComplex::Exp(TComplex(0,(2)*phi_trkMinus))*TComplex::Conjugate(QhfPlus[ibin][1]);
         if(useRe) tempReal=temp.Re();
         else tempReal=TComplex::Abs(temp);
         hv2V2star[ibin][cpt]->Fill(tempReal);
         temp = TComplex::Exp(TComplex(0,(3)*phi_trkMinus))*TComplex::Conjugate(QhfPlus[ibin][2]);
         if(useRe) tempReal=temp.Re();
         else tempReal=TComplex::Abs(temp);
         hv3V3star[ibin][cpt]->Fill(tempReal);
         temp = TComplex::Exp(TComplex(0,(4)*phi_trkMinus))*TComplex::Conjugate(QhfPlus[ibin][3]);
         if(useRe) tempReal=temp.Re();
         else tempReal=TComplex::Abs(temp);
         hv4V4star[ibin][cpt]->Fill(tempReal);
         temp = TComplex::Exp(TComplex(0,(5)*phi_trkMinus))*TComplex::Conjugate(QhfPlus[ibin][4]);
         if(useRe) tempReal=temp.Re();
         else tempReal=TComplex::Abs(temp);
         hv5V5star[ibin][cpt]->Fill(tempReal);
         temp = TComplex::Exp(TComplex(0,(6)*phi_trkMinus))*TComplex::Conjugate(QhfPlus[ibin][5]);
         if(useRe) tempReal=temp.Re();
         else tempReal=TComplex::Abs(temp);
         hv6V6star[ibin][cpt]->Fill(tempReal);
         temp = TComplex::Exp(TComplex(0,(7)*phi_trkMinus))*TComplex::Conjugate(QhfPlus[ibin][6]);
         if(useRe) tempReal=temp.Re();
         else tempReal=TComplex::Abs(temp);
         hv7V7star[ibin][cpt]->Fill(tempReal);
         temp = TComplex::Exp(TComplex(0,(8)*phi_trkMinus))*TComplex::Conjugate(QhfPlus[ibin][7]);
         if(useRe) tempReal=temp.Re();
         else tempReal=TComplex::Abs(temp);
         hv8V8star[ibin][cpt]->Fill(tempReal);

         temp = TComplex::Exp(TComplex(0,(4)*phi_trkMinus))*TComplex::Conjugate(QhfPlus[ibin][1])*TComplex::Conjugate(QhfPlus[ibin][1]);
         if(useRe) tempReal=temp.Re();
         else tempReal=TComplex::Abs(temp);
         hv4V2starV2star[ibin][cpt]->Fill(tempReal);
         temp = TComplex::Exp(TComplex(0,(4)*phi_trkMinus))*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfPlus[ibin][1]);
         if(useRe) tempReal=temp.Re();
         else tempReal=TComplex::Abs(temp);
         hv4V2starV2starAB[ibin][cpt]->Fill(tempReal);
         //temp = TComplex::Exp(TComplex(0,(4)*phi_trkMinus))*TComplex::Conjugate(QhfPlus[ibin][1])*TComplex::Conjugate(QhfPlus[ibin][1]) - TComplex::Exp(TComplex(0,(4)*phi_trkMinus))*TComplex::Conjugate(Qhf2p2Plus[ibin]);
         temp = TComplex::Exp(TComplex(0,(2)*phi_trkMinus))*TComplex::Exp(TComplex(0,(2)*phi_trkMinus)) * TComplex::Conjugate(QhfPlus[ibin][1])*TComplex::Conjugate(QhfPlus[ibin][1]);
         if(useRe) tempReal=temp.Re();
         else tempReal=TComplex::Abs(temp);
         hv4V2starV2starSub[ibin][cpt]->Fill(tempReal);
         //if(fabs(sumWPlus[ibin]*sumWPlus[ibin]-sumW2Plus[ibin])>0.00001) hv4V2starV2starSub[ibin][cpt]->Fill(tempReal*sumWPlus[ibin]*sumWPlus[ibin]/(sumWPlus[ibin]*sumWPlus[ibin]-sumW2Plus[ibin]));
         //else hv4V2starV2starSub[ibin][cpt]->Fill(tempReal);
         temp=TComplex::Exp(TComplex(0,(6)*phi_trkMinus))*TComplex::Conjugate(QhfPlus[ibin][1])*TComplex::Conjugate(QhfPlus[ibin][1])*TComplex::Conjugate(QhfPlus[ibin][1]);
         if(useRe) tempReal=temp.Re();
         else tempReal=TComplex::Abs(temp);
         hv6V2starV2starV2star[ibin][cpt]->Fill(tempReal);
         temp=TComplex::Exp(TComplex(0,(6)*phi_trkMinus))*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfPlus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][1]);
         if(useRe) tempReal=temp.Re();
         else tempReal=TComplex::Abs(temp);
         hv6V2starV2starV2starAB[ibin][cpt]->Fill(tempReal);
         //temp=TComplex::Exp(TComplex(0,(6)*phi_trkMinus))*TComplex::Conjugate(QhfPlus[ibin][1])*TComplex::Conjugate(QhfPlus[ibin][1])*TComplex::Conjugate(QhfPlus[ibin][1]) - (2+1)*TComplex::Exp(TComplex(0,(6)*phi_trkMinus))*TComplex::Conjugate(QhfPlus[ibin][1])*TComplex::Conjugate(Qhf2p2Plus[ibin]) + 2*TComplex::Exp(TComplex(0,(6)*phi_trkMinus))*TComplex::Conjugate(Qhf2p2p2Plus[ibin]);
         temp=TComplex::Exp(TComplex(0,(2)*phi_trkMinus))*TComplex::Exp(TComplex(0,(2)*phi_trkMinus))*TComplex::Exp(TComplex(0,(2)*phi_trkMinus)) * TComplex::Conjugate(QhfPlus[ibin][1])*TComplex::Conjugate(QhfPlus[ibin][1])*TComplex::Conjugate(QhfPlus[ibin][1]);
         if(useRe) tempReal=temp.Re();
         else tempReal=TComplex::Abs(temp);
         hv6V2starV2starV2starSub[ibin][cpt]->Fill(tempReal);
         //if(fabs(sumWMinus[ibin]*sumWMinus[ibin]*sumWMinus[ibin]-3*sumW2Minus[ibin]*sumWMinus[ibin]+2*sumW3Minus[ibin])>0.00001) hv6V2starV2starV2starSub[ibin][cpt]->Fill(tempReal*sumWMinus[ibin]*sumWMinus[ibin]*sumWMinus[ibin]/(sumWMinus[ibin]*sumWMinus[ibin]*sumWMinus[ibin]-3*sumW2Minus[ibin]*sumWMinus[ibin]+2*sumW3Minus[ibin]));
         //else hv6V2starV2starV2starSub[ibin][cpt]->Fill(tempReal);
         temp=TComplex::Exp(TComplex(0,(6)*phi_trkMinus))*TComplex::Conjugate(QhfPlus[ibin][2])*TComplex::Conjugate(QhfPlus[ibin][2]);
         if(useRe) tempReal=temp.Re();
         else tempReal=TComplex::Abs(temp);
         hv6V3starV3star[ibin][cpt]->Fill(tempReal);
         temp=TComplex::Exp(TComplex(0,(6)*phi_trkMinus))*TComplex::Conjugate(QhfMinus[ibin][2])*TComplex::Conjugate(QhfPlus[ibin][2]);
         if(useRe) tempReal=temp.Re();
         else tempReal=TComplex::Abs(temp);
         hv6V3starV3starAB[ibin][cpt]->Fill(tempReal);
         //temp=TComplex::Exp(TComplex(0,(6)*phi_trkMinus))*TComplex::Conjugate(QhfPlus[ibin][2])*TComplex::Conjugate(QhfPlus[ibin][2]) - TComplex::Exp(TComplex(0,(6)*phi_trkMinus))*TComplex::Conjugate(Qhf3p3Plus[ibin]);
         temp=TComplex::Exp(TComplex(0,(3)*phi_trkMinus))*TComplex::Exp(TComplex(0,(3)*phi_trkMinus)) * TComplex::Conjugate(QhfPlus[ibin][2])*TComplex::Conjugate(QhfPlus[ibin][2]);
         if(useRe) tempReal=temp.Re();
         else tempReal=TComplex::Abs(temp);
         hv6V3starV3starSub[ibin][cpt]->Fill(tempReal);
         //if(fabs(sumWPlus[ibin]*sumWPlus[ibin]-sumW2Plus[ibin])>0.00001) hv6V3starV3starSub[ibin][cpt]->Fill(tempReal*sumWPlus[ibin]*sumWPlus[ibin]/(sumWPlus[ibin]*sumWPlus[ibin]-sumW2Plus[ibin]));
         //else hv6V3starV3starSub[ibin][cpt]->Fill(tempReal);
         temp=TComplex::Exp(TComplex(0,(5)*phi_trkMinus))*TComplex::Conjugate(QhfPlus[ibin][1])*TComplex::Conjugate(QhfPlus[ibin][2]);
         if(useRe) tempReal=temp.Re();
         else tempReal=TComplex::Abs(temp);
         hv5V2starV3star[ibin][cpt]->Fill(tempReal);
         temp=TComplex::Exp(TComplex(0,(5)*phi_trkMinus))*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfPlus[ibin][2]);
         if(useRe) tempReal=temp.Re();
         else tempReal=TComplex::Abs(temp);
         hv5V2starV3starAB[ibin][cpt]->Fill(tempReal);
         //temp=TComplex::Exp(TComplex(0,(5)*phi_trkMinus))*TComplex::Conjugate(QhfPlus[ibin][1])*TComplex::Conjugate(QhfPlus[ibin][2]) - TComplex::Exp(TComplex(0,(5)*phi_trkMinus))*TComplex::Conjugate(Qhf2p3Plus[ibin]);
         temp=TComplex::Exp(TComplex(0,(2)*phi_trkMinus))*TComplex::Exp(TComplex(0,(3)*phi_trkMinus)) * TComplex::Conjugate(QhfPlus[ibin][1])*TComplex::Conjugate(QhfPlus[ibin][2]);
         if(useRe) tempReal=temp.Re();
         else tempReal=TComplex::Abs(temp);
         hv5V2starV3starSub[ibin][cpt]->Fill(tempReal);
         //if(fabs(sumWPlus[ibin]*sumWPlus[ibin]-sumW2Plus[ibin])>0.00001) hv5V2starV3starSub[ibin][cpt]->Fill(tempReal*sumWPlus[ibin]*sumWPlus[ibin]/(sumWPlus[ibin]*sumWPlus[ibin]-sumW2Plus[ibin]));
         //else hv5V2starV3starSub[ibin][cpt]->Fill(tempReal);
         temp=TComplex::Exp(TComplex(0,(7)*phi_trkMinus))*TComplex::Conjugate(QhfPlus[ibin][1])*TComplex::Conjugate(QhfPlus[ibin][1])*TComplex::Conjugate(QhfPlus[ibin][2]);
         if(useRe) tempReal=temp.Re();
         else tempReal=TComplex::Abs(temp);
         hv7V2starV2starV3star[ibin][cpt]->Fill(tempReal);
         temp=TComplex::Exp(TComplex(0,(7)*phi_trkMinus))*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfPlus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][2]);
         if(useRe) tempReal=temp.Re();
         else tempReal=TComplex::Abs(temp);
         hv7V2starV2starV3starAB[ibin][cpt]->Fill(tempReal);
         //temp=TComplex::Exp(TComplex(0,(7)*phi_trkMinus))*TComplex::Conjugate(QhfPlus[ibin][1])*TComplex::Conjugate(QhfPlus[ibin][1])*TComplex::Conjugate(QhfPlus[ibin][2]) - 2*TComplex::Exp(TComplex(0,(7)*phi_trkMinus))*TComplex::Conjugate(QhfPlus[ibin][1])*TComplex::Conjugate(Qhf2p3Plus[ibin]) - TComplex::Exp(TComplex(0,(7)*phi_trkMinus))*TComplex::Conjugate(QhfPlus[ibin][2])*TComplex::Conjugate(Qhf2p2Plus[ibin]) + 2*TComplex::Exp(TComplex(0,(7)*phi_trkMinus))*TComplex::Conjugate(Qhf2p2p3Plus[ibin]);
         temp=TComplex::Exp(TComplex(0,(2)*phi_trkMinus))*TComplex::Exp(TComplex(0,(2)*phi_trkMinus))*TComplex::Exp(TComplex(0,(3)*phi_trkMinus)) * TComplex::Conjugate(QhfPlus[ibin][1])*TComplex::Conjugate(QhfPlus[ibin][1])*TComplex::Conjugate(QhfPlus[ibin][2]);
         if(useRe) tempReal=temp.Re();
         else tempReal=TComplex::Abs(temp);
         hv7V2starV2starV3starSub[ibin][cpt]->Fill(tempReal);
         //if(fabs(sumWMinus[ibin]*sumWMinus[ibin]*sumWMinus[ibin]-3*sumW2Minus[ibin]*sumWMinus[ibin]+2*sumW3Minus[ibin])>0.00001) hv7V2starV2starV3starSub[ibin][cpt]->Fill(tempReal*sumWMinus[ibin]*sumWMinus[ibin]*sumWMinus[ibin]/(sumWMinus[ibin]*sumWMinus[ibin]*sumWMinus[ibin]-3*sumW2Minus[ibin]*sumWMinus[ibin]+2*sumW3Minus[ibin]));
         //else hv7V2starV2starV3starSub[ibin][cpt]->Fill(tempReal);
         temp=TComplex::Exp(TComplex(0,(8)*phi_trkMinus))*TComplex::Conjugate(QhfPlus[ibin][1])*TComplex::Conjugate(QhfPlus[ibin][1])*TComplex::Conjugate(QhfPlus[ibin][1])*TComplex::Conjugate(QhfPlus[ibin][1]);
         if(useRe) tempReal=temp.Re();
         else tempReal=TComplex::Abs(temp);
         hv8V2starV2starV2starV2star[ibin][cpt]->Fill(tempReal);
         temp=TComplex::Exp(TComplex(0,(8)*phi_trkMinus))*TComplex::Conjugate(QhfPlus[ibin][1])*TComplex::Conjugate(QhfPlus[ibin][2])*TComplex::Conjugate(QhfPlus[ibin][2]);
         if(useRe) tempReal=temp.Re();
         else tempReal=TComplex::Abs(temp);
         hv8V2starV3starV3star[ibin][cpt]->Fill(tempReal);

         hMeanPt[ibin][cpt]->Fill(pt_trkMinus);
       }

       for(int iH=0; iH<nHarmonics; iH++){
         for(int ipt=0; ipt<nPtBin; ipt++){
           //if(sumwtrkPt[ipt]>0) QtrkPt[ibin][iH][ipt]=QtrkPt[ibin][iH][ipt]/sumwtrkPt[ipt] - TComplex(meanQxTrkPt[ibin][iH][ipt], meanQyTrkPt[ibin][iH][ipt]); // re-centering
           if(sumwtrkPt[ipt]>0) QtrkPt[ibin][iH][ipt]=QtrkPt[ibin][iH][ipt]/sumwtrkPt[ipt];
           else QtrkPt[ibin][iH][ipt]=0;
         }
       }

       for(int iH=0; iH<nHarmonics; iH++){
         for(int iPt=0; iPt<nPtBin; iPt++){
           hQtrkPtX[ibin][iH][iPt]->Fill(QtrkPt[ibin][iH][iPt].Re());
           hQtrkPtY[ibin][iH][iPt]->Fill(QtrkPt[ibin][iH][iPt].Im());
         }
       }

       for(int ipt=0; ipt<nPtBin; ipt++){
         hq4Q2starQ2starAA[ibin][ipt]->Fill(QtrkPt[ibin][3][ipt]*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][1]));
         hq4Q2starQ2starBB[ibin][ipt]->Fill(QtrkPt[ibin][3][ipt]*TComplex::Conjugate(QhfPlus[ibin][1])*TComplex::Conjugate(QhfPlus[ibin][1]));
         hq4Q2starQ2starAB[ibin][ipt]->Fill(QtrkPt[ibin][3][ipt]*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfPlus[ibin][1]));
         hq6Q2starQ2starQ2starAA[ibin][ipt]->Fill(QtrkPt[ibin][5][ipt]*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][1]));
         hq6Q2starQ2starQ2starBB[ibin][ipt]->Fill(QtrkPt[ibin][5][ipt]*TComplex::Conjugate(QhfPlus[ibin][1])*TComplex::Conjugate(QhfPlus[ibin][1])*TComplex::Conjugate(QhfPlus[ibin][1]));
         hq6Q2starQ2starQ2starAB[ibin][ipt]->Fill(QtrkPt[ibin][5][ipt]*TComplex::Conjugate(QhfPlus[ibin][1])*TComplex::Conjugate(QhfPlus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][1]));
         hq6Q3starQ3starAA[ibin][ipt]->Fill(QtrkPt[ibin][5][ipt]*TComplex::Conjugate(QhfMinus[ibin][2])*TComplex::Conjugate(QhfMinus[ibin][2]));
         hq6Q3starQ3starBB[ibin][ipt]->Fill(QtrkPt[ibin][5][ipt]*TComplex::Conjugate(QhfPlus[ibin][2])*TComplex::Conjugate(QhfPlus[ibin][2]));
         hq6Q3starQ3starAB[ibin][ipt]->Fill(QtrkPt[ibin][5][ipt]*TComplex::Conjugate(QhfMinus[ibin][2])*TComplex::Conjugate(QhfPlus[ibin][2]));
         hq5Q2starQ3starAA[ibin][ipt]->Fill(QtrkPt[ibin][4][ipt]*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][2]));
         hq5Q2starQ3starBB[ibin][ipt]->Fill(QtrkPt[ibin][4][ipt]*TComplex::Conjugate(QhfPlus[ibin][1])*TComplex::Conjugate(QhfPlus[ibin][2]));
         hq5Q2starQ3starAB[ibin][ipt]->Fill(QtrkPt[ibin][4][ipt]*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfPlus[ibin][2]));
         hq7Q2starQ2starQ3starAA[ibin][ipt]->Fill(QtrkPt[ibin][6][ipt]*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][2]));
         hq7Q2starQ2starQ3starBB[ibin][ipt]->Fill(QtrkPt[ibin][6][ipt]*TComplex::Conjugate(QhfPlus[ibin][1])*TComplex::Conjugate(QhfPlus[ibin][1])*TComplex::Conjugate(QhfPlus[ibin][2]));
         hq7Q2starQ2starQ3starAB[ibin][ipt]->Fill(QtrkPt[ibin][6][ipt]*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfPlus[ibin][2]));
         hQ2Abs4AA[ibin][ipt]->Fill(QtrkPt[ibin][1][ipt]*QtrkPt[ibin][1][ipt]*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][1]));
         hQ2Abs4BB[ibin][ipt]->Fill(QtrkPt[ibin][1][ipt]*QtrkPt[ibin][1][ipt]*TComplex::Conjugate(QhfPlus[ibin][1])*TComplex::Conjugate(QhfPlus[ibin][1]));
         hQ2Abs4AB[ibin][ipt]->Fill(QtrkPt[ibin][1][ipt]*QtrkPt[ibin][1][ipt]*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfPlus[ibin][1]));
         hQ2Abs6AA[ibin][ipt]->Fill(QtrkPt[ibin][1][ipt]*QtrkPt[ibin][1][ipt]*QtrkPt[ibin][1][ipt]*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][1]));
         hQ2Abs6BB[ibin][ipt]->Fill(QtrkPt[ibin][1][ipt]*QtrkPt[ibin][1][ipt]*QtrkPt[ibin][1][ipt]*TComplex::Conjugate(QhfPlus[ibin][1])*TComplex::Conjugate(QhfPlus[ibin][1])*TComplex::Conjugate(QhfPlus[ibin][1]));
         hQ2Abs6AB[ibin][ipt]->Fill(QtrkPt[ibin][1][ipt]*QtrkPt[ibin][1][ipt]*QtrkPt[ibin][1][ipt]*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfPlus[ibin][1]));
         hQ3Abs4AA[ibin][ipt]->Fill(QtrkPt[ibin][2][ipt]*QtrkPt[ibin][2][ipt]*TComplex::Conjugate(QhfMinus[ibin][2])*TComplex::Conjugate(QhfMinus[ibin][2]));
         hQ3Abs4BB[ibin][ipt]->Fill(QtrkPt[ibin][2][ipt]*QtrkPt[ibin][2][ipt]*TComplex::Conjugate(QhfPlus[ibin][2])*TComplex::Conjugate(QhfPlus[ibin][2]));
         hQ3Abs4AB[ibin][ipt]->Fill(QtrkPt[ibin][2][ipt]*QtrkPt[ibin][2][ipt]*TComplex::Conjugate(QhfMinus[ibin][2])*TComplex::Conjugate(QhfPlus[ibin][2]));
         hQ2Abs2Q3Abs2AA[ibin][ipt]->Fill(QtrkPt[ibin][1][ipt]*QtrkPt[ibin][2][ipt]*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][2]));
         hQ2Abs2Q3Abs2BB[ibin][ipt]->Fill(QtrkPt[ibin][1][ipt]*QtrkPt[ibin][2][ipt]*TComplex::Conjugate(QhfPlus[ibin][1])*TComplex::Conjugate(QhfPlus[ibin][2]));
         hQ2Abs2Q3Abs2AB[ibin][ipt]->Fill(QtrkPt[ibin][1][ipt]*QtrkPt[ibin][2][ipt]*TComplex::Conjugate(QhfPlus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][2]));
         hQ2Abs4Q3Abs2AA[ibin][ipt]->Fill(QtrkPt[ibin][1][ipt]*QtrkPt[ibin][1][ipt]*QtrkPt[ibin][2][ipt]*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][2]));
         hQ2Abs4Q3Abs2BB[ibin][ipt]->Fill(QtrkPt[ibin][1][ipt]*QtrkPt[ibin][1][ipt]*QtrkPt[ibin][2][ipt]*TComplex::Conjugate(QhfPlus[ibin][1])*TComplex::Conjugate(QhfPlus[ibin][1])*TComplex::Conjugate(QhfPlus[ibin][2]));
         hQ2Abs4Q3Abs2AB[ibin][ipt]->Fill(QtrkPt[ibin][1][ipt]*QtrkPt[ibin][1][ipt]*QtrkPt[ibin][2][ipt]*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfPlus[ibin][2]));


       }


       delete pVect_trkEtaPlus;
       delete pVect_trkEtaMinus;
       delete pVect_hfEtaPlus;
       delete pVect_hfEtaMinus;



#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif
   
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
}


// ------------ method called once each job just before starting event loop  ------------
void 
FlowCorr::beginJob()
{
  //for(int i=0; i<nPtEffBin; i++) EffVsPtHist->SetBinContent(i+1, effValues[i]);
  for(int i=0; i<nPtEffBin; i++) EffVsPtHist->SetBinContent(i+1, 1.0);
  TH1D::SetDefaultSumw2();
  hCent = fs->make<TH1D>("centrality","PbPb Centrality",200,0,200);
  hHF = fs->make<TH1D>("hf","HF ET",8000,0,8000);
  hAngle = fs->make<TH1D>("angle","EP angle",200,-4,4);
  hAngleFlat = fs->make<TH1D>("angleFlat","EP angle",200,-4,4);
  hvz = fs->make<TH1D>("vz","vertex z",300,-30,30);
  hvx = fs->make<TH1D>("vx","vertex x",200,-0.5,0.5);
  hvy = fs->make<TH1D>("vy","vertex y",200,-0.5,0.5);
  hNtrks = fs->make<TH1D>("ntrks","number of tracks",3000,0,3000);
  hpt = fs->make<TH1D>("pt","pt",200,0,20);
  heta = fs->make<TH1D>("eta","eta",300,-3,3);
  hphi = fs->make<TH1D>("phi","phi",200,-4,4);
  hHFcal = fs->make<TH1D>("hfCal","HF ET",8000,0,8000);

  hMultTrkEtaPlus = fs->make<TH1D>("multtrketaplus","N",300,0,3000);
  hMultTrkEtaMinus = fs->make<TH1D>("multtrketaminus","N",300,0,3000);
  hMultHFEtaPlus = fs->make<TH1D>("multhfetaplus","N",400,0,4000);
  hMultHFEtaMinus = fs->make<TH1D>("multhfetaminus","N",400,0,4000);
  for(int ibin=0; ibin<nCentBin; ibin++){
    for(int iH=0; iH<nHarmonics; iH++){
      hQhfPlusX[ibin][iH] = fs->make<TH1D>(Form("hQhfPlusX_ibin%d_iH%d",ibin,iH),"",200,-1000,1000);
      hQhfPlusY[ibin][iH] = fs->make<TH1D>(Form("hQhfPlusY_ibin%d_iH%d",ibin,iH),"",200,-1000,1000);
      hQhfPlusQ[ibin][iH] = fs->make<TH1D>(Form("hQhfPlusQ_ibin%d_iH%d",ibin,iH),"",200,-1000,1000);
      hQhfMinusX[ibin][iH] = fs->make<TH1D>(Form("hQhfMinusX_ibin%d_iH%d",ibin,iH),"",200,-1000,1000);
      hQhfMinusY[ibin][iH] = fs->make<TH1D>(Form("hQhfMinusY_ibin%d_iH%d",ibin,iH),"",200,-1000,1000);
      hQhfMinusQ[ibin][iH] = fs->make<TH1D>(Form("hQhfMinusQ_ibin%d_iH%d",ibin,iH),"",200,-1000,1000);
      hQtrkPlusX[ibin][iH] = fs->make<TH1D>(Form("hQtrkPlusX_ibin%d_iH%d",ibin,iH),"",200,-1000,1000);
      hQtrkPlusY[ibin][iH] = fs->make<TH1D>(Form("hQtrkPlusY_ibin%d_iH%d",ibin,iH),"",200,-1000,1000);
      hQtrkMinusX[ibin][iH] = fs->make<TH1D>(Form("hQtrkMinusX_ibin%d_iH%d",ibin,iH),"",200,-1000,1000);
      hQtrkMinusY[ibin][iH] = fs->make<TH1D>(Form("hQtrkMinusY_ibin%d_iH%d",ibin,iH),"",200,-1000,1000);
      for(int iPt=0; iPt<nPtBin; iPt++){
        hQtrkPtX[ibin][iH][iPt] = fs->make<TH1D>(Form("hQtrkPtX_ibin%d_iH%d_iPt%d",ibin,iH,iPt),"",200,-1000,1000);
        hQtrkPtY[ibin][iH][iPt] = fs->make<TH1D>(Form("hQtrkPtY_ibin%d_iH%d_iPt%d",ibin,iH,iPt),"",200,-1000,1000);
      }
      hVnAbs2[ibin][iH] = fs->make<TH1D>(Form("hVnAbs2_ibin%d_iH%d",ibin,iH),"",200,-1000,1000);
      hVnAbs4[ibin][iH] = fs->make<TH1D>(Form("hVnAbs4_ibin%d_iH%d",ibin,iH),"",200,-1000,1000);
      hVnAbs6[ibin][iH] = fs->make<TH1D>(Form("hVnAbs6_ibin%d_iH%d",ibin,iH),"",200,-1000,1000);
      hVnAbs8[ibin][iH] = fs->make<TH1D>(Form("hVnAbs8_ibin%d_iH%d",ibin,iH),"",200,-1000,1000);
    }
    hV2Abs2V3Abs2[ibin] = fs->make<TH1D>(Form("hV2Abs2V3Abs2_ibin%d",ibin),"",200,-1000,1000);
    hV2Abs4V3Abs2[ibin] = fs->make<TH1D>(Form("hV2Abs4V3Abs2_ibin%d",ibin),"",200,-1000,1000);
    hV2Abs2V3Abs4[ibin] = fs->make<TH1D>(Form("hV2Abs2V3Abs4_ibin%d",ibin),"",200,-1000,1000);
    //trk
    hV2Abs4trk1[ibin] = fs->make<TH1D>(Form("hV2Abs4trk1_ibin%d",ibin),"",200,-1000,1000);
    hV2Abs6trk1[ibin] = fs->make<TH1D>(Form("hV2Abs6trk1_ibin%d",ibin),"",200,-1000,1000);
    hV3Abs4trk1[ibin] = fs->make<TH1D>(Form("hV3Abs4trk1_ibin%d",ibin),"",200,-1000,1000);
    hV2Abs2V3Abs2trk1[ibin] = fs->make<TH1D>(Form("hV2Abs2V3Abs2trk1_ibin%d",ibin),"",200,-1000,1000);
    hV2Abs4V3Abs2trk1[ibin] = fs->make<TH1D>(Form("hV2Abs4V3Abs2trk1_ibin%d",ibin),"",200,-1000,1000);
    hV2Abs4trk12[ibin] = fs->make<TH1D>(Form("hV2Abs4trk12_ibin%d",ibin),"",200,-1000,1000);
    hV2Abs6trk12[ibin] = fs->make<TH1D>(Form("hV2Abs6trk12_ibin%d",ibin),"",200,-1000,1000);
    hV3Abs4trk12[ibin] = fs->make<TH1D>(Form("hV3Abs4trk12_ibin%d",ibin),"",200,-1000,1000);
    hV2Abs2V3Abs2trk12[ibin] = fs->make<TH1D>(Form("hV2Abs2V3Abs2trk12_ibin%d",ibin),"",200,-1000,1000);
    hV2Abs4V3Abs2trk12[ibin] = fs->make<TH1D>(Form("hV2Abs4V3Abs2trk12_ibin%d",ibin),"",200,-1000,1000);    
    hV2Abs4trk2[ibin] = fs->make<TH1D>(Form("hV2Abs4trk2_ibin%d",ibin),"",200,-1000,1000);
    hV2Abs6trk2[ibin] = fs->make<TH1D>(Form("hV2Abs6trk2_ibin%d",ibin),"",200,-1000,1000);
    hV3Abs4trk2[ibin] = fs->make<TH1D>(Form("hV3Abs4trk2_ibin%d",ibin),"",200,-1000,1000);
    hV2Abs2V3Abs2trk2[ibin] = fs->make<TH1D>(Form("hV2Abs2V3Abs2trk2_ibin%d",ibin),"",200,-1000,1000);
    hV2Abs4V3Abs2trk2[ibin] = fs->make<TH1D>(Form("hV2Abs4V3Abs2trk2_ibin%d",ibin),"",200,-1000,1000);

    //Only Qtrk
    hV2V2starQtrk[ibin] = fs->make<TH1D>(Form("hV2V2starQtrk_ibin%d",ibin),"",200,-1000,1000);
    hV4V2starV2starQtrk[ibin] = fs->make<TH1D>(Form("hV4V2starV2starQtrk_ibin%d",ibin),"",200,-1000,1000);
    hV6V2starV2starV2starQtrk[ibin] = fs->make<TH1D>(Form("hV6V2starV2starV2starQtrk_ibin%d",ibin),"",200,-1000,1000);
    hV6V3starV3starQtrk[ibin] = fs->make<TH1D>(Form("hV6V3starV3starQtrk_ibin%d",ibin),"",200,-1000,1000);
    hV5V2starV3starQtrk[ibin] = fs->make<TH1D>(Form("hV5V2starV3starQtrk_ibin%d",ibin),"",200,-1000,1000);
    hV7V2starV2starV3starQtrk[ibin] = fs->make<TH1D>(Form("hV7V2starV2starV3starQtrk_ibin%d",ibin),"",200,-1000,1000);
    hV2Abs2Qtrk[ibin] = fs->make<TH1D>(Form("hV2Abs2Qtrk_ibin%d",ibin),"",200,-1000,1000);
    hV2Abs4Qtrk[ibin] = fs->make<TH1D>(Form("hV2Abs4Qtrk_ibin%d",ibin),"",200,-1000,1000);
    hV2Abs6Qtrk[ibin] = fs->make<TH1D>(Form("hV2Abs6Qtrk_ibin%d",ibin),"",200,-1000,1000);
    hV3Abs4Qtrk[ibin] = fs->make<TH1D>(Form("hV3Abs4Qtrk_ibin%d",ibin),"",200,-1000,1000);
    hV2Abs2V3Abs2Qtrk[ibin] = fs->make<TH1D>(Form("hV2Abs2V3Abs2Qtrk_ibin%d",ibin),"",200,-1000,1000);
    hV2Abs4V3Abs2Qtrk[ibin] = fs->make<TH1D>(Form("hV2Abs4V3Abs2Qtrk_ibin%d",ibin),"",200,-1000,1000);
    //Only QtrkHF
    hV2V2starQtrkHF[ibin] = fs->make<TH1D>(Form("hV2V2starQtrkHF_ibin%d",ibin),"",200,-1000,1000);
    hV4V2starV2starQtrkHF[ibin] = fs->make<TH1D>(Form("hV4V2starV2starQtrkHF_ibin%d",ibin),"",200,-1000,1000);
    hV6V2starV2starV2starQtrkHF[ibin] = fs->make<TH1D>(Form("hV6V2starV2starV2starQtrkHF_ibin%d",ibin),"",200,-1000,1000);
    hV6V3starV3starQtrkHF[ibin] = fs->make<TH1D>(Form("hV6V3starV3starQtrkHF_ibin%d",ibin),"",200,-1000,1000);
    hV5V2starV3starQtrkHF[ibin] = fs->make<TH1D>(Form("hV5V2starV3starQtrkHF_ibin%d",ibin),"",200,-1000,1000);
    hV7V2starV2starV3starQtrkHF[ibin] = fs->make<TH1D>(Form("hV7V2starV2starV3starQtrkHF_ibin%d",ibin),"",200,-1000,1000);
    hV2Abs2QtrkHF[ibin] = fs->make<TH1D>(Form("hV2Abs2QtrkHF_ibin%d",ibin),"",200,-1000,1000);
    hV2Abs4QtrkHF[ibin] = fs->make<TH1D>(Form("hV2Abs4QtrkHF_ibin%d",ibin),"",200,-1000,1000);
    hV2Abs6QtrkHF[ibin] = fs->make<TH1D>(Form("hV2Abs6QtrkHF_ibin%d",ibin),"",200,-1000,1000);
    hV3Abs4QtrkHF[ibin] = fs->make<TH1D>(Form("hV3Abs4QtrkHF_ibin%d",ibin),"",200,-1000,1000);
    hV2Abs2V3Abs2QtrkHF[ibin] = fs->make<TH1D>(Form("hV2Abs2V3Abs2QtrkHF_ibin%d",ibin),"",200,-1000,1000);
    hV2Abs4V3Abs2QtrkHF[ibin] = fs->make<TH1D>(Form("hV2Abs4V3Abs2QtrkHF_ibin%d",ibin),"",200,-1000,1000);

    hV2V2star[ibin] = fs->make<TH1D>(Form("hV2V2star_ibin%d",ibin),"",200,-1000,1000);
    hV4V2starV2star[ibin] = fs->make<TH1D>(Form("hV4V2starV2star_ibin%d",ibin),"",200,-1000,1000);
    hV6V2starV2starV2star[ibin] = fs->make<TH1D>(Form("hV6V2starV2starV2star_ibin%d",ibin),"",200,-1000,1000);
    hV6V3starV3star[ibin] = fs->make<TH1D>(Form("hV6V3starV3star_ibin%d",ibin),"",200,-1000,1000);
    hV5V2starV3star[ibin] = fs->make<TH1D>(Form("hV5V2starV3star_ibin%d",ibin),"",200,-1000,1000);
    hV7V2starV2starV3star[ibin] = fs->make<TH1D>(Form("hV7V2starV2starV3star_ibin%d",ibin),"",200,-1000,1000);
    for(int ipt=0; ipt<nPtBin; ipt++){
      hv2V2star[ibin][ipt] = fs->make<TH1D>(Form("hv2V2star_ibin%d_ipt%d",ibin,ipt),"",200,-1000,1000);
      hv3V3star[ibin][ipt] = fs->make<TH1D>(Form("hv3V3star_ibin%d_ipt%d",ibin,ipt),"",200,-1000,1000);
      hv4V4star[ibin][ipt] = fs->make<TH1D>(Form("hv4V4star_ibin%d_ipt%d",ibin,ipt),"",200,-1000,1000);
      hv5V5star[ibin][ipt] = fs->make<TH1D>(Form("hv5V5star_ibin%d_ipt%d",ibin,ipt),"",200,-1000,1000);
      hv6V6star[ibin][ipt] = fs->make<TH1D>(Form("hv6V6star_ibin%d_ipt%d",ibin,ipt),"",200,-1000,1000);
      hv7V7star[ibin][ipt] = fs->make<TH1D>(Form("hv7V7star_ibin%d_ipt%d",ibin,ipt),"",200,-1000,1000);
      hv8V8star[ibin][ipt] = fs->make<TH1D>(Form("hv8V8star_ibin%d_ipt%d",ibin,ipt),"",200,-1000,1000);
      hv4V2starV2star[ibin][ipt] = fs->make<TH1D>(Form("hv4V2starV2star_ibin%d_ipt%d",ibin,ipt),"",200,-1000,1000);
      hv4V2starV2starAB[ibin][ipt] = fs->make<TH1D>(Form("hv4V2starV2starAB_ibin%d_ipt%d",ibin,ipt),"",200,-1000,1000);
      hv4V2starV2starSub[ibin][ipt] = fs->make<TH1D>(Form("hv4V2starV2starSub_ibin%d_ipt%d",ibin,ipt),"",200,-1000,1000);
      hv6V2starV2starV2star[ibin][ipt] = fs->make<TH1D>(Form("hv6V2starV2starV2star_ibin%d_ipt%d",ibin,ipt),"",200,-1000,1000);
      hv6V2starV2starV2starAB[ibin][ipt] = fs->make<TH1D>(Form("hv6V2starV2starV2starAB_ibin%d_ipt%d",ibin,ipt),"",200,-1000,1000);
      hv6V2starV2starV2starSub[ibin][ipt] = fs->make<TH1D>(Form("hv6V2starV2starV2starSub_ibin%d_ipt%d",ibin,ipt),"",200,-1000,1000);
      hv6V3starV3star[ibin][ipt] = fs->make<TH1D>(Form("hv6V3starV3star_ibin%d_ipt%d",ibin,ipt),"",200,-1000,1000);
      hv6V3starV3starAB[ibin][ipt] = fs->make<TH1D>(Form("hv6V3starV3starAB_ibin%d_ipt%d",ibin,ipt),"",200,-1000,1000);
      hv6V3starV3starSub[ibin][ipt] = fs->make<TH1D>(Form("hv6V3starV3starSub_ibin%d_ipt%d",ibin,ipt),"",200,-1000,1000);
      hv5V2starV3star[ibin][ipt] = fs->make<TH1D>(Form("hv5V2starV3star_ibin%d_ipt%d",ibin,ipt),"",200,-1000,1000);
      hv5V2starV3starAB[ibin][ipt] = fs->make<TH1D>(Form("hv5V2starV3starAB_ibin%d_ipt%d",ibin,ipt),"",200,-1000,1000);
      hv5V2starV3starSub[ibin][ipt] = fs->make<TH1D>(Form("hv5V2starV3starSub_ibin%d_ipt%d",ibin,ipt),"",200,-1000,1000);
      hv7V2starV2starV3star[ibin][ipt] = fs->make<TH1D>(Form("hv7V2starV2starV3star_ibin%d_ipt%d",ibin,ipt),"",200,-1000,1000);
      hv7V2starV2starV3starAB[ibin][ipt] = fs->make<TH1D>(Form("hv7V2starV2starV3starAB_ibin%d_ipt%d",ibin,ipt),"",200,-1000,1000);
      hv7V2starV2starV3starSub[ibin][ipt] = fs->make<TH1D>(Form("hv7V2starV2starV3starSub_ibin%d_ipt%d",ibin,ipt),"",200,-1000,1000);
      hv8V2starV2starV2starV2star[ibin][ipt] = fs->make<TH1D>(Form("hv8V2starV2starV2starV2star_ibin%d_ipt%d",ibin,ipt),"",200,-1000,1000);
      hv8V2starV3starV3star[ibin][ipt] = fs->make<TH1D>(Form("hv8V2starV3starV3star_ibin%d_ipt%d",ibin,ipt),"",200,-1000,1000);

      hq4Q2starQ2starAA[ibin][ipt] = fs->make<TH1D>(Form("hq4Q2starQ2starAA_ibin%d_ipt%d",ibin,ipt),"",200,-1000,1000);
      hq4Q2starQ2starBB[ibin][ipt] = fs->make<TH1D>(Form("hq4Q2starQ2starBB_ibin%d_ipt%d",ibin,ipt),"",200,-1000,1000);
      hq4Q2starQ2starAB[ibin][ipt] = fs->make<TH1D>(Form("hq4Q2starQ2starAB_ibin%d_ipt%d",ibin,ipt),"",200,-1000,1000);
      hq6Q2starQ2starQ2starAA[ibin][ipt] = fs->make<TH1D>(Form("hq6Q2starQ2starQ2starAA_ibin%d_ipt%d",ibin,ipt),"",200,-1000,1000);
      hq6Q2starQ2starQ2starBB[ibin][ipt] = fs->make<TH1D>(Form("hq6Q2starQ2starQ2starBB_ibin%d_ipt%d",ibin,ipt),"",200,-1000,1000);
      hq6Q2starQ2starQ2starAB[ibin][ipt] = fs->make<TH1D>(Form("hq6Q2starQ2starQ2starAB_ibin%d_ipt%d",ibin,ipt),"",200,-1000,1000);
      hq6Q3starQ3starAA[ibin][ipt] = fs->make<TH1D>(Form("hq6Q3starQ3starAA_ibin%d_ipt%d",ibin,ipt),"",200,-1000,1000);
      hq6Q3starQ3starBB[ibin][ipt] = fs->make<TH1D>(Form("hq6Q3starQ3starBB_ibin%d_ipt%d",ibin,ipt),"",200,-1000,1000);
      hq6Q3starQ3starAB[ibin][ipt] = fs->make<TH1D>(Form("hq6Q3starQ3starAB_ibin%d_ipt%d",ibin,ipt),"",200,-1000,1000);
      hq5Q2starQ3starAA[ibin][ipt] = fs->make<TH1D>(Form("hq5Q2starQ3starAA_ibin%d_ipt%d",ibin,ipt),"",200,-1000,1000);
      hq5Q2starQ3starBB[ibin][ipt] = fs->make<TH1D>(Form("hq5Q2starQ3starBB_ibin%d_ipt%d",ibin,ipt),"",200,-1000,1000);
      hq5Q2starQ3starAB[ibin][ipt] = fs->make<TH1D>(Form("hq5Q2starQ3starAB_ibin%d_ipt%d",ibin,ipt),"",200,-1000,1000);
      hq7Q2starQ2starQ3starAA[ibin][ipt] = fs->make<TH1D>(Form("hq7Q2starQ2starQ3starAA_ibin%d_ipt%d",ibin,ipt),"",200,-1000,1000);
      hq7Q2starQ2starQ3starBB[ibin][ipt] = fs->make<TH1D>(Form("hq7Q2starQ2starQ3starBB_ibin%d_ipt%d",ibin,ipt),"",200,-1000,1000);
      hq7Q2starQ2starQ3starAB[ibin][ipt] = fs->make<TH1D>(Form("hq7Q2starQ2starQ3starAB_ibin%d_ipt%d",ibin,ipt),"",200,-1000,1000);
      hQ2Abs4AA[ibin][ipt] = fs->make<TH1D>(Form("hQ2Abs4AA_ibin%d_ipt%d",ibin,ipt),"",200,-1000,1000);
      hQ2Abs4BB[ibin][ipt] = fs->make<TH1D>(Form("hQ2Abs4BB_ibin%d_ipt%d",ibin,ipt),"",200,-1000,1000);
      hQ2Abs4AB[ibin][ipt] = fs->make<TH1D>(Form("hQ2Abs4AB_ibin%d_ipt%d",ibin,ipt),"",200,-1000,1000);
      hQ2Abs6AA[ibin][ipt] = fs->make<TH1D>(Form("hQ2Abs6AA_ibin%d_ipt%d",ibin,ipt),"",200,-1000,1000);
      hQ2Abs6BB[ibin][ipt] = fs->make<TH1D>(Form("hQ2Abs6BB_ibin%d_ipt%d",ibin,ipt),"",200,-1000,1000);
      hQ2Abs6AB[ibin][ipt] = fs->make<TH1D>(Form("hQ2Abs6AB_ibin%d_ipt%d",ibin,ipt),"",200,-1000,1000);
      hQ3Abs4AA[ibin][ipt] = fs->make<TH1D>(Form("hQ3Abs4AA_ibin%d_ipt%d",ibin,ipt),"",200,-1000,1000);
      hQ3Abs4BB[ibin][ipt] = fs->make<TH1D>(Form("hQ3Abs4BB_ibin%d_ipt%d",ibin,ipt),"",200,-1000,1000);
      hQ3Abs4AB[ibin][ipt] = fs->make<TH1D>(Form("hQ3Abs4AB_ibin%d_ipt%d",ibin,ipt),"",200,-1000,1000);
      hQ2Abs2Q3Abs2AA[ibin][ipt] = fs->make<TH1D>(Form("hQ2Abs2Q3Abs2AA_ibin%d_ipt%d",ibin,ipt),"",200,-1000,1000);
      hQ2Abs2Q3Abs2BB[ibin][ipt] = fs->make<TH1D>(Form("hQ2Abs2Q3Abs2BB_ibin%d_ipt%d",ibin,ipt),"",200,-1000,1000);
      hQ2Abs2Q3Abs2AB[ibin][ipt] = fs->make<TH1D>(Form("hQ2Abs2Q3Abs2AB_ibin%d_ipt%d",ibin,ipt),"",200,-1000,1000);
      hQ2Abs4Q3Abs2AA[ibin][ipt] = fs->make<TH1D>(Form("hQ2Abs4Q3Abs2AA_ibin%d_ipt%d",ibin,ipt),"",200,-1000,1000);
      hQ2Abs4Q3Abs2BB[ibin][ipt] = fs->make<TH1D>(Form("hQ2Abs4Q3Abs2BB_ibin%d_ipt%d",ibin,ipt),"",200,-1000,1000);
      hQ2Abs4Q3Abs2AB[ibin][ipt] = fs->make<TH1D>(Form("hQ2Abs4Q3Abs2AB_ibin%d_ipt%d",ibin,ipt),"",200,-1000,1000);


      hMeanPt[ibin][ipt] = fs->make<TH1D>(Form("hMeanPt_ibin%d_ipt%d",ibin,ipt),"",200,0,20);
    }
  }

}

// ------------ method called once each job just after ending the event loop  ------------
void 
FlowCorr::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
FlowCorr::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(FlowCorr);
