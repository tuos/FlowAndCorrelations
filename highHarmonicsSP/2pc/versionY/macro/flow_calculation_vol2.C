//this file is made by development of correlation_function_c2.C file
#include <math.h>
#include "TH1D.h"
#include "TH1F.h"
#include "TH2D.h"
#include <vector>
/*
 #include "TF1."
 #include "TH1F.h"
 #include <cstdlib>
 #include <iostream>
 #include "TCanvas.h"
 #include "TError.h"
 #include "TPad.h"
 #include "TString.h"
 #include "TRandom3.h"
 */
#include "TFile.h"
#include "TCanvas.h"
#include "Riostream.h"
#include "TROOT.h"
#include "TMath.h"
#include "TF1.h"
#include "TString.h"
void flow_calculation_vol2(){
   
        Double_t c;
	Double_t c1,c2,c3=0.;
	double error_bar=0.;


	TCanvas *MyC = new TCanvas("bas","",0, 0, 1000, 600);

	
	TString hist_bg="background_pt_20_30_cent_30_40";//   "background_all";
	TString hist_signal="signal_pt_20_30_cent_30_40";
	TString hist_pT="pT";
	
	int centmin=60;
	int centmax=70;
	int pttrigmin=10;
	int pttrigmax=30;
	double centBinMin, centBinMax;
	centBinMin = centmin/2.5; centBinMax= centmax/2.5;	
	
	int nfile=1;
        Float_t pt[17]={0.351362, 0.449742, 0.549246, 0.69504, 0.894686,1.12, 1.37, 1.71, 2.21, 2.72, 3.22, 3.72, 4.40, 5.42, 6.44, 7.45, 8.82};
	
	float ptassmin[]={.3,.4,.5,.6,.8,1.0,1.25,1.5,2.0,2.5,3.0,3.5,4.,5.,6.,7.,8.0}; //, 
	float ptassmax[]={.4,.5,.6,.8,1.,1.25,1.5,2.0,2.5,3.0,3.5,4.0,5.,6.,7.,8.,10.}; 
//	float ptassmin[]={1.0,2.0,3.0,4.,6.}; //, 
//	float ptassmax[]={2.0,3.0,4.0,6.,8.}; 
	int ptf1=3, ptf2=100;
	int nbins=17;
        char cuts[20] ="nominal";

		
	
//	float ptassmin[]={2.0,2.5,3.0,3.5};//{6,8.};//{4.0,5};//{2.5};//{2.0};//{1.2,1.6};//{1.};//{6,8.};//
//	float ptassmax[]={2.5,3.0,3.5,4.0};//{8,10};//{5.0,6};//{3.0};//{2.5};//{1.6,2.0};//{1.2};//{8,10};//

//	TFile* hfile=new TFile(Form("../effMinBias/output_pt_XeXe_MinBias1_10.root",centmin,centmax));	
//	TFile* work_reff=new TFile(Form("../effMinBias/output_reff_XeXe_MinBias1_5.root",centmin,centmax));	
	TFile* hfile=new TFile(Form("./output_pt_XeXeMinBias.root",centmin,centmax));	
	TFile* work_reff=new TFile(Form("./output_reff_XeXeMinBias.root",centmin,centmax));	
	
	TDirectoryFile* work = (TDirectoryFile*)hfile->Get("BigFlow");  
//	TDirectoryFile* work_reff = (TDirectoryFile*)hfile_reff->Get("demo");  
	
	
	TFile *output = new TFile(Form("2D_cent_%d_%d.root",centmin,centmax), "recreate");	

	TH3D* hist_trigger3D = (TH3D*)work->Get(Form("hcorr3D"));
	hist_trigger3D->GetZaxis()->SetRangeUser(centmin*2,centmax*2);
	hist_trigger3D->GetYaxis()->SetRangeUser(pttrigmin,pttrigmax*2);

	TH1D* hist_trigger;// = (TH1F*)work_reff->Get(Form("Trigger_all"));
	hist_trigger = (TH1D*)hist_trigger3D->ProjectionY("Trigger_all");
	int ptint, ptint1;

	double V[7][18], Ve[7][18];
	double er_long[31];

        std::vector<TH3D*> signal3D;
        std::vector<TH3D*> background3D;
        std::vector<TH2D*> signal1;
        std::vector<TH2D*> background1;
        std::vector<TH1D*> dphi_bg;
	std::vector<TH1D*> dphi_signal;
        signal3D.resize(nbins+1);
        background3D.resize(nbins+1);
        signal1.resize(nbins+1);
        background1.resize(nbins+1);
	dphi_signal.resize(nbins+1);
	dphi_bg.resize(nbins+1);

        signal3D[0] = (TH3D*)work_reff->Get(Form("signal_trig_%d_%d_ass_%d_%d",pttrigmin,pttrigmax,pttrigmin,pttrigmax));
        background3D[0] = (TH3D*)work_reff->Get(Form("beckground_trig_%d_%d_ass_%d_%d",pttrigmin,pttrigmax,pttrigmin,pttrigmax));
	cout << "radi "<<endl;

        for (Int_t i=1; i<nbins+1; i++) {
              ptint=ptassmin[i-1]*10;
              ptint1=ptassmax[i-1]*10;
              signal3D[i] = (TH3D*)work->Get(Form("signal_trig_%d_%d_ass_%d_%d",pttrigmin,pttrigmax,ptint,ptint1));
              background3D[i] = (TH3D*)work->Get(Form("beckground_trig_%d_%d_ass_%d_%d",pttrigmin,pttrigmax,ptint,ptint1));
        }


        for (Int_t i=0; i<nbins+1; i++) {
	      signal3D[i]->GetZaxis()->SetRangeUser(centBinMin,centBinMax);
	      background3D[i]->GetZaxis()->SetRangeUser(centBinMin,centBinMax);
              signal1[i] = (TH2D*)signal3D[i]->Project3D("yx");
              background1[i] = (TH2D*)background3D[i]->Project3D("yx");
        }


	






	for (int i=1; i<1001; i++) {

	      c3+= hist_trigger->GetBinContent(i);

	}



	
	TF1* Fourier = new TF1("Fourier","[0]*(1.0+2.0*[1]*cos(x)+2.0*[2]*cos(2.0*x)+2.0*[3]*cos(3.0*x)+2.0*[4]*cos(4.0*x)+2.0*[5]*cos(5.0*x)+2.0*[6]*cos(6.0*x)+2.0*[7]*cos(7.0*x))",0,3.1416);//+2.0*[6]*cos(6.0*x)+2.0*[7]*cos(7.0*x)+2.0*[8]*cos(8.0*x)+2.0*[9]*cos(9.0*x)+2.0*[10]*cos(10.0*x)+2.0*[11]*cos(11.0*x)+2.0*[12]*cos(12.0*x)+2.0*[13]*cos(13.0*x)+2.0*[14]*cos(14.0*x)+2.0*[15]*cos(15.0*x))",-1.5708,4.712389);
	
//	TF1* Fourier = new TF1("Fourier","[0]*(1+2*[1]*cos(x)+2*[2]*cos(2*x)+2*[3]*cos(3*x)+2*[4]*cos(4*x)+2*[5]*cos(5*x))+[6]*exp(-(x*x)/(2.0*[7]*[7]))/([7]*sqrt(2*3.145927))+[8]*exp(-((x-3.1415927)*(x-3.1415927))/(2.0*[9]*[9]))/([9]*sqrt(2*3.145927))",-1.5708,4.712389);
	
//	Fourier->SetParameter(00, 0.00001);
//	Fourier->SetParameter(01,0.00001);
//	Fourier->SetParameter(02,0.00001);
//	Fourier->SetParameter(03,0.00001);
//	Fourier->SetParameter(04,0.00001);
//	Fourier->SetParameter(05,0.00001);
//	Fourier->SetParameter(06,0.00001);
//	Fourier->SetParameter(07,0.30001);
//	Fourier->SetParameter(09,0.50001);	
	
//	Fourier->SetParLimits(01,0.0,1.0);
//	Fourier->SetParLimits(02,0.0,1.0);
//	Fourier->SetParLimits(03,0.0,0.1);
//	Fourier->SetParLimits(04,0.0,1.0);
//	Fourier->SetParLimits(05,0.0068,.007);
//	Fourier->SetParLimits(6,0.0,100.0);
//	Fourier->SetParLimits(7,0.0,13.0);
//	Fourier->SetParLimits(8,0.0,100.0);
//	Fourier->SetParLimits(9,0.0,13.0);
//	Fourier->SetParLimits(6,0.0,1.0);
	

	TH1D* hist_dphi_signal1;
	TH1D* hist_dphi_bg;

	ofstream fout2(Form("v2_cent_%d_%d_XeXe.txt",centmin,centmax));
	ofstream fout3(Form("v3_cent_%d_%d_XeXe.txt",centmin,centmax));
	ofstream fout4(Form("v4_cent_%d_%d_XeXe.txt",centmin,centmax));

        for (Int_t i=0; i<nbins+1; i++) {

			cout << "radi "<<i<<endl;

	      dphi_bg[i] = background1[i]-> ProjectionY(Form("bg_dphi_projekcija_%d",i),4,10);
	      dphi_signal[i] = signal1[i]-> ProjectionY(Form("signal_dphi_projekcija_%d",i),4,10);


		  for (int i_bin=0; i_bin<31; i_bin++) {
			  er_long[i_bin] = sqrt( 1.0/dphi_signal[i]->GetBinContent(i_bin+1) + 1.0/(dphi_bg[i]->GetBinContent(i_bin+1) ));
//			  cout << "greška moja = "<<sqrt(dphi_signal[i]->GetBinContent(i_bin+1))<<" greska default = "<<dphi_signal[i]->GetBinError(i_bin+1)<<endl ;
		  }	
			
			
//	      dphi_signal[i] = hist_dphi_bg1;
	      dphi_signal[i] ->Sumw2();
	
	      dphi_signal[i]->Divide(dphi_bg[i]);

	     cout<<" bin content = "<<dphi_signal[i]->GetBinContent(8)<<" bin error = "<<dphi_signal[i]->GetBinError(8)<<endl;
			
			
	      c= background1[i] -> GetBinContent(background1[i]->FindBin(0,0));
	      c1=background1[i] ->GetYaxis()->GetBinWidth(1);
	      c2=background1[i] ->GetXaxis()->GetBinWidth(1);

	      dphi_signal[i] -> Scale(c/(4.*c1*c2*c3));
	      dphi_signal[i]->Write();		
	      dphi_bg[i]->Write();
	      dphi_signal[i]->Fit("Fourier","RMEI");

			for (int i_bin=0; i_bin<31; i_bin++) {
				er_long[i_bin] = er_long[i_bin]*dphi_signal[i]->GetBinContent(i_bin+1);
//				cout << "greška moja = "<<er_long[i_bin]<<" greska default = "<<dphi_signal[i]->GetBinError(i_bin+1)<<endl ;
			}	
			
			
	      for (int i_n=0; i_n<7;i_n++) {
 		     V[i_n][i]=Fourier->GetParameter(i_n+2);
			 Ve[i_n][i]=Fourier->GetParError(i_n+2);
		     if (i!=0 && V[i_n][0] > 0 && i_n == 0 )  fout2<<pt[i-1]<<" "<<V[i_n][i]/sqrt(V[i_n][0])<<" ";
		     if (i!=0 && V[i_n][0] <= 0 && i_n == 0)  fout2<<pt[i-1]<<" "<<-10<<" ";

		     if (i!=0 && V[i_n][0] > 0 && i_n == 1 )  fout3<<pt[i-1]<<" "<<V[i_n][i]/sqrt(V[i_n][0])<<" ";
		     if (i!=0 && V[i_n][0] <= 0 && i_n == 1)  fout3<<pt[i-1]<<" "<<-10<<" ";

		     if (i!=0 && V[i_n][0] > 0 && i_n == 2 )  fout4<<pt[i-1]<<" "<<V[i_n][i]/sqrt(V[i_n][0])<<" ";
		     if (i!=0 && V[i_n][0] <= 0 && i_n == 2)  fout4<<pt[i-1]<<" "<<-10<<" ";
//			  cout << Fourier->GetParameter(i_n+2)<<" "<<i_n<<" "<<i<<" "<<V[i_n][i]/sqrt(V[i_n][0])<<endl;
		     if (i!=0 && V[i_n][0] > 0  && i_n == 0 )  fout2<<fabs(V[i_n][i])/sqrt(V[i_n][0])*sqrt(fabs(pow(Ve[i_n][i]/(V[i_n][i]),2)) + 0.25*fabs(pow(Ve[i_n][0]/V[i_n][0],2))) <<" ";
		     if (i!=0 && V[i_n][0] <= 0 && i_n == 0 )  fout2<<0<<" ";

		     if (i!=0 && V[i_n][0] > 0  && i_n == 1 )  fout3<<fabs(V[i_n][i])/sqrt(V[i_n][0])*sqrt(fabs(pow(Ve[i_n][i]/(V[i_n][i]),2)) + 0.25*fabs(pow(Ve[i_n][0]/V[i_n][0],2))) <<" ";
		     if (i!=0 && V[i_n][0] <= 0 && i_n == 1 )  fout3<<0<<" ";

		     if (i!=0 && V[i_n][0] > 0  && i_n == 2 )  fout4<<fabs(V[i_n][i])/sqrt(V[i_n][0])*sqrt(fabs(pow(Ve[i_n][i]/(V[i_n][i]),2)) + 0.25*fabs(pow(Ve[i_n][0]/V[i_n][0],2))) <<" ";
		     if (i!=0 && V[i_n][0] <= 0 && i_n == 2 )  fout4<<0<<" ";
			  error_bar=sqrt( pow(Ve[i_n][i]/sqrt(V[i_n][0]),2) + pow(V[i_n][i]*Ve[i_n][0],2)  );// + pow( V[i_n][i]Ve[i_n][0]/sqrt( pow(V[i_n][0],3)) ,2) );			
	      } 
			fout2<<endl; 
			fout3<<endl;
			fout4<<endl;
//	cout << fabs(V[0][1])/sqrt(V[0][0])<<endl;//*sqrt(fabs(pow(Ve[0][1]/(V[0][1]),2)) + 0.25*fabs(pow(Ve[0][0]/V[0][0],2))) <<endl;
	cout << sqrt(0.25*fabs(pow(Ve[0][0]/V[0][0],2))) <<endl;

	}
		
//	cout << "v8 = "<<sqrt(V[6][0])<<" ∂v8 = "<<0.5*Ve[6][0]/sqrt(V[6][0])<<" v6 = "<<sqrt(V[4][0])<<" ∂v6 = "<<0.5*Ve[4][0]/sqrt(V[4][0])<<" v2 = "<<sqrt(V[0][0])<<endl;
	cout << "V8 = "<<V[6][0]<<" ∂v8 = "<<Ve[6][0]<<endl;
	//"  v7/(v2*v2*3) = "<<sqrt(V[5][0]/V[1][0])/V[0][0]<<" v4/(v2*v2) = "<<sqrt(V[2][0])/V[0][0]<<endl;	
	
	Ve[0][1]=pow(V[0][1],3);
	cout << V[0][1]<<" "<<Ve[0][1];
        for (Int_t i=0; i<nbins+1; i++) {
		  signal1[i] -> Divide(background1[i]);

	      c= background1[i] -> GetBinContent(background1[i]->FindBin(0,0));
	      c1=background1[i] ->GetYaxis()->GetBinWidth(1);
	      c2=background1[i] ->GetXaxis()->GetBinWidth(1);

	      signal1[i] -> Scale(c/(4.*c1*c2*c3));
	      signal1[i]->Write();
        }

	for (int i=1; i<32; i++) {
//		cout << dphi_signal[4]->GetBinCenter(i)<<" "<<dphi_signal[4]->GetBinContent(i)<<endl;
	}
	
	
/*
	TH1D* hist_dphi;
	TH1D* hist_dphi1;

	TH1D* hist_dphi_signal;
	TH1D* hist_dphi_signal1;
	TH1D* hist_dphi_bg;

	hist_dphi_signal = hist_dphi_deta_signal-> ProjectionX("x projekcija",4,30);
//	hist_dphi_signal -> Add(hist_dphi_deta_signal->ProjectionX("x projekcija",21,30));

	hist_dphi_signal1 = hist_dphi_deta_signal->ProjectionX("x projekcija",21,30);

	TH1D *hist_dphi_Correlation=(TH1D*)hist_dphi_signal->Clone();	

//	hist_dphi_Correlation -> Add(hist_dphi_signal1,hist_dphi_signal);

	hist_dphi_bg = hist_dphi_deta_bg-> ProjectionX("x projekcija",4,13);
	hist_dphi_bg -> Add(hist_dphi_deta_bg->ProjectionX("x projekcija",21,30));

//	hist_dphi_Correlation->Divide(hist_dphi_signal,hist_dphi_bg);

//	hist_dphi_signal ->Scale(c/(2.*20.*c1*c2*c3))


	hist_dphi = hist_Correlation-> ProjectionX("x projekcija",4,13);
	hist_dphi1 = hist_Correlation-> ProjectionX("x projekcija",21,30);
	hist_dphi->Add(hist_dphi1);
	hist_dphi->Scale(1.0/20.);
	hist_dphi_signal->Draw();

	
//	TH1D* hist_dphi;
	
//	hist_dphi = hist_Correlation-> ProjectionX("x projekcija",14,21);
//	hist_dphi -> Scale(c/(3.47e07*c1*c2));

//	hist_dphi ->Draw();

	TF1* Fourier = new TF1("Fourier","[0]*(1.0+2.0*[1]*cos(x)+2.0*[2]*cos(2.0*x)+2.0*[3]*cos(3.0*x)+2.0*[4]*cos(4.0*x)+2.0*[5]*cos(5.0*x)+2.0*[6]*cos(6.0*x))",-1.5708,4.712389);

	Fourier->SetParameter(00, 0.00001);
	Fourier->SetParameter(01,0.00001);
	Fourier->SetParameter(02,0.00001);
	Fourier->SetParameter(03,0.00001);
	Fourier->SetParameter(04,0.00001);
	Fourier->SetParameter(05,0.00001);
	Fourier->SetParameter(06,0.00001);
	
	Fourier->SetParLimits(01,0.0,1.0);
	Fourier->SetParLimits(02,0.0,1.0);
	Fourier->SetParLimits(03,0.0,0.1);
	Fourier->SetParLimits(04,0.0,1.0);
	Fourier->SetParLimits(05,0.0,1.0);
	Fourier->SetParLimits(06,0.0,1.0);
	// 
*/	
//	hist_dphi->Fit("Fourier", "RME");
	
	
 /*
   Fourier->SetLineWidth(3);
   Fourier->SetLineColor(4);
   Fourier->SetParName(00,"G00");
   Fourier->SetParName(01,"G01");
   Fourier->SetParName(02,"G02");
   Fourier->SetParName(03,"G03");
   Fourier->SetParName(04,"G04");
   Fourier->SetParameter(00, 1.0);
   Fourier->SetParameter(01,0.1);
   Fourier->SetParameter(02,0.1);
   Fourier->SetParameter(03,0.1);
   Fourier->SetParameter(04,0.1);
   Fourier->SetParameter(05,0.1);
	Fourier->SetParameter(06,1.1);
	Fourier->SetParameter(07,0.1);
	Fourier->SetParameter(08,1.1);
	Fourier->SetParameter(09,0.1);
 //  Fourier->SetParameter(10,0.1);



	
	hist_dphi_deta_signal ->Write();
	hist_dphi_deta_bg -> Write();
	hist_Correlation -> Write();
*/	
//	signal1[1]->Draw("surf1");
}
