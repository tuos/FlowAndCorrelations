void mCMSv6(){

const int nCent=8;
double npart[nCent]={381, 329, 283, 240, 204, 171, 143, 118};
double cent[nCent], v44[nCent], v44Stat[nCent], v44Sys[nCent];
double cent2[nCent], v42[nCent], v42Stat[nCent], v42Sys[nCent];
double v42Overv44[nCent], v42Overv44Stat[nCent], v42Overv44Sys[nCent];
double cent3[nCent], nv44[nCent], nv44Stat[nCent], nv44Sys[nCent];
double cent4[nCent], nv42[nCent], nv42Stat[nCent], nv42Sys[nCent];
double nv42Overv44[nCent], nv42Overv44Stat[nCent], nv42Overv44Sys[nCent];
ifstream inFileV44;
inFileV44.open("v66.txt");
for(int i=0; i<nCent; i++){
inFileV44>>cent[i]; inFileV44>>v44[i]; inFileV44>>v44Stat[i]; inFileV44>>v44Sys[i];
}
ifstream inFileV42;
inFileV42.open("v62.txt");
for(int i=0; i<nCent; i++){
inFileV42>>cent[i]; inFileV42>>v42[i]; inFileV42>>v42Stat[i]; inFileV42>>v42Sys[i];
v42Overv44[i]=v42[i]/v44[i];
v42Overv44Sys[i]=v42Overv44[i]*(sqrt(v44Stat[i]*v44Stat[i]/v44[i]/v44[i] + v42Stat[i]*v42Stat[i]/v42[i]/v42[i]));
}
ifstream inFileV44n;
inFileV44n.open("newCMSv66.txt");
for(int i=0; i<nCent; i++){
inFileV44n>>cent3[i]; inFileV44n>>nv44[i]; inFileV44n>>nv44Stat[i]; 
}
ifstream inFileV42n;
inFileV42n.open("newCMSv62.txt");
for(int i=0; i<nCent; i++){
inFileV42n>>cent4[i]; inFileV42n>>nv42[i]; inFileV42n>>nv42Stat[i]; 
nv42Overv44[i]=nv42[i]/nv44[i];
nv42Overv44Sys[i]=nv42Overv44[i]*(sqrt(nv44Stat[i]*nv44Stat[i]/nv44[i]/nv44[i] + nv42Stat[i]*nv42Stat[i]/nv42[i]/nv42[i]));
nv42Overv44[1]=0.19;
nv42Overv44[3]=0.31;
nv42Overv44[4]=0.35;
nv42Overv44Sys[4]=0.06;

}

  TCanvas *c1 = new TCanvas("c1","c1",1,1,500,500);
  c1->SetFillColor(10);
  c1->SetFrameFillColor(0);
  c1->SetFrameBorderSize(0);
  c1->SetFrameBorderMode(0);
  c1->SetLeftMargin(0.15);
  c1->SetBottomMargin(0.15);
  c1->SetTopMargin(0.02);
  c1->SetRightMargin(0.02);
  //c1->Divide(5,1,0,0);
  gStyle->SetOptStat(0);
  c1->SetTicks(-1);
c1->cd();
 TH1D* hist = new TH1D("hist","",100,0.,430);
 hist->SetXTitle("N_{part}");
 hist->SetYTitle("v_{6}{#Psi_{2}}/v_{6}{#Psi_{6}}");
 hist->SetMinimum(0);
 hist->SetMaximum(1.);
 hist->GetXaxis()->CenterTitle(1);
 hist->GetYaxis()->CenterTitle(1);
 hist->GetYaxis()->SetTitleOffset(1.1);
 hist->GetXaxis()->SetTitleOffset(1.1);
 hist->GetXaxis()->SetTitleSize(0.055);
 hist->GetYaxis()->SetTitleSize(0.055);
 hist->GetXaxis()->SetLabelSize(0.046);
 hist->GetYaxis()->SetLabelSize(0.046);
 hist->GetXaxis()->SetLabelOffset(0.01);
 hist->GetYaxis()->SetLabelOffset(0.01);
 hist->Draw();

TGraphErrors *graph_v42Ov44 = new TGraphErrors(nCent,npart,v42Overv44,0,v42Overv44Sys);
graph_v42Ov44->SetTitle("");
graph_v42Ov44->SetMarkerSize(1.5);
graph_v42Ov44->SetMarkerColor(1);
graph_v42Ov44->SetMarkerStyle(20);
graph_v42Ov44->SetLineWidth(2);
graph_v42Ov44->SetLineStyle(1);
graph_v42Ov44->SetLineColor(1);
graph_v42Ov44->SetFillColor(1);
//graph_v42Ov44->Draw("pe");
TGraphErrors *graph_v42Ov44n = new TGraphErrors(nCent,npart,nv42Overv44,0,nv42Overv44Sys);
graph_v42Ov44n->SetTitle("");
graph_v42Ov44n->SetMarkerSize(1.5);
graph_v42Ov44n->SetMarkerColor(4);
graph_v42Ov44n->SetMarkerStyle(25);
graph_v42Ov44n->SetLineWidth(2);
graph_v42Ov44n->SetLineStyle(1);
graph_v42Ov44n->SetLineColor(4);
graph_v42Ov44n->SetFillColor(4);
//graph_v42Ov44n->Draw("pe");

//ATLAS
  // Plot: p8724_d9x1y2
  double p8724_d9x1y1_xval[] = { 400.6, 392.6, 383.2, 372.6, 361.8, 330.3, 281.9, 239.5, 202.6, 
    170.2, 141.7, 116.8, 95.0, 76.1, 59.9, 46.1, 34.7 };
  double p8724_d9x1y1_xerrminus[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
  double p8724_d9x1y1_xerrplus[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
  double p8724_d9x1y1_yval[] = { 0.04096, 0.03506, 0.05054, 0.0973, 0.09374, 0.1433, 0.2156, 0.2882, 0.3556, 
    0.4165, 0.4754, 0.4787, 0.5486, 0.5363, 0.5496, 0.4604, 0.4149 };
  double p8724_d9x1y1_yerrminus[] = { 0.028249665484745126, 0.024073907036457544, 0.02278301999296845, 0.022581277643215852, 0.021460684984408118, 0.01877975090356632, 0.023862148184939258, 0.030309318435095173, 0.03667759828560207, 
    0.042853671954687846, 0.04949638067576255, 0.050542834309128336, 0.06263768274768791, 0.06919028978115355, 0.09634886610645711, 0.09998733969858384, 0.17298856869747203 };
  double p8724_d9x1y1_yerrplus[] = { 0.028249665484745126, 0.024073907036457544, 0.02278301999296845, 0.022581277643215852, 0.021460684984408118, 0.01877975090356632, 0.023862148184939258, 0.030309318435095173, 0.03667759828560207, 
    0.042853671954687846, 0.04949638067576255, 0.050542834309128336, 0.06263768274768791, 0.06919028978115355, 0.09634886610645711, 0.09998733969858384, 0.17298856869747203 };
  double p8724_d9x1y1_ystatminus[] = { 0.02044, 0.01733, 0.01614, 0.0151, 0.01411, 0.005712, 0.005746, 0.006872, 0.008454, 
    0.01084, 0.01471, 0.0161, 0.02832, 0.03909, 0.07152, 0.07525, 0.1426 };
  double p8724_d9x1y1_ystatplus[] = { 0.02044, 0.01733, 0.01614, 0.0151, 0.01411, 0.005712, 0.005746, 0.006872, 0.008454, 
    0.01084, 0.01471, 0.0161, 0.02832, 0.03909, 0.07152, 0.07525, 0.1426 };
  int p8724_d9x1y1_numpoints = 17;
TGraphAsymmErrors *p8724_d9x1y1 = new TGraphAsymmErrors(p8724_d9x1y1_numpoints, p8724_d9x1y1_xval, p8724_d9x1y1_yval, p8724_d9x1y1_xerrminus, p8724_d9x1y1_xerrplus, p8724_d9x1y1_yerrminus, p8724_d9x1y1_yerrplus);
  //p8724_d9x1y1.SetName("/HepData/8724/d9x1y1");
  //p8724_d9x1y1.SetTitle("/HepData/8724/d9x1y1");
  p8724_d9x1y1->SetFillColor(kRed-9);
  p8724_d9x1y1->Draw("P3same");
graph_v42Ov44->Draw("pesame");
graph_v42Ov44n->Draw("pesame");

    TLegend *leg0 = new TLegend(0.2,0.16,0.4,0.355);
    leg0->SetFillColor(10);
    leg0->SetBorderSize(0.035);
    leg0->SetTextFont(42);
    leg0->SetTextSize(0.046);
    leg0->AddEntry(p8724_d9x1y1,"ATLAS #LTcos6(#Psi_{2}-#Psi_{6})#GT_{w} SP","f");
    leg0->AddEntry(graph_v42Ov44,"CMS v_{6}{#Psi_{2}}/v_{6}{#Psi_{6}}, 11-005","pl");
    leg0->AddEntry(graph_v42Ov44n,"New CMS v_{6}{#Psi_{2}}/v_{6}{#Psi_{6}}, 5.02 TeV","pl");
    leg0->Draw();
    TLatex *tex1= new TLatex(40.5,10e-3,"Comparison");
    tex1->SetTextColor(1);
    tex1->SetTextSize(0.05);
    tex1->SetTextFont(42);
    //tex1->Draw();

c1->SaveAs("plot_v6.png");
}





