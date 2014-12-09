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
#include<TDirectoryFile.h>

void topTagEfficiency_compare_Sept25(){
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(0000000000);
  gStyle->SetTitleBorderSize(0);
  /*
  TFile *f13 = new TFile("RSGttbar_topTagEff_13TeV.root");
  f13->ls();
  
  TFile *f8 = new TFile("SMttbar_topTagEff_8TeV.root");
  f8->ls();
  */
  TFile *f_ZPrime_13TeV_noBtag = new TFile("topTagEfficiency_ZPrime_13TeV_noBtag.root");
  f_ZPrime_13TeV_noBtag->ls();
  TFile *f_ZPrime_13TeV_looseBtag = new TFile("topTagEfficiency_ZPrime_13TeV_looseBtag.root");
  f_ZPrime_13TeV_looseBtag->ls();
  TFile *f_ZPrime_13TeV_mediumBtag = new TFile("topTagEfficiency_ZPrime_13TeV_mediumBtag.root");
  f_ZPrime_13TeV_mediumBtag->ls();

  TFile *f_QCD_13TeV_noBtag = new TFile("topTagEfficiency_QCD_13TeV_noBtag.root");
  f_QCD_13TeV_noBtag->ls();
  TFile *f_QCD_13TeV_looseBtag = new TFile("topTagEfficiency_QCD_13TeV_looseBtag.root");
  f_QCD_13TeV_looseBtag->ls();
  TFile *f_QCD_13TeV_mediumBtag = new TFile("topTagEfficiency_QCD_13TeV_mediumBtag.root");
  f_QCD_13TeV_mediumBtag->ls();
  /*
  TFile *f_QCD_FLAT_weighted_13TeV_noBtag = new TFile("topTagEfficiency_QCD_FLAT_weighted_13TeV_noBtag.root");
  f_QCD_FLAT_weighted_13TeV_noBtag->ls();
  TFile *f_QCD_FLAT_weighted_13TeV_looseBtag = new TFile("topTagEfficiency_QCD_FLAT_weighted_13TeV_looseBtag.root");
  f_QCD_FLAT_weighted_13TeV_looseBtag->ls();
  TFile *f_QCD_FLAT_weighted_13TeV_mediumBtag = new TFile("topTagEfficiency_QCD_FLAT_weighted_13TeV_mediumBtag.root");
  f_QCD_FLAT_weighted_13TeV_mediumBtag->ls();

  TFile *f_QCD_FLAT_13TeV_noBtag = new TFile("topTagEfficiency_QCD_FLAT_13TeV_noBtag.root");
  f_QCD_FLAT_13TeV_noBtag->ls();
  TFile *f_QCD_FLAT_13TeV_looseBtag = new TFile("topTagEfficiency_QCD_FLAT_13TeV_looseBtag.root");
  f_QCD_FLAT_13TeV_looseBtag->ls();
  TFile *f_QCD_FLAT_13TeV_mediumBtag = new TFile("topTagEfficiency_QCD_FLAT_13TeV_mediumBtag.root");
  f_QCD_FLAT_13TeV_mediumBtag->ls();
  
  TFile *f_SMttbar_13TeV_noBtag = new TFile("topTagEfficiency_SMttbar_13TeV_noBtag.root");
  f_SMttbar_13TeV_noBtag->ls();
  TFile *f_SMttbar_13TeV_looseBtag = new TFile("topTagEfficiency_SMttbar_13TeV_looseBtag.root");
  f_SMttbar_13TeV_looseBtag->ls();
  TFile *f_SMttbar_13TeV_mediumBtag = new TFile("topTagEfficiency_SMttbar_13TeV_mediumBtag.root");
  f_SMttbar_13TeV_mediumBtag->ls();
  
  //ttbar comparison histograms
  TH1F * hist_SMttbar_noBtag_topTagEffPt = (TH1F*)f_SMttbar_13TeV_noBtag->Get("hist_SMttbar_noBtag_topTagEffPt");
  TH1F * hist_SMttbar_noBtag_topTagEffNpv = (TH1F*)f_SMttbar_13TeV_noBtag->Get("hist_SMttbar_noBtag_topTagEffNpv");
  TH1F * hist_SMttbar_noBtag_topTagEffNpv_400 = (TH1F*)f_SMttbar_13TeV_noBtag->Get("hist_SMttbar_noBtag_topTagEffNpv_400");
  TH1F * hist_SMttbar_noBtag_jet1pt = (TH1F*)f_SMttbar_13TeV_noBtag->Get("hist_SMttbar_noBtag_jet1pt");
  TH1F * hist_SMttbar_noBtag_npv1 = (TH1F*)f_SMttbar_13TeV_noBtag->Get("hist_SMttbar_noBtag_npv1");

  TH1F * h_topTagEffPt = (TH1F*)f8->Get("h_topTagEffPt");
  TH1F * h_topTagEffNpv = (TH1F*)f8->Get("h_topTagEffNpv");
  TH1F * h_topTagEffNpv_400 = (TH1F*)f8->Get("h_topTagEffNpv_400");
  TH1F * h_topTagEffPtDenom = (TH1F*)f8->Get("h_topTagEffPtDenom");
  TH1F * h_topTagEffNpvDenom = (TH1F*)f8->Get("h_topTagEffNpvDenom");
  */

  //Z Prime Histograms
  //efficiency histograms
  TH1F * hist_ZPrime_noBtag_topTagEffPt = (TH1F*) f_ZPrime_13TeV_noBtag->Get("hist_ZPrime_noBtag_topTagEffPt");
  TH1F * hist_ZPrime_filtered_noBtag_topTagEffPt = (TH1F*) f_ZPrime_13TeV_noBtag->Get("hist_ZPrime_noBtag_filtered_topTagEffPt");
  TH1F * hist_ZPrime_pruned_noBtag_topTagEffPt = (TH1F*) f_ZPrime_13TeV_noBtag->Get("hist_ZPrime_noBtag_pruned_topTagEffPt");
  TH1F * hist_ZPrime_trimmed_noBtag_topTagEffPt = (TH1F*) f_ZPrime_13TeV_noBtag->Get("hist_ZPrime_noBtag_trimmed_topTagEffPt");

  TH1F * hist_ZPrime_noBtag_topTagEffNpv = (TH1F*) f_ZPrime_13TeV_noBtag->Get("hist_ZPrime_noBtag_topTagEffNpv");
  TH1F * hist_ZPrime_filtered_noBtag_topTagEffNpv = (TH1F*) f_ZPrime_13TeV_noBtag->Get("hist_ZPrime_noBtag_filtered_topTagEffNpv");
  TH1F * hist_ZPrime_pruned_noBtag_topTagEffNpv = (TH1F*) f_ZPrime_13TeV_noBtag->Get("hist_ZPrime_noBtag_pruned_topTagEffNpv");
  TH1F * hist_ZPrime_trimmed_noBtag_topTagEffNpv = (TH1F*) f_ZPrime_13TeV_noBtag->Get("hist_ZPrime_noBtag_trimmed_topTagEffNpv");

  TH1F * hist_ZPrime_noBtag_topTagEffNpv_400 = (TH1F*) f_ZPrime_13TeV_noBtag->Get("hist_ZPrime_noBtag_topTagEffNpv_400");
  TH1F * hist_ZPrime_filtered_noBtag_topTagEffNpv_400 = (TH1F*) f_ZPrime_13TeV_noBtag->Get("hist_ZPrime_noBtag_filtered_topTagEffNpv_400");
  TH1F * hist_ZPrime_pruned_noBtag_topTagEffNpv_400 = (TH1F*) f_ZPrime_13TeV_noBtag->Get("hist_ZPrime_noBtag_pruned_topTagEffNpv_400");
  TH1F * hist_ZPrime_trimmed_noBtag_topTagEffNpv_400 = (TH1F*) f_ZPrime_13TeV_noBtag->Get("hist_ZPrime_noBtag_trimmed_topTagEffNpv_400");

  TH1F * hist_ZPrime_looseBtag_topTagEffPt = (TH1F*) f_ZPrime_13TeV_looseBtag->Get("hist_ZPrime_looseBtag_topTagEffPt");
  TH1F * hist_ZPrime_filtered_looseBtag_topTagEffPt = (TH1F*) f_ZPrime_13TeV_looseBtag->Get("hist_ZPrime_looseBtag_filtered_topTagEffPt");
  TH1F * hist_ZPrime_pruned_looseBtag_topTagEffPt = (TH1F*) f_ZPrime_13TeV_looseBtag->Get("hist_ZPrime_looseBtag_pruned_topTagEffPt");
  TH1F * hist_ZPrime_trimmed_looseBtag_topTagEffPt = (TH1F*) f_ZPrime_13TeV_looseBtag->Get("hist_ZPrime_looseBtag_trimmed_topTagEffPt");

  TH1F * hist_ZPrime_looseBtag_topTagEffNpv = (TH1F*) f_ZPrime_13TeV_looseBtag->Get("hist_ZPrime_looseBtag_topTagEffNpv");
  TH1F * hist_ZPrime_filtered_looseBtag_topTagEffNpv = (TH1F*) f_ZPrime_13TeV_looseBtag->Get("hist_ZPrime_looseBtag_filtered_topTagEffNpv");
  TH1F * hist_ZPrime_pruned_looseBtag_topTagEffNpv = (TH1F*) f_ZPrime_13TeV_looseBtag->Get("hist_ZPrime_looseBtag_pruned_topTagEffNpv");
  TH1F * hist_ZPrime_trimmed_looseBtag_topTagEffNpv = (TH1F*) f_ZPrime_13TeV_looseBtag->Get("hist_ZPrime_looseBtag_trimmed_topTagEffNpv");

  TH1F * hist_ZPrime_looseBtag_topTagEffNpv_400 = (TH1F*) f_ZPrime_13TeV_looseBtag->Get("hist_ZPrime_looseBtag_topTagEffNpv_400");
  TH1F * hist_ZPrime_filtered_looseBtag_topTagEffNpv_400 = (TH1F*) f_ZPrime_13TeV_looseBtag->Get("hist_ZPrime_looseBtag_filtered_topTagEffNpv_400");
  TH1F * hist_ZPrime_pruned_looseBtag_topTagEffNpv_400 = (TH1F*) f_ZPrime_13TeV_looseBtag->Get("hist_ZPrime_looseBtag_pruned_topTagEffNpv_400");
  TH1F * hist_ZPrime_trimmed_looseBtag_topTagEffNpv_400 = (TH1F*) f_ZPrime_13TeV_looseBtag->Get("hist_ZPrime_looseBtag_trimmed_topTagEffNpv_400");

  TH1F * hist_ZPrime_mediumBtag_topTagEffPt = (TH1F*) f_ZPrime_13TeV_mediumBtag->Get("hist_ZPrime_mediumBtag_topTagEffPt");
  TH1F * hist_ZPrime_filtered_mediumBtag_topTagEffPt = (TH1F*) f_ZPrime_13TeV_mediumBtag->Get("hist_ZPrime_mediumBtag_filtered_topTagEffPt");
  TH1F * hist_ZPrime_pruned_mediumBtag_topTagEffPt = (TH1F*) f_ZPrime_13TeV_mediumBtag->Get("hist_ZPrime_mediumBtag_pruned_topTagEffPt");
  TH1F * hist_ZPrime_trimmed_mediumBtag_topTagEffPt = (TH1F*) f_ZPrime_13TeV_mediumBtag->Get("hist_ZPrime_mediumBtag_trimmed_topTagEffPt");

  TH1F * hist_ZPrime_mediumBtag_topTagEffNpv = (TH1F*) f_ZPrime_13TeV_mediumBtag->Get("hist_ZPrime_mediumBtag_topTagEffNpv");
  TH1F * hist_ZPrime_filtered_mediumBtag_topTagEffNpv = (TH1F*) f_ZPrime_13TeV_mediumBtag->Get("hist_ZPrime_mediumBtag_filtered_topTagEffNpv");
  TH1F * hist_ZPrime_pruned_mediumBtag_topTagEffNpv = (TH1F*) f_ZPrime_13TeV_mediumBtag->Get("hist_ZPrime_mediumBtag_pruned_topTagEffNpv");
  TH1F * hist_ZPrime_trimmed_mediumBtag_topTagEffNpv = (TH1F*) f_ZPrime_13TeV_mediumBtag->Get("hist_ZPrime_mediumBtag_trimmed_topTagEffNpv");

  TH1F * hist_ZPrime_mediumBtag_topTagEffNpv_400 = (TH1F*) f_ZPrime_13TeV_mediumBtag->Get("hist_ZPrime_mediumBtag_topTagEffNpv_400");
  TH1F * hist_ZPrime_filtered_mediumBtag_topTagEffNpv_400 = (TH1F*) f_ZPrime_13TeV_mediumBtag->Get("hist_ZPrime_mediumBtag_filtered_topTagEffNpv_400");
  TH1F * hist_ZPrime_pruned_mediumBtag_topTagEffNpv_400 = (TH1F*) f_ZPrime_13TeV_mediumBtag->Get("hist_ZPrime_mediumBtag_pruned_topTagEffNpv_400");
  TH1F * hist_ZPrime_trimmed_mediumBtag_topTagEffNpv_400 = (TH1F*) f_ZPrime_13TeV_mediumBtag->Get("hist_ZPrime_mediumBtag_trimmed_topTagEffNpv_400");

  //denominator histograms
  TH1F * hist_ZPrime_noBtag_jet1pt = (TH1F*) f_ZPrime_13TeV_noBtag->Get("hist_ZPrime_noBtag_jet1pt");
  TH1F * hist_ZPrime_filtered_noBtag_jet1pt = (TH1F*) f_ZPrime_13TeV_noBtag->Get("hist_ZPrime_noBtag_filtered_jet1pt");
  TH1F * hist_ZPrime_pruned_noBtag_jet1pt = (TH1F*) f_ZPrime_13TeV_noBtag->Get("hist_ZPrime_noBtag_pruned_jet1pt");
  TH1F * hist_ZPrime_trimmed_noBtag_jet1pt = (TH1F*) f_ZPrime_13TeV_noBtag->Get("hist_ZPrime_noBtag_trimmed_jet1pt");

  TH1F * hist_ZPrime_noBtag_npv1 = (TH1F*) f_ZPrime_13TeV_noBtag->Get("hist_ZPrime_noBtag_npv1");
  TH1F * hist_ZPrime_filtered_noBtag_npv1 = (TH1F*) f_ZPrime_13TeV_noBtag->Get("hist_ZPrime_noBtag_filtered_npv1");
  TH1F * hist_ZPrime_pruned_noBtag_npv1 = (TH1F*) f_ZPrime_13TeV_noBtag->Get("hist_ZPrime_noBtag_pruned_npv1");
  TH1F * hist_ZPrime_trimmed_noBtag_npv1 = (TH1F*) f_ZPrime_13TeV_noBtag->Get("hist_ZPrime_noBtag_trimmed_npv1");

  TH1F * hist_ZPrime_noBtag_npv1_400 = (TH1F*) f_ZPrime_13TeV_noBtag->Get("hist_ZPrime_noBtag_npv1_400");
  TH1F * hist_ZPrime_filtered_noBtag_npv1_400 = (TH1F*) f_ZPrime_13TeV_noBtag->Get("hist_ZPrime_noBtag_filtered_npv1_400");
  TH1F * hist_ZPrime_pruned_noBtag_npv1_400 = (TH1F*) f_ZPrime_13TeV_noBtag->Get("hist_ZPrime_noBtag_pruned_npv1_400");
  TH1F * hist_ZPrime_trimmed_noBtag_npv1_400 = (TH1F*) f_ZPrime_13TeV_noBtag->Get("hist_ZPrime_noBtag_trimmed_npv1_400");

  TH1F * hist_ZPrime_looseBtag_jet1pt = (TH1F*) f_ZPrime_13TeV_looseBtag->Get("hist_ZPrime_looseBtag_jet1pt");
  TH1F * hist_ZPrime_filtered_looseBtag_jet1pt = (TH1F*) f_ZPrime_13TeV_looseBtag->Get("hist_ZPrime_looseBtag_filtered_jet1pt");
  TH1F * hist_ZPrime_pruned_looseBtag_jet1pt = (TH1F*) f_ZPrime_13TeV_looseBtag->Get("hist_ZPrime_looseBtag_pruned_jet1pt");
  TH1F * hist_ZPrime_trimmed_looseBtag_jet1pt = (TH1F*) f_ZPrime_13TeV_looseBtag->Get("hist_ZPrime_looseBtag_trimmed_jet1pt");

  TH1F * hist_ZPrime_looseBtag_npv1 = (TH1F*) f_ZPrime_13TeV_looseBtag->Get("hist_ZPrime_looseBtag_npv1");
  TH1F * hist_ZPrime_filtered_looseBtag_npv1 = (TH1F*) f_ZPrime_13TeV_looseBtag->Get("hist_ZPrime_looseBtag_filtered_npv1");
  TH1F * hist_ZPrime_pruned_looseBtag_npv1 = (TH1F*) f_ZPrime_13TeV_looseBtag->Get("hist_ZPrime_looseBtag_pruned_npv1");
  TH1F * hist_ZPrime_trimmed_looseBtag_npv1 = (TH1F*) f_ZPrime_13TeV_looseBtag->Get("hist_ZPrime_looseBtag_trimmed_npv1");

  TH1F * hist_ZPrime_looseBtag_npv1_400 = (TH1F*) f_ZPrime_13TeV_looseBtag->Get("hist_ZPrime_looseBtag_npv1_400");
  TH1F * hist_ZPrime_filtered_looseBtag_npv1_400 = (TH1F*) f_ZPrime_13TeV_looseBtag->Get("hist_ZPrime_looseBtag_filtered_npv1_400");
  TH1F * hist_ZPrime_pruned_looseBtag_npv1_400 = (TH1F*) f_ZPrime_13TeV_looseBtag->Get("hist_ZPrime_looseBtag_pruned_npv1_400");
  TH1F * hist_ZPrime_trimmed_looseBtag_npv1_400 = (TH1F*) f_ZPrime_13TeV_looseBtag->Get("hist_ZPrime_looseBtag_trimmed_npv1_400");

  TH1F * hist_ZPrime_mediumBtag_jet1pt = (TH1F*) f_ZPrime_13TeV_mediumBtag->Get("hist_ZPrime_mediumBtag_jet1pt");
  TH1F * hist_ZPrime_filtered_mediumBtag_jet1pt = (TH1F*) f_ZPrime_13TeV_mediumBtag->Get("hist_ZPrime_mediumBtag_filtered_jet1pt");
  TH1F * hist_ZPrime_pruned_mediumBtag_jet1pt = (TH1F*) f_ZPrime_13TeV_mediumBtag->Get("hist_ZPrime_mediumBtag_pruned_jet1pt");
  TH1F * hist_ZPrime_trimmed_mediumBtag_jet1pt = (TH1F*) f_ZPrime_13TeV_mediumBtag->Get("hist_ZPrime_mediumBtag_trimmed_jet1pt");

  TH1F * hist_ZPrime_mediumBtag_npv1 = (TH1F*) f_ZPrime_13TeV_mediumBtag->Get("hist_ZPrime_mediumBtag_npv1");
  TH1F * hist_ZPrime_filtered_mediumBtag_npv1 = (TH1F*) f_ZPrime_13TeV_mediumBtag->Get("hist_ZPrime_mediumBtag_filtered_npv1");
  TH1F * hist_ZPrime_pruned_mediumBtag_npv1 = (TH1F*) f_ZPrime_13TeV_mediumBtag->Get("hist_ZPrime_mediumBtag_pruned_npv1");
  TH1F * hist_ZPrime_trimmed_mediumBtag_npv1 = (TH1F*) f_ZPrime_13TeV_mediumBtag->Get("hist_ZPrime_mediumBtag_trimmed_npv1");

  TH1F * hist_ZPrime_mediumBtag_npv1_400 = (TH1F*) f_ZPrime_13TeV_mediumBtag->Get("hist_ZPrime_mediumBtag_npv1_400");
  TH1F * hist_ZPrime_filtered_mediumBtag_npv1_400 = (TH1F*) f_ZPrime_13TeV_mediumBtag->Get("hist_ZPrime_mediumBtag_filtered_npv1_400");
  TH1F * hist_ZPrime_pruned_mediumBtag_npv1_400 = (TH1F*) f_ZPrime_13TeV_mediumBtag->Get("hist_ZPrime_mediumBtag_pruned_npv1_400");
  TH1F * hist_ZPrime_trimmed_mediumBtag_npv1_400 = (TH1F*) f_ZPrime_13TeV_mediumBtag->Get("hist_ZPrime_mediumBtag_trimmed_npv1_400");

  //numerator histograms
  TH1F * hist_ZPrime_noBtag_tagJet1pt = (TH1F*) f_ZPrime_13TeV_noBtag->Get("hist_ZPrime_noBtag_tagJet1pt");
  TH1F * hist_ZPrime_filtered_noBtag_tagJet1pt = (TH1F*) f_ZPrime_13TeV_noBtag->Get("hist_ZPrime_noBtag_filtered_tagJet1pt");
  TH1F * hist_ZPrime_pruned_noBtag_tagJet1pt = (TH1F*) f_ZPrime_13TeV_noBtag->Get("hist_ZPrime_noBtag_pruned_tagJet1pt");
  TH1F * hist_ZPrime_trimmed_noBtag_tagJet1pt = (TH1F*) f_ZPrime_13TeV_noBtag->Get("hist_ZPrime_noBtag_trimmed_tagJet1pt");

  TH1F * hist_ZPrime_noBtag_tagNpv1 = (TH1F*) f_ZPrime_13TeV_noBtag->Get("hist_ZPrime_noBtag_tagNpv1");
  TH1F * hist_ZPrime_filtered_noBtag_tagNpv1 = (TH1F*) f_ZPrime_13TeV_noBtag->Get("hist_ZPrime_noBtag_filtered_tagNpv1");
  TH1F * hist_ZPrime_pruned_noBtag_tagNpv1 = (TH1F*) f_ZPrime_13TeV_noBtag->Get("hist_ZPrime_noBtag_pruned_tagNpv1");
  TH1F * hist_ZPrime_trimmed_noBtag_tagNpv1 = (TH1F*) f_ZPrime_13TeV_noBtag->Get("hist_ZPrime_noBtag_trimmed_tagNpv1");

  TH1F * hist_ZPrime_noBtag_tagNpv1_400 = (TH1F*) f_ZPrime_13TeV_noBtag->Get("hist_ZPrime_noBtag_tagNpv1_400");
  TH1F * hist_ZPrime_filtered_noBtag_tagNpv1_400 = (TH1F*) f_ZPrime_13TeV_noBtag->Get("hist_ZPrime_noBtag_filtered_tagNpv1_400");
  TH1F * hist_ZPrime_pruned_noBtag_tagNpv1_400 = (TH1F*) f_ZPrime_13TeV_noBtag->Get("hist_ZPrime_noBtag_pruned_tagNpv1_400");
  TH1F * hist_ZPrime_trimmed_noBtag_tagNpv1_400 = (TH1F*) f_ZPrime_13TeV_noBtag->Get("hist_ZPrime_noBtag_trimmed_tagNpv1_400");

  TH1F * hist_ZPrime_looseBtag_tagJet1pt = (TH1F*) f_ZPrime_13TeV_looseBtag->Get("hist_ZPrime_looseBtag_tagJet1pt");
  TH1F * hist_ZPrime_filtered_looseBtag_tagJet1pt = (TH1F*) f_ZPrime_13TeV_looseBtag->Get("hist_ZPrime_looseBtag_filtered_tagJet1pt");
  TH1F * hist_ZPrime_pruned_looseBtag_tagJet1pt = (TH1F*) f_ZPrime_13TeV_looseBtag->Get("hist_ZPrime_looseBtag_pruned_tagJet1pt");
  TH1F * hist_ZPrime_trimmed_looseBtag_tagJet1pt = (TH1F*) f_ZPrime_13TeV_looseBtag->Get("hist_ZPrime_looseBtag_trimmed_tagJet1pt");

  TH1F * hist_ZPrime_looseBtag_tagNpv1 = (TH1F*) f_ZPrime_13TeV_looseBtag->Get("hist_ZPrime_looseBtag_tagNpv1");
  TH1F * hist_ZPrime_filtered_looseBtag_tagNpv1 = (TH1F*) f_ZPrime_13TeV_looseBtag->Get("hist_ZPrime_looseBtag_filtered_tagNpv1");
  TH1F * hist_ZPrime_pruned_looseBtag_tagNpv1 = (TH1F*) f_ZPrime_13TeV_looseBtag->Get("hist_ZPrime_looseBtag_pruned_tagNpv1");
  TH1F * hist_ZPrime_trimmed_looseBtag_tagNpv1 = (TH1F*) f_ZPrime_13TeV_looseBtag->Get("hist_ZPrime_looseBtag_trimmed_tagNpv1");

  TH1F * hist_ZPrime_looseBtag_tagNpv1_400 = (TH1F*) f_ZPrime_13TeV_looseBtag->Get("hist_ZPrime_looseBtag_tagNpv1_400");
  TH1F * hist_ZPrime_filtered_looseBtag_tagNpv1_400 = (TH1F*) f_ZPrime_13TeV_looseBtag->Get("hist_ZPrime_looseBtag_filtered_tagNpv1_400");
  TH1F * hist_ZPrime_pruned_looseBtag_tagNpv1_400 = (TH1F*) f_ZPrime_13TeV_looseBtag->Get("hist_ZPrime_looseBtag_pruned_tagNpv1_400");
  TH1F * hist_ZPrime_trimmed_looseBtag_tagNpv1_400 = (TH1F*) f_ZPrime_13TeV_looseBtag->Get("hist_ZPrime_looseBtag_trimmed_tagNpv1_400");

  TH1F * hist_ZPrime_mediumBtag_tagJet1pt = (TH1F*) f_ZPrime_13TeV_mediumBtag->Get("hist_ZPrime_mediumBtag_tagJet1pt");
  TH1F * hist_ZPrime_filtered_mediumBtag_tagJet1pt = (TH1F*) f_ZPrime_13TeV_mediumBtag->Get("hist_ZPrime_mediumBtag_filtered_tagJet1pt");
  TH1F * hist_ZPrime_pruned_mediumBtag_tagJet1pt = (TH1F*) f_ZPrime_13TeV_mediumBtag->Get("hist_ZPrime_mediumBtag_pruned_tagJet1pt");
  TH1F * hist_ZPrime_trimmed_mediumBtag_tagJet1pt = (TH1F*) f_ZPrime_13TeV_mediumBtag->Get("hist_ZPrime_mediumBtag_trimmed_tagJet1pt");

  TH1F * hist_ZPrime_mediumBtag_tagNpv1 = (TH1F*) f_ZPrime_13TeV_mediumBtag->Get("hist_ZPrime_mediumBtag_tagNpv1");
  TH1F * hist_ZPrime_filtered_mediumBtag_tagNpv1 = (TH1F*) f_ZPrime_13TeV_mediumBtag->Get("hist_ZPrime_mediumBtag_filtered_tagNpv1");
  TH1F * hist_ZPrime_pruned_mediumBtag_tagNpv1 = (TH1F*) f_ZPrime_13TeV_mediumBtag->Get("hist_ZPrime_mediumBtag_pruned_tagNpv1");
  TH1F * hist_ZPrime_trimmed_mediumBtag_tagNpv1 = (TH1F*) f_ZPrime_13TeV_mediumBtag->Get("hist_ZPrime_mediumBtag_trimmed_tagNpv1");

  TH1F * hist_ZPrime_mediumBtag_tagNpv1_400 = (TH1F*) f_ZPrime_13TeV_mediumBtag->Get("hist_ZPrime_mediumBtag_tagNpv1_400");
  TH1F * hist_ZPrime_filtered_mediumBtag_tagNpv1_400 = (TH1F*) f_ZPrime_13TeV_mediumBtag->Get("hist_ZPrime_mediumBtag_filtered_tagNpv1_400");
  TH1F * hist_ZPrime_pruned_mediumBtag_tagNpv1_400 = (TH1F*) f_ZPrime_13TeV_mediumBtag->Get("hist_ZPrime_mediumBtag_pruned_tagNpv1_400");
  TH1F * hist_ZPrime_trimmed_mediumBtag_tagNpv1_400 = (TH1F*) f_ZPrime_13TeV_mediumBtag->Get("hist_ZPrime_mediumBtag_trimmed_tagNpv1_400");
  /*
  //SM ttbar histograms
  TH1F * hist_SMttbar_noBtag_topTagEffPt = (TH1F*) f_SMttbar_13TeV_noBtag->Get("hist_SMttbar_noBtag_topTagEffPt");
  TH1F * hist_SMttbar_filtered_noBtag_topTagEffPt = (TH1F*) f_SMttbar_13TeV_noBtag->Get("hist_SMttbar_noBtag_filtered_topTagEffPt");
  TH1F * hist_SMttbar_pruned_noBtag_topTagEffPt = (TH1F*) f_SMttbar_13TeV_noBtag->Get("hist_SMttbar_noBtag_pruned_topTagEffPt");
  TH1F * hist_SMttbar_trimmed_noBtag_topTagEffPt = (TH1F*) f_SMttbar_13TeV_noBtag->Get("hist_SMttbar_noBtag_trimmed_topTagEffPt");

  TH1F * hist_SMttbar_noBtag_topTagEffNpv = (TH1F*) f_SMttbar_13TeV_noBtag->Get("hist_SMttbar_noBtag_topTagEffNpv");
  TH1F * hist_SMttbar_filtered_noBtag_topTagEffNpv = (TH1F*) f_SMttbar_13TeV_noBtag->Get("hist_SMttbar_noBtag_filtered_topTagEffNpv");
  TH1F * hist_SMttbar_pruned_noBtag_topTagEffNpv = (TH1F*) f_SMttbar_13TeV_noBtag->Get("hist_SMttbar_noBtag_pruned_topTagEffNpv");
  TH1F * hist_SMttbar_trimmed_noBtag_topTagEffNpv = (TH1F*) f_SMttbar_13TeV_noBtag->Get("hist_SMttbar_noBtag_trimmed_topTagEffNpv");

  TH1F * hist_SMttbar_noBtag_topTagEffNpv_400 = (TH1F*) f_SMttbar_13TeV_noBtag->Get("hist_SMttbar_noBtag_topTagEffNpv_400");
  TH1F * hist_SMttbar_filtered_noBtag_topTagEffNpv_400 = (TH1F*) f_SMttbar_13TeV_noBtag->Get("hist_SMttbar_noBtag_filtered_topTagEffNpv_400");
  TH1F * hist_SMttbar_pruned_noBtag_topTagEffNpv_400 = (TH1F*) f_SMttbar_13TeV_noBtag->Get("hist_SMttbar_noBtag_pruned_topTagEffNpv_400");
  TH1F * hist_SMttbar_trimmed_noBtag_topTagEffNpv_400 = (TH1F*) f_SMttbar_13TeV_noBtag->Get("hist_SMttbar_noBtag_trimmed_topTagEffNpv_400");

  TH1F * hist_SMttbar_noBtag_topTagEffNpv_500 = (TH1F*) f_SMttbar_13TeV_noBtag->Get("hist_SMttbar_noBtag_topTagEffNpv_500");
  TH1F * hist_SMttbar_filtered_noBtag_topTagEffNpv_500 = (TH1F*) f_SMttbar_13TeV_noBtag->Get("hist_SMttbar_noBtag_filtered_topTagEffNpv_500");
  TH1F * hist_SMttbar_pruned_noBtag_topTagEffNpv_500 = (TH1F*) f_SMttbar_13TeV_noBtag->Get("hist_SMttbar_noBtag_pruned_topTagEffNpv_500");
  TH1F * hist_SMttbar_trimmed_noBtag_topTagEffNpv_500 = (TH1F*) f_SMttbar_13TeV_noBtag->Get("hist_SMttbar_noBtag_trimmed_topTagEffNpv_500");

  TH1F * hist_SMttbar_noBtag_topTagEffNpv_600 = (TH1F*) f_SMttbar_13TeV_noBtag->Get("hist_SMttbar_noBtag_topTagEffNpv_600");
  TH1F * hist_SMttbar_filtered_noBtag_topTagEffNpv_600 = (TH1F*) f_SMttbar_13TeV_noBtag->Get("hist_SMttbar_noBtag_filtered_topTagEffNpv_600");
  TH1F * hist_SMttbar_pruned_noBtag_topTagEffNpv_600 = (TH1F*) f_SMttbar_13TeV_noBtag->Get("hist_SMttbar_noBtag_pruned_topTagEffNpv_600");
  TH1F * hist_SMttbar_trimmed_noBtag_topTagEffNpv_600 = (TH1F*) f_SMttbar_13TeV_noBtag->Get("hist_SMttbar_noBtag_trimmed_topTagEffNpv_600");

  TH1F * hist_SMttbar_noBtag_topTagEffNpv_700 = (TH1F*) f_SMttbar_13TeV_noBtag->Get("hist_SMttbar_noBtag_topTagEffNpv_700");
  TH1F * hist_SMttbar_filtered_noBtag_topTagEffNpv_700 = (TH1F*) f_SMttbar_13TeV_noBtag->Get("hist_SMttbar_noBtag_filtered_topTagEffNpv_700");
  TH1F * hist_SMttbar_pruned_noBtag_topTagEffNpv_700 = (TH1F*) f_SMttbar_13TeV_noBtag->Get("hist_SMttbar_noBtag_pruned_topTagEffNpv_700");
  TH1F * hist_SMttbar_trimmed_noBtag_topTagEffNpv_700 = (TH1F*) f_SMttbar_13TeV_noBtag->Get("hist_SMttbar_noBtag_trimmed_topTagEffNpv_700");

  TH1F * hist_SMttbar_looseBtag_topTagEffPt = (TH1F*) f_SMttbar_13TeV_looseBtag->Get("hist_SMttbar_looseBtag_topTagEffPt");
  TH1F * hist_SMttbar_filtered_looseBtag_topTagEffPt = (TH1F*) f_SMttbar_13TeV_looseBtag->Get("hist_SMttbar_looseBtag_filtered_topTagEffPt");
  TH1F * hist_SMttbar_pruned_looseBtag_topTagEffPt = (TH1F*) f_SMttbar_13TeV_looseBtag->Get("hist_SMttbar_looseBtag_pruned_topTagEffPt");
  TH1F * hist_SMttbar_trimmed_looseBtag_topTagEffPt = (TH1F*) f_SMttbar_13TeV_looseBtag->Get("hist_SMttbar_looseBtag_trimmed_topTagEffPt");

  TH1F * hist_SMttbar_looseBtag_topTagEffNpv = (TH1F*) f_SMttbar_13TeV_looseBtag->Get("hist_SMttbar_looseBtag_topTagEffNpv");
  TH1F * hist_SMttbar_filtered_looseBtag_topTagEffNpv = (TH1F*) f_SMttbar_13TeV_looseBtag->Get("hist_SMttbar_looseBtag_filtered_topTagEffNpv");
  TH1F * hist_SMttbar_pruned_looseBtag_topTagEffNpv = (TH1F*) f_SMttbar_13TeV_looseBtag->Get("hist_SMttbar_looseBtag_pruned_topTagEffNpv");
  TH1F * hist_SMttbar_trimmed_looseBtag_topTagEffNpv = (TH1F*) f_SMttbar_13TeV_looseBtag->Get("hist_SMttbar_looseBtag_trimmed_topTagEffNpv");

  TH1F * hist_SMttbar_looseBtag_topTagEffNpv_400 = (TH1F*) f_SMttbar_13TeV_looseBtag->Get("hist_SMttbar_looseBtag_topTagEffNpv_400");
  TH1F * hist_SMttbar_filtered_looseBtag_topTagEffNpv_400 = (TH1F*) f_SMttbar_13TeV_looseBtag->Get("hist_SMttbar_looseBtag_filtered_topTagEffNpv_400");
  TH1F * hist_SMttbar_pruned_looseBtag_topTagEffNpv_400 = (TH1F*) f_SMttbar_13TeV_looseBtag->Get("hist_SMttbar_looseBtag_pruned_topTagEffNpv_400");
  TH1F * hist_SMttbar_trimmed_looseBtag_topTagEffNpv_400 = (TH1F*) f_SMttbar_13TeV_looseBtag->Get("hist_SMttbar_looseBtag_trimmed_topTagEffNpv_400");

  TH1F * hist_SMttbar_mediumBtag_topTagEffPt = (TH1F*) f_SMttbar_13TeV_mediumBtag->Get("hist_SMttbar_mediumBtag_topTagEffPt");
  TH1F * hist_SMttbar_filtered_mediumBtag_topTagEffPt = (TH1F*) f_SMttbar_13TeV_mediumBtag->Get("hist_SMttbar_mediumBtag_filtered_topTagEffPt");
  TH1F * hist_SMttbar_pruned_mediumBtag_topTagEffPt = (TH1F*) f_SMttbar_13TeV_mediumBtag->Get("hist_SMttbar_mediumBtag_pruned_topTagEffPt");
  TH1F * hist_SMttbar_trimmed_mediumBtag_topTagEffPt = (TH1F*) f_SMttbar_13TeV_mediumBtag->Get("hist_SMttbar_mediumBtag_trimmed_topTagEffPt");

  TH1F * hist_SMttbar_mediumBtag_topTagEffNpv = (TH1F*) f_SMttbar_13TeV_mediumBtag->Get("hist_SMttbar_mediumBtag_topTagEffNpv");
  TH1F * hist_SMttbar_filtered_mediumBtag_topTagEffNpv = (TH1F*) f_SMttbar_13TeV_mediumBtag->Get("hist_SMttbar_mediumBtag_filtered_topTagEffNpv");
  TH1F * hist_SMttbar_pruned_mediumBtag_topTagEffNpv = (TH1F*) f_SMttbar_13TeV_mediumBtag->Get("hist_SMttbar_mediumBtag_pruned_topTagEffNpv");
  TH1F * hist_SMttbar_trimmed_mediumBtag_topTagEffNpv = (TH1F*) f_SMttbar_13TeV_mediumBtag->Get("hist_SMttbar_mediumBtag_trimmed_topTagEffNpv");

  TH1F * hist_SMttbar_mediumBtag_topTagEffNpv_400 = (TH1F*) f_SMttbar_13TeV_mediumBtag->Get("hist_SMttbar_mediumBtag_topTagEffNpv_400");
  TH1F * hist_SMttbar_filtered_mediumBtag_topTagEffNpv_400 = (TH1F*) f_SMttbar_13TeV_mediumBtag->Get("hist_SMttbar_mediumBtag_filtered_topTagEffNpv_400");
  TH1F * hist_SMttbar_pruned_mediumBtag_topTagEffNpv_400 = (TH1F*) f_SMttbar_13TeV_mediumBtag->Get("hist_SMttbar_mediumBtag_pruned_topTagEffNpv_400");
  TH1F * hist_SMttbar_trimmed_mediumBtag_topTagEffNpv_400 = (TH1F*) f_SMttbar_13TeV_mediumBtag->Get("hist_SMttbar_mediumBtag_trimmed_topTagEffNpv_400");
  */

  //QCD pt 1800 to 2400 Histograms
  //efficiency histograms
  TH1F * hist_QCD_noBtag_topTagEffPt = (TH1F*) f_QCD_13TeV_noBtag->Get("hist_QCD_noBtag_topTagEffPt");
  TH1F * hist_QCD_filtered_noBtag_topTagEffPt = (TH1F*) f_QCD_13TeV_noBtag->Get("hist_QCD_noBtag_filtered_topTagEffPt");
  TH1F * hist_QCD_pruned_noBtag_topTagEffPt = (TH1F*) f_QCD_13TeV_noBtag->Get("hist_QCD_noBtag_pruned_topTagEffPt");
  TH1F * hist_QCD_trimmed_noBtag_topTagEffPt = (TH1F*) f_QCD_13TeV_noBtag->Get("hist_QCD_noBtag_trimmed_topTagEffPt");

  TH1F * hist_QCD_noBtag_topTagEffNpv = (TH1F*) f_QCD_13TeV_noBtag->Get("hist_QCD_noBtag_topTagEffNpv");
  TH1F * hist_QCD_filtered_noBtag_topTagEffNpv = (TH1F*) f_QCD_13TeV_noBtag->Get("hist_QCD_noBtag_filtered_topTagEffNpv");
  TH1F * hist_QCD_pruned_noBtag_topTagEffNpv = (TH1F*) f_QCD_13TeV_noBtag->Get("hist_QCD_noBtag_pruned_topTagEffNpv");
  TH1F * hist_QCD_trimmed_noBtag_topTagEffNpv = (TH1F*) f_QCD_13TeV_noBtag->Get("hist_QCD_noBtag_trimmed_topTagEffNpv");

  TH1F * hist_QCD_noBtag_topTagEffNpv_400 = (TH1F*) f_QCD_13TeV_noBtag->Get("hist_QCD_noBtag_topTagEffNpv_400");
  TH1F * hist_QCD_filtered_noBtag_topTagEffNpv_400 = (TH1F*) f_QCD_13TeV_noBtag->Get("hist_QCD_noBtag_filtered_topTagEffNpv_400");
  TH1F * hist_QCD_pruned_noBtag_topTagEffNpv_400 = (TH1F*) f_QCD_13TeV_noBtag->Get("hist_QCD_noBtag_pruned_topTagEffNpv_400");
  TH1F * hist_QCD_trimmed_noBtag_topTagEffNpv_400 = (TH1F*) f_QCD_13TeV_noBtag->Get("hist_QCD_noBtag_trimmed_topTagEffNpv_400");

  TH1F * hist_QCD_looseBtag_topTagEffPt = (TH1F*) f_QCD_13TeV_looseBtag->Get("hist_QCD_looseBtag_topTagEffPt");
  TH1F * hist_QCD_filtered_looseBtag_topTagEffPt = (TH1F*) f_QCD_13TeV_looseBtag->Get("hist_QCD_looseBtag_filtered_topTagEffPt");
  TH1F * hist_QCD_pruned_looseBtag_topTagEffPt = (TH1F*) f_QCD_13TeV_looseBtag->Get("hist_QCD_looseBtag_pruned_topTagEffPt");
  TH1F * hist_QCD_trimmed_looseBtag_topTagEffPt = (TH1F*) f_QCD_13TeV_looseBtag->Get("hist_QCD_looseBtag_trimmed_topTagEffPt");

  TH1F * hist_QCD_looseBtag_topTagEffNpv = (TH1F*) f_QCD_13TeV_looseBtag->Get("hist_QCD_looseBtag_topTagEffNpv");
  TH1F * hist_QCD_filtered_looseBtag_topTagEffNpv = (TH1F*) f_QCD_13TeV_looseBtag->Get("hist_QCD_looseBtag_filtered_topTagEffNpv");
  TH1F * hist_QCD_pruned_looseBtag_topTagEffNpv = (TH1F*) f_QCD_13TeV_looseBtag->Get("hist_QCD_looseBtag_pruned_topTagEffNpv");
  TH1F * hist_QCD_trimmed_looseBtag_topTagEffNpv = (TH1F*) f_QCD_13TeV_looseBtag->Get("hist_QCD_looseBtag_trimmed_topTagEffNpv");

  TH1F * hist_QCD_looseBtag_topTagEffNpv_400 = (TH1F*) f_QCD_13TeV_looseBtag->Get("hist_QCD_looseBtag_topTagEffNpv_400");
  TH1F * hist_QCD_filtered_looseBtag_topTagEffNpv_400 = (TH1F*) f_QCD_13TeV_looseBtag->Get("hist_QCD_looseBtag_filtered_topTagEffNpv_400");
  TH1F * hist_QCD_pruned_looseBtag_topTagEffNpv_400 = (TH1F*) f_QCD_13TeV_looseBtag->Get("hist_QCD_looseBtag_pruned_topTagEffNpv_400");
  TH1F * hist_QCD_trimmed_looseBtag_topTagEffNpv_400 = (TH1F*) f_QCD_13TeV_looseBtag->Get("hist_QCD_looseBtag_trimmed_topTagEffNpv_400");

  TH1F * hist_QCD_mediumBtag_topTagEffPt = (TH1F*) f_QCD_13TeV_mediumBtag->Get("hist_QCD_mediumBtag_topTagEffPt");
  TH1F * hist_QCD_filtered_mediumBtag_topTagEffPt = (TH1F*) f_QCD_13TeV_mediumBtag->Get("hist_QCD_mediumBtag_filtered_topTagEffPt");
  TH1F * hist_QCD_pruned_mediumBtag_topTagEffPt = (TH1F*) f_QCD_13TeV_mediumBtag->Get("hist_QCD_mediumBtag_pruned_topTagEffPt");
  TH1F * hist_QCD_trimmed_mediumBtag_topTagEffPt = (TH1F*) f_QCD_13TeV_mediumBtag->Get("hist_QCD_mediumBtag_trimmed_topTagEffPt");

  TH1F * hist_QCD_mediumBtag_topTagEffNpv = (TH1F*) f_QCD_13TeV_mediumBtag->Get("hist_QCD_mediumBtag_topTagEffNpv");
  TH1F * hist_QCD_filtered_mediumBtag_topTagEffNpv = (TH1F*) f_QCD_13TeV_mediumBtag->Get("hist_QCD_mediumBtag_filtered_topTagEffNpv");
  TH1F * hist_QCD_pruned_mediumBtag_topTagEffNpv = (TH1F*) f_QCD_13TeV_mediumBtag->Get("hist_QCD_mediumBtag_pruned_topTagEffNpv");
  TH1F * hist_QCD_trimmed_mediumBtag_topTagEffNpv = (TH1F*) f_QCD_13TeV_mediumBtag->Get("hist_QCD_mediumBtag_trimmed_topTagEffNpv");

  TH1F * hist_QCD_mediumBtag_topTagEffNpv_400 = (TH1F*) f_QCD_13TeV_mediumBtag->Get("hist_QCD_mediumBtag_topTagEffNpv_400");
  TH1F * hist_QCD_filtered_mediumBtag_topTagEffNpv_400 = (TH1F*) f_QCD_13TeV_mediumBtag->Get("hist_QCD_mediumBtag_filtered_topTagEffNpv_400");
  TH1F * hist_QCD_pruned_mediumBtag_topTagEffNpv_400 = (TH1F*) f_QCD_13TeV_mediumBtag->Get("hist_QCD_mediumBtag_pruned_topTagEffNpv_400");
  TH1F * hist_QCD_trimmed_mediumBtag_topTagEffNpv_400 = (TH1F*) f_QCD_13TeV_mediumBtag->Get("hist_QCD_mediumBtag_trimmed_topTagEffNpv_400");

  //denominator histograms
  TH1F * hist_QCD_noBtag_jet1pt = (TH1F*) f_QCD_13TeV_noBtag->Get("hist_QCD_noBtag_jet1pt");
  TH1F * hist_QCD_filtered_noBtag_jet1pt = (TH1F*) f_QCD_13TeV_noBtag->Get("hist_QCD_noBtag_filtered_jet1pt");
  TH1F * hist_QCD_pruned_noBtag_jet1pt = (TH1F*) f_QCD_13TeV_noBtag->Get("hist_QCD_noBtag_pruned_jet1pt");
  TH1F * hist_QCD_trimmed_noBtag_jet1pt = (TH1F*) f_QCD_13TeV_noBtag->Get("hist_QCD_noBtag_trimmed_jet1pt");

  TH1F * hist_QCD_noBtag_npv1 = (TH1F*) f_QCD_13TeV_noBtag->Get("hist_QCD_noBtag_npv1");
  TH1F * hist_QCD_filtered_noBtag_npv1 = (TH1F*) f_QCD_13TeV_noBtag->Get("hist_QCD_noBtag_filtered_npv1");
  TH1F * hist_QCD_pruned_noBtag_npv1 = (TH1F*) f_QCD_13TeV_noBtag->Get("hist_QCD_noBtag_pruned_npv1");
  TH1F * hist_QCD_trimmed_noBtag_npv1 = (TH1F*) f_QCD_13TeV_noBtag->Get("hist_QCD_noBtag_trimmed_npv1");

  TH1F * hist_QCD_noBtag_npv1_400 = (TH1F*) f_QCD_13TeV_noBtag->Get("hist_QCD_noBtag_npv1_400");
  TH1F * hist_QCD_filtered_noBtag_npv1_400 = (TH1F*) f_QCD_13TeV_noBtag->Get("hist_QCD_noBtag_filtered_npv1_400");
  TH1F * hist_QCD_pruned_noBtag_npv1_400 = (TH1F*) f_QCD_13TeV_noBtag->Get("hist_QCD_noBtag_pruned_npv1_400");
  TH1F * hist_QCD_trimmed_noBtag_npv1_400 = (TH1F*) f_QCD_13TeV_noBtag->Get("hist_QCD_noBtag_trimmed_npv1_400");

  TH1F * hist_QCD_looseBtag_jet1pt = (TH1F*) f_QCD_13TeV_looseBtag->Get("hist_QCD_looseBtag_jet1pt");
  TH1F * hist_QCD_filtered_looseBtag_jet1pt = (TH1F*) f_QCD_13TeV_looseBtag->Get("hist_QCD_looseBtag_filtered_jet1pt");
  TH1F * hist_QCD_pruned_looseBtag_jet1pt = (TH1F*) f_QCD_13TeV_looseBtag->Get("hist_QCD_looseBtag_pruned_jet1pt");
  TH1F * hist_QCD_trimmed_looseBtag_jet1pt = (TH1F*) f_QCD_13TeV_looseBtag->Get("hist_QCD_looseBtag_trimmed_jet1pt");

  TH1F * hist_QCD_looseBtag_npv1 = (TH1F*) f_QCD_13TeV_looseBtag->Get("hist_QCD_looseBtag_npv1");
  TH1F * hist_QCD_filtered_looseBtag_npv1 = (TH1F*) f_QCD_13TeV_looseBtag->Get("hist_QCD_looseBtag_filtered_npv1");
  TH1F * hist_QCD_pruned_looseBtag_npv1 = (TH1F*) f_QCD_13TeV_looseBtag->Get("hist_QCD_looseBtag_pruned_npv1");
  TH1F * hist_QCD_trimmed_looseBtag_npv1 = (TH1F*) f_QCD_13TeV_looseBtag->Get("hist_QCD_looseBtag_trimmed_npv1");

  TH1F * hist_QCD_looseBtag_npv1_400 = (TH1F*) f_QCD_13TeV_looseBtag->Get("hist_QCD_looseBtag_npv1_400");
  TH1F * hist_QCD_filtered_looseBtag_npv1_400 = (TH1F*) f_QCD_13TeV_looseBtag->Get("hist_QCD_looseBtag_filtered_npv1_400");
  TH1F * hist_QCD_pruned_looseBtag_npv1_400 = (TH1F*) f_QCD_13TeV_looseBtag->Get("hist_QCD_looseBtag_pruned_npv1_400");
  TH1F * hist_QCD_trimmed_looseBtag_npv1_400 = (TH1F*) f_QCD_13TeV_looseBtag->Get("hist_QCD_looseBtag_trimmed_npv1_400");

  TH1F * hist_QCD_mediumBtag_jet1pt = (TH1F*) f_QCD_13TeV_mediumBtag->Get("hist_QCD_mediumBtag_jet1pt");
  TH1F * hist_QCD_filtered_mediumBtag_jet1pt = (TH1F*) f_QCD_13TeV_mediumBtag->Get("hist_QCD_mediumBtag_filtered_jet1pt");
  TH1F * hist_QCD_pruned_mediumBtag_jet1pt = (TH1F*) f_QCD_13TeV_mediumBtag->Get("hist_QCD_mediumBtag_pruned_jet1pt");
  TH1F * hist_QCD_trimmed_mediumBtag_jet1pt = (TH1F*) f_QCD_13TeV_mediumBtag->Get("hist_QCD_mediumBtag_trimmed_jet1pt");

  TH1F * hist_QCD_mediumBtag_npv1 = (TH1F*) f_QCD_13TeV_mediumBtag->Get("hist_QCD_mediumBtag_npv1");
  TH1F * hist_QCD_filtered_mediumBtag_npv1 = (TH1F*) f_QCD_13TeV_mediumBtag->Get("hist_QCD_mediumBtag_filtered_npv1");
  TH1F * hist_QCD_pruned_mediumBtag_npv1 = (TH1F*) f_QCD_13TeV_mediumBtag->Get("hist_QCD_mediumBtag_pruned_npv1");
  TH1F * hist_QCD_trimmed_mediumBtag_npv1 = (TH1F*) f_QCD_13TeV_mediumBtag->Get("hist_QCD_mediumBtag_trimmed_npv1");

  TH1F * hist_QCD_mediumBtag_npv1_400 = (TH1F*) f_QCD_13TeV_mediumBtag->Get("hist_QCD_mediumBtag_npv1_400");
  TH1F * hist_QCD_filtered_mediumBtag_npv1_400 = (TH1F*) f_QCD_13TeV_mediumBtag->Get("hist_QCD_mediumBtag_filtered_npv1_400");
  TH1F * hist_QCD_pruned_mediumBtag_npv1_400 = (TH1F*) f_QCD_13TeV_mediumBtag->Get("hist_QCD_mediumBtag_pruned_npv1_400");
  TH1F * hist_QCD_trimmed_mediumBtag_npv1_400 = (TH1F*) f_QCD_13TeV_mediumBtag->Get("hist_QCD_mediumBtag_trimmed_npv1_400");

  //numerator histograms
  TH1F * hist_QCD_noBtag_tagJet1pt = (TH1F*) f_QCD_13TeV_noBtag->Get("hist_QCD_noBtag_tagJet1pt");
  TH1F * hist_QCD_filtered_noBtag_tagJet1pt = (TH1F*) f_QCD_13TeV_noBtag->Get("hist_QCD_noBtag_filtered_tagJet1pt");
  TH1F * hist_QCD_pruned_noBtag_tagJet1pt = (TH1F*) f_QCD_13TeV_noBtag->Get("hist_QCD_noBtag_pruned_tagJet1pt");
  TH1F * hist_QCD_trimmed_noBtag_tagJet1pt = (TH1F*) f_QCD_13TeV_noBtag->Get("hist_QCD_noBtag_trimmed_tagJet1pt");

  TH1F * hist_QCD_noBtag_tagNpv1 = (TH1F*) f_QCD_13TeV_noBtag->Get("hist_QCD_noBtag_tagNpv1");
  TH1F * hist_QCD_filtered_noBtag_tagNpv1 = (TH1F*) f_QCD_13TeV_noBtag->Get("hist_QCD_noBtag_filtered_tagNpv1");
  TH1F * hist_QCD_pruned_noBtag_tagNpv1 = (TH1F*) f_QCD_13TeV_noBtag->Get("hist_QCD_noBtag_pruned_tagNpv1");
  TH1F * hist_QCD_trimmed_noBtag_tagNpv1 = (TH1F*) f_QCD_13TeV_noBtag->Get("hist_QCD_noBtag_trimmed_tagNpv1");

  TH1F * hist_QCD_noBtag_tagNpv1_400 = (TH1F*) f_QCD_13TeV_noBtag->Get("hist_QCD_noBtag_tagNpv1_400");
  TH1F * hist_QCD_filtered_noBtag_tagNpv1_400 = (TH1F*) f_QCD_13TeV_noBtag->Get("hist_QCD_noBtag_filtered_tagNpv1_400");
  TH1F * hist_QCD_pruned_noBtag_tagNpv1_400 = (TH1F*) f_QCD_13TeV_noBtag->Get("hist_QCD_noBtag_pruned_tagNpv1_400");
  TH1F * hist_QCD_trimmed_noBtag_tagNpv1_400 = (TH1F*) f_QCD_13TeV_noBtag->Get("hist_QCD_noBtag_trimmed_tagNpv1_400");

  TH1F * hist_QCD_looseBtag_tagJet1pt = (TH1F*) f_QCD_13TeV_looseBtag->Get("hist_QCD_looseBtag_tagJet1pt");
  TH1F * hist_QCD_filtered_looseBtag_tagJet1pt = (TH1F*) f_QCD_13TeV_looseBtag->Get("hist_QCD_looseBtag_filtered_tagJet1pt");
  TH1F * hist_QCD_pruned_looseBtag_tagJet1pt = (TH1F*) f_QCD_13TeV_looseBtag->Get("hist_QCD_looseBtag_pruned_tagJet1pt");
  TH1F * hist_QCD_trimmed_looseBtag_tagJet1pt = (TH1F*) f_QCD_13TeV_looseBtag->Get("hist_QCD_looseBtag_trimmed_tagJet1pt");

  TH1F * hist_QCD_looseBtag_tagNpv1 = (TH1F*) f_QCD_13TeV_looseBtag->Get("hist_QCD_looseBtag_tagNpv1");
  TH1F * hist_QCD_filtered_looseBtag_tagNpv1 = (TH1F*) f_QCD_13TeV_looseBtag->Get("hist_QCD_looseBtag_filtered_tagNpv1");
  TH1F * hist_QCD_pruned_looseBtag_tagNpv1 = (TH1F*) f_QCD_13TeV_looseBtag->Get("hist_QCD_looseBtag_pruned_tagNpv1");
  TH1F * hist_QCD_trimmed_looseBtag_tagNpv1 = (TH1F*) f_QCD_13TeV_looseBtag->Get("hist_QCD_looseBtag_trimmed_tagNpv1");

  TH1F * hist_QCD_looseBtag_tagNpv1_400 = (TH1F*) f_QCD_13TeV_looseBtag->Get("hist_QCD_looseBtag_tagNpv1_400");
  TH1F * hist_QCD_filtered_looseBtag_tagNpv1_400 = (TH1F*) f_QCD_13TeV_looseBtag->Get("hist_QCD_looseBtag_filtered_tagNpv1_400");
  TH1F * hist_QCD_pruned_looseBtag_tagNpv1_400 = (TH1F*) f_QCD_13TeV_looseBtag->Get("hist_QCD_looseBtag_pruned_tagNpv1_400");
  TH1F * hist_QCD_trimmed_looseBtag_tagNpv1_400 = (TH1F*) f_QCD_13TeV_looseBtag->Get("hist_QCD_looseBtag_trimmed_tagNpv1_400");

  TH1F * hist_QCD_mediumBtag_tagJet1pt = (TH1F*) f_QCD_13TeV_mediumBtag->Get("hist_QCD_mediumBtag_tagJet1pt");
  TH1F * hist_QCD_filtered_mediumBtag_tagJet1pt = (TH1F*) f_QCD_13TeV_mediumBtag->Get("hist_QCD_mediumBtag_filtered_tagJet1pt");
  TH1F * hist_QCD_pruned_mediumBtag_tagJet1pt = (TH1F*) f_QCD_13TeV_mediumBtag->Get("hist_QCD_mediumBtag_pruned_tagJet1pt");
  TH1F * hist_QCD_trimmed_mediumBtag_tagJet1pt = (TH1F*) f_QCD_13TeV_mediumBtag->Get("hist_QCD_mediumBtag_trimmed_tagJet1pt");

  TH1F * hist_QCD_mediumBtag_tagNpv1 = (TH1F*) f_QCD_13TeV_mediumBtag->Get("hist_QCD_mediumBtag_tagNpv1");
  TH1F * hist_QCD_filtered_mediumBtag_tagNpv1 = (TH1F*) f_QCD_13TeV_mediumBtag->Get("hist_QCD_mediumBtag_filtered_tagNpv1");
  TH1F * hist_QCD_pruned_mediumBtag_tagNpv1 = (TH1F*) f_QCD_13TeV_mediumBtag->Get("hist_QCD_mediumBtag_pruned_tagNpv1");
  TH1F * hist_QCD_trimmed_mediumBtag_tagNpv1 = (TH1F*) f_QCD_13TeV_mediumBtag->Get("hist_QCD_mediumBtag_trimmed_tagNpv1");

  TH1F * hist_QCD_mediumBtag_tagNpv1_400 = (TH1F*) f_QCD_13TeV_mediumBtag->Get("hist_QCD_mediumBtag_tagNpv1_400");
  TH1F * hist_QCD_filtered_mediumBtag_tagNpv1_400 = (TH1F*) f_QCD_13TeV_mediumBtag->Get("hist_QCD_mediumBtag_filtered_tagNpv1_400");
  TH1F * hist_QCD_pruned_mediumBtag_tagNpv1_400 = (TH1F*) f_QCD_13TeV_mediumBtag->Get("hist_QCD_mediumBtag_pruned_tagNpv1_400");
  TH1F * hist_QCD_trimmed_mediumBtag_tagNpv1_400 = (TH1F*) f_QCD_13TeV_mediumBtag->Get("hist_QCD_mediumBtag_trimmed_tagNpv1_400");
  
  //2D Z Prime/QCD histograms
  TH2D *h_ZPrime_QCD_nobtag_topTagEff = new TH2D("h_ZPrime_QCD_nobtag_topTagEff","QCD Background Rejection vs Z Prime Efficiency;Z Prime Efficiency;QCD Rejection",100,0,0.4,100,0.99,1);
  TH2D *h_ZPrime_QCD_loosebtag_topTagEff = new TH2D("h_ZPrime_QCD_loosebtag_topTagEff","QCD Background Rejection vs Z Prime Efficiency;Z Prime Efficiency;QCD Rejection",100,0,0.4,100,0.99,1);
  TH2D *h_ZPrime_QCD_mediumbtag_topTagEff = new TH2D("h_ZPrime_QCD_mediumbtag_topTagEff","QCD Background Rejection vs Z Prime Efficiency;Z Prime Efficiency;QCD Rejection",100,0,0.4,100,0.99,1);

  TH2D *h_ZPrime_QCD_ungroomed_topTagEff = new TH2D("h_ZPrime_QCD_ungroomed_topTagEff","QCD Background Rejection vs Z Prime Efficiency;Z Prime Efficiency;QCD Rejection",100,0,0.5,100,0.95,1);
  TH2D *h_ZPrime_QCD_filtered_topTagEff = new TH2D("h_ZPrime_QCD_filtered_topTagEff","QCD Background Rejection vs Z Prime Efficiency;Z Prime Efficiency;QCD Rejection",100,0,0.5,100,0.95,1);
  TH2D *h_ZPrime_QCD_pruned_topTagEff = new TH2D("h_ZPrime_QCD_pruned_topTagEff","QCD Background Rejection vs Z Prime Efficiency;Z Prime Efficiency;QCD Rejection",100,0,0.5,100,0.95,1);
  TH2D *h_ZPrime_QCD_trimmed_topTagEff = new TH2D("h_ZPrime_QCD_trimmed_topTagEff","QCD Background Rejection vs Z Prime Efficiency;Z Prime Efficiency;QCD Rejection",100,0,0.5,100,0.95,1);
  /*
  //QCD pt 15 to 3000 Weighted Histograms
  //efficiency histograms
  TH1F * hist_QCD_FLAT_weighted_noBtag_topTagEffPt = (TH1F*) f_QCD_FLAT_weighted_13TeV_noBtag->Get("hist_QCD_FLAT_weighted_noBtag_topTagEffPt");
  TH1F * hist_QCD_FLAT_weighted_filtered_noBtag_topTagEffPt = (TH1F*) f_QCD_FLAT_weighted_13TeV_noBtag->Get("hist_QCD_FLAT_weighted_noBtag_filtered_topTagEffPt");
  TH1F * hist_QCD_FLAT_weighted_pruned_noBtag_topTagEffPt = (TH1F*) f_QCD_FLAT_weighted_13TeV_noBtag->Get("hist_QCD_FLAT_weighted_noBtag_pruned_topTagEffPt");
  TH1F * hist_QCD_FLAT_weighted_trimmed_noBtag_topTagEffPt = (TH1F*) f_QCD_FLAT_weighted_13TeV_noBtag->Get("hist_QCD_FLAT_weighted_noBtag_trimmed_topTagEffPt");

  TH1F * hist_QCD_FLAT_weighted_noBtag_topTagEffNpv = (TH1F*) f_QCD_FLAT_weighted_13TeV_noBtag->Get("hist_QCD_FLAT_weighted_noBtag_topTagEffNpv");
  TH1F * hist_QCD_FLAT_weighted_filtered_noBtag_topTagEffNpv = (TH1F*) f_QCD_FLAT_weighted_13TeV_noBtag->Get("hist_QCD_FLAT_weighted_noBtag_filtered_topTagEffNpv");
  TH1F * hist_QCD_FLAT_weighted_pruned_noBtag_topTagEffNpv = (TH1F*) f_QCD_FLAT_weighted_13TeV_noBtag->Get("hist_QCD_FLAT_weighted_noBtag_pruned_topTagEffNpv");
  TH1F * hist_QCD_FLAT_weighted_trimmed_noBtag_topTagEffNpv = (TH1F*) f_QCD_FLAT_weighted_13TeV_noBtag->Get("hist_QCD_FLAT_weighted_noBtag_trimmed_topTagEffNpv");

  TH1F * hist_QCD_FLAT_weighted_noBtag_topTagEffNpv_400 = (TH1F*) f_QCD_FLAT_weighted_13TeV_noBtag->Get("hist_QCD_FLAT_weighted_noBtag_topTagEffNpv_400");
  TH1F * hist_QCD_FLAT_weighted_filtered_noBtag_topTagEffNpv_400 = (TH1F*) f_QCD_FLAT_weighted_13TeV_noBtag->Get("hist_QCD_FLAT_weighted_noBtag_filtered_topTagEffNpv_400");
  TH1F * hist_QCD_FLAT_weighted_pruned_noBtag_topTagEffNpv_400 = (TH1F*) f_QCD_FLAT_weighted_13TeV_noBtag->Get("hist_QCD_FLAT_weighted_noBtag_pruned_topTagEffNpv_400");
  TH1F * hist_QCD_FLAT_weighted_trimmed_noBtag_topTagEffNpv_400 = (TH1F*) f_QCD_FLAT_weighted_13TeV_noBtag->Get("hist_QCD_FLAT_weighted_noBtag_trimmed_topTagEffNpv_400");

  TH1F * hist_QCD_FLAT_weighted_looseBtag_topTagEffPt = (TH1F*) f_QCD_FLAT_weighted_13TeV_looseBtag->Get("hist_QCD_FLAT_weighted_looseBtag_topTagEffPt");
  TH1F * hist_QCD_FLAT_weighted_filtered_looseBtag_topTagEffPt = (TH1F*) f_QCD_FLAT_weighted_13TeV_looseBtag->Get("hist_QCD_FLAT_weighted_looseBtag_filtered_topTagEffPt");
  TH1F * hist_QCD_FLAT_weighted_pruned_looseBtag_topTagEffPt = (TH1F*) f_QCD_FLAT_weighted_13TeV_looseBtag->Get("hist_QCD_FLAT_weighted_looseBtag_pruned_topTagEffPt");
  TH1F * hist_QCD_FLAT_weighted_trimmed_looseBtag_topTagEffPt = (TH1F*) f_QCD_FLAT_weighted_13TeV_looseBtag->Get("hist_QCD_FLAT_weighted_looseBtag_trimmed_topTagEffPt");

  TH1F * hist_QCD_FLAT_weighted_looseBtag_topTagEffNpv = (TH1F*) f_QCD_FLAT_weighted_13TeV_looseBtag->Get("hist_QCD_FLAT_weighted_looseBtag_topTagEffNpv");
  TH1F * hist_QCD_FLAT_weighted_filtered_looseBtag_topTagEffNpv = (TH1F*) f_QCD_FLAT_weighted_13TeV_looseBtag->Get("hist_QCD_FLAT_weighted_looseBtag_filtered_topTagEffNpv");
  TH1F * hist_QCD_FLAT_weighted_pruned_looseBtag_topTagEffNpv = (TH1F*) f_QCD_FLAT_weighted_13TeV_looseBtag->Get("hist_QCD_FLAT_weighted_looseBtag_pruned_topTagEffNpv");
  TH1F * hist_QCD_FLAT_weighted_trimmed_looseBtag_topTagEffNpv = (TH1F*) f_QCD_FLAT_weighted_13TeV_looseBtag->Get("hist_QCD_FLAT_weighted_looseBtag_trimmed_topTagEffNpv");

  TH1F * hist_QCD_FLAT_weighted_looseBtag_topTagEffNpv_400 = (TH1F*) f_QCD_FLAT_weighted_13TeV_looseBtag->Get("hist_QCD_FLAT_weighted_looseBtag_topTagEffNpv_400");
  TH1F * hist_QCD_FLAT_weighted_filtered_looseBtag_topTagEffNpv_400 = (TH1F*) f_QCD_FLAT_weighted_13TeV_looseBtag->Get("hist_QCD_FLAT_weighted_looseBtag_filtered_topTagEffNpv_400");
  TH1F * hist_QCD_FLAT_weighted_pruned_looseBtag_topTagEffNpv_400 = (TH1F*) f_QCD_FLAT_weighted_13TeV_looseBtag->Get("hist_QCD_FLAT_weighted_looseBtag_pruned_topTagEffNpv_400");
  TH1F * hist_QCD_FLAT_weighted_trimmed_looseBtag_topTagEffNpv_400 = (TH1F*) f_QCD_FLAT_weighted_13TeV_looseBtag->Get("hist_QCD_FLAT_weighted_looseBtag_trimmed_topTagEffNpv_400");

  TH1F * hist_QCD_FLAT_weighted_mediumBtag_topTagEffPt = (TH1F*) f_QCD_FLAT_weighted_13TeV_mediumBtag->Get("hist_QCD_FLAT_weighted_mediumBtag_topTagEffPt");
  TH1F * hist_QCD_FLAT_weighted_filtered_mediumBtag_topTagEffPt = (TH1F*) f_QCD_FLAT_weighted_13TeV_mediumBtag->Get("hist_QCD_FLAT_weighted_mediumBtag_filtered_topTagEffPt");
  TH1F * hist_QCD_FLAT_weighted_pruned_mediumBtag_topTagEffPt = (TH1F*) f_QCD_FLAT_weighted_13TeV_mediumBtag->Get("hist_QCD_FLAT_weighted_mediumBtag_pruned_topTagEffPt");
  TH1F * hist_QCD_FLAT_weighted_trimmed_mediumBtag_topTagEffPt = (TH1F*) f_QCD_FLAT_weighted_13TeV_mediumBtag->Get("hist_QCD_FLAT_weighted_mediumBtag_trimmed_topTagEffPt");

  TH1F * hist_QCD_FLAT_weighted_mediumBtag_topTagEffNpv = (TH1F*) f_QCD_FLAT_weighted_13TeV_mediumBtag->Get("hist_QCD_FLAT_weighted_mediumBtag_topTagEffNpv");
  TH1F * hist_QCD_FLAT_weighted_filtered_mediumBtag_topTagEffNpv = (TH1F*) f_QCD_FLAT_weighted_13TeV_mediumBtag->Get("hist_QCD_FLAT_weighted_mediumBtag_filtered_topTagEffNpv");
  TH1F * hist_QCD_FLAT_weighted_pruned_mediumBtag_topTagEffNpv = (TH1F*) f_QCD_FLAT_weighted_13TeV_mediumBtag->Get("hist_QCD_FLAT_weighted_mediumBtag_pruned_topTagEffNpv");
  TH1F * hist_QCD_FLAT_weighted_trimmed_mediumBtag_topTagEffNpv = (TH1F*) f_QCD_FLAT_weighted_13TeV_mediumBtag->Get("hist_QCD_FLAT_weighted_mediumBtag_trimmed_topTagEffNpv");

  TH1F * hist_QCD_FLAT_weighted_mediumBtag_topTagEffNpv_400 = (TH1F*) f_QCD_FLAT_weighted_13TeV_mediumBtag->Get("hist_QCD_FLAT_weighted_mediumBtag_topTagEffNpv_400");
  TH1F * hist_QCD_FLAT_weighted_filtered_mediumBtag_topTagEffNpv_400 = (TH1F*) f_QCD_FLAT_weighted_13TeV_mediumBtag->Get("hist_QCD_FLAT_weighted_mediumBtag_filtered_topTagEffNpv_400");
  TH1F * hist_QCD_FLAT_weighted_pruned_mediumBtag_topTagEffNpv_400 = (TH1F*) f_QCD_FLAT_weighted_13TeV_mediumBtag->Get("hist_QCD_FLAT_weighted_mediumBtag_pruned_topTagEffNpv_400");
  TH1F * hist_QCD_FLAT_weighted_trimmed_mediumBtag_topTagEffNpv_400 = (TH1F*) f_QCD_FLAT_weighted_13TeV_mediumBtag->Get("hist_QCD_FLAT_weighted_mediumBtag_trimmed_topTagEffNpv_400");

  //denominator histograms
  TH1F * hist_QCD_FLAT_weighted_noBtag_jet1pt = (TH1F*) f_QCD_FLAT_weighted_13TeV_noBtag->Get("hist_QCD_FLAT_weighted_noBtag_jet1pt");
  TH1F * hist_QCD_FLAT_weighted_filtered_noBtag_jet1pt = (TH1F*) f_QCD_FLAT_weighted_13TeV_noBtag->Get("hist_QCD_FLAT_weighted_noBtag_filtered_jet1pt");
  TH1F * hist_QCD_FLAT_weighted_pruned_noBtag_jet1pt = (TH1F*) f_QCD_FLAT_weighted_13TeV_noBtag->Get("hist_QCD_FLAT_weighted_noBtag_pruned_jet1pt");
  TH1F * hist_QCD_FLAT_weighted_trimmed_noBtag_jet1pt = (TH1F*) f_QCD_FLAT_weighted_13TeV_noBtag->Get("hist_QCD_FLAT_weighted_noBtag_trimmed_jet1pt");

  TH1F * hist_QCD_FLAT_weighted_noBtag_npv1 = (TH1F*) f_QCD_FLAT_weighted_13TeV_noBtag->Get("hist_QCD_FLAT_weighted_noBtag_npv1");
  TH1F * hist_QCD_FLAT_weighted_filtered_noBtag_npv1 = (TH1F*) f_QCD_FLAT_weighted_13TeV_noBtag->Get("hist_QCD_FLAT_weighted_noBtag_filtered_npv1");
  TH1F * hist_QCD_FLAT_weighted_pruned_noBtag_npv1 = (TH1F*) f_QCD_FLAT_weighted_13TeV_noBtag->Get("hist_QCD_FLAT_weighted_noBtag_pruned_npv1");
  TH1F * hist_QCD_FLAT_weighted_trimmed_noBtag_npv1 = (TH1F*) f_QCD_FLAT_weighted_13TeV_noBtag->Get("hist_QCD_FLAT_weighted_noBtag_trimmed_npv1");

  TH1F * hist_QCD_FLAT_weighted_noBtag_npv1_400 = (TH1F*) f_QCD_FLAT_weighted_13TeV_noBtag->Get("hist_QCD_FLAT_weighted_noBtag_npv1_400");
  TH1F * hist_QCD_FLAT_weighted_filtered_noBtag_npv1_400 = (TH1F*) f_QCD_FLAT_weighted_13TeV_noBtag->Get("hist_QCD_FLAT_weighted_noBtag_filtered_npv1_400");
  TH1F * hist_QCD_FLAT_weighted_pruned_noBtag_npv1_400 = (TH1F*) f_QCD_FLAT_weighted_13TeV_noBtag->Get("hist_QCD_FLAT_weighted_noBtag_pruned_npv1_400");
  TH1F * hist_QCD_FLAT_weighted_trimmed_noBtag_npv1_400 = (TH1F*) f_QCD_FLAT_weighted_13TeV_noBtag->Get("hist_QCD_FLAT_weighted_noBtag_trimmed_npv1_400");

  TH1F * hist_QCD_FLAT_weighted_looseBtag_jet1pt = (TH1F*) f_QCD_FLAT_weighted_13TeV_looseBtag->Get("hist_QCD_FLAT_weighted_looseBtag_jet1pt");
  TH1F * hist_QCD_FLAT_weighted_filtered_looseBtag_jet1pt = (TH1F*) f_QCD_FLAT_weighted_13TeV_looseBtag->Get("hist_QCD_FLAT_weighted_looseBtag_filtered_jet1pt");
  TH1F * hist_QCD_FLAT_weighted_pruned_looseBtag_jet1pt = (TH1F*) f_QCD_FLAT_weighted_13TeV_looseBtag->Get("hist_QCD_FLAT_weighted_looseBtag_pruned_jet1pt");
  TH1F * hist_QCD_FLAT_weighted_trimmed_looseBtag_jet1pt = (TH1F*) f_QCD_FLAT_weighted_13TeV_looseBtag->Get("hist_QCD_FLAT_weighted_looseBtag_trimmed_jet1pt");

  TH1F * hist_QCD_FLAT_weighted_looseBtag_npv1 = (TH1F*) f_QCD_FLAT_weighted_13TeV_looseBtag->Get("hist_QCD_FLAT_weighted_looseBtag_npv1");
  TH1F * hist_QCD_FLAT_weighted_filtered_looseBtag_npv1 = (TH1F*) f_QCD_FLAT_weighted_13TeV_looseBtag->Get("hist_QCD_FLAT_weighted_looseBtag_filtered_npv1");
  TH1F * hist_QCD_FLAT_weighted_pruned_looseBtag_npv1 = (TH1F*) f_QCD_FLAT_weighted_13TeV_looseBtag->Get("hist_QCD_FLAT_weighted_looseBtag_pruned_npv1");
  TH1F * hist_QCD_FLAT_weighted_trimmed_looseBtag_npv1 = (TH1F*) f_QCD_FLAT_weighted_13TeV_looseBtag->Get("hist_QCD_FLAT_weighted_looseBtag_trimmed_npv1");

  TH1F * hist_QCD_FLAT_weighted_looseBtag_npv1_400 = (TH1F*) f_QCD_FLAT_weighted_13TeV_looseBtag->Get("hist_QCD_FLAT_weighted_looseBtag_npv1_400");
  TH1F * hist_QCD_FLAT_weighted_filtered_looseBtag_npv1_400 = (TH1F*) f_QCD_FLAT_weighted_13TeV_looseBtag->Get("hist_QCD_FLAT_weighted_looseBtag_filtered_npv1_400");
  TH1F * hist_QCD_FLAT_weighted_pruned_looseBtag_npv1_400 = (TH1F*) f_QCD_FLAT_weighted_13TeV_looseBtag->Get("hist_QCD_FLAT_weighted_looseBtag_pruned_npv1_400");
  TH1F * hist_QCD_FLAT_weighted_trimmed_looseBtag_npv1_400 = (TH1F*) f_QCD_FLAT_weighted_13TeV_looseBtag->Get("hist_QCD_FLAT_weighted_looseBtag_trimmed_npv1_400");

  TH1F * hist_QCD_FLAT_weighted_mediumBtag_jet1pt = (TH1F*) f_QCD_FLAT_weighted_13TeV_mediumBtag->Get("hist_QCD_FLAT_weighted_mediumBtag_jet1pt");
  TH1F * hist_QCD_FLAT_weighted_filtered_mediumBtag_jet1pt = (TH1F*) f_QCD_FLAT_weighted_13TeV_mediumBtag->Get("hist_QCD_FLAT_weighted_mediumBtag_filtered_jet1pt");
  TH1F * hist_QCD_FLAT_weighted_pruned_mediumBtag_jet1pt = (TH1F*) f_QCD_FLAT_weighted_13TeV_mediumBtag->Get("hist_QCD_FLAT_weighted_mediumBtag_pruned_jet1pt");
  TH1F * hist_QCD_FLAT_weighted_trimmed_mediumBtag_jet1pt = (TH1F*) f_QCD_FLAT_weighted_13TeV_mediumBtag->Get("hist_QCD_FLAT_weighted_mediumBtag_trimmed_jet1pt");

  TH1F * hist_QCD_FLAT_weighted_mediumBtag_npv1 = (TH1F*) f_QCD_FLAT_weighted_13TeV_mediumBtag->Get("hist_QCD_FLAT_weighted_mediumBtag_npv1");
  TH1F * hist_QCD_FLAT_weighted_filtered_mediumBtag_npv1 = (TH1F*) f_QCD_FLAT_weighted_13TeV_mediumBtag->Get("hist_QCD_FLAT_weighted_mediumBtag_filtered_npv1");
  TH1F * hist_QCD_FLAT_weighted_pruned_mediumBtag_npv1 = (TH1F*) f_QCD_FLAT_weighted_13TeV_mediumBtag->Get("hist_QCD_FLAT_weighted_mediumBtag_pruned_npv1");
  TH1F * hist_QCD_FLAT_weighted_trimmed_mediumBtag_npv1 = (TH1F*) f_QCD_FLAT_weighted_13TeV_mediumBtag->Get("hist_QCD_FLAT_weighted_mediumBtag_trimmed_npv1");

  TH1F * hist_QCD_FLAT_weighted_mediumBtag_npv1_400 = (TH1F*) f_QCD_FLAT_weighted_13TeV_mediumBtag->Get("hist_QCD_FLAT_weighted_mediumBtag_npv1_400");
  TH1F * hist_QCD_FLAT_weighted_filtered_mediumBtag_npv1_400 = (TH1F*) f_QCD_FLAT_weighted_13TeV_mediumBtag->Get("hist_QCD_FLAT_weighted_mediumBtag_filtered_npv1_400");
  TH1F * hist_QCD_FLAT_weighted_pruned_mediumBtag_npv1_400 = (TH1F*) f_QCD_FLAT_weighted_13TeV_mediumBtag->Get("hist_QCD_FLAT_weighted_mediumBtag_pruned_npv1_400");
  TH1F * hist_QCD_FLAT_weighted_trimmed_mediumBtag_npv1_400 = (TH1F*) f_QCD_FLAT_weighted_13TeV_mediumBtag->Get("hist_QCD_FLAT_weighted_mediumBtag_trimmed_npv1_400");

  //numerator histograms
  TH1F * hist_QCD_FLAT_weighted_noBtag_tagJet1pt = (TH1F*) f_QCD_FLAT_weighted_13TeV_noBtag->Get("hist_QCD_FLAT_weighted_noBtag_tagJet1pt");
  TH1F * hist_QCD_FLAT_weighted_filtered_noBtag_tagJet1pt = (TH1F*) f_QCD_FLAT_weighted_13TeV_noBtag->Get("hist_QCD_FLAT_weighted_noBtag_filtered_tagJet1pt");
  TH1F * hist_QCD_FLAT_weighted_pruned_noBtag_tagJet1pt = (TH1F*) f_QCD_FLAT_weighted_13TeV_noBtag->Get("hist_QCD_FLAT_weighted_noBtag_pruned_tagJet1pt");
  TH1F * hist_QCD_FLAT_weighted_trimmed_noBtag_tagJet1pt = (TH1F*) f_QCD_FLAT_weighted_13TeV_noBtag->Get("hist_QCD_FLAT_weighted_noBtag_trimmed_tagJet1pt");

  TH1F * hist_QCD_FLAT_weighted_noBtag_tagNpv1 = (TH1F*) f_QCD_FLAT_weighted_13TeV_noBtag->Get("hist_QCD_FLAT_weighted_noBtag_tagNpv1");
  TH1F * hist_QCD_FLAT_weighted_filtered_noBtag_tagNpv1 = (TH1F*) f_QCD_FLAT_weighted_13TeV_noBtag->Get("hist_QCD_FLAT_weighted_noBtag_filtered_tagNpv1");
  TH1F * hist_QCD_FLAT_weighted_pruned_noBtag_tagNpv1 = (TH1F*) f_QCD_FLAT_weighted_13TeV_noBtag->Get("hist_QCD_FLAT_weighted_noBtag_pruned_tagNpv1");
  TH1F * hist_QCD_FLAT_weighted_trimmed_noBtag_tagNpv1 = (TH1F*) f_QCD_FLAT_weighted_13TeV_noBtag->Get("hist_QCD_FLAT_weighted_noBtag_trimmed_tagNpv1");

  TH1F * hist_QCD_FLAT_weighted_noBtag_tagNpv1_400 = (TH1F*) f_QCD_FLAT_weighted_13TeV_noBtag->Get("hist_QCD_FLAT_weighted_noBtag_tagNpv1_400");
  TH1F * hist_QCD_FLAT_weighted_filtered_noBtag_tagNpv1_400 = (TH1F*) f_QCD_FLAT_weighted_13TeV_noBtag->Get("hist_QCD_FLAT_weighted_noBtag_filtered_tagNpv1_400");
  TH1F * hist_QCD_FLAT_weighted_pruned_noBtag_tagNpv1_400 = (TH1F*) f_QCD_FLAT_weighted_13TeV_noBtag->Get("hist_QCD_FLAT_weighted_noBtag_pruned_tagNpv1_400");
  TH1F * hist_QCD_FLAT_weighted_trimmed_noBtag_tagNpv1_400 = (TH1F*) f_QCD_FLAT_weighted_13TeV_noBtag->Get("hist_QCD_FLAT_weighted_noBtag_trimmed_tagNpv1_400");

  TH1F * hist_QCD_FLAT_weighted_looseBtag_tagJet1pt = (TH1F*) f_QCD_FLAT_weighted_13TeV_looseBtag->Get("hist_QCD_FLAT_weighted_looseBtag_tagJet1pt");
  TH1F * hist_QCD_FLAT_weighted_filtered_looseBtag_tagJet1pt = (TH1F*) f_QCD_FLAT_weighted_13TeV_looseBtag->Get("hist_QCD_FLAT_weighted_looseBtag_filtered_tagJet1pt");
  TH1F * hist_QCD_FLAT_weighted_pruned_looseBtag_tagJet1pt = (TH1F*) f_QCD_FLAT_weighted_13TeV_looseBtag->Get("hist_QCD_FLAT_weighted_looseBtag_pruned_tagJet1pt");
  TH1F * hist_QCD_FLAT_weighted_trimmed_looseBtag_tagJet1pt = (TH1F*) f_QCD_FLAT_weighted_13TeV_looseBtag->Get("hist_QCD_FLAT_weighted_looseBtag_trimmed_tagJet1pt");

  TH1F * hist_QCD_FLAT_weighted_looseBtag_tagNpv1 = (TH1F*) f_QCD_FLAT_weighted_13TeV_looseBtag->Get("hist_QCD_FLAT_weighted_looseBtag_tagNpv1");
  TH1F * hist_QCD_FLAT_weighted_filtered_looseBtag_tagNpv1 = (TH1F*) f_QCD_FLAT_weighted_13TeV_looseBtag->Get("hist_QCD_FLAT_weighted_looseBtag_filtered_tagNpv1");
  TH1F * hist_QCD_FLAT_weighted_pruned_looseBtag_tagNpv1 = (TH1F*) f_QCD_FLAT_weighted_13TeV_looseBtag->Get("hist_QCD_FLAT_weighted_looseBtag_pruned_tagNpv1");
  TH1F * hist_QCD_FLAT_weighted_trimmed_looseBtag_tagNpv1 = (TH1F*) f_QCD_FLAT_weighted_13TeV_looseBtag->Get("hist_QCD_FLAT_weighted_looseBtag_trimmed_tagNpv1");

  TH1F * hist_QCD_FLAT_weighted_looseBtag_tagNpv1_400 = (TH1F*) f_QCD_FLAT_weighted_13TeV_looseBtag->Get("hist_QCD_FLAT_weighted_looseBtag_tagNpv1_400");
  TH1F * hist_QCD_FLAT_weighted_filtered_looseBtag_tagNpv1_400 = (TH1F*) f_QCD_FLAT_weighted_13TeV_looseBtag->Get("hist_QCD_FLAT_weighted_looseBtag_filtered_tagNpv1_400");
  TH1F * hist_QCD_FLAT_weighted_pruned_looseBtag_tagNpv1_400 = (TH1F*) f_QCD_FLAT_weighted_13TeV_looseBtag->Get("hist_QCD_FLAT_weighted_looseBtag_pruned_tagNpv1_400");
  TH1F * hist_QCD_FLAT_weighted_trimmed_looseBtag_tagNpv1_400 = (TH1F*) f_QCD_FLAT_weighted_13TeV_looseBtag->Get("hist_QCD_FLAT_weighted_looseBtag_trimmed_tagNpv1_400");

  TH1F * hist_QCD_FLAT_weighted_mediumBtag_tagJet1pt = (TH1F*) f_QCD_FLAT_weighted_13TeV_mediumBtag->Get("hist_QCD_FLAT_weighted_mediumBtag_tagJet1pt");
  TH1F * hist_QCD_FLAT_weighted_filtered_mediumBtag_tagJet1pt = (TH1F*) f_QCD_FLAT_weighted_13TeV_mediumBtag->Get("hist_QCD_FLAT_weighted_mediumBtag_filtered_tagJet1pt");
  TH1F * hist_QCD_FLAT_weighted_pruned_mediumBtag_tagJet1pt = (TH1F*) f_QCD_FLAT_weighted_13TeV_mediumBtag->Get("hist_QCD_FLAT_weighted_mediumBtag_pruned_tagJet1pt");
  TH1F * hist_QCD_FLAT_weighted_trimmed_mediumBtag_tagJet1pt = (TH1F*) f_QCD_FLAT_weighted_13TeV_mediumBtag->Get("hist_QCD_FLAT_weighted_mediumBtag_trimmed_tagJet1pt");

  TH1F * hist_QCD_FLAT_weighted_mediumBtag_tagNpv1 = (TH1F*) f_QCD_FLAT_weighted_13TeV_mediumBtag->Get("hist_QCD_FLAT_weighted_mediumBtag_tagNpv1");
  TH1F * hist_QCD_FLAT_weighted_filtered_mediumBtag_tagNpv1 = (TH1F*) f_QCD_FLAT_weighted_13TeV_mediumBtag->Get("hist_QCD_FLAT_weighted_mediumBtag_filtered_tagNpv1");
  TH1F * hist_QCD_FLAT_weighted_pruned_mediumBtag_tagNpv1 = (TH1F*) f_QCD_FLAT_weighted_13TeV_mediumBtag->Get("hist_QCD_FLAT_weighted_mediumBtag_pruned_tagNpv1");
  TH1F * hist_QCD_FLAT_weighted_trimmed_mediumBtag_tagNpv1 = (TH1F*) f_QCD_FLAT_weighted_13TeV_mediumBtag->Get("hist_QCD_FLAT_weighted_mediumBtag_trimmed_tagNpv1");

  TH1F * hist_QCD_FLAT_weighted_mediumBtag_tagNpv1_400 = (TH1F*) f_QCD_FLAT_weighted_13TeV_mediumBtag->Get("hist_QCD_FLAT_weighted_mediumBtag_tagNpv1_400");
  TH1F * hist_QCD_FLAT_weighted_filtered_mediumBtag_tagNpv1_400 = (TH1F*) f_QCD_FLAT_weighted_13TeV_mediumBtag->Get("hist_QCD_FLAT_weighted_mediumBtag_filtered_tagNpv1_400");
  TH1F * hist_QCD_FLAT_weighted_pruned_mediumBtag_tagNpv1_400 = (TH1F*) f_QCD_FLAT_weighted_13TeV_mediumBtag->Get("hist_QCD_FLAT_weighted_mediumBtag_pruned_tagNpv1_400");
  TH1F * hist_QCD_FLAT_weighted_trimmed_mediumBtag_tagNpv1_400 = (TH1F*) f_QCD_FLAT_weighted_13TeV_mediumBtag->Get("hist_QCD_FLAT_weighted_mediumBtag_trimmed_tagNpv1_400");

  //2D Z Prime/QCD histograms
  TH2D *h_ZPrime_QCD_FLAT_weighted_nobtag_topTagEff = new TH2D("h_ZPrime_QCD_FLAT_weighted_nobtag_topTagEff","QCD Background Rejection vs Z Prime Efficiency (Pt > 400 GeV);Z Prime Efficiency;QCD Rejection",100,0,0.5,100,0.95,1);
  TH2D *h_ZPrime_QCD_FLAT_weighted_loosebtag_topTagEff = new TH2D("h_ZPrime_QCD_FLAT_weighted_loosebtag_topTagEff","QCD Background Rejection vs Z Prime Efficiency (Pt > 400 GeV);Z Prime Efficiency;QCD Rejection",100,0,0.5,100,0.95,1);
  TH2D *h_ZPrime_QCD_FLAT_weighted_mediumbtag_topTagEff = new TH2D("h_ZPrime_QCD_FLAT_weighted_mediumbtag_topTagEff","QCD Background Rejection vs Z Prime Efficiency (Pt > 400 GeV);Z Prime Efficiency;QCD Rejection",100,0,0.5,100,0.95,1);

  TH2D *h_ZPrime_QCD_FLAT_weighted_ungroomed_topTagEff = new TH2D("h_ZPrime_QCD_FLAT_weighted_ungroomed_topTagEff","QCD Background Rejection vs Z Prime Efficiency (Pt > 400 GeV);Z Prime Efficiency;QCD Rejection",100,0,0.7,100,0.96,1);
  TH2D *h_ZPrime_QCD_FLAT_weighted_filtered_topTagEff = new TH2D("h_ZPrime_QCD_FLAT_weighted_filtered_topTagEff","QCD Background Rejection vs Z Prime Efficiency (Pt > 400 GeV);Z Prime Efficiency;QCD Rejection",100,0,0.7,100,0.96,1);
  TH2D *h_ZPrime_QCD_FLAT_weighted_pruned_topTagEff = new TH2D("h_ZPrime_QCD_FLAT_weighted_pruned_topTagEff","QCD Background Rejection vs Z Prime Efficiency (Pt > 400 GeV);Z Prime Efficiency;QCD Rejection",100,0,0.7,100,0.96,1);
  TH2D *h_ZPrime_QCD_FLAT_weighted_trimmed_topTagEff = new TH2D("h_ZPrime_QCD_FLAT_weighted_trimmed_topTagEff","QCD Background Rejection vs Z Prime Efficiency (Pt > 400 GeV);Z Prime Efficiency;QCD Rejection",100,0,0.7,100,0.96,1);

  //QCD pt 15 to 3000 Unweighted Histograms
  //efficiency histograms
  TH1F * hist_QCD_FLAT_noBtag_topTagEffPt = (TH1F*) f_QCD_FLAT_13TeV_noBtag->Get("hist_QCD_FLAT_noBtag_topTagEffPt");
  TH1F * hist_QCD_FLAT_filtered_noBtag_topTagEffPt = (TH1F*) f_QCD_FLAT_13TeV_noBtag->Get("hist_QCD_FLAT_noBtag_filtered_topTagEffPt");
  TH1F * hist_QCD_FLAT_pruned_noBtag_topTagEffPt = (TH1F*) f_QCD_FLAT_13TeV_noBtag->Get("hist_QCD_FLAT_noBtag_pruned_topTagEffPt");
  TH1F * hist_QCD_FLAT_trimmed_noBtag_topTagEffPt = (TH1F*) f_QCD_FLAT_13TeV_noBtag->Get("hist_QCD_FLAT_noBtag_trimmed_topTagEffPt");

  TH1F * hist_QCD_FLAT_noBtag_topTagEffNpv = (TH1F*) f_QCD_FLAT_13TeV_noBtag->Get("hist_QCD_FLAT_noBtag_topTagEffNpv");
  TH1F * hist_QCD_FLAT_filtered_noBtag_topTagEffNpv = (TH1F*) f_QCD_FLAT_13TeV_noBtag->Get("hist_QCD_FLAT_noBtag_filtered_topTagEffNpv");
  TH1F * hist_QCD_FLAT_pruned_noBtag_topTagEffNpv = (TH1F*) f_QCD_FLAT_13TeV_noBtag->Get("hist_QCD_FLAT_noBtag_pruned_topTagEffNpv");
  TH1F * hist_QCD_FLAT_trimmed_noBtag_topTagEffNpv = (TH1F*) f_QCD_FLAT_13TeV_noBtag->Get("hist_QCD_FLAT_noBtag_trimmed_topTagEffNpv");

  TH1F * hist_QCD_FLAT_noBtag_topTagEffNpv_400 = (TH1F*) f_QCD_FLAT_13TeV_noBtag->Get("hist_QCD_FLAT_noBtag_topTagEffNpv_400");
  TH1F * hist_QCD_FLAT_filtered_noBtag_topTagEffNpv_400 = (TH1F*) f_QCD_FLAT_13TeV_noBtag->Get("hist_QCD_FLAT_noBtag_filtered_topTagEffNpv_400");
  TH1F * hist_QCD_FLAT_pruned_noBtag_topTagEffNpv_400 = (TH1F*) f_QCD_FLAT_13TeV_noBtag->Get("hist_QCD_FLAT_noBtag_pruned_topTagEffNpv_400");
  TH1F * hist_QCD_FLAT_trimmed_noBtag_topTagEffNpv_400 = (TH1F*) f_QCD_FLAT_13TeV_noBtag->Get("hist_QCD_FLAT_noBtag_trimmed_topTagEffNpv_400");

  TH1F * hist_QCD_FLAT_looseBtag_topTagEffPt = (TH1F*) f_QCD_FLAT_13TeV_looseBtag->Get("hist_QCD_FLAT_looseBtag_topTagEffPt");
  TH1F * hist_QCD_FLAT_filtered_looseBtag_topTagEffPt = (TH1F*) f_QCD_FLAT_13TeV_looseBtag->Get("hist_QCD_FLAT_looseBtag_filtered_topTagEffPt");
  TH1F * hist_QCD_FLAT_pruned_looseBtag_topTagEffPt = (TH1F*) f_QCD_FLAT_13TeV_looseBtag->Get("hist_QCD_FLAT_looseBtag_pruned_topTagEffPt");
  TH1F * hist_QCD_FLAT_trimmed_looseBtag_topTagEffPt = (TH1F*) f_QCD_FLAT_13TeV_looseBtag->Get("hist_QCD_FLAT_looseBtag_trimmed_topTagEffPt");

  TH1F * hist_QCD_FLAT_looseBtag_topTagEffNpv = (TH1F*) f_QCD_FLAT_13TeV_looseBtag->Get("hist_QCD_FLAT_looseBtag_topTagEffNpv");
  TH1F * hist_QCD_FLAT_filtered_looseBtag_topTagEffNpv = (TH1F*) f_QCD_FLAT_13TeV_looseBtag->Get("hist_QCD_FLAT_looseBtag_filtered_topTagEffNpv");
  TH1F * hist_QCD_FLAT_pruned_looseBtag_topTagEffNpv = (TH1F*) f_QCD_FLAT_13TeV_looseBtag->Get("hist_QCD_FLAT_looseBtag_pruned_topTagEffNpv");
  TH1F * hist_QCD_FLAT_trimmed_looseBtag_topTagEffNpv = (TH1F*) f_QCD_FLAT_13TeV_looseBtag->Get("hist_QCD_FLAT_looseBtag_trimmed_topTagEffNpv");

  TH1F * hist_QCD_FLAT_looseBtag_topTagEffNpv_400 = (TH1F*) f_QCD_FLAT_13TeV_looseBtag->Get("hist_QCD_FLAT_looseBtag_topTagEffNpv_400");
  TH1F * hist_QCD_FLAT_filtered_looseBtag_topTagEffNpv_400 = (TH1F*) f_QCD_FLAT_13TeV_looseBtag->Get("hist_QCD_FLAT_looseBtag_filtered_topTagEffNpv_400");
  TH1F * hist_QCD_FLAT_pruned_looseBtag_topTagEffNpv_400 = (TH1F*) f_QCD_FLAT_13TeV_looseBtag->Get("hist_QCD_FLAT_looseBtag_pruned_topTagEffNpv_400");
  TH1F * hist_QCD_FLAT_trimmed_looseBtag_topTagEffNpv_400 = (TH1F*) f_QCD_FLAT_13TeV_looseBtag->Get("hist_QCD_FLAT_looseBtag_trimmed_topTagEffNpv_400");

  TH1F * hist_QCD_FLAT_mediumBtag_topTagEffPt = (TH1F*) f_QCD_FLAT_13TeV_mediumBtag->Get("hist_QCD_FLAT_mediumBtag_topTagEffPt");
  TH1F * hist_QCD_FLAT_filtered_mediumBtag_topTagEffPt = (TH1F*) f_QCD_FLAT_13TeV_mediumBtag->Get("hist_QCD_FLAT_mediumBtag_filtered_topTagEffPt");
  TH1F * hist_QCD_FLAT_pruned_mediumBtag_topTagEffPt = (TH1F*) f_QCD_FLAT_13TeV_mediumBtag->Get("hist_QCD_FLAT_mediumBtag_pruned_topTagEffPt");
  TH1F * hist_QCD_FLAT_trimmed_mediumBtag_topTagEffPt = (TH1F*) f_QCD_FLAT_13TeV_mediumBtag->Get("hist_QCD_FLAT_mediumBtag_trimmed_topTagEffPt");

  TH1F * hist_QCD_FLAT_mediumBtag_topTagEffNpv = (TH1F*) f_QCD_FLAT_13TeV_mediumBtag->Get("hist_QCD_FLAT_mediumBtag_topTagEffNpv");
  TH1F * hist_QCD_FLAT_filtered_mediumBtag_topTagEffNpv = (TH1F*) f_QCD_FLAT_13TeV_mediumBtag->Get("hist_QCD_FLAT_mediumBtag_filtered_topTagEffNpv");
  TH1F * hist_QCD_FLAT_pruned_mediumBtag_topTagEffNpv = (TH1F*) f_QCD_FLAT_13TeV_mediumBtag->Get("hist_QCD_FLAT_mediumBtag_pruned_topTagEffNpv");
  TH1F * hist_QCD_FLAT_trimmed_mediumBtag_topTagEffNpv = (TH1F*) f_QCD_FLAT_13TeV_mediumBtag->Get("hist_QCD_FLAT_mediumBtag_trimmed_topTagEffNpv");

  TH1F * hist_QCD_FLAT_mediumBtag_topTagEffNpv_400 = (TH1F*) f_QCD_FLAT_13TeV_mediumBtag->Get("hist_QCD_FLAT_mediumBtag_topTagEffNpv_400");
  TH1F * hist_QCD_FLAT_filtered_mediumBtag_topTagEffNpv_400 = (TH1F*) f_QCD_FLAT_13TeV_mediumBtag->Get("hist_QCD_FLAT_mediumBtag_filtered_topTagEffNpv_400");
  TH1F * hist_QCD_FLAT_pruned_mediumBtag_topTagEffNpv_400 = (TH1F*) f_QCD_FLAT_13TeV_mediumBtag->Get("hist_QCD_FLAT_mediumBtag_pruned_topTagEffNpv_400");
  TH1F * hist_QCD_FLAT_trimmed_mediumBtag_topTagEffNpv_400 = (TH1F*) f_QCD_FLAT_13TeV_mediumBtag->Get("hist_QCD_FLAT_mediumBtag_trimmed_topTagEffNpv_400");

  //denominator histograms
  TH1F * hist_QCD_FLAT_noBtag_jet1pt = (TH1F*) f_QCD_FLAT_13TeV_noBtag->Get("hist_QCD_FLAT_noBtag_jet1pt");
  TH1F * hist_QCD_FLAT_filtered_noBtag_jet1pt = (TH1F*) f_QCD_FLAT_13TeV_noBtag->Get("hist_QCD_FLAT_noBtag_filtered_jet1pt");
  TH1F * hist_QCD_FLAT_pruned_noBtag_jet1pt = (TH1F*) f_QCD_FLAT_13TeV_noBtag->Get("hist_QCD_FLAT_noBtag_pruned_jet1pt");
  TH1F * hist_QCD_FLAT_trimmed_noBtag_jet1pt = (TH1F*) f_QCD_FLAT_13TeV_noBtag->Get("hist_QCD_FLAT_noBtag_trimmed_jet1pt");

  TH1F * hist_QCD_FLAT_noBtag_npv1 = (TH1F*) f_QCD_FLAT_13TeV_noBtag->Get("hist_QCD_FLAT_noBtag_npv1");
  TH1F * hist_QCD_FLAT_filtered_noBtag_npv1 = (TH1F*) f_QCD_FLAT_13TeV_noBtag->Get("hist_QCD_FLAT_noBtag_filtered_npv1");
  TH1F * hist_QCD_FLAT_pruned_noBtag_npv1 = (TH1F*) f_QCD_FLAT_13TeV_noBtag->Get("hist_QCD_FLAT_noBtag_pruned_npv1");
  TH1F * hist_QCD_FLAT_trimmed_noBtag_npv1 = (TH1F*) f_QCD_FLAT_13TeV_noBtag->Get("hist_QCD_FLAT_noBtag_trimmed_npv1");

  TH1F * hist_QCD_FLAT_noBtag_npv1_400 = (TH1F*) f_QCD_FLAT_13TeV_noBtag->Get("hist_QCD_FLAT_noBtag_npv1_400");
  TH1F * hist_QCD_FLAT_filtered_noBtag_npv1_400 = (TH1F*) f_QCD_FLAT_13TeV_noBtag->Get("hist_QCD_FLAT_noBtag_filtered_npv1_400");
  TH1F * hist_QCD_FLAT_pruned_noBtag_npv1_400 = (TH1F*) f_QCD_FLAT_13TeV_noBtag->Get("hist_QCD_FLAT_noBtag_pruned_npv1_400");
  TH1F * hist_QCD_FLAT_trimmed_noBtag_npv1_400 = (TH1F*) f_QCD_FLAT_13TeV_noBtag->Get("hist_QCD_FLAT_noBtag_trimmed_npv1_400");

  TH1F * hist_QCD_FLAT_looseBtag_jet1pt = (TH1F*) f_QCD_FLAT_13TeV_looseBtag->Get("hist_QCD_FLAT_looseBtag_jet1pt");
  TH1F * hist_QCD_FLAT_filtered_looseBtag_jet1pt = (TH1F*) f_QCD_FLAT_13TeV_looseBtag->Get("hist_QCD_FLAT_looseBtag_filtered_jet1pt");
  TH1F * hist_QCD_FLAT_pruned_looseBtag_jet1pt = (TH1F*) f_QCD_FLAT_13TeV_looseBtag->Get("hist_QCD_FLAT_looseBtag_pruned_jet1pt");
  TH1F * hist_QCD_FLAT_trimmed_looseBtag_jet1pt = (TH1F*) f_QCD_FLAT_13TeV_looseBtag->Get("hist_QCD_FLAT_looseBtag_trimmed_jet1pt");

  TH1F * hist_QCD_FLAT_looseBtag_npv1 = (TH1F*) f_QCD_FLAT_13TeV_looseBtag->Get("hist_QCD_FLAT_looseBtag_npv1");
  TH1F * hist_QCD_FLAT_filtered_looseBtag_npv1 = (TH1F*) f_QCD_FLAT_13TeV_looseBtag->Get("hist_QCD_FLAT_looseBtag_filtered_npv1");
  TH1F * hist_QCD_FLAT_pruned_looseBtag_npv1 = (TH1F*) f_QCD_FLAT_13TeV_looseBtag->Get("hist_QCD_FLAT_looseBtag_pruned_npv1");
  TH1F * hist_QCD_FLAT_trimmed_looseBtag_npv1 = (TH1F*) f_QCD_FLAT_13TeV_looseBtag->Get("hist_QCD_FLAT_looseBtag_trimmed_npv1");

  TH1F * hist_QCD_FLAT_looseBtag_npv1_400 = (TH1F*) f_QCD_FLAT_13TeV_looseBtag->Get("hist_QCD_FLAT_looseBtag_npv1_400");
  TH1F * hist_QCD_FLAT_filtered_looseBtag_npv1_400 = (TH1F*) f_QCD_FLAT_13TeV_looseBtag->Get("hist_QCD_FLAT_looseBtag_filtered_npv1_400");
  TH1F * hist_QCD_FLAT_pruned_looseBtag_npv1_400 = (TH1F*) f_QCD_FLAT_13TeV_looseBtag->Get("hist_QCD_FLAT_looseBtag_pruned_npv1_400");
  TH1F * hist_QCD_FLAT_trimmed_looseBtag_npv1_400 = (TH1F*) f_QCD_FLAT_13TeV_looseBtag->Get("hist_QCD_FLAT_looseBtag_trimmed_npv1_400");

  TH1F * hist_QCD_FLAT_mediumBtag_jet1pt = (TH1F*) f_QCD_FLAT_13TeV_mediumBtag->Get("hist_QCD_FLAT_mediumBtag_jet1pt");
  TH1F * hist_QCD_FLAT_filtered_mediumBtag_jet1pt = (TH1F*) f_QCD_FLAT_13TeV_mediumBtag->Get("hist_QCD_FLAT_mediumBtag_filtered_jet1pt");
  TH1F * hist_QCD_FLAT_pruned_mediumBtag_jet1pt = (TH1F*) f_QCD_FLAT_13TeV_mediumBtag->Get("hist_QCD_FLAT_mediumBtag_pruned_jet1pt");
  TH1F * hist_QCD_FLAT_trimmed_mediumBtag_jet1pt = (TH1F*) f_QCD_FLAT_13TeV_mediumBtag->Get("hist_QCD_FLAT_mediumBtag_trimmed_jet1pt");

  TH1F * hist_QCD_FLAT_mediumBtag_npv1 = (TH1F*) f_QCD_FLAT_13TeV_mediumBtag->Get("hist_QCD_FLAT_mediumBtag_npv1");
  TH1F * hist_QCD_FLAT_filtered_mediumBtag_npv1 = (TH1F*) f_QCD_FLAT_13TeV_mediumBtag->Get("hist_QCD_FLAT_mediumBtag_filtered_npv1");
  TH1F * hist_QCD_FLAT_pruned_mediumBtag_npv1 = (TH1F*) f_QCD_FLAT_13TeV_mediumBtag->Get("hist_QCD_FLAT_mediumBtag_pruned_npv1");
  TH1F * hist_QCD_FLAT_trimmed_mediumBtag_npv1 = (TH1F*) f_QCD_FLAT_13TeV_mediumBtag->Get("hist_QCD_FLAT_mediumBtag_trimmed_npv1");

  TH1F * hist_QCD_FLAT_mediumBtag_npv1_400 = (TH1F*) f_QCD_FLAT_13TeV_mediumBtag->Get("hist_QCD_FLAT_mediumBtag_npv1_400");
  TH1F * hist_QCD_FLAT_filtered_mediumBtag_npv1_400 = (TH1F*) f_QCD_FLAT_13TeV_mediumBtag->Get("hist_QCD_FLAT_mediumBtag_filtered_npv1_400");
  TH1F * hist_QCD_FLAT_pruned_mediumBtag_npv1_400 = (TH1F*) f_QCD_FLAT_13TeV_mediumBtag->Get("hist_QCD_FLAT_mediumBtag_pruned_npv1_400");
  TH1F * hist_QCD_FLAT_trimmed_mediumBtag_npv1_400 = (TH1F*) f_QCD_FLAT_13TeV_mediumBtag->Get("hist_QCD_FLAT_mediumBtag_trimmed_npv1_400");

  //numerator histograms
  TH1F * hist_QCD_FLAT_noBtag_tagJet1pt = (TH1F*) f_QCD_FLAT_13TeV_noBtag->Get("hist_QCD_FLAT_noBtag_tagJet1pt");
  TH1F * hist_QCD_FLAT_filtered_noBtag_tagJet1pt = (TH1F*) f_QCD_FLAT_13TeV_noBtag->Get("hist_QCD_FLAT_noBtag_filtered_tagJet1pt");
  TH1F * hist_QCD_FLAT_pruned_noBtag_tagJet1pt = (TH1F*) f_QCD_FLAT_13TeV_noBtag->Get("hist_QCD_FLAT_noBtag_pruned_tagJet1pt");
  TH1F * hist_QCD_FLAT_trimmed_noBtag_tagJet1pt = (TH1F*) f_QCD_FLAT_13TeV_noBtag->Get("hist_QCD_FLAT_noBtag_trimmed_tagJet1pt");

  TH1F * hist_QCD_FLAT_noBtag_tagNpv1 = (TH1F*) f_QCD_FLAT_13TeV_noBtag->Get("hist_QCD_FLAT_noBtag_tagNpv1");
  TH1F * hist_QCD_FLAT_filtered_noBtag_tagNpv1 = (TH1F*) f_QCD_FLAT_13TeV_noBtag->Get("hist_QCD_FLAT_noBtag_filtered_tagNpv1");
  TH1F * hist_QCD_FLAT_pruned_noBtag_tagNpv1 = (TH1F*) f_QCD_FLAT_13TeV_noBtag->Get("hist_QCD_FLAT_noBtag_pruned_tagNpv1");
  TH1F * hist_QCD_FLAT_trimmed_noBtag_tagNpv1 = (TH1F*) f_QCD_FLAT_13TeV_noBtag->Get("hist_QCD_FLAT_noBtag_trimmed_tagNpv1");

  TH1F * hist_QCD_FLAT_noBtag_tagNpv1_400 = (TH1F*) f_QCD_FLAT_13TeV_noBtag->Get("hist_QCD_FLAT_noBtag_tagNpv1_400");
  TH1F * hist_QCD_FLAT_filtered_noBtag_tagNpv1_400 = (TH1F*) f_QCD_FLAT_13TeV_noBtag->Get("hist_QCD_FLAT_noBtag_filtered_tagNpv1_400");
  TH1F * hist_QCD_FLAT_pruned_noBtag_tagNpv1_400 = (TH1F*) f_QCD_FLAT_13TeV_noBtag->Get("hist_QCD_FLAT_noBtag_pruned_tagNpv1_400");
  TH1F * hist_QCD_FLAT_trimmed_noBtag_tagNpv1_400 = (TH1F*) f_QCD_FLAT_13TeV_noBtag->Get("hist_QCD_FLAT_noBtag_trimmed_tagNpv1_400");

  TH1F * hist_QCD_FLAT_looseBtag_tagJet1pt = (TH1F*) f_QCD_FLAT_13TeV_looseBtag->Get("hist_QCD_FLAT_looseBtag_tagJet1pt");
  TH1F * hist_QCD_FLAT_filtered_looseBtag_tagJet1pt = (TH1F*) f_QCD_FLAT_13TeV_looseBtag->Get("hist_QCD_FLAT_looseBtag_filtered_tagJet1pt");
  TH1F * hist_QCD_FLAT_pruned_looseBtag_tagJet1pt = (TH1F*) f_QCD_FLAT_13TeV_looseBtag->Get("hist_QCD_FLAT_looseBtag_pruned_tagJet1pt");
  TH1F * hist_QCD_FLAT_trimmed_looseBtag_tagJet1pt = (TH1F*) f_QCD_FLAT_13TeV_looseBtag->Get("hist_QCD_FLAT_looseBtag_trimmed_tagJet1pt");

  TH1F * hist_QCD_FLAT_looseBtag_tagNpv1 = (TH1F*) f_QCD_FLAT_13TeV_looseBtag->Get("hist_QCD_FLAT_looseBtag_tagNpv1");
  TH1F * hist_QCD_FLAT_filtered_looseBtag_tagNpv1 = (TH1F*) f_QCD_FLAT_13TeV_looseBtag->Get("hist_QCD_FLAT_looseBtag_filtered_tagNpv1");
  TH1F * hist_QCD_FLAT_pruned_looseBtag_tagNpv1 = (TH1F*) f_QCD_FLAT_13TeV_looseBtag->Get("hist_QCD_FLAT_looseBtag_pruned_tagNpv1");
  TH1F * hist_QCD_FLAT_trimmed_looseBtag_tagNpv1 = (TH1F*) f_QCD_FLAT_13TeV_looseBtag->Get("hist_QCD_FLAT_looseBtag_trimmed_tagNpv1");

  TH1F * hist_QCD_FLAT_looseBtag_tagNpv1_400 = (TH1F*) f_QCD_FLAT_13TeV_looseBtag->Get("hist_QCD_FLAT_looseBtag_tagNpv1_400");
  TH1F * hist_QCD_FLAT_filtered_looseBtag_tagNpv1_400 = (TH1F*) f_QCD_FLAT_13TeV_looseBtag->Get("hist_QCD_FLAT_looseBtag_filtered_tagNpv1_400");
  TH1F * hist_QCD_FLAT_pruned_looseBtag_tagNpv1_400 = (TH1F*) f_QCD_FLAT_13TeV_looseBtag->Get("hist_QCD_FLAT_looseBtag_pruned_tagNpv1_400");
  TH1F * hist_QCD_FLAT_trimmed_looseBtag_tagNpv1_400 = (TH1F*) f_QCD_FLAT_13TeV_looseBtag->Get("hist_QCD_FLAT_looseBtag_trimmed_tagNpv1_400");

  TH1F * hist_QCD_FLAT_mediumBtag_tagJet1pt = (TH1F*) f_QCD_FLAT_13TeV_mediumBtag->Get("hist_QCD_FLAT_mediumBtag_tagJet1pt");
  TH1F * hist_QCD_FLAT_filtered_mediumBtag_tagJet1pt = (TH1F*) f_QCD_FLAT_13TeV_mediumBtag->Get("hist_QCD_FLAT_mediumBtag_filtered_tagJet1pt");
  TH1F * hist_QCD_FLAT_pruned_mediumBtag_tagJet1pt = (TH1F*) f_QCD_FLAT_13TeV_mediumBtag->Get("hist_QCD_FLAT_mediumBtag_pruned_tagJet1pt");
  TH1F * hist_QCD_FLAT_trimmed_mediumBtag_tagJet1pt = (TH1F*) f_QCD_FLAT_13TeV_mediumBtag->Get("hist_QCD_FLAT_mediumBtag_trimmed_tagJet1pt");

  TH1F * hist_QCD_FLAT_mediumBtag_tagNpv1 = (TH1F*) f_QCD_FLAT_13TeV_mediumBtag->Get("hist_QCD_FLAT_mediumBtag_tagNpv1");
  TH1F * hist_QCD_FLAT_filtered_mediumBtag_tagNpv1 = (TH1F*) f_QCD_FLAT_13TeV_mediumBtag->Get("hist_QCD_FLAT_mediumBtag_filtered_tagNpv1");
  TH1F * hist_QCD_FLAT_pruned_mediumBtag_tagNpv1 = (TH1F*) f_QCD_FLAT_13TeV_mediumBtag->Get("hist_QCD_FLAT_mediumBtag_pruned_tagNpv1");
  TH1F * hist_QCD_FLAT_trimmed_mediumBtag_tagNpv1 = (TH1F*) f_QCD_FLAT_13TeV_mediumBtag->Get("hist_QCD_FLAT_mediumBtag_trimmed_tagNpv1");

  TH1F * hist_QCD_FLAT_mediumBtag_tagNpv1_400 = (TH1F*) f_QCD_FLAT_13TeV_mediumBtag->Get("hist_QCD_FLAT_mediumBtag_tagNpv1_400");
  TH1F * hist_QCD_FLAT_filtered_mediumBtag_tagNpv1_400 = (TH1F*) f_QCD_FLAT_13TeV_mediumBtag->Get("hist_QCD_FLAT_mediumBtag_filtered_tagNpv1_400");
  TH1F * hist_QCD_FLAT_pruned_mediumBtag_tagNpv1_400 = (TH1F*) f_QCD_FLAT_13TeV_mediumBtag->Get("hist_QCD_FLAT_mediumBtag_pruned_tagNpv1_400");
  TH1F * hist_QCD_FLAT_trimmed_mediumBtag_tagNpv1_400 = (TH1F*) f_QCD_FLAT_13TeV_mediumBtag->Get("hist_QCD_FLAT_mediumBtag_trimmed_tagNpv1_400");

  //2D Z Prime/QCD histograms
  TH2D *h_ZPrime_QCD_FLAT_nobtag_topTagEff = new TH2D("h_ZPrime_QCD_FLAT_nobtag_topTagEff","QCD Background Rejection vs Z Prime Efficiency (Pt > 400 GeV);Z Prime Efficiency;QCD Rejection",100,0,0.5,100,0.93,1);
  TH2D *h_ZPrime_QCD_FLAT_loosebtag_topTagEff = new TH2D("h_ZPrime_QCD_FLAT_loosebtag_topTagEff","QCD Background Rejection vs Z Prime Efficiency (Pt > 400 GeV);Z Prime Efficiency;QCD Rejection",100,0,0.5,100,0.93,1);
  TH2D *h_ZPrime_QCD_FLAT_mediumbtag_topTagEff = new TH2D("h_ZPrime_QCD_FLAT_mediumbtag_topTagEff","QCD Background Rejection vs Z Prime Efficiency (Pt > 400 GeV);Z Prime Efficiency;QCD Rejection",100,0,0.5,100,0.93,1);

  TH2D *h_ZPrime_QCD_FLAT_ungroomed_topTagEff = new TH2D("h_ZPrime_QCD_FLAT_ungroomed_topTagEff","QCD Background Rejection vs Z Prime Efficiency (Pt > 400 GeV);Z Prime Efficiency;QCD Rejection",100,0,0.7,100,0.93,1);
  TH2D *h_ZPrime_QCD_FLAT_filtered_topTagEff = new TH2D("h_ZPrime_QCD_FLAT_filtered_topTagEff","QCD Background Rejection vs Z Prime Efficiency (Pt > 400 GeV);Z Prime Efficiency;QCD Rejection",100,0,0.7,100,0.93,1);
  TH2D *h_ZPrime_QCD_FLAT_pruned_topTagEff = new TH2D("h_ZPrime_QCD_FLAT_pruned_topTagEff","QCD Background Rejection vs Z Prime Efficiency (Pt > 400 GeV);Z Prime Efficiency;QCD Rejection",100,0,0.7,100,0.93,1);
  TH2D *h_ZPrime_QCD_FLAT_trimmed_topTagEff = new TH2D("h_ZPrime_QCD_FLAT_trimmed_topTagEff","QCD Background Rejection vs Z Prime Efficiency (Pt > 400 GeV);Z Prime Efficiency;QCD Rejection",100,0,1,100,0,1);
 
  //2D ZPrime/QCD comparison (QCD pt 1800 to 2400)
  //denominator integrals
  double int_ZPrime_noBtag_npv1_400 = hist_ZPrime_noBtag_npv1_400->Integral();
  double int_ZPrime_looseBtag_npv1_400 = hist_ZPrime_looseBtag_npv1_400->Integral();
  double int_ZPrime_mediumBtag_npv1_400 = hist_ZPrime_mediumBtag_npv1_400->Integral();
  double int_QCD_noBtag_npv1_400 = hist_QCD_noBtag_npv1_400->Integral();
  double int_QCD_looseBtag_npv1_400 = hist_QCD_looseBtag_npv1_400->Integral();
  double int_QCD_mediumBtag_npv1_400 = hist_QCD_mediumBtag_npv1_400->Integral();

  double int_ZPrime_filtered_noBtag_npv1_400 = hist_ZPrime_filtered_noBtag_npv1_400->Integral();
  double int_QCD_filtered_noBtag_npv1_400 = hist_QCD_filtered_noBtag_npv1_400->Integral();
  double int_ZPrime_pruned_noBtag_npv1_400 = hist_ZPrime_pruned_noBtag_npv1_400->Integral();
  double int_QCD_pruned_noBtag_npv1_400 = hist_QCD_pruned_noBtag_npv1_400->Integral();
  double int_ZPrime_trimmed_noBtag_npv1_400 = hist_ZPrime_trimmed_noBtag_npv1_400->Integral();
  double int_QCD_trimmed_noBtag_npv1_400 = hist_QCD_trimmed_noBtag_npv1_400->Integral();

  //numerator integrals
  double int_ZPrime_noBtag_tagNpv1_400 = hist_ZPrime_noBtag_tagNpv1_400->Integral();
  double int_ZPrime_looseBtag_tagNpv1_400 = hist_ZPrime_looseBtag_tagNpv1_400->Integral();
  double int_ZPrime_mediumBtag_tagNpv1_400 = hist_ZPrime_mediumBtag_tagNpv1_400->Integral();
  double int_QCD_noBtag_tagNpv1_400 = hist_QCD_noBtag_tagNpv1_400->Integral();
  double int_QCD_looseBtag_tagNpv1_400 = hist_QCD_looseBtag_tagNpv1_400->Integral();
  double int_QCD_mediumBtag_tagNpv1_400 = hist_QCD_mediumBtag_tagNpv1_400->Integral();

  double int_ZPrime_filtered_noBtag_tagNpv1_400 = hist_ZPrime_filtered_noBtag_tagNpv1_400->Integral();
  double int_QCD_filtered_noBtag_tagNpv1_400 = hist_QCD_filtered_noBtag_tagNpv1_400->Integral();
  double int_ZPrime_pruned_noBtag_tagNpv1_400 = hist_ZPrime_pruned_noBtag_tagNpv1_400->Integral();
  double int_QCD_pruned_noBtag_tagNpv1_400 = hist_QCD_pruned_noBtag_tagNpv1_400->Integral();
  double int_ZPrime_trimmed_noBtag_tagNpv1_400 = hist_ZPrime_trimmed_noBtag_tagNpv1_400->Integral();
  double int_QCD_trimmed_noBtag_tagNpv1_400 = hist_QCD_trimmed_noBtag_tagNpv1_400->Integral();

  //efficiencies
  double ZPrime_noBtag_efficiency_400 = int_ZPrime_noBtag_tagNpv1_400/int_ZPrime_noBtag_npv1_400;
  double ZPrime_looseBtag_efficiency_400 = int_ZPrime_looseBtag_tagNpv1_400/int_ZPrime_looseBtag_npv1_400;
  double ZPrime_mediumBtag_efficiency_400 = int_ZPrime_mediumBtag_tagNpv1_400/int_ZPrime_mediumBtag_npv1_400;
  double QCD_noBtag_efficiency_400 = int_QCD_noBtag_tagNpv1_400/int_QCD_noBtag_npv1_400;
  double QCD_looseBtag_efficiency_400 = int_QCD_looseBtag_tagNpv1_400/int_QCD_looseBtag_npv1_400;
  double QCD_mediumBtag_efficiency_400 = int_QCD_mediumBtag_tagNpv1_400/int_QCD_mediumBtag_npv1_400;

  double ZPrime_filtered_noBtag_efficiency_400 = int_ZPrime_filtered_noBtag_tagNpv1_400/int_ZPrime_filtered_noBtag_npv1_400;
  double QCD_filtered_noBtag_efficiency_400 = int_QCD_filtered_noBtag_tagNpv1_400/int_QCD_filtered_noBtag_npv1_400;
  double ZPrime_pruned_noBtag_efficiency_400 = int_ZPrime_pruned_noBtag_tagNpv1_400/int_ZPrime_pruned_noBtag_npv1_400;
  double QCD_pruned_noBtag_efficiency_400 = int_QCD_pruned_noBtag_tagNpv1_400/int_QCD_pruned_noBtag_npv1_400;
  double ZPrime_trimmed_noBtag_efficiency_400 = int_ZPrime_trimmed_noBtag_tagNpv1_400/int_ZPrime_trimmed_noBtag_npv1_400;
  double QCD_trimmed_noBtag_efficiency_400 = int_QCD_trimmed_noBtag_tagNpv1_400/int_QCD_trimmed_noBtag_npv1_400;

  //2D Z Prime/QCD efficiency plots - btagging
  h_ZPrime_QCD_nobtag_topTagEff->Fill(ZPrime_noBtag_efficiency_400, 1 - QCD_noBtag_efficiency_400);
  h_ZPrime_QCD_loosebtag_topTagEff->Fill(ZPrime_looseBtag_efficiency_400, 1 - QCD_looseBtag_efficiency_400);
  h_ZPrime_QCD_mediumbtag_topTagEff->Fill(ZPrime_mediumBtag_efficiency_400, 1 - QCD_mediumBtag_efficiency_400);

  //2D Z Prime/QCD efficiency plots - mass grooming
  h_ZPrime_QCD_ungroomed_topTagEff->Fill(ZPrime_noBtag_efficiency_400, 1 - QCD_noBtag_efficiency_400);
  h_ZPrime_QCD_filtered_topTagEff->Fill(ZPrime_filtered_noBtag_efficiency_400, 1 - QCD_filtered_noBtag_efficiency_400);
  h_ZPrime_QCD_pruned_topTagEff->Fill(ZPrime_pruned_noBtag_efficiency_400, 1 - QCD_pruned_noBtag_efficiency_400);
  h_ZPrime_QCD_trimmed_topTagEff->Fill(ZPrime_trimmed_noBtag_efficiency_400, 1 - QCD_trimmed_noBtag_efficiency_400);

  TCanvas* cBtag_compare_2D = new TCanvas("2D Btag comparison");
  h_ZPrime_QCD_nobtag_topTagEff->Draw("P");
  h_ZPrime_QCD_loosebtag_topTagEff->Draw("PSame");
  h_ZPrime_QCD_mediumbtag_topTagEff->Draw("PSame");
  h_ZPrime_QCD_nobtag_topTagEff->SetMarkerColor(kRed-3);
  h_ZPrime_QCD_loosebtag_topTagEff->SetMarkerColor(kAzure+3);
  h_ZPrime_QCD_mediumbtag_topTagEff->SetMarkerColor(kTeal-6);
  h_ZPrime_QCD_nobtag_topTagEff->SetMarkerStyle(8);
  h_ZPrime_QCD_loosebtag_topTagEff->SetMarkerStyle(8);
  h_ZPrime_QCD_mediumbtag_topTagEff->SetMarkerStyle(8);
  h_ZPrime_QCD_nobtag_topTagEff->GetYaxis()->SetTitleOffset(1.3);

  TLegend* lBtag_compare_2D = new TLegend(0.7,0.7,0.9,0.9);
  lBtag_compare_2D->AddEntry(h_ZPrime_QCD_nobtag_topTagEff,"No b-tagging","P");
  lBtag_compare_2D->AddEntry(h_ZPrime_QCD_loosebtag_topTagEff,"Loose b-tagging","P");
  lBtag_compare_2D->AddEntry(h_ZPrime_QCD_mediumbtag_topTagEff,"Medium b-tagging","P");
  lBtag_compare_2D->Draw("SAME");
  lBtag_compare_2D->SetFillColor(kWhite);

  cBtag_compare_2D->SaveAs("TopTagEfficiency2D_QCD_ZPrime_bTagCompare_400.pdf");

  TCanvas* cGrooming_compare_2D_400 = new TCanvas("2D Grooming comparison");
  h_ZPrime_QCD_ungroomed_topTagEff->Draw("P");
  h_ZPrime_QCD_filtered_topTagEff->Draw("PSame");
  h_ZPrime_QCD_pruned_topTagEff->Draw("PSame");
  h_ZPrime_QCD_trimmed_topTagEff->Draw("PSame");
  h_ZPrime_QCD_ungroomed_topTagEff->SetMarkerColor(kRed-3);
  h_ZPrime_QCD_filtered_topTagEff->SetMarkerColor(kAzure+3);
  h_ZPrime_QCD_pruned_topTagEff->SetMarkerColor(kTeal-6);
  h_ZPrime_QCD_trimmed_topTagEff->SetMarkerColor(kOrange);
  h_ZPrime_QCD_ungroomed_topTagEff->SetMarkerStyle(8);
  h_ZPrime_QCD_filtered_topTagEff->SetMarkerStyle(8);
  h_ZPrime_QCD_pruned_topTagEff->SetMarkerStyle(8);
  h_ZPrime_QCD_trimmed_topTagEff->SetMarkerStyle(8);
  h_ZPrime_QCD_ungroomed_topTagEff->GetYaxis()->SetTitleOffset(1.3);

  TLegend* lGrooming_compare_2D_400 = new TLegend(0.7,0.7,0.9,0.9);
  lGrooming_compare_2D_400->AddEntry(h_ZPrime_QCD_ungroomed_topTagEff,"No Grooming Techniques","P");
  lGrooming_compare_2D_400->AddEntry(h_ZPrime_QCD_filtered_topTagEff,"Fitered AK8 Jets","P");
  lGrooming_compare_2D_400->AddEntry(h_ZPrime_QCD_pruned_topTagEff,"Pruned AK8 Jets","P");
  lGrooming_compare_2D_400->AddEntry(h_ZPrime_QCD_trimmed_topTagEff,"Trimmed AK8 Jets","P");
  lGrooming_compare_2D_400->Draw("SAME");
  lGrooming_compare_2D_400->SetFillColor(kWhite); 

  cGrooming_compare_2D_400->SaveAs("TopTagEfficiency2D_QCD_ZPrime_massGroomCompare_400.pdf");

  //2D ZPrime/QCD comparison (QCD pt 15 to 3000 - weighted)
  //denominator integrals
  double int_ZPrime_noBtag_npv1_400 = hist_ZPrime_noBtag_npv1_400->Integral();
  double int_ZPrime_looseBtag_npv1_400 = hist_ZPrime_looseBtag_npv1_400->Integral();
  double int_ZPrime_mediumBtag_npv1_400 = hist_ZPrime_mediumBtag_npv1_400->Integral();
  double int_QCD_FLAT_weighted_noBtag_npv1_400 = hist_QCD_FLAT_weighted_noBtag_npv1_400->Integral();
  double int_QCD_FLAT_weighted_looseBtag_npv1_400 = hist_QCD_FLAT_weighted_looseBtag_npv1_400->Integral();
  double int_QCD_FLAT_weighted_mediumBtag_npv1_400 = hist_QCD_FLAT_weighted_mediumBtag_npv1_400->Integral();

  double int_ZPrime_filtered_noBtag_npv1_400 = hist_ZPrime_filtered_noBtag_npv1_400->Integral();
  double int_QCD_FLAT_weighted_filtered_noBtag_npv1_400 = hist_QCD_FLAT_weighted_filtered_noBtag_npv1_400->Integral();
  double int_ZPrime_pruned_noBtag_npv1_400 = hist_ZPrime_pruned_noBtag_npv1_400->Integral();
  double int_QCD_FLAT_weighted_pruned_noBtag_npv1_400 = hist_QCD_FLAT_weighted_pruned_noBtag_npv1_400->Integral();
  double int_ZPrime_trimmed_noBtag_npv1_400 = hist_ZPrime_trimmed_noBtag_npv1_400->Integral();
  double int_QCD_FLAT_weighted_trimmed_noBtag_npv1_400 = hist_QCD_FLAT_weighted_trimmed_noBtag_npv1_400->Integral();

  //numerator integrals
  double int_ZPrime_noBtag_tagNpv1_400 = hist_ZPrime_noBtag_tagNpv1_400->Integral();
  double int_ZPrime_looseBtag_tagNpv1_400 = hist_ZPrime_looseBtag_tagNpv1_400->Integral();
  double int_ZPrime_mediumBtag_tagNpv1_400 = hist_ZPrime_mediumBtag_tagNpv1_400->Integral();
  double int_QCD_FLAT_weighted_noBtag_tagNpv1_400 = hist_QCD_FLAT_weighted_noBtag_tagNpv1_400->Integral();
  double int_QCD_FLAT_weighted_looseBtag_tagNpv1_400 = hist_QCD_FLAT_weighted_looseBtag_tagNpv1_400->Integral();
  double int_QCD_FLAT_weighted_mediumBtag_tagNpv1_400 = hist_QCD_FLAT_weighted_mediumBtag_tagNpv1_400->Integral();

  double int_ZPrime_filtered_noBtag_tagNpv1_400 = hist_ZPrime_filtered_noBtag_tagNpv1_400->Integral();
  double int_QCD_FLAT_weighted_filtered_noBtag_tagNpv1_400 = hist_QCD_FLAT_weighted_filtered_noBtag_tagNpv1_400->Integral();
  double int_ZPrime_pruned_noBtag_tagNpv1_400 = hist_ZPrime_pruned_noBtag_tagNpv1_400->Integral();
  double int_QCD_FLAT_weighted_pruned_noBtag_tagNpv1_400 = hist_QCD_FLAT_weighted_pruned_noBtag_tagNpv1_400->Integral();
  double int_ZPrime_trimmed_noBtag_tagNpv1_400 = hist_ZPrime_trimmed_noBtag_tagNpv1_400->Integral();
  double int_QCD_FLAT_weighted_trimmed_noBtag_tagNpv1_400 = hist_QCD_FLAT_weighted_trimmed_noBtag_tagNpv1_400->Integral();

  //efficiencies
  double ZPrime_noBtag_efficiency_400 = int_ZPrime_noBtag_tagNpv1_400/int_ZPrime_noBtag_npv1_400;
  double ZPrime_looseBtag_efficiency_400 = int_ZPrime_looseBtag_tagNpv1_400/int_ZPrime_looseBtag_npv1_400;
  double ZPrime_mediumBtag_efficiency_400 = int_ZPrime_mediumBtag_tagNpv1_400/int_ZPrime_mediumBtag_npv1_400;
  double QCD_FLAT_weighted_noBtag_efficiency_400 = int_QCD_FLAT_weighted_noBtag_tagNpv1_400/int_QCD_FLAT_weighted_noBtag_npv1_400;
  double QCD_FLAT_weighted_looseBtag_efficiency_400 = int_QCD_FLAT_weighted_looseBtag_tagNpv1_400/int_QCD_FLAT_weighted_looseBtag_npv1_400;
  double QCD_FLAT_weighted_mediumBtag_efficiency_400 = int_QCD_FLAT_weighted_mediumBtag_tagNpv1_400/int_QCD_FLAT_weighted_mediumBtag_npv1_400;

  double ZPrime_filtered_noBtag_efficiency_400 = int_ZPrime_filtered_noBtag_tagNpv1_400/int_ZPrime_filtered_noBtag_npv1_400;
  double QCD_FLAT_weighted_filtered_noBtag_efficiency_400 = int_QCD_FLAT_weighted_filtered_noBtag_tagNpv1_400/int_QCD_FLAT_weighted_filtered_noBtag_npv1_400;
  double ZPrime_pruned_noBtag_efficiency_400 = int_ZPrime_pruned_noBtag_tagNpv1_400/int_ZPrime_pruned_noBtag_npv1_400;
  double QCD_FLAT_weighted_pruned_noBtag_efficiency_400 = int_QCD_FLAT_weighted_pruned_noBtag_tagNpv1_400/int_QCD_FLAT_weighted_pruned_noBtag_npv1_400;
  double ZPrime_trimmed_noBtag_efficiency_400 = int_ZPrime_trimmed_noBtag_tagNpv1_400/int_ZPrime_trimmed_noBtag_npv1_400;
  double QCD_FLAT_weighted_trimmed_noBtag_efficiency_400 = int_QCD_FLAT_weighted_trimmed_noBtag_tagNpv1_400/int_QCD_FLAT_weighted_trimmed_noBtag_npv1_400;

  //2D Z Prime/QCD efficiency plots - btagging
  h_ZPrime_QCD_FLAT_weighted_nobtag_topTagEff->Fill(ZPrime_noBtag_efficiency_400, 1 - QCD_FLAT_weighted_noBtag_efficiency_400);
  h_ZPrime_QCD_FLAT_weighted_loosebtag_topTagEff->Fill(ZPrime_looseBtag_efficiency_400, 1 - QCD_FLAT_weighted_looseBtag_efficiency_400);
  h_ZPrime_QCD_FLAT_weighted_mediumbtag_topTagEff->Fill(ZPrime_mediumBtag_efficiency_400, 1 - QCD_FLAT_weighted_mediumBtag_efficiency_400);

  //2D Z Prime/QCD efficiency plots - mass grooming
  h_ZPrime_QCD_FLAT_weighted_ungroomed_topTagEff->Fill(ZPrime_noBtag_efficiency_400, 1 - QCD_FLAT_weighted_noBtag_efficiency_400);
  h_ZPrime_QCD_FLAT_weighted_filtered_topTagEff->Fill(ZPrime_filtered_noBtag_efficiency_400, 1 - QCD_FLAT_weighted_filtered_noBtag_efficiency_400);
  h_ZPrime_QCD_FLAT_weighted_pruned_topTagEff->Fill(ZPrime_pruned_noBtag_efficiency_400, 1 - QCD_FLAT_weighted_pruned_noBtag_efficiency_400);
  h_ZPrime_QCD_FLAT_weighted_trimmed_topTagEff->Fill(ZPrime_trimmed_noBtag_efficiency_400, 1 - QCD_FLAT_weighted_trimmed_noBtag_efficiency_400);

  TCanvas* cBtag_compare_2D = new TCanvas("2D Btag comparison");
  h_ZPrime_QCD_FLAT_weighted_nobtag_topTagEff->Draw("P");
  h_ZPrime_QCD_FLAT_weighted_loosebtag_topTagEff->Draw("PSame");
  h_ZPrime_QCD_FLAT_weighted_mediumbtag_topTagEff->Draw("PSame");
  h_ZPrime_QCD_FLAT_weighted_nobtag_topTagEff->SetMarkerColor(kRed-3);
  h_ZPrime_QCD_FLAT_weighted_loosebtag_topTagEff->SetMarkerColor(kAzure+3);
  h_ZPrime_QCD_FLAT_weighted_mediumbtag_topTagEff->SetMarkerColor(kTeal-6);
  h_ZPrime_QCD_FLAT_weighted_nobtag_topTagEff->SetMarkerStyle(8);
  h_ZPrime_QCD_FLAT_weighted_loosebtag_topTagEff->SetMarkerStyle(8);
  h_ZPrime_QCD_FLAT_weighted_mediumbtag_topTagEff->SetMarkerStyle(8);
  h_ZPrime_QCD_FLAT_weighted_nobtag_topTagEff->GetYaxis()->SetTitleOffset(1.3);

  TLegend* lBtag_compare_2D = new TLegend(0.7,0.7,0.9,0.9);
  lBtag_compare_2D->AddEntry(h_ZPrime_QCD_FLAT_weighted_nobtag_topTagEff,"No b-tagging","P");
  lBtag_compare_2D->AddEntry(h_ZPrime_QCD_FLAT_weighted_loosebtag_topTagEff,"Loose b-tagging","P");
  lBtag_compare_2D->AddEntry(h_ZPrime_QCD_FLAT_weighted_mediumbtag_topTagEff,"Medium b-tagging","P");
  lBtag_compare_2D->Draw("SAME");
  lBtag_compare_2D->SetFillColor(kWhite);

  TCanvas* cGrooming_compare_2D = new TCanvas("2D Grooming comparison");
  h_ZPrime_QCD_FLAT_weighted_ungroomed_topTagEff->Draw("P");
  h_ZPrime_QCD_FLAT_weighted_filtered_topTagEff->Draw("PSame");
  h_ZPrime_QCD_FLAT_weighted_pruned_topTagEff->Draw("PSame");
  h_ZPrime_QCD_FLAT_weighted_trimmed_topTagEff->Draw("PSame");
  h_ZPrime_QCD_FLAT_weighted_ungroomed_topTagEff->SetMarkerColor(kRed-3);
  h_ZPrime_QCD_FLAT_weighted_filtered_topTagEff->SetMarkerColor(kAzure+3);
  h_ZPrime_QCD_FLAT_weighted_pruned_topTagEff->SetMarkerColor(kTeal-6);
  h_ZPrime_QCD_FLAT_weighted_trimmed_topTagEff->SetMarkerColor(kOrange);
  h_ZPrime_QCD_FLAT_weighted_ungroomed_topTagEff->SetMarkerStyle(8);
  h_ZPrime_QCD_FLAT_weighted_filtered_topTagEff->SetMarkerStyle(8);
  h_ZPrime_QCD_FLAT_weighted_pruned_topTagEff->SetMarkerStyle(8);
  h_ZPrime_QCD_FLAT_weighted_trimmed_topTagEff->SetMarkerStyle(8);
  h_ZPrime_QCD_FLAT_weighted_ungroomed_topTagEff->GetYaxis()->SetTitleOffset(1.3);

  TLegend* lGrooming_compare_2D = new TLegend(0.7,0.7,0.9,0.9);
  lGrooming_compare_2D->AddEntry(h_ZPrime_QCD_FLAT_weighted_ungroomed_topTagEff,"No Grooming Techniques","P");
  lGrooming_compare_2D->AddEntry(h_ZPrime_QCD_FLAT_weighted_filtered_topTagEff,"Fitered AK8 Jets","P");
  lGrooming_compare_2D->AddEntry(h_ZPrime_QCD_FLAT_weighted_pruned_topTagEff,"Pruned AK8 Jets","P");
  lGrooming_compare_2D->AddEntry(h_ZPrime_QCD_FLAT_weighted_trimmed_topTagEff,"Trimmed AK8 Jets","P");
  lGrooming_compare_2D->Draw("SAME");
  lGrooming_compare_2D->SetFillColor(kWhite); 

  //2D ZPrime/QCD comparison (QCD pt 15 to 3000 - weighted)
  //denominator integrals
  double int_ZPrime_noBtag_npv1_400 = hist_ZPrime_noBtag_npv1_400->Integral();
  double int_ZPrime_looseBtag_npv1_400 = hist_ZPrime_looseBtag_npv1_400->Integral();
  double int_ZPrime_mediumBtag_npv1_400 = hist_ZPrime_mediumBtag_npv1_400->Integral();
  double int_QCD_FLAT_noBtag_npv1_400 = hist_QCD_FLAT_noBtag_npv1_400->Integral();
  double int_QCD_FLAT_looseBtag_npv1_400 = hist_QCD_FLAT_looseBtag_npv1_400->Integral();
  double int_QCD_FLAT_mediumBtag_npv1_400 = hist_QCD_FLAT_mediumBtag_npv1_400->Integral();

  double int_ZPrime_filtered_noBtag_npv1_400 = hist_ZPrime_filtered_noBtag_npv1_400->Integral();
  double int_QCD_FLAT_filtered_noBtag_npv1_400 = hist_QCD_FLAT_filtered_noBtag_npv1_400->Integral();
  double int_ZPrime_pruned_noBtag_npv1_400 = hist_ZPrime_pruned_noBtag_npv1_400->Integral();
  double int_QCD_FLAT_pruned_noBtag_npv1_400 = hist_QCD_FLAT_pruned_noBtag_npv1_400->Integral();
  double int_ZPrime_trimmed_noBtag_npv1_400 = hist_ZPrime_trimmed_noBtag_npv1_400->Integral();
  double int_QCD_FLAT_trimmed_noBtag_npv1_400 = hist_QCD_FLAT_trimmed_noBtag_npv1_400->Integral();

  //numerator integrals
  double int_ZPrime_noBtag_tagNpv1_400 = hist_ZPrime_noBtag_tagNpv1_400->Integral();
  double int_ZPrime_looseBtag_tagNpv1_400 = hist_ZPrime_looseBtag_tagNpv1_400->Integral();
  double int_ZPrime_mediumBtag_tagNpv1_400 = hist_ZPrime_mediumBtag_tagNpv1_400->Integral();
  double int_QCD_FLAT_noBtag_tagNpv1_400 = hist_QCD_FLAT_noBtag_tagNpv1_400->Integral();
  double int_QCD_FLAT_looseBtag_tagNpv1_400 = hist_QCD_FLAT_looseBtag_tagNpv1_400->Integral();
  double int_QCD_FLAT_mediumBtag_tagNpv1_400 = hist_QCD_FLAT_mediumBtag_tagNpv1_400->Integral();

  double int_ZPrime_filtered_noBtag_tagNpv1_400 = hist_ZPrime_filtered_noBtag_tagNpv1_400->Integral();
  double int_QCD_FLAT_filtered_noBtag_tagNpv1_400 = hist_QCD_FLAT_filtered_noBtag_tagNpv1_400->Integral();
  double int_ZPrime_pruned_noBtag_tagNpv1_400 = hist_ZPrime_pruned_noBtag_tagNpv1_400->Integral();
  double int_QCD_FLAT_pruned_noBtag_tagNpv1_400 = hist_QCD_FLAT_pruned_noBtag_tagNpv1_400->Integral();
  double int_ZPrime_trimmed_noBtag_tagNpv1_400 = hist_ZPrime_trimmed_noBtag_tagNpv1_400->Integral();
  double int_QCD_FLAT_trimmed_noBtag_tagNpv1_400 = hist_QCD_FLAT_trimmed_noBtag_tagNpv1_400->Integral();

  //efficiencies
  double ZPrime_noBtag_efficiency_400 = int_ZPrime_noBtag_tagNpv1_400/int_ZPrime_noBtag_npv1_400;
  double ZPrime_looseBtag_efficiency_400 = int_ZPrime_looseBtag_tagNpv1_400/int_ZPrime_looseBtag_npv1_400;
  double ZPrime_mediumBtag_efficiency_400 = int_ZPrime_mediumBtag_tagNpv1_400/int_ZPrime_mediumBtag_npv1_400;
  double QCD_FLAT_noBtag_efficiency_400 = int_QCD_FLAT_noBtag_tagNpv1_400/int_QCD_FLAT_noBtag_npv1_400;
  double QCD_FLAT_looseBtag_efficiency_400 = int_QCD_FLAT_looseBtag_tagNpv1_400/int_QCD_FLAT_looseBtag_npv1_400;
  double QCD_FLAT_mediumBtag_efficiency_400 = int_QCD_FLAT_mediumBtag_tagNpv1_400/int_QCD_FLAT_mediumBtag_npv1_400;

  double ZPrime_filtered_noBtag_efficiency_400 = int_ZPrime_filtered_noBtag_tagNpv1_400/int_ZPrime_filtered_noBtag_npv1_400;
  double QCD_FLAT_filtered_noBtag_efficiency_400 = int_QCD_FLAT_filtered_noBtag_tagNpv1_400/int_QCD_FLAT_filtered_noBtag_npv1_400;
  double ZPrime_pruned_noBtag_efficiency_400 = int_ZPrime_pruned_noBtag_tagNpv1_400/int_ZPrime_pruned_noBtag_npv1_400;
  double QCD_FLAT_pruned_noBtag_efficiency_400 = int_QCD_FLAT_pruned_noBtag_tagNpv1_400/int_QCD_FLAT_pruned_noBtag_npv1_400;
  double ZPrime_trimmed_noBtag_efficiency_400 = int_ZPrime_trimmed_noBtag_tagNpv1_400/int_ZPrime_trimmed_noBtag_npv1_400;
  double QCD_FLAT_trimmed_noBtag_efficiency_400 = int_QCD_FLAT_trimmed_noBtag_tagNpv1_400/int_QCD_FLAT_trimmed_noBtag_npv1_400;

  //2D Z Prime/QCD efficiency plots - btagging
  h_ZPrime_QCD_FLAT_nobtag_topTagEff->Fill(ZPrime_noBtag_efficiency_400, 1 - QCD_FLAT_noBtag_efficiency_400);
  h_ZPrime_QCD_FLAT_loosebtag_topTagEff->Fill(ZPrime_looseBtag_efficiency_400, 1 - QCD_FLAT_looseBtag_efficiency_400);
  h_ZPrime_QCD_FLAT_mediumbtag_topTagEff->Fill(ZPrime_mediumBtag_efficiency_400, 1 - QCD_FLAT_mediumBtag_efficiency_400);

  //2D Z Prime/QCD efficiency plots - mass grooming
  h_ZPrime_QCD_FLAT_ungroomed_topTagEff->Fill(ZPrime_noBtag_efficiency_400, 1 - QCD_FLAT_noBtag_efficiency_400);
  h_ZPrime_QCD_FLAT_filtered_topTagEff->Fill(ZPrime_filtered_noBtag_efficiency_400, 1 - QCD_FLAT_filtered_noBtag_efficiency_400);
  h_ZPrime_QCD_FLAT_pruned_topTagEff->Fill(ZPrime_pruned_noBtag_efficiency_400, 1 - QCD_FLAT_pruned_noBtag_efficiency_400);
  h_ZPrime_QCD_FLAT_trimmed_topTagEff->Fill(ZPrime_trimmed_noBtag_efficiency_400, 1 - QCD_FLAT_trimmed_noBtag_efficiency_400);

  TCanvas* cBtag_compare_2D = new TCanvas("2D Btag comparison - unweighted");
  h_ZPrime_QCD_FLAT_nobtag_topTagEff->Draw("P");
  h_ZPrime_QCD_FLAT_loosebtag_topTagEff->Draw("PSame");
  h_ZPrime_QCD_FLAT_mediumbtag_topTagEff->Draw("PSame");
  h_ZPrime_QCD_FLAT_nobtag_topTagEff->SetMarkerColor(kRed-3);
  h_ZPrime_QCD_FLAT_loosebtag_topTagEff->SetMarkerColor(kAzure+3);
  h_ZPrime_QCD_FLAT_mediumbtag_topTagEff->SetMarkerColor(kTeal-6);
  h_ZPrime_QCD_FLAT_nobtag_topTagEff->SetMarkerStyle(8);
  h_ZPrime_QCD_FLAT_loosebtag_topTagEff->SetMarkerStyle(8);
  h_ZPrime_QCD_FLAT_mediumbtag_topTagEff->SetMarkerStyle(8);
  h_ZPrime_QCD_FLAT_nobtag_topTagEff->GetYaxis()->SetTitleOffset(1.3);

  TLegend* lBtag_compare_2D = new TLegend(0.7,0.7,0.9,0.9);
  lBtag_compare_2D->AddEntry(h_ZPrime_QCD_FLAT_nobtag_topTagEff,"No b-tagging","P");
  lBtag_compare_2D->AddEntry(h_ZPrime_QCD_FLAT_loosebtag_topTagEff,"Loose b-tagging","P");
  lBtag_compare_2D->AddEntry(h_ZPrime_QCD_FLAT_mediumbtag_topTagEff,"Medium b-tagging","P");
  lBtag_compare_2D->Draw("SAME");
  lBtag_compare_2D->SetFillColor(kWhite);

  TCanvas* cGrooming_compare_2D = new TCanvas("2D Grooming comparison - unweighted");
  h_ZPrime_QCD_FLAT_ungroomed_topTagEff->Draw("P");
  h_ZPrime_QCD_FLAT_filtered_topTagEff->Draw("PSame");
  h_ZPrime_QCD_FLAT_pruned_topTagEff->Draw("PSame");
  h_ZPrime_QCD_FLAT_trimmed_topTagEff->Draw("PSame");
  h_ZPrime_QCD_FLAT_ungroomed_topTagEff->SetMarkerColor(kRed-3);
  h_ZPrime_QCD_FLAT_filtered_topTagEff->SetMarkerColor(kAzure+3);
  h_ZPrime_QCD_FLAT_pruned_topTagEff->SetMarkerColor(kTeal-6);
  h_ZPrime_QCD_FLAT_trimmed_topTagEff->SetMarkerColor(kOrange);
  h_ZPrime_QCD_FLAT_ungroomed_topTagEff->SetMarkerStyle(8);
  h_ZPrime_QCD_FLAT_filtered_topTagEff->SetMarkerStyle(8);
  h_ZPrime_QCD_FLAT_pruned_topTagEff->SetMarkerStyle(8);
  h_ZPrime_QCD_FLAT_trimmed_topTagEff->SetMarkerStyle(8);
  h_ZPrime_QCD_FLAT_ungroomed_topTagEff->GetYaxis()->SetTitleOffset(1.3);

  TLegend* lGrooming_compare_2D = new TLegend(0.7,0.7,0.9,0.9);
  lGrooming_compare_2D->AddEntry(h_ZPrime_QCD_FLAT_ungroomed_topTagEff,"No Grooming Techniques","P");
  lGrooming_compare_2D->AddEntry(h_ZPrime_QCD_FLAT_filtered_topTagEff,"Fitered AK8 Jets","P");
  lGrooming_compare_2D->AddEntry(h_ZPrime_QCD_FLAT_pruned_topTagEff,"Pruned AK8 Jets","P");
  lGrooming_compare_2D->AddEntry(h_ZPrime_QCD_FLAT_trimmed_topTagEff,"Trimmed AK8 Jets","P");
  lGrooming_compare_2D->Draw("SAME");
  lGrooming_compare_2D->SetFillColor(kWhite); 

  TCanvas* cBtag_compare_npv = new TCanvas("Btag comparison - Efficiency vs Npv");
  hist_QCD_noBtag_topTagEffNpv->Draw();
  hist_QCD_noBtag_topTagEffNpv->SetMinimum(0.0001);
  hist_QCD_noBtag_topTagEffNpv->SetMaximum(5.0);
  hist_ZPrime_noBtag_topTagEffNpv->Draw("ESAME");
  hist_ZPrime_noBtag_topTagEffNpv->SetMinimum(0.0001);
  hist_ZPrime_noBtag_topTagEffNpv->SetMaximum(5.0);
  hist_QCD_noBtag_topTagEffNpv->SetTitle("Efficiency vs Npv - ZPrime/QCD Comparison");
  hist_QCD_noBtag_topTagEffNpv->SetLineColor(kBlue+3);
  hist_ZPrime_noBtag_topTagEffNpv->SetLineColor(kOrange+9);
  cBtag_compare_npv->SetLogy();

  //TCanvas* cLooseBtag_compare_npv = new TCanvas("Loose Btag efficiency - npv");
  hist_QCD_looseBtag_topTagEffNpv->Draw("ESAME");
  hist_QCD_looseBtag_topTagEffNpv->SetMinimum(0.0001);
  hist_QCD_looseBtag_topTagEffNpv->SetMaximum(5.0);
  hist_ZPrime_looseBtag_topTagEffNpv->Draw("ESAME");
  hist_ZPrime_looseBtag_topTagEffNpv->SetMinimum(0.0001);
  hist_ZPrime_looseBtag_topTagEffNpv->SetMaximum(5.0);
  hist_QCD_looseBtag_topTagEffNpv->SetLineColor(kBlue+10);
  hist_ZPrime_looseBtag_topTagEffNpv->SetLineColor(kOrange+10);

  //TCanvas* cMediumBtag_compare_npv = new TCanvas("Medium Btag efficiency - npv");
  hist_QCD_mediumBtag_topTagEffNpv->Draw("ESAME");
  hist_QCD_mediumBtag_topTagEffNpv->SetMinimum(0.0001);
  hist_QCD_mediumBtag_topTagEffNpv->SetMaximum(5.0);
  hist_ZPrime_mediumBtag_topTagEffNpv->Draw("ESAME");
  hist_ZPrime_mediumBtag_topTagEffNpv->SetMinimum(0.0001);
  hist_ZPrime_mediumBtag_topTagEffNpv->SetMaximum(5.0);
  hist_QCD_mediumBtag_topTagEffNpv->SetLineColor(kBlue-7);
  hist_ZPrime_mediumBtag_topTagEffNpv->SetLineColor(kOrange+6);

  TLegend* lBtag_compare_npv = new TLegend(0.7,0.7,0.9,0.9);
  lBtag_compare_npv->AddEntry(hist_ZPrime_noBtag_topTagEffNpv,"Z Prime - No b-tagging","LPE");
  lBtag_compare_npv->AddEntry(hist_ZPrime_looseBtag_topTagEffNpv,"Z Prime - Loose b-tagging","LPE");
  lBtag_compare_npv->AddEntry(hist_ZPrime_mediumBtag_topTagEffNpv,"Z Prime - Medium b-tagging","LPE");
  lBtag_compare_npv->AddEntry(hist_QCD_noBtag_topTagEffNpv,"QCD - No b-tagging","LPE");
  lBtag_compare_npv->AddEntry(hist_QCD_looseBtag_topTagEffNpv,"QCD - Loose b-tagging","LPE");
  lBtag_compare_npv->AddEntry(hist_QCD_mediumBtag_topTagEffNpv,"QCD - Medium b-tagging","LPE");
  lBtag_compare_npv->Draw("SAME");
  lBtag_compare_npv->SetFillColor(kWhite);

  TCanvas* cBtag_compare_pt = new TCanvas("Btag comparison - Efficiency vs Pt");
  hist_QCD_noBtag_topTagEffPt->Draw();
  hist_QCD_noBtag_topTagEffPt->SetMinimum(0.0001);
  hist_QCD_noBtag_topTagEffPt->SetMaximum(5.0);
  hist_ZPrime_noBtag_topTagEffPt->Draw("ESAME");
  hist_ZPrime_noBtag_topTagEffPt->SetMinimum(0.0001);
  hist_ZPrime_noBtag_topTagEffPt->SetMaximum(5.0);
  hist_QCD_noBtag_topTagEffPt->SetTitle("Efficiency vs Pt - ZPrime/QCD Comparison");
  hist_QCD_noBtag_topTagEffPt->SetLineColor(kBlue+3);
  hist_ZPrime_noBtag_topTagEffPt->SetLineColor(kOrange+9);
  cBtag_compare_pt->SetLogy();

  //TCanvas* cLooseBtag_compare_pt = new TCanvas("Loose Btag efficiency - pt");
  hist_QCD_looseBtag_topTagEffPt->Draw("ESAME");
  hist_QCD_looseBtag_topTagEffPt->SetMinimum(0.0001);
  hist_QCD_looseBtag_topTagEffPt->SetMaximum(5.0);
  hist_ZPrime_looseBtag_topTagEffPt->Draw("ESAME");
  hist_ZPrime_looseBtag_topTagEffPt->SetMinimum(0.0001);
  hist_ZPrime_looseBtag_topTagEffPt->SetMaximum(5.0);
  hist_QCD_looseBtag_topTagEffPt->SetLineColor(kBlue+10);
  hist_ZPrime_looseBtag_topTagEffPt->SetLineColor(kOrange+10);

  //TCanvas* cMediumBtag_compare_pt = new TCanvas("Medium Btag efficiency - pt");
  hist_QCD_mediumBtag_topTagEffPt->Draw("ESAME");
  hist_QCD_mediumBtag_topTagEffPt->SetMinimum(0.0001);
  hist_QCD_mediumBtag_topTagEffPt->SetMaximum(5.0);
  hist_ZPrime_mediumBtag_topTagEffPt->Draw("ESAME");
  hist_ZPrime_mediumBtag_topTagEffPt->SetMinimum(0.0001);
  hist_ZPrime_mediumBtag_topTagEffPt->SetMaximum(5.0);
  hist_QCD_mediumBtag_topTagEffPt->SetLineColor(kBlue-7);
  hist_ZPrime_mediumBtag_topTagEffPt->SetLineColor(kOrange+6);

  TLegend* lBtag_compare_pt = new TLegend(0.7,0.7,0.9,0.9);
  lBtag_compare_pt->AddEntry(hist_ZPrime_noBtag_topTagEffPt,"Z Prime - No b-tagging","LPE");
  lBtag_compare_pt->AddEntry(hist_ZPrime_looseBtag_topTagEffPt,"Z Prime - Loose b-tagging","LPE");
  lBtag_compare_pt->AddEntry(hist_ZPrime_mediumBtag_topTagEffPt,"Z Prime - Medium b-tagging","LPE");
  lBtag_compare_pt->AddEntry(hist_QCD_noBtag_topTagEffPt,"QCD - No b-tagging","LPE");
  lBtag_compare_pt->AddEntry(hist_QCD_looseBtag_topTagEffPt,"QCD - Loose b-tagging","LPE");
  lBtag_compare_pt->AddEntry(hist_QCD_mediumBtag_topTagEffPt,"QCD - Medium b-tagging","LPE");
  lBtag_compare_pt->Draw("SAME");
  lBtag_compare_pt->SetFillColor(kWhite);
  
  //ZPrime/weighted FLAT QCD 1D comparisons
  TCanvas* cBtag_compare_FLAT_weighted_npv = new TCanvas("Btag comparison - Efficiency vs Npv(QCD FLAT/ZPrime)");
  hist_QCD_FLAT_weighted_noBtag_topTagEffNpv_400->Draw();
  hist_QCD_FLAT_weighted_noBtag_topTagEffNpv_400->SetMinimum(0.0001);
  hist_QCD_FLAT_weighted_noBtag_topTagEffNpv_400->SetMaximum(5.0);
  hist_ZPrime_noBtag_topTagEffNpv_400->Draw("ESAME");
  hist_ZPrime_noBtag_topTagEffNpv_400->SetMinimum(0.0001);
  hist_ZPrime_noBtag_topTagEffNpv_400->SetMaximum(5.0);
  hist_QCD_FLAT_weighted_noBtag_topTagEffNpv_400->SetTitle("Efficiency vs Npv - ZPrime/QCD Comparison (Pt > 400 GeV)");
  hist_QCD_FLAT_weighted_noBtag_topTagEffNpv_400->SetLineColor(kBlue+3);
  hist_ZPrime_noBtag_topTagEffNpv_400->SetLineColor(kOrange+9);
  cBtag_compare_FLAT_weighted_npv->SetLogy();

  //TCanvas* cLooseBtag_compare_FLAT_weighted_npv = new TCanvas("Loose Btag efficiency - npv");
  hist_QCD_FLAT_weighted_looseBtag_topTagEffNpv_400->Draw("ESAME");
  hist_QCD_FLAT_weighted_looseBtag_topTagEffNpv_400->SetMinimum(0.0001);
  hist_QCD_FLAT_weighted_looseBtag_topTagEffNpv_400->SetMaximum(5.0);
  hist_ZPrime_looseBtag_topTagEffNpv_400->Draw("ESAME");
  hist_ZPrime_looseBtag_topTagEffNpv_400->SetMinimum(0.0001);
  hist_ZPrime_looseBtag_topTagEffNpv_400->SetMaximum(5.0);
  hist_QCD_FLAT_weighted_looseBtag_topTagEffNpv_400->SetLineColor(kBlue+10);
  hist_ZPrime_looseBtag_topTagEffNpv_400->SetLineColor(kOrange+10);

  //TCanvas* cMediumBtag_compare_FLAT_weighted_npv = new TCanvas("Medium Btag efficiency - npv");
  hist_QCD_FLAT_weighted_mediumBtag_topTagEffNpv_400->Draw("ESAME");
  hist_QCD_FLAT_weighted_mediumBtag_topTagEffNpv_400->SetMinimum(0.0001);
  hist_QCD_FLAT_weighted_mediumBtag_topTagEffNpv_400->SetMaximum(5.0);
  hist_ZPrime_mediumBtag_topTagEffNpv_400->Draw("ESAME");
  hist_ZPrime_mediumBtag_topTagEffNpv_400->SetMinimum(0.0001);
  hist_ZPrime_mediumBtag_topTagEffNpv_400->SetMaximum(5.0);
  hist_QCD_FLAT_weighted_mediumBtag_topTagEffNpv_400->SetLineColor(kBlue-7);
  hist_ZPrime_mediumBtag_topTagEffNpv_400->SetLineColor(kOrange+6);

  TLegend* lBtag_compare_FLAT_weighted_npv = new TLegend(0.7,0.7,0.9,0.9);
  lBtag_compare_FLAT_weighted_npv->AddEntry(hist_ZPrime_noBtag_topTagEffNpv_400,"Z Prime - No b-tagging","LPE");
  lBtag_compare_FLAT_weighted_npv->AddEntry(hist_ZPrime_looseBtag_topTagEffNpv_400,"Z Prime - Loose b-tagging","LPE");
  lBtag_compare_FLAT_weighted_npv->AddEntry(hist_ZPrime_mediumBtag_topTagEffNpv_400,"Z Prime - Medium b-tagging","LPE");
  lBtag_compare_FLAT_weighted_npv->AddEntry(hist_QCD_FLAT_weighted_noBtag_topTagEffNpv_400,"QCD - No b-tagging","LPE");
  lBtag_compare_FLAT_weighted_npv->AddEntry(hist_QCD_FLAT_weighted_looseBtag_topTagEffNpv_400,"QCD - Loose b-tagging","LPE");
  lBtag_compare_FLAT_weighted_npv->AddEntry(hist_QCD_FLAT_weighted_mediumBtag_topTagEffNpv_400,"QCD - Medium b-tagging","LPE");
  lBtag_compare_FLAT_weighted_npv->Draw("SAME");
  lBtag_compare_FLAT_weighted_npv->SetFillColor(kWhite);

  TCanvas* cBtag_compare_FLAT_weighted_pt = new TCanvas("Btag comparison - Efficiency vs Pt (QCD FLAT/ZPrime)");
  hist_QCD_FLAT_weighted_noBtag_topTagEffPt->Draw();
  hist_QCD_FLAT_weighted_noBtag_topTagEffPt->SetMinimum(0.0001);
  hist_QCD_FLAT_weighted_noBtag_topTagEffPt->SetMaximum(5.0);
  hist_ZPrime_noBtag_topTagEffPt->Draw("ESAME");
  hist_ZPrime_noBtag_topTagEffPt->SetMinimum(0.0001);
  hist_ZPrime_noBtag_topTagEffPt->SetMaximum(5.0);
  hist_QCD_FLAT_weighted_noBtag_topTagEffPt->SetTitle("Efficiency vs Pt - ZPrime/QCD Comparison");
  hist_QCD_FLAT_weighted_noBtag_topTagEffPt->SetLineColor(kBlue+3);
  hist_ZPrime_noBtag_topTagEffPt->SetLineColor(kOrange+9);
  cBtag_compare_FLAT_weighted_pt->SetLogy();

  //TCanvas* cLooseBtag_compare_FLAT_weighted_pt = new TCanvas("Loose Btag efficiency - pt");
  hist_QCD_FLAT_weighted_looseBtag_topTagEffPt->Draw("ESAME");
  hist_QCD_FLAT_weighted_looseBtag_topTagEffPt->SetMinimum(0.0001);
  hist_QCD_FLAT_weighted_looseBtag_topTagEffPt->SetMaximum(5.0);
  hist_ZPrime_looseBtag_topTagEffPt->Draw("ESAME");
  hist_ZPrime_looseBtag_topTagEffPt->SetMinimum(0.0001);
  hist_ZPrime_looseBtag_topTagEffPt->SetMaximum(5.0);
  hist_QCD_FLAT_weighted_looseBtag_topTagEffPt->SetLineColor(kBlue+10);
  hist_ZPrime_looseBtag_topTagEffPt->SetLineColor(kOrange+10);

  //TCanvas* cMediumBtag_compare_FLAT_weighted_pt = new TCanvas("Medium Btag efficiency - pt");
  hist_QCD_FLAT_weighted_mediumBtag_topTagEffPt->Draw("ESAME");
  hist_QCD_FLAT_weighted_mediumBtag_topTagEffPt->SetMinimum(0.0001);
  hist_QCD_FLAT_weighted_mediumBtag_topTagEffPt->SetMaximum(5.0);
  hist_ZPrime_mediumBtag_topTagEffPt->Draw("ESAME");
  hist_ZPrime_mediumBtag_topTagEffPt->SetMinimum(0.0001);
  hist_ZPrime_mediumBtag_topTagEffPt->SetMaximum(5.0);
  hist_QCD_FLAT_weighted_mediumBtag_topTagEffPt->SetLineColor(kBlue-7);
  hist_ZPrime_mediumBtag_topTagEffPt->SetLineColor(kOrange+6);

  TLegend* lBtag_compare_FLAT_weighted_pt = new TLegend(0.7,0.7,0.9,0.9);
  lBtag_compare_FLAT_weighted_pt->AddEntry(hist_ZPrime_noBtag_topTagEffPt,"Z Prime - No b-tagging","LPE");
  lBtag_compare_FLAT_weighted_pt->AddEntry(hist_ZPrime_looseBtag_topTagEffPt,"Z Prime - Loose b-tagging","LPE");
  lBtag_compare_FLAT_weighted_pt->AddEntry(hist_ZPrime_mediumBtag_topTagEffPt,"Z Prime - Medium b-tagging","LPE");
  lBtag_compare_FLAT_weighted_pt->AddEntry(hist_QCD_FLAT_weighted_noBtag_topTagEffPt,"QCD - No b-tagging","LPE");
  lBtag_compare_FLAT_weighted_pt->AddEntry(hist_QCD_FLAT_weighted_looseBtag_topTagEffPt,"QCD - Loose b-tagging","LPE");
  lBtag_compare_FLAT_weighted_pt->AddEntry(hist_QCD_FLAT_weighted_mediumBtag_topTagEffPt,"QCD - Medium b-tagging","LPE");
  lBtag_compare_FLAT_weighted_pt->Draw("SAME");
  lBtag_compare_FLAT_weighted_pt->SetFillColor(kWhite);
  */
  TCanvas* cMassGroom_compare_npv = new TCanvas("Mass Grooming comparison - Efficiency vs Npv(QCD/ZPrime)");
  hist_QCD_noBtag_topTagEffNpv_400->Draw();
  hist_QCD_noBtag_topTagEffNpv_400->SetMinimum(0.001);
  hist_QCD_noBtag_topTagEffNpv_400->SetMaximum(10.0);
  hist_ZPrime_noBtag_topTagEffNpv_400->Draw("ESAME");
  hist_ZPrime_noBtag_topTagEffNpv_400->SetMinimum(0.001);
  hist_ZPrime_noBtag_topTagEffNpv_400->SetMaximum(10.0);
  //hist_QCD_noBtag_topTagEffNpv_400->SetTitle("Efficiency vs Npv - ZPrime/QCD Comparison (Pt > 400 GeV)");
  hist_QCD_noBtag_topTagEffNpv_400->SetLineWidth(2);
  hist_QCD_noBtag_topTagEffNpv_400->SetLineStyle(2);
  hist_QCD_noBtag_topTagEffNpv_400->SetLineColor(kRed-3);
  hist_ZPrime_noBtag_topTagEffNpv_400->SetLineColor(kRed-3);
  cMassGroom_compare_npv->SetLogy();

  //TCanvas* cLooseMassGroom_compare_npv = new TCanvas("Filtered Mass efficiency - npv");
  hist_QCD_filtered_noBtag_topTagEffNpv_400->Draw("ESAME");
  hist_QCD_filtered_noBtag_topTagEffNpv_400->SetMinimum(0.001);
  hist_QCD_filtered_noBtag_topTagEffNpv_400->SetMaximum(10.0);
  hist_ZPrime_filtered_noBtag_topTagEffNpv_400->Draw("ESAME");
  hist_ZPrime_filtered_noBtag_topTagEffNpv_400->SetMinimum(0.001);
  hist_ZPrime_filtered_noBtag_topTagEffNpv_400->SetMaximum(10.0);
  hist_QCD_filtered_noBtag_topTagEffNpv_400->SetLineWidth(2);
  hist_QCD_filtered_noBtag_topTagEffNpv_400->SetLineStyle(2);
  hist_QCD_filtered_noBtag_topTagEffNpv_400->SetLineColor(kAzure+3);
  hist_ZPrime_filtered_noBtag_topTagEffNpv_400->SetLineColor(kAzure+3);

  //TCanvas* cLooseMassGroom_compare_npv = new TCanvas("Pruned Mass efficiency - npv");
  hist_QCD_pruned_noBtag_topTagEffNpv_400->Draw("ESAME");
  hist_QCD_pruned_noBtag_topTagEffNpv_400->SetMinimum(0.001);
  hist_QCD_pruned_noBtag_topTagEffNpv_400->SetMaximum(10.0);
  hist_ZPrime_pruned_noBtag_topTagEffNpv_400->Draw("ESAME");
  hist_ZPrime_pruned_noBtag_topTagEffNpv_400->SetMinimum(0.001);
  hist_ZPrime_pruned_noBtag_topTagEffNpv_400->SetMaximum(10.0);
  hist_QCD_pruned_noBtag_topTagEffNpv_400->SetLineWidth(2);
  hist_QCD_pruned_noBtag_topTagEffNpv_400->SetLineStyle(2);
  hist_QCD_pruned_noBtag_topTagEffNpv_400->SetLineColor(kTeal-6);
  hist_ZPrime_pruned_noBtag_topTagEffNpv_400->SetLineColor(kTeal-6);

  //TCanvas* cLooseMassGroom_compare_npv = new TCanvas("Trimmed Mass efficiency - npv");
  hist_QCD_trimmed_noBtag_topTagEffNpv_400->Draw("ESAME");
  hist_QCD_trimmed_noBtag_topTagEffNpv_400->SetMinimum(0.001);
  hist_QCD_trimmed_noBtag_topTagEffNpv_400->SetMaximum(10.0);
  hist_ZPrime_trimmed_noBtag_topTagEffNpv_400->Draw("ESAME");
  hist_ZPrime_trimmed_noBtag_topTagEffNpv_400->SetMinimum(0.001);
  hist_ZPrime_trimmed_noBtag_topTagEffNpv_400->SetMaximum(10.0);
  hist_QCD_trimmed_noBtag_topTagEffNpv_400->SetLineWidth(2);
  hist_QCD_trimmed_noBtag_topTagEffNpv_400->SetLineStyle(2);
  hist_QCD_trimmed_noBtag_topTagEffNpv_400->SetLineColor(kOrange);
  hist_ZPrime_trimmed_noBtag_topTagEffNpv_400->SetLineColor(kOrange);

  TLegend* lMassGroom_compare_npv = new TLegend(0.7,0.7,0.9,0.9);
  lMassGroom_compare_npv->AddEntry(hist_ZPrime_noBtag_topTagEffNpv_400,"Z Prime - No Mass Grooming","LPE");
  lMassGroom_compare_npv->AddEntry(hist_ZPrime_filtered_noBtag_topTagEffNpv_400,"Z Prime - Filtered AK8 Jets","LPE");
  lMassGroom_compare_npv->AddEntry(hist_ZPrime_pruned_noBtag_topTagEffNpv_400,"Z Prime - Pruned AK8 Jets","LPE");
  lMassGroom_compare_npv->AddEntry(hist_ZPrime_trimmed_noBtag_topTagEffNpv_400,"Z Prime - Trimmed AK8 Jets","LPE");
  lMassGroom_compare_npv->AddEntry(hist_QCD_noBtag_topTagEffNpv_400,"QCD - No Mass Grooming","LPE");
  lMassGroom_compare_npv->AddEntry(hist_QCD_filtered_noBtag_topTagEffNpv_400,"QCD - Filtered AK8 Jets","LPE");
  lMassGroom_compare_npv->AddEntry(hist_QCD_pruned_noBtag_topTagEffNpv_400,"QCD - Pruned AK8 Jets","LPE");
  lMassGroom_compare_npv->AddEntry(hist_QCD_trimmed_noBtag_topTagEffNpv_400,"QCD - Trimmed AK8 Jets","LPE");
  lMassGroom_compare_npv->Draw("SAME");
  lMassGroom_compare_npv->SetFillColor(kWhite);

  cMassGroom_compare_npv->SaveAs("topTagEfficiencyNpv_ZPrime_QCD_pt1800to2400_13TeV_MassGroomCompare.root");
 

  TCanvas* cMassGroom_compare_pt = new TCanvas("Mass Grooming comparison - Efficiency vs Pt(QCD/ZPrime)");
  hist_QCD_noBtag_topTagEffPt->Draw();
  hist_QCD_noBtag_topTagEffPt->SetMinimum(0.0001);
  hist_QCD_noBtag_topTagEffPt->SetMaximum(10.0);
  hist_ZPrime_noBtag_topTagEffPt->Draw("ESAME");
  hist_ZPrime_noBtag_topTagEffPt->SetMinimum(0.0001);
  hist_ZPrime_noBtag_topTagEffPt->SetMaximum(10.0);
  hist_QCD_noBtag_topTagEffPt->SetLineWidth(2);
  hist_QCD_noBtag_topTagEffPt->SetLineStyle(2);
  //hist_QCD_noBtag_topTagEffPt->SetTitle("Efficiency vs Pt - ZPrime/QCD Comparison");
  hist_QCD_noBtag_topTagEffPt->SetLineColor(kRed-3);
  hist_ZPrime_noBtag_topTagEffPt->SetLineColor(kRed-3);
  cMassGroom_compare_pt->SetLogy();

  //TCanvas* cLooseMassGroom_compare_pt = new TCanvas("Filtered Mass efficiency - pt");
  hist_QCD_filtered_noBtag_topTagEffPt->Draw("ESAME");
  hist_QCD_filtered_noBtag_topTagEffPt->SetMinimum(0.0001);
  hist_QCD_filtered_noBtag_topTagEffPt->SetMaximum(10.0);
  hist_ZPrime_filtered_noBtag_topTagEffPt->Draw("ESAME");
  hist_ZPrime_filtered_noBtag_topTagEffPt->SetMinimum(0.0001);
  hist_ZPrime_filtered_noBtag_topTagEffPt->SetMaximum(10.0);
  hist_QCD_filtered_noBtag_topTagEffPt->SetLineWidth(2);
  hist_QCD_filtered_noBtag_topTagEffPt->SetLineStyle(2);
  hist_QCD_filtered_noBtag_topTagEffPt->SetLineColor(kAzure+3);
  hist_ZPrime_filtered_noBtag_topTagEffPt->SetLineColor(kAzure+3);

  //TCanvas* cLooseMassGroom_compare_pt = new TCanvas("Pruned Mass efficiency - pt");
  hist_QCD_pruned_noBtag_topTagEffPt->Draw("ESAME");
  hist_QCD_pruned_noBtag_topTagEffPt->SetMinimum(0.0001);
  hist_QCD_pruned_noBtag_topTagEffPt->SetMaximum(10.0);
  hist_ZPrime_pruned_noBtag_topTagEffPt->Draw("ESAME");
  hist_ZPrime_pruned_noBtag_topTagEffPt->SetMinimum(0.0001);
  hist_ZPrime_pruned_noBtag_topTagEffPt->SetMaximum(10.0);
  hist_QCD_pruned_noBtag_topTagEffPt->SetLineWidth(2);
  hist_QCD_pruned_noBtag_topTagEffPt->SetLineStyle(2);
  hist_QCD_pruned_noBtag_topTagEffPt->SetLineColor(kTeal-6);
  hist_ZPrime_pruned_noBtag_topTagEffPt->SetLineColor(kTeal-6);

  //TCanvas* cLooseMassGroom_compare_pt = new TCanvas("Trimmed Mass efficiency - pt");
  hist_QCD_trimmed_noBtag_topTagEffPt->Draw("ESAME");
  hist_QCD_trimmed_noBtag_topTagEffPt->SetMinimum(0.0001);
  hist_QCD_trimmed_noBtag_topTagEffPt->SetMaximum(10.0);
  hist_ZPrime_trimmed_noBtag_topTagEffPt->Draw("ESAME");
  hist_ZPrime_trimmed_noBtag_topTagEffPt->SetMinimum(0.0001);
  hist_ZPrime_trimmed_noBtag_topTagEffPt->SetMaximum(10.0);
  hist_QCD_trimmed_noBtag_topTagEffPt->SetLineWidth(2);
  hist_QCD_trimmed_noBtag_topTagEffPt->SetLineStyle(2);
  hist_QCD_trimmed_noBtag_topTagEffPt->SetLineColor(kOrange);
  hist_ZPrime_trimmed_noBtag_topTagEffPt->SetLineColor(kOrange);

  TLegend* lMassGroom_compare_pt = new TLegend(0.7,0.7,0.9,0.9);
  lMassGroom_compare_pt->AddEntry(hist_ZPrime_noBtag_topTagEffPt,"Z Prime - No Mass Grooming","LPE");
  lMassGroom_compare_pt->AddEntry(hist_ZPrime_filtered_noBtag_topTagEffPt,"Z Prime - Filtered AK8 Jets","LPE");
  lMassGroom_compare_pt->AddEntry(hist_ZPrime_pruned_noBtag_topTagEffPt,"Z Prime - Pruned AK8 Jets","LPE");
  lMassGroom_compare_pt->AddEntry(hist_ZPrime_trimmed_noBtag_topTagEffPt,"Z Prime - Trimmed AK8 Jets","LPE");
  lMassGroom_compare_pt->AddEntry(hist_QCD_noBtag_topTagEffPt,"QCD - No Mass Grooming","LPE");
  lMassGroom_compare_pt->AddEntry(hist_QCD_filtered_noBtag_topTagEffPt,"QCD - Filtered AK8 Jets","LPE");
  lMassGroom_compare_pt->AddEntry(hist_QCD_pruned_noBtag_topTagEffPt,"QCD - Pruned AK8 Jets","LPE");
  lMassGroom_compare_pt->AddEntry(hist_QCD_trimmed_noBtag_topTagEffPt,"QCD - Trimmed AK8 Jets","LPE");
  lMassGroom_compare_pt->Draw("SAME");
  lMassGroom_compare_pt->SetFillColor(kWhite);

  cMassGroom_compare_pt->SaveAs("topTagEfficiencyPt_ZPrime_QCD_pt1800to2400_13TeV_MassGroomCompare.root");
  /*  
  //ZPrime/unweighted FLAT QCD 1D comparisons 
  TCanvas* cBtag_compare_FLAT_npv = new TCanvas("Btag comparison - Efficiency vs Npv(QCD FLAT, unweighted/ZPrime)");
  hist_QCD_FLAT_noBtag_topTagEffNpv_400->Draw();
  hist_QCD_FLAT_noBtag_topTagEffNpv_400->SetMinimum(0.0001);
  hist_QCD_FLAT_noBtag_topTagEffNpv_400->SetMaximum(5.0);
  hist_ZPrime_noBtag_topTagEffNpv_400->Draw("ESAME");
  hist_ZPrime_noBtag_topTagEffNpv_400->SetMinimum(0.0001);
  hist_ZPrime_noBtag_topTagEffNpv_400->SetMaximum(5.0);
  hist_QCD_FLAT_noBtag_topTagEffNpv_400->SetTitle("Efficiency vs Npv - ZPrime/QCD Comparison (Pt > 400 GeV)");
  hist_QCD_FLAT_noBtag_topTagEffNpv_400->SetLineColor(kBlue+3);
  hist_ZPrime_noBtag_topTagEffNpv_400->SetLineColor(kOrange+9);
  cBtag_compare_FLAT_npv->SetLogy();

  //TCanvas* cLooseBtag_compare_FLAT_npv = new TCanvas("Loose Btag efficiency - npv");
  hist_QCD_FLAT_looseBtag_topTagEffNpv_400->Draw("ESAME");
  hist_QCD_FLAT_looseBtag_topTagEffNpv_400->SetMinimum(0.0001);
  hist_QCD_FLAT_looseBtag_topTagEffNpv_400->SetMaximum(5.0);
  hist_ZPrime_looseBtag_topTagEffNpv_400->Draw("ESAME");
  hist_ZPrime_looseBtag_topTagEffNpv_400->SetMinimum(0.0001);
  hist_ZPrime_looseBtag_topTagEffNpv_400->SetMaximum(5.0);
  hist_QCD_FLAT_looseBtag_topTagEffNpv_400->SetLineColor(kBlue+10);
  hist_ZPrime_looseBtag_topTagEffNpv_400->SetLineColor(kOrange+10);

  //TCanvas* cMediumBtag_compare_FLAT_npv = new TCanvas("Medium Btag efficiency - npv");
  hist_QCD_FLAT_mediumBtag_topTagEffNpv_400->Draw("ESAME");
  hist_QCD_FLAT_mediumBtag_topTagEffNpv_400->SetMinimum(0.0001);
  hist_QCD_FLAT_mediumBtag_topTagEffNpv_400->SetMaximum(5.0);
  hist_ZPrime_mediumBtag_topTagEffNpv_400->Draw("ESAME");
  hist_ZPrime_mediumBtag_topTagEffNpv_400->SetMinimum(0.0001);
  hist_ZPrime_mediumBtag_topTagEffNpv_400->SetMaximum(5.0);
  hist_QCD_FLAT_mediumBtag_topTagEffNpv_400->SetLineColor(kBlue-7);
  hist_ZPrime_mediumBtag_topTagEffNpv_400->SetLineColor(kOrange+6);

  TLegend* lBtag_compare_FLAT_npv = new TLegend(0.7,0.7,0.9,0.9);
  lBtag_compare_FLAT_npv->AddEntry(hist_ZPrime_noBtag_topTagEffNpv_400,"Z Prime - No b-tagging","LPE");
  lBtag_compare_FLAT_npv->AddEntry(hist_ZPrime_looseBtag_topTagEffNpv_400,"Z Prime - Loose b-tagging","LPE");
  lBtag_compare_FLAT_npv->AddEntry(hist_ZPrime_mediumBtag_topTagEffNpv_400,"Z Prime - Medium b-tagging","LPE");
  lBtag_compare_FLAT_npv->AddEntry(hist_QCD_FLAT_noBtag_topTagEffNpv_400,"QCD - No b-tagging","LPE");
  lBtag_compare_FLAT_npv->AddEntry(hist_QCD_FLAT_looseBtag_topTagEffNpv_400,"QCD - Loose b-tagging","LPE");
  lBtag_compare_FLAT_npv->AddEntry(hist_QCD_FLAT_mediumBtag_topTagEffNpv_400,"QCD - Medium b-tagging","LPE");
  lBtag_compare_FLAT_npv->Draw("SAME");
  lBtag_compare_FLAT_npv->SetFillColor(kWhite);

  TCanvas* cBtag_compare_FLAT_pt = new TCanvas("Btag comparison - Efficiency vs Pt (QCD FLAT, unweighted/ZPrime)");
  hist_QCD_FLAT_noBtag_topTagEffPt->Draw();
  hist_QCD_FLAT_noBtag_topTagEffPt->SetMinimum(0.0001);
  hist_QCD_FLAT_noBtag_topTagEffPt->SetMaximum(5.0);
  hist_ZPrime_noBtag_topTagEffPt->Draw("ESAME");
  hist_ZPrime_noBtag_topTagEffPt->SetMinimum(0.0001);
  hist_ZPrime_noBtag_topTagEffPt->SetMaximum(5.0);
  hist_QCD_FLAT_noBtag_topTagEffPt->SetTitle("Efficiency vs Pt - ZPrime/QCD Comparison");
  hist_QCD_FLAT_noBtag_topTagEffPt->SetLineColor(kBlue+3);
  hist_ZPrime_noBtag_topTagEffPt->SetLineColor(kOrange+9);
  cBtag_compare_FLAT_pt->SetLogy();

  //TCanvas* cLooseBtag_compare_FLAT_pt = new TCanvas("Loose Btag efficiency - pt");
  hist_QCD_FLAT_looseBtag_topTagEffPt->Draw("ESAME");
  hist_QCD_FLAT_looseBtag_topTagEffPt->SetMinimum(0.0001);
  hist_QCD_FLAT_looseBtag_topTagEffPt->SetMaximum(5.0);
  hist_ZPrime_looseBtag_topTagEffPt->Draw("ESAME");
  hist_ZPrime_looseBtag_topTagEffPt->SetMinimum(0.0001);
  hist_ZPrime_looseBtag_topTagEffPt->SetMaximum(5.0);
  hist_QCD_FLAT_looseBtag_topTagEffPt->SetLineColor(kBlue+10);
  hist_ZPrime_looseBtag_topTagEffPt->SetLineColor(kOrange+10);

  //TCanvas* cMediumBtag_compare_FLAT_pt = new TCanvas("Medium Btag efficiency - pt");
  hist_QCD_FLAT_mediumBtag_topTagEffPt->Draw("ESAME");
  hist_QCD_FLAT_mediumBtag_topTagEffPt->SetMinimum(0.0001);
  hist_QCD_FLAT_mediumBtag_topTagEffPt->SetMaximum(5.0);
  hist_ZPrime_mediumBtag_topTagEffPt->Draw("ESAME");
  hist_ZPrime_mediumBtag_topTagEffPt->SetMinimum(0.0001);
  hist_ZPrime_mediumBtag_topTagEffPt->SetMaximum(5.0);
  hist_QCD_FLAT_mediumBtag_topTagEffPt->SetLineColor(kBlue-7);
  hist_ZPrime_mediumBtag_topTagEffPt->SetLineColor(kOrange+6);

  TLegend* lBtag_compare_FLAT_pt = new TLegend(0.7,0.7,0.9,0.9);
  lBtag_compare_FLAT_pt->AddEntry(hist_ZPrime_noBtag_topTagEffPt,"Z Prime - No b-tagging","LPE");
  lBtag_compare_FLAT_pt->AddEntry(hist_ZPrime_looseBtag_topTagEffPt,"Z Prime - Loose b-tagging","LPE");
  lBtag_compare_FLAT_pt->AddEntry(hist_ZPrime_mediumBtag_topTagEffPt,"Z Prime - Medium b-tagging","LPE");
  lBtag_compare_FLAT_pt->AddEntry(hist_QCD_FLAT_noBtag_topTagEffPt,"QCD - No b-tagging","LPE");
  lBtag_compare_FLAT_pt->AddEntry(hist_QCD_FLAT_looseBtag_topTagEffPt,"QCD - Loose b-tagging","LPE");
  lBtag_compare_FLAT_pt->AddEntry(hist_QCD_FLAT_mediumBtag_topTagEffPt,"QCD - Medium b-tagging","LPE");
  lBtag_compare_FLAT_pt->Draw("SAME");
  lBtag_compare_FLAT_pt->SetFillColor(kWhite);
  
  TCanvas* cMassGroom_compare_FLAT_npv = new TCanvas("Mass Grooming comparison - Efficiency vs Npv(QCD FLAT, unweighted/ZPrime)");
  hist_QCD_FLAT_noBtag_topTagEffNpv_400->Draw();
  hist_QCD_FLAT_noBtag_topTagEffNpv_400->SetMinimum(0.001);
  hist_QCD_FLAT_noBtag_topTagEffNpv_400->SetMaximum(10.0);
  hist_ZPrime_noBtag_topTagEffNpv_400->Draw("ESAME");
  hist_ZPrime_noBtag_topTagEffNpv_400->SetMinimum(0.001);
  hist_ZPrime_noBtag_topTagEffNpv_400->SetMaximum(10.0);
  hist_QCD_FLAT_noBtag_topTagEffNpv_400->SetTitle("Efficiency vs Npv - ZPrime/QCD Comparison (Pt > 400 GeV)");
  hist_QCD_FLAT_noBtag_topTagEffNpv_400->SetLineColor(kBlue+3);
  hist_ZPrime_noBtag_topTagEffNpv_400->SetLineColor(kOrange+9);
  cMassGroom_compare_FLAT_npv->SetLogy();

  //TCanvas* cLooseMassGroom_compare_FLAT_npv = new TCanvas("Filtered Mass efficiency - npv");
  hist_QCD_FLAT_filtered_noBtag_topTagEffNpv_400->Draw("ESAME");
  hist_QCD_FLAT_filtered_noBtag_topTagEffNpv_400->SetMinimum(0.001);
  hist_QCD_FLAT_filtered_noBtag_topTagEffNpv_400->SetMaximum(10.0);
  hist_ZPrime_filtered_noBtag_topTagEffNpv_400->Draw("ESAME");
  hist_ZPrime_filtered_noBtag_topTagEffNpv_400->SetMinimum(0.001);
  hist_ZPrime_filtered_noBtag_topTagEffNpv_400->SetMaximum(10.0);
  hist_QCD_FLAT_filtered_noBtag_topTagEffNpv_400->SetLineColor(kBlue+10);
  hist_ZPrime_filtered_noBtag_topTagEffNpv_400->SetLineColor(kOrange+10);

  //TCanvas* cLooseMassGroom_compare_FLAT_npv = new TCanvas("Pruned Mass efficiency - npv");
  hist_QCD_FLAT_pruned_noBtag_topTagEffNpv_400->Draw("ESAME");
  hist_QCD_FLAT_pruned_noBtag_topTagEffNpv_400->SetMinimum(0.001);
  hist_QCD_FLAT_pruned_noBtag_topTagEffNpv_400->SetMaximum(10.0);
  hist_ZPrime_pruned_noBtag_topTagEffNpv_400->Draw("ESAME");
  hist_ZPrime_pruned_noBtag_topTagEffNpv_400->SetMinimum(0.001);
  hist_ZPrime_pruned_noBtag_topTagEffNpv_400->SetMaximum(10.0);
  hist_QCD_FLAT_pruned_noBtag_topTagEffNpv_400->SetLineColor(kBlue-7);
  hist_ZPrime_pruned_noBtag_topTagEffNpv_400->SetLineColor(kOrange+6);

  //TCanvas* cLooseMassGroom_compare_FLAT_npv = new TCanvas("Trimmed Mass efficiency - npv");
  hist_QCD_FLAT_trimmed_noBtag_topTagEffNpv_400->Draw("ESAME");
  hist_QCD_FLAT_trimmed_noBtag_topTagEffNpv_400->SetMinimum(0.001);
  hist_QCD_FLAT_trimmed_noBtag_topTagEffNpv_400->SetMaximum(10.0);
  hist_ZPrime_trimmed_noBtag_topTagEffNpv_400->Draw("ESAME");
  hist_ZPrime_trimmed_noBtag_topTagEffNpv_400->SetMinimum(0.001);
  hist_ZPrime_trimmed_noBtag_topTagEffNpv_400->SetMaximum(10.0);
  hist_QCD_FLAT_trimmed_noBtag_topTagEffNpv_400->SetLineColor(kCyan+1);
  hist_ZPrime_trimmed_noBtag_topTagEffNpv_400->SetLineColor(kOrange);

  TLegend* lMassGroom_compare_FLAT_npv = new TLegend(0.65,0.7,0.9,0.9);
  lMassGroom_compare_FLAT_npv->AddEntry(hist_ZPrime_noBtag_topTagEffNpv_400,"Z Prime - No Mass Grooming","LPE");
  lMassGroom_compare_FLAT_npv->AddEntry(hist_ZPrime_filtered_noBtag_topTagEffNpv_400,"Z Prime - Filtered AK8 Jets","LPE");
  lMassGroom_compare_FLAT_npv->AddEntry(hist_ZPrime_pruned_noBtag_topTagEffNpv_400,"Z Prime - Pruned AK8 Jets","LPE");
  lMassGroom_compare_FLAT_npv->AddEntry(hist_ZPrime_trimmed_noBtag_topTagEffNpv_400,"Z Prime - Trimmed AK8 Jets","LPE");
  lMassGroom_compare_FLAT_npv->AddEntry(hist_QCD_FLAT_noBtag_topTagEffNpv_400,"QCD - No Mass Grooming","LPE");
  lMassGroom_compare_FLAT_npv->AddEntry(hist_QCD_FLAT_filtered_noBtag_topTagEffNpv_400,"QCD - Filtered AK8 Jets","LPE");
  lMassGroom_compare_FLAT_npv->AddEntry(hist_QCD_FLAT_pruned_noBtag_topTagEffNpv_400,"QCD - Pruned AK8 Jets","LPE");
  lMassGroom_compare_FLAT_npv->AddEntry(hist_QCD_FLAT_trimmed_noBtag_topTagEffNpv_400,"QCD - Trimmed AK8 Jets","LPE");
  lMassGroom_compare_FLAT_npv->Draw("SAME");
  lMassGroom_compare_FLAT_npv->SetFillColor(kWhite);
  
  TCanvas* cMassGroom_compare_FLAT_pt = new TCanvas("Mass Grooming comparison - Efficiency vs Pt(QCD FLAT, unweighted/ZPrime)");
  hist_QCD_FLAT_noBtag_topTagEffPt->Draw();
  hist_QCD_FLAT_noBtag_topTagEffPt->SetMinimum(0.0001);
  hist_QCD_FLAT_noBtag_topTagEffPt->SetMaximum(10.0);
  hist_ZPrime_noBtag_topTagEffPt->Draw("ESAME");
  hist_ZPrime_noBtag_topTagEffPt->SetMinimum(0.0001);
  hist_ZPrime_noBtag_topTagEffPt->SetMaximum(10.0);
  hist_QCD_FLAT_noBtag_topTagEffPt->SetTitle("Efficiency vs Pt - ZPrime/QCD Comparison");
  hist_QCD_FLAT_noBtag_topTagEffPt->SetLineColor(kBlue+3);
  hist_ZPrime_noBtag_topTagEffPt->SetLineColor(kOrange+9);
  cMassGroom_compare_FLAT_pt->SetLogy();

  //TCanvas* cLooseMassGroom_compare_FLAT_pt = new TCanvas("Filtered Mass efficiency - pt");
  hist_QCD_FLAT_filtered_noBtag_topTagEffPt->Draw("ESAME");
  hist_QCD_FLAT_filtered_noBtag_topTagEffPt->SetMinimum(0.0001);
  hist_QCD_FLAT_filtered_noBtag_topTagEffPt->SetMaximum(10.0);
  hist_ZPrime_filtered_noBtag_topTagEffPt->Draw("ESAME");
  hist_ZPrime_filtered_noBtag_topTagEffPt->SetMinimum(0.0001);
  hist_ZPrime_filtered_noBtag_topTagEffPt->SetMaximum(10.0);
  hist_QCD_FLAT_filtered_noBtag_topTagEffPt->SetLineColor(kBlue+10);
  hist_ZPrime_filtered_noBtag_topTagEffPt->SetLineColor(kOrange+10);

  //TCanvas* cLooseMassGroom_compare_FLAT_pt = new TCanvas("Pruned Mass efficiency - pt");
  hist_QCD_FLAT_pruned_noBtag_topTagEffPt->Draw("ESAME");
  hist_QCD_FLAT_pruned_noBtag_topTagEffPt->SetMinimum(0.0001);
  hist_QCD_FLAT_pruned_noBtag_topTagEffPt->SetMaximum(10.0);
  hist_ZPrime_pruned_noBtag_topTagEffPt->Draw("ESAME");
  hist_ZPrime_pruned_noBtag_topTagEffPt->SetMinimum(0.0001);
  hist_ZPrime_pruned_noBtag_topTagEffPt->SetMaximum(10.0);
  hist_QCD_FLAT_pruned_noBtag_topTagEffPt->SetLineColor(kBlue-7);
  hist_ZPrime_pruned_noBtag_topTagEffPt->SetLineColor(kOrange+6);

  //TCanvas* cLooseMassGroom_compare_FLAT_pt = new TCanvas("Trimmed Mass efficiency - pt");
  hist_QCD_FLAT_trimmed_noBtag_topTagEffPt->Draw("ESAME");
  hist_QCD_FLAT_trimmed_noBtag_topTagEffPt->SetMinimum(0.0001);
  hist_QCD_FLAT_trimmed_noBtag_topTagEffPt->SetMaximum(10.0);
  hist_ZPrime_trimmed_noBtag_topTagEffPt->Draw("ESAME");
  hist_ZPrime_trimmed_noBtag_topTagEffPt->SetMinimum(0.0001);
  hist_ZPrime_trimmed_noBtag_topTagEffPt->SetMaximum(10.0);
  hist_QCD_FLAT_trimmed_noBtag_topTagEffPt->SetLineColor(kCyan+1);
  hist_ZPrime_trimmed_noBtag_topTagEffPt->SetLineColor(kOrange);

  TLegend* lMassGroom_compare_FLAT_pt = new TLegend(0.65,0.7,0.9,0.9);
  lMassGroom_compare_FLAT_pt->AddEntry(hist_ZPrime_noBtag_topTagEffPt,"Z Prime - No Mass Grooming","LPE");
  lMassGroom_compare_FLAT_pt->AddEntry(hist_ZPrime_filtered_noBtag_topTagEffPt,"Z Prime - Filtered AK8 Jets","LPE");
  lMassGroom_compare_FLAT_pt->AddEntry(hist_ZPrime_pruned_noBtag_topTagEffPt,"Z Prime - Pruned AK8 Jets","LPE");
  lMassGroom_compare_FLAT_pt->AddEntry(hist_ZPrime_trimmed_noBtag_topTagEffPt,"Z Prime - Trimmed AK8 Jets","LPE");
  lMassGroom_compare_FLAT_pt->AddEntry(hist_QCD_FLAT_noBtag_topTagEffPt,"QCD - No Mass Grooming","LPE");
  lMassGroom_compare_FLAT_pt->AddEntry(hist_QCD_FLAT_filtered_noBtag_topTagEffPt,"QCD - Filtered AK8 Jets","LPE");
  lMassGroom_compare_FLAT_pt->AddEntry(hist_QCD_FLAT_pruned_noBtag_topTagEffPt,"QCD - Pruned AK8 Jets","LPE");
  lMassGroom_compare_FLAT_pt->AddEntry(hist_QCD_FLAT_trimmed_noBtag_topTagEffPt,"QCD - Trimmed AK8 Jets","LPE");
  lMassGroom_compare_FLAT_pt->Draw("SAME");
  lMassGroom_compare_FLAT_pt->SetFillColor(kWhite);
  
  TCanvas* cZ_pt = new TCanvas("Z Prime Pt efficiency");
  hist_ZPrime_noBtag_topTagEffPt->Draw();
  hist_ZPrime_filtered_noBtag_topTagEffPt->Draw("ESAME");
  hist_ZPrime_filtered_noBtag_topTagEffPt->SetMarkerColor(2);
  hist_ZPrime_filtered_noBtag_topTagEffPt->SetLineColor(2);
  hist_ZPrime_pruned_noBtag_topTagEffPt->Draw("ESAME");
  hist_ZPrime_pruned_noBtag_topTagEffPt->SetMarkerColor(4);
  hist_ZPrime_pruned_noBtag_topTagEffPt->SetLineColor(4);
  hist_ZPrime_trimmed_noBtag_topTagEffPt->Draw("ESAME");
  hist_ZPrime_trimmed_noBtag_topTagEffPt->SetMarkerColor(3);
  hist_ZPrime_trimmed_noBtag_topTagEffPt->SetLineColor(3);

  TLegend* lZ_pt = new TLegend(0.65,0.7,0.9,0.9);
  lZ_pt->AddEntry(hist_ZPrime_noBtag_topTagEffPt,"No Grooming Techniques","LPE");
  lZ_pt->AddEntry(hist_ZPrime_filtered_noBtag_topTagEffPt,"Filtered Jets","LPE");
  lZ_pt->AddEntry(hist_ZPrime_pruned_noBtag_topTagEffPt,"Pruned Jets","LPE");
  lZ_pt->AddEntry(hist_ZPrime_trimmed_noBtag_topTagEffPt,"Trimmed Jets","LPE");
  lZ_pt->SetFillColor(kWhite);
  lZ_pt->Draw("Same");

  TCanvas* cZ_npv = new TCanvas("Z Prime Npv efficiency");
  hist_ZPrime_noBtag_topTagEffNpv->Draw();
  hist_ZPrime_filtered_noBtag_topTagEffNpv->Draw("ESAME");
  hist_ZPrime_filtered_noBtag_topTagEffNpv->SetMarkerColor(2);
  hist_ZPrime_filtered_noBtag_topTagEffNpv->SetLineColor(2);
  hist_ZPrime_pruned_noBtag_topTagEffNpv->Draw("ESAME");
  hist_ZPrime_pruned_noBtag_topTagEffNpv->SetMarkerColor(4);
  hist_ZPrime_pruned_noBtag_topTagEffNpv->SetLineColor(4);
  hist_ZPrime_trimmed_noBtag_topTagEffNpv->Draw("ESAME");
  hist_ZPrime_trimmed_noBtag_topTagEffNpv->SetMarkerColor(3);
  hist_ZPrime_trimmed_noBtag_topTagEffNpv->SetLineColor(3);

  TLegend* lZ_npv = new TLegend(0.65,0.7,0.9,0.9);
  lZ_npv->AddEntry(hist_ZPrime_noBtag_topTagEffNpv,"No Grooming Techniques","LPE");
  lZ_npv->AddEntry(hist_ZPrime_filtered_noBtag_topTagEffNpv,"Filtered Jets","LPE");
  lZ_npv->AddEntry(hist_ZPrime_pruned_noBtag_topTagEffNpv,"Pruned Jets","LPE");
  lZ_npv->AddEntry(hist_ZPrime_trimmed_noBtag_topTagEffNpv,"Trimmed Jets","LPE");
  lZ_npv->SetFillColor(kWhite);
  lZ_npv->Draw("Same");

  TCanvas* cQCD_pt = new TCanvas("QCD Mistag Rate");
  hist_QCD_noBtag_topTagEffPt->Draw();
  hist_QCD_filtered_noBtag_topTagEffPt->Draw("ESAME");
  hist_QCD_filtered_noBtag_topTagEffPt->SetMarkerColor(2);
  hist_QCD_filtered_noBtag_topTagEffPt->SetLineColor(2);
  hist_QCD_pruned_noBtag_topTagEffPt->Draw("ESAME");
  hist_QCD_pruned_noBtag_topTagEffPt->SetMarkerColor(4);
  hist_QCD_pruned_noBtag_topTagEffPt->SetLineColor(4);
  hist_QCD_trimmed_noBtag_topTagEffPt->Draw("ESAME");
  hist_QCD_trimmed_noBtag_topTagEffPt->SetMarkerColor(3);
  hist_QCD_trimmed_noBtag_topTagEffPt->SetLineColor(3);
  hist_QCD_noBtag_topTagEffPt->SetMaximum(0.2);
  hist_QCD_filtered_noBtag_topTagEffPt->SetMaximum(0.2);
  hist_QCD_pruned_noBtag_topTagEffPt->SetMaximum(0.2);
  hist_QCD_trimmed_noBtag_topTagEffPt->SetMaximum(0.2);

  TLegend* lQCD_pt = new TLegend(0.65,0.7,0.9,0.9);
  lQCD_pt->AddEntry(hist_QCD_noBtag_topTagEffPt,"No Grooming Techniques","LPE");
  lQCD_pt->AddEntry(hist_QCD_filtered_noBtag_topTagEffPt,"Filtered Jets","LPE");
  lQCD_pt->AddEntry(hist_QCD_pruned_noBtag_topTagEffPt,"Pruned Jets","LPE");
  lQCD_pt->AddEntry(hist_QCD_trimmed_noBtag_topTagEffPt,"Trimmed Jets","LPE");
  lQCD_pt->SetFillColor(kWhite);
  lQCD_pt->Draw("Same");

  TCanvas* cQCD_npv = new TCanvas("QCD Npv Mistag rate");
  hist_QCD_noBtag_topTagEffNpv->Draw();
  hist_QCD_filtered_noBtag_topTagEffNpv->Draw("ESAME");
  hist_QCD_filtered_noBtag_topTagEffNpv->SetMarkerColor(2);
  hist_QCD_filtered_noBtag_topTagEffNpv->SetLineColor(2);
  hist_QCD_pruned_noBtag_topTagEffNpv->Draw("ESAME");
  hist_QCD_pruned_noBtag_topTagEffNpv->SetMarkerColor(4);
  hist_QCD_pruned_noBtag_topTagEffNpv->SetLineColor(4);
  hist_QCD_trimmed_noBtag_topTagEffNpv->Draw("ESAME");
  hist_QCD_trimmed_noBtag_topTagEffNpv->SetMarkerColor(3);
  hist_QCD_trimmed_noBtag_topTagEffNpv->SetLineColor(3);
  hist_QCD_noBtag_topTagEffNpv->SetMaximum(0.2);
  hist_QCD_filtered_noBtag_topTagEffNpv->SetMaximum(0.2);
  hist_QCD_pruned_noBtag_topTagEffNpv->SetMaximum(0.2);
  hist_QCD_trimmed_noBtag_topTagEffNpv->SetMaximum(0.2);

  TLegend* lQCD_npv = new TLegend(0.65,0.7,0.9,0.9);
  lQCD_npv->AddEntry(hist_QCD_noBtag_topTagEffNpv,"No Grooming Techniques","LPE");
  lQCD_npv->AddEntry(hist_QCD_filtered_noBtag_topTagEffNpv,"Filtered Jets","LPE");
  lQCD_npv->AddEntry(hist_QCD_pruned_noBtag_topTagEffNpv,"Pruned Jets","LPE");
  lQCD_npv->AddEntry(hist_QCD_trimmed_noBtag_topTagEffNpv,"Trimmed Jets","LPE");
  lQCD_npv->SetFillColor(kWhite);
  lQCD_npv->Draw("Same");
  
  TCanvas* c1 = new TCanvas("Pt efficiency");
  hist_SMttbar_noBtag_topTagEffPt->Draw();
  hist_SMttbar_noBtag_topTagEffPt->SetTitle("Top Tagging Efficiency vs Pt");
  h_topTagEffPt->Draw("ESAME");
  h_topTagEffPt->SetLineColor(2);
  h_topTagEffPt->SetMarkerColor(2);

  //legend
  TLegend *legend_topTagEffPt = new TLegend(0.6,0.75,0.9,0.9);
  legend_topTagEffPt->AddEntry(h_topTagEffPt,"#sqrt{s} = 8 TeV, SM t#bar{t}","LPE");
  legend_topTagEffPt->AddEntry(hist_SMttbar_noBtag_topTagEffPt,"#sqrt{s} = 13 TeV, SM t#bar{t}","LPE");
  legend_topTagEffPt->SetFillColor(kWhite); 
  legend_topTagEffPt->Draw("Same");

  TCanvas* c2 = new TCanvas("Npv efficiency");
  hist_SMttbar_noBtag_topTagEffNpv->Draw();
  hist_SMttbar_noBtag_topTagEffNpv->SetLineColor(1);
  hist_SMttbar_noBtag_topTagEffNpv->SetTitle("Top Tagging Efficiency vs Npv - No Pt Cut");
  h_topTagEffNpv->Draw("ESAME");
  h_topTagEffNpv->SetLineColor(2);
  h_topTagEffNpv->SetMarkerColor(2);

  //legend
  TLegend *legend_topTagEffNpv = new TLegend(0.6,0.75,0.9,0.9);
  legend_topTagEffNpv->AddEntry(h_topTagEffNpv,"#sqrt{s} = 8 TeV, SM t#bar{t}","LPE");
  legend_topTagEffNpv->AddEntry(hist_SMttbar_noBtag_topTagEffNpv,"#sqrt{s} = 13 TeV, SM t#bar{t}","LPE");
  legend_topTagEffNpv->SetFillColor(kWhite);
  legend_topTagEffNpv->Draw("Same");

  TCanvas* c3 = new TCanvas("Npv_400 efficiency");
  hist_SMttbar_noBtag_topTagEffNpv_400->Draw();
  hist_SMttbar_noBtag_topTagEffNpv_400->SetLineColor(1);
  hist_SMttbar_noBtag_topTagEffNpv_400->SetTitle("Top Tagging Efficiency vs Npv - Pt > 400 GeV");
  h_topTagEffNpv_400->Draw("ESAME");
  h_topTagEffNpv_400->SetLineColor(2);
  h_topTagEffNpv_400->SetMarkerColor(2);

  //legend
  TLegend *legend_topTagEffNpv_400 = new TLegend(0.6,0.75,0.9,0.9);
  legend_topTagEffNpv_400->AddEntry(h_topTagEffNpv_400,"#sqrt{s} = 8 TeV, SM t#bar{t}","LPE");
  legend_topTagEffNpv_400->AddEntry(hist_SMttbar_noBtag_topTagEffNpv_400,"#sqrt{s} = 13 TeV, SM t#bar{t}","LPE");
  legend_topTagEffNpv_400->SetFillColor(kWhite);
  legend_topTagEffNpv_400->Draw("Same");

  TCanvas* c4 = new TCanvas("13 TeV Pt Spectrum");
  hist_SMttbar_noBtag_jet1pt->Draw();
  hist_SMttbar_noBtag_jet1pt->SetTitle("13 TeV Jet Pt Spectrum - SM TTbar;Jet Pt;Events");
  hist_SMttbar_noBtag_jet1pt->GetYaxis()->SetTitleOffset(1.2);
  hist_SMttbar_noBtag_jet1pt->SetAxisRange(0,1700);

  TCanvas* c5 = new TCanvas("13 TeV Npv Spectrum");
  hist_SMttbar_noBtag_npv1->Draw();
  hist_SMttbar_noBtag_npv1->SetTitle("13 TeV Pileup - SM TTbar;Pileup;Events");
  hist_SMttbar_noBtag_npv1->GetYaxis()->SetTitleOffset(1.5);

  TCanvas* c6 = new TCanvas("8 TeV Pt Spectrum");
  h_topTagEffPtDenom->Draw();
  h_topTagEffPtDenom->SetTitle("8 TeV Jet Pt Spectrum - SM TTbar;Jet Pt;Events");
  h_topTagEffPtDenom->GetYaxis()->SetTitleOffset(1.2);
    
  TCanvas* c7 = new TCanvas("8 TeV Npv Spectrum");
  h_topTagEffNpvDenom->Draw();
  h_topTagEffNpvDenom->SetTitle("8 TeV Pileup - SM TTbar;Pileup;Events");
  h_topTagEffNpvDenom->GetYaxis()->SetTitleOffset(1.2);
  
  c1->SaveAs("topTagEfficiencyPtCompare_SMttbar.pdf");
  c2->SaveAs("topTagEfficiencyNpvCompare_SMttbar.pdf");
  c3->SaveAs("topTagEfficiencyNpvCompare_SMttbar_400.pdf");
  c4->SaveAs("SMttbar_JetPtSpectrum_13TeV.pdf");
  c5->SaveAs("SMttbar_Npv_13TeV.pdf");
  c6->SaveAs("SMttbar_JetPtSpectrum_8TeV.pdf");
  c7->SaveAs("SMttbar_Npv_8TeV.pdf");
  */  
}
