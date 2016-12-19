{
   TCanvas *c1 = new TCanvas("c1", "Test",4,18,500,500);
   TBox *box1 = new TBox(0.3,0.3,0.4,0.4);
   box1->SetFillColor(16);
   box1->SetFillStyle(4050);
   box1->Draw();
   TBox *box2 = new TBox(0.5,0.5,0.6,0.6);
   box2->SetFillStyle(1001);
   box2->SetFillColor(4);
   box2->SetLineColor(2);
   //box2->SetLineWidth(2);
   box2->Draw();
}
