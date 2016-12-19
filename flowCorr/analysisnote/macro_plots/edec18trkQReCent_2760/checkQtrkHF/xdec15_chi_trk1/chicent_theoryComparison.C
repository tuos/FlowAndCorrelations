void drawSysBox(TGraph* gr, int fillcolor=TColor::GetColor("#ffff00"), double xwidth=0.3, double percent=0, double xshift=0)
{

  TBox* box;
  for(int n=0;n<gr->GetN();n++)
  {
    double x,y;
    gr->GetPoint(n,x,y);
//sysXYZ[5]={5,6,7,7,11};
    //double percent=0;
    //if(x>=260) percent=0.074;
    //else if(x<260 && x>=200) percent=0.055;
    //else percent=0.039;
    double tmp;
    if(n==0) tmp=percent*1.3;
    else if(n==1) tmp=percent*1.3;
    else if(n==2) tmp=percent*1.3;
    else tmp=percent*1.3;
    double yerr = y*tmp*0.01;
    box = new TBox(x+xshift-xwidth,y-fabs(yerr),x+xwidth,y+fabs(yerr));
    //box->SetFillStyle(3001);
  //box->SetFillColor(fillcolor);
    //box->SetFillColor(2);
    box->SetLineWidth(0);
  box->SetFillColor(kGray);
    box->Draw("Fsame");
    //box->Draw();
  }

}

chicent_theoryComparison()
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
double nxa[Mfiles][Mpoints],nxe[Mfiles][Mpoints];
double nya[Mfiles][Mpoints],nye[Mfiles][Mpoints];

double aexl[Mfiles][Mpoints],aexh[Mfiles][Mpoints];
double aeyl[Mfiles][Mpoints],aeyh[Mfiles][Mpoints];

double oli_cent[6]={2.5, 7.5, 15, 25, 35, 45};
double nxa_oli008[Mfiles][Mpoints],nxe_oli008[Mfiles][Mpoints];
double nya_oli008[Mfiles][Mpoints],nye_oli008[Mfiles][Mpoints];
double nxa_oli020[Mfiles][Mpoints],nxe_oli020[Mfiles][Mpoints];
double nya_oli020[Mfiles][Mpoints],nye_oli020[Mfiles][Mpoints];
double xa5[Mfiles][Mpoints],xe5[Mfiles][Mpoints];
double ya5[Mfiles][Mpoints],ye5[Mfiles][Mpoints];
double osu_cent[6]={2.5, 7.5, 15, 25, 35, 45};
double nxa_osu020[Mfiles][Mpoints],nxe_osu020[Mfiles][Mpoints];
double nya_osu020[Mfiles][Mpoints],nye_osu020[Mfiles][Mpoints];
double nxa_osu020kln[Mfiles][Mpoints],nxe_osu020kln[Mfiles][Mpoints];
double nya_osu020kln[Mfiles][Mpoints],nye_osu020kln[Mfiles][Mpoints];

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
    //  hxmin[ip]=0.0; hxmax[ip]=11.9;
    hxmin[ip]=0.0001; hxmax[ip]=70.8;
    hymin[ip]=-0.99; hymax[ip]=5.99;
    lxmin[ip]=0.24; lxmax[ip]=0.88;
    lymin[ip]=0.65; lymax[ip]=0.94;
    ptit[ip][0]=3.0; ptit[ip][1]=-1.;// position legends 
    atit[ip][0]="Centrality (%)"; atit[ip][1]="#chi";
  }
  //
  // Read data and create vector files
  //

  double sysXYZ[5]={5,6,7,7,11};
  double tmp;
  const int nw=5;
  const int npt=14;
  const int npt_oli=8;
  ifstream inEP;
  inEP.open("./data_chiX_integral.txt");
  for(int i=0; i<nw; i++){
    for(int j=0; j<npt; j++){
      //inEP>>tmp; inEP>>tmp; inEP>>xa[i][j]; inEP>>tmp; inEP>>ya[i][j]; inEP>>ye[i][j];
      inEP>>xa[i][j]; inEP>>ya[i][j]; inEP>>ye[i][j]; 
      ya[1][10]=-10.0; ya[2][0]=-10.0; ya[3][10]=-10.0; ya[4][10]=-10.0; ya[4][0]=-10.0;
      //ya[2][0]=-10.0; ya[3][10]=-10.0; ya[4][0]=-10.0; ya[4][10]=-10.0;
      //ya[1][0]=-10.0; ya[3][0]=-10.0; ya[2][10]=-10.0;
      xe[i][j]=0.0;
    }
  }
  inEP.close();
  double tmp;
  const int nw=5;
  const int npt=14;
  const int npt_oli=8;
  const int npt_osu=6;
  ifstream inEP;
  inEP.open("./data_chiX5020_integral.txt");
  for(int i=0; i<nw; i++){
    for(int j=0; j<npt; j++){
      //inEP>>tmp; inEP>>tmp; inEP>>xa[i][j]; inEP>>tmp; inEP>>ya[i][j]; inEP>>ye[i][j];
      inEP>>xa5[i][j]; inEP>>ya5[i][j]; inEP>>ye5[i][j];
      ya5[1][10]=-10.0; ya5[2][0]=-10.0; ya5[3][10]=-10.0; ya5[4][10]=-10.0;
      //ya5[2][0]=-10.0; ya5[3][10]=-10.0; ya5[4][0]=-10.0; ya5[4][10]=-10.0;
      //ya5[1][0]=-10.0; ya5[3][0]=-10.0; ya5[2][10]=-10.0;
      xe5[i][j]=0.0;
    }
  }
  inEP.close();

  ifstream inSP;
  inSP.open("./oli_chiX_Glb_ideal_integral.txt");
  for(int i=0; i<nw; i++){
    for(int j=0; j<npt_oli; j++){
      inSP>>nxa[i][j]; inSP>>nya[i][j];
      nye[i][j]=0.0;
      nxe[i][j]=0.0;
    }
  }
  inSP.close();
  ifstream inSP;
  inSP.open("./oli_chiX_Glb_SV008_integral.txt");
  for(int i=0; i<nw; i++){
    for(int j=0; j<npt_oli; j++){
      inSP>>nxa_oli008[i][j]; inSP>>nya_oli008[i][j];
      nye_oli008[i][j]=0.0;
      nxe_oli008[i][j]=0.0;
    }
  }
  inSP.close();
  ifstream inSP;
  inSP.open("./oli_chiX_Glb_AMPT_integral.txt");
  for(int i=0; i<nw; i++){
    for(int j=0; j<npt_oli-1; j++){
      inSP>>nxa_oli020[i][j]; inSP>>nya_oli020[i][j]; inSP>>nye_oli020[i][j]; inSP>>tmp;
      nye_oli020[i][j]=nya_oli020[i][j]-nye_oli020[i][j];
      nxe_oli020[i][j]=0.0;
    }
  }
  inSP.close();
  ifstream inSP;
  inSP.open("./osu_chiX_Glb_SV020_integral.txt");
  for(int i=0; i<nw; i++){
    for(int j=0; j<npt_osu; j++){
      inSP>>nya_osu020[i][j]; inSP>>nye_osu020[i][j];
      nxa_osu020[i][j]=osu_cent[j];
      nxe_osu020[i][j]=0.0;
    }
  }
  inSP.close();
  ifstream inSP;
  inSP.open("./osu_chiX_KLN_SV020_integral.txt");
  for(int i=0; i<nw; i++){
    for(int j=0; j<npt_osu; j++){
      inSP>>nya_osu020kln[i][j]; inSP>>nye_osu020kln[i][j];
      nxa_osu020kln[i][j]=osu_cent[j];
      nxe_osu020kln[i][j]=0.0;
    }
  }
  inSP.close();

  TCanvas *can=new TCanvas("can","can",10,10,1050*0.8*1.3,800*0.3*1.3);

  can->Divide(5,1,0,0); //sticks the pads with no space inbetween 
  
  TH1D *h1[nw];
  for (int iw=0;iw<nw;iw++)
  {
    can->cd(iw+1);
    if(iw==4) gPad->SetRightMargin(0.02);
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
      h1[iw]->GetYaxis()->SetTitleOffset(1.4);
      h1[iw]->GetYaxis()->SetLabelSize(textsize);
      h1[iw]->GetXaxis()->SetTitleSize(textsize);
      h1[iw]->GetXaxis()->SetTitleOffset(1.2);
      h1[iw]->GetXaxis()->SetLabelSize(textsize);
     // h1[iw]->GetXaxis()->SetLabelOffset(1.2);

    h1[iw]->Draw();
  }
  //
  // Draw! 
  //
  cout << "Now Draw!" << endl;
  TGraphErrors *ge, *ge2;
  for (int iw=0;iw<nw;iw++)
  {
    can->cd(iw+1);

    //
    if (iw==1)
    {
      tex=new TLatex(8,3.55*1.1,"0.3 < p_{T} < 3.0 GeV/c");
      tex->SetTextSize(textsize*1.0);
      tex->Draw();
      tex=new TLatex(8,4.35*1.1,"|#eta| < 2.4");
      tex->SetTextSize(textsize*1.0);
      tex->Draw();
    }
    if (iw==3)
    {
      tex=new TLatex(4.6,4.55*1.1,"Phys.Lett. B744 (2015) 82");
      tex->SetTextSize(textsize*0.88);
      tex->Draw();
    }
    if (iw==2)
    {
      tex=new TLatex(4.8,4.55*1.1,"Phys. Rev. C 93, 064901");
      tex->SetTextSize(textsize*0.88);
      tex->Draw();
    }
    //if (iw < 4) tex=new TLatex(ptit[iw][0]+2,0.27,htit[iw]);
    tex=new TLatex(ptit[iw][0]*1.0,ptit[iw][1]*0.451,htit[iw]);
    if ( iw == 0)   tex->SetTextSize(textsize);
    else if (iw == 8) tex->SetTextSize(textsize);
    else  tex->SetTextSize(textsize);
    tex->Draw();
    //
    // Legend
    //
    TLegend *leg = new TLegend(lxmin[iw]*1.1,lymin[iw]*1.1,lxmax[iw]*1.1,lymax[iw]);
    leg->SetFillStyle(0);
    leg->SetFillColor(0);
    leg->SetTextSize(textsize);
    TLegend *leg2 = new TLegend(lxmin[iw]*0.66,lymin[iw]*0.99,lxmax[iw]*1.0,lymax[iw]*0.91);
    leg2->SetFillStyle(0);
    leg2->SetFillColor(0);
    leg2->SetTextSize(textsize);
    TLegend *leg3 = new TLegend(lxmin[iw]*0.52,lymin[iw]*1.05,lxmax[iw]*1.0,lymax[iw]*0.91);
    leg3->SetFillStyle(0);
    leg3->SetFillColor(0);
    leg3->SetTextSize(textsize);
    //
    // Read data
    //
//Oli
    for (int im=0;im<1;im++)
    {
      int j=im*5+iw;
      int col=1;
      //if (ndp[j]==0) continue;
      ge=new TGraphErrors(8,&nxa[j][0],&nya[j][0],&nxe[j][0],&nye[j][0]);
      ge->SetTitle("");
      //ge->SetMarkerStyle(25);
      //      ge->SetMarkerStyle(msty[im]);
      ge->SetMarkerSize(0.0001);
      ge->SetMarkerColor(col);
      ge->SetLineWidth(3);
      ge->SetLineStyle(1);
      ge->SetLineColor(col);
      //ge->SetFillColor(kYellow+2);
      ge->Draw("pe");
      //leg2->AddEntry(ge,"#eta/s=0","l");
//Error bar line style
      ge2=new TGraphErrors(8,&nxa[j][0],&nya[j][0],&nxe[j][0],&nye[j][0]);
      ge2->SetLineWidth(3);
      ge2->SetLineStyle(1);
      ge2->SetLineColor(col);
      ge2->Draw("l");
      leg2->AddEntry(ge2,"#eta/s=0","l");
    }
    for (int im=0;im<1;im++)
    {
      int j=im*5+iw;
      int col=2;
      //if (ndp[j]==0) continue;
      ge=new TGraphErrors(8,&nxa_oli008[j][0],&nya_oli008[j][0],&nxe_oli008[j][0],&nye_oli008[j][0]);
      ge->SetTitle("");
      //ge->SetMarkerStyle(25);
      //      ge->SetMarkerStyle(msty[im]);
      ge->SetMarkerSize(0.0001);
      ge->SetMarkerColor(col);
      ge->SetLineWidth(3);
      ge->SetLineStyle(1);
      ge->SetLineColor(col);
      //ge->SetFillColor(kYellow+2);
      ge->Draw("pe");
      //leg2->AddEntry(ge,"#eta/s=0.08","l");
//Error bar line style
      ge2=new TGraphErrors(8,&nxa_oli008[j][0],&nya_oli008[j][0],&nxe_oli008[j][0],&nye_oli008[j][0]);
      ge2->SetLineWidth(3);
      ge2->SetLineStyle(2);
      ge2->SetLineColor(col);
      ge2->Draw("l");
      leg2->AddEntry(ge2,"#eta/s=0.08","l");
    }
    for (int im=0;im<1;im++)
    {
      int j=im*5+iw;
      int col=8;
      //if (ndp[j]==0) continue;
      ge=new TGraphErrors(7,&nxa_oli020[j][0],&nya_oli020[j][0],&nxe_oli020[j][0],&nye_oli020[j][0]);
      ge->SetTitle("");
      //ge->SetMarkerStyle(25);
      //      ge->SetMarkerStyle(msty[im]);
      ge->SetMarkerSize(0.0001);
      ge->SetMarkerColor(col);
      ge->SetLineWidth(3);
      ge->SetLineStyle(1);
      ge->SetLineColor(col);
      //ge->SetFillColor(kYellow+2);
      ge->Draw("pe");
      //leg2->AddEntry(ge,"2.76 TeV, AMPT","l");

//Error bar line style
      ge2=new TGraphErrors(7,&nxa_oli020[j][0],&nya_oli020[j][0],&nxe_oli020[j][0],&nye_oli020[j][0]);
      ge2->SetLineWidth(3);
      ge2->SetLineStyle(5);
      ge2->SetLineColor(col);
      ge2->Draw("l");
      leg2->AddEntry(ge2,"AMPT","l");
    }
    if (iw==3) leg2->Draw();

//OSU
    for (int im=0;im<1;im++)
    {
      int j=im*5+iw;
      int col=4;
      //if (ndp[j]==0) continue;
      ge=new TGraphErrors(6,&nxa_osu020[j][0],&nya_osu020[j][0],&nxe_osu020[j][0],&nye_osu020[j][0]);
      ge->SetTitle("");
      //ge->SetMarkerStyle(25);
      //      ge->SetMarkerStyle(msty[im]);
      ge->SetMarkerSize(0.0001);
      ge->SetMarkerColor(col);
      ge->SetLineWidth(3);
      ge->SetLineStyle(1);
      ge->SetLineColor(col);
      //ge->SetFillColor(kYellow+2);
      ge->Draw("pe");
      //leg3->AddEntry(ge,"#eta/s=0.2, Glb","l");
//Error bar line style
      ge2=new TGraphErrors(6,&nxa_osu020[j][0],&nya_osu020[j][0],&nxe_osu020[j][0],&nye_osu020[j][0]);
      ge2->SetLineWidth(3);
      ge2->SetLineStyle(3);
      ge2->SetLineColor(col);
      ge2->Draw("l");
      leg3->AddEntry(ge2,"#eta/s=0.2, Glb","l");
    }
    for (int im=0;im<1;im++)
    {
      int j=im*5+iw;
      int col=6;
      //if (ndp[j]==0) continue;
      ge=new TGraphErrors(6,&nxa_osu020kln[j][0],&nya_osu020kln[j][0],&nxe_osu020kln[j][0],&nye_osu020kln[j][0]);
      ge->SetTitle("");
      //ge->SetMarkerStyle(25);
      //      ge->SetMarkerStyle(msty[im]);
      ge->SetMarkerSize(0.0001);
      ge->SetMarkerColor(col);
      ge->SetLineWidth(3);
      ge->SetLineStyle(1);
      ge->SetLineColor(col);
      //ge->SetFillColor(kYellow+2);
      ge->Draw("pe");
      //leg3->AddEntry(ge,"#eta/s=0.2, KLN","l");
//Error bar line style
      ge2=new TGraphErrors(6,&nxa_osu020kln[j][0],&nya_osu020kln[j][0],&nxe_osu020kln[j][0],&nye_osu020kln[j][0]);
      ge2->SetLineWidth(3);
      ge2->SetLineStyle(7);
      ge2->SetLineColor(col);
      ge2->Draw("l");
      leg3->AddEntry(ge2,"#eta/s=0.2, KLN","l");
    }
    if (iw==2) leg3->Draw();

//Data
    for (int im=0;im<1;im++)
    {
      int j=im*5+iw;
      int col=1;
      //if (ndp[j]==0) continue;
      ge=new TGraphErrors(11,&xa5[j][0],&ya5[j][0],&xe5[j][0],&ye5[j][0]);
      drawSysBox(ge,16,2., sysXYZ[j]);
      ge->SetTitle("");
      ge->SetMarkerStyle(20);
      //      ge->SetMarkerStyle(msty[im]);
      ge->SetMarkerSize(msiz[im]);
      ge->SetMarkerColor(col);
      ge->SetLineWidth(1.2);
      ge->SetLineColor(col);
      //ge->Draw("pe");
      leg->AddEntry(ge,"PbPb 5.02 TeV","pl");
    }
    for (int im=0;im<1;im++)
    {
      int j=im*5+iw;
      int col=2;
      //if (ndp[j]==0) continue;
      ge2=new TGraphErrors(11,&xa[j][0],&ya[j][0],&xe[j][0],&ye[j][0]);
      drawSysBox(ge2,16,2., sysXYZ[j]);
      ge2->SetTitle("");
      ge2->SetMarkerStyle(25);
      //      ge2->SetMarkerStyle(msty[im]);
      ge2->SetMarkerSize(msiz[im]);
      ge2->SetMarkerColor(col);
      ge2->SetLineWidth(1.2);
      ge2->SetLineColor(col);
      //ge2->Draw("pe");
      leg->AddEntry(ge2,"PbPb 2.76 TeV","pl");
    }
    ge2->Draw("pe");
    ge->Draw("pe");
    if (iw==0) leg->Draw();

  }
  cout << "end of process" << endl;
  can->cd();
  can->Print("./figures/plot_chicent_theorycomp.png");
  can->Print("./figures/plot_chicent_theorycomp.pdf");
}

