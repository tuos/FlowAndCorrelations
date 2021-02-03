void get_txt_toymodel(){
    
    TFile *eventFile = new TFile("/store/user/tuos/healpy/toyModel/steg10_m2000_flow08/steg10kevts_m2000_jbMerged.root","read");
    TTree *tree = (TTree*)eventFile->Get("tree");
    	
    Float_t pt[244002];
    Float_t eta[244002];
    Float_t phi[244002];
    int nParticles=0;
    int nEvents;
    int cent = 0;
    int nEventCent=0;
    int nEventCentIndex=0;

    tree->SetBranchAddress("n", &nParticles);
    tree->SetBranchAddress("ptg", &pt);
    tree->SetBranchAddress("etag", &eta);
    tree->SetBranchAddress("phig", &phi);

    nEvents=tree->GetEntries();
    //nEvents=300;

    ofstream outputFile;
    outputFile.open(Form("/store/user/tuos/healpy/toyModel/steg10_m2000_flow08/txt_toyModel_10kevts_m2000_08flow.txt"));
    outputFile<<nEvents<<endl;
    for(int i=0; i<nEvents; i++){
      if(i%20==0)  cout<<"Have run "<<i<<" of all the "<<nEvents<<" events; "<<endl;
      tree->GetEntry(i);

      outputFile<<nEventCentIndex<<"   " << nParticles<<"   "<< cent << endl;
      for(int k=0; k<nParticles; k++){
        //outputFile<<eta[k]<<"   "<<phi[k]<<endl;
        outputFile<<2*TMath::ATan(exp(-eta[k]))<<"   "<<phi[k]<<endl;
        //outputFile<<pt[k]<<"   "<<2*TMath::ATan(exp(-eta[k]))<<"   "<<phi[k]<<endl;
      }

      nEventCentIndex = nEventCentIndex+1;

    }

}

