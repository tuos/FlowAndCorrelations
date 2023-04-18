void integrated_vn(){

  static const int nCentBin = 14;
  static const int nHarmonics = 20;
  static const int nPtBin = 18;
  double cBin[nCentBin+1]={0,5,10,15,20,25,30,35,40,50,60,70,80,90,100};
  double ptBins[nPtBin+1]={0.5, 0.6, 0.8, 1.0, 1.25, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 5.0, 6.0, 7.0, 8.0, 10.0, 12.0, 14.0, 20000.0};

  TH1D* hqnPlusQnMinusStar[nCentBin][nHarmonics][nPtBin];
  TH1D* hqnMinusQnPlusStar[nCentBin][nHarmonics][nPtBin];
  TH1D* hQnPlusQnMinusStar[nCentBin][nHarmonics];
  TH1D* hMeanPt[nCentBin][nPtBin];

  double nH[nHarmonics];
  double vnValues[nCentBin][nHarmonics];
  double vnErrors[nCentBin][nHarmonics];

  TFile *inFile = new TFile("./mergedA_pbpbMB_miniAOD_vn_ABCDE_1k.root","read");
   for(int iC=0;iC<nCentBin;iC++){
     for(int iPt=0; iPt<nPtBin; iPt++){
       hMeanPt[iC][iPt] = (TH1D*)inFile->Get(Form("demo/hMeanPt_iC%d_iPt%d",iC, iPt));
     }
     for(int iH=0; iH<nHarmonics; iH++){
       hQnPlusQnMinusStar[iC][iH] = (TH1D*)inFile->Get(Form("demo/hQnPlusQnMinusStar_iC%d_iH%d",iC,iH));
       for(int iPt=0; iPt<nPtBin; iPt++){
         hqnPlusQnMinusStar[iC][iH][iPt] = (TH1D*)inFile->Get(Form("demo/hqnPlusQnMinusStar_iC%d_iH%d_iPt%d",iC,iH,iPt));
         hqnMinusQnPlusStar[iC][iH][iPt] = (TH1D*)inFile->Get(Form("demo/hqnMinusQnPlusStar_iC%d_iH%d_iPt%d",iC,iH,iPt));
       }
     }
   } //iC

  TH1D* hqnQnStarMerged[nCentBin][nHarmonics][nPtBin];
  for(int iC=0;iC<nCentBin;iC++){
    for(int iH=0; iH<nHarmonics; iH++){
      for(int iPt=0; iPt<nPtBin; iPt++){
        hqnQnStarMerged[iC][iH][iPt] = (TH1D*)hqnPlusQnMinusStar[iC][iH][iPt]->Clone(Form("hqnQnStarMerged_iC%d_iH%d_iPt%d",iC,iH,iPt));
        hqnQnStarMerged[iC][iH][iPt]->Reset();
        hqnQnStarMerged[iC][iH][iPt]->Add(hqnPlusQnMinusStar[iC][iH][iPt], hqnMinusQnPlusStar[iC][iH][iPt],  1, 1);
      }
    }
  } //iC


  // integral
  TH1D* hqnQnStarIntegrated[nCentBin][nHarmonics];
  //TH1D* hMeanPtIntegrated[nCentBin];
  for(int iC=0;iC<nCentBin;iC++){
    for(int iH=0; iH<nHarmonics; iH++){
      hqnQnStarIntegrated[iC][iH] = (TH1D*)hqnQnStarMerged[iC][iH][0]->Clone(Form("hqnQnStarMerged_iC%d_iH%d_iPt0",iC,iH));
      hqnQnStarIntegrated[iC][iH]->Reset();
      for(int iPt=0; iPt<9; iPt+=2){
        hqnQnStarIntegrated[iC][iH]->Add(hqnQnStarMerged[iC][iH][iPt], hqnQnStarMerged[iC][iH][iPt+1],  hMeanPt[iC][iPt]->GetEntries(), hMeanPt[iC][iPt+1]->GetEntries());
      }
  
    }
  } //iC


  for(int iH=0; iH<nHarmonics; iH++){ 
    nH[iH] = iH+1;
  }
  for(int iC=0;iC<nCentBin;iC++){ //nCentBin
    for(int iH=0; iH<nHarmonics; iH++){ //nHarmonics
        vnValues[iC][iH] = hqnQnStarIntegrated[iC][iH]->GetMean()/sqrt(fabs(hQnPlusQnMinusStar[iC][iH]->GetMean()));
        vnErrors[iC][iH] = fabs(vnValues[iC][iH]) * sqrt( hqnQnStarIntegrated[iC][iH]->GetMeanError()*hqnQnStarIntegrated[iC][iH]->GetMeanError()/hqnQnStarIntegrated[iC][iH]->GetMean()/hqnQnStarIntegrated[iC][iH]->GetMean() + 1.0/4*hQnPlusQnMinusStar[iC][iH]->GetMeanError()*hQnPlusQnMinusStar[iC][iH]->GetMeanError()/hQnPlusQnMinusStar[iC][iH]->GetMean()/hQnPlusQnMinusStar[iC][iH]->GetMean() );   
    }
  }

  ofstream outTxt;
  outTxt.open("out_sp_255.txt");
  for(int iC=0;iC<nCentBin;iC++){
    for(int iH=0; iH<nHarmonics; iH++){
      cout<<iC<<"  "<<iH<<"     "<<vnValues[iC][iH]<<"  "<<vnErrors[iC][iH]<<endl;
      outTxt<<iC<<"  "<<iH<<"     "<<vnValues[iC][iH]<<"  "<<vnErrors[iC][iH]<<endl;
    }
  }


  TH1D* hvn[nCentBin];
  for(int iC=0;iC<nCentBin;iC++){
      hvn[iC] = new TH1D(Form("hvn_iC%d", iC), Form("hvn_iC%d", iC), 20,0.5,20.5);
      for(int iH=0; iH<nHarmonics; iH++){
        hvn[iC]->SetBinContent(iH+1, vnValues[iC][iH]);
        hvn[iC]->SetBinError(iH+1, vnErrors[iC][iH]);
      }
  }


//draw 
  TCanvas *c1 = new TCanvas("c1","c1",1250,750);
  c1->SetFillColor(10);
  c1->SetFrameFillColor(0);
  c1->SetFrameBorderSize(0);
  c1->SetFrameBorderMode(0);
  c1->SetLeftMargin(0.12);
  c1->SetBottomMargin(0.12);
  c1->SetTopMargin(0.07);
  c1->SetRightMargin(0.02);
  gStyle->SetOptStat(0);
  c1->SetTicks(-1);
  c1->Divide(5,3);
  //c1->Divide(5,3,0,0);

    TLatex *tex= new TLatex();
    tex->SetTextColor(1);
    tex->SetTextSize(0.05);
    tex->SetTextFont(42);

  for(int i=0; i<nCentBin; i++){
    c1->cd(i+1);
    gPad->SetTicks(-1);
    gPad->SetLogy();
    if(i==4||i==9||i==14){
      gPad->SetRightMargin(0.02);
    }
    hvn[i]->SetMaximum(5.5*hvn[i]->GetMaximum());
    hvn[i]->SetMinimum(0.00001*hvn[i]->GetMaximum());
    hvn[i]->SetMarkerStyle(20);
    hvn[i]->SetMarkerColor(1);
    hvn[i]->SetMarkerSize(0.6);
    hvn[i]->Draw("pez");

    tex->DrawLatex(5, -0.2*hvn[i]->GetMaximum(), Form("Cent: %f - %f", cBin[i], cBin[i+1]));

  }  

  c1->SaveAs("plot_look_vn_integrated.png");


}


