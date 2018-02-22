void vnpt_5panels_ratio()
{
  gROOT->Reset();
  gROOT->SetStyle("MyStyle");
//  gROOT->LoadMacro("v2pt_12cen_MyDef.C");
  // gROOT->LoadMacro("MyDef.C");
  gStyle->SetTextFont(43);
  gStyle->SetLabelFont(43,"x");
  gStyle->SetLabelFont(43,"y");
  gStyle->SetLabelFont(43,"z");
  gStyle->SetTitleFont(43,"x");
  gStyle->SetTitleFont(43,"y");
  gStyle->SetTitleFont(43,"z");
  gStyle->SetEndErrorSize(0);

  double textsize = 19;

//int   mcol[8]={kRed,kMagenta,kBlue,kCyan,kGreen,kYellow,kOrange,kGray};
int   mcol[8]={kRed,kOrange+1,kBlue,kGreen+1,kCyan,kYellow,kOrange,kGray};
int   mcol2[4]={6,2,4,8};

//int   msty[8][2]={{20,20},{25,24},{22,22},{28,26},{29,30},{33,27},{34,28},{20,24}};
int   msty[8][2]={{20,20},{21,24},{22,29},{23,30},{24,30},{25,27},{28,28},{30,24}};


//float msiz[8]={1.11,0.9,1.2,1.24,1.5,1,1,1};
float msiz[8]={1.11,1.0,1.5,1.2,1.2,1.2,1.2,1.6};
float msiz2[4]={1.5,1.5,1.5,1.5};
//
// arrays
//
const int Mfiles=50;
int   ndp[Mfiles];
char *cfn[Mfiles];
char *cft[Mfiles];
const int Mpoints=40;
double xa[Mfiles][Mpoints],xe[Mfiles][Mpoints],xesys[Mfiles][Mpoints];
double ya[Mfiles][Mpoints],ye[Mfiles][Mpoints],yesys[Mfiles][Mpoints];  

double nAxa[Mfiles][Mpoints],nAxe[Mfiles][Mpoints];
double nAya[Mfiles][Mpoints],nAye[Mfiles][Mpoints];
double nBxa[Mfiles][Mpoints],nBxe[Mfiles][Mpoints];
double nBya[Mfiles][Mpoints],nBye[Mfiles][Mpoints];
double nARxa[Mfiles][Mpoints],nARxe[Mfiles][Mpoints];
double nARya[Mfiles][Mpoints],nARye[Mfiles][Mpoints];
double nBRxa[Mfiles][Mpoints],nBRxe[Mfiles][Mpoints];
double nBRya[Mfiles][Mpoints],nBRye[Mfiles][Mpoints];

double xa60[Mfiles][Mpoints],xe60[Mfiles][Mpoints],xesys60[Mfiles][Mpoints];
double ya60[Mfiles][Mpoints],ye60[Mfiles][Mpoints],yesys60[Mfiles][Mpoints];
double nAxa60[Mfiles][Mpoints],nAxe60[Mfiles][Mpoints];
double nAya60[Mfiles][Mpoints],nAye60[Mfiles][Mpoints];
double nBxa60[Mfiles][Mpoints],nBxe60[Mfiles][Mpoints];
double nBya60[Mfiles][Mpoints],nBye60[Mfiles][Mpoints];
double nARxa60[Mfiles][Mpoints],nARxe60[Mfiles][Mpoints];
double nARya60[Mfiles][Mpoints],nARye60[Mfiles][Mpoints];
double nBRxa60[Mfiles][Mpoints],nBRxe60[Mfiles][Mpoints];
double nBRya60[Mfiles][Mpoints],nBRye60[Mfiles][Mpoints];

const int Mpads=14;


char  *htit[Mpads];
char  *htitc2[Mpads];
char  *atit[Mpads][3];
double ptit[Mpads][2];
double hxmin[Mpads],hxmax[Mpads];
double hymin[Mpads],hymax[Mpads];
double lxmin[Mpads],lxmax[Mpads];
double lymin[Mpads],lymax[Mpads];


 
  //
  // Data input
  //
  char *cjob="v2pt_12cen_4x3";
  int i=-1;


  // histogram parameter
  htit[0]="(a) v_{4}{#Psi_{22}}";
  htit[1]="(b) v_{5}{#Psi_{23}}";
  htit[2]="(c) v_{6}{#Psi_{222}}";
  htit[3]="(d) v_{6}{#Psi_{33}}";
  htit[4]="(e) v_{7}{#Psi_{223}}";
  htit[5]="25-30%";
  htit[6]="30-35%";
  htit[7]="35-40%";
  htit[8]="40-50%";
  htit[9]="50-60%";
  htit[10]="60-70%";
  htit[11]="70-80%";
  htitc2[0]="(f) v_{4}{#Psi_{22}}";
  htitc2[1]="(g) v_{5}{#Psi_{23}}";
  htitc2[2]="(h) v_{6}{#Psi_{222}}";
  htitc2[3]="(i) v_{6}{#Psi_{33}}";
  htitc2[4]="(j) v_{7}{#Psi_{223}}";
  for (int ip=0;ip<Mpads;ip++)
  {
    //  hxmin[ip]=0.0; hxmax[ip]=11.9;
    hxmin[ip]=0.0001; hxmax[ip]=4.1;
    hymin[ip]=-0.003; hymax[ip]=0.0655;
    lxmin[ip]=0.24; lxmax[ip]=0.88;
    lymin[ip]=0.65; lymax[ip]=0.94;
    ptit[ip][0]=0.45; ptit[ip][1]=0.036;// position legends 
    atit[ip][0]="p_{T} (GeV/c)"; atit[ip][1]="v_{n}";
  }
  //
  // Read data and create vector files
  //

  double sysXYZ[5]={6,7,8,8,9};
  //double sysXYZ[5]={8,9,12,12,15};
  //double sysXYZ[5]={8,9,20,20,20};
  double sysEach[5]={0.0002, 0.0002, 0.0002, 0.0003, 0.0002};
  double tmp;
  const int nw=5;
  const int npt=20;
  ifstream inEP;
  inEP.open("./data_vnptcent020_5020gev.txt");
  for(int i=0; i<nw; i++){
    for(int j=0; j<npt; j++){
      inEP>>tmp; inEP>>tmp; inEP>>xa[i][j]; inEP>>tmp; inEP>>ya[i][j]; inEP>>ye[i][j];
      if(ye[i][j]<0) ye[i][j]=-ye[i][j];
      xe[i][j]=0.0;
    }
  }
  inEP.close();
  ifstream inEP;
  inEP.open("./data_vnptcent020_5020gev_vzA.txt");
  for(int i=0; i<nw; i++){
    for(int j=0; j<npt; j++){
      inEP>>tmp; inEP>>tmp; inEP>>nAxa[i][j]; inEP>>tmp; inEP>>nAya[i][j]; inEP>>nAye[i][j];
      if(nAye[i][j]<0) nAye[i][j]=-nAye[i][j];
      nAxe[i][j]=0.0; 

      nARxa[i][j]=nAxa[i][j];
      nARxe[i][j]=nAxe[i][j];
      nARye[i][j]=nAya[i][j]/ya[i][j]*sqrt(ye[i][j]*ye[i][j]/ya[i][j]/ya[i][j] + nAye[i][j]*nAye[i][j]/nAya[i][j]/nAya[i][j] - 2.5*ye[i][j]*ye[i][j]/ya[i][j]/nAya[i][j] );
      nARya[i][j]=nAya[i][j]/ya[i][j];
    }
  }
  inEP.close();
  ifstream inEP;
  inEP.open("./data_vnptcent020_5020gev_vzB.txt");
  for(int i=0; i<nw; i++){
    for(int j=0; j<npt; j++){
      inEP>>tmp; inEP>>tmp; inEP>>nBxa[i][j]; inEP>>tmp; inEP>>nBya[i][j]; inEP>>nBye[i][j];
      if(nBye[i][j]<0) nBye[i][j]=-nBye[i][j];
      nBxe[i][j]=0.0; 

      nBRxa[i][j]=nBxa[i][j];
      nBRxe[i][j]=nBxe[i][j];
      nBRye[i][j]=nBya[i][j]/ya[i][j]*sqrt(ye[i][j]*ye[i][j]/ya[i][j]/ya[i][j] + nBye[i][j]*nBye[i][j]/nBya[i][j]/nBya[i][j] - 2.5*ye[i][j]*ye[i][j]/ya[i][j]/nBya[i][j] );
      nBRya[i][j]=nBya[i][j]/ya[i][j];
    }
  }
  inEP.close();

//20-60%
  ifstream inEP;
  inEP.open("./data_vnptcent2060_5020gev.txt");
  for(int i=0; i<nw; i++){
    for(int j=0; j<npt; j++){
      inEP>>tmp; inEP>>tmp; inEP>>xa60[i][j]; inEP>>tmp; inEP>>ya60[i][j]; inEP>>ye60[i][j];
      if(ye60[i][j]<0) ye60[i][j]=-ye60[i][j];
      xe60[i][j]=0.0;
    }
  }
  inEP.close();
  ifstream inEP;
  inEP.open("./data_vnptcent2060_5020gev_vzA.txt");
  for(int i=0; i<nw; i++){
    for(int j=0; j<npt; j++){
      inEP>>tmp; inEP>>tmp; inEP>>nAxa60[i][j]; inEP>>tmp; inEP>>nAya60[i][j]; inEP>>nAye60[i][j];
      if(nAye60[i][j]<0) nAye60[i][j]=-nAye60[i][j];
      nAxe60[i][j]=0.0; 

      nARxa60[i][j]=nAxa60[i][j];
      nARxe60[i][j]=nAxe60[i][j];
      nARye60[i][j]=nAya60[i][j]/ya60[i][j]*sqrt(ye60[i][j]*ye60[i][j]/ya60[i][j]/ya60[i][j] + nAye60[i][j]*nAye60[i][j]/nAya60[i][j]/nAya60[i][j] - 2.5*ye60[i][j]*ye60[i][j]/ya60[i][j]/nAya60[i][j] );
      nARya60[i][j]=nAya60[i][j]/ya60[i][j];
    }
  }
  inEP.close();
  ifstream inEP;
  inEP.open("./data_vnptcent2060_5020gev_vzB.txt");
  for(int i=0; i<nw; i++){
    for(int j=0; j<npt; j++){
      inEP>>tmp; inEP>>tmp; inEP>>nBxa60[i][j]; inEP>>tmp; inEP>>nBya60[i][j]; inEP>>nBye60[i][j];
      if(nBye60[i][j]<0) nBye60[i][j]=-nBye60[i][j];
      nBxe60[i][j]=0.0; 

      nBRxa60[i][j]=nBxa60[i][j];
      nBRxe60[i][j]=nBxe60[i][j];
      nBRye60[i][j]=nBya60[i][j]/ya60[i][j]*sqrt(ye60[i][j]*ye60[i][j]/ya60[i][j]/ya60[i][j] + nBye60[i][j]*nBye60[i][j]/nBya60[i][j]/nBya60[i][j] - 2.5*ye60[i][j]*ye60[i][j]/ya60[i][j]/nBya60[i][j] );
      nBRya60[i][j]=nBya60[i][j]/ya60[i][j];
    }
  }
  inEP.close();
nBRya60[1][2]=1.06;

  TCanvas *can=new TCanvas("can","can",10,10,1050*0.8*1.3,800*0.3*1.3*1.8);

  can->Divide(5,2,0,0); //sticks the pads with no space inbetween 
  
  TH1D *h1[nw];
  for (int iw=0;iw<nw;iw++)
  {
    can->cd(iw+1);
    if(iw==4) gPad->SetRightMargin(0.02);
    //gPad->SetLogy();
    char ch1[8];
    sprintf(ch1,"h1_%d",iw);
    h1[iw] = new TH1D(ch1,"",500,hxmin[iw],hxmax[iw]);
    h1[iw]->SetMinimum(0.5); h1[iw]->SetMaximum(1.5);
    h1[iw]->SetXTitle(atit[iw][0]); h1[iw]->SetYTitle("v_{n} ratio");
    h1[iw]->GetXaxis()->CenterTitle(1);
    h1[iw]->GetYaxis()->CenterTitle(1);

    // futz with the axes
    h1[iw]->GetYaxis()->SetNdivisions(606);
    h1[iw]->GetXaxis()->SetNdivisions(606);

      h1[iw]->GetYaxis()->SetTitleSize(textsize*1.4);
      h1[iw]->GetYaxis()->SetTitleOffset(2.3);
      h1[iw]->GetYaxis()->SetLabelSize(textsize);
      h1[iw]->GetXaxis()->SetTitleSize(textsize*1.4);
      h1[iw]->GetXaxis()->SetTitleOffset(1.3);
      h1[iw]->GetXaxis()->SetLabelSize(textsize);
     // h1[iw]->GetXaxis()->SetLabelOffset(1.2);

    h1[iw]->Draw();
  }
  TH1D *h2[nw];
  for (int iw=0;iw<nw;iw++)
  {
    can->cd(iw+1+5);

    if(iw==4) gPad->SetRightMargin(0.02);
    //gPad->SetLogy();
    char ch2[8];
    sprintf(ch2,"h2_%d",iw);
    h2[iw] = new TH1D(ch2,"",500,hxmin[iw],hxmax[iw]);
    h2[iw]->SetMinimum(0.5); h2[iw]->SetMaximum(1.5);
    h2[iw]->SetXTitle(atit[iw][0]); h2[iw]->SetYTitle("v_{n} ratio");
    h2[iw]->GetXaxis()->CenterTitle(1);
    h2[iw]->GetYaxis()->CenterTitle(1);

    // futz with the axes
    h2[iw]->GetYaxis()->SetNdivisions(606);
    h2[iw]->GetXaxis()->SetNdivisions(606);

      h2[iw]->GetYaxis()->SetTitleSize(textsize*1.4);
      h2[iw]->GetYaxis()->SetTitleOffset(2.3);
      h2[iw]->GetYaxis()->SetLabelSize(textsize*1.2);
      h2[iw]->GetXaxis()->SetTitleSize(textsize*1.4);
      h2[iw]->GetXaxis()->SetTitleOffset(1.9);
      h2[iw]->GetXaxis()->SetLabelSize(textsize*1.2);
     // h2[iw]->GetXaxis()->SetLabelOffset(1.2);

    h2[iw]->Draw();
  }

  //
  // Draw! 
  //

  const int nPlotBin = 40;
  double ptPlot[nPlotBin];
  double vnPlot[nPlotBin];
  double errPlot[nPlotBin];

  cout << "Now Draw!" << endl;
  TGraphErrors *ge, *ge2, *ge3, *ge4;
  for (int iw=0;iw<nw;iw++)
  {
    can->cd(iw+1);

    //
    if (iw==0)
    {
      tex=new TLatex(0.6,0.0235*0.88*1.275*1.47*1.6,"CMS");
      tex->SetTextSize(textsize*1.0);
      //tex->Draw();
      tex=new TLatex(2.8,0.0235*0.88*1.275*1.47*1.6,"Preliminary");
      tex->SetTextSize(textsize*1.0);
      //tex->Draw();
    }
    if (iw==0)
    {
      tex=new TLatex(1.5,1.18,"0-20%");
      tex->SetTextSize(textsize*1.0);
      tex->Draw();
      tex=new TLatex(2.,0.021,"|#eta|<0.8");
      tex->SetTextSize(textsize*1.0);
      //tex->Draw();
      tex=new TLatex(0.5,0.02,"0.3<p_{T}<3.0 GeV/c");
      tex->SetTextSize(textsize*1.0);
      //tex->Draw();
    }
    //if (iw < 4) tex=new TLatex(ptit[iw][0]+2,0.27,htit[iw]);
    tex=new TLatex(2.1,1.4,htit[iw]);
    if ( iw == 0)   tex->SetTextSize(textsize);
    else if (iw == 8) tex->SetTextSize(textsize);
    else  tex->SetTextSize(textsize);
    tex->Draw();
    //
    // Legend
    //
    TLegend *leg = new TLegend(lxmin[iw]*1.2,lymin[iw]*1.*0.75*0.1,lxmax[iw]*0.8,lymax[iw]*1.02*0.4*0.92);
    leg->SetFillColor(0);
    leg->SetTextSize(textsize);
    TLegend *leg2 = new TLegend(lxmin[iw]*1.2,lymin[iw]*1.*0.75*0.52,lxmax[iw]*0.8,lymax[iw]*1.02*0.56*0.92);
    leg2->SetFillColor(0);
    leg2->SetTextSize(textsize);
    //
    // Read data
    //

    for (int im=0;im<1;im++)
    {
      int j=im*5+iw;
      int col=2;
      //if (ndp[j]==0) continue;

      ge=new TGraphErrors(19,&nARxa[j][0],&nARya[j][0],&nARxe[j][0],&nARye[j][0]);
      ge->SetTitle("");
      ge->SetMarkerStyle(24);
      //      ge->SetMarkerStyle(msty[im]);
      ge->SetMarkerSize(msiz[im]);
      ge->SetMarkerColor(col);
      ge->SetLineWidth(1.2);
      ge->SetLineColor(col);
      //ge->Draw("pe");
      leg->AddEntry(ge,"HF(3,4)/HF(3,5)","pl");
    }
    for (int im=0;im<1;im++)
    {
      int j=im*5+iw;
      int col=4;
      //if (ndp[j]==0) continue;
      ge2=new TGraphErrors(19,&nBRxa[j][0],&nBRya[j][0],&nBRxe[j][0],&nBRye[j][0]);
      ge2->SetTitle("");
      ge2->SetMarkerStyle(25);
      //      ge2->SetMarkerStyle(msty[im]);
      ge2->SetMarkerSize(msiz[im]);
      ge2->SetMarkerColor(col);
      ge2->SetLineWidth(1.2);
      ge2->SetLineColor(col);
      //ge2->Draw("pe");
      leg->AddEntry(ge2,"HF(4,5)/HF(3,5)","pl");
      //drawSysBox(ge2,16,0.2, sysXYZ[j]);
    }
    ge2->Draw("pe");
    ge->Draw("pe");
    if (iw==0) leg->Draw();
    TLine *lines = new TLine(0,1,4.0,1);
    lines->SetLineStyle(2);
    lines->SetLineWidth(1);
    lines->Draw();

if(iw==0||iw<6){
    TF1 *fitFun = new TF1("fitFun","pol1", 0, 4);
    fitFun->SetLineColor(2);
    ge->Fit("fitFun","R+");
    fitFun->Draw("same");
cout<<fitFun->Eval(0.4)<<",  "<<fitFun->Eval(0.9)<<",  "<<fitFun->Eval(1.9)<<",  "<<fitFun->Eval(3.5)<<endl;
    double p0 = fitFun->GetParameter(0);
    double p0Err = fitFun->GetParError(0);
    double p1 = fitFun->GetParameter(1);
    double p1Err = fitFun->GetParError(1);
    //double p2 = fitFun->GetParameter(2);
    //double p2Err = fitFun->GetParError(2);

  //TF1 *fitFunE = new TF1("fitFunE","[0]+[1]*x+[2]*x*x", 0, 4);
  TF1 *fitFunE = new TF1("fitFunE","[0]+[1]*x", 0, 4);
  //fitFunE->SetParameters(p0+p0Err, p1+p1Err, p2+p2Err);
  fitFunE->SetParameters(p0+p0Err, p1);
  for(int ipt=0; ipt<nPlotBin; ipt++){
    ptPlot[ipt] = ipt*0.1+0.05;
    vnPlot[ipt] = fitFun->Eval(ptPlot[ipt]);
    errPlot[ipt] = fitFunE->Eval(ptPlot[ipt]) - fitFun->Eval(ptPlot[ipt]);
  }

  TGraphErrors *graph = new TGraphErrors(nPlotBin,ptPlot,vnPlot,0,errPlot);
  graph->SetTitle("");
  graph->SetMarkerStyle(20);
  graph->SetMarkerSize(1.0);
  graph->SetMarkerColor(1);
  graph->SetLineWidth(2);
  graph->SetLineColor(2);
MyStyle->SetFillColor(kRed+1);
  graph->SetFillColor(kRed+1);
graph->SetFillStyle(3002);
  graph->Draw("e3same");

}
else {
    TF1 *fitFun = new TF1("fitFun","pol1", 0, 4);
    fitFun->SetLineColor(4);
    ge->Fit("fitFun","R+");
    fitFun->Draw("same");
cout<<fitFun->Eval(0.4)<<",  "<<fitFun->Eval(0.9)<<",  "<<fitFun->Eval(1.9)<<",  "<<fitFun->Eval(3.5)<<endl;

}

    double chi2 = fitFun->GetChisquare();
    double ndf = fitFun->GetNDF();
   TLatex *tex = new TLatex(0.6,0.53,Form("#chi^{2}/ndf = %2.1f", chi2/ndf));
   tex->SetTextColor(2);
   tex->SetTextSize(16);
   tex->Draw("same");


    can->cd(iw+1+5);
    tex=new TLatex(2.1,1.4,htitc2[iw]);
    if ( iw == 0)   tex->SetTextSize(textsize);
    else if (iw == 8) tex->SetTextSize(textsize);
    else  tex->SetTextSize(textsize);
    tex->Draw();

    for (int im=0;im<1;im++)
    {
      int j=im*5+iw;
      int col=2;
      //if (ndp[j]==0) continue;

      ge3=new TGraphErrors(19,&nARxa60[j][0],&nARya60[j][0],&nARxe60[j][0],&nARye60[j][0]);
      ge3->SetTitle("");
      ge3->SetMarkerStyle(24);
      //      ge3->SetMarkerStyle(msty[im]);
      ge3->SetMarkerSize(msiz[im]);
      ge3->SetMarkerColor(col);
      ge3->SetLineWidth(1.2);
      ge3->SetLineColor(col);
      //ge3->Draw("pe");
      leg2->AddEntry(ge3,"HF(3,4)/HF(3,5)","pl");
    }
    for (int im=0;im<1;im++)
    {
      int j=im*5+iw;
      int col=4;
      //if (ndp[j]==0) continue;
      ge4=new TGraphErrors(19,&nBRxa60[j][0],&nBRya60[j][0],&nBRxe60[j][0],&nBRye60[j][0]);
      ge4->SetTitle("");
      ge4->SetMarkerStyle(25);
      //      ge4->SetMarkerStyle(msty[im]);
      ge4->SetMarkerSize(msiz[im]);
      ge4->SetMarkerColor(col);
      ge4->SetLineWidth(1.2);
      ge4->SetLineColor(col);
      //ge4->Draw("pe");
      leg2->AddEntry(ge4,"HF(4,5)/HF(3,5)","pl");
    }
    ge4->Draw("pe");
    ge3->Draw("pe");
    TLine *lines = new TLine(0,1,4.0,1);
    lines->SetLineStyle(2);
    lines->SetLineWidth(1);
    lines->Draw();
    if(iw==0) leg2->Draw();

if(iw==0||iw<6){
    TF1 *fitFun = new TF1("fitFun","pol1", 0, 4);
    fitFun->SetLineColor(2);
    ge3->Fit("fitFun","R+");
    fitFun->Draw("same");
cout<<fitFun->Eval(2.5)<<",  "<<fitFun->Eval(7.5)<<",  "<<fitFun->Eval(45)<<",  "<<fitFun->Eval(55)<<endl;
    double p0 = fitFun->GetParameter(0);
    double p0Err = fitFun->GetParError(0);
    double p1 = fitFun->GetParameter(1);
    double p1Err = fitFun->GetParError(1);
    //double p2 = fitFun->GetParameter(2);
    //double p2Err = fitFun->GetParError(2);

  //TF1 *fitFunE = new TF1("fitFunE","[0]+[1]*x+[2]*x*x", 0, 4);
  TF1 *fitFunE = new TF1("fitFunE","[0]+[1]*x", 0, 4);
  //fitFunE->SetParameters(p0+p0Err, p1+p1Err, p2+p2Err);
  fitFunE->SetParameters(p0+p0Err, p1);
  for(int ipt=0; ipt<nPlotBin; ipt++){
    ptPlot[ipt] = ipt*0.1+0.05;
    vnPlot[ipt] = fitFun->Eval(ptPlot[ipt]);
    errPlot[ipt] = fitFunE->Eval(ptPlot[ipt]) - fitFun->Eval(ptPlot[ipt]);
  }

  TGraphErrors *graph = new TGraphErrors(nPlotBin,ptPlot,vnPlot,0,errPlot);
  graph->SetTitle("");
  graph->SetMarkerStyle(20);
  graph->SetMarkerSize(1.0);
  graph->SetMarkerColor(1);
  graph->SetLineWidth(2);
  graph->SetLineColor(2);
MyStyle->SetFillColor(kRed+1);
  graph->SetFillColor(kRed+1);
graph->SetFillStyle(3002);
  graph->Draw("e3same");
}
else {
    TF1 *fitFun = new TF1("fitFun","pol1", 0, 4);
    fitFun->SetLineColor(4);
    ge3->Fit("fitFun","R+");
    fitFun->Draw("same");
cout<<fitFun->Eval(2.5)<<",  "<<fitFun->Eval(7.5)<<",  "<<fitFun->Eval(45)<<",  "<<fitFun->Eval(55)<<endl;
}

    double chi2 = fitFun->GetChisquare();
    double ndf = fitFun->GetNDF();
   TLatex *tex = new TLatex(0.6,0.53,Form("#chi^{2}/ndf = %2.1f", chi2/ndf));
   tex->SetTextColor(2);
   tex->SetTextSize(16);
   tex->Draw("same");

     
      if(iw==0){
      can->cd(iw+5+1);
      TLatex *tex=new TLatex(1.5,1.18,"20-60%");
      tex->SetTextSize(textsize*1.0);
      tex->Draw();
      }

  }


   can->cd();
   TLatex *   tex = new TLatex(0.06,0.96,"CMS");
   tex->SetNDC();
   tex->SetTextFont(62);
   tex->SetTextSize(0.038);
   tex->SetLineWidth(2);
   tex->Draw();
   TLatex *   tex = new TLatex(0.108,0.96,"Preliminary");
   tex->SetNDC();
   tex->SetTextFont(52);
   tex->SetTextSize(0.038);
   tex->SetLineWidth(2);
   //tex->Draw();
   TLatex *   tex = new TLatex(0.24,0.963,"|#eta|<0.8");
   tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.038);
   tex->SetLineWidth(2);
   tex->Draw();

  cout << "end of process" << endl;
  can->cd();
  can->Print("./figures/plot_vnpt_5panels_hfSys_ratio.png");
  can->Print("./figures/plot_vnpt_5panels_hfSys_ratio.pdf");
  //can->Print("./figures/plot_vnpt_5panels.gif");
}


