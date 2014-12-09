#if !defined(__CINT__) && !defined(__MAKECINT__)
#include<TROOT.h>
#include<TFile.h>
#include<vector>
#include<TChain.h>
#include<TCanvas.h>
#include<THStack.h>
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
#include<TLatex.h>
#include<TMath.h>
#include<TStyle.h>
#include<TSystem.h>
#include<TApplication.h>
//#include "boost/shared_ptr.hpp"
#include "/uscms_data/d3/camclean/CSA14/topTaggingEfficiency/CMSSW_7_0_6_patch1/src/Analysis/FWCore/FWLite/interface/AutoLibraryLoader.h"
#include "/uscms_data/d3/camclean/CSA14/topTaggingEfficiency/CMSSW_7_0_6_patch1/src/Analysis/DataFormats/FWLite/interface/Handle.h"
#include "/uscms_data/d3/camclean/CSA14/topTaggingEfficiency/CMSSW_7_0_6_patch1/src/Analysis/DataFormats/FWLite/interface/ChainEvent.h"
#include "/uscms_data/d3/camclean/CSA14/topTaggingEfficiency/CMSSW_7_0_6_patch1/src/Analysis/FWCore/ParameterSet/interface/ParameterSet.h"
#include "/uscms_data/d3/camclean/CSA14/topTaggingEfficiency/CMSSW_7_0_6_patch1/src/Analysis/DataFormats/PatCandidates/interface/Jet.h"
#include "/uscms_data/d3/camclean/CSA14/topTaggingEfficiency/CMSSW_7_0_6_patch1/src/Analysis/DataFormats/PatCandidates/interface/PackedGenParticle.h"
#include "/uscms_data/d3/camclean/CSA14/topTaggingEfficiency/CMSSW_7_0_6_patch1/src/Analysis/DataFormats/Candidate/interface/Candidate.h"
#include "/uscms_data/d3/camclean/CSA14/topTaggingEfficiency/CMSSW_7_0_6_patch1/src/Analysis/DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "/uscms_data/d3/camclean/CSA14/topTaggingEfficiency/CMSSW_7_0_6_patch1/src/Analysis/DataFormats/JetReco/interface/CATopJetTagInfo.h"
#endif

//using namespace fastjet;
using namespace std;

//argv[0] = topTagEfficiency_massWindowOptimize, argv[1] = Z' mass (string), argv[2] = Z' width, argv[3] = value of pt cut (string)
int main(int argc, char *argv[]){
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(0000000000);
  gStyle->SetTitleBorderSize(0);
  //gStyle->SetTitleAlign(0); 

  gSystem->Load("libFWCoreFWLite.so"); 
  gSystem->Load("libDataFormatsFWLite.so");
  AutoLibraryLoader::enable();

  //using file arguments
  string InputFileName = "topTagEfficiency_massWindowOptimize_QCD_ZPrime_M" + (string) argv[1] + "000GeV_W" + (string) argv[2] + "GeV_13TeV_jetPt" + (string) argv[3] + "+.root";
  
  double ptCut;
  stringstream convert((string) argv[3]);
  if ( !(convert >> ptCut) )//give the value to ptCut using the characters in the string
    ptCut = 0;

  /*
  double ZPrimeXmax;
  stringstream convert2((string) argv[4]);
  if ( !(convert2 >> ZPrimeXmax) )//give the value to ZPrimeXmax using the characters in the string 
    ZPrimeXmax = 0;
  
  double QCDyMin;
  stringstream convert3((string) argv[4]);
  if ( !(convert3 >> QCDyMin) )//give the value to QCDyMin using the characters in the string 
    QCDyMin = 0;
  */

  string legendPtCutLabel;
  double QCDyMin;
  if(ptCut == 0){
    legendPtCutLabel = "No Jet Pt Cut";
    QCDyMin = 0.95;
  }
  else{
    legendPtCutLabel = "Jet Pt > " + (string) argv[3] + " GeV";
    if(ptCut == 400){
      QCDyMin = 0.9;
    }
    else{
      QCDyMin = 0.88;
    }
  }

  string ZPrimeWidthPercent;
  if((string) argv[2] == "300" || (string) argv[2] == "400"){
    ZPrimeWidthPercent = "10";
  }
  else{
    ZPrimeWidthPercent = "1";
  }

  string legendSignalLabel = "Signal: " + (string) argv[1] + "TeV Z'#rightarrow t#bar{t}, #Gamma/m = " + ZPrimeWidthPercent + "%";

  TFile *f = new TFile(InputFileName.c_str());
  f->ls();

  //jet mass histograms
  TH1F * hist_ZPrime_noBtag_ungroomed_jetMass_preMassWindowCut = (TH1F*) f->Get("hist_ZPrime_noBtag_ungroomed_jetMass_preMassWindowCut");
  TH1F * hist_ZPrime_noBtag_subjets_jetMass_preMassWindowCut = (TH1F*) f->Get("hist_ZPrime_noBtag_subjets_jetMass_preMassWindowCut");
  TH1F * hist_ZPrime_noBtag_filtered_AK8jetMass_preMassWindowCut = (TH1F*) f->Get("hist_ZPrime_noBtag_filtered_AK8jetMass_preMassWindowCut");
  TH1F * hist_ZPrime_noBtag_pruned_AK8jetMass_preMassWindowCut = (TH1F*) f->Get("hist_ZPrime_noBtag_pruned_AK8jetMass_preMassWindowCut");
  TH1F * hist_ZPrime_noBtag_trimmed_AK8jetMass_preMassWindowCut = (TH1F*) f->Get("hist_ZPrime_noBtag_trimmed_AK8jetMass_preMassWindowCut");

  TH1F * hist_300toInf_QCD_noBtag_ungroomed_jetMass_preMassWindowCut = (TH1F*) f->Get("hist_300toInf_QCD_noBtag_ungroomed_jetMass_preMassWindowCut");
  TH1F * hist_300toInf_QCD_noBtag_subjets_jetMass_preMassWindowCut = (TH1F*) f->Get("hist_300toInf_QCD_noBtag_subjets_jetMass_preMassWindowCut");
  TH1F * hist_300toInf_QCD_noBtag_filtered_AK8jetMass_preMassWindowCut = (TH1F*) f->Get("hist_300toInf_QCD_noBtag_filtered_AK8jetMass_preMassWindowCut");
  TH1F * hist_300toInf_QCD_noBtag_pruned_AK8jetMass_preMassWindowCut = (TH1F*) f->Get("hist_300toInf_QCD_noBtag_pruned_AK8jetMass_preMassWindowCut");
  TH1F * hist_300toInf_QCD_noBtag_trimmed_AK8jetMass_preMassWindowCut = (TH1F*) f->Get("hist_300toInf_QCD_noBtag_trimmed_AK8jetMass_preMassWindowCut");

  //denominator histograms
  TH1F * hist_ZPrime_noBtag_ungroomed_jetMass_noTopTagCut = (TH1F*) f->Get("hist_ZPrime_noBtag_ungroomed_jetMass_noTopTagCut");
  //TH1F * hist_ZPrime_noBtag_subjets_jetMass_noTopTagCut = (TH1F*) f->Get("hist_ZPrime_noBtag_subjets_jetMass_noTopTagCut");
  TH1F * hist_ZPrime_noBtag_filtered_AK8jetMass_noTopTagCut = (TH1F*) f->Get("hist_ZPrime_noBtag_filtered_AK8jetMass_noTopTagCut");
  TH1F * hist_ZPrime_noBtag_pruned_AK8jetMass_noTopTagCut = (TH1F*) f->Get("hist_ZPrime_noBtag_pruned_AK8jetMass_noTopTagCut");
  TH1F * hist_ZPrime_noBtag_trimmed_AK8jetMass_noTopTagCut = (TH1F*) f->Get("hist_ZPrime_noBtag_trimmed_AK8jetMass_noTopTagCut");

  TH1F * hist_300toInf_QCD_noBtag_ungroomed_jetMass_noTopTagCut = (TH1F*) f->Get("hist_300toInf_QCD_noBtag_ungroomed_jetMass_noTopTagCut");
  //TH1F * hist_300toInf_QCD_noBtag_subjets_jetMass_noTopTagCut = (TH1F*) f->Get("hist_300toInf_QCD_noBtag_subjets_jetMass_noTopTagCut");
  TH1F * hist_300toInf_QCD_noBtag_filtered_AK8jetMass_noTopTagCut = (TH1F*) f->Get("hist_300toInf_QCD_noBtag_filtered_AK8jetMass_noTopTagCut");
  TH1F * hist_300toInf_QCD_noBtag_pruned_AK8jetMass_noTopTagCut = (TH1F*) f->Get("hist_300toInf_QCD_noBtag_pruned_AK8jetMass_noTopTagCut");
  TH1F * hist_300toInf_QCD_noBtag_trimmed_AK8jetMass_noTopTagCut = (TH1F*) f->Get("hist_300toInf_QCD_noBtag_trimmed_AK8jetMass_noTopTagCut");

  //2D efficiency histograms - all points
  TH2D *h_ZPrime_QCD_ungroomed_topTagEff = new TH2D("h_ZPrime_QCD_ungroomed_topTagEff",";Top Tagging Efficiency;QCD Rejection",100,0,1,100,QCDyMin,1);
  TH2D *h_ZPrime_QCD_subjets_topTagEff = new TH2D("h_ZPrime_QCD_subjets_topTagEff",";Top Tagging Efficiency;QCD Rejection",100,0,1,100,QCDyMin,1);
  TH2D *h_ZPrime_QCD_filtered_topTagEff = new TH2D("h_ZPrime_QCD_filtered_topTagEff",";Top Tagging Efficiency;QCD Rejection",100,0,1,100,QCDyMin,1);
  TH2D *h_ZPrime_QCD_pruned_topTagEff = new TH2D("h_ZPrime_QCD_pruned_topTagEff",";Top Tagging Efficiency;QCD Rejection",100,0,1,100,QCDyMin,1);
  TH2D *h_ZPrime_QCD_trimmed_topTagEff = new TH2D("h_ZPrime_QCD_trimmed_topTagEff",";Top Tagging Efficiency;QCD Rejection",100,0,1,100,QCDyMin,1);

  //2D efficiency histograms - standard top tagging
  TH2D *h_ZPrime_QCD_ungroomed_topTagEff_standard = new TH2D("h_ZPrime_QCD_ungroomed_topTagEff_standard",";Top Tagging Efficiency;QCD Rejection",100,0,1,100,QCDyMin,1);
  TH2D *h_ZPrime_QCD_subjets_topTagEff_standard = new TH2D("h_ZPrime_QCD_subjets_topTagEff_standard",";Top Tagging Efficiency;QCD Rejection",100,0,1,100,QCDyMin,1);
  TH2D *h_ZPrime_QCD_filtered_topTagEff_standard = new TH2D("h_ZPrime_QCD_filtered_topTagEff_standard",";Top Tagging Efficiency;QCD Rejection",100,0,1,100,QCDyMin,1);
  TH2D *h_ZPrime_QCD_pruned_topTagEff_standard = new TH2D("h_ZPrime_QCD_pruned_topTagEff_standard",";Top Tagging Efficiency;QCD Rejection",100,0,1,100,QCDyMin,1);
  TH2D *h_ZPrime_QCD_trimmed_topTagEff_standard = new TH2D("h_ZPrime_QCD_trimmed_topTagEff_standard",";Top Tagging Efficiency;QCD Rejection",100,0,1,100,QCDyMin,1);

  //2D efficiency histograms - new top tagging window
  TH2D *h_ZPrime_QCD_ungroomed_topTagEff_new = new TH2D("h_ZPrime_QCD_ungroomed_topTagEff_new",";Top Tagging Efficiency;QCD Rejection",100,0,1,100,QCDyMin,1);
  TH2D *h_ZPrime_QCD_subjets_topTagEff_new = new TH2D("h_ZPrime_QCD_subjets_topTagEff_new",";Top Tagging Efficiency;QCD Rejection",100,0,1,100,QCDyMin,1);
  TH2D *h_ZPrime_QCD_filtered_topTagEff_new = new TH2D("h_ZPrime_QCD_filtered_topTagEff_new",";Top Tagging Efficiency;QCD Rejection",100,0,1,100,QCDyMin,1);
  TH2D *h_ZPrime_QCD_pruned_topTagEff_new = new TH2D("h_ZPrime_QCD_pruned_topTagEff_new",";Top Tagging Efficiency;QCD Rejection",100,0,1,100,QCDyMin,1);
  TH2D *h_ZPrime_QCD_trimmed_topTagEff_new = new TH2D("h_ZPrime_QCD_trimmed_topTagEff_new",";Top Tagging Efficiency;QCD Rejection",100,0,1,100,QCDyMin,1);

  //efficiency denominator integrals
  double int_ZPrime_noBtag_ungroomed_jetMass_noTopTagCut = hist_ZPrime_noBtag_ungroomed_jetMass_noTopTagCut->Integral();
  double int_ZPrime_noBtag_subjets_jetMass_noTopTagCut = hist_ZPrime_noBtag_ungroomed_jetMass_noTopTagCut->Integral();//only ungroomed jets without nsubj cut
  double int_ZPrime_noBtag_filtered_AK8jetMass_noTopTagCut = hist_ZPrime_noBtag_filtered_AK8jetMass_noTopTagCut->Integral();
  double int_ZPrime_noBtag_pruned_AK8jetMass_noTopTagCut = hist_ZPrime_noBtag_pruned_AK8jetMass_noTopTagCut->Integral();
  double int_ZPrime_noBtag_trimmed_AK8jetMass_noTopTagCut = hist_ZPrime_noBtag_trimmed_AK8jetMass_noTopTagCut->Integral();
  
  double int_300toInf_QCD_noBtag_ungroomed_jetMass_noTopTagCut = hist_300toInf_QCD_noBtag_ungroomed_jetMass_noTopTagCut->Integral();
  double int_300toInf_QCD_noBtag_subjets_jetMass_noTopTagCut = hist_300toInf_QCD_noBtag_ungroomed_jetMass_noTopTagCut->Integral();//only ungroomed jets without nsubj cut
  double int_300toInf_QCD_noBtag_filtered_AK8jetMass_noTopTagCut = hist_300toInf_QCD_noBtag_filtered_AK8jetMass_noTopTagCut->Integral();
  double int_300toInf_QCD_noBtag_pruned_AK8jetMass_noTopTagCut = hist_300toInf_QCD_noBtag_pruned_AK8jetMass_noTopTagCut->Integral();
  double int_300toInf_QCD_noBtag_trimmed_AK8jetMass_noTopTagCut = hist_300toInf_QCD_noBtag_trimmed_AK8jetMass_noTopTagCut->Integral();

  //finding the best mass window for S/sqrt(B) 
  double max_ratio_ungroomed = 0.;//initializing the value of the maximum ratio of S/sqrt(B)
  double Zprime_signal_ungroomed, background_qcd_ungroomed, Zprime_signal_ungroomed_optimum = 0., background_qcd_ungroomed_optimum = 0., ratio_ungroomed = 0., ratio_ungroomed_standard = 0.;
  int bin_min_optimum_ungroomed = 0, bin_max_optimum_ungroomed = 0;

  double max_ratio_subjets = 0.;//initializing the value of the maximum ratio of S/sqrt(B)
  double Zprime_signal_subjets, background_qcd_subjets, Zprime_signal_subjets_optimum = 0., background_qcd_subjets_optimum = 0., ratio_subjets = 0., ratio_subjets_standard = 0.;
  int bin_min_optimum_subjets = 0, bin_max_optimum_subjets = 0;

  double max_ratio_filtered = 0.;//initializing the value of the maximum ratio of S/sqrt(B)
  double Zprime_signal_filtered, background_qcd_filtered, Zprime_signal_filtered_optimum = 0., background_qcd_filtered_optimum = 0., ratio_filtered = 0., ratio_filtered_standard = 0.;
  int bin_min_optimum_filtered = 0, bin_max_optimum_filtered = 0;

  double max_ratio_pruned = 0.;//initializing the value of the maximum ratio of S/sqrt(B)
  double Zprime_signal_pruned, background_qcd_pruned, Zprime_signal_pruned_optimum = 0., background_qcd_pruned_optimum = 0., ratio_pruned = 0., ratio_pruned_standard = 0.;
  int bin_min_optimum_pruned = 0, bin_max_optimum_pruned = 0;

  double max_ratio_trimmed = 0.;//initializing the value of the maximum ratio of S/sqrt(B)
  double Zprime_signal_trimmed, background_qcd_trimmed, Zprime_signal_trimmed_optimum = 0., background_qcd_trimmed_optimum = 0., ratio_trimmed = 0., ratio_trimmed_standard = 0.;
  int bin_min_optimum_trimmed = 0, bin_max_optimum_trimmed = 0;

  TCanvas* cGrooming_compare_2D = new TCanvas("2D Grooming comparison");//2D efficiency canvas
  TLegend* lGrooming_compare_2D = new TLegend(0.53,0.05,0.9,0.9);//legend

  for(int i=(11);i<(19);i++){
    for(int j=18;j<(28);j++){      //18 is the bin with 175 GeV (top mass)
      //ungroomed
      Zprime_signal_ungroomed = hist_ZPrime_noBtag_ungroomed_jetMass_preMassWindowCut->Integral(i,j);
      background_qcd_ungroomed = hist_300toInf_QCD_noBtag_ungroomed_jetMass_preMassWindowCut->Integral(i,j);
      ratio_ungroomed = Zprime_signal_ungroomed/sqrt(background_qcd_ungroomed);

      if(ratio_ungroomed > max_ratio_ungroomed){
        max_ratio_ungroomed = ratio_ungroomed;
        bin_min_optimum_ungroomed = i;
        bin_max_optimum_ungroomed = j;
	Zprime_signal_ungroomed_optimum = Zprime_signal_ungroomed;
	background_qcd_ungroomed_optimum = background_qcd_ungroomed;
      }

      //subjets                                                                                                                                                                                                                                                               
      Zprime_signal_subjets = hist_ZPrime_noBtag_subjets_jetMass_preMassWindowCut->Integral(i,j);
      background_qcd_subjets = hist_300toInf_QCD_noBtag_subjets_jetMass_preMassWindowCut->Integral(i,j);
      ratio_subjets = Zprime_signal_subjets/sqrt(background_qcd_subjets);

      if(ratio_subjets > max_ratio_subjets){
        max_ratio_subjets = ratio_subjets;
        bin_min_optimum_subjets = i;
        bin_max_optimum_subjets = j;
        Zprime_signal_subjets_optimum = Zprime_signal_subjets;
        background_qcd_subjets_optimum = background_qcd_subjets;
      }

      //filtered
      Zprime_signal_filtered = hist_ZPrime_noBtag_filtered_AK8jetMass_preMassWindowCut->Integral(i,j);
      background_qcd_filtered = hist_300toInf_QCD_noBtag_filtered_AK8jetMass_preMassWindowCut->Integral(i,j);
      ratio_filtered = Zprime_signal_filtered/sqrt(background_qcd_filtered);
      
      if(ratio_filtered > max_ratio_filtered){
	max_ratio_filtered = ratio_filtered;
	bin_min_optimum_filtered = i;
	bin_max_optimum_filtered = j;
        Zprime_signal_filtered_optimum = Zprime_signal_filtered;
        background_qcd_filtered_optimum = background_qcd_filtered;
      }

      //pruned                                                                                                                                                                                            
      Zprime_signal_pruned = hist_ZPrime_noBtag_pruned_AK8jetMass_preMassWindowCut->Integral(i,j);
      background_qcd_pruned = hist_300toInf_QCD_noBtag_pruned_AK8jetMass_preMassWindowCut->Integral(i,j);
      ratio_pruned = Zprime_signal_pruned/sqrt(background_qcd_pruned);

      if(ratio_pruned > max_ratio_pruned){
        max_ratio_pruned = ratio_pruned;
        bin_min_optimum_pruned = i;
        bin_max_optimum_pruned = j;
	Zprime_signal_pruned_optimum = Zprime_signal_pruned;
        background_qcd_pruned_optimum = background_qcd_pruned;
      }

      //trimmed                                                                                                                                                 
      Zprime_signal_trimmed = hist_ZPrime_noBtag_trimmed_AK8jetMass_preMassWindowCut->Integral(i,j);
      background_qcd_trimmed = hist_300toInf_QCD_noBtag_trimmed_AK8jetMass_preMassWindowCut->Integral(i,j);
      ratio_trimmed = Zprime_signal_trimmed/sqrt(background_qcd_trimmed);

      if(ratio_trimmed > max_ratio_trimmed){
        max_ratio_trimmed = ratio_trimmed;
        bin_min_optimum_trimmed = i;
        bin_max_optimum_trimmed = j;
        Zprime_signal_trimmed_optimum = Zprime_signal_trimmed;
        background_qcd_trimmed_optimum = background_qcd_trimmed;
      }

      //efficiencies
      double ZPrime_noBtag_ungroomed_efficiency = Zprime_signal_ungroomed/int_ZPrime_noBtag_ungroomed_jetMass_noTopTagCut;
      double QCD_noBtag_ungroomed_efficiency = background_qcd_ungroomed/int_300toInf_QCD_noBtag_ungroomed_jetMass_noTopTagCut;
      double ZPrime_noBtag_subjets_efficiency = Zprime_signal_subjets/int_ZPrime_noBtag_subjets_jetMass_noTopTagCut;
      double QCD_noBtag_subjets_efficiency = background_qcd_subjets/int_300toInf_QCD_noBtag_subjets_jetMass_noTopTagCut;
      double ZPrime_noBtag_filtered_efficiency = Zprime_signal_filtered/int_ZPrime_noBtag_filtered_AK8jetMass_noTopTagCut;
      double QCD_noBtag_filtered_efficiency = background_qcd_filtered/int_300toInf_QCD_noBtag_filtered_AK8jetMass_noTopTagCut;
      double ZPrime_noBtag_pruned_efficiency = Zprime_signal_pruned/int_ZPrime_noBtag_pruned_AK8jetMass_noTopTagCut;
      double QCD_noBtag_pruned_efficiency = background_qcd_pruned/int_300toInf_QCD_noBtag_pruned_AK8jetMass_noTopTagCut;
      double ZPrime_noBtag_trimmed_efficiency = Zprime_signal_trimmed/int_ZPrime_noBtag_trimmed_AK8jetMass_noTopTagCut;
      double QCD_noBtag_trimmed_efficiency = background_qcd_trimmed/int_300toInf_QCD_noBtag_trimmed_AK8jetMass_noTopTagCut;

      //filling, labeling, and drawing histograms
      if(i==15 && j==25){
	ratio_ungroomed_standard = ratio_ungroomed;
	ratio_subjets_standard = ratio_subjets;
	ratio_filtered_standard = ratio_filtered;
	ratio_pruned_standard = ratio_pruned;
	ratio_trimmed_standard = ratio_trimmed;
	  
	h_ZPrime_QCD_ungroomed_topTagEff_standard->Fill(ZPrime_noBtag_ungroomed_efficiency, 1 - QCD_noBtag_ungroomed_efficiency);
	h_ZPrime_QCD_subjets_topTagEff_standard->Fill(ZPrime_noBtag_subjets_efficiency, 1 - QCD_noBtag_subjets_efficiency);
	h_ZPrime_QCD_filtered_topTagEff_standard->Fill(ZPrime_noBtag_filtered_efficiency, 1 - QCD_noBtag_filtered_efficiency);
	h_ZPrime_QCD_pruned_topTagEff_standard->Fill(ZPrime_noBtag_pruned_efficiency, 1 - QCD_noBtag_pruned_efficiency);
	h_ZPrime_QCD_trimmed_topTagEff_standard->Fill(ZPrime_noBtag_trimmed_efficiency, 1 - QCD_noBtag_trimmed_efficiency);

	h_ZPrime_QCD_ungroomed_topTagEff_standard->SetMarkerColor(kRed-3);
	h_ZPrime_QCD_subjets_topTagEff_standard->SetMarkerColor(kViolet+2);
	h_ZPrime_QCD_filtered_topTagEff_standard->SetMarkerColor(kAzure+3);
	h_ZPrime_QCD_pruned_topTagEff_standard->SetMarkerColor(kTeal-6);
	h_ZPrime_QCD_trimmed_topTagEff_standard->SetMarkerColor(kOrange);

	h_ZPrime_QCD_ungroomed_topTagEff_standard->SetMarkerStyle(33);
	h_ZPrime_QCD_subjets_topTagEff_standard->SetMarkerStyle(33);
        h_ZPrime_QCD_filtered_topTagEff_standard->SetMarkerStyle(33);
        h_ZPrime_QCD_pruned_topTagEff_standard->SetMarkerStyle(33);
        h_ZPrime_QCD_trimmed_topTagEff_standard->SetMarkerStyle(33);

	h_ZPrime_QCD_ungroomed_topTagEff_standard->Draw("PSame");
	h_ZPrime_QCD_subjets_topTagEff_standard->Draw("PSame");
        h_ZPrime_QCD_filtered_topTagEff_standard->Draw("PSame");
	h_ZPrime_QCD_pruned_topTagEff_standard->Draw("PSame");
        h_ZPrime_QCD_trimmed_topTagEff_standard->Draw("PSame");
      }//standard top tagging mass window
      else{
	h_ZPrime_QCD_ungroomed_topTagEff->Fill(ZPrime_noBtag_ungroomed_efficiency, 1 - QCD_noBtag_ungroomed_efficiency);
	
	if(i == 11 && j == 18){
	  h_ZPrime_QCD_ungroomed_topTagEff->Draw("P");
	}
	else{
	  h_ZPrime_QCD_ungroomed_topTagEff->Draw("PSame");
	}
      }
      h_ZPrime_QCD_subjets_topTagEff->Fill(ZPrime_noBtag_subjets_efficiency, 1 - QCD_noBtag_subjets_efficiency);
      h_ZPrime_QCD_subjets_topTagEff->Draw("PSame");

      h_ZPrime_QCD_filtered_topTagEff->Fill(ZPrime_noBtag_filtered_efficiency, 1 - QCD_noBtag_filtered_efficiency);
      h_ZPrime_QCD_filtered_topTagEff->Draw("PSame");
      
      h_ZPrime_QCD_pruned_topTagEff->Fill(ZPrime_noBtag_pruned_efficiency, 1 - QCD_noBtag_pruned_efficiency);
      h_ZPrime_QCD_pruned_topTagEff->Draw("PSame");
      
      h_ZPrime_QCD_trimmed_topTagEff->Fill(ZPrime_noBtag_trimmed_efficiency, 1 - QCD_noBtag_trimmed_efficiency);
      h_ZPrime_QCD_trimmed_topTagEff->Draw("PSame");
    }//mass window max loop
  }//mass window min loop

  //optimum efficiencies
  double ZPrime_noBtag_ungroomed_optimum_efficiency = Zprime_signal_ungroomed_optimum/int_ZPrime_noBtag_ungroomed_jetMass_noTopTagCut;
  double QCD_noBtag_ungroomed_optimum_efficiency = background_qcd_ungroomed_optimum/int_300toInf_QCD_noBtag_ungroomed_jetMass_noTopTagCut;
  double ZPrime_noBtag_subjets_optimum_efficiency = Zprime_signal_subjets_optimum/int_ZPrime_noBtag_subjets_jetMass_noTopTagCut;
  double QCD_noBtag_subjets_optimum_efficiency = background_qcd_subjets_optimum/int_300toInf_QCD_noBtag_subjets_jetMass_noTopTagCut;
  double ZPrime_noBtag_filtered_optimum_efficiency = Zprime_signal_filtered_optimum/int_ZPrime_noBtag_filtered_AK8jetMass_noTopTagCut;
  double QCD_noBtag_filtered_optimum_efficiency = background_qcd_filtered_optimum/int_300toInf_QCD_noBtag_filtered_AK8jetMass_noTopTagCut;
  double ZPrime_noBtag_pruned_optimum_efficiency = Zprime_signal_pruned_optimum/int_ZPrime_noBtag_pruned_AK8jetMass_noTopTagCut;
  double QCD_noBtag_pruned_optimum_efficiency = background_qcd_pruned_optimum/int_300toInf_QCD_noBtag_pruned_AK8jetMass_noTopTagCut;
  double ZPrime_noBtag_trimmed_optimum_efficiency = Zprime_signal_trimmed_optimum/int_ZPrime_noBtag_trimmed_AK8jetMass_noTopTagCut;
  double QCD_noBtag_trimmed_optimum_efficiency = background_qcd_trimmed_optimum/int_300toInf_QCD_noBtag_trimmed_AK8jetMass_noTopTagCut;  

  //filling optimal top tagging window points (stars)
  h_ZPrime_QCD_ungroomed_topTagEff_new->Fill(ZPrime_noBtag_ungroomed_optimum_efficiency, 1 - QCD_noBtag_ungroomed_optimum_efficiency);
  h_ZPrime_QCD_ungroomed_topTagEff_new->SetMarkerColor(kRed-3);
  h_ZPrime_QCD_ungroomed_topTagEff_new->SetMarkerStyle(29);
  h_ZPrime_QCD_ungroomed_topTagEff_new->Draw("PSame");

  h_ZPrime_QCD_subjets_topTagEff_new->Fill(ZPrime_noBtag_subjets_optimum_efficiency, 1 - QCD_noBtag_subjets_optimum_efficiency);
  h_ZPrime_QCD_subjets_topTagEff_new->SetMarkerColor(kViolet+2);
  h_ZPrime_QCD_subjets_topTagEff_new->SetMarkerStyle(29);
  h_ZPrime_QCD_subjets_topTagEff_new->Draw("PSame");

  h_ZPrime_QCD_filtered_topTagEff_new->Fill(ZPrime_noBtag_filtered_optimum_efficiency, 1 - QCD_noBtag_filtered_optimum_efficiency);
  h_ZPrime_QCD_filtered_topTagEff_new->SetMarkerColor(kAzure+3);
  h_ZPrime_QCD_filtered_topTagEff_new->SetMarkerStyle(29);
  h_ZPrime_QCD_filtered_topTagEff_new->Draw("PSame");
  
  h_ZPrime_QCD_pruned_topTagEff_new->Fill(ZPrime_noBtag_pruned_optimum_efficiency, 1 - QCD_noBtag_pruned_optimum_efficiency);
  h_ZPrime_QCD_pruned_topTagEff_new->SetMarkerColor(kTeal-6);
  h_ZPrime_QCD_pruned_topTagEff_new->SetMarkerStyle(29);
  h_ZPrime_QCD_pruned_topTagEff_new->Draw("PSame");
  
  h_ZPrime_QCD_trimmed_topTagEff_new->Fill(ZPrime_noBtag_trimmed_optimum_efficiency, 1 - QCD_noBtag_trimmed_optimum_efficiency);
  h_ZPrime_QCD_trimmed_topTagEff_new->SetMarkerColor(kOrange);
  h_ZPrime_QCD_trimmed_topTagEff_new->SetMarkerStyle(29);
  h_ZPrime_QCD_trimmed_topTagEff_new->Draw("PSame");
  
  //setting the rest of the marker settings
  h_ZPrime_QCD_ungroomed_topTagEff->SetMarkerColor(kRed-3);
  h_ZPrime_QCD_subjets_topTagEff->SetMarkerColor(kViolet+2);
  h_ZPrime_QCD_filtered_topTagEff->SetMarkerColor(kAzure+3);
  h_ZPrime_QCD_pruned_topTagEff->SetMarkerColor(kTeal-6);
  h_ZPrime_QCD_trimmed_topTagEff->SetMarkerColor(kOrange);

  h_ZPrime_QCD_ungroomed_topTagEff->SetMarkerStyle(4);
  h_ZPrime_QCD_subjets_topTagEff->SetMarkerStyle(4);
  h_ZPrime_QCD_filtered_topTagEff->SetMarkerStyle(4);
  h_ZPrime_QCD_pruned_topTagEff->SetMarkerStyle(4);
  h_ZPrime_QCD_trimmed_topTagEff->SetMarkerStyle(4);

  h_ZPrime_QCD_ungroomed_topTagEff->SetMarkerSize(0.3);
  h_ZPrime_QCD_subjets_topTagEff->SetMarkerSize(0.3);
  h_ZPrime_QCD_filtered_topTagEff->SetMarkerSize(0.3);
  h_ZPrime_QCD_pruned_topTagEff->SetMarkerSize(0.3);
  h_ZPrime_QCD_trimmed_topTagEff->SetMarkerSize(0.3);

  h_ZPrime_QCD_ungroomed_topTagEff_standard->SetMarkerSize(2.5);
  h_ZPrime_QCD_subjets_topTagEff_standard->SetMarkerSize(2.5);
  h_ZPrime_QCD_filtered_topTagEff_standard->SetMarkerSize(2.5);
  h_ZPrime_QCD_pruned_topTagEff_standard->SetMarkerSize(2.5);
  h_ZPrime_QCD_trimmed_topTagEff_standard->SetMarkerSize(2.5);

  h_ZPrime_QCD_ungroomed_topTagEff_new->SetMarkerSize(2.5);
  h_ZPrime_QCD_subjets_topTagEff_new->SetMarkerSize(2.5);
  h_ZPrime_QCD_filtered_topTagEff_new->SetMarkerSize(2.5);
  h_ZPrime_QCD_pruned_topTagEff_new->SetMarkerSize(2.5);
  h_ZPrime_QCD_trimmed_topTagEff_new->SetMarkerSize(2.5);

  h_ZPrime_QCD_ungroomed_topTagEff->GetYaxis()->SetTitleOffset(1.3);

  lGrooming_compare_2D->AddEntry((TObject*)0 ,legendSignalLabel.c_str(),"");
  lGrooming_compare_2D->AddEntry((TObject*)0 ,"Background: Pt 300+ QCD","");
  lGrooming_compare_2D->AddEntry((TObject*)0 ,legendPtCutLabel.c_str(),"");

  lGrooming_compare_2D->AddEntry((TObject*)0 ,"","");
  lGrooming_compare_2D->AddEntry((TObject*)0 ,"Standard Top Tagging Mass Window:","");
  lGrooming_compare_2D->AddEntry(h_ZPrime_QCD_ungroomed_topTagEff_standard,"No Grooming Techniques","P");
  lGrooming_compare_2D->AddEntry(h_ZPrime_QCD_subjets_topTagEff_standard,"CA8 Subjet Mass","P");
  lGrooming_compare_2D->AddEntry(h_ZPrime_QCD_filtered_topTagEff_standard,"Filtered AK8 Jets","P");
  lGrooming_compare_2D->AddEntry(h_ZPrime_QCD_pruned_topTagEff_standard,"Pruned AK8 Jets","P");
  lGrooming_compare_2D->AddEntry(h_ZPrime_QCD_trimmed_topTagEff_standard,"Trimmed AK8 Jets","P");

  lGrooming_compare_2D->AddEntry((TObject*)0 ,"","");
  lGrooming_compare_2D->AddEntry((TObject*)0 ,"Mass Window with Best (S/#sqrt{B}):","");
  lGrooming_compare_2D->AddEntry(h_ZPrime_QCD_ungroomed_topTagEff_new,"No Grooming Techniques","P");
  lGrooming_compare_2D->AddEntry(h_ZPrime_QCD_subjets_topTagEff_new,"CA8 Subjet Mass","P");
  lGrooming_compare_2D->AddEntry(h_ZPrime_QCD_filtered_topTagEff_new,"Filtered AK8 Jets","P");
  lGrooming_compare_2D->AddEntry(h_ZPrime_QCD_pruned_topTagEff_new,"Pruned AK8 Jets","P");
  lGrooming_compare_2D->AddEntry(h_ZPrime_QCD_trimmed_topTagEff_new,"Trimmed AK8 Jets","P");

  lGrooming_compare_2D->AddEntry((TObject*)0 ,"","");
  lGrooming_compare_2D->AddEntry((TObject*)0 ,"Other Mass Windows:","");
  lGrooming_compare_2D->AddEntry(h_ZPrime_QCD_ungroomed_topTagEff,"No Grooming Techniques","P");
  lGrooming_compare_2D->AddEntry(h_ZPrime_QCD_subjets_topTagEff,"CA8 Subjet Mass","P");
  lGrooming_compare_2D->AddEntry(h_ZPrime_QCD_filtered_topTagEff,"Filtered AK8 Jets","P");
  lGrooming_compare_2D->AddEntry(h_ZPrime_QCD_pruned_topTagEff,"Pruned AK8 Jets","P");
  lGrooming_compare_2D->AddEntry(h_ZPrime_QCD_trimmed_topTagEff,"Trimmed AK8 Jets","P");

  lGrooming_compare_2D->Draw("SAME");
  lGrooming_compare_2D->SetFillColor(kWhite);

  TLatex *cmsLabel = new TLatex();
  cmsLabel->SetNDC();
  cmsLabel->DrawLatex(0.1,0.9, "CMS Simulation, #sqrt{s} = 13 TeV");

  string canvasName2D = "topTagEfficiency2D_massGrooming_massWindowOptimize_QCD_ZPrime_M" + (string) argv[1] + "000GeV_W" + (string) argv[2] + "GeV_13TeV_jetPt" + (string) argv[3] + "+.root";
  cGrooming_compare_2D->SaveAs(canvasName2D.c_str());

  TCanvas* cGrooming_compare_2D_standardWindow = new TCanvas("");
  h_ZPrime_QCD_ungroomed_topTagEff_standard->Draw("P");
  h_ZPrime_QCD_subjets_topTagEff_standard->Draw("PSame");
  h_ZPrime_QCD_filtered_topTagEff_standard->Draw("PSame");
  h_ZPrime_QCD_pruned_topTagEff_standard->Draw("PSame");
  h_ZPrime_QCD_trimmed_topTagEff_standard->Draw("PSame");  
  h_ZPrime_QCD_ungroomed_topTagEff_standard->GetYaxis()->SetTitleOffset(1.3);

  TLegend* lGrooming_compare_2D_standardWindow = new TLegend(0.53,0.5,0.9,0.9);//legend  
  lGrooming_compare_2D_standardWindow->AddEntry((TObject*)0 ,legendSignalLabel.c_str(),"");
  lGrooming_compare_2D_standardWindow->AddEntry((TObject*)0 ,"Background: Pt 300+ QCD","");
  lGrooming_compare_2D_standardWindow->AddEntry((TObject*)0 ,legendPtCutLabel.c_str(),"");

  lGrooming_compare_2D_standardWindow->AddEntry((TObject*)0 ,"","");
  lGrooming_compare_2D_standardWindow->AddEntry((TObject*)0 ,"Standard Top Tagging Mass Window:","");
  lGrooming_compare_2D_standardWindow->AddEntry(h_ZPrime_QCD_ungroomed_topTagEff_standard,"No Grooming Techniques","P");
  lGrooming_compare_2D_standardWindow->AddEntry(h_ZPrime_QCD_subjets_topTagEff_standard,"CA8 Subjet Mass","P");
  lGrooming_compare_2D_standardWindow->AddEntry(h_ZPrime_QCD_filtered_topTagEff_standard,"Filtered AK8 Jets","P");
  lGrooming_compare_2D_standardWindow->AddEntry(h_ZPrime_QCD_pruned_topTagEff_standard,"Pruned AK8 Jets","P");
  lGrooming_compare_2D_standardWindow->AddEntry(h_ZPrime_QCD_trimmed_topTagEff_standard,"Trimmed AK8 Jets","P");

  lGrooming_compare_2D_standardWindow->Draw("SAME");
  lGrooming_compare_2D_standardWindow->SetFillColor(kWhite);

  TLatex *cmsLabel_standardWindow = new TLatex();
  cmsLabel_standardWindow->SetNDC();
  cmsLabel_standardWindow->DrawLatex(0.1,0.9, "CMS Simulation, #sqrt{s} = 13 TeV");

  string canvasName2D_standardWindow = "topTagEfficiency2D_standardWindow_massGrooming_massWindowOptimize_QCD_ZPrime_M" + (string) argv[1] + "000GeV_W" + (string) argv[2] + "GeV_13TeV_jetPt" + (string) argv[3] + "+.root";
  cGrooming_compare_2D_standardWindow->SaveAs(canvasName2D_standardWindow.c_str());

  //printing the results of the window optimization                                                                                                                                                        
  //ungroomed
  cout<<"The optimal signal window for a Z' using ungroomed jets is from bin "<<bin_min_optimum_ungroomed<<" to bin "<<bin_max_optimum_ungroomed<<", or a mass window of "<<hist_ZPrime_noBtag_ungroomed_jetMass_preMassWindowCut->GetBinLowEdge(bin_min_optimum_ungroomed)<<" GeV to "<<hist_ZPrime_noBtag_ungroomed_jetMass_preMassWindowCut->GetBinLowEdge(bin_max_optimum_ungroomed + 1)<<" GeV. This corresponds to S/sqrt(B) = "<<max_ratio_ungroomed<<". The standard top tagging window, 140 GeV to 150 GeV, gives an S/sqrt(B) of "<<ratio_ungroomed_standard<<". The new signal window shows an improvement of "<<max_ratio_ungroomed/ratio_ungroomed_standard*100<<"% in S/sqrt(B) from the standard top tagging window."<<endl;

  cout<<""<<endl;

  //subjets
  cout<<"The optimal signal window for a Z' using the invariant mass of the leading three CA8 subjets is from bin "<<bin_min_optimum_subjets<<" to bin "<<bin_max_optimum_subjets<<", or a mass window of "<<hist_ZPrime_noBtag_subjets_jetMass_preMassWindowCut->GetBinLowEdge(bin_min_optimum_subjets)<<" GeV to "<<hist_ZPrime_noBtag_subjets_jetMass_preMassWindowCut->GetBinLowEdge(bin_max_optimum_subjets + 1)<<" GeV. This corresponds to S/sqrt(B) = "<<max_ratio_subjets<<". The standard top tagging window, 140 GeV to 150 GeV, gives an S/sqrt(B) of "<<ratio_subjets_standard<<". The new signal window shows an improvement of "<<max_ratio_subjets/ratio_subjets_standard*100<<"% in S/sqrt(B) from the standard top tagging window."<<endl;

  cout<<""<<endl;

  //filtered
  cout<<"The optimal signal window for a Z' using filtered jets is from bin "<<bin_min_optimum_filtered<<" to bin "<<bin_max_optimum_filtered<<", or a mass window of "<<hist_ZPrime_noBtag_filtered_AK8jetMass_preMassWindowCut->GetBinLowEdge(bin_min_optimum_filtered)<<" GeV to "<<hist_ZPrime_noBtag_filtered_AK8jetMass_preMassWindowCut->GetBinLowEdge(bin_max_optimum_filtered + 1)<<" GeV. This corresponds to S/sqrt(B) = "<<max_ratio_filtered<<". The standard top tagging window, 140 GeV to 150 GeV, gives an S/sqrt(B) of "<<ratio_filtered_standard<<". The new signal window shows an improvement of "<<max_ratio_filtered/ratio_filtered_standard*100<<"% in S/sqrt(B) from the standard top tagging window."<<endl;

  cout<<""<<endl;

  //pruned                                                                                                                                                                                                
  cout<<"The optimal signal window for a Z' using pruned jets is from bin "<<bin_min_optimum_pruned<<" to bin "<<bin_max_optimum_pruned<<", or a mass window of "<<hist_ZPrime_noBtag_pruned_AK8jetMass_preMassWindowCut->GetBinLowEdge(bin_min_optimum_pruned)<<" GeV to "<<hist_ZPrime_noBtag_pruned_AK8jetMass_preMassWindowCut->GetBinLowEdge(bin_max_optimum_pruned + 1)<<" GeV. This corresponds to S/sqrt(B) = "<<max_ratio_pruned<<". The standard top tagging window, 140 GeV to 150 GeV, gives an S/sqrt(B) of "<<ratio_pruned_standard<<". The new signal window shows an improvement of "<<max_ratio_pruned/ratio_pruned_standard*100<<"% in S/sqrt(B) from the standard top tagging window."<<endl;

  cout<<""<<endl;

  //trimmed 
  cout<<"The optimal signal window for a Z' using trimmed jets is from bin "<<bin_min_optimum_trimmed<<" to bin "<<bin_max_optimum_trimmed<<", or a mass window of "<<hist_ZPrime_noBtag_trimmed_AK8jetMass_preMassWindowCut->GetBinLowEdge(bin_min_optimum_trimmed)<<" GeV to "<<hist_ZPrime_noBtag_trimmed_AK8jetMass_preMassWindowCut->GetBinLowEdge(bin_max_optimum_trimmed + 1)<<" GeV. This corresponds to S/sqrt(B) = "<<max_ratio_trimmed<<". The standard top tagging window, 140 GeV to 150 GeV, gives an S/sqrt(B) of "<<ratio_trimmed_standard<<". The new signal window shows an improvement of "<<max_ratio_trimmed/ratio_trimmed_standard*100<<"% in S/sqrt(B) from the standard top tagging window."<<endl;

  cout<<""<<endl;

  ////////////////////////
  //making stacked plots
  ///////////////////////

  //with Nsubj and minmass cuts
  TCanvas* c_ungroomed = new TCanvas("Ungroomed Top Tagging Window");
  THStack* hs_ungroomed = new THStack("h_stack_ungroomed","Ungroomed Jet Mass - After Minmass and Nsubjettiness Cuts");
  hist_ZPrime_noBtag_ungroomed_jetMass_preMassWindowCut->SetFillColor(kAzure+3);
  hist_300toInf_QCD_noBtag_ungroomed_jetMass_preMassWindowCut->SetFillColor(kOrange);

  hs_ungroomed->Add(hist_ZPrime_noBtag_ungroomed_jetMass_preMassWindowCut);
  hs_ungroomed->Add(hist_300toInf_QCD_noBtag_ungroomed_jetMass_preMassWindowCut);
  hs_ungroomed->Draw();
  hs_ungroomed->SetMinimum(0.01);
  //hs_ungroomed->GetHistogram()->SetTitle("Ungroomed Jet Mass - After Minmass and Nsubjettiness Cuts");
  hs_ungroomed->GetHistogram()->GetXaxis()->SetTitle("Mass (GeV)");
  hs_ungroomed->GetHistogram()->GetYaxis()->SetTitle("Events");
  c_ungroomed->SetLogy();

  TLegend *legend_ungroomed = new TLegend(0.75,0.8,0.9,0.9);
  legend_ungroomed->AddEntry(hist_ZPrime_noBtag_ungroomed_jetMass_preMassWindowCut,"4 TeV Z Prime","F");
  legend_ungroomed->AddEntry(hist_300toInf_QCD_noBtag_ungroomed_jetMass_preMassWindowCut,"300+ pt QCD","F");
  legend_ungroomed->SetFillColor(kWhite);
  legend_ungroomed->Draw("Same");

  string CanvasNameUngroomed = "topTagEfficiency_massWindowOptimize_QCD_ZPrime_M" + (string) argv[1] + "000GeV_W" + (string) argv[2] + "GeV_13TeV_jetPt" + (string) argv[3] + "+_ungroomed.pdf";
  c_ungroomed->SaveAs(CanvasNameUngroomed.c_str());
  
  TCanvas* c_subjets = new TCanvas("Subjets Top Tagging Window");
  THStack* hs_subjets = new THStack("h_stack_subjets","Subjets Jet Mass - After Minmass and Nsubjettiness Cuts");
  hist_ZPrime_noBtag_subjets_jetMass_preMassWindowCut->SetFillColor(kAzure+3);
  hist_300toInf_QCD_noBtag_subjets_jetMass_preMassWindowCut->SetFillColor(kOrange);

  hs_subjets->Add(hist_ZPrime_noBtag_subjets_jetMass_preMassWindowCut);
  hs_subjets->Add(hist_300toInf_QCD_noBtag_subjets_jetMass_preMassWindowCut);
  hs_subjets->Draw();
  hs_subjets->SetMinimum(0.01);
  //hs_subjets->GetHistogram()->SetTitle("Subjets Jet Mass - After Minmass and Nsubjettiness Cuts");                                                                                                                                                                        
  hs_subjets->GetHistogram()->GetXaxis()->SetTitle("Mass (GeV)");
  hs_subjets->GetHistogram()->GetYaxis()->SetTitle("Events");
  c_subjets->SetLogy();

  TLegend *legend_subjets = new TLegend(0.75,0.8,0.9,0.9);
  legend_subjets->AddEntry(hist_ZPrime_noBtag_subjets_jetMass_preMassWindowCut,"4 TeV Z Prime","F");
  legend_subjets->AddEntry(hist_300toInf_QCD_noBtag_subjets_jetMass_preMassWindowCut,"300+ pt QCD","F");
  legend_subjets->SetFillColor(kWhite);
  legend_subjets->Draw("Same");

  string CanvasNameSubjets = "topTagEfficiency_massWindowOptimize_QCD_ZPrime_M" + (string) argv[1] + "000GeV_W" + (string) argv[2] + "GeV_13TeV_jetPt" + (string) argv[3] + "+_subjets.pdf";
  c_subjets->SaveAs(CanvasNameSubjets.c_str());

  TCanvas* c_filtered = new TCanvas("Filtered Top Tagging Window");
  THStack* hs_filtered = new THStack("h_stack_filtered","Filtered Jet Mass - After Minmass and Nsubjettiness Cuts");
  hist_ZPrime_noBtag_filtered_AK8jetMass_preMassWindowCut->SetFillColor(kAzure+3);
  hist_300toInf_QCD_noBtag_filtered_AK8jetMass_preMassWindowCut->SetFillColor(kOrange);

  hs_filtered->Add(hist_ZPrime_noBtag_filtered_AK8jetMass_preMassWindowCut);
  hs_filtered->Add(hist_300toInf_QCD_noBtag_filtered_AK8jetMass_preMassWindowCut);
  hs_filtered->Draw();
  hs_filtered->SetMinimum(0.01);
  //hs_filtered->GetHistogram()->SetTitle("Filtered Jet Mass - After Minmass and Nsubjettiness Cuts");
  hs_filtered->GetHistogram()->GetXaxis()->SetTitle("Mass (GeV)");
  hs_filtered->GetHistogram()->GetYaxis()->SetTitle("Events");
  c_filtered->SetLogy();

  TLegend *legend_filtered = new TLegend(0.75,0.8,0.9,0.9);
  legend_filtered->AddEntry(hist_ZPrime_noBtag_filtered_AK8jetMass_preMassWindowCut,"4 TeV Z Prime","F");
  legend_filtered->AddEntry(hist_300toInf_QCD_noBtag_filtered_AK8jetMass_preMassWindowCut,"300+ pt QCD","F");
  legend_filtered->SetFillColor(kWhite);
  legend_filtered->Draw("Same");

  string CanvasNameFiltered = "topTagEfficiency_massWindowOptimize_QCD_ZPrime_M" + (string) argv[1] + "000GeV_W" + (string) argv[2] + "GeV_13TeV_jetPt" + (string) argv[3] + "+_filtered.pdf";
  c_filtered->SaveAs(CanvasNameFiltered.c_str());

  TCanvas* c_pruned = new TCanvas("Pruned Top Tagging Window");
  THStack* hs_pruned = new THStack("h_stack_pruned","Pruned Jet Mass - After Minmass and Nsubjettiness Cuts");
  hist_ZPrime_noBtag_pruned_AK8jetMass_preMassWindowCut->SetFillColor(kAzure+3);
  hist_300toInf_QCD_noBtag_pruned_AK8jetMass_preMassWindowCut->SetFillColor(kOrange);

  hs_pruned->Add(hist_ZPrime_noBtag_pruned_AK8jetMass_preMassWindowCut);
  hs_pruned->Add(hist_300toInf_QCD_noBtag_pruned_AK8jetMass_preMassWindowCut);
  hs_pruned->Draw();
  hs_pruned->SetMinimum(0.01);
  //hs_pruned->GetHistogram()->SetTitle("Pruned Jet Mass - After Minmass and Nsubjettiness Cuts");
  hs_pruned->GetHistogram()->GetXaxis()->SetTitle("Mass (GeV)");
  hs_pruned->GetHistogram()->GetYaxis()->SetTitle("Events");
  c_pruned->SetLogy();

  TLegend *legend_pruned = new TLegend(0.75,0.8,0.9,0.9);
  legend_pruned->AddEntry(hist_ZPrime_noBtag_pruned_AK8jetMass_preMassWindowCut,"4 TeV Z Prime","F");
  legend_pruned->AddEntry(hist_300toInf_QCD_noBtag_pruned_AK8jetMass_preMassWindowCut,"300+ pt QCD","F");
  legend_pruned->SetFillColor(kWhite);
  legend_pruned->Draw("Same");

  string CanvasNamePruned = "topTagEfficiency_massWindowOptimize_QCD_ZPrime_M" + (string) argv[1] + "000GeV_W" + (string) argv[2] + "GeV_13TeV_jetPt" + (string) argv[3] + "+_pruned.pdf";
  c_pruned->SaveAs(CanvasNamePruned.c_str());

  TCanvas* c_trimmed = new TCanvas("Trimmed Top Tagging Window");
  THStack* hs_trimmed = new THStack("h_stack_trimmed","Trimmed Jet Mass - After Minmass and Nsubjettiness Cuts");
  hist_ZPrime_noBtag_trimmed_AK8jetMass_preMassWindowCut->SetFillColor(kAzure+3);
  hist_300toInf_QCD_noBtag_trimmed_AK8jetMass_preMassWindowCut->SetFillColor(kOrange);

  hs_trimmed->Add(hist_ZPrime_noBtag_trimmed_AK8jetMass_preMassWindowCut);
  hs_trimmed->Add(hist_300toInf_QCD_noBtag_trimmed_AK8jetMass_preMassWindowCut);
  hs_trimmed->Draw();
  hs_trimmed->SetMinimum(0.01);
  //hs_trimmed->GetHistogram()->SetTitle("Trimmed Jet Mass - After Minmass and Nsubjettiness Cuts");
  hs_trimmed->GetHistogram()->GetXaxis()->SetTitle("Mass (GeV)");
  hs_trimmed->GetHistogram()->GetYaxis()->SetTitle("Events");
  c_trimmed->SetLogy();

  TLegend *legend_trimmed = new TLegend(0.75,0.8,0.9,0.9);
  legend_trimmed->AddEntry(hist_ZPrime_noBtag_trimmed_AK8jetMass_preMassWindowCut,"4 TeV Z Prime","F");
  legend_trimmed->AddEntry(hist_300toInf_QCD_noBtag_trimmed_AK8jetMass_preMassWindowCut,"300+ pt QCD","F");
  legend_trimmed->SetFillColor(kWhite);
  legend_trimmed->Draw("Same");

  string CanvasNameTrimmed = "topTagEfficiency_massWindowOptimize_QCD_ZPrime_M" + (string) argv[1] + "000GeV_W" + (string) argv[2] + "GeV_13TeV_jetPt" + (string) argv[3] + "+_trimmed.pdf";
  c_trimmed->SaveAs(CanvasNameTrimmed.c_str());

  //no top tag cuts
  TCanvas* c_ungroomed_noTopTagCut = new TCanvas("Ungroomed Top Tagging Window - No Top Tag Cuts");
  THStack* hs_ungroomed_noTopTagCut = new THStack("h_stack_ungroomed_noTopTagCut","Ungroomed Jet Mass - No Top Tagging Cuts");
  hist_ZPrime_noBtag_ungroomed_jetMass_noTopTagCut->SetFillColor(kAzure+3);
  hist_300toInf_QCD_noBtag_ungroomed_jetMass_noTopTagCut->SetFillColor(kOrange);

  hs_ungroomed_noTopTagCut->Add(hist_ZPrime_noBtag_ungroomed_jetMass_noTopTagCut);
  hs_ungroomed_noTopTagCut->Add(hist_300toInf_QCD_noBtag_ungroomed_jetMass_noTopTagCut);
  hs_ungroomed_noTopTagCut->Draw();
  hs_ungroomed_noTopTagCut->SetMinimum(0.01);
  //hs_ungroomed_noTopTagCut->GetHistogram()->SetTitle("Ungroomed Jet Mass");
  hs_ungroomed_noTopTagCut->GetHistogram()->GetXaxis()->SetTitle("Mass (GeV)");
  hs_ungroomed_noTopTagCut->GetHistogram()->GetYaxis()->SetTitle("Events");
  c_ungroomed_noTopTagCut->SetLogy();

  TLegend *legend_ungroomed_noTopTagCut = new TLegend(0.75,0.8,0.9,0.9);
  legend_ungroomed_noTopTagCut->AddEntry(hist_ZPrime_noBtag_ungroomed_jetMass_noTopTagCut,"4 TeV Z Prime","F");
  legend_ungroomed_noTopTagCut->AddEntry(hist_300toInf_QCD_noBtag_ungroomed_jetMass_noTopTagCut,"300+ pt QCD","F");
  legend_ungroomed_noTopTagCut->SetFillColor(kWhite);
  legend_ungroomed_noTopTagCut->Draw("Same");

  string CanvasNameUngroomed_noTopTagCut = "topTagEfficiency_massWindowOptimize_QCD_ZPrime_M" + (string) argv[1] + "000GeV_W" + (string) argv[2] + "GeV_13TeV_jetPt" + (string) argv[3] + "+_ungroomed_noTopTagCut.pdf";
  c_ungroomed_noTopTagCut->SaveAs(CanvasNameUngroomed_noTopTagCut.c_str());
  
  /* TCanvas* c_subjets_noTopTagCut = new TCanvas("Subjets Top Tagging Window - No Top Tag Cuts");
  THStack* hs_subjets_noTopTagCut = new THStack("h_stack_subjets_noTopTagCut","Subjets Jet Mass - No Top Tagging Cuts");
  hist_ZPrime_noBtag_subjets_jetMass_noTopTagCut->SetFillColor(kAzure+3);
  hist_300toInf_QCD_noBtag_subjets_jetMass_noTopTagCut->SetFillColor(kOrange);

  hs_subjets_noTopTagCut->Add(hist_ZPrime_noBtag_subjets_jetMass_noTopTagCut);
  hs_subjets_noTopTagCut->Add(hist_300toInf_QCD_noBtag_subjets_jetMass_noTopTagCut);
  hs_subjets_noTopTagCut->Draw();
  hs_subjets_noTopTagCut->SetMinimum(0.01);
  //hs_subjets_noTopTagCut->GetHistogram()->SetTitle("Subjets Jet Mass");                                                                                                                                                                                                   
  hs_subjets_noTopTagCut->GetHistogram()->GetXaxis()->SetTitle("Mass (GeV)");
  hs_subjets_noTopTagCut->GetHistogram()->GetYaxis()->SetTitle("Events");
  c_subjets_noTopTagCut->SetLogy();
  
  TLegend *legend_subjets_noTopTagCut = new TLegend(0.75,0.8,0.9,0.9);
  legend_subjets_noTopTagCut->AddEntry(hist_ZPrime_noBtag_subjets_jetMass_noTopTagCut,"4 TeV Z Prime","F");
  legend_subjets_noTopTagCut->AddEntry(hist_300toInf_QCD_noBtag_subjets_jetMass_noTopTagCut,"300+ pt QCD","F");
  legend_subjets_noTopTagCut->SetFillColor(kWhite);
  legend_subjets_noTopTagCut->Draw("Same");

  string CanvasNameSubjets_noTopTagCut = "topTagEfficiency_massWindowOptimize_QCD_ZPrime_M" + (string) argv[1] + "000GeV_W" + (string) argv[2] + "GeV_13TeV_jetPt" + (string) argv[3] + "+_subjets_noTopTagCut.pdf";
  c_subjets_noTopTagCut->SaveAs(CanvasNameSubjets_noTopTagCut.c_str());
  */
  TCanvas* c_filtered_noTopTagCut = new TCanvas("Filtered_noTopTagCut Top Tagging Window");
  THStack* hs_filtered_noTopTagCut = new THStack("h_stack_filtered_noTopTagCut","Filtered Jet Mass - No Top Tagging Cuts");
  hist_ZPrime_noBtag_filtered_AK8jetMass_noTopTagCut->SetFillColor(kAzure+3);
  hist_300toInf_QCD_noBtag_filtered_AK8jetMass_noTopTagCut->SetFillColor(kOrange);

  hs_filtered_noTopTagCut->Add(hist_ZPrime_noBtag_filtered_AK8jetMass_noTopTagCut);
  hs_filtered_noTopTagCut->Add(hist_300toInf_QCD_noBtag_filtered_AK8jetMass_noTopTagCut);
  hs_filtered_noTopTagCut->Draw();
  hs_filtered_noTopTagCut->SetMinimum(0.01);
  //hs_filtered_noTopTagCut->GetHistogram()->SetTitle("Filtered Jet Mass");
  hs_filtered_noTopTagCut->GetHistogram()->GetXaxis()->SetTitle("Mass (GeV)");
  hs_filtered_noTopTagCut->GetHistogram()->GetYaxis()->SetTitle("Events");
  c_filtered_noTopTagCut->SetLogy();

  TLegend *legend_filtered_noTopTagCut = new TLegend(0.75,0.8,0.9,0.9);
  legend_filtered_noTopTagCut->AddEntry(hist_ZPrime_noBtag_filtered_AK8jetMass_noTopTagCut,"4 TeV Z Prime","F");
  legend_filtered_noTopTagCut->AddEntry(hist_300toInf_QCD_noBtag_filtered_AK8jetMass_noTopTagCut,"300+ pt QCD","F");
  legend_filtered_noTopTagCut->SetFillColor(kWhite);
  legend_filtered_noTopTagCut->Draw("Same");

  string CanvasNameFiltered_noTopTagCut = "topTagEfficiency_massWindowOptimize_QCD_ZPrime_M" + (string) argv[1] + "000GeV_W" + (string) argv[2] + "GeV_13TeV_jetPt" + (string) argv[3] + "+_filtered_noTopTagCut.pdf";
  c_filtered_noTopTagCut->SaveAs(CanvasNameFiltered_noTopTagCut.c_str());

  TCanvas* c_pruned_noTopTagCut = new TCanvas("Pruned_noTopTagCut Top Tagging Window");
  THStack* hs_pruned_noTopTagCut = new THStack("h_stack_pruned_noTopTagCut","Pruned Jet Mass - No Top Tagging Cuts");
  hist_ZPrime_noBtag_pruned_AK8jetMass_noTopTagCut->SetFillColor(kAzure+3);
  hist_300toInf_QCD_noBtag_pruned_AK8jetMass_noTopTagCut->SetFillColor(kOrange);

  hs_pruned_noTopTagCut->Add(hist_ZPrime_noBtag_pruned_AK8jetMass_noTopTagCut);
  hs_pruned_noTopTagCut->Add(hist_300toInf_QCD_noBtag_pruned_AK8jetMass_noTopTagCut);
  hs_pruned_noTopTagCut->Draw();
  hs_pruned_noTopTagCut->SetMinimum(0.01);
  //hs_pruned_noTopTagCut->GetHistogram()->SetTitle("Pruned Jet Mass");
  hs_pruned_noTopTagCut->GetHistogram()->GetXaxis()->SetTitle("Mass (GeV)");
  hs_pruned_noTopTagCut->GetHistogram()->GetYaxis()->SetTitle("Events");
  c_pruned_noTopTagCut->SetLogy();

  TLegend *legend_pruned_noTopTagCut = new TLegend(0.75,0.8,0.9,0.9);
  legend_pruned_noTopTagCut->AddEntry(hist_ZPrime_noBtag_pruned_AK8jetMass_noTopTagCut,"4 TeV Z Prime","F");
  legend_pruned_noTopTagCut->AddEntry(hist_300toInf_QCD_noBtag_pruned_AK8jetMass_noTopTagCut,"300+ pt QCD","F");
  legend_pruned_noTopTagCut->SetFillColor(kWhite);
  legend_pruned_noTopTagCut->Draw("Same");

  string CanvasNamePruned_noTopTagCut = "topTagEfficiency_massWindowOptimize_QCD_ZPrime_M" + (string) argv[1] + "000GeV_W" + (string) argv[2] + "GeV_13TeV_jetPt" + (string) argv[3] + "+_pruned_noTopTagCut.pdf";
  c_pruned_noTopTagCut->SaveAs(CanvasNamePruned_noTopTagCut.c_str());

  TCanvas* c_trimmed_noTopTagCut = new TCanvas("Trimmed_noTopTagCut Top Tagging Window");
  THStack* hs_trimmed_noTopTagCut = new THStack("h_stack_trimmed_noTopTagCut","Trimmed Jet Mass - No Top Tagging Cuts");
  hist_ZPrime_noBtag_trimmed_AK8jetMass_noTopTagCut->SetFillColor(kAzure+3);
  hist_300toInf_QCD_noBtag_trimmed_AK8jetMass_noTopTagCut->SetFillColor(kOrange);

  hs_trimmed_noTopTagCut->Add(hist_ZPrime_noBtag_trimmed_AK8jetMass_noTopTagCut);
  hs_trimmed_noTopTagCut->Add(hist_300toInf_QCD_noBtag_trimmed_AK8jetMass_noTopTagCut);
  hs_trimmed_noTopTagCut->Draw();
  hs_trimmed_noTopTagCut->SetMinimum(0.01);
  //hs_trimmed_noTopTagCut->GetHistogram()->SetTitle("Trimmed Jet Mass");
  hs_trimmed_noTopTagCut->GetHistogram()->GetXaxis()->SetTitle("Mass (GeV)");
  hs_trimmed_noTopTagCut->GetHistogram()->GetYaxis()->SetTitle("Events");
  c_trimmed_noTopTagCut->SetLogy();

  TLegend *legend_trimmed_noTopTagCut = new TLegend(0.75,0.8,0.9,0.9);
  legend_trimmed_noTopTagCut->AddEntry(hist_ZPrime_noBtag_trimmed_AK8jetMass_noTopTagCut,"4 TeV Z Prime","F");
  legend_trimmed_noTopTagCut->AddEntry(hist_300toInf_QCD_noBtag_trimmed_AK8jetMass_noTopTagCut,"300+ pt QCD","F");
  legend_trimmed_noTopTagCut->SetFillColor(kWhite);
  legend_trimmed_noTopTagCut->Draw("Same");

  string CanvasNameTrimmed_noTopTagCut = "topTagEfficiency_massWindowOptimize_QCD_ZPrime_M" + (string) argv[1] + "000GeV_W" + (string) argv[2] + "GeV_13TeV_jetPt" + (string) argv[3] + "+_trimmed_noTopTagCut.pdf";
  c_trimmed_noTopTagCut->SaveAs(CanvasNameTrimmed_noTopTagCut.c_str());

  return 0;
}

//  LocalWords:  ZPrimeFileNames ifstream ZPrimeFile rootFiles Zprime13TeV txt
//  LocalWords:  getline ev ZPrime toBegin atEnd jet1tagEff AK8jet1tagEff
//  LocalWords:  jet2tagEff AK8jet2tagEff jet1NsubjEff jet1minmassEff miniAOD
//  LocalWords:  jet1topMassEff AK8jet1filteredMassEff AK8jet1prunedMassEff
//  LocalWords:  AK8jet1trimmedMassEff jet2NsubjEff jet2minmassEff getByLabel
//  LocalWords:  jet2topMassEff AK8jet2filteredMassEff AK8jet2prunedMassEff
//  LocalWords:  AK8jet2trimmedMassEff MiniAOD 1800to2400 noBtag ungroomed
//  LocalWords:  jetMass AK8jetMass
