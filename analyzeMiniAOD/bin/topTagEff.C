#include<TROOT.h>
#include<TFile.h>
#include<vector>
#include<TChain.h>
#include<TCanvas.h>
#include<TH1.h>
#include<TH2.h>
#include<TProfile.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<TLegend.h>
#include<TMath.h>
#include<TStyle.h>

void topTagEff(){
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(0000000000);
  gStyle->SetTitleBorderSize(0);
  //gStyle->SetTitleAlign(0);

  int jet1tagEff, jet2tagEff;
  unsigned int npv, npv1Eff, npv2Eff;                                                                                                                                                                   
  double jet1ptEff, jet2ptEff;                                                                                                                                                                     
  int nbins_pt = 35;
  float bins_pt[36] = {0,20,40,60,80,100,120,140,160,180,200,220,240,260,280,300,320,340,360,380,400,420,440,460,480,500,520,540,560,580,600,700,800,900,1000,2000};                                       
  int nbins_npv = 30;                                                                                                                                                                                      
  float bins_npv[31] = {0,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,35,40,50};

  TChain* chain = new TChain("Events");
  chain->Add("/uscms_data/d3/camclean/CSA14/topTaggingEfficiency/CMSSW_7_0_6_patch1/src/Analysis/analyzeMiniAOD/RSGluonToTT_M_4000_08_19_2014/res/*.root");
 
  TBranch *b_jet1tagEff;
  TBranch *b_jet2tagEff;
  TBranch *b_jet1ptEff;
  TBranch *b_jet2ptEff;
  TBranch *b_npv;

  chain->SetBranchAddress("int_miniAOD_jet1tagEff_MiniAOD.obj",&jet1tagEff,&b_jet1tagEff);
  chain->SetBranchAddress("int_miniAOD_jet2tagEff_MiniAOD.obj",&jet2tagEff,&b_jet2tagEff);
  chain->SetBranchAddress("doubles_miniAOD_jet1ptEff_MiniAOD.obj",&jet1ptEff,&b_jet1ptEff);
  chain->SetBranchAddress("doubles_miniAOD_jet2ptEff_MiniAOD.obj",&jet2ptEff,&b_jet2ptEff);
  chain->SetBranchAddress("uint_miniAOD_npv_MiniAOD.obj",&npv,&b_npv); 

  //  chain->Draw("jet1ptEff");
  /*
  TCanvas* canvas = new TCanvas();
  chain->Draw("npv");
  */
  int n_entries = chain->GetEntries();

  /////pt histograms
  TH1F *h_topTagEffPt = new TH1F("h_topTagEffPt","Top Tagging Efficiency - 13 TeV; pt; Efficiency",nbins_pt,bins_pt);
  TH1F *h_tagJet1pt = new TH1F("h_tagJet1pt","Top Tagging Efficiency - 13 TeV; pt; Efficiency",nbins_pt,bins_pt);
  TH1F *h_tagJet2pt = new TH1F("h_tagJet2pt","Jet 2 Pt - 13 TeV; pt; Events",nbins_pt,bins_pt);
  //TH1F *h_jetPt = new TH1F("h_jetPt","Jet Pt - 13 TeV; pt; Events",nbins_pt,bins_pt);
  TH1F *h_jet1pt = new TH1F("h_jet1pt","Generated Top 1 Pt - 13 TeV; pt; Events",nbins_pt,bins_pt);
  TH1F *h_jet2pt = new TH1F("h_jet2pt","Generated Top 2 Pt - 13 TeV; pt; Events",nbins_pt,bins_pt);
  //TH1F *h_genTopPt = new TH1F("h_genTopPt","Generated Top Pt - 13 TeV; pt; Events",nbins_pt,bins_pt);
  
  h_tagJet1pt->Sumw2();
  h_tagJet2pt->Sumw2();
  h_jet1pt->Sumw2();
  h_jet2pt->Sumw2();

  /////pileup histograms - no pt cut
  TH1F *h_topTagEffNpv = new TH1F("h_topTagEffNpv","Top Tagging Efficiency (Npv)- 13 TeV; Number of Primary Vertices; Efficiency",nbins_npv,bins_npv);
  TH1F *h_tagNpv1 = new TH1F("h_tagNpv1pt","Top Tagging Efficiency - 13 TeV; Npv; Efficiency",nbins_npv,bins_npv);
  TH1F *h_tagNpv2 = new TH1F("h_tagNpv2pt","Jet 2 Pt - 13 TeV; Npt; Events",nbins_npv,bins_npv);
  TH1F *h_npv1 = new TH1F("h_npv1","Generated Top 1 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);
  TH1F *h_npv2 = new TH1F("h_npv2","Generated Top 2 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);

  h_tagNpv1->Sumw2();
  h_tagNpv2->Sumw2();
  h_npv1->Sumw2();
  h_npv2->Sumw2();

  /////pileup histograms - pt > 400 GeV
  TH1F *h_topTagEffNpv_400 = new TH1F("h_topTagEffNpv_400","Top Tagging Efficiency (Npv)- 13 TeV; Number of Primary Vertices; Efficiency",nbins_npv,bins_npv);
  TH1F *h_tagNpv1_400 = new TH1F("h_tagNpv1pt_400","Top Tagging Efficiency - 13 TeV; Npv; Efficiency",nbins_npv,bins_npv);
  TH1F *h_tagNpv2_400 = new TH1F("h_tagNpv2pt_400","Jet 2 Pt - 13 TeV; Npt; Events",nbins_npv,bins_npv);
  TH1F *h_npv1_400 = new TH1F("h_npv1_400","Generated Top 1 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);
  TH1F *h_npv2_400 = new TH1F("h_npv2_400","Generated Top 2 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);

  h_tagNpv1_400->Sumw2();
  h_tagNpv2_400->Sumw2();
  h_npv1_400->Sumw2();
  h_npv2_400->Sumw2();

  /////pileup histograms - pt > 500 GeV
  TH1F *h_topTagEffNpv_500 = new TH1F("h_topTagEffNpv_500","Top Tagging Efficiency (Npv)- 13 TeV; Number of Primary Vertices; Efficiency",nbins_npv,bins_npv);
  TH1F *h_tagNpv1_500 = new TH1F("h_tagNpv1pt_500","Top Tagging Efficiency - 13 TeV; Npv; Efficiency",nbins_npv,bins_npv);
  TH1F *h_tagNpv2_500 = new TH1F("h_tagNpv2pt_500","Jet 2 Pt - 13 TeV; Npt; Events",nbins_npv,bins_npv);
  TH1F *h_npv1_500 = new TH1F("h_npv1_500","Generated Top 1 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);
  TH1F *h_npv2_500 = new TH1F("h_npv2_500","Generated Top 2 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);

  h_tagNpv1_500->Sumw2();
  h_tagNpv2_500->Sumw2();
  h_npv1_500->Sumw2();
  h_npv2_500->Sumw2();

  /////pileup histograms - pt > 600 GeV
  TH1F *h_topTagEffNpv_600 = new TH1F("h_topTagEffNpv_600","Top Tagging Efficiency (Npv)- 13 TeV; Number of Primary Vertices; Efficiency",nbins_npv,bins_npv);
  TH1F *h_tagNpv1_600 = new TH1F("h_tagNpv1pt_600","Top Tagging Efficiency - 13 TeV; Npv; Efficiency",nbins_npv,bins_npv);
  TH1F *h_tagNpv2_600 = new TH1F("h_tagNpv2pt_600","Jet 2 Pt - 13 TeV; Npt; Events",nbins_npv,bins_npv);
  TH1F *h_npv1_600 = new TH1F("h_npv1_600","Generated Top 1 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);
  TH1F *h_npv2_600 = new TH1F("h_npv2_600","Generated Top 2 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);

  h_tagNpv1_600->Sumw2();
  h_tagNpv2_600->Sumw2();
  h_npv1_600->Sumw2();
  h_npv2_600->Sumw2();

  /////pileup histograms - pt > 700 GeV
  TH1F *h_topTagEffNpv_700 = new TH1F("h_topTagEffNpv_700","Top Tagging Efficiency (Npv)- 13 TeV; Number of Primary Vertices; Efficiency",nbins_npv,bins_npv);
  TH1F *h_tagNpv1_700 = new TH1F("h_tagNpv1pt_700","Top Tagging Efficiency - 13 TeV; Npv; Efficiency",nbins_npv,bins_npv);
  TH1F *h_tagNpv2_700 = new TH1F("h_tagNpv2pt_700","Jet 2 Pt - 13 TeV; Npt; Events",nbins_npv,bins_npv);
  TH1F *h_npv1_700 = new TH1F("h_npv1_700","Generated Top 1 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);
  TH1F *h_npv2_700 = new TH1F("h_npv2_700","Generated Top 2 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);  

  h_tagNpv1_700->Sumw2();
  h_tagNpv2_700->Sumw2();
  h_npv1_700->Sumw2();
  h_npv2_700->Sumw2();
  
  //filling histograms
  for(int i = 0; i<n_entries;i++){

    b_jet1tagEff->SetAddress(b_jet1tagEff);
    b_jet1tagEff->GetEntry(i);
    b_jet2tagEff->SetAddress(b_jet2tagEff);
    b_jet2tagEff->GetEntry(i);
    b_jet1ptEff->SetAddress(b_jet1ptEff);
    b_jet1ptEff->GetEntry(i);
    b_jet2ptEff->SetAddress(b_jet2ptEff);
    b_jet2ptEff->GetEntry(i);
    b_npv->SetAddress(b_npv);
    b_npv->GetEntry(i);

    chain->GetEntry(i,0);

    //cout <<jet1ptEff<< endl;

    cout <<npv<<endl;
    
    //denominator histograms - 0 = top-matched, not top-tagged; 1 = top-matched and top-tagged
    if(jet1tagEff == 0 || jet1tagEff == 1){
      
      //cout <<jet1ptEff<< endl;
      
      h_jet1pt->Fill(jet1ptEff); 
      h_npv1->Fill(npv);
      if(jet1ptEff > 400.){
	h_npv1_400->Fill(npv);
      }
      if(jet1ptEff > 500.){
	h_npv1_500->Fill(npv);
      }
      if(jet1ptEff > 600.){
	h_npv1_600->Fill(npv);
      }
      if(jet1ptEff > 700.){
	h_npv1_700->Fill(npv);
      }
    }

    if(jet2tagEff == 0 || jet2tagEff == 1){
      h_jet2pt->Fill(jet2ptEff); 
      h_npv2->Fill(npv2Eff);
      if(jet2ptEff > 400.){
	h_npv2_400->Fill(npv2Eff);
      }
      if(jet2ptEff > 500.){
	h_npv2_500->Fill(npv2Eff);
      }
      if(jet2ptEff > 600.){
	h_npv2_600->Fill(npv2Eff);
      }
      if(jet2ptEff > 700.){
	h_npv2_700->Fill(npv2Eff);
      }
    }

    //numerator histograms
    if(jet1tagEff == 1){      
      h_tagJet1pt->Fill(jet1ptEff); 
      h_tagNpv1->Fill(npv);
      if(jet1ptEff > 400.){
	h_tagNpv1_400->Fill(npv);
      }
      if(jet1ptEff > 500.){
	h_tagNpv1_500->Fill(npv);
      }
      if(jet1ptEff > 600.){
	h_tagNpv1_600->Fill(npv);
      }
      if(jet1ptEff > 700.){
	h_tagNpv1_700->Fill(npv);
      }
      
      //jet1pt_tag = jet1ptEff;
    }    

    if(jet2tagEff == 1){     
      h_tagJet2pt->Fill(jet2ptEff);
      h_tagNpv2->Fill(npv);
      if(jet2ptEff > 400.){
	h_tagNpv2_400->Fill(npv);
      }
      if(jet2ptEff > 500.){
	h_tagNpv2_500->Fill(npv);
      }
      if(jet2ptEff > 600.){
	h_tagNpv2_600->Fill(npv);
      }
      if(jet2ptEff > 700.){
	h_tagNpv2_700->Fill(npv);
      //jet2pt_tag = jet1ptEff;
      }
    }

    //jetPt_tag = jet1pt_tag + jet2pt_tag;

    //h_topTagEff->Fill(jetPt_tag/(genTopPt));
  }
  /*
  //efficiency histograms
  h_jet1pt->Add(h_jet2pt);
  h_tagJet1pt->Add(h_tagJet2pt);
  //h_tagJet1pt->Divide(h_jet1pt);
  h_topTagEffPt->Divide(h_tagJet1pt,h_jet1pt,1,1,"B");

  h_npv1->Add(h_npv2);
  h_tagNpv1->Add(h_tagNpv2);
  h_topTagEffNpv->Divide(h_tagNpv1,h_npv1,1,1,"B");

  h_npv1_400->Add(h_npv2_400);
  h_tagNpv1_400->Add(h_tagNpv2_400);
  h_topTagEffNpv_400->Divide(h_tagNpv1_400,h_npv1_400,1,1,"B");

  h_npv1_500->Add(h_npv2_500);
  h_tagNpv1_500->Add(h_tagNpv2_500);
  h_topTagEffNpv_500->Divide(h_tagNpv1_500,h_npv1_500,1,1,"B");

  h_npv1_600->Add(h_npv2_600);
  h_tagNpv1_600->Add(h_tagNpv2_600);
  h_topTagEffNpv_600->Divide(h_tagNpv1_600,h_npv1_600,1,1,"B");

  h_npv1_700->Add(h_npv2_700);
  h_tagNpv1_700->Add(h_tagNpv2_700);
  h_topTagEffNpv_700->Divide(h_tagNpv1_700,h_npv1_700,1,1,"B");

  TCanvas* c1 = new TCanvas();
  h_topTagEffPt->Draw("E");
  h_topTagEffPt->SetMarkerStyle(7);
  h_topTagEffPt->SetMaximum(1.1);
  h_topTagEffPt->SetTitle("Top Tagging Efficiency - 13 TeV, 1000+ Invt M");

  TCanvas* c2 = new TCanvas();
  h_topTagEffNpv->Draw("E");
  h_topTagEffNpv->SetMarkerStyle(7);
  h_topTagEffNpv->SetMaximum(1.1);

  h_topTagEffNpv_400->Draw("ESAME");
  h_topTagEffNpv_400->SetMarkerStyle(7);
  h_topTagEffNpv_400->SetMaximum(1.1);
  h_topTagEffNpv_400->SetLineColor(kMagenta+1);
  h_topTagEffNpv_400->SetMarkerColor(kMagenta+1);

  h_topTagEffNpv_500->Draw("ESAME");
  h_topTagEffNpv_500->SetMarkerStyle(7);
  h_topTagEffNpv_500->SetMaximum(1.1);
  h_topTagEffNpv_500->SetLineColor(kBlue);
  h_topTagEffNpv_500->SetMarkerColor(kBlue);

  h_topTagEffNpv_600->Draw("ESAME");
  h_topTagEffNpv_600->SetMarkerStyle(7);
  h_topTagEffNpv_600->SetMaximum(1.1);
  h_topTagEffNpv_600->SetLineColor(kCyan+1);
  h_topTagEffNpv_600->SetMarkerColor(kCyan+1);

  h_topTagEffNpv_700->Draw("ESAME");
  h_topTagEffNpv_700->SetMarkerStyle(7);
  h_topTagEffNpv_700->SetMaximum(1.1);
  h_topTagEffNpv_700->SetLineColor(kGreen+2);
  h_topTagEffNpv_700->SetMarkerColor(kGreen+2);
  //h_topTagEffPt->SetTitle("Top Tagging Efficiency - 13 TeV, 1000+ Invt M");

 //legend 
  TLegend *legend_topTagEffNpv = new TLegend(0.2,0.65,0.45,0.88);
  legend_topTagEffNpv->AddEntry(h_topTagEffNpv,"No Pt Cut","LPE");
  legend_topTagEffNpv->AddEntry(h_topTagEffNpv_400,"Pt > 400 GeV","LPE");
  legend_topTagEffNpv->AddEntry(h_topTagEffNpv_500,"Pt > 500 GeV","LPE");
  legend_topTagEffNpv->AddEntry(h_topTagEffNpv_600,"Pt > 600 GeV","LPE");
  legend_topTagEffNpv->AddEntry(h_topTagEffNpv_700,"Pt > 700 GeV","LPE");
  legend_topTagEffNpv->SetFillColor(kWhite); legend_topTagEffNpv->Draw("Same");
    */ 
  /*
  double luminosity = 19.7; //fb^-1
  double sigma_ttbar = 245000; //fb
  int nbins_pt = 35;
  float bins_pt[36] = {0,20,40,60,80,100,120,140,160,180,200,220,240,260,280,300,320,340,360,380,400,420,440,460,480,500,520,540,560,580,600,700,800,900,1000,2000};
  int nbins_npv = 30;
  float bins_npv[31] = {0,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,35,40,50};
  
  
  /////////////
  //powheg 10 - ttbar invariant mass of 1000+ GeV
  ////////////
  TFile *f_topTagEff_10 = new TFile (file1.c_str(), "READ");
  TTree *t_topTagEff_10 = static_cast<TTree*> (f_topTagEff_10->Get("treeEff"));

  int jet1tag_eff_10, jet2tag_eff_10;
  unsigned int npv1_eff_10, npv2_eff_10;
  float jet1pt_eff_10, jet2pt_eff_10;
  double Ngen_10 = 1249111;
  double eps_10 = 0.014;
  double w_10 = (sigma_ttbar*eps_10*luminosity)/Ngen_10;
  
  t_topTagEff_10->SetBranchAddress("jet1tag_eff",&jet1tag_eff_10);
  t_topTagEff_10->SetBranchAddress("jet2tag_eff",&jet2tag_eff_10);
  t_topTagEff_10->SetBranchAddress("jet1pt_eff",&jet1pt_eff_10);
  t_topTagEff_10->SetBranchAddress("jet2pt_eff",&jet2pt_eff_10);
  t_topTagEff_10->SetBranchAddress("npv1_eff",&npv1_eff_10);
  t_topTagEff_10->SetBranchAddress("npv2_eff",&npv2_eff_10);
  //t_topTagEff_10->SetBranchAddress("genTop1pt_eff",&genTop1pt_eff_10);
  //t_topTagEff_10->SetBranchAddress("genTop2pt_eff",&genTop2pt_eff_10);

  int n_entries_10 = t_topTagEff_10->GetEntries();

  /////////////
  //powheg 7 - ttbar invariant mass of 700 - 1000 GeV
  ////////////
  TFile *f_topTagEff_7 = new TFile (file2.c_str(), "READ");
  TTree *t_topTagEff_7 = static_cast<TTree*> (f_topTagEff_7->Get("treeEff"));

  int jet1tag_eff_7, jet2tag_eff_7;
  unsigned int npv1_eff_7, npv2_eff_7;
  float jet1pt_eff_7, jet2pt_eff_7;
  int nbins_pt = 35;
  float bins_pt[36] = {0,20,40,60,80,100,120,140,160,180,200,220,240,260,280,300,320,340,360,380,400,420,440,460,480,500,520,540,560,580,600,700,800,900,1000,2000};
  double Ngen_7 = 3082812;
  double eps_7 = 0.077;
  double w_7 = (sigma_ttbar*eps_7*luminosity)/Ngen_7;

  t_topTagEff_7->SetBranchAddress("jet1tag_eff",&jet1tag_eff_7);
  t_topTagEff_7->SetBranchAddress("jet2tag_eff",&jet2tag_eff_7);
  t_topTagEff_7->SetBranchAddress("jet1pt_eff",&jet1pt_eff_7);
  t_topTagEff_7->SetBranchAddress("jet2pt_eff",&jet2pt_eff_7);
  t_topTagEff_7->SetBranchAddress("npv1_eff",&npv1_eff_7);
  t_topTagEff_7->SetBranchAddress("npv2_eff",&npv2_eff_7);
  //t_topTagEff_7->SetBranchAddress("genTop1pt_eff",&genTop1pt_eff_7);
  //t_topTagEff_7->SetBranchAddress("genTop2pt_eff",&genTop2pt_eff_7);

  int n_entries_7 = t_topTagEff_7->GetEntries();

  /////pt histograms
  TH1F *h_topTagEffPt_7 = new TH1F("h_topTagEffPt_7","Top Tagging Efficiency - 8 TeV; pt; Efficiency",nbins_pt,bins_pt);
  TH1F *h_tagJet1pt_7 = new TH1F("h_tagJet1pt_7","Top Tagging Efficiency - 8 TeV; pt; Efficiency",nbins_pt,bins_pt);
  TH1F *h_tagJet2pt_7 = new TH1F("h_tagJet2pt_7","Jet 2 Pt - 8 TeV; pt; Events",nbins_pt,bins_pt);
  //TH1F *h_jetPt_7 = new TH1F("h_jetPt_7","Jet Pt - 8 TeV; pt; Events",nbins_pt,bins_pt);
  TH1F *h_jet1pt_7 = new TH1F("h_jet1pt_7","Generated Top 1 Pt - 8 TeV; pt; Events",nbins_pt,bins_pt);
  TH1F *h_jet2pt_7 = new TH1F("h_jet2pt_7","Generated Top 2 Pt - 8 TeV; pt; Events",nbins_pt,bins_pt);
  //TH1F *h_genTopPt_7 = new TH1F("h_genTopPt_7","Generated Top Pt - 8 TeV; pt; Events",nbins_pt,bins_pt);
  
  h_tagJet1pt_7->Sumw2();
  h_tagJet2pt_7->Sumw2();
  h_jet1pt_7->Sumw2();
  h_jet2pt_7->Sumw2();

  /////pileup histograms - no pt cut
  TH1F *h_topTagEffNpv_7 = new TH1F("h_topTagEffNpv_7","Top Tagging Efficiency (Npv)- 8 TeV; Number of Primary Vertices; Efficiency",nbins_npv,bins_npv);
  TH1F *h_tagNpv1_7 = new TH1F("h_tagNpv1pt_7","Top Tagging Efficiency - 8 TeV; Npv; Efficiency",nbins_npv,bins_npv);
  TH1F *h_tagNpv2_7 = new TH1F("h_tagNpv2pt_7","Jet 2 Pt - 8 TeV; Npt; Events",nbins_npv,bins_npv);
  TH1F *h_npv1_7 = new TH1F("h_npv1_7","Generated Top 1 Npv - 8 TeV; Npv; Events",nbins_npv,bins_npv);
  TH1F *h_npv2_7 = new TH1F("h_npv2_7","Generated Top 2 Npv - 8 TeV; Npv; Events",nbins_npv,bins_npv);

  h_tagNpv1_7->Sumw2();
  h_tagNpv2_7->Sumw2();
  h_npv1_7->Sumw2();
  h_npv2_7->Sumw2();

  /////pileup histograms - pt > 400 GeV
  TH1F *h_topTagEffNpv_7_400 = new TH1F("h_topTagEffNpv_7_400","Top Tagging Efficiency (Npv)- 8 TeV; Number of Primary Vertices; Efficiency",nbins_npv,bins_npv);
  TH1F *h_tagNpv1_7_400 = new TH1F("h_tagNpv1pt_7_400","Top Tagging Efficiency - 8 TeV; Npv; Efficiency",nbins_npv,bins_npv);
  TH1F *h_tagNpv2_7_400 = new TH1F("h_tagNpv2pt_7_400","Jet 2 Pt - 8 TeV; Npt; Events",nbins_npv,bins_npv);
  TH1F *h_npv1_7_400 = new TH1F("h_npv1_7_400","Generated Top 1 Npv - 8 TeV; Npv; Events",nbins_npv,bins_npv);
  TH1F *h_npv2_7_400 = new TH1F("h_npv2_7_400","Generated Top 2 Npv - 8 TeV; Npv; Events",nbins_npv,bins_npv);

  h_tagNpv1_7_400->Sumw2();
  h_tagNpv2_7_400->Sumw2();
  h_npv1_7_400->Sumw2();
  h_npv2_7_400->Sumw2();

  /////pileup histograms - pt > 500 GeV
  TH1F *h_topTagEffNpv_7_500 = new TH1F("h_topTagEffNpv_7_500","Top Tagging Efficiency (Npv)- 8 TeV; Number of Primary Vertices; Efficiency",nbins_npv,bins_npv);
  TH1F *h_tagNpv1_7_500 = new TH1F("h_tagNpv1pt_7_500","Top Tagging Efficiency - 8 TeV; Npv; Efficiency",nbins_npv,bins_npv);
  TH1F *h_tagNpv2_7_500 = new TH1F("h_tagNpv2pt_7_500","Jet 2 Pt - 8 TeV; Npt; Events",nbins_npv,bins_npv);
  TH1F *h_npv1_7_500 = new TH1F("h_npv1_7_500","Generated Top 1 Npv - 8 TeV; Npv; Events",nbins_npv,bins_npv);
  TH1F *h_npv2_7_500 = new TH1F("h_npv2_7_500","Generated Top 2 Npv - 8 TeV; Npv; Events",nbins_npv,bins_npv);

  h_tagNpv1_7_500->Sumw2();
  h_tagNpv2_7_500->Sumw2();
  h_npv1_7_500->Sumw2();
  h_npv2_7_500->Sumw2();

  /////pileup histograms - pt > 600 GeV
  TH1F *h_topTagEffNpv_7_600 = new TH1F("h_topTagEffNpv_7_600","Top Tagging Efficiency (Npv)- 8 TeV; Number of Primary Vertices; Efficiency",nbins_npv,bins_npv);
  TH1F *h_tagNpv1_7_600 = new TH1F("h_tagNpv1pt_7_600","Top Tagging Efficiency - 8 TeV; Npv; Efficiency",nbins_npv,bins_npv);
  TH1F *h_tagNpv2_7_600 = new TH1F("h_tagNpv2pt_7_600","Jet 2 Pt - 8 TeV; Npt; Events",nbins_npv,bins_npv);
  TH1F *h_npv1_7_600 = new TH1F("h_npv1_7_600","Generated Top 1 Npv - 8 TeV; Npv; Events",nbins_npv,bins_npv);
  TH1F *h_npv2_7_600 = new TH1F("h_npv2_7_600","Generated Top 2 Npv - 8 TeV; Npv; Events",nbins_npv,bins_npv);

  h_tagNpv1_7_600->Sumw2();
  h_tagNpv2_7_600->Sumw2();
  h_npv1_7_600->Sumw2();
  h_npv2_7_600->Sumw2();

  /////pileup histograms - pt > 700 GeV
  TH1F *h_topTagEffNpv_7_700 = new TH1F("h_topTagEffNpv_7_700","Top Tagging Efficiency (Npv)- 8 TeV; Number of Primary Vertices; Efficiency",nbins_npv,bins_npv);
  TH1F *h_tagNpv1_7_700 = new TH1F("h_tagNpv1pt_7_700","Top Tagging Efficiency - 8 TeV; Npv; Efficiency",nbins_npv,bins_npv);
  TH1F *h_tagNpv2_7_700 = new TH1F("h_tagNpv2pt_7_700","Jet 2 Pt - 8 TeV; Npt; Events",nbins_npv,bins_npv);
  TH1F *h_npv1_7_700 = new TH1F("h_npv1_7_700","Generated Top 1 Npv - 8 TeV; Npv; Events",nbins_npv,bins_npv);
  TH1F *h_npv2_7_700 = new TH1F("h_npv2_7_700","Generated Top 2 Npv - 8 TeV; Npv; Events",nbins_npv,bins_npv);  

  h_tagNpv1_7_700->Sumw2();
  h_tagNpv2_7_700->Sumw2();
  h_npv1_7_700->Sumw2();
  h_npv2_7_700->Sumw2();
  
  //filling histograms
  for(int i = 1; i<n_entries_7;i++){
    t_topTagEff_7->GetEntry(i);
    
    //denominator histograms - 0 = top-matched, not top-tagged; 1 = top-matched and top-tagged
    if(jet1tag_eff_7 == 0 || jet1tag_eff_7 == 1){
      h_jet1pt_7->Fill(jet1pt_eff_7); 
      h_npv1_7->Fill(npv1_eff_7);
      if(jet1pt_eff_7 > 400.){
	h_npv1_7_400->Fill(npv1_eff_7);
      }
      if(jet1pt_eff_7 > 500.){
	h_npv1_7_500->Fill(npv1_eff_7);
      }
      if(jet1pt_eff_7 > 600.){
	h_npv1_7_600->Fill(npv1_eff_7);
      }
      if(jet1pt_eff_7 > 700.){
	h_npv1_7_700->Fill(npv1_eff_7);
      }
    }

    if(jet2tag_eff_7 == 0 || jet2tag_eff_7 == 1){
      h_jet2pt_7->Fill(jet2pt_eff_7); 
      h_npv2_7->Fill(npv2_eff_7);
      if(jet2pt_eff_7 > 400.){
	h_npv2_7_400->Fill(npv2_eff_7);
      }
      if(jet2pt_eff_7 > 500.){
	h_npv2_7_500->Fill(npv2_eff_7);
      }
      if(jet2pt_eff_7 > 600.){
	h_npv2_7_600->Fill(npv2_eff_7);
      }
      if(jet2pt_eff_7 > 700.){
	h_npv2_7_700->Fill(npv2_eff_7);
      }
    }

    //numerator histograms
    if(jet1tag_eff_7 == 1){      
      h_tagJet1pt_7->Fill(jet1pt_eff_7); 
      h_tagNpv1_7->Fill(npv1_eff_7);
      if(jet1pt_eff_7 > 400.){
	h_tagNpv1_7_400->Fill(npv1_eff_7);
      }
      if(jet1pt_eff_7 > 500.){
	h_tagNpv1_7_500->Fill(npv1_eff_7);
      }
      if(jet1pt_eff_7 > 600.){
	h_tagNpv1_7_600->Fill(npv1_eff_7);
      }
      if(jet1pt_eff_7 > 700.){
	h_tagNpv1_7_700->Fill(npv1_eff_7);
      }
      
      //jet1pt_tag = jet1pt_eff_7;
    }    

    if(jet2tag_eff_7 == 1){     
      h_tagJet2pt_7->Fill(jet2pt_eff_7);
      h_tagNpv2_7->Fill(npv2_eff_7);
      if(jet2pt_eff_7 > 400.){
	h_tagNpv2_7_400->Fill(npv2_eff_7);
      }
      if(jet2pt_eff_7 > 500.){
	h_tagNpv2_7_500->Fill(npv2_eff_7);
      }
      if(jet2pt_eff_7 > 600.){
	h_tagNpv2_7_600->Fill(npv2_eff_7);
      }
      if(jet2pt_eff_7 > 700.){
	h_tagNpv2_7_700->Fill(npv2_eff_7);
      //jet2pt_tag = jet1pt_eff_7;
      }
    }

    //jetPt_tag = jet1pt_tag + jet2pt_tag;

    //h_topTagEff_7->Fill(jetPt_tag/(genTopPt));
    
  }
  
  //efficiency histograms
  h_jet1pt_7->Add(h_jet2pt_7);
  h_tagJet1pt_7->Add(h_tagJet2pt_7);
  //h_tagJet1pt_7->Divide(h_jet1pt);
  h_topTagEffPt_7->Divide(h_tagJet1pt_7,h_jet1pt_7,1,1,"B");

  h_npv1_7->Add(h_npv2_7);
  h_tagNpv1_7->Add(h_tagNpv2_7);
  h_topTagEffNpv_7->Divide(h_tagNpv1_7,h_npv1_7,1,1,"B");

  h_npv1_7_400->Add(h_npv2_7_400);
  h_tagNpv1_7_400->Add(h_tagNpv2_7_400);
  h_topTagEffNpv_7_400->Divide(h_tagNpv1_7_400,h_npv1_7_400,1,1,"B");

  h_npv1_7_500->Add(h_npv2_7_500);
  h_tagNpv1_7_500->Add(h_tagNpv2_7_500);
  h_topTagEffNpv_7_500->Divide(h_tagNpv1_7_500,h_npv1_7_500,1,1,"B");

  h_npv1_7_600->Add(h_npv2_7_600);
  h_tagNpv1_7_600->Add(h_tagNpv2_7_600);
  h_topTagEffNpv_7_600->Divide(h_tagNpv1_7_600,h_npv1_7_600,1,1,"B");

  h_npv1_7_700->Add(h_npv2_7_700);
  h_tagNpv1_7_700->Add(h_tagNpv2_7_700);
  h_topTagEffNpv_7_700->Divide(h_tagNpv1_7_700,h_npv1_7_700,1,1,"B");

  TCanvas* c1_7 = new TCanvas();
  h_topTagEffPt_7->Draw("E");
  h_topTagEffPt_7->SetMarkerStyle(7);
  h_topTagEffPt_7->SetMaximum(1.1);
  h_topTagEffPt_7->SetTitle("Top Tagging Efficiency - 8 TeV, 1000+ Invt M");

  TCanvas* c2_7 = new TCanvas();
  h_topTagEffNpv_7->Draw("E");
  h_topTagEffNpv_7->SetMarkerStyle(7);
  h_topTagEffNpv_7->SetMaximum(1.1);

  h_topTagEffNpv_7_400->Draw("ESAME");
  h_topTagEffNpv_7_400->SetMarkerStyle(7);
  h_topTagEffNpv_7_400->SetMaximum(1.1);
  h_topTagEffNpv_7_400->SetLineColor(kMagenta+1);
  h_topTagEffNpv_7_400->SetMarkerColor(kMagenta+1);

  h_topTagEffNpv_7_500->Draw("ESAME");
  h_topTagEffNpv_7_500->SetMarkerStyle(7);
  h_topTagEffNpv_7_500->SetMaximum(1.1);
  h_topTagEffNpv_7_500->SetLineColor(kBlue);
  h_topTagEffNpv_7_500->SetMarkerColor(kBlue);

  h_topTagEffNpv_7_600->Draw("ESAME");
  h_topTagEffNpv_7_600->SetMarkerStyle(7);
  h_topTagEffNpv_7_600->SetMaximum(1.1);
  h_topTagEffNpv_7_600->SetLineColor(kCyan+1);
  h_topTagEffNpv_7_600->SetMarkerColor(kCyan+1);

  h_topTagEffNpv_7_700->Draw("ESAME");
  h_topTagEffNpv_7_700->SetMarkerStyle(7);
  h_topTagEffNpv_7_700->SetMaximum(1.1);
  h_topTagEffNpv_7_700->SetLineColor(kGreen+2);
  h_topTagEffNpv_7_700->SetMarkerColor(kGreen+2);
  //h_topTagEffPt_7->SetTitle("Top Tagging Efficiency - 8 TeV, 1000+ Invt M");

 //legend 
  TLegend *legend_topTagEffNpv_7 = new TLegend(0.2,0.65,0.45,0.88);
  legend_topTagEffNpv_7->AddEntry(h_topTagEffNpv_7,"No Pt Cut","LPE");
  legend_topTagEffNpv_7->AddEntry(h_topTagEffNpv_7_400,"Pt > 400 GeV","LPE");
  legend_topTagEffNpv_7->AddEntry(h_topTagEffNpv_7_500,"Pt > 500 GeV","LPE");
  legend_topTagEffNpv_7->AddEntry(h_topTagEffNpv_7_600,"Pt > 600 GeV","LPE");
  legend_topTagEffNpv_7->AddEntry(h_topTagEffNpv_7_700,"Pt > 700 GeV","LPE");
  legend_topTagEffNpv_7->SetFillColor(kWhite); legend_topTagEffNpv_7->Draw("Same");

  //////////////////////////////
  ////combined powheg 7 and 10 - ttbar invariant mass of 700+
  /////////////////////////////

  //pt histograms
  h_topTagEffPtNum->Add(h_tagJet1pt_7,h_tagJet1pt_10,w_7,w_10);
  h_topTagEffPtDenom->Add(h_jet1pt_7,h_jet1pt_10,w_7,w_10);
  h_topTagEffPt->Divide(h_topTagEffPtNum,h_topTagEffPtDenom,1,1,"B");
  
  //pileup histograms
  h_topTagEffNpvNum->Add(h_tagNpv1_7,h_tagNpv1_10,w_7,w_10);
  h_topTagEffNpvDenom->Add(h_npv1_7,h_npv1_10,w_7,w_10);
  h_topTagEffNpv->Divide(h_topTagEffNpvNum,h_topTagEffNpvDenom,1,1,"B");

  h_topTagEffNpvNum_400->Add(h_tagNpv1_7_400,h_tagNpv1_10_400,w_7,w_10);
  h_topTagEffNpvDenom_400->Add(h_npv1_7_400,h_npv1_10_400,w_7,w_10);
  h_topTagEffNpv_400->Divide(h_topTagEffNpvNum_400,h_topTagEffNpvDenom_400,1,1,"B");

  h_topTagEffNpvNum_500->Add(h_tagNpv1_7_500,h_tagNpv1_10_500,w_7,w_10);
  h_topTagEffNpvDenom_500->Add(h_npv1_7_500,h_npv1_10_500,w_7,w_10);
  h_topTagEffNpv_500->Divide(h_topTagEffNpvNum_500,h_topTagEffNpvDenom_500,1,1,"B");

  h_topTagEffNpvNum_600->Add(h_tagNpv1_7_600,h_tagNpv1_10_600,w_7,w_10);
  h_topTagEffNpvDenom_600->Add(h_npv1_7_600,h_npv1_10_600,w_7,w_10);
  h_topTagEffNpv_600->Divide(h_topTagEffNpvNum_600,h_topTagEffNpvDenom_600,1,1,"B");

  h_topTagEffNpvNum_700->Add(h_tagNpv1_7_700,h_tagNpv1_10_700,w_7,w_10);
  h_topTagEffNpvDenom_700->Add(h_npv1_7_700,h_npv1_10_700,w_7,w_10);
  h_topTagEffNpv_700->Divide(h_topTagEffNpvNum_700,h_topTagEffNpvDenom_700,1,1,"B");
 
  //fit functions
  TF1 *fit_topTagEffNpv = new TF1("fit_topTagEffNpv","[0]*x + [1]",0.,50.);
  fit_topTagEffNpv->SetParameters(0.0,0.165);
  fit_topTagEffNpv->SetParNames("No pt cut: slope","No pt cut: y intercept");
  h_topTagEffNpv->Fit("fit_topTagEffNpv");

  TF1 *fit_topTagEffNpv_400 = new TF1("fit_topTagEffNpv_400","[0]*x + [1]",0.,50.);
  fit_topTagEffNpv_400->SetParameters(0.0,0.417);
  fit_topTagEffNpv_400->SetParNames("pt > 400: slope","pt > 400: y intercept");
  h_topTagEffNpv_400->Fit("fit_topTagEffNpv_400");

  TF1 *fit_topTagEffNpv_500 = new TF1("fit_topTagEffNpv_500","[0]*x + [1]",0.,50.);
  fit_topTagEffNpv_500->SetParameters(0.0,0.498);
  fit_topTagEffNpv_500->SetParNames("pt > 500: slope","pt > 500: y intercept");
  h_topTagEffNpv_500->Fit("fit_topTagEffNpv_500");

  TF1 *fit_topTagEffNpv_600 = new TF1("fit_topTagEffNpv_600","[0]*x + [1]",0.,50.);
  fit_topTagEffNpv_600->SetParameters(0.0,0.567);
  fit_topTagEffNpv_600->SetParNames("pt > 600: slope","pt > 600: y intercept");
  h_topTagEffNpv_600->Fit("fit_topTagEffNpv_600");

  TF1 *fit_topTagEffNpv_700 = new TF1("fit_topTagEffNpv_700","[0]*x + [1]",0.,50.);
  fit_topTagEffNpv_700->SetParameters(0.0,0.559);
  fit_topTagEffNpv_700->SetParNames("pt > 700: slope","pt > 700: y intercept");
  h_topTagEffNpv_700->Fit("fit_topTagEffNpv_700");

  TCanvas* c1_combo = new TCanvas("Pt Combined Canvas");
  h_topTagEffPt->SetTitle("Top Tagging Efficiency - 8 TeV");
  h_topTagEffPt->Draw("E");
  h_topTagEffPt->SetMarkerStyle(7);
  h_topTagEffPt->SetMaximum(1.1);

  TCanvas* c2_combo = new TCanvas("Npv Combined Canvas");
  h_topTagEffNpv->Draw("E");
  h_topTagEffNpv->SetMarkerStyle(7);
  h_topTagEffNpv->SetMaximum(1.1);
  h_topTagEffNpv->SetTitle("Top Tagging Efficiency - 8 TeV");
  h_topTagEffNpv->SetMinimum(0.0);

  fit_topTagEffNpv->Draw("Same");
  fit_topTagEffNpv->SetLineColor(1);

  h_topTagEffNpv_400->Draw("ESAME");
  h_topTagEffNpv_400->SetMarkerStyle(7);
  h_topTagEffNpv_400->SetMaximum(1.1);
  h_topTagEffNpv_400->SetLineColor(kMagenta+1);
  h_topTagEffNpv_400->SetMarkerColor(kMagenta+1);

  fit_topTagEffNpv_400->Draw("Same");
  fit_topTagEffNpv_400->SetLineColor(kMagenta+1);

  h_topTagEffNpv_500->Draw("ESAME");
  h_topTagEffNpv_500->SetMarkerStyle(7);
  h_topTagEffNpv_500->SetMaximum(1.1);
  h_topTagEffNpv_500->SetLineColor(kBlue);
  h_topTagEffNpv_500->SetMarkerColor(kBlue);
 
  fit_topTagEffNpv_500->Draw("Same");
  fit_topTagEffNpv_500->SetLineColor(kBlue);

  h_topTagEffNpv_600->Draw("ESAME");
  h_topTagEffNpv_600->SetMarkerStyle(7);
  h_topTagEffNpv_600->SetMaximum(1.1);
  h_topTagEffNpv_600->SetLineColor(kCyan+1);
  h_topTagEffNpv_600->SetMarkerColor(kCyan+1);
 
  fit_topTagEffNpv_600->Draw("Same");
  fit_topTagEffNpv_600->SetLineColor(kCyan+1);

  h_topTagEffNpv_700->Draw("ESAME");
  h_topTagEffNpv_700->SetMarkerStyle(7);
  h_topTagEffNpv_700->SetMaximum(1.1);
  h_topTagEffNpv_700->SetLineColor(kGreen+2);
  h_topTagEffNpv_700->SetMarkerColor(kGreen+2);
 
  fit_topTagEffNpv_700->Draw("Same");
  fit_topTagEffNpv_700->SetLineColor(kGreen+2);

  //h_topTagEffPt->SetTitle("Top Tagging Efficiency - 8 TeV, 1000+ Invt M");

 //legend 
  TLegend *legend_topTagEffNpv = new TLegend(0.2,0.65,0.45,0.88);
  legend_topTagEffNpv->AddEntry(h_topTagEffNpv,"No Pt Cut","LPE");
  legend_topTagEffNpv->AddEntry(h_topTagEffNpv_400,"Pt > 400 GeV","LPE");
  legend_topTagEffNpv->AddEntry(h_topTagEffNpv_500,"Pt > 500 GeV","LPE");
  legend_topTagEffNpv->AddEntry(h_topTagEffNpv_600,"Pt > 600 GeV","LPE");
  legend_topTagEffNpv->AddEntry(h_topTagEffNpv_700,"Pt > 700 GeV","LPE");
  legend_topTagEffNpv->SetFillColor(kWhite); legend_topTagEffNpv->Draw("Same");
  */
}
  
