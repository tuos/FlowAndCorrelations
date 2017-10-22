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
#include "DataFormats/VertexReco/interface/VertexFwd.h"
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
  double chi2nPixelMax_;
  double dzRelPixelCut_;
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
  chi2nPixelMax_(iConfig.getParameter<double>("chi2nPixelMax")),
  dzRelPixelCut_(iConfig.getParameter<double>("dzRelPixelCut")),
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

    Int_t runID = iEvent.id().run();
    for(int ibin=0; ibin<nCentBin; ibin++){
      for(int iH=0; iH<nHarmonics; iH++){
        if(runID>=262548 && runID<=262799){ 
          meanQxPlus[ibin][iH] = meanQxPlusA[ibin][iH];
          meanQyPlus[ibin][iH] = meanQyPlusA[ibin][iH];
          meanQxMinus[ibin][iH] = meanQxMinusA[ibin][iH];
          meanQyMinus[ibin][iH] = meanQyMinusA[ibin][iH];
          for(int ipt=0; ipt<nPtBin; ipt++){
            meanQxTrkPt[ibin][iH][ipt] = meanQxTrkPtA[ibin][iH][ipt];
            meanQyTrkPt[ibin][iH][ipt] = meanQyTrkPtA[ibin][iH][ipt];
          }
        }
        if(runID>=262800 && runID<=263230){ 
          meanQxPlus[ibin][iH] = meanQxPlusB[ibin][iH];
          meanQyPlus[ibin][iH] = meanQyPlusB[ibin][iH];
          meanQxMinus[ibin][iH] = meanQxMinusB[ibin][iH];
          meanQyMinus[ibin][iH] = meanQyMinusB[ibin][iH];
          for(int ipt=0; ipt<nPtBin; ipt++){
            meanQxTrkPt[ibin][iH][ipt] = meanQxTrkPtB[ibin][iH][ipt];
            meanQyTrkPt[ibin][iH][ipt] = meanQyTrkPtB[ibin][iH][ipt];
          }
        }
        if(runID>=263231 && runID<=263359){ 
          meanQxPlus[ibin][iH] = meanQxPlusC[ibin][iH];
          meanQyPlus[ibin][iH] = meanQyPlusC[ibin][iH];
          meanQxMinus[ibin][iH] = meanQxMinusC[ibin][iH];
          meanQyMinus[ibin][iH] = meanQyMinusC[ibin][iH];
          for(int ipt=0; ipt<nPtBin; ipt++){
            meanQxTrkPt[ibin][iH][ipt] = meanQxTrkPtC[ibin][iH][ipt];
            meanQyTrkPt[ibin][iH][ipt] = meanQyTrkPtC[ibin][iH][ipt];
          }
        }
        if(runID>=263360 && runID<=263379){ 
          meanQxPlus[ibin][iH] = meanQxPlusD[ibin][iH];
          meanQyPlus[ibin][iH] = meanQyPlusD[ibin][iH];
          meanQxMinus[ibin][iH] = meanQxMinusD[ibin][iH];
          meanQyMinus[ibin][iH] = meanQyMinusD[ibin][iH];
          for(int ipt=0; ipt<nPtBin; ipt++){
            meanQxTrkPt[ibin][iH][ipt] = meanQxTrkPtD[ibin][iH][ipt];
            meanQyTrkPt[ibin][iH][ipt] = meanQyTrkPtD[ibin][iH][ipt];
          }
        }
        if(runID>=263380 && runID<=263614){ 
          meanQxPlus[ibin][iH] = meanQxPlusE[ibin][iH];
          meanQyPlus[ibin][iH] = meanQyPlusE[ibin][iH];
          meanQxMinus[ibin][iH] = meanQxMinusE[ibin][iH];
          meanQyMinus[ibin][iH] = meanQyMinusE[ibin][iH];
          for(int ipt=0; ipt<nPtBin; ipt++){
            meanQxTrkPt[ibin][iH][ipt] = meanQxTrkPtE[ibin][iH][ipt];
            meanQyTrkPt[ibin][iH][ipt] = meanQyTrkPtE[ibin][iH][ipt];
          }
        }
      }
    }

// re-centering using only one set of parameters, begin
// /*
    for(int ibin=0; ibin<nCentBin; ibin++){
      for(int iH=0; iH<nHarmonics; iH++){
          meanQxPlus[ibin][iH] = meanQxPlusA[ibin][iH];
          meanQyPlus[ibin][iH] = meanQyPlusA[ibin][iH];
          meanQxMinus[ibin][iH] = meanQxMinusA[ibin][iH];
          meanQyMinus[ibin][iH] = meanQyMinusA[ibin][iH];
          for(int ipt=0; ipt<nPtBin; ipt++){
            meanQxTrkPt[ibin][iH][ipt] = meanQxTrkPtA[ibin][iH][ipt];
            meanQyTrkPt[ibin][iH][ipt] = meanQyTrkPtA[ibin][iH][ipt];
          }
      }
    }
// */
// re-centering using only one set of parameters, end

//cout<<"runID = "<<runID<<",   meanQxTrkPt = "<<meanQxTrkPt[0][0][0]<<endl;

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

    Handle<VertexCollection> vertexCollection;
    iEvent.getByToken(VertexTag_, vertexCollection);
    VertexCollection recoVertices = *vertexCollection;
    if ( recoVertices.size() > 100 ) return;
    sort(recoVertices.begin(), recoVertices.end(), [](const reco::Vertex &a, const reco::Vertex &b){
      if ( a.tracksSize() == b.tracksSize() ) return a.chi2() < b.chi2();
      return a.tracksSize() > b.tracksSize();
    });
    int primaryvtx = 0;
    double vx = recoVertices[primaryvtx].x();
    double vy = recoVertices[primaryvtx].y();
    double vz = recoVertices[primaryvtx].z();
    double vxError = recoVertices[primaryvtx].xError();
    double vyError = recoVertices[primaryvtx].yError();
    double vzError = recoVertices[primaryvtx].zError();
    if(fabs(vz)<vertexZMin_ || fabs(vz)>vertexZMax_) return;
    hvz->Fill(vz);
    hvx->Fill(vx);
    hvy->Fill(vy);
    math::XYZPoint v1(vx,vy,vz);   

     int nTracks = 0;
     pVect_trkEtaPlus = new vector<TVector3>;
     pVect_trkEtaMinus = new vector<TVector3>;
     edm::Handle<TrackCollection> tracks;
     iEvent.getByToken(TrackTag_,tracks);
    for(TrackCollection::const_iterator itTrack = tracks->begin(); itTrack != tracks->end(); ++itTrack) {
      if ( itTrack->charge() == 0 ) continue;
      if ( !itTrack->quality(reco::TrackBase::highPurity) ) continue;
      if ( fabs(itTrack->eta()) > trackEtaCut_ ) continue;
      if ( itTrack->pt() < trackPtMinCut_ ) continue;
      if ( itTrack->pt() > trackPtMaxCut_ ) continue;

      bool bPix = false;
      int nHits = itTrack->numberOfValidHits();
      if ( itTrack->pt() < 2.4 and (nHits==3 or nHits==4 or nHits==5 or nHits==6) ) bPix = true;
      if ( bPix ) {
        if ( itTrack->normalizedChi2() / itTrack->hitPattern().trackerLayersWithMeasurement() > chi2nPixelMax_ ) continue;
        double dzp=itTrack->dz(v1);
        double dzperror=sqrt(itTrack->dzError()*itTrack->dzError()+vzError*vzError);
        if ( fabs( dzp/dzperror ) > dzRelPixelCut_ ) continue;        
      }
      if ( not bPix ) {
        if ( nHits < nhitsMin_ ) continue;
        if ( itTrack->normalizedChi2() / itTrack->hitPattern().trackerLayersWithMeasurement() > chi2nMax_ ) continue;
        if ( itTrack->ptError()/itTrack->pt() > ptErrCut_ ) continue;
        if (
             itTrack->pt() > 2.4 and
             itTrack->originalAlgo() != 4 and
             itTrack->originalAlgo() != 5 and
             itTrack->originalAlgo() != 6 and
             itTrack->originalAlgo() != 7
           ) continue;
        double d0 = -1.* itTrack->dxy(v1);
        double derror=sqrt(itTrack->dxyError()*itTrack->dxyError()+vxError*vyError);
        if ( fabs( d0/derror ) > dxyRelCut_ ) continue;
        double dz=itTrack->dz(v1);
        double dzerror=sqrt(itTrack->dzError()*itTrack->dzError()+vzError*vzError);
        if ( fabs( dz/dzerror ) > dzRelCut_ ) continue;
      }
      hpt->Fill(itTrack->pt());
      heta->Fill(itTrack->eta());
      hphi->Fill(itTrack->phi());
      nTracks++;
      TVector3 pvectorTrack;
      pvectorTrack.SetPtEtaPhi(itTrack->pt(),itTrack->eta(),itTrack->phi());
      if(itTrack->eta()>=trackEtaMinCut_) pVect_trkEtaPlus->push_back(pvectorTrack);
      if(itTrack->eta()<-1*trackEtaMinCut_) pVect_trkEtaMinus->push_back(pvectorTrack);
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
         if(sumwPlus>0) QhfPlus[ibin][iH]=QhfPlus[ibin][iH]/sumwPlus - TComplex(meanQxPlus[ibin][iH], meanQyPlus[ibin][iH]); //re-centering
         //if(sumwPlus>0) QhfPlus[ibin][iH]=QhfPlus[ibin][iH]/sumwPlus;
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
         if(sumwMinus>0) QhfMinus[ibin][iH]=QhfMinus[ibin][iH]/sumwMinus - TComplex(meanQxMinus[ibin][iH], meanQyMinus[ibin][iH]); //re-centering;
         //if(sumwMinus>0) QhfMinus[ibin][iH]=QhfMinus[ibin][iH]/sumwMinus;
         else QhfMinus[ibin][iH]=0;

         hnPsi2_cent3035_hfp->Fill(TMath::ATan(QhfPlus[6][1].Im()/QhfPlus[6][1].Re()));
         hnPsi3_cent3035_hfp->Fill(TMath::ATan(QhfPlus[6][2].Im()/QhfPlus[6][2].Re()));
         hnPsi4_cent3035_hfp->Fill(TMath::ATan(QhfPlus[6][3].Im()/QhfPlus[6][3].Re()));
         hnPsi5_cent3035_hfp->Fill(TMath::ATan(QhfPlus[6][4].Im()/QhfPlus[6][4].Re()));
         hnPsi6_cent3035_hfp->Fill(TMath::ATan(QhfPlus[6][5].Im()/QhfPlus[6][5].Re()));
         hnPsi7_cent3035_hfp->Fill(TMath::ATan(QhfPlus[6][6].Im()/QhfPlus[6][6].Re()));
         hnPsi2_cent3035_hfm->Fill(TMath::ATan(QhfMinus[6][1].Im()/QhfMinus[6][1].Re()));
         hnPsi3_cent3035_hfm->Fill(TMath::ATan(QhfMinus[6][2].Im()/QhfMinus[6][2].Re()));
         hnPsi4_cent3035_hfm->Fill(TMath::ATan(QhfMinus[6][3].Im()/QhfMinus[6][3].Re()));
         hnPsi5_cent3035_hfm->Fill(TMath::ATan(QhfMinus[6][4].Im()/QhfMinus[6][4].Re()));
         hnPsi6_cent3035_hfm->Fill(TMath::ATan(QhfMinus[6][5].Im()/QhfMinus[6][5].Re()));
         hnPsi7_cent3035_hfm->Fill(TMath::ATan(QhfMinus[6][6].Im()/QhfMinus[6][6].Re()));

       }

       TComplex temp;
       double tempReal;
       for(int iH=0; iH<nHarmonics; iH++){
         hQhfPlusX[ibin][iH]->Fill(QhfPlus[ibin][iH].Re());
         hQhfPlusY[ibin][iH]->Fill(QhfPlus[ibin][iH].Im());
         hQhfMinusX[ibin][iH]->Fill(QhfMinus[ibin][iH].Re());
         hQhfMinusY[ibin][iH]->Fill(QhfMinus[ibin][iH].Im());

         double vnabsmevt;
         temp=QhfPlus[ibin][iH]*TComplex::Conjugate(QhfMinus[ibin][iH]);
         if(useReDenominator) vnabsmevt=temp.Re();  // or use Abs(temp) ???
         else vnabsmevt=TComplex::Abs(temp);  // or use Abs(temp) ???
         hVnAbs2[ibin][iH]->Fill(vnabsmevt);
         temp=QhfPlus[ibin][iH]*TComplex::Conjugate(QhfMinus[ibin][iH]) * QhfPlus[ibin][iH]*TComplex::Conjugate(QhfMinus[ibin][iH]);
         if(useReDenominator) vnabsmevt=temp.Re();
         else vnabsmevt=TComplex::Abs(temp);
         hVnAbs4[ibin][iH]->Fill(vnabsmevt);
         temp=QhfPlus[ibin][iH]*TComplex::Conjugate(QhfMinus[ibin][iH]) * QhfPlus[ibin][iH]*TComplex::Conjugate(QhfMinus[ibin][iH]) * QhfPlus[ibin][iH]*TComplex::Conjugate(QhfMinus[ibin][iH]);
         if(useReDenominator) vnabsmevt=temp.Re();
         else vnabsmevt=TComplex::Abs(temp);
         hVnAbs6[ibin][iH]->Fill(vnabsmevt);
         temp=QhfPlus[ibin][iH]*TComplex::Conjugate(QhfMinus[ibin][iH]) * QhfPlus[ibin][iH]*TComplex::Conjugate(QhfMinus[ibin][iH]) * QhfPlus[ibin][iH]*TComplex::Conjugate(QhfMinus[ibin][iH]) * QhfPlus[ibin][iH]*TComplex::Conjugate(QhfMinus[ibin][iH]);
         if(useReDenominator) vnabsmevt=temp.Re();
         else vnabsmevt=TComplex::Abs(temp);
         hVnAbs8[ibin][iH]->Fill(vnabsmevt);
       }

       if(useReDenominator) tempReal=(QhfPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1]) * QhfPlus[ibin][2]*TComplex::Conjugate(QhfMinus[ibin][2])).Re();
       else tempReal=TComplex::Abs(QhfPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1])) * TComplex::Abs(QhfPlus[ibin][2]*TComplex::Conjugate(QhfMinus[ibin][2]));
       hV2Abs2V3Abs2[ibin]->Fill(tempReal);
       if(useReDenominator) tempReal=(QhfPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1]) * QhfPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1]) * QhfPlus[ibin][2]*TComplex::Conjugate(QhfMinus[ibin][2])).Re();
       else tempReal=TComplex::Abs(QhfPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1])) * TComplex::Abs(QhfPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1])) * TComplex::Abs(QhfPlus[ibin][2]*TComplex::Conjugate(QhfMinus[ibin][2]));
       hV2Abs4V3Abs2[ibin]->Fill(tempReal);
       if(useReDenominator) tempReal=(QhfPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1]) * QhfPlus[ibin][2]*TComplex::Conjugate(QhfMinus[ibin][2]) * QhfPlus[ibin][2]*TComplex::Conjugate(QhfMinus[ibin][2])).Re();
       else tempReal=TComplex::Abs(QhfPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1])) * TComplex::Abs(QhfPlus[ibin][2]*TComplex::Conjugate(QhfMinus[ibin][2])) * TComplex::Abs(QhfPlus[ibin][2]*TComplex::Conjugate(QhfMinus[ibin][2]));
       hV2Abs2V3Abs4[ibin]->Fill(tempReal);

//Numerators
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

         hMeanPt[ibin][cpt]->Fill(pt_trkMinus);
       }

       for(int iH=0; iH<nHarmonics; iH++){
         for(int ipt=0; ipt<nPtBin; ipt++){
           if(sumwtrkPt[ipt]>0) QtrkPt[ibin][iH][ipt]=QtrkPt[ibin][iH][ipt]/sumwtrkPt[ipt] - TComplex(meanQxTrkPt[ibin][iH][ipt], meanQyTrkPt[ibin][iH][ipt]); // re-centering
           //if(sumwtrkPt[ipt]>0) QtrkPt[ibin][iH][ipt]=QtrkPt[ibin][iH][ipt]/sumwtrkPt[ipt];
           else QtrkPt[ibin][iH][ipt]=0;
         }
       }

       for(int iH=0; iH<nHarmonics; iH++){
         for(int iPt=0; iPt<nPtBin; iPt++){
           hQtrkPtX[ibin][iH][iPt]->Fill(QtrkPt[ibin][iH][iPt].Re());
           hQtrkPtY[ibin][iH][iPt]->Fill(QtrkPt[ibin][iH][iPt].Im());
         }
       }
       hnPsi2_cent05_trk0304->Fill(TMath::ATan(QtrkPt[0][1][0].Im()/QtrkPt[0][1][0].Re()));
       hnPsi3_cent05_trk0304->Fill(TMath::ATan(QtrkPt[0][2][0].Im()/QtrkPt[0][2][0].Re()));
       hnPsi4_cent05_trk0304->Fill(TMath::ATan(QtrkPt[0][3][0].Im()/QtrkPt[0][3][0].Re()));
       hnPsi5_cent05_trk0304->Fill(TMath::ATan(QtrkPt[0][4][0].Im()/QtrkPt[0][4][0].Re()));
       hnPsi6_cent05_trk0304->Fill(TMath::ATan(QtrkPt[0][5][0].Im()/QtrkPt[0][5][0].Re()));
       hnPsi7_cent05_trk0304->Fill(TMath::ATan(QtrkPt[0][6][0].Im()/QtrkPt[0][6][0].Re()));
       hnPsi2_cent4050_trk2025->Fill(TMath::ATan(QtrkPt[8][1][8].Im()/QtrkPt[8][1][8].Re()));
       hnPsi3_cent4050_trk2025->Fill(TMath::ATan(QtrkPt[8][2][8].Im()/QtrkPt[8][2][8].Re()));
       hnPsi4_cent4050_trk2025->Fill(TMath::ATan(QtrkPt[8][3][8].Im()/QtrkPt[8][3][8].Re()));
       hnPsi5_cent4050_trk2025->Fill(TMath::ATan(QtrkPt[8][4][8].Im()/QtrkPt[8][4][8].Re()));
       hnPsi6_cent4050_trk2025->Fill(TMath::ATan(QtrkPt[8][5][8].Im()/QtrkPt[8][5][8].Re()));
       hnPsi7_cent4050_trk2025->Fill(TMath::ATan(QtrkPt[8][6][8].Im()/QtrkPt[8][6][8].Re()));

       for(int ipt=0; ipt<nPtBin; ipt++){
        if(sumwtrkPt[ipt]>0){

         hq2Q2PstarAB[ibin][ipt]->Fill((QtrkPt[ibin][1][ipt]*TComplex::Conjugate(QhfPlus[ibin][1])).Re()); 
         hq3Q3PstarAB[ibin][ipt]->Fill((QtrkPt[ibin][2][ipt]*TComplex::Conjugate(QhfPlus[ibin][2])).Re()); 
         hq4Q4PstarAB[ibin][ipt]->Fill((QtrkPt[ibin][3][ipt]*TComplex::Conjugate(QhfPlus[ibin][3])).Re()); 
         hq5Q5PstarAB[ibin][ipt]->Fill((QtrkPt[ibin][4][ipt]*TComplex::Conjugate(QhfPlus[ibin][4])).Re()); 
         hq6Q6PstarAB[ibin][ipt]->Fill((QtrkPt[ibin][5][ipt]*TComplex::Conjugate(QhfPlus[ibin][5])).Re()); 
         hq7Q7PstarAB[ibin][ipt]->Fill((QtrkPt[ibin][6][ipt]*TComplex::Conjugate(QhfPlus[ibin][6])).Re()); 
         hq8Q8PstarAB[ibin][ipt]->Fill((QtrkPt[ibin][7][ipt]*TComplex::Conjugate(QhfPlus[ibin][7])).Re()); 
         hq2Q2MstarAB[ibin][ipt]->Fill((QtrkPt[ibin][1][ipt]*TComplex::Conjugate(QhfMinus[ibin][1])).Re()); 
         hq3Q3MstarAB[ibin][ipt]->Fill((QtrkPt[ibin][2][ipt]*TComplex::Conjugate(QhfMinus[ibin][2])).Re()); 
         hq4Q4MstarAB[ibin][ipt]->Fill((QtrkPt[ibin][3][ipt]*TComplex::Conjugate(QhfMinus[ibin][3])).Re()); 
         hq5Q5MstarAB[ibin][ipt]->Fill((QtrkPt[ibin][4][ipt]*TComplex::Conjugate(QhfMinus[ibin][4])).Re()); 
         hq6Q6MstarAB[ibin][ipt]->Fill((QtrkPt[ibin][5][ipt]*TComplex::Conjugate(QhfMinus[ibin][5])).Re()); 
         hq7Q7MstarAB[ibin][ipt]->Fill((QtrkPt[ibin][6][ipt]*TComplex::Conjugate(QhfMinus[ibin][6])).Re()); 
         hq8Q8MstarAB[ibin][ipt]->Fill((QtrkPt[ibin][7][ipt]*TComplex::Conjugate(QhfMinus[ibin][7])).Re()); 

         hq4Q2starQ2starAB[ibin][ipt]->Fill((QtrkPt[ibin][3][ipt]*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfPlus[ibin][1])).Re());
         hq6Q2starQ2starQ2starAB[ibin][ipt]->Fill((QtrkPt[ibin][5][ipt]*TComplex::Conjugate(QhfPlus[ibin][1])*TComplex::Conjugate(QhfPlus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][1])).Re());
         hq6Q3starQ3starAB[ibin][ipt]->Fill((QtrkPt[ibin][5][ipt]*TComplex::Conjugate(QhfMinus[ibin][2])*TComplex::Conjugate(QhfPlus[ibin][2])).Re());
         hq5Q2starQ3starAB[ibin][ipt]->Fill((QtrkPt[ibin][4][ipt]*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfPlus[ibin][2])).Re());
         hq7Q2starQ2starQ3starAB[ibin][ipt]->Fill((QtrkPt[ibin][6][ipt]*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfPlus[ibin][2])).Re());
         hQ2Abs4AB[ibin][ipt]->Fill((QtrkPt[ibin][1][ipt]*QtrkPt[ibin][1][ipt]*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfPlus[ibin][1])).Re());
         hQ2Abs6AB[ibin][ipt]->Fill((QtrkPt[ibin][1][ipt]*QtrkPt[ibin][1][ipt]*QtrkPt[ibin][1][ipt]*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfPlus[ibin][1])).Re());
         hQ3Abs4AB[ibin][ipt]->Fill((QtrkPt[ibin][2][ipt]*QtrkPt[ibin][2][ipt]*TComplex::Conjugate(QhfMinus[ibin][2])*TComplex::Conjugate(QhfPlus[ibin][2])).Re());
         hQ2Abs2Q3Abs2AB[ibin][ipt]->Fill((QtrkPt[ibin][1][ipt]*QtrkPt[ibin][2][ipt]*TComplex::Conjugate(QhfPlus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][2])).Re());
         hQ2Abs4Q3Abs2AB[ibin][ipt]->Fill((QtrkPt[ibin][1][ipt]*QtrkPt[ibin][1][ipt]*QtrkPt[ibin][2][ipt]*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfPlus[ibin][2])).Re());

        }
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
  hpt = fs->make<TH1D>("pt","pt",nPtBin,ptBin);
  heta = fs->make<TH1D>("eta","eta",300,-3,3);
  hphi = fs->make<TH1D>("phi","phi",200,-4,4);
  hHFcal = fs->make<TH1D>("hfCal","HF ET",8000,0,8000);

  hMultTrkEtaPlus = fs->make<TH1D>("multtrketaplus","N",300,0,3000);
  hMultTrkEtaMinus = fs->make<TH1D>("multtrketaminus","N",300,0,3000);
  hMultHFEtaPlus = fs->make<TH1D>("multhfetaplus","N",400,0,4000);
  hMultHFEtaMinus = fs->make<TH1D>("multhfetaminus","N",400,0,4000);
  for(int ibin=0; ibin<nCentBin; ibin++){
    for(int iH=0; iH<nHarmonics; iH++){
      hQhfPlusX[ibin][iH] = fs->make<TH1D>(Form("hQhfPlusX_ibin%d_iH%d",ibin,iH),"",100,-1000,1000);
      hQhfPlusY[ibin][iH] = fs->make<TH1D>(Form("hQhfPlusY_ibin%d_iH%d",ibin,iH),"",100,-1000,1000);
      hQhfMinusX[ibin][iH] = fs->make<TH1D>(Form("hQhfMinusX_ibin%d_iH%d",ibin,iH),"",100,-1000,1000);
      hQhfMinusY[ibin][iH] = fs->make<TH1D>(Form("hQhfMinusY_ibin%d_iH%d",ibin,iH),"",100,-1000,1000);
      for(int iPt=0; iPt<nPtBin; iPt++){
        hQtrkPtX[ibin][iH][iPt] = fs->make<TH1D>(Form("hQtrkPtX_ibin%d_iH%d_iPt%d",ibin,iH,iPt),"",100,-1000,1000);
        hQtrkPtY[ibin][iH][iPt] = fs->make<TH1D>(Form("hQtrkPtY_ibin%d_iH%d_iPt%d",ibin,iH,iPt),"",100,-1000,1000);
      }
      hVnAbs2[ibin][iH] = fs->make<TH1D>(Form("hVnAbs2_ibin%d_iH%d",ibin,iH),"",100,-1000,1000);
      hVnAbs4[ibin][iH] = fs->make<TH1D>(Form("hVnAbs4_ibin%d_iH%d",ibin,iH),"",100,-1000,1000);
      hVnAbs6[ibin][iH] = fs->make<TH1D>(Form("hVnAbs6_ibin%d_iH%d",ibin,iH),"",100,-1000,1000);
      hVnAbs8[ibin][iH] = fs->make<TH1D>(Form("hVnAbs8_ibin%d_iH%d",ibin,iH),"",100,-1000,1000);
    }
    hV2Abs2V3Abs2[ibin] = fs->make<TH1D>(Form("hV2Abs2V3Abs2_ibin%d",ibin),"",100,-1000,1000);
    hV2Abs4V3Abs2[ibin] = fs->make<TH1D>(Form("hV2Abs4V3Abs2_ibin%d",ibin),"",100,-1000,1000);
    hV2Abs2V3Abs4[ibin] = fs->make<TH1D>(Form("hV2Abs2V3Abs4_ibin%d",ibin),"",100,-1000,1000);

    for(int ipt=0; ipt<nPtBin; ipt++){

      hq2Q2PstarAB[ibin][ipt] = fs->make<TH1D>(Form("hq2Q2PstarAB_ibin%d_ipt%d",ibin,ipt),"",100,-1000,1000); 
      hq3Q3PstarAB[ibin][ipt] = fs->make<TH1D>(Form("hq3Q3PstarAB_ibin%d_ipt%d",ibin,ipt),"",100,-1000,1000); 
      hq4Q4PstarAB[ibin][ipt] = fs->make<TH1D>(Form("hq4Q4PstarAB_ibin%d_ipt%d",ibin,ipt),"",100,-1000,1000); 
      hq5Q5PstarAB[ibin][ipt] = fs->make<TH1D>(Form("hq5Q5PstarAB_ibin%d_ipt%d",ibin,ipt),"",100,-1000,1000); 
      hq6Q6PstarAB[ibin][ipt] = fs->make<TH1D>(Form("hq6Q6PstarAB_ibin%d_ipt%d",ibin,ipt),"",100,-1000,1000); 
      hq7Q7PstarAB[ibin][ipt] = fs->make<TH1D>(Form("hq7Q7PstarAB_ibin%d_ipt%d",ibin,ipt),"",100,-1000,1000); 
      hq8Q8PstarAB[ibin][ipt] = fs->make<TH1D>(Form("hq8Q8PstarAB_ibin%d_ipt%d",ibin,ipt),"",100,-1000,1000); 
      hq2Q2MstarAB[ibin][ipt] = fs->make<TH1D>(Form("hq2Q2MstarAB_ibin%d_ipt%d",ibin,ipt),"",100,-1000,1000); 
      hq3Q3MstarAB[ibin][ipt] = fs->make<TH1D>(Form("hq3Q3MstarAB_ibin%d_ipt%d",ibin,ipt),"",100,-1000,1000); 
      hq4Q4MstarAB[ibin][ipt] = fs->make<TH1D>(Form("hq4Q4MstarAB_ibin%d_ipt%d",ibin,ipt),"",100,-1000,1000); 
      hq5Q5MstarAB[ibin][ipt] = fs->make<TH1D>(Form("hq5Q5MstarAB_ibin%d_ipt%d",ibin,ipt),"",100,-1000,1000); 
      hq6Q6MstarAB[ibin][ipt] = fs->make<TH1D>(Form("hq6Q6MstarAB_ibin%d_ipt%d",ibin,ipt),"",100,-1000,1000); 
      hq7Q7MstarAB[ibin][ipt] = fs->make<TH1D>(Form("hq7Q7MstarAB_ibin%d_ipt%d",ibin,ipt),"",100,-1000,1000); 
      hq8Q8MstarAB[ibin][ipt] = fs->make<TH1D>(Form("hq8Q8MstarAB_ibin%d_ipt%d",ibin,ipt),"",100,-1000,1000); 

      hq4Q2starQ2starAB[ibin][ipt] = fs->make<TH1D>(Form("hq4Q2starQ2starAB_ibin%d_ipt%d",ibin,ipt),"",100,-1000,1000);
      hq6Q2starQ2starQ2starAB[ibin][ipt] = fs->make<TH1D>(Form("hq6Q2starQ2starQ2starAB_ibin%d_ipt%d",ibin,ipt),"",100,-1000,1000);
      hq6Q3starQ3starAB[ibin][ipt] = fs->make<TH1D>(Form("hq6Q3starQ3starAB_ibin%d_ipt%d",ibin,ipt),"",100,-1000,1000);
      hq5Q2starQ3starAB[ibin][ipt] = fs->make<TH1D>(Form("hq5Q2starQ3starAB_ibin%d_ipt%d",ibin,ipt),"",100,-1000,1000);
      hq7Q2starQ2starQ3starAB[ibin][ipt] = fs->make<TH1D>(Form("hq7Q2starQ2starQ3starAB_ibin%d_ipt%d",ibin,ipt),"",100,-1000,1000);
      hQ2Abs4AB[ibin][ipt] = fs->make<TH1D>(Form("hQ2Abs4AB_ibin%d_ipt%d",ibin,ipt),"",100,-1000,1000);
      hQ2Abs6AB[ibin][ipt] = fs->make<TH1D>(Form("hQ2Abs6AB_ibin%d_ipt%d",ibin,ipt),"",100,-1000,1000);
      hQ3Abs4AB[ibin][ipt] = fs->make<TH1D>(Form("hQ3Abs4AB_ibin%d_ipt%d",ibin,ipt),"",100,-1000,1000);
      hQ2Abs2Q3Abs2AB[ibin][ipt] = fs->make<TH1D>(Form("hQ2Abs2Q3Abs2AB_ibin%d_ipt%d",ibin,ipt),"",100,-1000,1000);
      hQ2Abs4Q3Abs2AB[ibin][ipt] = fs->make<TH1D>(Form("hQ2Abs4Q3Abs2AB_ibin%d_ipt%d",ibin,ipt),"",100,-1000,1000);


      hMeanPt[ibin][ipt] = fs->make<TH1D>(Form("hMeanPt_ibin%d_ipt%d",ibin,ipt),"",100,0,20);
    }
  }

  hnPsi2_cent05_trk0304 = fs->make<TH1D>(Form("hnPsi2_cent05_trk0304"),"",100,-2,2);
  hnPsi3_cent05_trk0304 = fs->make<TH1D>(Form("hnPsi3_cent05_trk0304"),"",100,-2,2);
  hnPsi4_cent05_trk0304 = fs->make<TH1D>(Form("hnPsi4_cent05_trk0304"),"",100,-2,2);
  hnPsi5_cent05_trk0304 = fs->make<TH1D>(Form("hnPsi5_cent05_trk0304"),"",100,-2,2);
  hnPsi6_cent05_trk0304 = fs->make<TH1D>(Form("hnPsi6_cent05_trk0304"),"",100,-2,2);
  hnPsi7_cent05_trk0304 = fs->make<TH1D>(Form("hnPsi7_cent05_trk0304"),"",100,-2,2);
  hnPsi2_cent4050_trk2025 = fs->make<TH1D>(Form("hnPsi2_cent4050_trk2025"),"",100,-2,2);
  hnPsi3_cent4050_trk2025 = fs->make<TH1D>(Form("hnPsi3_cent4050_trk2025"),"",100,-2,2);
  hnPsi4_cent4050_trk2025 = fs->make<TH1D>(Form("hnPsi4_cent4050_trk2025"),"",100,-2,2);
  hnPsi5_cent4050_trk2025 = fs->make<TH1D>(Form("hnPsi5_cent4050_trk2025"),"",100,-2,2);
  hnPsi6_cent4050_trk2025 = fs->make<TH1D>(Form("hnPsi6_cent4050_trk2025"),"",100,-2,2);
  hnPsi7_cent4050_trk2025 = fs->make<TH1D>(Form("hnPsi7_cent4050_trk2025"),"",100,-2,2);
  hnPsi2_cent3035_hfp = fs->make<TH1D>(Form("hnPsi2_cent3035_hfp"),"",100,-2,2);
  hnPsi3_cent3035_hfp = fs->make<TH1D>(Form("hnPsi3_cent3035_hfp"),"",100,-2,2);
  hnPsi4_cent3035_hfp = fs->make<TH1D>(Form("hnPsi4_cent3035_hfp"),"",100,-2,2);
  hnPsi5_cent3035_hfp = fs->make<TH1D>(Form("hnPsi5_cent3035_hfp"),"",100,-2,2);
  hnPsi6_cent3035_hfp = fs->make<TH1D>(Form("hnPsi6_cent3035_hfp"),"",100,-2,2);
  hnPsi7_cent3035_hfp = fs->make<TH1D>(Form("hnPsi7_cent3035_hfp"),"",100,-2,2);
  hnPsi2_cent3035_hfm = fs->make<TH1D>(Form("hnPsi2_cent3035_hfm"),"",100,-2,2);
  hnPsi3_cent3035_hfm = fs->make<TH1D>(Form("hnPsi3_cent3035_hfm"),"",100,-2,2);
  hnPsi4_cent3035_hfm = fs->make<TH1D>(Form("hnPsi4_cent3035_hfm"),"",100,-2,2);
  hnPsi5_cent3035_hfm = fs->make<TH1D>(Form("hnPsi5_cent3035_hfm"),"",100,-2,2);
  hnPsi6_cent3035_hfm = fs->make<TH1D>(Form("hnPsi6_cent3035_hfm"),"",100,-2,2);
  hnPsi7_cent3035_hfm = fs->make<TH1D>(Form("hnPsi7_cent3035_hfm"),"",100,-2,2);

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
