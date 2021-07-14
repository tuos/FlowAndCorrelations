void image_prod(){

  ifstream inputData;
  inputData.open("/store/user/anderht3/cent0_pt_total.txt");
  const int totalEvent = 100;
  int nEvt;
  int nParticle;
  double tmp;
  const int maxParticle = 30000;
  double pt[maxParticle];
  double phi[maxParticle];
  TH2D *histImages[totalEvent];
  for(int i=0; i<totalEvent; i++){
    histImages[i] = new TH2D(Form("imagesPtVsPhi_%d",i),"",10,-1*TMath::Pi(),TMath::Pi(), 10,0.0,2.0);
  }

  inputData>>nEvt;
  for(int i=0; i<nEvt; i++){
    if(i%10==0) cout<<"running event #: "<<i<<endl;
    inputData>>tmp;
    inputData>>nParticle;
    inputData>>tmp;
    for(int j=0; j<nParticle; j++){
      inputData>>pt[j];
      inputData>>phi[j];
      histImages[i]->Fill(phi[j], pt[j]);   
    }

  }

  TCanvas *c1 = new TCanvas("c1","c1",1,1,550,550);
  c1->SetFillColor(10);
  c1->SetFrameFillColor(0);
  c1->SetFrameBorderSize(0);
  c1->SetFrameBorderMode(0);
  c1->SetLeftMargin(0.);
  c1->SetBottomMargin(0.);
  c1->SetTopMargin(0.0);
  c1->SetRightMargin(0.0);
  gStyle->SetOptStat(0);

  for(int i=0; i<totalEvent; i++){
    histImages[i]->Draw("colAH");
    c1->SaveAs(Form("/store/user/tuos/healpy/savedImages/savedImagesPtVsPhi_%d.png",i)); 
  }


}

