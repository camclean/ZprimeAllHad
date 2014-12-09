#if !defined(__CINT__) && !defined(__MAKECINT__)
#include<TROOT.h>
#include<TFile.h>
#include<vector>
#include<TChain.h>
#include<TCanvas.h>
#include<TH1.h>
#include<TF1.h>
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
#include<TSystem.h>
#include<TApplication.h>
//#include "boost/shared_ptr.hpp"
#include "/uscms_data/d3/camclean/CSA14/topTaggingEfficiency/CMSSW_7_0_6_patch1/src/Analysis/FWCore/FWLite/interface/AutoLibraryLoader.h"
#include "/uscms_data/d3/camclean/CSA14/topTaggingEfficiency/CMSSW_7_0_6_patch1/src/Analysis/DataFormats/FWLite/interface/Handle.h"
#include "/uscms_data/d3/camclean/CSA14/topTaggingEfficiency/CMSSW_7_0_6_patch1/src/Analysis/DataFormats/FWLite/interface/ChainEvent.h"
#endif

using namespace std;

int main(){
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(0000000000);
  gStyle->SetTitleBorderSize(0);
  //gStyle->SetTitleAlign(0); 

  gSystem->Load("libFWCoreFWLite.so"); 
  gSystem->Load("libDataFormatsFWLite.so");
  AutoLibraryLoader::enable();
  /*
  int nbins_pt = 35;
  float bins_pt[36] = {0,100,200,220,240,260,280,300,320,340,360,380,400,420,440,460,480,500,520,540,560,580,600,700,800,900,1000,2000};                                    
  */
  int nbins_npv = 42;                                                                                                                                                                                   
  float bins_npv[43] = {0,5,10,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,50,55,60};
 
  /////////////////////////////////                                                                                                                                                         
  //// No Mass Grooming Techniques                                                                                                                                                               
  /////////////////////////////////  

  /////pt histograms                                                                                                                                                                                 
  TH1F *hist_ZPrime_looseBtag_topTagEffPt = new TH1F("hist_ZPrime_looseBtag_topTagEffPt","Top Tagging Efficiency (Pt) - 13 TeV (4 TeV Narrow Z Prime to t#bar{t}); pt; Efficiency",125,0,2500);
  TH1F *hist_ZPrime_looseBtag_tagJet1pt = new TH1F("hist_ZPrime_looseBtag_tagJet1pt","Top Tagging Efficiency - 13 TeV; pt; Efficiency",125,0,2500);
  TH1F *hist_ZPrime_looseBtag_tagJet2pt = new TH1F("hist_ZPrime_looseBtag_tagJet2pt","Jet 2 Pt - 13 TeV; pt; Events",125,0,2500);
  //TH1F *hist_ZPrime_looseBtag_jetPt = new TH1F("hist_ZPrime_looseBtag_jetPt","Jet Pt - 13 TeV; pt; Events",125,0,2500);                                                                                                                  
  TH1F *hist_ZPrime_looseBtag_jet1pt = new TH1F("hist_ZPrime_looseBtag_jet1pt","Generated Top 1 Pt - 13 TeV; pt; Events",125,0,2500);
  TH1F *hist_ZPrime_looseBtag_jet2pt = new TH1F("hist_ZPrime_looseBtag_jet2pt","Generated Top 2 Pt - 13 TeV; pt; Events",125,0,2500);
  //TH1F *hist_ZPrime_looseBtag_genTopPt = new TH1F("hist_ZPrime_looseBtag_genTopPt","Generated Top Pt - 13 TeV; pt; Events",125,0,2500);                                                                                                  
  hist_ZPrime_looseBtag_tagJet1pt->Sumw2();
  hist_ZPrime_looseBtag_tagJet2pt->Sumw2();
  hist_ZPrime_looseBtag_jet1pt->Sumw2();
  hist_ZPrime_looseBtag_jet2pt->Sumw2();

  /////pileup histograms - no pt cut                                                                                                                                                                     
  TH1F *hist_ZPrime_looseBtag_topTagEffNpv = new TH1F("hist_ZPrime_looseBtag_topTagEffNpv","Top Tagging Efficiency (Npv)- 13 TeV (4 TeV Narrow Z Prime to t#bar{t}); Number of Primary Vertices; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_tagNpv1 = new TH1F("hist_ZPrime_looseBtag_tagNpv1","Top Tagging Efficiency - 13 TeV; Npv; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_tagNpv2 = new TH1F("hist_ZPrime_looseBtag_tagNpv2","Jet 2 Pt - 13 TeV; Npt; Events",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_npv1 = new TH1F("hist_ZPrime_looseBtag_npv1","Generated Top 1 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_npv2 = new TH1F("hist_ZPrime_looseBtag_npv2","Generated Top 2 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);

  hist_ZPrime_looseBtag_tagNpv1->Sumw2();
  hist_ZPrime_looseBtag_tagNpv2->Sumw2();
  hist_ZPrime_looseBtag_npv1->Sumw2();
  hist_ZPrime_looseBtag_npv2->Sumw2();

  /////pileup histograms - pt > 400 GeV                                                                                                                                                                  
  TH1F *hist_ZPrime_looseBtag_topTagEffNpv_400 = new TH1F("hist_ZPrime_looseBtag_topTagEffNpv_400","Top Tagging Efficiency (Npv)- 13 TeV; Number of Primary Vertices; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_tagNpv1_400 = new TH1F("hist_ZPrime_looseBtag_tagNpv1_400","Top Tagging Efficiency - 13 TeV; Npv; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_tagNpv2_400 = new TH1F("hist_ZPrime_looseBtag_tagNpv2_400","Jet 2 Pt - 13 TeV; Npt; Events",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_npv1_400 = new TH1F("hist_ZPrime_looseBtag_npv1_400","Generated Top 1 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_npv2_400 = new TH1F("hist_ZPrime_looseBtag_npv2_400","Generated Top 2 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);

  hist_ZPrime_looseBtag_tagNpv1_400->Sumw2();
  hist_ZPrime_looseBtag_tagNpv2_400->Sumw2();
  hist_ZPrime_looseBtag_npv1_400->Sumw2();
  hist_ZPrime_looseBtag_npv2_400->Sumw2();

  /////pileup histograms - pt > 500 GeV                                                                                                                                                                  
  TH1F *hist_ZPrime_looseBtag_topTagEffNpv_500 = new TH1F("hist_ZPrime_looseBtag_topTagEffNpv_500","Top Tagging Efficiency (Npv)- 13 TeV; Number of Primary Vertices; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_tagNpv1_500 = new TH1F("hist_ZPrime_looseBtag_tagNpv1_500","Top Tagging Efficiency - 13 TeV; Npv; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_tagNpv2_500 = new TH1F("hist_ZPrime_looseBtag_tagNpv2_500","Jet 2 Pt - 13 TeV; Npt; Events",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_npv1_500 = new TH1F("hist_ZPrime_looseBtag_npv1_500","Generated Top 1 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_npv2_500 = new TH1F("hist_ZPrime_looseBtag_npv2_500","Generated Top 2 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);

  hist_ZPrime_looseBtag_tagNpv1_500->Sumw2();
  hist_ZPrime_looseBtag_tagNpv2_500->Sumw2();
  hist_ZPrime_looseBtag_npv1_500->Sumw2();
  hist_ZPrime_looseBtag_npv2_500->Sumw2();

  /////pileup histograms - pt > 600 GeV                                                                                                                                                                  
  TH1F *hist_ZPrime_looseBtag_topTagEffNpv_600 = new TH1F("hist_ZPrime_looseBtag_topTagEffNpv_600","Top Tagging Efficiency (Npv)- 13 TeV; Number of Primary Vertices; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_tagNpv1_600 = new TH1F("hist_ZPrime_looseBtag_tagNpv1_600","Top Tagging Efficiency - 13 TeV; Npv; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_tagNpv2_600 = new TH1F("hist_ZPrime_looseBtag_tagNpv2_600","Jet 2 Pt - 13 TeV; Npt; Events",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_npv1_600 = new TH1F("hist_ZPrime_looseBtag_npv1_600","Generated Top 1 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_npv2_600 = new TH1F("hist_ZPrime_looseBtag_npv2_600","Generated Top 2 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);

  hist_ZPrime_looseBtag_tagNpv1_600->Sumw2();
  hist_ZPrime_looseBtag_tagNpv2_600->Sumw2();
  hist_ZPrime_looseBtag_npv1_600->Sumw2();
  hist_ZPrime_looseBtag_npv2_600->Sumw2();

  /////pileup histograms - pt > 700 GeV                                                                                                                                                                  
  TH1F *hist_ZPrime_looseBtag_topTagEffNpv_700 = new TH1F("hist_ZPrime_looseBtag_topTagEffNpv_700","Top Tagging Efficiency (Npv)- 13 TeV; Number of Primary Vertices; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_tagNpv1_700 = new TH1F("hist_ZPrime_looseBtag_tagNpv1_700","Top Tagging Efficiency - 13 TeV; Npv; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_tagNpv2_700 = new TH1F("hist_ZPrime_looseBtag_tagNpv2_700","Jet 2 Pt - 13 TeV; Npt; Events",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_npv1_700 = new TH1F("hist_ZPrime_looseBtag_npv1_700","Generated Top 1 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_npv2_700 = new TH1F("hist_ZPrime_looseBtag_npv2_700","Generated Top 2 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);

  hist_ZPrime_looseBtag_tagNpv1_700->Sumw2();
  hist_ZPrime_looseBtag_tagNpv2_700->Sumw2();
  hist_ZPrime_looseBtag_npv1_700->Sumw2();
  hist_ZPrime_looseBtag_npv2_700->Sumw2();

  /////////////////////////////////                                                                                                                                                                   
  //// AK8 Filtered Jets                                                                                                                                                                           
  /////////////////////////////////  

  /////pt histograms                                                                                                                                                                          
  TH1F *hist_ZPrime_looseBtag_filtered_topTagEffPt = new TH1F("hist_ZPrime_looseBtag_filtered_topTagEffPt","Top Tagging Efficiency (Pt) - 13 TeV (4 TeV Narrow Z Prime to t#bar{t}); pt; Efficiency",125,0,2500);
  TH1F *hist_ZPrime_looseBtag_filtered_tagJet1pt = new TH1F("hist_ZPrime_looseBtag_filtered_tagJet1pt","Top Tagging Efficiency - 13 TeV; pt; Efficiency",125,0,2500);
  TH1F *hist_ZPrime_looseBtag_filtered_tagJet2pt = new TH1F("hist_ZPrime_looseBtag_filtered_tagJet2pt","Jet 2 Pt - 13 TeV; pt; Events",125,0,2500);
  //TH1F *hist_ZPrime_looseBtag_filtered_jetPt = new TH1F("hist_ZPrime_looseBtag_filtered_jetPt","Jet Pt - 13 TeV; pt; Events",125,0,2500);                                                                                                                  
  TH1F *hist_ZPrime_looseBtag_filtered_jet1pt = new TH1F("hist_ZPrime_looseBtag_filtered_jet1pt","Generated Top 1 Pt - 13 TeV; pt; Events",125,0,2500);
  TH1F *hist_ZPrime_looseBtag_filtered_jet2pt = new TH1F("hist_ZPrime_looseBtag_filtered_jet2pt","Generated Top 2 Pt - 13 TeV; pt; Events",125,0,2500);
  //TH1F *hist_ZPrime_looseBtag_filtered_genTopPt = new TH1F("hist_ZPrime_looseBtag_filtered_genTopPt","Generated Top Pt - 13 TeV; pt; Events",125,0,2500);                                                                                                  
  hist_ZPrime_looseBtag_filtered_tagJet1pt->Sumw2();
  hist_ZPrime_looseBtag_filtered_tagJet2pt->Sumw2();
  hist_ZPrime_looseBtag_filtered_jet1pt->Sumw2();
  hist_ZPrime_looseBtag_filtered_jet2pt->Sumw2();

  /////pileup histograms - no pt cut                                                                                                                                                                 
  TH1F *hist_ZPrime_looseBtag_filtered_topTagEffNpv = new TH1F("hist_ZPrime_looseBtag_filtered_topTagEffNpv","Top Tagging Efficiency (Npv)- 13 TeV (4 TeV Narrow Z Prime to t#bar{t}); Number of Primary Vertices; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_filtered_tagNpv1 = new TH1F("hist_ZPrime_looseBtag_filtered_tagNpv1","Top Tagging Efficiency - 13 TeV; Npv; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_filtered_tagNpv2 = new TH1F("hist_ZPrime_looseBtag_filtered_tagNpv2","Jet 2 Pt - 13 TeV; Npt; Events",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_filtered_npv1 = new TH1F("hist_ZPrime_looseBtag_filtered_npv1","Generated Top 1 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_filtered_npv2 = new TH1F("hist_ZPrime_looseBtag_filtered_npv2","Generated Top 2 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);

  hist_ZPrime_looseBtag_filtered_tagNpv1->Sumw2();
  hist_ZPrime_looseBtag_filtered_tagNpv2->Sumw2();
  hist_ZPrime_looseBtag_filtered_npv1->Sumw2();
  hist_ZPrime_looseBtag_filtered_npv2->Sumw2();

  /////pileup histograms - pt > 400 GeV                                                                                                                                                                  
  TH1F *hist_ZPrime_looseBtag_filtered_topTagEffNpv_400 = new TH1F("hist_ZPrime_looseBtag_filtered_topTagEffNpv_400","Top Tagging Efficiency (Npv)- 13 TeV; Number of Primary Vertices; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_filtered_tagNpv1_400 = new TH1F("hist_ZPrime_looseBtag_filtered_tagNpv1_400","Top Tagging Efficiency - 13 TeV; Npv; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_filtered_tagNpv2_400 = new TH1F("hist_ZPrime_looseBtag_filtered_tagNpv2_400","Jet 2 Pt - 13 TeV; Npt; Events",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_filtered_npv1_400 = new TH1F("hist_ZPrime_looseBtag_filtered_npv1_400","Generated Top 1 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_filtered_npv2_400 = new TH1F("hist_ZPrime_looseBtag_filtered_npv2_400","Generated Top 2 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);

  hist_ZPrime_looseBtag_filtered_tagNpv1_400->Sumw2();
  hist_ZPrime_looseBtag_filtered_tagNpv2_400->Sumw2();
  hist_ZPrime_looseBtag_filtered_npv1_400->Sumw2();
  hist_ZPrime_looseBtag_filtered_npv2_400->Sumw2();

  /////pileup histograms - pt > 500 GeV                                                                                                                                                                  
  TH1F *hist_ZPrime_looseBtag_filtered_topTagEffNpv_500 = new TH1F("hist_ZPrime_looseBtag_filtered_topTagEffNpv_500","Top Tagging Efficiency (Npv)- 13 TeV; Number of Primary Vertices; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_filtered_tagNpv1_500 = new TH1F("hist_ZPrime_looseBtag_filtered_tagNpv1_500","Top Tagging Efficiency - 13 TeV; Npv; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_filtered_tagNpv2_500 = new TH1F("hist_ZPrime_looseBtag_filtered_tagNpv2_500","Jet 2 Pt - 13 TeV; Npt; Events",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_filtered_npv1_500 = new TH1F("hist_ZPrime_looseBtag_filtered_npv1_500","Generated Top 1 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_filtered_npv2_500 = new TH1F("hist_ZPrime_looseBtag_filtered_npv2_500","Generated Top 2 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);

  hist_ZPrime_looseBtag_filtered_tagNpv1_500->Sumw2();
  hist_ZPrime_looseBtag_filtered_tagNpv2_500->Sumw2();
  hist_ZPrime_looseBtag_filtered_npv1_500->Sumw2();
  hist_ZPrime_looseBtag_filtered_npv2_500->Sumw2();

  /////pileup histograms - pt > 600 GeV                                                                                                                                                                  
  TH1F *hist_ZPrime_looseBtag_filtered_topTagEffNpv_600 = new TH1F("hist_ZPrime_looseBtag_filtered_topTagEffNpv_600","Top Tagging Efficiency (Npv)- 13 TeV; Number of Primary Vertices; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_filtered_tagNpv1_600 = new TH1F("hist_ZPrime_looseBtag_filtered_tagNpv1_600","Top Tagging Efficiency - 13 TeV; Npv; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_filtered_tagNpv2_600 = new TH1F("hist_ZPrime_looseBtag_filtered_tagNpv2_600","Jet 2 Pt - 13 TeV; Npt; Events",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_filtered_npv1_600 = new TH1F("hist_ZPrime_looseBtag_filtered_npv1_600","Generated Top 1 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_filtered_npv2_600 = new TH1F("hist_ZPrime_looseBtag_filtered_npv2_600","Generated Top 2 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);

  hist_ZPrime_looseBtag_filtered_tagNpv1_600->Sumw2();
  hist_ZPrime_looseBtag_filtered_tagNpv2_600->Sumw2();
  hist_ZPrime_looseBtag_filtered_npv1_600->Sumw2();
  hist_ZPrime_looseBtag_filtered_npv2_600->Sumw2();

  /////pileup histograms - pt > 700 GeV                                                                                                                                                                  
  TH1F *hist_ZPrime_looseBtag_filtered_topTagEffNpv_700 = new TH1F("hist_ZPrime_looseBtag_filtered_topTagEffNpv_700","Top Tagging Efficiency (Npv)- 13 TeV; Number of Primary Vertices; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_filtered_tagNpv1_700 = new TH1F("hist_ZPrime_looseBtag_filtered_tagNpv1_700","Top Tagging Efficiency - 13 TeV; Npv; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_filtered_tagNpv2_700 = new TH1F("hist_ZPrime_looseBtag_filtered_tagNpv2_700","Jet 2 Pt - 13 TeV; Npt; Events",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_filtered_npv1_700 = new TH1F("hist_ZPrime_looseBtag_filtered_npv1_700","Generated Top 1 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_filtered_npv2_700 = new TH1F("hist_ZPrime_looseBtag_filtered_npv2_700","Generated Top 2 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);

  hist_ZPrime_looseBtag_filtered_tagNpv1_700->Sumw2();
  hist_ZPrime_looseBtag_filtered_tagNpv2_700->Sumw2();
  hist_ZPrime_looseBtag_filtered_npv1_700->Sumw2();
  hist_ZPrime_looseBtag_filtered_npv2_700->Sumw2();

  /////////////////////////////////                                                                                                                                                                   
  //// AK8 Pruned Jets                                                                                                                                                                           
  /////////////////////////////////  

  /////pt histograms                                                                                                                                                                          
  TH1F *hist_ZPrime_looseBtag_pruned_topTagEffPt = new TH1F("hist_ZPrime_looseBtag_pruned_topTagEffPt","Top Tagging Efficiency (Pt) - 13 TeV (4 TeV Narrow Z Prime to t#bar{t}); pt; Efficiency",125,0,2500);
  TH1F *hist_ZPrime_looseBtag_pruned_tagJet1pt = new TH1F("hist_ZPrime_looseBtag_pruned_tagJet1pt","Top Tagging Efficiency - 13 TeV; pt; Efficiency",125,0,2500);
  TH1F *hist_ZPrime_looseBtag_pruned_tagJet2pt = new TH1F("hist_ZPrime_looseBtag_pruned_tagJet2pt","Jet 2 Pt - 13 TeV; pt; Events",125,0,2500);
  //TH1F *hist_ZPrime_looseBtag_pruned_jetPt = new TH1F("hist_ZPrime_looseBtag_pruned_jetPt","Jet Pt - 13 TeV; pt; Events",125,0,2500);                                                                                                                  
  TH1F *hist_ZPrime_looseBtag_pruned_jet1pt = new TH1F("hist_ZPrime_looseBtag_pruned_jet1pt","Generated Top 1 Pt - 13 TeV; pt; Events",125,0,2500);
  TH1F *hist_ZPrime_looseBtag_pruned_jet2pt = new TH1F("hist_ZPrime_looseBtag_pruned_jet2pt","Generated Top 2 Pt - 13 TeV; pt; Events",125,0,2500);
  //TH1F *hist_ZPrime_looseBtag_pruned_genTopPt = new TH1F("hist_ZPrime_looseBtag_pruned_genTopPt","Generated Top Pt - 13 TeV; pt; Events",125,0,2500);                                                                                                  
  hist_ZPrime_looseBtag_pruned_tagJet1pt->Sumw2();
  hist_ZPrime_looseBtag_pruned_tagJet2pt->Sumw2();
  hist_ZPrime_looseBtag_pruned_jet1pt->Sumw2();
  hist_ZPrime_looseBtag_pruned_jet2pt->Sumw2();

  /////pileup histograms - no pt cut                                                                                                                                                                 
  TH1F *hist_ZPrime_looseBtag_pruned_topTagEffNpv = new TH1F("hist_ZPrime_looseBtag_pruned_topTagEffNpv","Top Tagging Efficiency (Npv)- 13 TeV (4 TeV Narrow Z Prime to t#bar{t}); Number of Primary Vertices; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_pruned_tagNpv1 = new TH1F("hist_ZPrime_looseBtag_pruned_tagNpv1","Top Tagging Efficiency - 13 TeV; Npv; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_pruned_tagNpv2 = new TH1F("hist_ZPrime_looseBtag_pruned_tagNpv2","Jet 2 Pt - 13 TeV; Npt; Events",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_pruned_npv1 = new TH1F("hist_ZPrime_looseBtag_pruned_npv1","Generated Top 1 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_pruned_npv2 = new TH1F("hist_ZPrime_looseBtag_pruned_npv2","Generated Top 2 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);

  hist_ZPrime_looseBtag_pruned_tagNpv1->Sumw2();
  hist_ZPrime_looseBtag_pruned_tagNpv2->Sumw2();
  hist_ZPrime_looseBtag_pruned_npv1->Sumw2();
  hist_ZPrime_looseBtag_pruned_npv2->Sumw2();

  /////pileup histograms - pt > 400 GeV                                                                                                                                                                  
  TH1F *hist_ZPrime_looseBtag_pruned_topTagEffNpv_400 = new TH1F("hist_ZPrime_looseBtag_pruned_topTagEffNpv_400","Top Tagging Efficiency (Npv)- 13 TeV; Number of Primary Vertices; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_pruned_tagNpv1_400 = new TH1F("hist_ZPrime_looseBtag_pruned_tagNpv1_400","Top Tagging Efficiency - 13 TeV; Npv; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_pruned_tagNpv2_400 = new TH1F("hist_ZPrime_looseBtag_pruned_tagNpv2_400","Jet 2 Pt - 13 TeV; Npt; Events",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_pruned_npv1_400 = new TH1F("hist_ZPrime_looseBtag_pruned_npv1_400","Generated Top 1 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_pruned_npv2_400 = new TH1F("hist_ZPrime_looseBtag_pruned_npv2_400","Generated Top 2 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);

  hist_ZPrime_looseBtag_pruned_tagNpv1_400->Sumw2();
  hist_ZPrime_looseBtag_pruned_tagNpv2_400->Sumw2();
  hist_ZPrime_looseBtag_pruned_npv1_400->Sumw2();
  hist_ZPrime_looseBtag_pruned_npv2_400->Sumw2();

  /////pileup histograms - pt > 500 GeV                                                                                                                                                                  
  TH1F *hist_ZPrime_looseBtag_pruned_topTagEffNpv_500 = new TH1F("hist_ZPrime_looseBtag_pruned_topTagEffNpv_500","Top Tagging Efficiency (Npv)- 13 TeV; Number of Primary Vertices; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_pruned_tagNpv1_500 = new TH1F("hist_ZPrime_looseBtag_pruned_tagNpv1_500","Top Tagging Efficiency - 13 TeV; Npv; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_pruned_tagNpv2_500 = new TH1F("hist_ZPrime_looseBtag_pruned_tagNpv2_500","Jet 2 Pt - 13 TeV; Npt; Events",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_pruned_npv1_500 = new TH1F("hist_ZPrime_looseBtag_pruned_npv1_500","Generated Top 1 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_pruned_npv2_500 = new TH1F("hist_ZPrime_looseBtag_pruned_npv2_500","Generated Top 2 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);

  hist_ZPrime_looseBtag_pruned_tagNpv1_500->Sumw2();
  hist_ZPrime_looseBtag_pruned_tagNpv2_500->Sumw2();
  hist_ZPrime_looseBtag_pruned_npv1_500->Sumw2();
  hist_ZPrime_looseBtag_pruned_npv2_500->Sumw2();

  /////pileup histograms - pt > 600 GeV                                                                                                                                                                  
  TH1F *hist_ZPrime_looseBtag_pruned_topTagEffNpv_600 = new TH1F("hist_ZPrime_looseBtag_pruned_topTagEffNpv_600","Top Tagging Efficiency (Npv)- 13 TeV; Number of Primary Vertices; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_pruned_tagNpv1_600 = new TH1F("hist_ZPrime_looseBtag_pruned_tagNpv1_600","Top Tagging Efficiency - 13 TeV; Npv; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_pruned_tagNpv2_600 = new TH1F("hist_ZPrime_looseBtag_pruned_tagNpv2_600","Jet 2 Pt - 13 TeV; Npt; Events",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_pruned_npv1_600 = new TH1F("hist_ZPrime_looseBtag_pruned_npv1_600","Generated Top 1 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_pruned_npv2_600 = new TH1F("hist_ZPrime_looseBtag_pruned_npv2_600","Generated Top 2 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);

  hist_ZPrime_looseBtag_pruned_tagNpv1_600->Sumw2();
  hist_ZPrime_looseBtag_pruned_tagNpv2_600->Sumw2();
  hist_ZPrime_looseBtag_pruned_npv1_600->Sumw2();
  hist_ZPrime_looseBtag_pruned_npv2_600->Sumw2();

  /////pileup histograms - pt > 700 GeV                                                                                                                                                                  
  TH1F *hist_ZPrime_looseBtag_pruned_topTagEffNpv_700 = new TH1F("hist_ZPrime_looseBtag_pruned_topTagEffNpv_700","Top Tagging Efficiency (Npv)- 13 TeV; Number of Primary Vertices; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_pruned_tagNpv1_700 = new TH1F("hist_ZPrime_looseBtag_pruned_tagNpv1_700","Top Tagging Efficiency - 13 TeV; Npv; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_pruned_tagNpv2_700 = new TH1F("hist_ZPrime_looseBtag_pruned_tagNpv2_700","Jet 2 Pt - 13 TeV; Npt; Events",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_pruned_npv1_700 = new TH1F("hist_ZPrime_looseBtag_pruned_npv1_700","Generated Top 1 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_pruned_npv2_700 = new TH1F("hist_ZPrime_looseBtag_pruned_npv2_700","Generated Top 2 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);

  hist_ZPrime_looseBtag_pruned_tagNpv1_700->Sumw2();
  hist_ZPrime_looseBtag_pruned_tagNpv2_700->Sumw2();
  hist_ZPrime_looseBtag_pruned_npv1_700->Sumw2();
  hist_ZPrime_looseBtag_pruned_npv2_700->Sumw2();

  /////////////////////////////////                                                                                                                                                                   
  //// AK8 Trimmed Jets                                                                                                                                                                           
  /////////////////////////////////  

  /////pt histograms                                                                                                                                                                          
  TH1F *hist_ZPrime_looseBtag_trimmed_topTagEffPt = new TH1F("hist_ZPrime_looseBtag_trimmed_topTagEffPt","Top Tagging Efficiency (Pt) - 13 TeV (4 TeV Narrow Z Prime to t#bar{t}); pt; Efficiency",125,0,2500);
  TH1F *hist_ZPrime_looseBtag_trimmed_tagJet1pt = new TH1F("hist_ZPrime_looseBtag_trimmed_tagJet1pt","Top Tagging Efficiency - 13 TeV; pt; Efficiency",125,0,2500);
  TH1F *hist_ZPrime_looseBtag_trimmed_tagJet2pt = new TH1F("hist_ZPrime_looseBtag_trimmed_tagJet2pt","Jet 2 Pt - 13 TeV; pt; Events",125,0,2500);
  //TH1F *hist_ZPrime_looseBtag_trimmed_jetPt = new TH1F("hist_ZPrime_looseBtag_trimmed_jetPt","Jet Pt - 13 TeV; pt; Events",125,0,2500);                                                                                                                  
  TH1F *hist_ZPrime_looseBtag_trimmed_jet1pt = new TH1F("hist_ZPrime_looseBtag_trimmed_jet1pt","Generated Top 1 Pt - 13 TeV; pt; Events",125,0,2500);
  TH1F *hist_ZPrime_looseBtag_trimmed_jet2pt = new TH1F("hist_ZPrime_looseBtag_trimmed_jet2pt","Generated Top 2 Pt - 13 TeV; pt; Events",125,0,2500);
  //TH1F *hist_ZPrime_looseBtag_trimmed_genTopPt = new TH1F("hist_ZPrime_looseBtag_trimmed_genTopPt","Generated Top Pt - 13 TeV; pt; Events",125,0,2500);                                                                                                  
  hist_ZPrime_looseBtag_trimmed_tagJet1pt->Sumw2();
  hist_ZPrime_looseBtag_trimmed_tagJet2pt->Sumw2();
  hist_ZPrime_looseBtag_trimmed_jet1pt->Sumw2();
  hist_ZPrime_looseBtag_trimmed_jet2pt->Sumw2();

  /////pileup histograms - no pt cut                                                                                                                                                                 
  TH1F *hist_ZPrime_looseBtag_trimmed_topTagEffNpv = new TH1F("hist_ZPrime_looseBtag_trimmed_topTagEffNpv","Top Tagging Efficiency (Npv)- 13 TeV (4 TeV Narrow Z Prime to t#bar{t}); Number of Primary Vertices; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_trimmed_tagNpv1 = new TH1F("hist_ZPrime_looseBtag_trimmed_tagNpv1","Top Tagging Efficiency - 13 TeV; Npv; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_trimmed_tagNpv2 = new TH1F("hist_ZPrime_looseBtag_trimmed_tagNpv2","Jet 2 Pt - 13 TeV; Npt; Events",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_trimmed_npv1 = new TH1F("hist_ZPrime_looseBtag_trimmed_npv1","Generated Top 1 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_trimmed_npv2 = new TH1F("hist_ZPrime_looseBtag_trimmed_npv2","Generated Top 2 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);

  hist_ZPrime_looseBtag_trimmed_tagNpv1->Sumw2();
  hist_ZPrime_looseBtag_trimmed_tagNpv2->Sumw2();
  hist_ZPrime_looseBtag_trimmed_npv1->Sumw2();
  hist_ZPrime_looseBtag_trimmed_npv2->Sumw2();

  /////pileup histograms - pt > 400 GeV                                                                                                                                                                  
  TH1F *hist_ZPrime_looseBtag_trimmed_topTagEffNpv_400 = new TH1F("hist_ZPrime_looseBtag_trimmed_topTagEffNpv_400","Top Tagging Efficiency (Npv)- 13 TeV; Number of Primary Vertices; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_trimmed_tagNpv1_400 = new TH1F("hist_ZPrime_looseBtag_trimmed_tagNpv1_400","Top Tagging Efficiency - 13 TeV; Npv; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_trimmed_tagNpv2_400 = new TH1F("hist_ZPrime_looseBtag_trimmed_tagNpv2_400","Jet 2 Pt - 13 TeV; Npt; Events",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_trimmed_npv1_400 = new TH1F("hist_ZPrime_looseBtag_trimmed_npv1_400","Generated Top 1 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_trimmed_npv2_400 = new TH1F("hist_ZPrime_looseBtag_trimmed_npv2_400","Generated Top 2 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);

  hist_ZPrime_looseBtag_trimmed_tagNpv1_400->Sumw2();
  hist_ZPrime_looseBtag_trimmed_tagNpv2_400->Sumw2();
  hist_ZPrime_looseBtag_trimmed_npv1_400->Sumw2();
  hist_ZPrime_looseBtag_trimmed_npv2_400->Sumw2();

  /////pileup histograms - pt > 500 GeV                                                                                                                                                                  
  TH1F *hist_ZPrime_looseBtag_trimmed_topTagEffNpv_500 = new TH1F("hist_ZPrime_looseBtag_trimmed_topTagEffNpv_500","Top Tagging Efficiency (Npv)- 13 TeV; Number of Primary Vertices; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_trimmed_tagNpv1_500 = new TH1F("hist_ZPrime_looseBtag_trimmed_tagNpv1_500","Top Tagging Efficiency - 13 TeV; Npv; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_trimmed_tagNpv2_500 = new TH1F("hist_ZPrime_looseBtag_trimmed_tagNpv2_500","Jet 2 Pt - 13 TeV; Npt; Events",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_trimmed_npv1_500 = new TH1F("hist_ZPrime_looseBtag_trimmed_npv1_500","Generated Top 1 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_trimmed_npv2_500 = new TH1F("hist_ZPrime_looseBtag_trimmed_npv2_500","Generated Top 2 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);

  hist_ZPrime_looseBtag_trimmed_tagNpv1_500->Sumw2();
  hist_ZPrime_looseBtag_trimmed_tagNpv2_500->Sumw2();
  hist_ZPrime_looseBtag_trimmed_npv1_500->Sumw2();
  hist_ZPrime_looseBtag_trimmed_npv2_500->Sumw2();

  /////pileup histograms - pt > 600 GeV                                                                                                                                                                  
  TH1F *hist_ZPrime_looseBtag_trimmed_topTagEffNpv_600 = new TH1F("hist_ZPrime_looseBtag_trimmed_topTagEffNpv_600","Top Tagging Efficiency (Npv)- 13 TeV; Number of Primary Vertices; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_trimmed_tagNpv1_600 = new TH1F("hist_ZPrime_looseBtag_trimmed_tagNpv1_600","Top Tagging Efficiency - 13 TeV; Npv; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_trimmed_tagNpv2_600 = new TH1F("hist_ZPrime_looseBtag_trimmed_tagNpv2_600","Jet 2 Pt - 13 TeV; Npt; Events",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_trimmed_npv1_600 = new TH1F("hist_ZPrime_looseBtag_trimmed_npv1_600","Generated Top 1 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_trimmed_npv2_600 = new TH1F("hist_ZPrime_looseBtag_trimmed_npv2_600","Generated Top 2 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);

  hist_ZPrime_looseBtag_trimmed_tagNpv1_600->Sumw2();
  hist_ZPrime_looseBtag_trimmed_tagNpv2_600->Sumw2();
  hist_ZPrime_looseBtag_trimmed_npv1_600->Sumw2();
  hist_ZPrime_looseBtag_trimmed_npv2_600->Sumw2();

  /////pileup histograms - pt > 700 GeV                                                                                                                                                                  
  TH1F *hist_ZPrime_looseBtag_trimmed_topTagEffNpv_700 = new TH1F("hist_ZPrime_looseBtag_trimmed_topTagEffNpv_700","Top Tagging Efficiency (Npv)- 13 TeV; Number of Primary Vertices; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_trimmed_tagNpv1_700 = new TH1F("hist_ZPrime_looseBtag_trimmed_tagNpv1_700","Top Tagging Efficiency - 13 TeV; Npv; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_trimmed_tagNpv2_700 = new TH1F("hist_ZPrime_looseBtag_trimmed_tagNpv2_700","Jet 2 Pt - 13 TeV; Npt; Events",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_trimmed_npv1_700 = new TH1F("hist_ZPrime_looseBtag_trimmed_npv1_700","Generated Top 1 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);
  TH1F *hist_ZPrime_looseBtag_trimmed_npv2_700 = new TH1F("hist_ZPrime_looseBtag_trimmed_npv2_700","Generated Top 2 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);

  hist_ZPrime_looseBtag_trimmed_tagNpv1_700->Sumw2();
  hist_ZPrime_looseBtag_trimmed_tagNpv2_700->Sumw2();
  hist_ZPrime_looseBtag_trimmed_npv1_700->Sumw2();
  hist_ZPrime_looseBtag_trimmed_npv2_700->Sumw2();
    
  vector<string> fileNames;

  string line;
  ifstream myfile ("rootFiles_Zprime13TeV.txt");
  if (myfile.is_open()){
      while ( getline (myfile,line) )
	{
	  fileNames.push_back(line);
	}
      myfile.close();
    }
  
  //fileNames.push_back("/uscms_data/d3/camclean/CSA14/topTaggingEfficiency/CMSSW_7_0_6_patch1/src/Analysis/analyzeMiniAOD/RSGluonToTT_M_4000_08_19_2014/res/miniAOD*.root");

  fwlite::ChainEvent ev(fileNames);

  for( ev.toBegin(); ! ev.atEnd(); ++ev) {
    fwlite::Handle<int> h_jet1tagEff;
    fwlite::Handle<int> h_jet2tagEff;
    fwlite::Handle<int> h_AK8jet1tagEff;
    fwlite::Handle<int> h_AK8jet2tagEff;
    fwlite::Handle<unsigned int> h_npv;
    fwlite::Handle<double> h_jet1ptEff;
    fwlite::Handle<double> h_jet2ptEff;
    fwlite::Handle<double> h_jet1maxSubjBDisc;
    fwlite::Handle<double> h_jet2maxSubjBDisc;

    h_jet1tagEff.getByLabel(ev,"miniAOD","jet1tagEff","MiniAOD");
    h_jet2tagEff.getByLabel(ev,"miniAOD","jet2tagEff","MiniAOD");
    h_AK8jet1tagEff.getByLabel(ev,"miniAOD","AK8jet1tagEff","MiniAOD");
    h_AK8jet2tagEff.getByLabel(ev,"miniAOD","AK8jet2tagEff","MiniAOD");
    h_jet1ptEff.getByLabel(ev,"miniAOD","jet1ptEff","MiniAOD");
    h_jet2ptEff.getByLabel(ev,"miniAOD","jet2ptEff","MiniAOD");
    h_npv.getByLabel(ev,"miniAOD","npv","MiniAOD");
    h_jet1maxSubjBDisc.getByLabel(ev,"miniAOD","jet1MaxSubjBDiscEff","MiniAOD");
    h_jet2maxSubjBDisc.getByLabel(ev,"miniAOD","jet2MaxSubjBDiscEff","MiniAOD");

    /////////////////////////////////
    //// No Mass Grooming Techniques
    /////////////////////////////////

    //denominator histograms (no mass grooming) - 0 = top-matched, not top-tagged; 1 = top-matched and top-tagged                                                                 
    if(*h_jet1tagEff == 0 || *h_jet1tagEff == 1){

      hist_ZPrime_looseBtag_npv1->Fill(*h_npv);
      hist_ZPrime_looseBtag_jet1pt->Fill(*h_jet1ptEff);
      
      if(*h_jet1ptEff > 400.){
	hist_ZPrime_looseBtag_npv1_400->Fill(*h_npv);
      }
      if(*h_jet1ptEff > 500.){
	hist_ZPrime_looseBtag_npv1_500->Fill(*h_npv);
      }
      if(*h_jet1ptEff > 600.){
	hist_ZPrime_looseBtag_npv1_600->Fill(*h_npv);
      }
      if(*h_jet1ptEff > 700.){
	hist_ZPrime_looseBtag_npv1_700->Fill(*h_npv);
      }
    }
 
    if(*h_jet2tagEff == 0 || *h_jet2tagEff == 1){
      hist_ZPrime_looseBtag_npv2->Fill(*h_npv);
      hist_ZPrime_looseBtag_jet2pt->Fill(*h_jet2ptEff);
      
      if(*h_jet2ptEff > 400.){
	hist_ZPrime_looseBtag_npv2_400->Fill(*h_npv);
      }
      if(*h_jet2ptEff > 500.){
	hist_ZPrime_looseBtag_npv2_500->Fill(*h_npv);
      }
      if(*h_jet2ptEff > 600.){
	hist_ZPrime_looseBtag_npv2_600->Fill(*h_npv);
      }
      if(*h_jet2ptEff > 700.){
	hist_ZPrime_looseBtag_npv2_700->Fill(*h_npv);
      }
    }

    //numerator histograms                                                                                                                                                                               
    if(*h_jet1tagEff == 1 && *h_jet1maxSubjBDisc > 0.244){
      hist_ZPrime_looseBtag_tagJet1pt->Fill(*h_jet1ptEff);
      hist_ZPrime_looseBtag_tagNpv1->Fill(*h_npv);
      
      if(*h_jet1ptEff > 400.){
        hist_ZPrime_looseBtag_tagNpv1_400->Fill(*h_npv);
      }
      if(*h_jet1ptEff > 500.){
        hist_ZPrime_looseBtag_tagNpv1_500->Fill(*h_npv);
      }
      if(*h_jet1ptEff > 600.){
        hist_ZPrime_looseBtag_tagNpv1_600->Fill(*h_npv);
      }
      if(*h_jet1ptEff > 700.){
        hist_ZPrime_looseBtag_tagNpv1_700->Fill(*h_npv);
      }
    }

    if(*h_jet2tagEff == 1 && *h_jet2maxSubjBDisc > 0.244){
      hist_ZPrime_looseBtag_tagJet2pt->Fill(*h_jet2ptEff);
      hist_ZPrime_looseBtag_tagNpv2->Fill(*h_npv);
      
      if(*h_jet2ptEff > 400.){
        hist_ZPrime_looseBtag_tagNpv2_400->Fill(*h_npv);
      }
      if(*h_jet2ptEff > 500.){
        hist_ZPrime_looseBtag_tagNpv2_500->Fill(*h_npv);
      }
      if(*h_jet2ptEff > 600.){
        hist_ZPrime_looseBtag_tagNpv2_600->Fill(*h_npv);
      }
      if(*h_jet2ptEff > 700.){
        hist_ZPrime_looseBtag_tagNpv2_700->Fill(*h_npv);
	//jet2pt_tag = jet1ptEff;                                                                                                                                                                        
      }
    }

    /////////////////////////////////
    //// AK8 Filtered Jets
    /////////////////////////////////

    int filteredJet1tag_1 = *h_AK8jet1tagEff;
    int filteredJet1tag_2 = *h_AK8jet1tagEff;
    int filteredJet1tag_3 = *h_AK8jet1tagEff;
    int filteredJet2tag_1 = *h_AK8jet2tagEff;
    int filteredJet2tag_2 = *h_AK8jet2tagEff;
    int filteredJet2tag_3 = *h_AK8jet2tagEff;

    //denominator histograms (filtered mass) -  1 = top-matched, not top-tagged; 2 = top-matched and top-tagged                                                                 

    if((filteredJet1tag_1 &= 1) == 1 || (filteredJet1tag_2 &= 2) == 2){
      hist_ZPrime_looseBtag_filtered_npv1->Fill(*h_npv);
      hist_ZPrime_looseBtag_filtered_jet1pt->Fill(*h_jet1ptEff);
      
      if(*h_jet1ptEff > 400.){
	hist_ZPrime_looseBtag_filtered_npv1_400->Fill(*h_npv);
      }
      if(*h_jet1ptEff > 500.){
	hist_ZPrime_looseBtag_filtered_npv1_500->Fill(*h_npv);
      }
      if(*h_jet1ptEff > 600.){
	hist_ZPrime_looseBtag_filtered_npv1_600->Fill(*h_npv);
      }
      if(*h_jet1ptEff > 700.){
	hist_ZPrime_looseBtag_filtered_npv1_700->Fill(*h_npv);
      }
    }
 
    if((filteredJet2tag_1 &= 1) == 1 || (filteredJet2tag_2 &= 2) == 2){
      hist_ZPrime_looseBtag_filtered_npv2->Fill(*h_npv);
      hist_ZPrime_looseBtag_filtered_jet2pt->Fill(*h_jet2ptEff);
      
      if(*h_jet2ptEff > 400.){
	hist_ZPrime_looseBtag_filtered_npv2_400->Fill(*h_npv);
      }
      if(*h_jet2ptEff > 500.){
	hist_ZPrime_looseBtag_filtered_npv2_500->Fill(*h_npv);
      }
      if(*h_jet2ptEff > 600.){
	hist_ZPrime_looseBtag_filtered_npv2_600->Fill(*h_npv);
      }
      if(*h_jet2ptEff > 700.){
	hist_ZPrime_looseBtag_filtered_npv2_700->Fill(*h_npv);
      }
    }

    //numerator histograms                                                                                                                                                                           
    if((filteredJet1tag_3 &= 2) == 2 && *h_jet1maxSubjBDisc > 0.244){
      hist_ZPrime_looseBtag_filtered_tagJet1pt->Fill(*h_jet1ptEff);
      hist_ZPrime_looseBtag_filtered_tagNpv1->Fill(*h_npv);

      if(*h_jet1ptEff > 400.){
        hist_ZPrime_looseBtag_filtered_tagNpv1_400->Fill(*h_npv);
      }
      if(*h_jet1ptEff > 500.){
        hist_ZPrime_looseBtag_filtered_tagNpv1_500->Fill(*h_npv);
      }
      if(*h_jet1ptEff > 600.){
        hist_ZPrime_looseBtag_filtered_tagNpv1_600->Fill(*h_npv);
      }
      if(*h_jet1ptEff > 700.){
        hist_ZPrime_looseBtag_filtered_tagNpv1_700->Fill(*h_npv);
      }
    }

    if((filteredJet2tag_3 &= 2) == 2 && *h_jet2maxSubjBDisc > 0.244){
      hist_ZPrime_looseBtag_filtered_tagJet2pt->Fill(*h_jet2ptEff);
      hist_ZPrime_looseBtag_filtered_tagNpv2->Fill(*h_npv);
      
      if(*h_jet2ptEff > 400.){
        hist_ZPrime_looseBtag_filtered_tagNpv2_400->Fill(*h_npv);
      }
      if(*h_jet2ptEff > 500.){
        hist_ZPrime_looseBtag_filtered_tagNpv2_500->Fill(*h_npv);
      }
      if(*h_jet2ptEff > 600.){
        hist_ZPrime_looseBtag_filtered_tagNpv2_600->Fill(*h_npv);
      }
      if(*h_jet2ptEff > 700.){
        hist_ZPrime_looseBtag_filtered_tagNpv2_700->Fill(*h_npv);
	//jet2pt_tag = jet1ptEff;                                                                                                                                                                     
      }
    }

    /////////////////////////////////
    //// AK8 Pruned Jets
    /////////////////////////////////

    int prunedJet1tag_1 = *h_AK8jet1tagEff;
    int prunedJet1tag_2 = *h_AK8jet1tagEff;
    int prunedJet1tag_3 = *h_AK8jet1tagEff;
    int prunedJet2tag_1 = *h_AK8jet2tagEff;
    int prunedJet2tag_2 = *h_AK8jet2tagEff;
    int prunedJet2tag_3 = *h_AK8jet2tagEff;

    //denominator histograms (pruned mass) -  1 = top-matched, not top-tagged; 4 = top-matched and top-tagged                                                                 

    if((prunedJet1tag_1 &= 1) == 1 || (prunedJet1tag_2 &= 4) == 4){
      hist_ZPrime_looseBtag_pruned_npv1->Fill(*h_npv);
      hist_ZPrime_looseBtag_pruned_jet1pt->Fill(*h_jet1ptEff);
      
      if(*h_jet1ptEff > 400.){
	hist_ZPrime_looseBtag_pruned_npv1_400->Fill(*h_npv);
      }
      if(*h_jet1ptEff > 500.){
	hist_ZPrime_looseBtag_pruned_npv1_500->Fill(*h_npv);
      }
      if(*h_jet1ptEff > 600.){
	hist_ZPrime_looseBtag_pruned_npv1_600->Fill(*h_npv);
      }
      if(*h_jet1ptEff > 700.){
	hist_ZPrime_looseBtag_pruned_npv1_700->Fill(*h_npv);
      }
    }
 
    if((prunedJet2tag_1 &= 1) == 1 || (prunedJet2tag_2 &= 4) == 4){
      hist_ZPrime_looseBtag_pruned_npv2->Fill(*h_npv);
      hist_ZPrime_looseBtag_pruned_jet2pt->Fill(*h_jet2ptEff);
      
      if(*h_jet2ptEff > 400.){
	hist_ZPrime_looseBtag_pruned_npv2_400->Fill(*h_npv);
      }
      if(*h_jet2ptEff > 500.){
	hist_ZPrime_looseBtag_pruned_npv2_500->Fill(*h_npv);
      }
      if(*h_jet2ptEff > 600.){
	hist_ZPrime_looseBtag_pruned_npv2_600->Fill(*h_npv);
      }
      if(*h_jet2ptEff > 700.){
	hist_ZPrime_looseBtag_pruned_npv2_700->Fill(*h_npv);
      }
    }

    //numerator histograms                                                                                                                                                                           
    if((prunedJet1tag_3 &= 4) == 4 && *h_jet1maxSubjBDisc > 0.244){
      hist_ZPrime_looseBtag_pruned_tagJet1pt->Fill(*h_jet1ptEff);
      hist_ZPrime_looseBtag_pruned_tagNpv1->Fill(*h_npv);

      if(*h_jet1ptEff > 400.){
        hist_ZPrime_looseBtag_pruned_tagNpv1_400->Fill(*h_npv);
      }
      if(*h_jet1ptEff > 500.){
        hist_ZPrime_looseBtag_pruned_tagNpv1_500->Fill(*h_npv);
      }
      if(*h_jet1ptEff > 600.){
        hist_ZPrime_looseBtag_pruned_tagNpv1_600->Fill(*h_npv);
      }
      if(*h_jet1ptEff > 700.){
        hist_ZPrime_looseBtag_pruned_tagNpv1_700->Fill(*h_npv);
      }
    }

    if((prunedJet2tag_3 &= 4) == 4 && *h_jet2maxSubjBDisc > 0.244){
      hist_ZPrime_looseBtag_pruned_tagJet2pt->Fill(*h_jet2ptEff);
      hist_ZPrime_looseBtag_pruned_tagNpv2->Fill(*h_npv);
      
      if(*h_jet2ptEff > 400.){
        hist_ZPrime_looseBtag_pruned_tagNpv2_400->Fill(*h_npv);
      }
      if(*h_jet2ptEff > 500.){
        hist_ZPrime_looseBtag_pruned_tagNpv2_500->Fill(*h_npv);
      }
      if(*h_jet2ptEff > 600.){
        hist_ZPrime_looseBtag_pruned_tagNpv2_600->Fill(*h_npv);
      }
      if(*h_jet2ptEff > 700.){
        hist_ZPrime_looseBtag_pruned_tagNpv2_700->Fill(*h_npv);
	//jet2pt_tag = jet1ptEff;                                                                                                                                                                     
      }
    }

    /////////////////////////////////
    //// AK8 Trimmed Jets
    /////////////////////////////////

    int trimmedJet1tag_1 = *h_AK8jet1tagEff;
    int trimmedJet1tag_2 = *h_AK8jet1tagEff;
    int trimmedJet1tag_3 = *h_AK8jet1tagEff;
    int trimmedJet2tag_1 = *h_AK8jet2tagEff;
    int trimmedJet2tag_2 = *h_AK8jet2tagEff;
    int trimmedJet2tag_3 = *h_AK8jet2tagEff;

    //denominator histograms (trimmed mass) -  1 = top-matched, not top-tagged; 8 = top-matched and top-tagged                                                                 

    if((trimmedJet1tag_1 &= 1) == 1 || (trimmedJet1tag_2 &= 8) == 8){
      hist_ZPrime_looseBtag_trimmed_npv1->Fill(*h_npv);
      hist_ZPrime_looseBtag_trimmed_jet1pt->Fill(*h_jet1ptEff);
      
      if(*h_jet1ptEff > 400.){
	hist_ZPrime_looseBtag_trimmed_npv1_400->Fill(*h_npv);
      }
      if(*h_jet1ptEff > 500.){
	hist_ZPrime_looseBtag_trimmed_npv1_500->Fill(*h_npv);
      }
      if(*h_jet1ptEff > 600.){
	hist_ZPrime_looseBtag_trimmed_npv1_600->Fill(*h_npv);
      }
      if(*h_jet1ptEff > 700.){
	hist_ZPrime_looseBtag_trimmed_npv1_700->Fill(*h_npv);
      }
    }
 
    if((trimmedJet2tag_1 &= 1) == 1 || (trimmedJet2tag_2 &= 8) == 8){
      hist_ZPrime_looseBtag_trimmed_npv2->Fill(*h_npv);
      hist_ZPrime_looseBtag_trimmed_jet2pt->Fill(*h_jet2ptEff);
      
      if(*h_jet2ptEff > 400.){
	hist_ZPrime_looseBtag_trimmed_npv2_400->Fill(*h_npv);
      }
      if(*h_jet2ptEff > 500.){
	hist_ZPrime_looseBtag_trimmed_npv2_500->Fill(*h_npv);
      }
      if(*h_jet2ptEff > 600.){
	hist_ZPrime_looseBtag_trimmed_npv2_600->Fill(*h_npv);
      }
      if(*h_jet2ptEff > 700.){
	hist_ZPrime_looseBtag_trimmed_npv2_700->Fill(*h_npv);
      }
    }

    //numerator histograms                                                                                                                                                                           
    if((trimmedJet1tag_3 &= 8) == 8 && *h_jet1maxSubjBDisc > 0.244){
      hist_ZPrime_looseBtag_trimmed_tagJet1pt->Fill(*h_jet1ptEff);
      hist_ZPrime_looseBtag_trimmed_tagNpv1->Fill(*h_npv);

      if(*h_jet1ptEff > 400.){
        hist_ZPrime_looseBtag_trimmed_tagNpv1_400->Fill(*h_npv);
      }
      if(*h_jet1ptEff > 500.){
        hist_ZPrime_looseBtag_trimmed_tagNpv1_500->Fill(*h_npv);
      }
      if(*h_jet1ptEff > 600.){
        hist_ZPrime_looseBtag_trimmed_tagNpv1_600->Fill(*h_npv);
      }
      if(*h_jet1ptEff > 700.){
        hist_ZPrime_looseBtag_trimmed_tagNpv1_700->Fill(*h_npv);
      }
    }

    if((trimmedJet2tag_3 &= 8) == 8 && *h_jet2maxSubjBDisc > 0.244){
      hist_ZPrime_looseBtag_trimmed_tagJet2pt->Fill(*h_jet2ptEff);
      hist_ZPrime_looseBtag_trimmed_tagNpv2->Fill(*h_npv);
      
      if(*h_jet2ptEff > 400.){
        hist_ZPrime_looseBtag_trimmed_tagNpv2_400->Fill(*h_npv);
      }
      if(*h_jet2ptEff > 500.){
        hist_ZPrime_looseBtag_trimmed_tagNpv2_500->Fill(*h_npv);
      }
      if(*h_jet2ptEff > 600.){
        hist_ZPrime_looseBtag_trimmed_tagNpv2_600->Fill(*h_npv);
      }
      if(*h_jet2ptEff > 700.){
        hist_ZPrime_looseBtag_trimmed_tagNpv2_700->Fill(*h_npv);
	//jet2pt_tag = jet1ptEff;                                                                                                                                                                     
      }
    }
  }

  /////////////////////////////////
  //// No Mass Grooming Techniques
  /////////////////////////////////

  //efficiency histograms                                                                                                                                                                            
  hist_ZPrime_looseBtag_jet1pt->Add(hist_ZPrime_looseBtag_jet2pt);                                                                                                                                                                     
  hist_ZPrime_looseBtag_tagJet1pt->Add(hist_ZPrime_looseBtag_tagJet2pt);                                                                                                                                                              
  //hist_ZPrime_looseBtag_tagJet1pt->Divide(hist_ZPrime_looseBtag_jet1pt);                                                                                                                                                             
  hist_ZPrime_looseBtag_topTagEffPt->Divide(hist_ZPrime_looseBtag_tagJet1pt,hist_ZPrime_looseBtag_jet1pt,1,1,"B");                                                                                                                                                                                                                                                                                                                                            
  hist_ZPrime_looseBtag_npv1->Add(hist_ZPrime_looseBtag_npv2);                                                                                                                                                                       
  hist_ZPrime_looseBtag_tagNpv1->Add(hist_ZPrime_looseBtag_tagNpv2);                                                                                                                                                   
  hist_ZPrime_looseBtag_topTagEffNpv->Divide(hist_ZPrime_looseBtag_tagNpv1,hist_ZPrime_looseBtag_npv1,1,1,"B");                                                                                                                                                      
  hist_ZPrime_looseBtag_npv1_400->Add(hist_ZPrime_looseBtag_npv2_400); 
  hist_ZPrime_looseBtag_tagNpv1_400->Add(hist_ZPrime_looseBtag_tagNpv2_400);
  hist_ZPrime_looseBtag_topTagEffNpv_400->Divide(hist_ZPrime_looseBtag_tagNpv1_400,hist_ZPrime_looseBtag_npv1_400,1,1,"B");                                                                                                                                 
  hist_ZPrime_looseBtag_npv1_500->Add(hist_ZPrime_looseBtag_npv2_500);      
  hist_ZPrime_looseBtag_tagNpv1_500->Add(hist_ZPrime_looseBtag_tagNpv2_500);
  hist_ZPrime_looseBtag_topTagEffNpv_500->Divide(hist_ZPrime_looseBtag_tagNpv1_500,hist_ZPrime_looseBtag_npv1_500,1,1,"B");                                                                                                                                 
  hist_ZPrime_looseBtag_npv1_600->Add(hist_ZPrime_looseBtag_npv2_600);      
  hist_ZPrime_looseBtag_tagNpv1_600->Add(hist_ZPrime_looseBtag_tagNpv2_600);
  hist_ZPrime_looseBtag_topTagEffNpv_600->Divide(hist_ZPrime_looseBtag_tagNpv1_600,hist_ZPrime_looseBtag_npv1_600,1,1,"B");                                                                                                                                 
  hist_ZPrime_looseBtag_npv1_700->Add(hist_ZPrime_looseBtag_npv2_700);      
  hist_ZPrime_looseBtag_tagNpv1_700->Add(hist_ZPrime_looseBtag_tagNpv2_700);
  hist_ZPrime_looseBtag_topTagEffNpv_700->Divide(hist_ZPrime_looseBtag_tagNpv1_700,hist_ZPrime_looseBtag_npv1_700,1,1,"B");                                                                                                                                
 
  //fit functions
  TF1 *fit_topTagEffNpv = new TF1("fit_topTagEffNpv","[0]*x + [1]",0.,60.);
  fit_topTagEffNpv->SetParameters(-0.0011,0.388);
  fit_topTagEffNpv->SetParNames("No pt cut: slope","No pt cut: y intercept");
  hist_ZPrime_looseBtag_topTagEffNpv->Fit("fit_topTagEffNpv","N");                             
                                                                                                                        
  TF1 *fit_topTagEffNpv_400 = new TF1("fit_topTagEffNpv_400","[0]*x + [1]",0.,60.);
  fit_topTagEffNpv_400->SetParameters(-0.0015,0.43);
  fit_topTagEffNpv_400->SetParNames("pt > 400: slope","pt > 400: y intercept");    
  hist_ZPrime_looseBtag_topTagEffNpv_400->Fit("fit_topTagEffNpv_400","N");                                                                                                                                                
  TF1 *fit_topTagEffNpv_500 = new TF1("fit_topTagEffNpv_500","[0]*x + [1]",0.,60.);
  fit_topTagEffNpv_500->SetParameters(-0.002,0.445);
  fit_topTagEffNpv_500->SetParNames("pt > 500: slope","pt > 500: y intercept");    
  hist_ZPrime_looseBtag_topTagEffNpv_500->Fit("fit_topTagEffNpv_500","N");                          
                                                                                                                                                                                                 
  TF1 *fit_topTagEffNpv_600 = new TF1("fit_topTagEffNpv_600","[0]*x + [1]",0.,60.);
  fit_topTagEffNpv_600->SetParameters(-0.0025,0.446);
  fit_topTagEffNpv_600->SetParNames("pt > 600: slope","pt > 600: y intercept");    
  hist_ZPrime_looseBtag_topTagEffNpv_600->Fit("fit_topTagEffNpv_600","N");                          

  TF1 *fit_topTagEffNpv_700 = new TF1("fit_topTagEffNpv_700","[0]*x + [1]",0.,60.);
  fit_topTagEffNpv_700->SetParameters(-0.0029,0.438);
  fit_topTagEffNpv_700->SetParNames("pt > 700: slope","pt > 700: y intercept");
  hist_ZPrime_looseBtag_topTagEffNpv_700->Fit("fit_topTagEffNpv_700","N");

  TCanvas* c1 = new TCanvas("canvas1");
  //c1->Draw();
  //c1->Update();
  hist_ZPrime_looseBtag_topTagEffPt->Draw("E");      
  hist_ZPrime_looseBtag_topTagEffPt->SetMaximum(1.1);                                                                                                                                                                   

  //legend                                                                                                                                                                                                 
  TLegend *legend_topTagEffPt = new TLegend(0.75,0.8,0.9,0.9);
  legend_topTagEffPt->AddEntry((TObject*)0 ,"No Grooming Techniques","");
  legend_topTagEffPt->AddEntry((TObject*)0 ,"Loose B-tagging","");
  legend_topTagEffPt->SetFillColor(kWhite);
  legend_topTagEffPt->Draw("Same");
                                                                                                                                           
  TCanvas* c2 = new TCanvas("canvas2");                  
  hist_ZPrime_looseBtag_topTagEffNpv->Draw("E");
  hist_ZPrime_looseBtag_topTagEffNpv->SetMaximum(0.75);
  hist_ZPrime_looseBtag_topTagEffNpv->SetMinimum(0.0); 

  fit_topTagEffNpv->Draw("Same");    
  fit_topTagEffNpv->SetLineColor(1);
  fit_topTagEffNpv->SetLineWidth(2);

  hist_ZPrime_looseBtag_topTagEffNpv_400->Draw("ESAME");                                                                                                                                                       
  hist_ZPrime_looseBtag_topTagEffNpv_400->SetMaximum(0.75);                                                                                                                                                     
  hist_ZPrime_looseBtag_topTagEffNpv_400->SetLineColor(kMagenta+1);                                                                                                                                          
  
  fit_topTagEffNpv_400->Draw("Same");
  fit_topTagEffNpv_400->SetLineColor(kMagenta+1);
  fit_topTagEffNpv_400->SetLineWidth(2);
  
  hist_ZPrime_looseBtag_topTagEffNpv_500->Draw("ESAME");
  hist_ZPrime_looseBtag_topTagEffNpv_500->SetMaximum(0.75);
  hist_ZPrime_looseBtag_topTagEffNpv_500->SetLineColor(kBlue);
  
  fit_topTagEffNpv_500->Draw("Same");
  fit_topTagEffNpv_500->SetLineColor(kBlue);
  fit_topTagEffNpv_500->SetLineWidth(2);
  
  hist_ZPrime_looseBtag_topTagEffNpv_600->Draw("ESAME");                                                                                                                                                        
  hist_ZPrime_looseBtag_topTagEffNpv_600->SetMaximum(0.75);                                                                                                                                                    
  hist_ZPrime_looseBtag_topTagEffNpv_600->SetLineColor(kCyan+1);                                                                                                                                                          
  fit_topTagEffNpv_600->Draw("Same");
  fit_topTagEffNpv_600->SetLineColor(kCyan+1);
  fit_topTagEffNpv_600->SetLineWidth(2);

  hist_ZPrime_looseBtag_topTagEffNpv_700->Draw("ESAME");                                                                                                                                                        
  hist_ZPrime_looseBtag_topTagEffNpv_700->SetMaximum(0.75);                                                                                                                                                     
  hist_ZPrime_looseBtag_topTagEffNpv_700->SetLineColor(kGreen+2);                                                                                                                                                         
  fit_topTagEffNpv_700->Draw("Same");
  fit_topTagEffNpv_700->SetLineColor(kGreen+2);
  fit_topTagEffNpv_700->SetLineWidth(2);

  //legend                                                                                                                                                                                             
  TLegend *legend_topTagEffNpv = new TLegend(0.7,0.7,0.9,0.9);
  legend_topTagEffNpv->AddEntry((TObject*)0 ,"No Grooming Techniques","");
  legend_topTagEffNpv->AddEntry((TObject*)0 ,"Loose B-tagging","");
  legend_topTagEffNpv->AddEntry(hist_ZPrime_looseBtag_topTagEffNpv,"No Pt Cut","LPE");
  legend_topTagEffNpv->AddEntry(hist_ZPrime_looseBtag_topTagEffNpv_400,"Pt > 400 GeV","LPE");
  legend_topTagEffNpv->AddEntry(hist_ZPrime_looseBtag_topTagEffNpv_500,"Pt > 500 GeV","LPE");
  legend_topTagEffNpv->AddEntry(hist_ZPrime_looseBtag_topTagEffNpv_600,"Pt > 600 GeV","LPE");                                                                                                                          
  legend_topTagEffNpv->AddEntry(hist_ZPrime_looseBtag_topTagEffNpv_700,"Pt > 700 GeV","LPE");
  legend_topTagEffNpv->SetFillColor(kWhite); 
  legend_topTagEffNpv->Draw("Same"); 

  c1->SaveAs("topTagEfficiencyPt_ZPrime_13TeV_looseBtag.pdf");
  c2->SaveAs("topTagEfficiencyNpv_ZPrime_13TeV_looseBtag.pdf");

  /////////////////////////////////
  //// AK8 Filtered Jets
  /////////////////////////////////

  //efficiency histograms                                                                                                                                                                            
  hist_ZPrime_looseBtag_filtered_jet1pt->Add(hist_ZPrime_looseBtag_filtered_jet2pt);                                                                                                                                                   
  hist_ZPrime_looseBtag_filtered_tagJet1pt->Add(hist_ZPrime_looseBtag_filtered_tagJet2pt);                                                                                                                                             
  //hist_ZPrime_looseBtag_filtered_tagJet1pt->Divide(hist_ZPrime_looseBtag_filtered_jet1pt);                                                                                                                                           
  hist_ZPrime_looseBtag_filtered_topTagEffPt->Divide(hist_ZPrime_looseBtag_filtered_tagJet1pt,hist_ZPrime_looseBtag_filtered_jet1pt,1,1,"B");                                                                                                                                                                                                                                                                                                              
  hist_ZPrime_looseBtag_filtered_npv1->Add(hist_ZPrime_looseBtag_filtered_npv2);                                                                                                                                                        
  hist_ZPrime_looseBtag_filtered_tagNpv1->Add(hist_ZPrime_looseBtag_filtered_tagNpv2);                                                                                                                                                  
  hist_ZPrime_looseBtag_filtered_topTagEffNpv->Divide(hist_ZPrime_looseBtag_filtered_tagNpv1,hist_ZPrime_looseBtag_filtered_npv1,1,1,"B");                                                                                                                                                      
  hist_ZPrime_looseBtag_filtered_npv1_400->Add(hist_ZPrime_looseBtag_filtered_npv2_400); 
  hist_ZPrime_looseBtag_filtered_tagNpv1_400->Add(hist_ZPrime_looseBtag_filtered_tagNpv2_400);
  hist_ZPrime_looseBtag_filtered_topTagEffNpv_400->Divide(hist_ZPrime_looseBtag_filtered_tagNpv1_400,hist_ZPrime_looseBtag_filtered_npv1_400,1,1,"B");                                                                                                                                 
  hist_ZPrime_looseBtag_filtered_npv1_500->Add(hist_ZPrime_looseBtag_filtered_npv2_500);      
  hist_ZPrime_looseBtag_filtered_tagNpv1_500->Add(hist_ZPrime_looseBtag_filtered_tagNpv2_500);
  hist_ZPrime_looseBtag_filtered_topTagEffNpv_500->Divide(hist_ZPrime_looseBtag_filtered_tagNpv1_500,hist_ZPrime_looseBtag_filtered_npv1_500,1,1,"B");                                                                                                                                 
  hist_ZPrime_looseBtag_filtered_npv1_600->Add(hist_ZPrime_looseBtag_filtered_npv2_600);      
  hist_ZPrime_looseBtag_filtered_tagNpv1_600->Add(hist_ZPrime_looseBtag_filtered_tagNpv2_600);
  hist_ZPrime_looseBtag_filtered_topTagEffNpv_600->Divide(hist_ZPrime_looseBtag_filtered_tagNpv1_600,hist_ZPrime_looseBtag_filtered_npv1_600,1,1,"B");                                                                                                                                 
  hist_ZPrime_looseBtag_filtered_npv1_700->Add(hist_ZPrime_looseBtag_filtered_npv2_700);      
  hist_ZPrime_looseBtag_filtered_tagNpv1_700->Add(hist_ZPrime_looseBtag_filtered_tagNpv2_700);
  hist_ZPrime_looseBtag_filtered_topTagEffNpv_700->Divide(hist_ZPrime_looseBtag_filtered_tagNpv1_700,hist_ZPrime_looseBtag_filtered_npv1_700,1,1,"B");                                                                                                                                
  //fit functions
  TF1 *fit_filtered_topTagEffNpv = new TF1("fit_filtered_topTagEffNpv","[0]*x + [1]",0.,60.);
  fit_filtered_topTagEffNpv->SetParameters(-0.0011,0.388);
  fit_filtered_topTagEffNpv->SetParNames("No pt cut: slope","No pt cut: y intercept");
  hist_ZPrime_looseBtag_filtered_topTagEffNpv->Fit("fit_filtered_topTagEffNpv","N");                             
                                                                                                                        
  TF1 *fit_filtered_topTagEffNpv_400 = new TF1("fit_filtered_topTagEffNpv_400","[0]*x + [1]",0.,60.);
  fit_filtered_topTagEffNpv_400->SetParameters(-0.0015,0.43);
  fit_filtered_topTagEffNpv_400->SetParNames("pt > 400: slope","pt > 400: y intercept");    
  hist_ZPrime_looseBtag_filtered_topTagEffNpv_400->Fit("fit_filtered_topTagEffNpv_400","N");                                                                                                                                                
  TF1 *fit_filtered_topTagEffNpv_500 = new TF1("fit_filtered_topTagEffNpv_500","[0]*x + [1]",0.,60.);
  fit_filtered_topTagEffNpv_500->SetParameters(-0.002,0.445);
  fit_filtered_topTagEffNpv_500->SetParNames("pt > 500: slope","pt > 500: y intercept");    
  hist_ZPrime_looseBtag_filtered_topTagEffNpv_500->Fit("fit_filtered_topTagEffNpv_500","N");                          
                                                                                                                                                                                                 
  TF1 *fit_filtered_topTagEffNpv_600 = new TF1("fit_filtered_topTagEffNpv_600","[0]*x + [1]",0.,60.);
  fit_filtered_topTagEffNpv_600->SetParameters(-0.0025,0.446);
  fit_filtered_topTagEffNpv_600->SetParNames("pt > 600: slope","pt > 600: y intercept");    
  hist_ZPrime_looseBtag_filtered_topTagEffNpv_600->Fit("fit_filtered_topTagEffNpv_600","N");                          

  TF1 *fit_filtered_topTagEffNpv_700 = new TF1("fit_filtered_topTagEffNpv_700","[0]*x + [1]",0.,60.);
  fit_filtered_topTagEffNpv_700->SetParameters(-0.0029,0.438);
  fit_filtered_topTagEffNpv_700->SetParNames("pt > 700: slope","pt > 700: y intercept");
  hist_ZPrime_looseBtag_filtered_topTagEffNpv_700->Fit("fit_filtered_topTagEffNpv_700","N");

  TCanvas* c1_filtered = new TCanvas("canvas1");
  //c1_filtered->Draw();
  //c1_filtered->Update();
  hist_ZPrime_looseBtag_filtered_topTagEffPt->Draw("E");      
  hist_ZPrime_looseBtag_filtered_topTagEffPt->SetMaximum(1.1);                                                                                                                                                                   
  //legend                                                                                                                                                                                                 
  TLegend *legend_filtered_topTagEffPt = new TLegend(0.75,0.8,0.9,0.9);
  legend_filtered_topTagEffPt->AddEntry((TObject*)0 ,"Filtered Mass Jets","");
  legend_filtered_topTagEffPt->AddEntry((TObject*)0 ,"Loose B-tagging","");
  legend_filtered_topTagEffPt->SetFillColor(kWhite);
  legend_filtered_topTagEffPt->Draw("Same");
                                                     
  TCanvas* c2_filtered = new TCanvas("canvas2");
  hist_ZPrime_looseBtag_filtered_topTagEffNpv->Draw("E");
  hist_ZPrime_looseBtag_filtered_topTagEffNpv->SetMaximum(0.75);
  hist_ZPrime_looseBtag_filtered_topTagEffNpv->SetMinimum(0.0); 

  fit_filtered_topTagEffNpv->Draw("Same");    
  fit_filtered_topTagEffNpv->SetLineColor(1);
  fit_filtered_topTagEffNpv->SetLineWidth(2);

  hist_ZPrime_looseBtag_filtered_topTagEffNpv_400->Draw("ESAME");                                                                                                                                                    
  hist_ZPrime_looseBtag_filtered_topTagEffNpv_400->SetMaximum(0.75);                                                                                                                                                  
  hist_ZPrime_looseBtag_filtered_topTagEffNpv_400->SetLineColor(kMagenta+1);                                                                                                                                          
  
  fit_filtered_topTagEffNpv_400->Draw("Same");
  fit_filtered_topTagEffNpv_400->SetLineColor(kMagenta+1);
  fit_filtered_topTagEffNpv_400->SetLineWidth(2);
  
  hist_ZPrime_looseBtag_filtered_topTagEffNpv_500->Draw("ESAME");
  hist_ZPrime_looseBtag_filtered_topTagEffNpv_500->SetMaximum(0.75);
  hist_ZPrime_looseBtag_filtered_topTagEffNpv_500->SetLineColor(kBlue);
  
  fit_filtered_topTagEffNpv_500->Draw("Same");
  fit_filtered_topTagEffNpv_500->SetLineColor(kBlue);
  fit_filtered_topTagEffNpv_500->SetLineWidth(2);
  
  hist_ZPrime_looseBtag_filtered_topTagEffNpv_600->Draw("ESAME");                                                                                                                                                      
  hist_ZPrime_looseBtag_filtered_topTagEffNpv_600->SetMaximum(0.75);                                                                                                                                                  
  hist_ZPrime_looseBtag_filtered_topTagEffNpv_600->SetLineColor(kCyan+1);                                                                                                                                                          
  fit_filtered_topTagEffNpv_600->Draw("Same");
  fit_filtered_topTagEffNpv_600->SetLineColor(kCyan+1);
  fit_filtered_topTagEffNpv_600->SetLineWidth(2);

  hist_ZPrime_looseBtag_filtered_topTagEffNpv_700->Draw("ESAME");                                                                                                                                                     
  hist_ZPrime_looseBtag_filtered_topTagEffNpv_700->SetMaximum(0.75);                                                                                                                                                   
  hist_ZPrime_looseBtag_filtered_topTagEffNpv_700->SetLineColor(kGreen+2);                                                                                                                                                         
  fit_filtered_topTagEffNpv_700->Draw("Same");
  fit_filtered_topTagEffNpv_700->SetLineColor(kGreen+2);
  fit_filtered_topTagEffNpv_700->SetLineWidth(2);

  //legend                                                                                                                                                                                           
  TLegend *legend_filtered_topTagEffNpv = new TLegend(0.7,0.7,0.9,0.9);
  legend_filtered_topTagEffNpv->AddEntry((TObject*)0 ,"Filtered Mass Jets","");
  legend_filtered_topTagEffNpv->AddEntry((TObject*)0 ,"Loose B-tagging","");
  legend_filtered_topTagEffNpv->AddEntry(hist_ZPrime_looseBtag_filtered_topTagEffNpv,"No Pt Cut","LPE");
  legend_filtered_topTagEffNpv->AddEntry(hist_ZPrime_looseBtag_filtered_topTagEffNpv_400,"Pt > 400 GeV","LPE");
  legend_filtered_topTagEffNpv->AddEntry(hist_ZPrime_looseBtag_filtered_topTagEffNpv_500,"Pt > 500 GeV","LPE");
  legend_filtered_topTagEffNpv->AddEntry(hist_ZPrime_looseBtag_filtered_topTagEffNpv_600,"Pt > 600 GeV","LPE");                         
  legend_filtered_topTagEffNpv->AddEntry(hist_ZPrime_looseBtag_filtered_topTagEffNpv_700,"Pt > 700 GeV","LPE");
  legend_filtered_topTagEffNpv->SetFillColor(kWhite); 
  legend_filtered_topTagEffNpv->Draw("Same"); 

  c1_filtered->SaveAs("topTagEfficiencyPt_filtered_ZPrime_13TeV_looseBtag.pdf");
  c2_filtered->SaveAs("topTagEfficiencyNpv_filtered_ZPrime_13TeV_looseBtag.pdf");

  /////////////////////////////////
  //// AK8 Pruned Jets
  /////////////////////////////////

  //efficiency histograms                                                                                                                                                                            
  hist_ZPrime_looseBtag_pruned_jet1pt->Add(hist_ZPrime_looseBtag_pruned_jet2pt);                                                                                                                                                   
  hist_ZPrime_looseBtag_pruned_tagJet1pt->Add(hist_ZPrime_looseBtag_pruned_tagJet2pt);                                                                                                                                             
  //hist_ZPrime_looseBtag_pruned_tagJet1pt->Divide(hist_ZPrime_looseBtag_pruned_jet1pt);                                                                                                                                           
  hist_ZPrime_looseBtag_pruned_topTagEffPt->Divide(hist_ZPrime_looseBtag_pruned_tagJet1pt,hist_ZPrime_looseBtag_pruned_jet1pt,1,1,"B");                                                                                                                                                                                                                                                                                                              
  hist_ZPrime_looseBtag_pruned_npv1->Add(hist_ZPrime_looseBtag_pruned_npv2);                                                                                                                                                        
  hist_ZPrime_looseBtag_pruned_tagNpv1->Add(hist_ZPrime_looseBtag_pruned_tagNpv2);                                                                                                                                                  
  hist_ZPrime_looseBtag_pruned_topTagEffNpv->Divide(hist_ZPrime_looseBtag_pruned_tagNpv1,hist_ZPrime_looseBtag_pruned_npv1,1,1,"B");                                                                                                                                                      
  hist_ZPrime_looseBtag_pruned_npv1_400->Add(hist_ZPrime_looseBtag_pruned_npv2_400); 
  hist_ZPrime_looseBtag_pruned_tagNpv1_400->Add(hist_ZPrime_looseBtag_pruned_tagNpv2_400);
  hist_ZPrime_looseBtag_pruned_topTagEffNpv_400->Divide(hist_ZPrime_looseBtag_pruned_tagNpv1_400,hist_ZPrime_looseBtag_pruned_npv1_400,1,1,"B");                                                                                                                                 
  hist_ZPrime_looseBtag_pruned_npv1_500->Add(hist_ZPrime_looseBtag_pruned_npv2_500);      
  hist_ZPrime_looseBtag_pruned_tagNpv1_500->Add(hist_ZPrime_looseBtag_pruned_tagNpv2_500);
  hist_ZPrime_looseBtag_pruned_topTagEffNpv_500->Divide(hist_ZPrime_looseBtag_pruned_tagNpv1_500,hist_ZPrime_looseBtag_pruned_npv1_500,1,1,"B");                                                                                                                                 
  hist_ZPrime_looseBtag_pruned_npv1_600->Add(hist_ZPrime_looseBtag_pruned_npv2_600);      
  hist_ZPrime_looseBtag_pruned_tagNpv1_600->Add(hist_ZPrime_looseBtag_pruned_tagNpv2_600);
  hist_ZPrime_looseBtag_pruned_topTagEffNpv_600->Divide(hist_ZPrime_looseBtag_pruned_tagNpv1_600,hist_ZPrime_looseBtag_pruned_npv1_600,1,1,"B");                                                                                                                                 
  hist_ZPrime_looseBtag_pruned_npv1_700->Add(hist_ZPrime_looseBtag_pruned_npv2_700);      
  hist_ZPrime_looseBtag_pruned_tagNpv1_700->Add(hist_ZPrime_looseBtag_pruned_tagNpv2_700);
  hist_ZPrime_looseBtag_pruned_topTagEffNpv_700->Divide(hist_ZPrime_looseBtag_pruned_tagNpv1_700,hist_ZPrime_looseBtag_pruned_npv1_700,1,1,"B");                                                                                                                                
  //fit functions
  TF1 *fit_pruned_topTagEffNpv = new TF1("fit_pruned_topTagEffNpv","[0]*x + [1]",0.,60.);
  fit_pruned_topTagEffNpv->SetParameters(-0.0011,0.388);
  fit_pruned_topTagEffNpv->SetParNames("No pt cut: slope","No pt cut: y intercept");
  hist_ZPrime_looseBtag_pruned_topTagEffNpv->Fit("fit_pruned_topTagEffNpv","N");                             
                                                                                                                        
  TF1 *fit_pruned_topTagEffNpv_400 = new TF1("fit_pruned_topTagEffNpv_400","[0]*x + [1]",0.,60.);
  fit_pruned_topTagEffNpv_400->SetParameters(-0.0015,0.43);
  fit_pruned_topTagEffNpv_400->SetParNames("pt > 400: slope","pt > 400: y intercept");    
  hist_ZPrime_looseBtag_pruned_topTagEffNpv_400->Fit("fit_pruned_topTagEffNpv_400","N");                                                                                                                                                
  TF1 *fit_pruned_topTagEffNpv_500 = new TF1("fit_pruned_topTagEffNpv_500","[0]*x + [1]",0.,60.);
  fit_pruned_topTagEffNpv_500->SetParameters(-0.002,0.445);
  fit_pruned_topTagEffNpv_500->SetParNames("pt > 500: slope","pt > 500: y intercept");    
  hist_ZPrime_looseBtag_pruned_topTagEffNpv_500->Fit("fit_pruned_topTagEffNpv_500","N");                          
                                                                                                                                                                                                 
  TF1 *fit_pruned_topTagEffNpv_600 = new TF1("fit_pruned_topTagEffNpv_600","[0]*x + [1]",0.,60.);
  fit_pruned_topTagEffNpv_600->SetParameters(-0.0025,0.446);
  fit_pruned_topTagEffNpv_600->SetParNames("pt > 600: slope","pt > 600: y intercept");    
  hist_ZPrime_looseBtag_pruned_topTagEffNpv_600->Fit("fit_pruned_topTagEffNpv_600","N");                          

  TF1 *fit_pruned_topTagEffNpv_700 = new TF1("fit_pruned_topTagEffNpv_700","[0]*x + [1]",0.,60.);
  fit_pruned_topTagEffNpv_700->SetParameters(-0.0029,0.438);
  fit_pruned_topTagEffNpv_700->SetParNames("pt > 700: slope","pt > 700: y intercept");
  hist_ZPrime_looseBtag_pruned_topTagEffNpv_700->Fit("fit_pruned_topTagEffNpv_700","N");

  TCanvas* c1_pruned = new TCanvas("canvas1");
  //c1_pruned->Draw();
  //c1_pruned->Update();
  hist_ZPrime_looseBtag_pruned_topTagEffPt->Draw("E");      
  hist_ZPrime_looseBtag_pruned_topTagEffPt->SetMaximum(1.1);                                                                                                                                                                   
  //legend                                                                                                                                                 
  TLegend *legend_pruned_topTagEffPt = new TLegend(0.75,0.8,0.9,0.9);
  legend_pruned_topTagEffPt->AddEntry((TObject*)0 ,"Pruned Mass Jets","");
  legend_pruned_topTagEffPt->AddEntry((TObject*)0 ,"Loose B-tagging","");
  legend_pruned_topTagEffPt->SetFillColor(kWhite);
  legend_pruned_topTagEffPt->Draw("Same");
                                                                                                                                                                                         
  TCanvas* c2_pruned = new TCanvas("canvas2");
  hist_ZPrime_looseBtag_pruned_topTagEffNpv->Draw("E");
  hist_ZPrime_looseBtag_pruned_topTagEffNpv->SetMaximum(0.75);
  hist_ZPrime_looseBtag_pruned_topTagEffNpv->SetMinimum(0.0); 

  fit_pruned_topTagEffNpv->Draw("Same");    
  fit_pruned_topTagEffNpv->SetLineColor(1);
  fit_pruned_topTagEffNpv->SetLineWidth(2);

  hist_ZPrime_looseBtag_pruned_topTagEffNpv_400->Draw("ESAME");                                                                                                                                                    
  hist_ZPrime_looseBtag_pruned_topTagEffNpv_400->SetMaximum(0.75);                                                                                                                                                  
  hist_ZPrime_looseBtag_pruned_topTagEffNpv_400->SetLineColor(kMagenta+1);                                                                                                                                          
  
  fit_pruned_topTagEffNpv_400->Draw("Same");
  fit_pruned_topTagEffNpv_400->SetLineColor(kMagenta+1);
  fit_pruned_topTagEffNpv_400->SetLineWidth(2);
  
  hist_ZPrime_looseBtag_pruned_topTagEffNpv_500->Draw("ESAME");
  hist_ZPrime_looseBtag_pruned_topTagEffNpv_500->SetMaximum(0.75);
  hist_ZPrime_looseBtag_pruned_topTagEffNpv_500->SetLineColor(kBlue);
  
  fit_pruned_topTagEffNpv_500->Draw("Same");
  fit_pruned_topTagEffNpv_500->SetLineColor(kBlue);
  fit_pruned_topTagEffNpv_500->SetLineWidth(2);
  
  hist_ZPrime_looseBtag_pruned_topTagEffNpv_600->Draw("ESAME");                                                                                                                                                      
  hist_ZPrime_looseBtag_pruned_topTagEffNpv_600->SetMaximum(0.75);                                                                                                                                                  
  hist_ZPrime_looseBtag_pruned_topTagEffNpv_600->SetLineColor(kCyan+1);                                                                                                                                                          
  fit_pruned_topTagEffNpv_600->Draw("Same");
  fit_pruned_topTagEffNpv_600->SetLineColor(kCyan+1);
  fit_pruned_topTagEffNpv_600->SetLineWidth(2);

  hist_ZPrime_looseBtag_pruned_topTagEffNpv_700->Draw("ESAME");                                                                                                                                                     
  hist_ZPrime_looseBtag_pruned_topTagEffNpv_700->SetMaximum(0.75);                                                                                                                                                   
  hist_ZPrime_looseBtag_pruned_topTagEffNpv_700->SetLineColor(kGreen+2);                                                                                                                                                         
  fit_pruned_topTagEffNpv_700->Draw("Same");
  fit_pruned_topTagEffNpv_700->SetLineColor(kGreen+2);
  fit_pruned_topTagEffNpv_700->SetLineWidth(2);

  //legend                                                                                                                                                                                           
  TLegend *legend_pruned_topTagEffNpv = new TLegend(0.7,0.7,0.9,0.9);
  legend_pruned_topTagEffNpv->AddEntry((TObject*)0 ,"Pruned Mass Jets","");
  legend_pruned_topTagEffNpv->AddEntry((TObject*)0 ,"Loose B-tagging","");
  legend_pruned_topTagEffNpv->AddEntry(hist_ZPrime_looseBtag_pruned_topTagEffNpv,"No Pt Cut","LPE");
  legend_pruned_topTagEffNpv->AddEntry(hist_ZPrime_looseBtag_pruned_topTagEffNpv_400,"Pt > 400 GeV","LPE");
  legend_pruned_topTagEffNpv->AddEntry(hist_ZPrime_looseBtag_pruned_topTagEffNpv_500,"Pt > 500 GeV","LPE");
  legend_pruned_topTagEffNpv->AddEntry(hist_ZPrime_looseBtag_pruned_topTagEffNpv_600,"Pt > 600 GeV","LPE");                                                                    
  legend_pruned_topTagEffNpv->AddEntry(hist_ZPrime_looseBtag_pruned_topTagEffNpv_700,"Pt > 700 GeV","LPE");
  legend_pruned_topTagEffNpv->SetFillColor(kWhite); 
  legend_pruned_topTagEffNpv->Draw("Same"); 

  c1_pruned->SaveAs("topTagEfficiencyPt_pruned_ZPrime_13TeV_looseBtag.pdf");
  c2_pruned->SaveAs("topTagEfficiencyNpv_pruned_ZPrime_13TeV_looseBtag.pdf");

  /////////////////////////////////
  //// AK8 Trimmed Jets
  /////////////////////////////////

  //efficiency histograms                                                                                                                                                                            
  hist_ZPrime_looseBtag_trimmed_jet1pt->Add(hist_ZPrime_looseBtag_trimmed_jet2pt);                                                                                                                                                   
  hist_ZPrime_looseBtag_trimmed_tagJet1pt->Add(hist_ZPrime_looseBtag_trimmed_tagJet2pt);                                                                                                                                             
  //hist_ZPrime_looseBtag_trimmed_tagJet1pt->Divide(hist_ZPrime_looseBtag_trimmed_jet1pt);                                                                                                                                           
  hist_ZPrime_looseBtag_trimmed_topTagEffPt->Divide(hist_ZPrime_looseBtag_trimmed_tagJet1pt,hist_ZPrime_looseBtag_trimmed_jet1pt,1,1,"B");                                                                                                                                                                                                                                                                                                              
  hist_ZPrime_looseBtag_trimmed_npv1->Add(hist_ZPrime_looseBtag_trimmed_npv2);                                                                                                                                                        
  hist_ZPrime_looseBtag_trimmed_tagNpv1->Add(hist_ZPrime_looseBtag_trimmed_tagNpv2);                                                                                                                                                  
  hist_ZPrime_looseBtag_trimmed_topTagEffNpv->Divide(hist_ZPrime_looseBtag_trimmed_tagNpv1,hist_ZPrime_looseBtag_trimmed_npv1,1,1,"B");                                                                                                                                                      
  hist_ZPrime_looseBtag_trimmed_npv1_400->Add(hist_ZPrime_looseBtag_trimmed_npv2_400); 
  hist_ZPrime_looseBtag_trimmed_tagNpv1_400->Add(hist_ZPrime_looseBtag_trimmed_tagNpv2_400);
  hist_ZPrime_looseBtag_trimmed_topTagEffNpv_400->Divide(hist_ZPrime_looseBtag_trimmed_tagNpv1_400,hist_ZPrime_looseBtag_trimmed_npv1_400,1,1,"B");                                                                                                                                 
  hist_ZPrime_looseBtag_trimmed_npv1_500->Add(hist_ZPrime_looseBtag_trimmed_npv2_500);      
  hist_ZPrime_looseBtag_trimmed_tagNpv1_500->Add(hist_ZPrime_looseBtag_trimmed_tagNpv2_500);
  hist_ZPrime_looseBtag_trimmed_topTagEffNpv_500->Divide(hist_ZPrime_looseBtag_trimmed_tagNpv1_500,hist_ZPrime_looseBtag_trimmed_npv1_500,1,1,"B");                                                                                                                                 
  hist_ZPrime_looseBtag_trimmed_npv1_600->Add(hist_ZPrime_looseBtag_trimmed_npv2_600);      
  hist_ZPrime_looseBtag_trimmed_tagNpv1_600->Add(hist_ZPrime_looseBtag_trimmed_tagNpv2_600);
  hist_ZPrime_looseBtag_trimmed_topTagEffNpv_600->Divide(hist_ZPrime_looseBtag_trimmed_tagNpv1_600,hist_ZPrime_looseBtag_trimmed_npv1_600,1,1,"B");                                                                                                                                 
  hist_ZPrime_looseBtag_trimmed_npv1_700->Add(hist_ZPrime_looseBtag_trimmed_npv2_700);      
  hist_ZPrime_looseBtag_trimmed_tagNpv1_700->Add(hist_ZPrime_looseBtag_trimmed_tagNpv2_700);
  hist_ZPrime_looseBtag_trimmed_topTagEffNpv_700->Divide(hist_ZPrime_looseBtag_trimmed_tagNpv1_700,hist_ZPrime_looseBtag_trimmed_npv1_700,1,1,"B");                                                                                                                                
  //fit functions
  TF1 *fit_trimmed_topTagEffNpv = new TF1("fit_trimmed_topTagEffNpv","[0]*x + [1]",0.,60.);
  fit_trimmed_topTagEffNpv->SetParameters(-0.0011,0.388);
  fit_trimmed_topTagEffNpv->SetParNames("No pt cut: slope","No pt cut: y intercept");
  hist_ZPrime_looseBtag_trimmed_topTagEffNpv->Fit("fit_trimmed_topTagEffNpv","N");                             
                                                                                                                        
  TF1 *fit_trimmed_topTagEffNpv_400 = new TF1("fit_trimmed_topTagEffNpv_400","[0]*x + [1]",0.,60.);
  fit_trimmed_topTagEffNpv_400->SetParameters(-0.0015,0.43);
  fit_trimmed_topTagEffNpv_400->SetParNames("pt > 400: slope","pt > 400: y intercept");    
  hist_ZPrime_looseBtag_trimmed_topTagEffNpv_400->Fit("fit_trimmed_topTagEffNpv_400","N");                                                                                                                                                
  TF1 *fit_trimmed_topTagEffNpv_500 = new TF1("fit_trimmed_topTagEffNpv_500","[0]*x + [1]",0.,60.);
  fit_trimmed_topTagEffNpv_500->SetParameters(-0.002,0.445);
  fit_trimmed_topTagEffNpv_500->SetParNames("pt > 500: slope","pt > 500: y intercept");    
  hist_ZPrime_looseBtag_trimmed_topTagEffNpv_500->Fit("fit_trimmed_topTagEffNpv_500","N");                          
                                                                                                                                                       
  TF1 *fit_trimmed_topTagEffNpv_600 = new TF1("fit_trimmed_topTagEffNpv_600","[0]*x + [1]",0.,60.);
  fit_trimmed_topTagEffNpv_600->SetParameters(-0.0025,0.446);
  fit_trimmed_topTagEffNpv_600->SetParNames("pt > 600: slope","pt > 600: y intercept");    
  hist_ZPrime_looseBtag_trimmed_topTagEffNpv_600->Fit("fit_trimmed_topTagEffNpv_600","N");                          

  TF1 *fit_trimmed_topTagEffNpv_700 = new TF1("fit_trimmed_topTagEffNpv_700","[0]*x + [1]",0.,60.);
  fit_trimmed_topTagEffNpv_700->SetParameters(-0.0029,0.438);
  fit_trimmed_topTagEffNpv_700->SetParNames("pt > 700: slope","pt > 700: y intercept");
  hist_ZPrime_looseBtag_trimmed_topTagEffNpv_700->Fit("fit_trimmed_topTagEffNpv_700","N");

  TCanvas* c1_trimmed = new TCanvas("canvas1");
  //c1_trimmed->Draw();
  //c1_trimmed->Update();
  hist_ZPrime_looseBtag_trimmed_topTagEffPt->Draw("E");      
  hist_ZPrime_looseBtag_trimmed_topTagEffPt->SetMaximum(1.1);                                                                                                                                                                   
  //legend                                                                                                                                               
  TLegend *legend_trimmed_topTagEffPt = new TLegend(0.75,0.8,0.9,0.9);
  legend_trimmed_topTagEffPt->AddEntry((TObject*)0 ,"Trimmed Mass Jets","");
  legend_trimmed_topTagEffPt->AddEntry((TObject*)0 ,"Loose B-tagging","");
  legend_trimmed_topTagEffPt->SetFillColor(kWhite);
  legend_trimmed_topTagEffPt->Draw("Same");
                                                                                                                                                                                         
  TCanvas* c2_trimmed = new TCanvas("canvas2");
  hist_ZPrime_looseBtag_trimmed_topTagEffNpv->Draw("E");
  hist_ZPrime_looseBtag_trimmed_topTagEffNpv->SetMaximum(0.75);
  hist_ZPrime_looseBtag_trimmed_topTagEffNpv->SetMinimum(0.0); 

  fit_trimmed_topTagEffNpv->Draw("Same");    
  fit_trimmed_topTagEffNpv->SetLineColor(1);
  fit_trimmed_topTagEffNpv->SetLineWidth(2);

  hist_ZPrime_looseBtag_trimmed_topTagEffNpv_400->Draw("ESAME");                                                                                                                                                    
  hist_ZPrime_looseBtag_trimmed_topTagEffNpv_400->SetMaximum(0.75);                                                                                                                                                  
  hist_ZPrime_looseBtag_trimmed_topTagEffNpv_400->SetLineColor(kMagenta+1);                                                                                                                                          
  
  fit_trimmed_topTagEffNpv_400->Draw("Same");
  fit_trimmed_topTagEffNpv_400->SetLineColor(kMagenta+1);
  fit_trimmed_topTagEffNpv_400->SetLineWidth(2);
  
  hist_ZPrime_looseBtag_trimmed_topTagEffNpv_500->Draw("ESAME");
  hist_ZPrime_looseBtag_trimmed_topTagEffNpv_500->SetMaximum(0.75);
  hist_ZPrime_looseBtag_trimmed_topTagEffNpv_500->SetLineColor(kBlue);
  
  fit_trimmed_topTagEffNpv_500->Draw("Same");
  fit_trimmed_topTagEffNpv_500->SetLineColor(kBlue);
  fit_trimmed_topTagEffNpv_500->SetLineWidth(2);
  
  hist_ZPrime_looseBtag_trimmed_topTagEffNpv_600->Draw("ESAME");                                                                                                                                                      
  hist_ZPrime_looseBtag_trimmed_topTagEffNpv_600->SetMaximum(0.75);                                                                                                                                                  
  hist_ZPrime_looseBtag_trimmed_topTagEffNpv_600->SetLineColor(kCyan+1);                                                                                                                                                          
  fit_trimmed_topTagEffNpv_600->Draw("Same");
  fit_trimmed_topTagEffNpv_600->SetLineColor(kCyan+1);
  fit_trimmed_topTagEffNpv_600->SetLineWidth(2);

  hist_ZPrime_looseBtag_trimmed_topTagEffNpv_700->Draw("ESAME");                                                                                                                                                     
  hist_ZPrime_looseBtag_trimmed_topTagEffNpv_700->SetMaximum(0.75);                                                                                                                                                   
  hist_ZPrime_looseBtag_trimmed_topTagEffNpv_700->SetLineColor(kGreen+2);                                                                                                                                                         
  fit_trimmed_topTagEffNpv_700->Draw("Same");
  fit_trimmed_topTagEffNpv_700->SetLineColor(kGreen+2);
  fit_trimmed_topTagEffNpv_700->SetLineWidth(2);

  //legend                                                                                                                                                                                           
  TLegend *legend_trimmed_topTagEffNpv = new TLegend(0.7,0.7,0.9,0.9);
  legend_trimmed_topTagEffNpv->AddEntry((TObject*)0 ,"Trimmed Mass Jets","");
  legend_trimmed_topTagEffNpv->AddEntry((TObject*)0 ,"Loose B-tagging","");
  legend_trimmed_topTagEffNpv->AddEntry(hist_ZPrime_looseBtag_trimmed_topTagEffNpv,"No Pt Cut","LPE");
  legend_trimmed_topTagEffNpv->AddEntry(hist_ZPrime_looseBtag_trimmed_topTagEffNpv_400,"Pt > 400 GeV","LPE");
  legend_trimmed_topTagEffNpv->AddEntry(hist_ZPrime_looseBtag_trimmed_topTagEffNpv_500,"Pt > 500 GeV","LPE");
  legend_trimmed_topTagEffNpv->AddEntry(hist_ZPrime_looseBtag_trimmed_topTagEffNpv_600,"Pt > 600 GeV","LPE");                                                                 
  legend_trimmed_topTagEffNpv->AddEntry(hist_ZPrime_looseBtag_trimmed_topTagEffNpv_700,"Pt > 700 GeV","LPE");
  legend_trimmed_topTagEffNpv->SetFillColor(kWhite); 
  legend_trimmed_topTagEffNpv->Draw("Same"); 

  c1_trimmed->SaveAs("topTagEfficiencyPt_trimmed_ZPrime_13TeV_looseBtag.pdf");
  c2_trimmed->SaveAs("topTagEfficiencyNpv_trimmed_ZPrime_13TeV_looseBtag.pdf");

  TFile f("topTagEfficiency_ZPrime_13TeV_looseBtag.root","recreate");
  hist_ZPrime_looseBtag_topTagEffPt->Write();
  hist_ZPrime_looseBtag_topTagEffNpv->Write();
  hist_ZPrime_looseBtag_topTagEffNpv_400->Write();
  hist_ZPrime_looseBtag_topTagEffNpv_500->Write();
  hist_ZPrime_looseBtag_topTagEffNpv_600->Write();
  hist_ZPrime_looseBtag_topTagEffNpv_700->Write();

  hist_ZPrime_looseBtag_filtered_topTagEffPt->Write();
  hist_ZPrime_looseBtag_filtered_topTagEffNpv->Write();
  hist_ZPrime_looseBtag_filtered_topTagEffNpv_400->Write();
  hist_ZPrime_looseBtag_filtered_topTagEffNpv_500->Write();
  hist_ZPrime_looseBtag_filtered_topTagEffNpv_600->Write();
  hist_ZPrime_looseBtag_filtered_topTagEffNpv_700->Write();

  hist_ZPrime_looseBtag_pruned_topTagEffPt->Write();
  hist_ZPrime_looseBtag_pruned_topTagEffNpv->Write();
  hist_ZPrime_looseBtag_pruned_topTagEffNpv_400->Write();
  hist_ZPrime_looseBtag_pruned_topTagEffNpv_500->Write();
  hist_ZPrime_looseBtag_pruned_topTagEffNpv_600->Write();
  hist_ZPrime_looseBtag_pruned_topTagEffNpv_700->Write();

  hist_ZPrime_looseBtag_trimmed_topTagEffPt->Write();
  hist_ZPrime_looseBtag_trimmed_topTagEffNpv->Write();
  hist_ZPrime_looseBtag_trimmed_topTagEffNpv_400->Write();
  hist_ZPrime_looseBtag_trimmed_topTagEffNpv_500->Write();
  hist_ZPrime_looseBtag_trimmed_topTagEffNpv_600->Write();
  hist_ZPrime_looseBtag_trimmed_topTagEffNpv_700->Write();

  hist_ZPrime_looseBtag_jet1pt->Write();
  hist_ZPrime_looseBtag_npv1->Write();
  hist_ZPrime_looseBtag_npv1_400->Write();
  hist_ZPrime_looseBtag_npv1_500->Write();
  hist_ZPrime_looseBtag_npv1_600->Write();
  hist_ZPrime_looseBtag_npv1_700->Write();

  hist_ZPrime_looseBtag_filtered_jet1pt->Write();
  hist_ZPrime_looseBtag_filtered_npv1->Write();
  hist_ZPrime_looseBtag_filtered_npv1_400->Write();
  hist_ZPrime_looseBtag_filtered_npv1_500->Write();
  hist_ZPrime_looseBtag_filtered_npv1_600->Write();
  hist_ZPrime_looseBtag_filtered_npv1_700->Write();

  hist_ZPrime_looseBtag_pruned_jet1pt->Write();
  hist_ZPrime_looseBtag_pruned_npv1->Write();
  hist_ZPrime_looseBtag_pruned_npv1_400->Write();
  hist_ZPrime_looseBtag_pruned_npv1_500->Write();
  hist_ZPrime_looseBtag_pruned_npv1_600->Write();
  hist_ZPrime_looseBtag_pruned_npv1_700->Write();

  hist_ZPrime_looseBtag_trimmed_jet1pt->Write();
  hist_ZPrime_looseBtag_trimmed_npv1->Write();
  hist_ZPrime_looseBtag_trimmed_npv1_400->Write();
  hist_ZPrime_looseBtag_trimmed_npv1_500->Write();
  hist_ZPrime_looseBtag_trimmed_npv1_600->Write();
  hist_ZPrime_looseBtag_trimmed_npv1_700->Write();

  hist_ZPrime_looseBtag_tagJet1pt->Write();
  hist_ZPrime_looseBtag_tagNpv1->Write();
  hist_ZPrime_looseBtag_tagNpv1_400->Write();
  hist_ZPrime_looseBtag_tagNpv1_500->Write();
  hist_ZPrime_looseBtag_tagNpv1_600->Write();
  hist_ZPrime_looseBtag_tagNpv1_700->Write();

  hist_ZPrime_looseBtag_filtered_tagJet1pt->Write();
  hist_ZPrime_looseBtag_filtered_tagNpv1->Write();
  hist_ZPrime_looseBtag_filtered_tagNpv1_400->Write();
  hist_ZPrime_looseBtag_filtered_tagNpv1_500->Write();
  hist_ZPrime_looseBtag_filtered_tagNpv1_600->Write();
  hist_ZPrime_looseBtag_filtered_tagNpv1_700->Write();

  hist_ZPrime_looseBtag_pruned_tagJet1pt->Write();
  hist_ZPrime_looseBtag_pruned_tagNpv1->Write();
  hist_ZPrime_looseBtag_pruned_tagNpv1_400->Write();
  hist_ZPrime_looseBtag_pruned_tagNpv1_500->Write();
  hist_ZPrime_looseBtag_pruned_tagNpv1_600->Write();
  hist_ZPrime_looseBtag_pruned_tagNpv1_700->Write();

  hist_ZPrime_looseBtag_trimmed_tagJet1pt->Write();
  hist_ZPrime_looseBtag_trimmed_tagNpv1->Write();
  hist_ZPrime_looseBtag_trimmed_tagNpv1_400->Write();
  hist_ZPrime_looseBtag_trimmed_tagNpv1_500->Write();
  hist_ZPrime_looseBtag_trimmed_tagNpv1_600->Write();
  hist_ZPrime_looseBtag_trimmed_tagNpv1_700->Write();

  hist_ZPrime_looseBtag_jet1pt->Write();
  hist_ZPrime_looseBtag_npv1->Write();
  f.Close();

  return 0;
}
