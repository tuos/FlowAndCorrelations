void chicent_sys_ratio()
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
double xa[Mfiles][Mpoints],xe[Mfiles][Mpoints];
double ya[Mfiles][Mpoints],ye[Mfiles][Mpoints];

double nAxa[Mfiles][Mpoints],nAxe[Mfiles][Mpoints];
double nAya[Mfiles][Mpoints],nAye[Mfiles][Mpoints];
double nBxa[Mfiles][Mpoints],nBxe[Mfiles][Mpoints];
double nBya[Mfiles][Mpoints],nBye[Mfiles][Mpoints];
double nARxa[Mfiles][Mpoints],nARxe[Mfiles][Mpoints];
double nARya[Mfiles][Mpoints],nARye[Mfiles][Mpoints];
double nBRxa[Mfiles][Mpoints],nBRxe[Mfiles][Mpoints];
double nBRya[Mfiles][Mpoints],nBRye[Mfiles][Mpoints];

double aexl[Mfiles][Mpoints],aexh[Mfiles][Mpoints];
double aeyl[Mfiles][Mpoints],aeyh[Mfiles][Mpoints];


double ra[Mfiles][Mpoints],re[Mfiles][Mpoints];

const int Mpads=14;


char  *htit[Mpads];
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
  htit[0]="(a) #chi_{422}";
  htit[1]="(b) #chi_{523}";
  htit[2]="(c) #chi_{6222}";
  htit[3]="(d) #chi_{633}";
  htit[4]="(e) #chi_{7223}";
  htit[5]="25-30%";
  htit[6]="30-35%";
  htit[7]="35-40%";
  htit[8]="40-50%";
  htit[9]="50-60%";
  htit[10]="60-70%";
  htit[11]="70-80%";
  for (int ip=0;ip<Mpads;ip++)
  {
    hxmin[ip]=0.0001; hxmax[ip]=62.8;
    hymin[ip]=-0.3; hymax[ip]=6.99;
    lxmin[ip]=0.24; lxmax[ip]=0.88;
    lymin[ip]=0.65; lymax[ip]=0.94;
    ptit[ip][0]=3.0; ptit[ip][1]=-1.;// position legends 
    atit[ip][0]="Centrality (%)"; atit[ip][1]="#chi";
  }
  //
  // Read data and create vector files
  //

  double sysXYZ[5]={6,7,8,8,9};
  //double sysXYZ[5]={9,9,13,13,15};
  //double sysXYZ[5]={8,9,20,20,20};
  double sysEach[5]={0.0002, 0.0002, 0.0002, 0.0003, 0.0002};
  double tmp;
  const int nw=5;
  const int npt=14;
  const int npt_oli=8;
  ifstream inEP;
  inEP.open("./data_vncent5020_integral.txt");
  for(int i=0; i<nw; i++){
    for(int j=0; j<npt; j++){
      inEP>>xa[i][j]; inEP>>ya[i][j]; inEP>>ye[i][j]; 
      xe[i][j]=0.0;
    }
  }
  inEP.close();
  ifstream inEP;
  inEP.open("./data_vncent5020_integral_vzA.txt");
  for(int i=0; i<nw; i++){
    for(int j=0; j<npt; j++){
      inEP>>nAxa[i][j]; inEP>>nAya[i][j]; inEP>>nAye[i][j];
      nAxe[i][j]=0.0;

      nARxa[i][j]=nAxa[i][j];
      nARxe[i][j]=nAxe[i][j];
      nARye[i][j]=nAya[i][j]/ya[i][j]*sqrt(ye[i][j]*ye[i][j]/ya[i][j]/ya[i][j] + nAye[i][j]*nAye[i][j]/nAya[i][j]/nAya[i][j] - 2.0*ye[i][j]*ye[i][j]/ya[i][j]/nAya[i][j] );
      nARya[i][j]=nAya[i][j]/ya[i][j];
    }
  }
  inEP.close();
  ifstream inEP;
  inEP.open("./data_vncent5020_integral_vzB.txt");
  for(int i=0; i<nw; i++){
    for(int j=0; j<npt; j++){
      inEP>>nBxa[i][j]; inEP>>nBya[i][j]; inEP>>nBye[i][j];
      nBxe[i][j]=0.0;

      nBRxa[i][j]=nBxa[i][j];
      nBRxe[i][j]=nBxe[i][j];
      nBRye[i][j]=nBya[i][j]/ya[i][j]*sqrt(ye[i][j]*ye[i][j]/ya[i][j]/ya[i][j] + nBye[i][j]*nBye[i][j]/nBya[i][j]/nBya[i][j] - 2.0*ye[i][j]*ye[i][j]/ya[i][j]/nBya[i][j] );
      nBRya[i][j]=nBya[i][j]/ya[i][j];
cout<<"ratio A: "<<nARya[i][j]<<",  Aerr = "<<nARye[i][j]<<",  ratio B="<<nBRya[i][j]<<",  Berr = "<<nBRye[i][j]<<endl;
    }
  }
  inEP.close();



  TCanvas *can=new TCanvas("can","can",10,10,1050*0.8*1.3,800*0.3*1.3 * 1.5);

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
    h1[iw]->SetMinimum(hymin[iw]); h1[iw]->SetMaximum(hymax[iw]);
    h1[iw]->SetXTitle(atit[iw][0]); h1[iw]->SetYTitle(atit[iw][1]);
    h1[iw]->GetXaxis()->CenterTitle(1);
    h1[iw]->GetYaxis()->CenterTitle(1);

    // futz with the axes
    h1[iw]->GetYaxis()->SetNdivisions(606);
    h1[iw]->GetXaxis()->SetNdivisions(606);

      h1[iw]->GetYaxis()->SetTitleSize(textsize);
      h1[iw]->GetYaxis()->SetTitleOffset(1.8);
      h1[iw]->GetYaxis()->SetLabelSize(textsize);
      h1[iw]->GetXaxis()->SetTitleSize(textsize);
      h1[iw]->GetXaxis()->SetTitleOffset(1.3);
      h1[iw]->GetXaxis()->SetLabelSize(textsize);
     // h1[iw]->GetXaxis()->SetLabelOffset(1.2);

    h1[iw]->Draw();
  }
  //
  // Draw! 
  //
  cout << "Now Draw!" << endl;
  TGraphErrors *ge, *geB, *ge2;
  for (int iw=0;iw<nw;iw++)
  {
    can->cd(iw+1);

    //
    if (iw==3)
    {
      tex=new TLatex(11,0.0100,"CMS Preliminary");
      tex->SetTextSize(textsize*1.0);
      //tex->Draw();
    }
    if (iw==0)
    {
      tex=new TLatex(5,0.00015,"Hydro. at #sqrt{s_{NN}}=2.76TeV");
      tex->SetTextSize(textsize*0.85);
      //tex->Draw();
      tex=new TLatex(7,0.00033,"|#eta|<2.4");
      tex->SetTextSize(textsize*1.0);
      //tex->Draw();
      tex=new TLatex(7,0.00012,"0.3<p_{T}<3.0 GeV/c");
      tex->SetTextSize(textsize*1.0);
      //tex->Draw();
    }
    //if (iw < 4) tex=new TLatex(ptit[iw][0]+2,0.27,htit[iw]);
    tex=new TLatex(ptit[iw][0],ptit[iw][1],htit[iw]);
    if ( iw == 0)   tex->SetTextSize(textsize);
    else if (iw == 8) tex->SetTextSize(textsize);
    else  tex->SetTextSize(textsize);
    tex->Draw();


    //
    // Read data
    //
    TLegend *leg = new TLegend(lxmin[iw]*0.3,lymin[iw]*1.05,lxmax[iw]*1.15,lymax[iw]*1.02);
    leg->SetFillStyle(0);
    leg->SetFillColor(0);
    leg->SetTextSize(textsize);

    for (int im=0;im<1;im++)
    {
      int j=im*5+iw;
      int col=2;
      //if (ndp[j]==0) continue;
      ge=new TGraphErrors(10,&nAxa[j][0],&nAya[j][0],&nAxe[j][0],&nAye[j][0]);
      ///drawSysBoxValue(ge,16,1.6, ye5sys[j]);
      //drawSysBox(ge,16,2., sysXYZ[j]);
      ge->SetTitle("");
      ge->SetMarkerStyle(24);
      //      ge->SetMarkerStyle(msty[im]);
      ge->SetMarkerSize(msiz[im]);
      ge->SetMarkerColor(col);
      ge->SetLineWidth(1.2);
      ge->SetLineColor(col);
      //ge->Draw("pe");
      leg->AddEntry(ge,"HF 3<|#eta|<4","pl");
    }
    for (int im=0;im<1;im++)
    { 
      int j=im*5+iw;
      int col=4;
      //if (ndp[j]==0) continue;
      geB=new TGraphErrors(10,&nBxa[j][0],&nBya[j][0],&nBxe[j][0],&nBye[j][0]);
      ///drawSysBoxValue(ge,16,1.6, ye5sys[j]);
      //drawSysBox(ge,16,2., sysXYZ[j]);
      geB->SetTitle("");
      geB->SetMarkerStyle(25);
      //      ge->SetMarkerStyle(msty[im]);
      geB->SetMarkerSize(msiz[im]);
      geB->SetMarkerColor(col);
      geB->SetLineWidth(1.2);
      geB->SetLineColor(col);
      //ge->Draw("pe");
      leg->AddEntry(geB,"HF 4<|#eta|<5","pl");
    }
    for (int im=0;im<1;im++)
    {
      int j=im*5+iw;
      int col=1;
      //if (ndp[j]==0) continue;
      ge2=new TGraphErrors(10,&xa[j][0],&ya[j][0],&xe[j][0],&ye[j][0]);
      ///drawSysBoxValue(ge2,16,1.6, yesys[j]);
      //drawSysBox(ge2,16,2., sysXYZ[j]);
      ge2->SetTitle("");
      ge2->SetMarkerStyle(20);
      //      ge2->SetMarkerStyle(msty[im]);
      ge2->SetMarkerSize(msiz[im]);
      ge2->SetMarkerColor(col);
      ge2->SetLineWidth(1.2);
      ge2->SetLineColor(col);
      //ge2->Draw("pe");
      leg->AddEntry(ge2,"Default, HF(3,5)","pl");
    }
    ge2->Draw("pe");
    ge->Draw("pe");
    geB->Draw("pe");
    if (iw==2) leg->Draw();

  }

//start new
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
    h2[iw]->SetXTitle(atit[iw][0]); h2[iw]->SetYTitle(atit[iw][1]);
    h2[iw]->GetXaxis()->CenterTitle(1);
    h2[iw]->GetYaxis()->CenterTitle(1);
    h2[iw]->GetYaxis()->SetNdivisions(606);
    h2[iw]->GetXaxis()->SetNdivisions(606);
      h2[iw]->GetYaxis()->SetTitleSize(textsize);
      h2[iw]->GetYaxis()->SetTitleOffset(1.8);
      h2[iw]->GetYaxis()->SetLabelSize(textsize);
      h2[iw]->GetXaxis()->SetTitleSize(textsize);
      h2[iw]->GetXaxis()->SetTitleOffset(1.3);
      h2[iw]->GetXaxis()->SetLabelSize(textsize);
    
    h2[iw]->Draw();
  }
  for (int iw=0;iw<nw;iw++)
  {
    can->cd(iw+5+1);

    //
    if (iw==3+5)
    {
      tex=new TLatex(11,0.0100,"CMS Preliminary");
      tex->SetTextSize(textsize*1.0);
      //tex->Draw();
    }
    if (iw==0+5)
    {
      tex=new TLatex(5,0.00015,"Hydro. at #sqrt{s_{NN}}=2.76TeV");
      tex->SetTextSize(textsize*0.85);
      //tex->Draw();
      tex=new TLatex(7,0.00033,"|#eta|<2.4");
      tex->SetTextSize(textsize*1.0);
      //tex->Draw();
      tex=new TLatex(7,0.00012,"0.3<p_{T}<3.0 GeV/c");
      tex->SetTextSize(textsize*1.0);
      //tex->Draw();
    }
    //if (iw < 4) tex=new TLatex(ptit[iw][0]+2,0.27,htit[iw]);
    //tex=new TLatex(10,0.9,htit[iw]);
    tex=new TLatex(10,0.9,"CMS");
    if ( iw == 0)   tex->SetTextSize(textsize);
    else if (iw == 8) tex->SetTextSize(textsize);
    else  tex->SetTextSize(textsize);
    //tex->Draw();


    //
    // Read data
    //
    TLegend *leg2 = new TLegend(lxmin[iw]*0.3,lymin[iw]*1.16,lxmax[iw]*1.15,lymax[iw]*1.02);
    leg2->SetFillStyle(0);
    leg2->SetFillColor(0);
    leg2->SetTextSize(textsize);

    for (int im=0;im<1;im++)
    {
      int j=im*5+iw;
      int col=2;
      //if (ndp[j]==0) continue;
      ge=new TGraphErrors(10,&nARxa[j][0],&nARya[j][0],&nARxe[j][0],&nARye[j][0]);
      ///drawSysBoxValue(ge,16,1.6, ye5sys[j]);
      //drawSysBox(ge,16,2., sysXYZ[j]);
      ge->SetTitle("");
      ge->SetMarkerStyle(24);
      //      ge->SetMarkerStyle(msty[im]);
      ge->SetMarkerSize(msiz[im]);
      ge->SetMarkerColor(col);
      ge->SetLineWidth(1.2);
      ge->SetLineColor(col);
      //ge->Draw("pe");
      leg2->AddEntry(ge,"HF(3,4)/HF(3,5)","pl");
    }
    for (int im=0;im<1;im++)
    { 
      int j=im*5+iw;
      int col=4;
      //if (ndp[j]==0) continue;
      geB=new TGraphErrors(10,&nBRxa[j][0],&nBRya[j][0],&nBRxe[j][0],&nBRye[j][0]);
      ///drawSysBoxValue(ge,16,1.6, ye5sys[j]);
      //drawSysBox(ge,16,2., sysXYZ[j]);
      geB->SetTitle("");
      geB->SetMarkerStyle(25);
      //      ge->SetMarkerStyle(msty[im]);
      geB->SetMarkerSize(msiz[im]);
      geB->SetMarkerColor(col);
      geB->SetLineWidth(1.2);
      geB->SetLineColor(col);
      //ge->Draw("pe");
      leg2->AddEntry(geB,"HF(4,5)/HF(3,5)","pl");
    }
    ge->Draw("pe");
    geB->Draw("pe");
    if (iw==2) leg2->Draw();

    TLine *lines = new TLine(0,1,60,1);
    lines->SetLineStyle(2);
    lines->SetLineWidth(1); 
    lines->Draw();

if(iw==0||iw==1){
    TF1 *fitFun = new TF1("fitFun","pol2", 0, 60);
    fitFun->SetLineColor(4);
    geB->Fit("fitFun","R+");
    fitFun->Draw("same");
cout<<fitFun->Eval(2.5)<<",  "<<fitFun->Eval(7.5)<<",  "<<fitFun->Eval(45)<<",  "<<fitFun->Eval(55)<<endl;
}
else {
    TF1 *fitFun = new TF1("fitFun","pol0", 0, 60);
    fitFun->SetLineColor(4);
    geB->Fit("fitFun","R+");
    fitFun->Draw("same");
cout<<fitFun->Eval(2.5)<<",  "<<fitFun->Eval(7.5)<<",  "<<fitFun->Eval(45)<<",  "<<fitFun->Eval(55)<<endl;
}

    double chi2 = fitFun->GetChisquare();
    double ndf = fitFun->GetNDF();
   TLatex *tex = new TLatex(10.06,0.6,Form("#chi^{2}/ndf = %2.1f", chi2/ndf));
   //tex->SetNDC();
   //tex->SetTextFont(42);
   tex->SetTextColor(2);
   tex->SetTextSize(16);
   //tex->SetLineWidth(2);
   tex->Draw("same");


   //TLatex *text = new TLatex();
   //text->DrawTextNDC(10.12, 1.14, "D0 Preliminary");

/*
    double p0 = fitFun->GetParameter(0);
    double p0Err = fitFun->GetParError(0);
    TLine *linesErrP = new TLine(0,p0+p0Err,60,p0+p0Err);
    linesErrP->SetLineStyle(2);
    linesErrP->SetLineWidth(1);
    linesErrP->SetLineColor(2);
    linesErrP->Draw();
    TLine *linesErrM = new TLine(0,p0-p0Err,60,p0-p0Err);
    linesErrM->SetLineStyle(2);
    linesErrM->SetLineWidth(1);
    linesErrM->SetLineColor(2);
    linesErrM->Draw();
*/
  }
//end new

   can->cd();
   TLatex *   tex = new TLatex(0.06,0.97,"CMS");
   tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.034);
   tex->SetLineWidth(2);
   tex->Draw();
   TLatex *   tex = new TLatex(0.108,0.97,"Preliminary");
   tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.044);
   tex->SetLineWidth(2);
   //tex->Draw();
   TLatex *   tex = new TLatex(0.24,0.970,"0.3<p_{T}<3.0 GeV/c         |#eta|<0.8");
   tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.044);
   tex->SetLineWidth(2);
   tex->Draw();

  cout << "end of process" << endl;
  can->cd();
  can->Print("./figures/plot_chicent_hfSys_ratio.png");
  can->Print("./figures/plot_chicent_hfSys_ratio.pdf");

}

