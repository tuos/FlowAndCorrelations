void plot_c24_six_panels_3sub(){
  
  const int nMultBin=17;
  double tmp;

  double cov_1[nMultBin];
  double cove_1[nMultBin];
  double rho_1[nMultBin];
  double rhoe_1[nMultBin];
  double Nch_1[nMultBin];
  double cov_2[nMultBin];
  double cove_2[nMultBin];
  double rho_2[nMultBin];
  double rhoe_2[nMultBin];
  double Nch_2[nMultBin];
  double cov_3[nMultBin];
  double cove_3[nMultBin];
  double rho_3[nMultBin];
  double rhoe_3[nMultBin];
  double Nch_3[nMultBin];
  double cov_4[nMultBin];
  double cove_4[nMultBin];
  double rho_4[nMultBin];
  double rhoe_4[nMultBin];
  double Nch_4[nMultBin];

  ifstream in1;
  in1.open("./outputTEXT_c2_4_allsub_2B.txt");
  if(!in1.good())    cout<<" input fail"<<endl;
  else cout<<" input OK! "<<endl;
  float test=0;
  for(int i=0;i<nMultBin;i++){
    in1>>Nch_1[i]; in1>>cov_1[i]; in1>>cove_1[i]; in1>>rho_1[i]; in1>>rhoe_1[i];
    in1>>Nch_2[i]; in1>>cov_2[i]; in1>>cove_2[i]; in1>>rho_2[i]; in1>>rhoe_2[i];
    in1>>Nch_3[i]; in1>>cov_3[i]; in1>>cove_3[i]; in1>>rho_3[i]; in1>>rhoe_3[i];
    in1>>Nch_4[i]; in1>>cov_4[i]; in1>>cove_4[i]; in1>>rho_4[i]; in1>>rhoe_4[i];

  }


/////////////////////////////////////
 TH1D* hist = new TH1D("hist","",139,0.,139.);
 hist->SetXTitle("N_{ch}");


 hist->GetYaxis()->SetNdivisions(505);
 hist->GetXaxis()->CenterTitle(1);
 hist->GetYaxis()->CenterTitle(1);
 hist->GetYaxis()->SetTitleOffset(1.15);
 hist->GetXaxis()->SetTitleOffset(0.95);
 hist->GetXaxis()->SetTitleSize(0.066);
 hist->GetYaxis()->SetTitleSize(0.066);
 hist->GetXaxis()->SetLabelSize(0.05);
 hist->GetYaxis()->SetLabelSize(0.05);

        TCanvas *c1 = new TCanvas("c1","c1",1.5*2*350,2*350);
        //TCanvas *c1 = new TCanvas("c1","c1",1.1*2*350,2*350);
        c1->Divide(2,2);
        gStyle->SetOptStat(0);

        c1->cd(1);
        gPad->SetTopMargin(0.06);
        gPad->SetBottomMargin(0.15);
        gPad->SetLeftMargin(0.17);
        gPad->SetRightMargin(0.02);
        gPad->SetTicks(-1);
        TH1D *hist1=(TH1D*)hist->Clone();
        hist1->SetYTitle("cov(c_{2}{4}, [p_{T}])");
        hist1->GetYaxis()->SetTitleOffset(1.35);
        hist1->SetMinimum(-0.0017);
        hist1->SetMaximum(0.00013);
        hist1->Draw();
  TGraphErrors *gra1 = new TGraphErrors(nMultBin,Nch_1,cov_1,0,cove_1);
  gra1->SetTitle("");
  gra1->SetMarkerStyle(24);
  gra1->SetMarkerSize(1);
  gra1->SetMarkerColor(8);
  gra1->SetLineWidth(2);
  gra1->SetLineColor(8);
  gra1->Draw("psameez");

  TGraphErrors *gra2 = new TGraphErrors(nMultBin,Nch_2,cov_2,0,cove_2);
  gra2->SetTitle("");
  gra2->SetMarkerStyle(25);
  gra2->SetMarkerSize(1);
  gra2->SetMarkerColor(4);
  gra2->SetLineWidth(2);
  gra2->SetLineColor(4);
  gra2->Draw("psameez");

  TGraphErrors *gra3 = new TGraphErrors(nMultBin,Nch_3,cov_3,0,cove_3);
  gra3->SetTitle("");
  gra3->SetMarkerStyle(20);
  gra3->SetMarkerSize(1);
  gra3->SetMarkerColor(2);
  gra3->SetLineWidth(2);
  gra3->SetLineColor(2);
  gra3->Draw("psameez");

  TGraphErrors *gra4 = new TGraphErrors(nMultBin,Nch_4,cov_4,0,cove_4);
  gra4->SetTitle("");
  gra4->SetMarkerStyle(21);
  gra4->SetMarkerSize(1);
  gra4->SetMarkerColor(1);
  gra4->SetLineWidth(2);
  gra4->SetLineColor(1);
  gra4->Draw("psameez");

        TLatex *tex = new TLatex(73,-0.0003,"PYTHIA8 13 TeV");
        tex->SetTextSize(0.07);
        tex->SetLineWidth(1);
        tex->SetTextFont(42);
        tex->Draw();
        tex = new TLatex(73,-0.0005,"0.3 < p_{T} < 2 GeV");
        tex->SetTextSize(0.07);
        tex->SetLineWidth(1);
        tex->SetTextFont(42);
        tex->Draw();
        tex = new TLatex(40,-0.0015,"c_{2}{4} from 3-subevent");
        tex->SetTextSize(0.05);
        tex->SetLineWidth(2);
        tex->SetTextFont(42);
        //tex->Draw();

    TLegend *leg = new TLegend(0.58,0.25,0.82,0.55);
    leg->SetFillColor(10);
    leg->SetBorderSize(0);
    leg->SetTextFont(42);
    leg->SetTextColor(1);
    leg->SetTextSize(0.07);
    leg->AddEntry(gra1,"Standard","pl");
    leg->AddEntry(gra2,"Two subevents","pl");
    leg->AddEntry(gra3,"Three subevents","pl");
    leg->AddEntry(gra4,"Four subevents","pl");
    leg->Draw();



        c1->cd(2);
        gPad->SetTopMargin(0.06);
        gPad->SetBottomMargin(0.15);
        gPad->SetLeftMargin(0.15);
        gPad->SetRightMargin(0.02);
        gPad->SetTicks(-1);
        TH1D *hist2=(TH1D*)hist->Clone();
        hist2->SetYTitle("cov(c_{2}{4}, [p_{T}])");
        hist2->SetMinimum(-0.00001);
        hist2->SetMaximum(0.00002);
        hist2->Draw();
  TGraphErrors *grb1 = new TGraphErrors(nMultBin,Nch_1,cov_1,0,cove_1);
  grb1->SetTitle("");
  grb1->SetMarkerStyle(24);
  grb1->SetMarkerSize(1);
  grb1->SetMarkerColor(8);
  grb1->SetLineWidth(2);
  grb1->SetLineColor(8);
  grb1->Draw("psameez");

  TGraphErrors *grb2 = new TGraphErrors(nMultBin,Nch_2,cov_2,0,cove_2);
  grb2->SetTitle("");
  grb2->SetMarkerStyle(25);
  grb2->SetMarkerSize(1);
  grb2->SetMarkerColor(4);
  grb2->SetLineWidth(2);
  grb2->SetLineColor(4);
  grb2->Draw("psameez");

  TGraphErrors *grb3 = new TGraphErrors(nMultBin,Nch_3,cov_3,0,cove_3);
  grb3->SetTitle("");
  grb3->SetMarkerStyle(20);
  grb3->SetMarkerSize(1);
  grb3->SetMarkerColor(2);
  grb3->SetLineWidth(2);
  grb3->SetLineColor(2);
  grb3->Draw("psameez");

  TGraphErrors *grb4 = new TGraphErrors(nMultBin,Nch_4,cov_4,0,cove_4);
  grb4->SetTitle("");
  grb4->SetMarkerStyle(21);
  grb4->SetMarkerSize(1);
  grb4->SetMarkerColor(1);
  grb4->SetLineWidth(2);
  grb4->SetLineColor(1);
  grb4->Draw("psameez");

        tex = new TLatex(10,0.000016,"Zoom in");
        tex->SetTextSize(0.07);
        tex->SetLineWidth(1);
        tex->SetTextFont(42);
        tex->Draw();


        c1->cd(3);
        gPad->SetTopMargin(0.06);
        gPad->SetBottomMargin(0.15);
        gPad->SetLeftMargin(0.17);
        gPad->SetRightMargin(0.02);
        gPad->SetTicks(-1);
        TH1D *hist3=(TH1D*)hist->Clone();
        hist3->SetYTitle("#rho(c_{2}{4}, [p_{T}])");
        hist3->GetYaxis()->SetTitleOffset(1.35);
        hist3->SetMinimum(-0.1);
        hist3->SetMaximum(0.1);
        hist3->Draw();
  TGraphErrors *grc1 = new TGraphErrors(nMultBin,Nch_1,rho_1,0,rhoe_1);
  grc1->SetTitle("");
  grc1->SetMarkerStyle(24);
  grc1->SetMarkerSize(1);
  grc1->SetMarkerColor(8);
  grc1->SetLineWidth(2);
  grc1->SetLineColor(8);
  grc1->Draw("psameez");

  TGraphErrors *grc2 = new TGraphErrors(nMultBin,Nch_2,rho_2,0,rhoe_2);
  grc2->SetTitle("");
  grc2->SetMarkerStyle(25);
  grc2->SetMarkerSize(1);
  grc2->SetMarkerColor(4);
  grc2->SetLineWidth(2);
  grc2->SetLineColor(4);
  grc2->Draw("psameez");

  TGraphErrors *grc3 = new TGraphErrors(nMultBin,Nch_3,rho_3,0,rhoe_3);
  grc3->SetTitle("");
  grc3->SetMarkerStyle(20);
  grc3->SetMarkerSize(1);
  grc3->SetMarkerColor(2);
  grc3->SetLineWidth(2);
  grc3->SetLineColor(2);
  grc3->Draw("psameez");

  TGraphErrors *grc4 = new TGraphErrors(nMultBin,Nch_4,rho_4,0,rhoe_4);
  grc4->SetTitle("");
  grc4->SetMarkerStyle(21);
  grc4->SetMarkerSize(1);
  grc4->SetMarkerColor(1);
  grc4->SetLineWidth(2);
  grc4->SetLineColor(1);
  grc4->Draw("psameez");

        //tex = new TLatex(50,-0.084,"#sqrt{Var(c_{2}#{}{4})} from GetRMS()");
        tex = new TLatex(10,0.075,"Var(c_{2}#{}{4}) and Var([p_{T}]) are not dynamic");
        tex->SetTextSize(0.07);
        tex->SetLineWidth(1);
        tex->SetTextFont(42);
        tex->Draw();

        c1->cd(4);
        gPad->SetTopMargin(0.06);
        gPad->SetBottomMargin(0.15);
        gPad->SetLeftMargin(0.15);
        gPad->SetRightMargin(0.02);
        gPad->SetTicks(-1);
        TH1D *hist4=(TH1D*)hist->Clone();
        hist4->SetYTitle("#rho(c_{2}{4}, [p_{T}])");
        hist4->SetMinimum(-0.003);
        hist4->SetMaximum(0.003);
        hist4->Draw();
  TGraphErrors *grd1 = new TGraphErrors(nMultBin,Nch_1,rho_1,0,rhoe_1);
  grd1->SetTitle("");
  grd1->SetMarkerStyle(24);
  grd1->SetMarkerSize(1);
  grd1->SetMarkerColor(8);
  grd1->SetLineWidth(2);
  grd1->SetLineColor(8);
  grd1->Draw("psameez");

  TGraphErrors *grd2 = new TGraphErrors(nMultBin,Nch_2,rho_2,0,rhoe_2);
  grd2->SetTitle("");
  grd2->SetMarkerStyle(25);
  grd2->SetMarkerSize(1);
  grd2->SetMarkerColor(4);
  grd2->SetLineWidth(2);
  grd2->SetLineColor(4);
  grd2->Draw("psameez");

  TGraphErrors *grd3 = new TGraphErrors(nMultBin,Nch_3,rho_3,0,rhoe_3);
  grd3->SetTitle("");
  grd3->SetMarkerStyle(20);
  grd3->SetMarkerSize(1);
  grd3->SetMarkerColor(2);
  grd3->SetLineWidth(2);
  grd3->SetLineColor(2);
  grd3->Draw("psameez");

  TGraphErrors *grd4 = new TGraphErrors(nMultBin,Nch_4,rho_4,0,rhoe_4);
  grd4->SetTitle("");
  grd4->SetMarkerStyle(21);
  grd4->SetMarkerSize(1);
  grd4->SetMarkerColor(1);
  grd4->SetLineWidth(2);
  grd4->SetLineColor(1);
  grd4->Draw("psameez");

        tex = new TLatex(10,0.0022,"Zoom in");
        tex->SetTextSize(0.07);
        tex->SetLineWidth(1);
        tex->SetTextFont(42);
        tex->Draw();
        tex = new TLatex(10,-0.0025,"#sqrt{Var(c_{2}#{}{4})} from GetRMS()");
        tex->SetTextSize(0.07);
        tex->SetLineWidth(1);
        tex->SetTextFont(42);
        //tex->Draw();

  c1->Print("fig_06.png");
  c1->Print("fig_06.pdf");


}
