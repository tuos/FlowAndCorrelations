
#include "TMinuit.h"
#include "TString.h"
#include "TDatime.h"
#include "TGraph.h"
#include "TAxis.h"
#include "TCanvas.h"

    const char *f1 = "K0s_mult130-inf_pp_7000GeV.txt";   //Data File Array
    const char *f2 = "Lambda_mult130-inf_pp_7000GeV.txt";
    //const char *f4 = "K0s_mult220-260_pPb_5020GeV.txt"; 
    //const char *f5 = "Lambda_mult220-260_pPb_5020GeV.txt";
    //const char *f7 = "K0s_mult220-260_PbPb_2760GeV.txt";
    //const char *f8 = "Lambda_mult220-260_PbPb_2760GeV.txt";

int linenumber = 0;
Float_t x1ks[30], y1ks[30], ey1ks[30];
Float_t x1la[30], y1la[30], ey1la[30];
Float_t x2ks[30], y2ks[30], ey2ks[30];
Float_t x2la[30], y2la[30], ey2la[30];
Float_t x3ks[30], y3ks[30], ey3ks[30];
Float_t x3la[30], y3la[30], ey3la[30];


//______________________________________________________________________________
double getChi2;
int getNdf;

const double R = 1.0;
const double dr = 1e-2; // FIXME

double integral(double beta_T, double T, double n, double pt, double mt)
{
  
  double s = 0.;
  for(double r = dr/2; r < R; r += dr)
  {
    double beta_r = (beta_T*(n+2)/2) * TMath::Power((r/R),n);
    //double beta_r = (beta_T*(n+2)/6) * TMath::Power((r/R),n);
    double rho = TMath::ATanH(beta_r);

    s += r * dr * TMath::BesselK1((mt*cosh(rho))/T) * TMath::BesselI0((pt*sinh(rho))/T);
    //s += r * dr * sin((mt*cosh(rho))*T) * cos((pt*sinh(rho))*T);
  }

  return s;
}

//______________________________________________________________________________
void function(int &npar, double *gin, double &f, double *par, int flag)
{
  double aka    = par[0];
  double aka1   = par[4];
  double T      = par[2];
  double beta_T = par[1];
  double n = par[3];

  double chi2 = 0.;

  for(int i = 0; i < 14; i++)
  //for(int i = 5; i < 10; i++)
  {
    double m = 0.497;

    double pt = x1ks[i];
    double mt = sqrt(m*m + pt*pt);

    double a = 0.;
    a = aka;
  
    double theo = a * mt * integral(beta_T, T, n, pt, mt);
    double q = (y1ks[i] - theo)/ey1ks[i];

    chi2 += q*q;

    //cout<<"pt = "<<x1ks[i]<<" ; y1ks = "<<y1ks[i]<<" ;  ey1ks = "<<ey1ks[i]<<endl;
    //cout<<"pt = "<<x1ks[i]<<" ; theo = "<<theo<<endl;
  }

  for(int i = 0; i < 12; i++){
  //for(int i = 5; i < 10; i++){

    double m1 = 1.115;

    double pt1 = x1la[i];
    double mt1 = sqrt(m1*m1 + pt1*pt1);

    double a1 = 0.;
    a1 = aka1;

    double theo1 = a1 * mt1 * integral(beta_T,T,n,pt1,mt1);
    double q1 = (y1la[i]-theo1)/ey1la[i];

    chi2 += q1*q1;
  }

  f = chi2;

//  getChi2 = f;
//  getNdf  = 14 + 12 - 5 - 1;

  //getNdf  = 14 - 5 - 1;
  //getNdf  = 5 + 5 - 5 - 1;
}
//______________________________________________________________________________
void blastwave()
{

std::ifstream ifs1(f1, std::ifstream::in);           //K0s 130-inf pp Data File
    
    Double_t x1, y1, ey1;
    
    TGraphErrors *g1 = new TGraphErrors();
    g1->SetName("g1");
    
    
        int i=0;
    while(ifs1 >> x1 >> y1 >> ey1)
    {
      //g1->SetPoint(g1->GetN(), x1, y1);
      //g1->SetPointError(linenumber, 0, ey1);
      //linenumber++ ;
        //int i=0;
        x1ks[i]=x1;
        y1ks[i]=y1;
        ey1ks[i]=ey1;
        //cout<<"x1ks = "<<x1ks[i]<<"   y1ks = "<<y1ks[i]<<"  ey1ks = "<<ey1ks[i]<<endl;
        //cout<<ey1ks[i]<<", ";
        i++;
    }
   
std::ifstream ifs2(f2, std::ifstream::in);           //Lambda 130-inf pp Data File
    
    Double_t x2, y2, ey2;
    
    TGraphErrors *g2 = new TGraphErrors();
    g2->SetName("g2");
    
    i =0;
    while(ifs2 >> x2 >> y2 >> ey2)
    {
      //g2->SetPoint(g2->GetN(), x2, y2);
      //g2->SetPointError(linenumber, 0, ey2);
      //linenumber++ ;
        x1la[i]=x2;
        y1la[i]=y2;
        ey1la[i]=ey2;
        //cout<<"x1la = "<<x1la[i]<<"   y1la = "<<y1la[i]<<"  ey1la = "<<ey1la[i]<<endl;
        //cout<<ey1la[i]<<", ";
        i++;
    }
    
    double beta_T,Tkin,aka,aka1,n;
    double ebeta_T,eTkin,eaka,eaka1,en;
    
      TMinuit * gMinuit;
      gMinuit = new TMinuit(5);

      //set the function to minimize with minuit;
      gMinuit->SetFCN(function);

      double arglist[10];
      //arglist[0] = 5000;
      //arglist[1] = 1;
      arglist[0] = 1;
      Int_t ierflg = 0;

      gMinuit->mnexcm("SET ERR", arglist, 1, ierflg);
/*
      gMinuit->mnparm(0, "aka",    100,    0.1,   1,    10000, ierflg);
      gMinuit->mnparm(1, "beta_T", 0.3,   0.001,  0.005, 1.0,   ierflg);
      gMinuit->mnparm(2, "Tkin",   0.16,  0.001,  0.1, 10.0,   ierflg);
      gMinuit->mnparm(3, "n",      1.0,   0.01,  0.1,  10.0,  ierflg);
      gMinuit->mnparm(4, "aka1",   100,    0.1,   1,    10000, ierflg);
*/

      gMinuit->mnparm(0, "aka",    10,    0.1,   0,    0, ierflg);
      gMinuit->mnparm(1, "beta_T", 0.3,   0.001,  0, 0,   ierflg);
      gMinuit->mnparm(2, "Tkin",   0.16,  0.001,  0.001, 10,   ierflg);
      gMinuit->mnparm(3, "n",      1.0,   0.01,  0,  0,  ierflg);
      gMinuit->mnparm(4, "aka1",   1,    0.1,   0,   0, ierflg);

      arglist[0] = 500;
      arglist[1] = 1.;

      gMinuit->mnexcm("MIGRAD",    arglist,  2,   ierflg);
      //gMinuit->mnexcm("MINOS",     arglist,  1,   ierflg);
      //gMinuit->mnexcm("CALL FCN",  arglist,  1,   ierflg);

      //gMinuit->mnexcm("HESSE",     arglist,  1,   0);

   Double_t amin,edm,errdef;
   Int_t nvpar,nparx,icstat;
   gMinuit->mnstat(amin,edm,errdef,nvpar,nparx,icstat);

/*
      gMinuit->GetParameter(0, aka,    eaka);
      gMinuit->GetParameter(1, beta_T, ebeta_T);
      gMinuit->GetParameter(2, Tkin,   eTkin);
      gMinuit->GetParameter(3, n,      en);
      gMinuit->GetParameter(4, aka1,   eaka1);

      //gMinuit->SetErrorDef(1);
      //test = (TGraph*)gMinuit->Contour(100,1,2);
      //test->SetFillColor(42);
     
      cout<<"beta_T = "<<beta_T<<"   "<<"Tkin = "<<Tkin<<endl;
      cout<<"ebeta_T = "<<ebeta_T<<"   "<<"eTkin = "<<eTkin<<endl;
*/
     
}
