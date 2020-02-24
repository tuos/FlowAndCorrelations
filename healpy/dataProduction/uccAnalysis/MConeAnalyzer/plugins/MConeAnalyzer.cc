// -*- C++ -*-
//
// Package:    uccAnalysis/MConeAnalyzer
// Class:      MConeAnalyzer
// 
/**\class MConeAnalyzer MConeAnalyzer.cc uccAnalysis/MConeAnalyzer/plugins/MConeAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Shengquan Tuo
//         Created:  Mon, 24 Feb 2020 22:00:26 GMT
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

#include "uccAnalysis/MConeAnalyzer/plugins/MConeAnalyzer.h"

//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

class MConeAnalyzer : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit MConeAnalyzer(const edm::ParameterSet&);
      ~MConeAnalyzer();

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
MConeAnalyzer::MConeAnalyzer(const edm::ParameterSet& iConfig) :
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


MConeAnalyzer::~MConeAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
MConeAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
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
cout<<"nTracs = "<<nTracks<<endl;

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
MConeAnalyzer::beginJob()
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
  hpt = fs->make<TH1D>("pt","pt",nPtBin,ptBin);
  heta = fs->make<TH1D>("eta","eta",300,-3,3);
  hphi = fs->make<TH1D>("phi","phi",200,-4,4);
  hHFcal = fs->make<TH1D>("hfCal","HF ET",8000,0,8000);


}

// ------------ method called once each job just after ending the event loop  ------------
void 
MConeAnalyzer::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
MConeAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(MConeAnalyzer);
