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


using namespace std;
using namespace reco;
using namespace edm;

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

  edm::Service<TFileService> fs;

   TH1D* hCent;
   TH1D* hHF;
   TH1D* hAngle;
   TH1D* hAngleFlat;
   TH1D* hvz;
   TH1D* hvx;
   TH1D* hvy;
   TH1D* hNtrks;
   TH1D* hpt;
   TH1D* heta;
   TH1D* hphi;

  double trackPtMinCut_;
  double trackPtMaxCut_;
  double trackEtaCut_;
  double ptErrCut_;
  double dzRelCut_;
  double dxyRelCut_;

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
  trackPtMinCut_(iConfig.getParameter<double>("trackPtMinCut")),
  trackPtMaxCut_(iConfig.getParameter<double>("trackPtMaxCut")),
  trackEtaCut_(iConfig.getParameter<double>("trackEtaCut")),
  ptErrCut_(iConfig.getParameter<double>("ptErrCut")),
  dzRelCut_(iConfig.getParameter<double>("dzRelCut")),
  dxyRelCut_(iConfig.getParameter<double>("dxyRelCut")),
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
    hvz->Fill(vz);
    hvx->Fill(vx);
    hvy->Fill(vy);
   

     //edm::Handle<std::vector<reco::Track> tracks;
     //iEvent.getByToken(TrackTag_,tracks);
     Handle<vector<Track>> tracks;
     iEvent.getByToken(TrackTag_, tracks);
     int nTracks = 0;
     for(unsigned int i = 0 ; i < tracks->size(); ++i){
       const Track& track = (*tracks)[i];
       if(!track.quality(reco::TrackBase::qualityByName(TrackQualityTag_))) continue;

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
       }
     }

     hNtrks->Fill(nTracks);

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
