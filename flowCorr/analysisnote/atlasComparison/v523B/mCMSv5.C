void mCMSv5(){

const int nCent=11;
double npart[nCent]={381, 329, 283, 240, 204, 171, 143, 118, 86.2, 53.5, 30.5};
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
inFileV44n.open("newCMSv55.txt");
for(int i=0; i<nCent; i++){
inFileV44n>>cent3[i]; inFileV44n>>nv44[i]; inFileV44n>>nv44Stat[i]; 
}
ifstream inFileV42n;
inFileV42n.open("newCMSv523.txt");
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
 hist->SetYTitle("v_{5}{#Psi_{23}}/v_{5}{#Psi_{5}}");
 hist->SetMinimum(0);
 hist->SetMaximum(1.2);
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
  // Plot: p8724_d17x1y2
  double p8724_d17x1y1_xval[] = { 400.6, 392.6, 383.2, 372.6, 361.8, 330.3, 281.9, 239.5, 202.6, 
    170.2, 141.7, 116.8, 95.0, 76.1, 59.9 };
  double p8724_d17x1y1_xerrminus[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
  double p8724_d17x1y1_xerrplus[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
  double p8724_d17x1y1_yval[] = { 0.2017, 0.2625, 0.3147, 0.3772, 0.425, 0.5601, 0.6918, 0.7679, 0.8126, 
    0.835, 0.8553, 0.8412, 0.8539, 0.8802, 0.7278 };
  double p8724_d17x1y1_yerrminus[] = { 0.023482809542301364, 0.029815615036420096, 0.034164759987449056, 0.039867220883828866, 0.04428437421935643, 0.05755706004479381, 0.07080783823843233, 0.07997933805677564, 0.08377625415951706, 
    0.08548919955760494, 0.08882806369610902, 0.08725226071569721, 0.10288193476019004, 0.09603769468286918, 0.18713500180351084 };
  double p8724_d17x1y1_yerrplus[] = { 0.023482809542301364, 0.029815615036420096, 0.034164759987449056, 0.039867220883828866, 0.04428437421935643, 0.05755706004479381, 0.07080783823843233, 0.07997933805677564, 0.08377625415951706, 
    0.08548919955760494, 0.08882806369610902, 0.08725226071569721, 0.10288193476019004, 0.09603769468286918, 0.18713500180351084 };
  double p8724_d17x1y1_ystatminus[] = { 0.005662, 0.00578, 0.005965, 0.006401, 0.00673, 0.003669, 0.004416, 0.005046, 0.005731, 
    0.006779, 0.0084, 0.01089, 0.01555, 0.02782, 0.04183 };
  double p8724_d17x1y1_ystatplus[] = { 0.005662, 0.00578, 0.005965, 0.006401, 0.00673, 0.003669, 0.004416, 0.005046, 0.005731, 
    0.006779, 0.0084, 0.01089, 0.01555, 0.02782, 0.04183 };
  int p8724_d17x1y1_numpoints = 15;
TGraphAsymmErrors *p8724_d17x1y1 = new TGraphAsymmErrors(p8724_d17x1y1_numpoints, p8724_d17x1y1_xval, p8724_d17x1y1_yval, p8724_d17x1y1_xerrminus, p8724_d17x1y1_xerrplus, p8724_d17x1y1_yerrminus, p8724_d17x1y1_yerrplus);
  //p8724_d17x1y1.SetName("/HepData/8724/d17x1y1");
  //p8724_d17x1y1.SetTitle("/HepData/8724/d17x1y1");
  p8724_d17x1y1->SetFillColor(kRed-9);
  p8724_d17x1y1->Draw("P3same");
//graph_v42Ov44->Draw("pesame");
graph_v42Ov44n->Draw("pesame");

    TLegend *leg0 = new TLegend(0.2,0.16,0.4,0.355);
    leg0->SetFillColor(10);
    leg0->SetBorderSize(0.035);
    leg0->SetTextFont(42);
    leg0->SetTextSize(0.046);
    leg0->AddEntry(p8724_d17x1y1,"ATLAS #LTcos(2#Psi_{2}+3#Psi_{3}-5#Psi_{5})#GT_{w} SP","f");
    //leg0->AddEntry(graph_v42Ov44,"CMS v_{6}{#Psi_{2}}/v_{6}{#Psi_{6}}, 11-005","pl");
    leg0->AddEntry(graph_v42Ov44n,"New CMS v_{5}{#Psi_{23}}/v_{5}{#Psi_{5}}, 2.76 TeV","pl");
    leg0->Draw();
    TLatex *tex1= new TLatex(40.5,10e-3,"Comparison");
    tex1->SetTextColor(1);
    tex1->SetTextSize(0.05);
    tex1->SetTextFont(42);
    //tex1->Draw();

c1->SaveAs("plot_v5.png");
}





