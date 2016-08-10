// -*- C++ -*-
//
// Package:    FlowCorr
// Class:      FlowCorr
// 
/**\class FlowCorr FlowCorr.cc Analysis/FlowCorr/src/FlowCorr.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Shengquan Tuo,,,
//         Created:  Thu Aug  4 22:00:31 CEST 2016
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include <TH1D.h>
#include <TH2D.h>
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/HeavyIonEvent/interface/Centrality.h"
#include "DataFormats/HeavyIonEvent/interface/EvtPlane.h"
#include "RecoHI/HiCentralityAlgos/interface/CentralityProvider.h"
#include "DataFormats/CaloTowers/interface/CaloTowerCollection.h"

#include "Analysis/FlowCorr/src/FlowCorr.h"

//
// class declaration
//

class FlowCorr : public edm::EDAnalyzer {
   public:
      explicit FlowCorr(const edm::ParameterSet&);
      ~FlowCorr();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      virtual void beginRun(edm::Run const&, edm::EventSetup const&);
      virtual void endRun(edm::Run const&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

      // ----------member data ---------------------------
  edm::InputTag CentralityTag_;
  edm::InputTag CentralityBinTag_;
  edm::InputTag EvtPlaneTag_;
  edm::InputTag EvtPlaneFlatTag_;

  edm::InputTag HiMCTag_;
  edm::InputTag VertexTag_;
  edm::InputTag TrackTag_;
  reco::TrackBase::TrackQuality TrackQualityTag_;
  edm::InputTag TowerTag_;

  double trackPtMinCut_;
  double trackPtMaxCut_;
  double trackEtaCut_;
  double trackEtaMinCut_;
  double ptErrCut_;
  double dzRelCut_;
  double dxyRelCut_;

  edm::Service<TFileService> fs;
  CentralityProvider * centProvider;

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
FlowCorr::FlowCorr(const edm::ParameterSet& iConfig) 
{
   //now do what ever initialization is needed
  EvtPlaneTag_ = iConfig.getParameter<edm::InputTag> ("EvtPlane");
  EvtPlaneFlatTag_ = iConfig.getParameter<edm::InputTag> ("EvtPlaneFlat");
  HiMCTag_ = iConfig.getParameter<edm::InputTag> ("HiMC");
  VertexTag_ = iConfig.getParameter<edm::InputTag> ("Vertex");
  TrackTag_ = iConfig.getParameter<edm::InputTag>("Track");
  TrackQualityTag_ = TrackBase::qualityByName(iConfig.getParameter<std::string>("TrackQuality"));
  TowerTag_ = iConfig.getParameter<edm::InputTag>("Tower");
  trackPtMinCut_ = iConfig.getParameter<double>("trackPtMinCut");
  trackPtMaxCut_ = iConfig.getParameter<double>("trackPtMaxCut");
  trackEtaCut_ = iConfig.getParameter<double>("trackEtaCut");
  trackEtaMinCut_ = iConfig.getParameter<double>("trackEtaMinCut");
  ptErrCut_ = iConfig.getParameter<double>("ptErrCut");
  dzRelCut_ = iConfig.getParameter<double>("dzRelCut");
  dxyRelCut_ = iConfig.getParameter<double>("dxyRelCut");


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

    centProvider = 0;
    if (!centProvider) centProvider = new CentralityProvider(iSetup);
    centProvider->newEvent(iEvent,iSetup);
    const reco::Centrality* centrality = centProvider->raw();
    int hiBin = centProvider->getBin();
    hCent->Fill(hiBin);
    hHF->Fill(centrality->EtHFtowerSum());
       int ibin=-1;
       for(int j=0;j<nCentBin;j++)
       if(hiBin>=2*cBin[j]&&hiBin<2*cBin[j+1])
         ibin=j;
       if(ibin<0 || ibin==nCentBin) return;

    edm::Handle<reco::EvtPlaneCollection> evtPlanes;
    iEvent.getByLabel(EvtPlaneTag_,evtPlanes);
    if(evtPlanes.isValid()){
      //6=HFm2, 7=HFp2, 8=HF2, 9=trackmid2
      //13=HFm3, 14=HFp3, 15=HF3, 16=trackmid3
      double anglem2 = (*evtPlanes)[6].angle();
      hAngle->Fill(anglem2);        
    }
    edm::Handle<reco::EvtPlaneCollection> evtPlanesFlat;
    iEvent.getByLabel(EvtPlaneFlatTag_,evtPlanesFlat);
    if(evtPlanesFlat.isValid()){
      double anglem2Flat = (*evtPlanesFlat)[6].angle();
      hAngleFlat->Fill(anglem2Flat);
    }

    edm::Handle<std::vector<reco::Vertex>> vertex;
    iEvent.getByLabel(VertexTag_, vertex);
    double vx=vertex->begin()->x();
    double vy=vertex->begin()->y();
    double vz=vertex->begin()->z();
    double vxError=vertex->begin()->xError();
    double vyError=vertex->begin()->yError();
    double vzError=vertex->begin()->zError();
    hvz->Fill(vz);
    hvx->Fill(vx);
    hvy->Fill(vy);

     int nTracks = 0;
     pVect_trkEtaPlus = new vector<TVector3>;
     pVect_trkEtaMinus = new vector<TVector3>;
     edm::Handle<reco::TrackCollection> tracks;
     iEvent.getByLabel(TrackTag_,tracks);
     for(unsigned int i = 0 ; i < tracks->size(); ++i){
       const Track& track = (*tracks)[i];
       if(!track.quality(TrackQualityTag_)) continue;
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

       if(track.pt()>trackPtMinCut_ && track.pt()<trackPtMaxCut_ && 
       track.eta()<trackEtaCut_ && track.eta()>-1.0*trackEtaCut_ &&
       track.ptError()/track.pt() < ptErrCut_ &&
       dz*dz < dzRelCut_*dzRelCut_ * dzsigma2 &&
       dxy*dxy < dxyRelCut_*dxyRelCut_ * dxysigma2 ){
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
    iEvent.getByLabel(TowerTag_,towers);
    for( size_t i = 0; i<towers->size(); ++ i){
       const CaloTower & tower = (*towers)[ i ];
       double etahf = tower.eta();
       bool isHF = tower.ietaAbs() > 29;
       TVector3 pvectorHF;
       pvectorHF.SetPtEtaPhi(tower.pt(),tower.eta(),tower.phi());
          if(isHF && etahf > 0 && tower.pt()>0.005 && tower.pt()<30.0){
            etHFtowerSumPlus += tower.pt();
            pVect_hfEtaPlus->push_back(pvectorHF);
          }
          if(isHF && etahf < 0 && tower.pt()>0.005 && tower.pt()<30.0){
            etHFtowerSumMinus += tower.pt();
            pVect_hfEtaMinus->push_back(pvectorHF);
          }
    }
    etHFtowerSum = etHFtowerSumPlus + etHFtowerSumMinus;
    hHFcal->Fill(etHFtowerSum);


// START Flow Analysis
       for(int j=0;j<nCentBin;j++){
         for(int iH=0; iH<nHarmonics; iH++){
           QhfPlus[j][iH]=0;   
           QhfMinus[j][iH]=0;   
         }
       }
       nEvent[ibin]+=1;

       hMultTrkEtaPlus->Fill((int)pVect_trkEtaPlus->size());
       hMultTrkEtaMinus->Fill((int)pVect_trkEtaMinus->size());
       hMultHFEtaPlus->Fill((int)pVect_hfEtaPlus->size());  
       hMultHFEtaMinus->Fill((int)pVect_hfEtaMinus->size()); 

       for(int iH=0; iH<nHarmonics; iH++){
         double sumwPlus=0;
         double sumwMinus=0;
         // choose hf or trk here (two lines): pVect_hfEtaPlus vs pVect_trkEtaPlus;
         for(int iplus=0;iplus<(int)pVect_hfEtaPlus->size();iplus++){
           TVector3 pvector_hfPlus = (*pVect_hfEtaPlus)[iplus];
           //double pt_hfPlus = pvector_hfPlus.Pt();
           double phi_hfPlus = pvector_hfPlus.Phi();
           //sumwPlus+=pt_hfPlus; 
           sumwPlus+=1; 
           QhfPlus[ibin][iH]+=TComplex::Exp(TComplex(0,(iH+1)*phi_hfPlus));
         }
         if(sumwPlus>0) QhfPlus[ibin][iH]=QhfPlus[ibin][iH]/sumwPlus - TComplex(meanQxPlus[ibin][iH], meanQyPlus[ibin][iH]); //re-centering
         else QhfPlus[ibin][iH]=0;

         // choose hf or trk here (two lines): pVect_hfEtaMinus vs pVect_trkEtaMinus;
         for(int iminus=0;iminus<(int)pVect_hfEtaMinus->size();iminus++){
           TVector3 pvector_hfMinus = (*pVect_hfEtaMinus)[iminus];
           //double pt_hfMinus = pvector_hfMinus.Pt();
           double phi_hfMinus = pvector_hfMinus.Phi();
           //sumwMinus+=pt_hfMinus; 
           sumwMinus+=1;
           QhfMinus[ibin][iH]+=TComplex::Exp(TComplex(0,(iH+1)*phi_hfMinus));
         }
         if(sumwMinus>0) QhfMinus[ibin][iH]=QhfMinus[ibin][iH]/sumwMinus - TComplex(meanQxMinus[ibin][iH], meanQyMinus[ibin][iH]); //re-centering;
         else QhfMinus[ibin][iH]=0;

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
         temp=QhfPlus[ibin][iH]*TComplex::Conjugate(QhfMinus[ibin][iH]);
         double vnabs2evt;
         if(useRe) vnabs2evt=temp.Re();  // or use Abs(temp) ???
         else vnabs2evt=TComplex::Abs(temp);  // or use Abs(temp) ???
         //double vnabs2evt=(QhfPlus[ibin][iH]*TComplex::Conjugate(QhfMinus[ibin][iH])).Re();
         VnAbs2[ibin][iH]+=vnabs2evt;
         VnAbs4[ibin][iH]+=vnabs2evt*vnabs2evt;
         VnAbs6[ibin][iH]+=vnabs2evt*vnabs2evt*vnabs2evt;
         hVnAbs2[ibin][iH]->Fill(vnabs2evt);
         hVnAbs4[ibin][iH]->Fill(vnabs2evt*vnabs2evt);
         hVnAbs6[ibin][iH]->Fill(vnabs2evt*vnabs2evt*vnabs2evt);
       }

       temp=QhfPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1]) * QhfPlus[ibin][2]*TComplex::Conjugate(QhfMinus[ibin][2]);
       if(useRe) tempReal=temp.Re();
       else tempReal=TComplex::Abs(temp);
       V2Abs2V3Abs2[ibin]+=tempReal;
       hV2Abs2V3Abs2[ibin]->Fill(tempReal);
       //V2Abs2V3Abs2[ibin]+=(QhfPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1]) * QhfPlus[ibin][2]*TComplex::Conjugate(QhfMinus[ibin][2])).Re();
       temp=QhfPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1]) * QhfPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1]) * QhfPlus[ibin][2]*TComplex::Conjugate(QhfMinus[ibin][2]);
       if(useRe) tempReal=temp.Re();
       else tempReal=TComplex::Abs(temp);       
       V2Abs4V3Abs2[ibin]+=tempReal;
       hV2Abs4V3Abs2[ibin]->Fill(tempReal);

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

         temp = TComplex::Exp(TComplex(0,(2)*phi_trkPlus))*TComplex::Conjugate(QhfMinus[ibin][1]);
         if(useRe) tempReal=temp.Re();
         else tempReal=TComplex::Abs(temp);
         hv2V2star[ibin][cpt]->Fill(tempReal);
         temp = TComplex::Exp(TComplex(0,(4)*phi_trkPlus))*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][1]);
         if(useRe) tempReal=temp.Re();
         else tempReal=TComplex::Abs(temp);
         hv4V2starV2star[ibin][cpt]->Fill(tempReal);
         temp=TComplex::Exp(TComplex(0,(6)*phi_trkPlus))*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][1]);
         if(useRe) tempReal=temp.Re();
         else tempReal=TComplex::Abs(temp);
         hv6V2starV2starV2star[ibin][cpt]->Fill(tempReal);
         temp=TComplex::Exp(TComplex(0,(6)*phi_trkPlus))*TComplex::Conjugate(QhfMinus[ibin][2])*TComplex::Conjugate(QhfMinus[ibin][2]);
         if(useRe) tempReal=temp.Re();
         else tempReal=TComplex::Abs(temp);
         hv6V3starV3star[ibin][cpt]->Fill(tempReal);
         temp=TComplex::Exp(TComplex(0,(5)*phi_trkPlus))*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][2]);
         if(useRe) tempReal=temp.Re();
         else tempReal=TComplex::Abs(temp);
         hv5V2starV3star[ibin][cpt]->Fill(tempReal);
         temp=TComplex::Exp(TComplex(0,(7)*phi_trkPlus))*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][2]);
         if(useRe) tempReal=temp.Re();
         else tempReal=TComplex::Abs(temp);
         hv7V2starV2starV3star[ibin][cpt]->Fill(tempReal);
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

         temp = TComplex::Exp(TComplex(0,(2)*phi_trkMinus))*TComplex::Conjugate(QhfPlus[ibin][1]);
         if(useRe) tempReal=temp.Re();
         else tempReal=TComplex::Abs(temp);
         hv2V2star[ibin][cpt]->Fill(tempReal);
         temp = TComplex::Exp(TComplex(0,(4)*phi_trkMinus))*TComplex::Conjugate(QhfPlus[ibin][1])*TComplex::Conjugate(QhfPlus[ibin][1]);
         if(useRe) tempReal=temp.Re();
         else tempReal=TComplex::Abs(temp);
         hv4V2starV2star[ibin][cpt]->Fill(tempReal);
         temp=TComplex::Exp(TComplex(0,(6)*phi_trkMinus))*TComplex::Conjugate(QhfPlus[ibin][1])*TComplex::Conjugate(QhfPlus[ibin][1])*TComplex::Conjugate(QhfPlus[ibin][1]);
         if(useRe) tempReal=temp.Re();
         else tempReal=TComplex::Abs(temp);
         hv6V2starV2starV2star[ibin][cpt]->Fill(tempReal);
         temp=TComplex::Exp(TComplex(0,(6)*phi_trkMinus))*TComplex::Conjugate(QhfPlus[ibin][2])*TComplex::Conjugate(QhfPlus[ibin][2]);
         if(useRe) tempReal=temp.Re();
         else tempReal=TComplex::Abs(temp);
         hv6V3starV3star[ibin][cpt]->Fill(tempReal);
         temp=TComplex::Exp(TComplex(0,(5)*phi_trkMinus))*TComplex::Conjugate(QhfPlus[ibin][1])*TComplex::Conjugate(QhfPlus[ibin][2]);
         if(useRe) tempReal=temp.Re();
         else tempReal=TComplex::Abs(temp);
         hv5V2starV3star[ibin][cpt]->Fill(tempReal);
         temp=TComplex::Exp(TComplex(0,(7)*phi_trkMinus))*TComplex::Conjugate(QhfPlus[ibin][1])*TComplex::Conjugate(QhfPlus[ibin][1])*TComplex::Conjugate(QhfPlus[ibin][2]);
         if(useRe) tempReal=temp.Re();
         else tempReal=TComplex::Abs(temp);
         hv7V2starV2starV3star[ibin][cpt]->Fill(tempReal);
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
      hVnAbs2[ibin][iH] = fs->make<TH1D>(Form("hVnAbs2_ibin%d_iH%d",ibin,iH),"",200,-1000,1000);
      hVnAbs4[ibin][iH] = fs->make<TH1D>(Form("hVnAbs4_ibin%d_iH%d",ibin,iH),"",200,-1000,1000);
      hVnAbs6[ibin][iH] = fs->make<TH1D>(Form("hVnAbs6_ibin%d_iH%d",ibin,iH),"",200,-1000,1000);
    }
    hV2Abs2V3Abs2[ibin] = fs->make<TH1D>(Form("hV2Abs2V3Abs2_ibin%d",ibin),"",200,-1000,1000);
    hV2Abs4V3Abs2[ibin] = fs->make<TH1D>(Form("hV2Abs4V3Abs2_ibin%d",ibin),"",200,-1000,1000);

    hV2V2star[ibin] = fs->make<TH1D>(Form("hV2V2star_ibin%d",ibin),"",200,-1000,1000);
    hV4V2starV2star[ibin] = fs->make<TH1D>(Form("hV4V2starV2star_ibin%d",ibin),"",200,-1000,1000);
    hV6V2starV2starV2star[ibin] = fs->make<TH1D>(Form("hV6V2starV2starV2star_ibin%d",ibin),"",200,-1000,1000);
    hV6V3starV3star[ibin] = fs->make<TH1D>(Form("hV6V3starV3star_ibin%d",ibin),"",200,-1000,1000);
    hV5V2starV3star[ibin] = fs->make<TH1D>(Form("hV5V2starV3star_ibin%d",ibin),"",200,-1000,1000);
    hV7V2starV2starV3star[ibin] = fs->make<TH1D>(Form("hV7V2starV2starV3star_ibin%d",ibin),"",200,-1000,1000);
    for(int ipt=0; ipt<nPtBin; ipt++){
      hv2V2star[ibin][ipt] = fs->make<TH1D>(Form("hv2V2star_ibin%d_ipt%d",ibin,ipt),"",200,-1000,1000);
      hv4V2starV2star[ibin][ipt] = fs->make<TH1D>(Form("hv4V2starV2star_ibin%d_ipt%d",ibin,ipt),"",200,-1000,1000);
      hv6V2starV2starV2star[ibin][ipt] = fs->make<TH1D>(Form("hv6V2starV2starV2star_ibin%d_ipt%d",ibin,ipt),"",200,-1000,1000);
      hv6V3starV3star[ibin][ipt] = fs->make<TH1D>(Form("hv6V3starV3star_ibin%d_ipt%d",ibin,ipt),"",200,-1000,1000);
      hv5V2starV3star[ibin][ipt] = fs->make<TH1D>(Form("hv5V2starV3star_ibin%d_ipt%d",ibin,ipt),"",200,-1000,1000);
      hv7V2starV2starV3star[ibin][ipt] = fs->make<TH1D>(Form("hv7V2starV2starV3star_ibin%d_ipt%d",ibin,ipt),"",200,-1000,1000);
    }
  }

}

// ------------ method called once each job just after ending the event loop  ------------
void 
FlowCorr::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
void 
FlowCorr::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
FlowCorr::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
FlowCorr::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
FlowCorr::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
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
