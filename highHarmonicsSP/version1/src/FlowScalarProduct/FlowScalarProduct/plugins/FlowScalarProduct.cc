// -*- C++ -*-
//
// Package:    FlowScalarProduct/FlowScalarProduct
// Class:      FlowScalarProduct
//
/**\class FlowScalarProduct FlowScalarProduct.cc FlowScalarProduct/FlowScalarProduct/plugins/FlowScalarProduct.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Shengquan Tuo
//         Created:  Wed, 05 Apr 2023 20:44:27 GMT
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

#include "TComplex.h"
#include <vector>
#include <TVector3.h>

using namespace std;
using namespace reco;
using namespace edm;

//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<>
// This will improve performance in multithreaded jobs.

using reco::TrackCollection;

class FlowScalarProduct : public edm::one::EDAnalyzer<edm::one::SharedResources> {
public:
  explicit FlowScalarProduct(const edm::ParameterSet&);
  ~FlowScalarProduct();

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

private:
  void beginJob() override;
  void analyze(const edm::Event&, const edm::EventSetup&) override;
  void endJob() override;

  // ----------member data ---------------------------

  edm::EDGetTokenT< edm::View< pat::PackedCandidate > > tracksToken_;
  edm::EDGetTokenT< pat::PackedCandidateCollection > pfToken_;
  edm::EDGetTokenT< reco::VertexCollection > vertexToken_;
  edm::EDGetTokenT< edm::ValueMap< float > > chi2Map_;
//  edm::EDGetTokenT< reco::Centrality > centralityTag_;
  edm::EDGetTokenT< int > centralityBinTag_;
  //edm::EDGetTokenT< std::vector<reco::EvtPlane> > eventPlane_;
  bool isPixelTracks_;

  edm::Service<TFileService> fs;

  static const int nCentBin = 14;
  static const int nHarmonics = 20;
  static const int nPtBin = 18;
  double cBin[nCentBin+1]={0,5,10,15,20,25,30,35,40,50,60,70,80,90,100};
  double ptBins[nPtBin+1]={0.5, 0.6, 0.8, 1.0, 1.25, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 5.0, 6.0, 7.0, 8.0, 10.0, 12.0, 14.0, 20000.0};


  TComplex QhfPlus[nCentBin][nHarmonics];
  TComplex QhfMinus[nCentBin][nHarmonics];
  TComplex QtrkPtPlus[nCentBin][nHarmonics][nPtBin];
  TComplex QtrkPtMinus[nCentBin][nHarmonics][nPtBin];
  TH1D* hqnPlusQnMinusStar[nCentBin][nHarmonics][nPtBin];
  TH1D* hqnMinusQnPlusStar[nCentBin][nHarmonics][nPtBin];
  TH1D* hQnPlusQnMinusStar[nCentBin][nHarmonics];
  TH1D* hMeanPt[nCentBin][nPtBin];

  double sumwPlus[nCentBin];
  double sumwMinus[nCentBin];
  double sumwPlusTrk[nCentBin][nPtBin];
  double sumwMinusTrk[nCentBin][nPtBin];

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
FlowScalarProduct::FlowScalarProduct(const edm::ParameterSet& iConfig)
    : tracksToken_( consumes< edm::View< pat::PackedCandidate > >( iConfig.getParameter< edm::InputTag >( "tracks" ) ) ),
      pfToken_(consumes<pat::PackedCandidateCollection>(iConfig.getParameter<edm::InputTag>("pfCands"))),
      vertexToken_( consumes< reco::VertexCollection >( iConfig.getParameter< edm::InputTag >( "vertices" ) ) ),
      chi2Map_( consumes< edm::ValueMap< float > >( iConfig.getParameter< edm::InputTag >( "trackschi2" ) ) ),
//      centralityTag_( consumes< reco::Centrality >( iConfig.getParameter< edm::InputTag >( "centrality" ) ) ),
      centralityBinTag_( consumes< int >( iConfig.getParameter< edm::InputTag >(    "centralityBin" ) ) ),
//      eventPlane_( consumes< std::vector< reco::EvtPlane > >( iConfig.getParameter< edm::InputTag >( "eventPlane" ) ) ),
      isPixelTracks_( iConfig.getParameter< bool >( "isPixelTracks" ) ) {
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
  setupDataToken_ = esConsumes<SetupData, SetupRecord>();
#endif
  //now do what ever initialization is needed
}

FlowScalarProduct::~FlowScalarProduct() {
  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)
  //
  // please remove this method altogether if it would be left empty
}

//
// member functions
//

// ------------ method called for each event  ------------
void FlowScalarProduct::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
  using namespace edm;

   //access centrality bins
   auto cbin = iEvent.getHandle( centralityBinTag_ );
   int cent = -1;
   cent = ( int ) (*cbin);
   //hist_cent_->Fill(cent);
   //if(cent<60) return;
   int ibin=-1;
   for(int j=0;j<nCentBin;j++)
   if(cent>=2*cBin[j]&&cent<2*cBin[j+1])
     ibin=j;
   if(ibin<0 || ibin==nCentBin) return;

    //cout<<" cent = "<<cent<<endl;

    //edm::Handle<reco::Centrality> centrality;
    //iEvent.getByToken(centralityTag_, centrality);
    //cout<<" cent = "<<cent<<" ;  hiNtracks = "<<centrality->Ntracks()<<endl;
    //_nTrkOffline = centrality->Ntracks();

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
   //cout<<" bestvzError = "<<bestvzError<<endl;


   for(int iC=0;iC<nCentBin;iC++){
     sumwPlus[iC] = 0.0;
     sumwMinus[iC] = 0.0;
     for(int iPt=0; iPt<nPtBin; iPt++){
       sumwPlusTrk[iC][iPt] = 0.0;
       sumwMinusTrk[iC][iPt] = 0.0;
     }
     for(int iH=0; iH<nHarmonics; iH++){
       QhfPlus[iC][iH] = 0;
       QhfMinus[iC][iH] = 0;
       for(int iPt=0; iPt<nPtBin; iPt++){
         QtrkPtPlus[iC][iH][iPt] = 0;
         QtrkPtMinus[iC][iH][iPt] = 0;
       }
     }
   }


   //loop over tracks
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
         if ( std::abs( iter_tk.ptError() ) / iter_tk.pt() >= 0.1 ) continue;
         if ( std::abs( dzvtx / dzerror ) >= 3 ) continue;
         if ( std::abs( dxyvtx / dxyerror ) >= 3 ) continue;
         if ( ( chi2ndof / hit_pattern.trackerLayersWithMeasurement() ) >= 0.18 ) continue;
         if ( iter_tk.numberOfValidHits() < 11 ) continue;
      } else {
         //pixel tracks selection for 2018 PbPb data
         chi2ndof = iter_tk.normalizedChi2(); 
         if ( std::abs( dzvtx / dzerror ) >= 7 ) continue;
         if ( std::abs( dxyvtx / dxyerror ) >= 7 ) continue;
      }       

      //please, do whatever you want here with your selected tracks   
      int cpt=-1;
      for(int ipt=0; ipt<nPtBin; ipt++){
        if(iter_tk.pt()>=ptBins[ipt] && iter_tk.pt()<ptBins[ipt+1])
          cpt=ipt;
      }
      if(cpt<0) cpt=nPtBin-1;

      hMeanPt[ibin][cpt]->Fill(iter_tk.pt());
      double pt_weight = 1.0; 
      if(iter_tk.eta() > 0 ){
        sumwPlusTrk[ibin][cpt]+= pt_weight;
        for(int iH=0; iH<nHarmonics; iH++){
          QtrkPtPlus[ibin][iH][cpt]+= pt_weight * TComplex::Exp(TComplex(0,(iH+1)*iter_tk.phi()));        
        }
      }
      if(iter_tk.eta() < 0 ){
        sumwMinusTrk[ibin][cpt]+= pt_weight;
        for(int iH=0; iH<nHarmonics; iH++){
          QtrkPtMinus[ibin][iH][cpt]+= pt_weight * TComplex::Exp(TComplex(0,(iH+1)*iter_tk.phi()));
        }
      }

   } // end trk
    for(int iH=0; iH<nHarmonics; iH++){
      for(int iPt=0; iPt<nPtBin; iPt++){
        if(sumwPlusTrk[ibin][iPt]>0) { QtrkPtPlus[ibin][iH][iPt]=QtrkPtPlus[ibin][iH][iPt]/sumwPlusTrk[ibin][iPt]; }
        else {QtrkPtPlus[ibin][iH][iPt]=0; }
        if(sumwMinusTrk[ibin][iPt]>0) { QtrkPtMinus[ibin][iH][iPt]=QtrkPtMinus[ibin][iH][iPt]/sumwMinusTrk[ibin][iPt]; }
        else { QtrkPtMinus[ibin][iH][iPt]=0; }
      }
    }//iH
  //cout<<" trkIndx = "<<trkIndx<<endl;


  //hf from pf 
  edm::Handle<pat::PackedCandidateCollection> pfs;
  iEvent.getByToken(pfToken_, pfs);
  for(unsigned int i = 0, n = pfs->size(); i < n; ++i) {
    const pat::PackedCandidate &pf = (*pfs)[i];
    // pdfId 1 and 2 for hadronic and em particles in HF
    if(pf.pdgId() == 1 || pf.pdgId() == 2){
      if(pf.et()<0.01 || pf.et()>30) continue;

      double pt_weight = 1.0;
      if(pf.eta()>3.0 && pf.eta()<5.2){
        sumwPlus[ibin]+= pt_weight;
        for(int iH=0; iH<nHarmonics; iH++){
          QhfPlus[ibin][iH]+= pt_weight * TComplex::Exp(TComplex(0,(iH+1)*pf.phi()));
        }
      }
      if(pf.eta()<-3.0 && pf.eta()>-5.2){
        sumwMinus[ibin]+= pt_weight;
        for(int iH=0; iH<nHarmonics; iH++){
          QhfMinus[ibin][iH]+= pt_weight * TComplex::Exp(TComplex(0,(iH+1)*pf.phi()));
        }
      }

    } // end pf hf
  } // end pf
    for(int iH=0; iH<nHarmonics; iH++){
      if(sumwPlus[ibin]>0) { QhfPlus[ibin][iH]=QhfPlus[ibin][iH]/sumwPlus[ibin]; }
      else { QhfPlus[ibin][iH]=0; }
      if(sumwMinus[ibin]>0) { QhfMinus[ibin][iH]=QhfMinus[ibin][iH]/sumwMinus[ibin]; }
      else { QhfMinus[ibin][iH]=0; }
    }//iH

    // final histograms
    for(int iH=0; iH<nHarmonics; iH++){
      hQnPlusQnMinusStar[ibin][iH]->Fill((QhfPlus[ibin][iH]*TComplex::Conjugate(QhfMinus[ibin][iH])).Re());
      for(int iPt=0; iPt<nPtBin; iPt++){
        hqnPlusQnMinusStar[ibin][iH][iPt]->Fill((QtrkPtPlus[ibin][iH][iPt]*TComplex::Conjugate(QhfMinus[ibin][iH])).Re());
        hqnMinusQnPlusStar[ibin][iH][iPt]->Fill((QtrkPtMinus[ibin][iH][iPt]*TComplex::Conjugate(QhfPlus[ibin][iH])).Re());
      }
    }



#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
  // if the SetupData is always needed
  auto setup = iSetup.getData(setupToken_);
  // if need the ESHandle to check if the SetupData was there or not
  auto pSetup = iSetup.getHandle(setupToken_);
#endif
}

// ------------ method called once each job just before starting event loop  ------------
void FlowScalarProduct::beginJob() {
  // please remove this method if not needed
  TH1D::SetDefaultSumw2();
  for(int iC=0;iC<nCentBin;iC++){
    for(int iH=0; iH<nHarmonics; iH++){
      hQnPlusQnMinusStar[iC][iH] = fs->make<TH1D>(Form("hQnPlusQnMinusStar_iC%d_iH%d",iC,iH),"",100,-1000,1000);
      for(int iPt=0; iPt<nPtBin; iPt++){
        hqnPlusQnMinusStar[iC][iH][iPt] = fs->make<TH1D>(Form("hqnPlusQnMinusStar_iC%d_iH%d_iPt%d",iC,iH,iPt),"",100,-1000,1000);
        hqnMinusQnPlusStar[iC][iH][iPt] = fs->make<TH1D>(Form("hqnMinusQnPlusStar_iC%d_iH%d_iPt%d",iC,iH,iPt),"",100,-1000,1000);
      }
    }//iH
    for(int iPt=0; iPt<nPtBin; iPt++){
      hMeanPt[iC][iPt] = fs->make<TH1D>(Form("hMeanPt_iC%d_iPt%d",iC,iPt),"",100,0,20);
    }
  }  


}

// ------------ method called once each job just after ending the event loop  ------------
void FlowScalarProduct::endJob() {
  // please remove this method if not needed
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void FlowScalarProduct::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
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
DEFINE_FWK_MODULE(FlowScalarProduct);
