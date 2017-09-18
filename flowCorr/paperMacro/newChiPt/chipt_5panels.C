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
double ya5[Mfiles][Mpoints],ye5[Mfiles][Mpoints],ye5sys[Mfiles][Mpoints];

double xac2[Mfiles][Mpoints],xec2[Mfiles][Mpoints],xesysc2[Mfiles][Mpoints];
double yac2[Mfiles][Mpoints],yec2[Mfiles][Mpoints],yesysc2[Mfiles][Mpoints];
double xa5c2[Mfiles][Mpoints],xe5c2[Mfiles][Mpoints],xe5sysc2[Mfiles][Mpoints];
double ya5c2[Mfiles][Mpoints],ye5c2[Mfiles][Mpoints],ye5sysc2[Mfiles][Mpoints];

double ra[Mfiles][Mpoints],re[Mfiles][Mpoints];

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
  htitc2[0]="(f) #chi_{422}";
  htitc2[1]="(g) #chi_{523}";
  htitc2[2]="(h) #chi_{6222}";
  htitc2[3]="(i) #chi_{633}";
  htitc2[4]="(j) #chi_{7223}";
  for (int ip=0;ip<Mpads;ip++)
  {
    //  hxmin[ip]=0.0; hxmax[ip]=11.9;
    hxmin[ip]=0.0001; hxmax[ip]=7.9; 
    hymin[ip]=-0.99*0.75; hymax[ip]=4.1;//54.9413*0.75;
    lxmin[ip]=0.24; lxmax[ip]=0.88;
    lymin[ip]=0.65; lymax[ip]=0.94;
    ptit[ip][0]=0.4; ptit[ip][1]=49.028*0.475;
    atit[ip][0]="p_{T} (GeV/c)"; atit[ip][1]="#chi";
  }
  //
  // Read data and create vector files
  //

  double sysXYZ[5]={6,7,8,8,9};
  //double sysXYZ[5]={8,9,12,12,15};
  //double sysXYZ[5]={8,9,20,20,20};
  double sysEach[5]={0.02, 0.1, 0.2, 0.3, 0.4};
  double tmp;
  const int nw=5;
  const int npt=20;
  const int npt_oli=8;
  ifstream inEP;
  inEP.open("./data_chiXpt_cent020_2760gev.txt");
  for(int i=0; i<nw; i++){
    for(int j=0; j<npt; j++){
      inEP>>tmp; inEP>>tmp; inEP>>xa[i][j]; inEP>>tmp; inEP>>ya[i][j]; inEP>>ye[i][j];
      //inEP>>xa[i][j]; inEP>>ya[i][j]; inEP>>ye[i][j]; 
      xe[i][j]=0.0; //yesys[i][j]=sysXYZ[i]*ya[i][j];
      xesys[i][j]=0.2;
      yesys[i][j]=sqrt(sysEach[i]*sysEach[i] + (ya[i][j]*sysXYZ[i]*0.01)*(ya[i][j]*sysXYZ[i]*0.01));
    }
  }
  inEP.close();
  ifstream inEP;
  inEP.open("./data_chiXpt_cent020_5020gev.txt");
  for(int i=0; i<nw; i++){
    for(int j=0; j<npt; j++){
      inEP>>tmp; inEP>>tmp; inEP>>xa5[i][j]; inEP>>tmp; inEP>>ya5[i][j]; inEP>>ye5[i][j];
      //inEP>>xa5[i][j]; inEP>>ya5[i][j]; inEP>>ye5[i][j];
      xe5[i][j]=0.0; //ye5sys[i][j]=sysXYZ[i]*ya5[i][j];
      xe5sys[i][j]=0.2;
      ye5sys[i][j]=sqrt(sysEach[i]*sysEach[i]+(ya5[i][j]*sysXYZ[i]*0.01)*(ya5[i][j]*sysXYZ[i]*0.01));
    }
  }
  inEP.close();
  ifstream inEP;
  inEP.open("./data_chiXpt_cent2060_2760gev.txt");
  for(int i=0; i<nw; i++){
    for(int j=0; j<npt; j++){
      inEP>>tmp; inEP>>tmp; inEP>>xac2[i][j]; inEP>>tmp; inEP>>yac2[i][j]; inEP>>yec2[i][j];
      xec2[i][j]=0.0; //yesysc2[i][j]=sysXYZ[i]*yac2[i][j];
      xesysc2[i][j]=0.2;
      yesysc2[i][j]=sqrt(sysEach[i]*sysEach[i] + (yac2[i][j]*sysXYZ[i]*0.01)*(yac2[i][j]*sysXYZ[i]*0.01));
    }
  }
  inEP.close();
  ifstream inEP;
  inEP.open("./data_chiXpt_cent2060_5020gev.txt");
  for(int i=0; i<nw; i++){
    for(int j=0; j<npt; j++){
      inEP>>tmp; inEP>>tmp; inEP>>xa5c2[i][j]; inEP>>tmp; inEP>>ya5c2[i][j]; inEP>>ye5c2[i][j];
      xe5c2[i][j]=0.0; //ye5sysc2[i][j]=sysXYZ[i]*ya5c2[i][j];
      xe5sysc2[i][j]=0.2;
      ye5sysc2[i][j]=sqrt(sysEach[i]*sysEach[i]+(ya5c2[i][j]*sysXYZ[i]*0.01)*(ya5c2[i][j]*sysXYZ[i]*0.01));
    }
  }
  inEP.close();

/// not used below
  ifstream inEP;
  inEP.open("./data_chiXpt_cent2060_5020gev.txt");
  for(int i=0; i<nw; i++){
    for(int j=0; j<npt; j++){
      //inEP>>tmp; inEP>>tmp; inEP>>nxa[i][j]; inEP>>tmp; inEP>>nya[i][j]; inEP>>nye[i][j];
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
      //cout<<nxa[i][j]<<"   "<<fabs(ya5[i][j]-ya[i][j])/fabs(ya[i][j])<<"     "<<fabs(ye[i][j])/fabs(ya[i][j])<<endl;
    }
  }


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
    h1[iw]->SetMinimum(hymin[iw]); h1[iw]->SetMaximum(hymax[iw]);
    h1[iw]->SetXTitle(atit[iw][0]); h1[iw]->SetYTitle(atit[iw][1]);
    h1[iw]->GetXaxis()->CenterTitle(1);
    h1[iw]->GetYaxis()->CenterTitle(1);

    // futz with the axes
    h1[iw]->GetYaxis()->SetNdivisions(606);
    h1[iw]->GetXaxis()->SetNdivisions(606);

      h1[iw]->GetYaxis()->SetTitleSize(textsize*1.4);
      h1[iw]->GetYaxis()->SetTitleOffset(2.);
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
    h2[iw]->SetMinimum(hymin[iw]); h2[iw]->SetMaximum(hymax[iw]);
    h2[iw]->SetXTitle(atit[iw][0]); h2[iw]->SetYTitle(atit[iw][1]);
    h2[iw]->GetXaxis()->CenterTitle(1);
    h2[iw]->GetYaxis()->CenterTitle(1);

    // futz with the axes
    h2[iw]->GetYaxis()->SetNdivisions(606);
    h2[iw]->GetXaxis()->SetNdivisions(606);

      h2[iw]->GetYaxis()->SetTitleSize(textsize*1.4);
      h2[iw]->GetYaxis()->SetTitleOffset(2.);
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
  cout << "Now Draw!" << endl;
  TGraphErrors *ge, *ge2, *ge3, *ge4;
  for (int iw=0;iw<nw;iw++)
  {
    can->cd(iw+1);

    //
    if (iw==0)
    {
      tex=new TLatex(1.2,0.0235*0.88*1.275*1.3*660.47,"CMS Preliminary");
      tex->SetTextSize(textsize*1.0);
      //tex->Draw();
    }
    if (iw==3)
    {
      tex=new TLatex(2.9,0.0235*0.88*1.275*1.3*66,"0-20%");
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
    tex=new TLatex(ptit[iw][0],ptit[iw][1]*1.125*1.39*0.1,htit[iw]);
    if ( iw == 0)   tex->SetTextSize(textsize);
    else if (iw == 8) tex->SetTextSize(textsize);
    else  tex->SetTextSize(textsize);
    tex->Draw();
    //
    // Legend
    //
    TLegend *leg = new TLegend(lxmin[iw]*0.4,lymin[iw]*1.16*0.75*0.8*1.25,lxmax[iw]*1.15,lymax[iw]*1.02*0.8*0.92*1.15);
    leg->SetFillColor(0);
    leg->SetTextSize(textsize);
    TLegend *leg2 = new TLegend(lxmin[iw]*0.4,lymin[iw]*1.16*0.75*1.25,lxmax[iw]*1.15,lymax[iw]*1.02*0.8*1.15);
    leg2->SetFillColor(0);
    leg2->SetTextSize(textsize);
    //
    // Read data
    //

    for (int im=0;im<1;im++)
    {
      int j=im*5+iw;
      int col=1;
      //if (ndp[j]==0) continue;
      ge2=new TGraphErrors(19,&xa[j][0],&ya[j][0],&xe[j][0],&ye[j][0]);
      ///drawSysBoxValue(ge2,16,0.2, yesys[j]);
      ge2->SetTitle("");
      ge2->SetMarkerStyle(20);
      //      ge2->SetMarkerStyle(msty[im]);
      ge2->SetMarkerSize(msiz[im]);
      ge2->SetMarkerColor(col);
      ge2->SetLineWidth(1.2);
      ge2->SetLineColor(col);
      //ge2->Draw("pe");
      leg->AddEntry(ge2,"PbPb 5.02 TeV","pl");
      //drawSysBox(ge2,16,0.2, sysXYZ[j]);
    }
    for (int im=0;im<1;im++)
    {
      int j=im*5+iw;
      int col=2;
      //if (ndp[j]==0) continue;

      ge=new TGraphErrors(19,&xa5[j][0],&ya5[j][0],&xe5[j][0],&ye5[j][0]);
      drawSysBoxValue(ge,16,0.2, ye5sys[j]);
      //drawSysBox(ge,16,0.2, sysXYZ[j]);
      ge->SetTitle("");
      ge->SetMarkerStyle(25);
      //      ge->SetMarkerStyle(msty[im]);
      ge->SetMarkerSize(msiz[im]);
      ge->SetMarkerColor(col);
      ge->SetLineWidth(1.2);
      ge->SetLineColor(col);
      //ge->Draw("pe");
      leg->AddEntry(ge,"PbPb 5.02 TeV","pl");
    }
    ///ge2->Draw("pe");
    ge->Draw("pe");
    if (iw==2) leg->Draw();


    can->cd(iw+1+5);
    tex=new TLatex(ptit[iw][0],ptit[iw][1]*1.125*1.39,htitc2[iw]);
    if ( iw == 0)   tex->SetTextSize(textsize);
    else if (iw == 8) tex->SetTextSize(textsize);
    else  tex->SetTextSize(textsize);
    tex->Draw();

    for (int im=0;im<1;im++)
    {
      int j=im*5+iw;
      int col=1;
      //if (ndp[j]==0) continue;
      ge4=new TGraphErrors(19,&xac2[j][0],&yac2[j][0],&xec2[j][0],&yec2[j][0]);
      ///drawSysBoxValue(ge4,16,0.2, yesysc2[j]);
      ge4->SetTitle("");
      ge4->SetMarkerStyle(20);
      //      ge4->SetMarkerStyle(msty[im]);
      ge4->SetMarkerSize(msiz[im]);
      ge4->SetMarkerColor(col);
      ge4->SetLineWidth(1.2);
      ge4->SetLineColor(col);
      //ge4->Draw("pe");
      leg2->AddEntry(ge4,"PbPb 2.76 TeV","pl");
      //drawSysBox(ge4,16,0.2, sysXYZ[j]);
    }
    for (int im=0;im<1;im++)
    {
      int j=im*5+iw;
      int col=2;
      //if (ndp[j]==0) continue;

      ge3=new TGraphErrors(19,&xa5c2[j][0],&ya5c2[j][0],&xe5c2[j][0],&ye5c2[j][0]);
      drawSysBoxValue(ge3,16,0.2, ye5sysc2[j]);
      //drawSysBox(ge3,16,0.2, sysXYZ[j]);
      ge3->SetTitle("");
      ge3->SetMarkerStyle(25);
      //      ge3->SetMarkerStyle(msty[im]);
      ge3->SetMarkerSize(msiz[im]);
      ge3->SetMarkerColor(col);
      ge3->SetLineWidth(1.2);
      ge3->SetLineColor(col);
      //ge3->Draw("pe");
      leg2->AddEntry(ge3,"PbPb 5.02 TeV","pl");
    }
    ///ge4->Draw("pe");
    ge3->Draw("pe");
    can->cd(2+1+5); leg2->Draw();

      if(iw==3){      
      can->cd(iw+5+1);
      tex=new TLatex(2.9,0.0235*0.88*1.275*1.3*66,"20-60%");
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
   tex->Draw();
   TLatex *   tex = new TLatex(0.24,0.963,"|#eta|<0.8");
   tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.038);
   tex->SetLineWidth(2);
   tex->Draw();

  cout << "end of process" << endl;
  can->cd();
  can->Print("./figures/plot_chipt_5panels_linYNew.png");
  can->Print("./figures/plot_chipt_5panels_linYNew.pdf");
  //can->Print("./figures/plot_chipt_5panels_linY.gif");
}

