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

void chipt_5panels()
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
double nxa[Mfiles][Mpoints],nxe[Mfiles][Mpoints],nxesys[Mfiles][Mpoints];
double nya[Mfiles][Mpoints],nye[Mfiles][Mpoints],nyesys[Mfiles][Mpoints];

double aexl[Mfiles][Mpoints],aexh[Mfiles][Mpoints];
double aeyl[Mfiles][Mpoints],aeyh[Mfiles][Mpoints];

double oli_cent[6]={2.5, 7.5, 15, 25, 35, 45};
double nxa_oli7223[Mfiles][Mpoints],nxe_oli7223[Mfiles][Mpoints];
double nya_oli7223[Mfiles][Mpoints],nye_oli7223[Mfiles][Mpoints];
double nxa_oli523exp[Mfiles][Mpoints],nxe_oli523exp[Mfiles][Mpoints];
double nya_oli523exp[Mfiles][Mpoints],nye_oli523exp[Mfiles][Mpoints];
double nxa_oli633exp[Mfiles][Mpoints],nxe_oli633exp[Mfiles][Mpoints];
double nya_oli633exp[Mfiles][Mpoints],nye_oli633exp[Mfiles][Mpoints];
double xa5[Mfiles][Mpoints],xe5[Mfiles][Mpoints],xe5sys[Mfiles][Mpoints];
double ya5[Mfiles][Mpoints],ye5[Mfiles][Mpoints],ye5sys[Mfiles][Mpoints];;

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
    hxmin[ip]=0.0001; hxmax[ip]=7.9;
    hymin[ip]=-0.99*0.45; hymax[ip]=54.9413*0.45; //linY
    //hymin[ip]=0.01; hymax[ip]=204.9413; //logY
    lxmin[ip]=0.24; lxmax[ip]=0.88;
    lymin[ip]=0.65; lymax[ip]=0.94;
    ptit[ip][0]=0.4; ptit[ip][1]=49.028*0.45;  //linY 
    //ptit[ip][0]=0.4; ptit[ip][1]=80.028;  //logY
    atit[ip][0]="p_{T} (GeV/c)"; atit[ip][1]="#chi";
  }
  //
  // Read data and create vector files
  //

  double sysXYZ[5]={5,6,7,7,11};
  double tmp;
  const int nw=5;
  const int npt=20;
  const int npt_oli=8;
  ifstream inEP;
  inEP.open("./data_chiXpt_cent550_2760gev.txt");
  for(int i=0; i<nw; i++){
    for(int j=0; j<npt; j++){
      inEP>>tmp; inEP>>tmp; inEP>>xa[i][j]; inEP>>tmp; inEP>>ya[i][j]; inEP>>ye[i][j];
      //inEP>>xa[i][j]; inEP>>ya[i][j]; inEP>>ye[i][j]; 
      xe[i][j]=0.0; yesys[i][j]=0.045*ya[i][j];
      xesys[i][j]=0.2;
    }
  }
  inEP.close();
  ifstream inEP;
  inEP.open("./data_chiXpt_cent550_5020gev.txt");
  for(int i=0; i<nw; i++){
    for(int j=0; j<npt; j++){
      inEP>>tmp; inEP>>tmp; inEP>>xa5[i][j]; inEP>>tmp; inEP>>ya5[i][j]; inEP>>ye5[i][j];
      //inEP>>xa5[i][j]; inEP>>ya5[i][j]; inEP>>ye5[i][j];
      xe5[i][j]=0.0; ye5sys[i][j]=0.045*ya5[i][j];
      xe5sys[i][j]=0.2;
    }
  }
  inEP.close();
  ifstream inEP;
  inEP.open("./data_chiXpt_cent550_5020gev_generalTracks.txt");
  for(int i=0; i<nw; i++){
    for(int j=0; j<npt; j++){
      inEP>>tmp; inEP>>tmp; inEP>>nxa[i][j]; inEP>>tmp; inEP>>nya[i][j]; inEP>>nye[i][j];
      nxe[i][j]=0.0;
      if(j>4){
        //xa5[i][j]=nxa[i][j];
        //ya5[i][j]=nya[i][j];
        //ye5[i][j]=nye[i][j];
      }
    }
  }
  inEP.close();

  for(int i=0; i<nw; i++){
    cout<<"sys for vn: "<<i<<endl;
    for(int j=0; j<15; j++){
      cout<<nxa[i][j]<<"   "<<fabs(ya5[i][j]-ya[i][j])/fabs(ya[i][j])<<"     "<<fabs(ye[i][j])/fabs(ya[i][j])<<endl;
    }
  }


  TCanvas *can=new TCanvas("can","can",10,10,1050*0.8*1.3,800*0.3*1.3);

  can->Divide(5,1,0,0); //sticks the pads with no space inbetween 
  
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
      h1[iw]->GetYaxis()->SetTitleOffset(1.6);
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
    if (iw==3)
    {
      //tex=new TLatex(1.5,15.0235,"5-50%,  |#eta|<0.8"); //logY
      tex=new TLatex(1.5,30.0235*0.45,"5-50%,  |#eta|<2.4");
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
    tex=new TLatex(ptit[iw][0],ptit[iw][1],htit[iw]);
    if ( iw == 0)   tex->SetTextSize(textsize);
    else if (iw == 8) tex->SetTextSize(textsize);
    else  tex->SetTextSize(textsize);
    tex->Draw();
    //
    // Legend
    //
    //TLegend *leg = new TLegend(lxmin[iw]*0.6,lymin[iw]*1.16*0.75*1.3,lxmax[iw]*0.6,lymax[iw]*1.02*0.8*1.14); //logY
    TLegend *leg = new TLegend(lxmin[iw]*0.3,lymin[iw]*1.16*0.75,lxmax[iw]*1.15,lymax[iw]*1.02*0.8);
    leg->SetFillColor(0);
    leg->SetTextSize(textsize);
    //
    // Read data
    //

    for (int im=0;im<1;im++)
    {
      int j=im*5+iw;
      int col=1;
      //if (ndp[j]==0) continue;

      ge=new TGraphErrors(19,&xa5[j][0],&ya5[j][0],&xe5[j][0],&ye5[j][0]);
      drawSysBox(ge,16,0.2, sysXYZ[j]);
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
      ge2=new TGraphErrors(19,&xa[j][0],&ya[j][0],&xe[j][0],&ye[j][0]);
      ge2->SetTitle("");
      ge2->SetMarkerStyle(25);
      //      ge2->SetMarkerStyle(msty[im]);
      ge2->SetMarkerSize(msiz[im]);
      ge2->SetMarkerColor(col);
      ge2->SetLineWidth(1.2);
      ge2->SetLineColor(col);
      //ge2->Draw("pe");
      leg->AddEntry(ge2,"PbPb 2.76 TeV","pl");
      drawSysBox(ge2,16,0.2, sysXYZ[j]);
    }
    ge2->Draw("pe");
    ge->Draw("pe");
    if (iw==2) leg->Draw();

  }
  cout << "end of process" << endl;
  can->cd();
  can->Print("./figures/plot_chipt_5panels_linY.png");
  can->Print("./figures/plot_chipt_5panels_linY.pdf");
  //can->Print("./figures/plot_chipt_5panels_logY.png");
  //can->Print("./figures/plot_chipt_5panels_logY.pdf");
}

