// -*- C++ -*-
//
// Package:    C2nMeanPtAnalysis/TreeProduction
// Class:      TreeProduction
//
/**\class TreeProduction TreeProduction.cc C2nMeanPtAnalysis/TreeProduction/plugins/TreeProduction.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Shengquan Tuo
//         Created:  Tue, 19 Oct 2021 22:19:52 GMT
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
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "DataFormats/PatCandidates/interface/PackedCandidate.h"
#include "DataFormats/Common/interface/ValueMap.h"

#include "DataFormats/HeavyIonEvent/interface/Centrality.h"
#include "DataFormats/HeavyIonEvent/interface/CentralityBins.h"
#include "RecoHI/HiEvtPlaneAlgos/interface/HiEvtPlaneList.h"
#include "DataFormats/HeavyIonEvent/interface/EvtPlane.h"

#include "TH1D.h"
#include "TH2D.h"
#include "TTree.h"

using namespace std;
using namespace reco;
using namespace edm;

  int maxNchAnalysis = 300;
  double minEta = -2.4;
  double maxEta = 2.4;


//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<>
// This will improve performance in multithreaded jobs.

using reco::TrackCollection;

class TreeProduction : public edm::one::EDAnalyzer<edm::one::SharedResources> {
public:
  explicit TreeProduction(const edm::ParameterSet&);
  ~TreeProduction();

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

private:
  void beginJob() override;
  void analyze(const edm::Event&, const edm::EventSetup&) override;
  void endJob() override;

  // ----------member data ---------------------------
  edm::EDGetTokenT< edm::View< pat::PackedCandidate > > tracksToken_;
  edm::EDGetTokenT< reco::VertexCollection > vertexToken_;
  edm::EDGetTokenT< edm::ValueMap< float > > chi2Map_;
  edm::EDGetTokenT< reco::Centrality > centralityTag_;
  edm::EDGetTokenT< int > centralityBinTag_;
  //edm::EDGetTokenT< std::vector<reco::EvtPlane> > eventPlane_;
  bool isPixelTracks_;

  TTree *trackTree;

      // vetex
      float _vz;
      float _vy;
      float _vx;

      // centrality
      int _centralityBin;
      int _nTrkOffline;

      // tracks
      static const int _nTrkMax = 10000;
      int _nTrk;
      float _trackPt[_nTrkMax];
      float _trackEta[_nTrkMax];
      float _trackPhi[_nTrkMax];

      float _trackPtErrOverPt[_nTrkMax];
      float _trackDzOverDzSigma[_nTrkMax];
      float _trackDxyOverDxySigma[_nTrkMax];
      float _trackChiNdofOverNlayers[_nTrkMax];
      float _trackNHits[_nTrkMax];

  //TH2F* histNtrk_NtrkCut;

#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
  edm::ESGetToken<SetupData, SetupRecord> setupToken_;
#endif
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
TreeProduction::TreeProduction(const edm::ParameterSet& iConfig)
    : tracksToken_( consumes< edm::View< pat::PackedCandidate > >( iConfig.         getParameter< edm::InputTag >( "tracks" ) ) ),
      vertexToken_( consumes< reco::VertexCollection >( iConfig.getParameter< edm:: InputTag >( "vertices" ) ) ),
      chi2Map_( consumes< edm::ValueMap< float > >( iConfig.getParameter< edm::     InputTag >( "trackschi2" ) ) ),
      centralityTag_( consumes< reco::Centrality >( iConfig.getParameter< edm::     InputTag >( "centrality" ) ) ),
      centralityBinTag_( consumes< int >( iConfig.getParameter< edm::InputTag >(    "centralityBin" ) ) ),
//      eventPlane_( consumes< std::vector< reco::EvtPlane > >( iConfig.getParameter< edm::InputTag >( "eventPlane" ) ) ),
      isPixelTracks_( iConfig.getParameter< bool >( "isPixelTracks" ) ) {
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
  setupDataToken_ = esConsumes<SetupData, SetupRecord>();
#endif
  //now do what ever initialization is needed
}

TreeProduction::~TreeProduction() {
  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)
  //
  // please remove this method altogether if it would be left empty
}

//
// member functions
//

// ------------ method called for each event  ------------
void TreeProduction::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {

   //access centrality bins
   auto cbin = iEvent.getHandle( centralityBinTag_ );
   int cent = -1;
   cent = ( int ) (*cbin);
   //hist_cent_->Fill(cent);
   if(cent<60) return;

    edm::Handle<reco::Centrality> centrality;
    iEvent.getByToken(centralityTag_, centrality);
    //cout<<" cent = "<<cent<<" ;  hiNtracks = "<<centrality->Ntracks()<<endl;
    _nTrkOffline = centrality->Ntracks();

   //track collection
   auto trks = iEvent.getHandle( tracksToken_ );

   //access tracks chi2/ndf
   auto chi2Map = iEvent.getHandle( chi2Map_ );  

   //vtx collection
   auto pvs = iEvent.getHandle( vertexToken_ );

   //best vertex
   double bestvzError;
   math::XYZPoint bestvtx;
   math::Error<3>::type vtx_cov;
   if ( !pvs->empty() ) {
      const reco::Vertex& vtx = (*pvs)[0];
      bestvzError = vtx.zError();
      bestvtx = vtx.position();
      vtx_cov = vtx.covariance();      
   }else { 
      return; 
   }
   
   if ( std::abs( bestvtx.z() ) > 15. ) return;
   //if (  std::sqrt(bestvtx.x()*bestvtx.x() + bestvtx.y()*bestvtx.y())  > 0.2 ) return;

     _vz = bestvtx.z();
     _vy = bestvtx.y();
     _vx = bestvtx.x();
     _centralityBin = cent;

   //loop over tracks
   _nTrk = 0;
   //int nTrkCut = 0;
   int trkIndx = -1;
   for (auto const& trk : *trks) {   

      trkIndx++;      

      if ( !trk.hasTrackDetails() ) continue;
      auto iter_tk = trk.pseudoTrack(); 

      double pTcut = -1.;
      if( !isPixelTracks_ ) {
         pTcut = 0.5;
      } else {
         pTcut = 0.3;
      }

      if ( iter_tk.pt() <= pTcut ) continue;
      if ( std::abs( iter_tk.eta() ) >= 2.4 ) continue;

      double dzvtx = iter_tk.dz( bestvtx );
      double dxyvtx = iter_tk.dxy( bestvtx );
      double dzerror = std::hypot( iter_tk.dzError(), bestvzError );
      double dxyerror = iter_tk.dxyError( bestvtx, vtx_cov );     
     
      auto hit_pattern = iter_tk.hitPattern();
     
      double chi2ndof = 999.9;
 
      if ( !isPixelTracks_ ) {
         //general tracks selection for 2018 PbPb data
         chi2ndof = ( double ) ( *chi2Map )[ trks->ptrAt( trkIndx ) ];
         if ( std::abs( iter_tk.ptError() ) / iter_tk.pt() >= 0.15 ) continue; //default 0.1/loose 0.15
         if ( std::abs( dzvtx / dzerror ) >= 5 ) continue; //default 3/loose 5
         if ( std::abs( dxyvtx / dxyerror ) >= 5 ) continue; //default 3/loose 5
         if ( ( chi2ndof / hit_pattern.trackerLayersWithMeasurement() ) >= 0.18 ) continue;
         if ( iter_tk.numberOfValidHits() < 11 ) continue;
         if ( iter_tk.charge() == 0 ) continue; //adding charge requirement
      } else {
         //pixel tracks selection for 2018 PbPb data
         chi2ndof = iter_tk.normalizedChi2(); 
         if ( std::abs( dzvtx / dzerror ) >= 7 ) continue;
         if ( std::abs( dxyvtx / dxyerror ) >= 7 ) continue;
      }       

      //please, do whatever you want here with your selected tracks    
  
      //std::cout<<" pt: "<<iter_tk.pt()<<"; eta: "<<iter_tk.eta()<<"; phi: "<<iter_tk.phi()<<"; chi2/ndf/nlayers: "<<chi2ndof / hit_pattern.trackerLayersWithMeasurement()<<std::endl;  
      //hist_trkpt_->Fill( iter_tk.pt() );
      //hist_trketa_->Fill( iter_tk.eta() );
      //hist_trkphi_->Fill( iter_tk.phi() ); 
      //hist_trkdzsig_->Fill( dzvtx / dzerror );
      //hist_trkdxysig_->Fill( dxyvtx / dxyerror );
      //hist_trkptres_->Fill( std::abs( iter_tk.ptError() ) / iter_tk.pt() );
      //hist_trkchi2_->Fill( chi2ndof / hit_pattern.trackerLayersWithMeasurement() );
      //hist_trkNHits_->Fill( iter_tk.numberOfValidHits() );

      if(iter_tk.eta()>=maxEta || iter_tk.eta()<=minEta) continue;
       _trackPt[_nTrk] = iter_tk.pt();
       _trackEta[_nTrk] = iter_tk.eta();
       _trackPhi[_nTrk] = iter_tk.phi();      
       _trackPtErrOverPt[_nTrk] = std::abs( iter_tk.ptError() ) / iter_tk.pt();
       _trackDzOverDzSigma[_nTrk] = dzvtx / dzerror;
       _trackDxyOverDxySigma[_nTrk] = dxyvtx / dxyerror;
       _trackChiNdofOverNlayers[_nTrk] = chi2ndof / hit_pattern.trackerLayersWithMeasurement();
       _trackNHits[_nTrk] = iter_tk.numberOfValidHits();

       _nTrk++;

      //if(iter_tk.pt()>0.5 && iter_tk.pt()<5.0)  nTrkCut++;

   }

  if(_nTrk==0 || _nTrk>maxNchAnalysis) return;

  trackTree->Fill(); 

  //histNtrk_NtrkCut->Fill(_nTrk, nTrkCut);

#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
  // if the SetupData is always needed
  auto setup = iSetup.getData(setupToken_);
  // if need the ESHandle to check if the SetupData was there or not
  auto pSetup = iSetup.getHandle(setupToken_);
#endif
}

// ------------ method called once each job just before starting event loop  ------------
void TreeProduction::beginJob() {
  // please remove this method if not needed

  edm::Service< TFileService > fs;
  TH1D::SetDefaultSumw2();

  trackTree = fs->make<TTree>("trackTree","track tree");
  // tracks
  trackTree->Branch("nTrk", &_nTrk, "nTrk/I"); // number of tracks
  trackTree->Branch("trackPt", _trackPt, "trackPt[nTrk]/F"); // track pT
  trackTree->Branch("trackEta", _trackEta, "trackEta[nTrk]/F"); // track eta
  trackTree->Branch("trackPhi", _trackPhi, "trackPhi[nTrk]/F"); // track phi
  trackTree->Branch("trackPtErrOverPt", _trackPtErrOverPt, "trackPtErrOverPt[nTrk]/F"); // track ptErr/pt
  trackTree->Branch("trackDzOverDzSigma", _trackDzOverDzSigma, "trackDzOverDzSigma[nTrk]/F"); // track dzsigma/dz
  trackTree->Branch("trackDxyOverDxySigma", _trackDxyOverDxySigma, "trackDxyOverDxySigma[nTrk]/F"); // track dxysigma/dxy
  trackTree->Branch("trackChiNdofOverNlayers", _trackChiNdofOverNlayers, "trackChiNdofOverNlayers[nTrk]/F"); // track Chi^2/ndof/Nlayers
  trackTree->Branch("trackNHits", _trackNHits, "trackNHits[nTrk]/F"); // track Chi^2/ndof/Nlayers

  trackTree->Branch("vz", &_vz, "vz/F"); // z component of the primary vertex
  trackTree->Branch("vy", &_vy, "vy/F"); // y component of the primary vertex
  trackTree->Branch("vx", &_vx, "vx/F"); // x component of the primary vertex
  trackTree->Branch("centralityBin", &_centralityBin, "centralityBin/I"); // centrality bin (200 total)
  trackTree->Branch("nTrkOffline", &_nTrkOffline, "nTrkOffline/I"); // hiNtracks from centrality collection

  //histNtrk_NtrkCut = fs->make<TH2F>(Form("histNtrk_NtrkCut"),"", 400,0,400, 400,0,400);  

}

// ------------ method called once each job just after ending the event loop  ------------
void TreeProduction::endJob() {
  // please remove this method if not needed
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void TreeProduction::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);

  //Specify that only 'tracks' is allowed
  //To use, remove the default given above and uncomment below
  //ParameterSetDescription desc;
  //desc.addUntracked<edm::InputTag>("tracks","ctfWithMaterialTracks");
  //descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(TreeProduction);
