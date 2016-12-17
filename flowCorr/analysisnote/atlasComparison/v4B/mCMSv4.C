void mCMSv4(){

const int nCent=11;
double npart[nCent]={381, 329, 283, 240, 204, 171, 143, 118, 86.2, 53.5, 30.5};
double cent[nCent], v44[nCent], v44Stat[nCent], v44Sys[nCent];
double cent2[nCent], v42[nCent], v42Stat[nCent], v42Sys[nCent];
double v42Overv44[nCent], v42Overv44Stat[nCent], v42Overv44Sys[nCent];
double cent3[nCent], nv44[nCent], nv44Stat[nCent], nv44Sys[nCent];
double cent4[nCent], nv42[nCent], nv42Stat[nCent], nv42Sys[nCent];
double nv42Overv44[nCent], nv42Overv44Stat[nCent], nv42Overv44Sys[nCent];
ifstream inFileV44;
inFileV44.open("v44.txt");
for(int i=0; i<nCent; i++){
inFileV44>>cent[i]; inFileV44>>v44[i]; inFileV44>>v44Stat[i]; inFileV44>>v44Sys[i];
}
ifstream inFileV42;
inFileV42.open("v42.txt");
for(int i=0; i<nCent; i++){
inFileV42>>cent[i]; inFileV42>>v42[i]; inFileV42>>v42Stat[i]; inFileV42>>v42Sys[i];
v42Overv44[i]=v42[i]/v44[i];
v42Overv44Sys[i]=v42Overv44[i]*(sqrt(v44Stat[i]*v44Stat[i]/v44[i]/v44[i] + v42Stat[i]*v42Stat[i]/v42[i]/v42[i]));
}
ifstream inFileV44n;
inFileV44n.open("newCMSv44.txt");
for(int i=0; i<nCent; i++){
inFileV44n>>cent3[i]; inFileV44n>>nv44[i]; inFileV44n>>nv44Stat[i]; 
}
ifstream inFileV42n;
inFileV42n.open("newCMSv42.txt");
for(int i=0; i<nCent; i++){
inFileV42n>>cent4[i]; inFileV42n>>nv42[i]; inFileV42n>>nv42Stat[i]; 
nv42Overv44[i]=nv42[i]/nv44[i];
nv42Overv44Sys[i]=nv42Overv44[i]*(sqrt(nv44Stat[i]*nv44Stat[i]/nv44[i]/nv44[i] + nv42Stat[i]*nv42Stat[i]/nv42[i]/nv42[i]));
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
 hist->SetYTitle("v_{4}{#Psi_{2}}/v_{4}{#Psi_{4}}");
 hist->SetMinimum(0);
 hist->SetMaximum(1.1);
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
  // Plot: p8724_d1x1y2
  double p8724_d1x1y1_xval[] = { 400.6, 392.6, 383.2, 372.6, 361.8, 330.3, 281.9, 239.5, 202.6, 
    170.2, 141.7, 116.8, 95.0, 76.1, 59.9, 46.1, 34.7, 25.4, 18.0 };
  double p8724_d1x1y1_xerrminus[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
  double p8724_d1x1y1_xerrplus[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
  double p8724_d1x1y1_yval[] = { 0.0548, 0.1061, 0.1581, 0.1953, 0.2262, 0.3065, 0.4104, 0.5076, 0.5944, 
    0.6658, 0.7223, 0.7683, 0.7984, 0.8244, 0.83, 0.8366, 0.8152, 0.8219, 0.7815 };
  double p8724_d1x1y1_yerrminus[] = { 0.0046842020665210414, 0.005214933364866708, 0.006341925417410709, 0.007340134671789067, 0.00823579079384609, 0.010607411466045803, 0.01404135210156059, 0.017290765194172292, 0.020202871182086964, 
    0.022606949462499356, 0.024523916673321166, 0.026146240571064894, 0.027468033438890378, 0.029077404646907536, 0.030637572749811628, 0.033573802718786565, 0.038316739161885896, 0.052662173331528964, 0.08808951129391057 };
  double p8724_d1x1y1_yerrplus[] = { 0.0046842020665210414, 0.005214933364866708, 0.006341925417410709, 0.007340134671789067, 0.00823579079384609, 0.010607411466045803, 0.01404135210156059, 0.017290765194172292, 0.020202871182086964, 
    0.022606949462499356, 0.024523916673321166, 0.026146240571064894, 0.027468033438890378, 0.029077404646907536, 0.030637572749811628, 0.033573802718786565, 0.038316739161885896, 0.052662173331528964, 0.08808951129391057 };
  double p8724_d1x1y1_ystatminus[] = { 0.002718, 0.002417, 0.002203, 0.002091, 0.002009, 8.901E-4, 9.378E-4, 0.001031, 0.001152, 
    0.001292, 0.001467, 0.001714, 0.002069, 0.002719, 0.003808, 0.006127, 0.0105, 0.02153, 0.04378 };
  double p8724_d1x1y1_ystatplus[] = { 0.002718, 0.002417, 0.002203, 0.002091, 0.002009, 8.901E-4, 9.378E-4, 0.001031, 0.001152, 
    0.001292, 0.001467, 0.001714, 0.002069, 0.002719, 0.003808, 0.006127, 0.0105, 0.02153, 0.04378 };
  int p8724_d1x1y1_numpoints = 19;
TGraphAsymmErrors *p8724_d1x1y1 = new TGraphAsymmErrors(p8724_d1x1y1_numpoints, p8724_d1x1y1_xval, p8724_d1x1y1_yval, p8724_d1x1y1_xerrminus, p8724_d1x1y1_xerrplus, p8724_d1x1y1_yerrminus, p8724_d1x1y1_yerrplus);
  //p8724_d1x1y1->SetName("/HepData/8724/d1x1y1");
  //p8724_d1x1y1->SetTitle("/HepData/8724/d1x1y1");
  p8724_d1x1y1->SetFillColor(kRed-9);
  p8724_d1x1y1->Draw("P3same");
graph_v42Ov44->Draw("pesame");
graph_v42Ov44n->Draw("pesame");

    TLegend *leg0 = new TLegend(0.2,0.16,0.4,0.355);
    leg0->SetFillColor(10);
    leg0->SetBorderSize(0.035);
    leg0->SetTextFont(42);
    leg0->SetTextSize(0.046);
    leg0->AddEntry(p8724_d1x1y1,"ATLAS #LTcos4(#Psi_{2}-#Psi_{4})#GT_{w} SP","f");
    leg0->AddEntry(graph_v42Ov44,"CMS v_{4}{#Psi_{2}}/v_{4}{#Psi_{4}}, 11-005","pl");
    leg0->AddEntry(graph_v42Ov44n,"New CMS v_{4}{#Psi_{2}}/v_{4}{#Psi_{4}}, 2.76 TeV","pl");
    leg0->Draw();
    TLatex *tex1= new TLatex(40.5,10e-3,"Comparison");
    tex1->SetTextColor(1);
    tex1->SetTextSize(0.05);
    tex1->SetTextFont(42);
    //tex1->Draw();

c1->SaveAs("plot_v4.png");

}





