#include "TH1.h"
#include "TFile.h"
void FourierDecomposition(){

  gStyle->SetOptStat(0);
  
  // input 1d correlation function 
  //
  float V1=-0.05, V2=0.02, V3=0.01, V4=0.005, V5=0.003, V6=0.001;
  TF1 *inputDist = new TF1("inputDist","[0]*(1 + 2*[1]*cos(x) + 2*[2]*cos(2*x) + 2*[3]*cos(3*x) + 2*[4]*cos(4*x) + 2*[5]*cos(5*x) + 2*[6]*cos(6*x))",-TMath::Pi()/2, TMath::Pi()*3/2);
  inputDist->SetParameter(0, 1);
  inputDist->SetParameter(1, V1);
  inputDist->SetParameter(2, V2);
  inputDist->SetParameter(3, V3);
  inputDist->SetParameter(4, V4);
  inputDist->SetParameter(5, V5);
  inputDist->SetParameter(6, V6);

  // create 1d histogram and fill it 1 million times following the input function
  TH1D *corr_1d = new TH1D("corr_1d", "", 64, -TMath::Pi()/2, TMath::Pi()*3/2);
  corr_1d->Sumw2();
  for(int i=0; i<1000000; i++){
    corr_1d->Fill(inputDist->GetRandom());
  }
  corr_1d->Scale(64.0/corr_1d->GetEntries());

  TCanvas *c1 = new TCanvas("c1","c1",1,1,600,500);
  c1->SetFillColor(10);
  c1->SetFrameFillColor(0);
  c1->SetFrameBorderSize(0);
  c1->SetFrameBorderMode(0);
  c1->SetLeftMargin(0.16);
  c1->SetBottomMargin(0.12);
  c1->SetTopMargin(0.03);
  c1->SetRightMargin(0.03);

  corr_1d->GetXaxis()->SetTitle("|#Delta#phi|");
  corr_1d->GetXaxis()->CenterTitle();
  corr_1d->GetYaxis()->SetTitle("#frac{1}{N_{trig}}#frac{dN^{pair}}{d#Delta#phi}");
  corr_1d->GetYaxis()->CenterTitle();
  corr_1d->GetYaxis()->SetTitleOffset(1.3);
  corr_1d->GetXaxis()->SetTitleOffset(1.2);
  corr_1d->GetYaxis()->SetTitleSize(0.052);
  corr_1d->GetXaxis()->SetTitleSize(0.042);
  corr_1d->GetYaxis()->SetLabelSize(0.045);
  corr_1d->GetXaxis()->SetLabelSize(0.045);
  corr_1d->SetLineColor(1);
  corr_1d->SetMarkerStyle(24);
  corr_1d->SetMarkerColor(1);

  //corr_1d->Draw("p");

  TF1 *fit = new TF1("fit","[0]*(1 + 2*[1]*cos(x) + 2*[2]*cos(2*x) + 2*[3]*cos(3*x) + 2*[4]*cos(4*x) + 2*[5]*cos(5*x) + 2*[6]*cos(6*x))",-TMath::Pi()/2, TMath::Pi()*3/2);
  //fit->SetParameters(1,0.1,0.05,0.003,0.002,0.001);
  fit->SetLineStyle(2);
  fit->SetLineColor(1);
  fit->SetLineWidth(2);
  corr_1d->Fit("fit","R+");

  ofstream txt_out_fit;
  txt_out_fit.open("txt_out_fit.txt");
  cout<<"chi2 = "<<fit->GetChisquare()<<", NDF="<<fit->GetNDF()<<",  chi2/ndf= "<<fit->GetChisquare()/fit->GetNDF()<<endl;

  const int nOrder=7;
  double para[nOrder]; double paraErr[nOrder];
  for(int i=0;i<nOrder;i++){
    para[i]=fit->GetParameter(i);
    paraErr[i]=fit->GetParError(i);
    cout<<"para_i="<<para[i]<<",  paraErr_i="<<paraErr[i]<<endl;
    txt_out_fit<<i<<"    "<<"V_n="<<para[i]<<",  V_n_Err="<<paraErr[i]<<endl;
  }
  txt_out_fit<<"chi2 = "<<fit->GetChisquare()<<", NDF="<<fit->GetNDF()<<",  chi2/ndf= "<<fit->GetChisquare()/fit->GetNDF()<<endl;

  cout<<"Input Vn:"<<endl;
  cout<<"V1="<<V1<<",  V2="<<V2<<",  V3="<<V3<<",  V4="<<V4<<",  V5="<<V5<<",  V6="<<V6<<endl;
  txt_out_fit<<"Input Vn:"<<endl;
  txt_out_fit<<"V1="<<V1<<",  V2="<<V2<<",  V3="<<V3<<",  V4="<<V4<<",  V5="<<V5<<",  V6="<<V6<<endl;

  TF1 *fun1 = new TF1("fun1","[0]*(1 + 2*[1]*cos(x))",-TMath::Pi()/2, TMath::Pi()*3/2);
  fun1->SetParameter(0,para[0]);
  fun1->SetParameter(1,para[1]);
  fun1->SetLineColor(1);
  fun1->SetLineWidth(2);
  fun1->Draw("lsame");
  TF1 *fun2 = new TF1("fun2","[0]*(1 + 2*[1]*cos(2*x))",-TMath::Pi()/2, TMath::Pi()*3/2);
  fun2->SetParameter(0,para[0]);
  fun2->SetParameter(1,para[2]);
  fun2->SetLineColor(2);
  fun2->SetLineWidth(2);
  fun2->Draw("lsame");

  TF1 *fun3 = new TF1("fun3","[0]*(1 + 2*[1]*cos(3*x))",-TMath::Pi()/2, TMath::Pi()*3/2);
  fun3->SetParameter(0,para[0]);
  fun3->SetParameter(1,para[3]);
  fun3->SetLineColor(4);
  fun3->SetLineWidth(2);
  fun3->Draw("lsame");
  TF1 *fun4 = new TF1("fun4","[0]*(1 + 2*[1]*cos(4*x))",-TMath::Pi()/2, TMath::Pi()*3/2);
  fun4->SetParameter(0,para[0]);
  fun4->SetParameter(1,para[4]);
  fun4->SetLineColor(6);
  fun4->SetLineWidth(2);
  fun4->Draw("lsame");
  TF1 *fun5 = new TF1("fun5","[0]*(1 + 2*[1]*cos(5*x))",-TMath::Pi()/2, TMath::Pi()*3/2);
  fun5->SetParameter(0,para[0]);
  fun5->SetParameter(1,para[5]);
  fun5->SetLineColor(8);
  fun5->SetLineWidth(2);
  fun5->Draw("lsame");
  TF1 *fun6 = new TF1("fun6","[0]*(1 + 2*[1]*cos(6*x))",-TMath::Pi()/2, TMath::Pi()*3/2);
  fun6->SetParameter(0,para[0]);
  fun6->SetParameter(1,para[6]);
  fun6->SetLineColor(52);
  fun6->SetLineWidth(2);
  fun6->Draw("lsame");

  TLegend *leg = new TLegend(0.2,0.65,0.35,0.92);
  leg->SetFillColor(10);
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  leg->SetTextColor(1);
  leg->SetTextSize(0.045);
  leg->AddEntry(fit,"Sum","l");
  leg->AddEntry(fun1,"n=1","l");
  leg->AddEntry(fun2,"n=2","l");
  leg->AddEntry(fun3,"n=3","l");
  leg->AddEntry(fun4,"n=4","l");
  leg->AddEntry(fun5,"n=5","l");
  leg->AddEntry(fun6,"n=6","l");
  leg->Draw();

  double maxm=corr_1d->GetMaximum();
  TLatex *tex1= new TLatex(0.0,maxm*0.9994,"Toy model simulation");
  tex1->SetTextColor(1);
  tex1->SetTextSize(0.045);
  tex1->SetTextFont(42);
  tex1->Draw();

  c1->SaveAs("fig_corr_fit.png");


}


