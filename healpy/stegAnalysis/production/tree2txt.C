void tree2txt(){

    TFile *eventFile = new TFile("./steg10_m2000_prod.root","read");
    TTree *tree = (TTree*)eventFile->Get("tree");
 
    Float_t pt[20000];
    Float_t eta[20000];
    Float_t phi[20000];
    int nParticles=0;
    int nEvents;

    tree->SetBranchAddress("n", &nParticles);
    tree->SetBranchAddress("ptg", &pt);
    tree->SetBranchAddress("etag", &eta);
    tree->SetBranchAddress("phig", &phi);

    ofstream outputFile;
    outputFile.open("eventFile2.txt");
    nEvents=tree->GetEntries();
    for(int i=0; i<nEvents; i++){
      if(i%2==0)  cout<<"Have run "<<i<<" of all the "<<nEvents<<" events; "<<endl;
      tree->GetEntry(i);
      //outputFile<<i<<"   "<<nParticles<<endl;
      for(int j=0; j<nParticles; j++){
        //outputFile<<pt[j]<<"   "<<eta[j]<<"   "<<phi[j]<<endl;
        outputFile<<pt[j]<<"   "<<2*TMath::ATan(exp(-eta[j]))<<"   "<<phi[j]<<endl;
      }

    }

}

