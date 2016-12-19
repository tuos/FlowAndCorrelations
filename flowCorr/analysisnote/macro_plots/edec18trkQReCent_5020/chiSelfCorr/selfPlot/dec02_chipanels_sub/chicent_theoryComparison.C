void drawSysBox(TGraph* gr, int fillcolor=TColor::GetColor("#ffff00"), double xwidth=0.3, double percent=0, double xshift=0)
{

  TBox* box;
  for(int n=0;n<gr->GetN();n++)
  {
    double x,y;
    gr->GetPoint(n,x,y);

    //double percent=0;
    //if(x>=260) percent=0.074;
    //else if(x<260 && x>=200) percent=0.055;
    //else percent=0.039;

    double yerr = y*percent*0.01;
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

double osu_cent[6]={2.5, 7.5, 15, 25, 35, 45};
double nxa_osu008[Mfiles][Mpoints],nxe_osu008[Mfiles][Mpoints];
double nya_osu008[Mfiles][Mpoints],nye_osu008[Mfiles][Mpoints];
double nxa_osu020[Mfiles][Mpoints],nxe_osu020[Mfiles][Mpoints];
double nya_osu020[Mfiles][Mpoints],nye_osu020[Mfiles][Mpoints];
double xa5[Mfiles][Mpoints],xe5[Mfiles][Mpoints];
double ya5[Mfiles][Mpoints],ye5[Mfiles][Mpoints];

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
    hymin[ip]=0.5; hymax[ip]=1.52;
    lxmin[ip]=0.24; lxmax[ip]=0.88;
    lymin[ip]=0.65; lymax[ip]=0.94;
    ptit[ip][0]=0.8; ptit[ip][1]=-1.;// position legends 
    atit[ip][0]="Centrality (%)"; atit[ip][1]="#chi";
  }
  //
  // Read data and create vector files
  //

  double sysXYZ[5]={5,6,7,7,11};
  double tmp;
  const int nw=5;
  const int npt=14;
  const int npt_osu=6;
  ifstream inEP;
  inEP.open("./data_chiX_integral.txt");
  for(int i=0; i<nw; i++){
    for(int j=0; j<npt; j++){
      //inEP>>tmp; inEP>>tmp; inEP>>xa[i][j]; inEP>>tmp; inEP>>ya[i][j]; inEP>>ye[i][j];
      inEP>>xa[i][j]; inEP>>ya[i][j]; inEP>>ye[i][j]; 
      xe[i][j]=0.0;
    }
  }
  inEP.close();
  ifstream inEP;
  inEP.open("./data_chiX5020_integral.txt");
  for(int i=0; i<nw; i++){
    for(int j=0; j<npt; j++){
      //inEP>>tmp; inEP>>tmp; inEP>>xa[i][j]; inEP>>tmp; inEP>>ya[i][j]; inEP>>ye[i][j];
      inEP>>xa5[i][j]; inEP>>ya5[i][j]; inEP>>ye5[i][j];
      ya5[i][j]=(ya5[i][j])/ya[i][j];
      ye5[i][j]=ye5[i][j]/ya5[i][j];
/*
      ya5[1][0]=1.03; ye5[1][0]=0.04;
      ya5[1][10]=-1.03; ye5[1][9]=ye5[1][8]; ye5[1][10]=ye5[1][8];
      ye5[2][j]=ye5[1][j];  ye5[2][0]=0.05;
      ya5[2][0]=1.04; ya5[2][1]=0.98; ya5[2][2]=0.983; ya5[2][3]=0.985; ya5[2][4]=0.986;
      ya5[2][5]=0.987; ya5[2][6]=0.987; ya5[2][7]=0.988; ya5[2][8]=0.988; ya5[2][9]=0.989; ya5[2][10]=0.995; 
      ya5[3][3]=0.996; ya5[3][4]=0.995; ya5[3][5]=0.993; ya5[3][6]=0.995; ya5[3][7]=0.99; ya5[3][8]=0.989; ya5[3][9]=0.995; ya5[3][10]=0.99;
      if(j>0) ye5[3][j]=ye5[1][j]*1.2;
      ye5[4][j]=ye5[4][j]*0.05; ya5[4][10]=-10;
      ya5[4][j]=ya5[4][j]*1.03;
      ya5[4][1]=0.98; ya5[4][9]=0.96;
*/
     xe5[i][j]=0.0;
    }
  }
  inEP.close();

  ifstream inSP;
  inSP.open("./osu_chiX_Glb_ideal_integral.txt");
  for(int i=0; i<nw; i++){
    for(int j=0; j<npt_osu; j++){
      inSP>>nya[i][j]; inSP>>nye[i][j];
      nxa[i][j]=osu_cent[j];
      nxe[i][j]=0.0;
    }
  }
  inSP.close();
  ifstream inSP;
  inSP.open("./osu_chiX_Glb_SV008_integral.txt");
  for(int i=0; i<nw; i++){
    for(int j=0; j<npt_osu; j++){
      inSP>>nya_osu008[i][j]; inSP>>nye_osu008[i][j];
      nxa_osu008[i][j]=osu_cent[j];
      nxe_osu008[i][j]=0.0;
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
      h1[iw]->GetXaxis()->SetTitleOffset(1.3);
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
    if (iw==0)
    {
      tex=new TLatex(5,6.30,"0.3<p_{T}<3.0 GeV/c");
      tex->SetTextSize(textsize*1.0);
      tex->Draw();
      tex=new TLatex(5,8.35,"|#eta|<0.8");
      tex->SetTextSize(textsize*1.0);
      tex->Draw();
    }
    //if (iw < 4) tex=new TLatex(ptit[iw][0]+2,0.27,htit[iw]);
    tex=new TLatex(10,0.65,htit[iw]);
    if ( iw == 0)   tex->SetTextSize(textsize);
    else if (iw == 8) tex->SetTextSize(textsize);
    else  tex->SetTextSize(textsize);
    tex->Draw();
    //
    // Legend
    //
    TLegend *leg = new TLegend(lxmin[iw]*0.4,lymin[iw]*1.0,lxmax[iw]*0.5,lymax[iw]*1.1);
    leg->SetFillStyle(0);
    leg->SetFillColor(0);
    leg->SetTextSize(textsize*0.9);
    //
    // Read data
    //

    for (int im=0;im<1;im++)
    {
      int j=im*5+iw;
      int col=2;
      //if (ndp[j]==0) continue;
      ge=new TGraphErrors(11,&xa5[j][0],&ya5[j][0],&xe5[j][0],&ye5[j][0]);
      //drawSysBox(ge,16,2., sysXYZ[j]);
      ge->SetTitle("");
      ge->SetMarkerStyle(25);
      //      ge->SetMarkerStyle(msty[im]);
      ge->SetMarkerSize(msiz[im]);
      ge->SetMarkerColor(col);
      ge->SetLineWidth(1.2);
      ge->SetLineColor(col);
      //ge->Draw("pe");
      leg->AddEntry(ge,"#frac{#chi with Self correction}{#chi No Self correction} ","pl");
    }
    for (int im=0;im<1;im++)
    {
      int j=im*5+iw;
      int col=1;
      //if (ndp[j]==0) continue;
      ge2=new TGraphErrors(11,&xa[j][0],&ya[j][0],&xe[j][0],&ye[j][0]);
      //drawSysBox(ge2,16,2., sysXYZ[j]);
      ge2->SetTitle("");
      ge2->SetMarkerStyle(20);
      //      ge2->SetMarkerStyle(msty[im]);
      ge2->SetMarkerSize(msiz[im]);
      ge2->SetMarkerColor(col);
      ge2->SetLineWidth(1.2);
      ge2->SetLineColor(col);
      //ge2->Draw("pe");
      //leg->AddEntry(ge2,"CMS #chi, 2.76 TeV","pl");
    }
    ge->Draw("pe");
    TLine *l = new TLine(0,1,70,1);
    l->SetLineStyle(2);
    l->Draw();
    //ge2->Draw("pe");
    if (iw==2) leg->Draw();

    for (int im=0;im<1;im++)
    {
      int j=im*5+iw;
      int col=1;
      //if (ndp[j]==0) continue;
      ge=new TGraphErrors(6,&nxa[j][0],&nya[j][0],&nxe[j][0],&nye[j][0]);
      ge->SetTitle("");
      ge->SetMarkerStyle(25);
      //      ge->SetMarkerStyle(msty[im]);
      ge->SetMarkerSize(msiz[im]);
      ge->SetMarkerColor(col);
      ge->SetLineWidth(3);
      ge->SetLineStyle(1);
      ge->SetLineColor(col);
      //ge->SetFillColor(kYellow+2);
      //ge->Draw("le");
      //leg->AddEntry(ge,"2.76 TeV, #eta/s=0, Glb","l");
    }
    for (int im=0;im<1;im++)
    {
      int j=im*5+iw;
      int col=2;
      //if (ndp[j]==0) continue;
      ge=new TGraphErrors(6,&nxa_osu008[j][0],&nya_osu008[j][0],&nxe_osu008[j][0],&nye_osu008[j][0]);
      ge->SetTitle("");
      ge->SetMarkerStyle(25);
      //      ge->SetMarkerStyle(msty[im]);
      ge->SetMarkerSize(msiz[im]);
      ge->SetMarkerColor(col);
      ge->SetLineWidth(3);
      ge->SetLineStyle(2);
      ge->SetLineColor(col);
      //ge->SetFillColor(kYellow+2);
      //ge->Draw("le");
      //leg->AddEntry(ge,"2.76 TeV, #eta/s=0.08, Glb","l");
    }
    for (int im=0;im<1;im++)
    {
      int j=im*5+iw;
      int col=4;
      //if (ndp[j]==0) continue;
      ge=new TGraphErrors(6,&nxa_osu020[j][0],&nya_osu020[j][0],&nxe_osu020[j][0],&nye_osu020[j][0]);
      ge->SetTitle("");
      ge->SetMarkerStyle(25);
      //      ge->SetMarkerStyle(msty[im]);
      ge->SetMarkerSize(msiz[im]);
      ge->SetMarkerColor(col);
      ge->SetLineWidth(3);
      ge->SetLineStyle(5);
      ge->SetLineColor(col);
      //ge->SetFillColor(kYellow+2);
      //ge->Draw("le");
      //leg->AddEntry(ge,"2.76 TeV, #eta/s=0.2, Glb","l");
    }

  }
  cout << "end of process" << endl;
  can->cd();
  can->Print("./figures/chi_cent_theorycompHeinz.png");
  can->Print("./figures/chi_cent_theorycompHeinz.pdf");
}

