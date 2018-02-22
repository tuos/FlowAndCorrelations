void vncent_sys()
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
  for (int ip=0;ip<Mpads;ip++)
  {
    //  hxmin[ip]=0.0; hxmax[ip]=11.9;
    hxmin[ip]=0.0001; hxmax[ip]=62.8;
    hymin[ip]=0.00001; hymax[ip]=0.0559;
    lxmin[ip]=0.24; lxmax[ip]=0.88;
    lymin[ip]=0.65; lymax[ip]=0.94;
    ptit[ip][0]=5.0; ptit[ip][1]=0.00002*0.92;// position legends 
    atit[ip][0]="Centrality (%)"; atit[ip][1]="v_{n}";
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
    }
  }
  inEP.close();
  ifstream inEP;
  inEP.open("./data_vncent5020_integral_vzB.txt");
  for(int i=0; i<nw; i++){
    for(int j=0; j<npt; j++){
      inEP>>nBxa[i][j]; inEP>>nBya[i][j]; inEP>>nBye[i][j];
      nBxe[i][j]=0.0;
    }
  }
  inEP.close();



  TCanvas *can=new TCanvas("can","can",10,10,1050*0.8*1.3,800*0.3*1.3);

  can->Divide(5,1,0,0); //sticks the pads with no space inbetween 
  
  TH1D *h1[nw];
  for (int iw=0;iw<nw;iw++)
  {
    can->cd(iw+1);
    if(iw==4) gPad->SetRightMargin(0.02);
    gPad->SetLogy();
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
    TLegend *leg = new TLegend(lxmin[iw]*0.3,lymin[iw]*1.16,lxmax[iw]*1.15,lymax[iw]*1.02);
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
      leg->AddEntry(ge,"|vz|<3 cm","pl");
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
      leg->AddEntry(geB,"3<|vz|<15 cm","pl");
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
      leg->AddEntry(ge2,"|vz|<15 cm","pl");
    }
    ge2->Draw("pe");
    ge->Draw("pe");
    geB->Draw("pe");
    if (iw==2) leg->Draw();

  }

   can->cd();
   TLatex *   tex = new TLatex(0.06,0.92,"CMS");
   tex->SetNDC();
   tex->SetTextFont(62);
   tex->SetTextSize(0.074);
   tex->SetLineWidth(2);
   tex->Draw();
   TLatex *   tex = new TLatex(0.108,0.92,"Preliminary");
   tex->SetNDC();
   tex->SetTextFont(52);
   tex->SetTextSize(0.074);
   tex->SetLineWidth(2);
   //tex->Draw();
   TLatex *   tex = new TLatex(0.24,0.940,"0.3<p_{T}<3.0 GeV/c         |#eta|<0.8");
   tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.074);
   tex->SetLineWidth(2);
   tex->Draw();

  cout << "end of process" << endl;
  can->cd();
  can->Print("./figures/plot_vncent_vzSys.png");
  can->Print("./figures/plot_vncent_vzSys.pdf");

}

