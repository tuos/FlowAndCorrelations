{

  gROOT->Reset();
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1);
  TFile* infile = new TFile("mergedOuttreefile_ampt.root");
  TH1D* hb = new TH1D("hb","",25000,0.,25);
  TTree* tree = infile->Get("ana/hi");
  tree->Draw("b>>hb","","GOFF");

  long int nCounts=0;
  int iBin10=0;
  int iBin20=0;
  int iBin30=0;
  int iBin40=0;
  int iBin50=0;
  int iBin60=0;
  int iBin70=0;
  int iBin80=0;
  int iBin90=0;
  int iBin100=1;

  ofstream outfile;
  outfile.open("bAsCent.txt");
  for(int i=1; i<=hb->GetNbinsX(); i++){
    nCounts=nCounts+hb->GetBinContent(i);
    if(nCounts>=(0.1*hb->GetEntries())&&iBin10==0){
      iBin10=i;
      cout<<"10  "<<hb->GetBinCenter(iBin10)<<endl;
      outfile<<hb->GetBinCenter(iBin10)<<", ";
    }
    if(nCounts>=(0.2*hb->GetEntries())&&iBin20==0){
      iBin20=i;
      cout<<"20  "<<hb->GetBinCenter(iBin20)<<endl;
      outfile<<hb->GetBinCenter(iBin20)<<", ";
    }
    if(nCounts>=(0.3*hb->GetEntries())&&iBin30==0){
      iBin30=i;
      cout<<"30  "<<hb->GetBinCenter(iBin30)<<endl;
      outfile<<hb->GetBinCenter(iBin30)<<", ";
    }
    if(nCounts>=(0.4*hb->GetEntries())&&iBin40==0){
      iBin40=i;
      cout<<"40  "<<hb->GetBinCenter(iBin40)<<endl;
      outfile<<hb->GetBinCenter(iBin40)<<", ";
    }
    if(nCounts>=(0.5*hb->GetEntries())&&iBin50==0){
      iBin50=i;
      cout<<"50  "<<hb->GetBinCenter(iBin50)<<endl;
      outfile<<hb->GetBinCenter(iBin50)<<", ";
    }
    if(nCounts>=(0.6*hb->GetEntries())&&iBin60==0){
      iBin60=i;
      cout<<"60  "<<hb->GetBinCenter(iBin60)<<endl;
      outfile<<hb->GetBinCenter(iBin60)<<", ";
    }
    if(nCounts>=(0.7*hb->GetEntries())&&iBin70==0){
      iBin70=i;
      cout<<"70  "<<hb->GetBinCenter(iBin70)<<endl;
      outfile<<hb->GetBinCenter(iBin70)<<", ";
    }
    if(nCounts>=(0.8*hb->GetEntries())&&iBin80==0){
      iBin80=i;
      cout<<"80  "<<hb->GetBinCenter(iBin80)<<endl;
      outfile<<hb->GetBinCenter(iBin80)<<", ";
    }
    if(nCounts>=(0.9*hb->GetEntries())&&iBin90==0){
      iBin90=i;
      cout<<"90  "<<hb->GetBinCenter(iBin90)<<endl;
      outfile<<hb->GetBinCenter(iBin90)<<", ";
    }
  }  
    cout<<"100  "<<30<<endl;
      outfile<<"30"<<endl;
      //outfile<<"5,      "<<"10,     "<<"20,     "<<"30,     "<<"40,     "<<"50,     "<<"60,     "<<"100"<<endl;


  TCanvas* cd = new TCanvas("cd","",600,500);
  cd->SetLeftMargin(0.12);
  cd->SetRightMargin(0.02);
  cd->SetTopMargin(0.02);
  cd->SetBottomMargin(0.12);
  cd->SetTicks(1);
   
  hb->Draw("pez");
    TLatex *tex1= new TLatex(-1.6,1000.305,"AMPT, 5TeV PbPb, b=0fm");
    tex1->SetTextColor(1);
    tex1->SetTextSize(0.05);
    tex1->SetTextFont(62);
    //tex1->Draw();


}

