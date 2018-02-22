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

void drawSysBoxValue(TGraph* gr, int fillcolor=TColor::GetColor("#ffff00"), double xwidth=0.3, double *percent, double xshift=0)
{

  TBox* box;
  for(int n=0;n<gr->GetN();n++)
  {
    double x,y;
    gr->GetPoint(n,x,y);

    double yerr = percent[n]*1.0;
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

v523pt_compareZ()
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
double mxa[Mfiles][Mpoints],mxe[Mfiles][Mpoints];
double mya[Mfiles][Mpoints],mye[Mfiles][Mpoints];

double xesys[Mfiles][Mpoints], yesys[Mfiles][Mpoints];
double mxesys[Mfiles][Mpoints], myesys[Mfiles][Mpoints];

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
  htit[0]="0-5%";
  htit[1]="5-10%";
  htit[2]="10-15%";
  htit[3]="15-20%";
  htit[4]="20-25%";
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
    hxmin[ip]=0.0001; hxmax[ip]=8.3;
    hymin[ip]=-0.002; hymax[ip]=0.0919;
    lxmin[ip]=0.08; lxmax[ip]=0.35;
    lymin[ip]=0.4; lymax[ip]=0.65;
    ptit[ip][0]=4.0; ptit[ip][1]=0.06;// position legends 
    atit[ip][0]="p_{T} (GeV/c)"; atit[ip][1]="v_{5}{#Psi_{23}}";
  }
  //
  // Read data and create vector files
  //

  double sysXYZ[12];
  double sysEach[12];

  double tmp;
  const int nw=12;
  const int npt=20;
  ifstream inEP;
  inEP.open("../outv523_corrFlow.txt");
  for(int i=0; i<nw-2; i++){
sysXYZ[i]=6;
sysEach[i]=0.0002;
      inEP>>tmp; inEP>>tmp;
    for(int j=0; j<npt; j++){
      inEP>>tmp; inEP>>tmp; inEP>>xa[i][j]; inEP>>tmp; inEP>>ya[i][j]; inEP>>ye[i][j];
      //inEP>>xa[i][j]; inEP>>ya[i][j]; inEP>>ye[i][j]; inEP>>tmp;
      xe[i][j]=0.0;
      xesys[i][j]=0.2;
      yesys[i][j]=sqrt(sysEach[i]*sysEach[i] + (ya[i][j]*sysXYZ[i]*0.01)*(ya[i][j]*sysXYZ[i]*0.01));
    }
  }
  inEP.close();

  ifstream inSP;
  inSP.open("/Users/shengquantuo/Downloads/tmp3/figures_-0.8_00.8/outv523steve.txt");
  for(int i=0; i<nw-2; i++){
    for(int j=0; j<npt-2; j++){
      inSP>>mxa[i][j]; inSP>>mya[i][j]; inSP>>mye[i][j];
      mxe[i][j]=0.0; 

      mxesys[i][j]=0.2;
      myesys[i][j]=sqrt(sysEach[i]*sysEach[i] + (mya[i][j]*sysXYZ[i]*0.01)*(mya[i][j]*sysXYZ[i]*0.01));
    }
  }
  inSP.close();

  for(int i=0; i<nw-2; i++){
    cout<<"sys for cent: "<<i<<endl;
    for(int j=0; j<10; j++){
      cout<<nxa[i][j]<<"   "<<fabs(ya[i][j]-nya[i][j])/fabs(ya[i][j])<<endl;
    }
  }


  TCanvas *can=new TCanvas("can","can",10,10,1050*0.9,800*0.85);

  can->Divide(4,3,0,0); //sticks the pads with no space inbetween 
  
  TH1D *h1[nw];
  for (int iw=0;iw<nw;iw++)
  {
    can->cd(iw+1);
    if(iw==3||iw==7||iw==11) gPad->SetRightMargin(0.02);
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
      h1[iw]->GetYaxis()->SetTitleOffset(3.5);
      h1[iw]->GetYaxis()->SetLabelSize(textsize);
      h1[iw]->GetXaxis()->SetTitleSize(textsize);
      h1[iw]->GetXaxis()->SetTitleOffset(3.0);
      h1[iw]->GetXaxis()->SetLabelSize(textsize);
     // h1[iw]->GetXaxis()->SetLabelOffset(1.2);

    h1[iw]->Draw();
  }
  //
  // Draw! 
  //
  cout << "Now Draw!" << endl;
  TGraphErrors *ge;
  for (int iw=0;iw<nw;iw++)
  {
    can->cd(iw+1);

    //
    if (iw==0)
    {
      tex=new TLatex(0.7,0.05,"HIN11005 is 2.76TeV, EP");
      tex->SetTextSize(textsize*0.9);
      //tex->Draw();
      tex=new TLatex(1.5,0.07,"|#eta|<0.8");
      tex->SetTextSize(textsize);
      //tex->Draw();
    }
    if (iw < 4) tex=new TLatex(ptit[iw][0]*1.2,ptit[iw][1]*1.27,htit[iw]);
    else tex=new TLatex(ptit[iw][0]*1.2,ptit[iw][1]*1.27,htit[iw]);
    if ( iw == 0)   tex->SetTextSize(textsize);
    else if (iw == 8) tex->SetTextSize(textsize);
    else  tex->SetTextSize(textsize);
    tex->Draw();
    //
    // Legend
    //
    TLegend *leg = new TLegend(lxmin[iw]*3.99,lymin[iw]*1.1,lxmax[iw]*1.99,lymax[iw]*1.2);
    leg->SetFillColor(0);
    leg->SetTextSize(textsize);
    //
    // Read data
    //
    for (int im=0;im<1;im++)
    {
      int j=im*12+iw;
      int col=2;
      //if (ndp[j]==0) continue;
      ge=new TGraphErrors(16,&mxa[j][0],&mya[j][0],&mxe[j][0],&mye[j][0]);
      drawSysBoxValue(ge,16,0.2, myesys[j]);
      ge->SetTitle("");
      ge->SetMarkerStyle(25);
      //      ge->SetMarkerStyle(msty[im]);
      ge->SetMarkerSize(msiz[im]);
      ge->SetMarkerColor(col);
      ge->SetLineWidth(1.2);
      ge->SetLineColor(col);
      ge->Draw("pe");
      leg->AddEntry(ge,"v_{5}{#Psi_{23}} Steve","p");
    }
    for (int im=0;im<1;im++)
    {
      int j=im*12+iw;
      int col=1;
      //if (ndp[j]==0) continue;
      ge=new TGraphErrors(19,&xa[j][0],&ya[j][0],&xe[j][0],&ye[j][0]);
      //drawSysBoxValue(ge,16,0.2, yesys[j]);
      ge->SetTitle("");
      ge->SetMarkerStyle(msty[im][1]);
      //      ge->SetMarkerStyle(msty[im]);
      ge->SetMarkerSize(msiz[im]);
      ge->SetMarkerColor(col);
      ge->SetLineWidth(1.2);
      ge->SetLineColor(col);
      ge->Draw("pe");
      leg->AddEntry(ge,"v_{5}{#Psi_{23}} Shengquan","p");
    }
    if (iw==0) leg->Draw();

  }
  cout << "end of process" << endl;
  can->cd();
  can->Print("./figures/v523_pt_ShengquanSteve.png");
  can->Print("./figures/v523_pt_ShengquanSteve.pdf");
}

