void plotV3_gap0_gap1()
{
const int NCentBin=15;
const int NCentBin24=24;
  double pt[NCentBin];
  double pta[NCentBin];
  double pta2[NCentBin];
  double pta3[NCentBin];
  double v2a[NCentBin];
  double v2ae[NCentBin];
  double v21[NCentBin];
  double v21e[NCentBin];
  double v22[NCentBin24];
  double v22e[NCentBin24];
  double v23[NCentBin];
  double v23e[NCentBin];

double temp;

  ofstream sysbn;

  ifstream inv2a;
  ifstream inv21;
  ifstream inv22;
  ifstream inv23;
  inv2a.open("v3.txt");
  if(!inv2a.good())    cout<<" input fail"<<endl;
  else cout<<" have put in"<<endl;
  for(int i=0;i<NCentBin;i++){
    inv2a>>pt[i];  
    inv2a>>v2a[i];  
    inv2a>>v2ae[i];  
  } 

  for(int i=0;i<NCentBin;i++){
    inv2a>>pta[i];  //inv21>>temp;
    inv2a>>v21[i];
    inv2a>>v21e[i];
  }
  for(int i=0;i<NCentBin;i++){
    inv2a>>pta2[i];  //inv21>>temp;
    inv2a>>v22[i];
    inv2a>>v22e[i];
  }
  for(int i=0;i<NCentBin;i++){
    inv2a>>pta3[i];  //inv21>>temp;
    inv2a>>v23[i];
    inv2a>>v23e[i];
  }

////////////////
//real data
  const int realN=15;
  double realpt[realN], realv2[realN], realv2state[realN], realv2syse[realN], realv2e[realN];
  ifstream inv2real;
  inv2real.open("realdatacent3035v3EP.txt");
  for(int i=0; i<realN; i++){
    inv2real>>realpt[i];
    inv2real>>realv2[i];
    inv2real>>realv2state[i];
    inv2real>>realv2syse[i];
    realv2e[i]=sqrt(realv2state[i]*realv2state[i] + realv2syse[i]*realv2syse[i]);
    //cout<<realv2e[i]<<endl;
  }

////////
  TCanvas *c1 = new TCanvas("c1","c1",1,1,650,550);
  c1->SetFillColor(10);
  c1->SetFrameFillColor(0);
  c1->SetFrameBorderSize(0);
  c1->SetFrameBorderMode(0);
  c1->SetLeftMargin(0.15);
  c1->SetBottomMargin(0.15);
  c1->SetTopMargin(0.02);
  c1->SetRightMargin(0.02);
  //c1->Divide(2,1,0,0);
 gStyle->SetOptStat(0);
  c1->SetTicks(-1);
 TH1D* hist = new TH1D("hist","",100,0.,5.9);
 hist->SetXTitle("p_{T} (GeV/c)");
 hist->SetYTitle("v_{3}{EP}");
 hist->SetMinimum(0.001);
 hist->SetMaximum(0.199);
 hist->GetXaxis()->CenterTitle(1);
 hist->GetYaxis()->CenterTitle(1);
 hist->GetYaxis()->SetTitleOffset(1.1);
 hist->GetXaxis()->SetTitleOffset(0.95);
 hist->GetXaxis()->SetTitleSize(0.066);
 hist->GetYaxis()->SetTitleSize(0.066);
 hist->GetXaxis()->SetLabelSize(0.05);
 hist->GetYaxis()->SetLabelSize(0.05);
 hist->Draw();

  TF1 *V2vsPt = new TF1("V2vsPt","((x/3.4)^1.8/(1+(x/3)^1.8))*(.00005+(1/x)^0.8)",0.2,10);
  //TF1 *V2vsPt = new TF1("V2vsPt","0.000000001*x+0.04",0.2,10);
  V2vsPt->SetLineColor(1);
  V2vsPt->SetLineWidth(2);
  V2vsPt->SetLineStyle(2);
  //V2vsPt->Draw("same");
  TGraphErrors *grreal = new TGraphErrors(15,realpt,realv2,0,realv2e);
      grreal->SetTitle("");
      grreal->SetMarkerStyle(20);
      grreal->SetMarkerSize(1.0);
      grreal->SetMarkerColor(1);
      grreal->SetLineWidth(2);
      grreal->SetLineColor(1);
  grreal->Draw("plsameez");


  TGraphErrors *gr2 = new TGraphErrors(NCentBin,pt,v2a,0,v2ae);
      gr2->SetTitle("");
      gr2->SetMarkerStyle(21);
      gr2->SetMarkerSize(1.0);
      gr2->SetMarkerColor(2);
      gr2->SetLineWidth(2);
      gr2->SetLineColor(2);
  gr2->Draw("psameez");
 
  TGraphErrors *gr3 = new TGraphErrors(NCentBin,pta,v21,0,v21e);
      gr3->SetMarkerStyle(24);
      gr3->SetMarkerSize(1.);
      gr3->SetMarkerColor(4);
      gr3->SetLineWidth(2);
      gr3->SetLineColor(4);
  gr3->Draw("psameez");

  TGraphErrors *gr4 = new TGraphErrors(NCentBin,pta2,v22,0,v22e);
      gr4->SetMarkerStyle(25);
      gr4->SetMarkerSize(1.);
      gr4->SetMarkerColor(6);
      gr4->SetLineWidth(2);
      gr4->SetLineColor(6);
  gr4->Draw("psameez");

  TGraphErrors *gr5 = new TGraphErrors(NCentBin,pta3,v23,0,v23e);
      gr5->SetMarkerStyle(28);
      gr5->SetMarkerSize(1);
      gr5->SetMarkerColor(8);
      gr5->SetLineWidth(2);
      gr5->SetLineColor(8);
  gr5->Draw("psameez");

    TLegend *leg = new TLegend(0.19,0.65,0.38,0.93);
    leg->SetFillColor(10);
    leg->SetBorderSize(0);
    leg->SetTextFont(42);
    leg->SetTextColor(1);
    leg->SetTextSize(0.04);
    //leg->SetLineStyle(0.06);
    leg->AddEntry(grreal,"Published v_{3}","pl");
    leg->AddEntry(gr2,"|#Delta#eta|>0.0","p");
    leg->AddEntry(gr3,"|#Delta#eta|>1.0","p");
    leg->AddEntry(gr4,"|#Delta#eta|>1.5","p");
    leg->AddEntry(gr5,"|#Delta#eta|>2.0","p");
    leg->Draw();
  
    TLatex *tex1= new TLatex(3,0.305,"Real Data, 30-35%");
    tex1->SetTextColor(1);
    tex1->SetTextSize(0.05);
    tex1->SetTextFont(42);
    tex1->Draw();

    TLatex *tex2= new TLatex(3,0.265,"90>N>=35,  |#eta| < 2.4");
    tex2->SetTextColor(1);
    tex2->SetTextSize(0.05);
    tex2->SetTextFont(42);
    //tex2->Draw();


  c1->Print("eventplanev3.png");

}

