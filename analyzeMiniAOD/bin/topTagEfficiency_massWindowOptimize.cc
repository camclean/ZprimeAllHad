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

//argv[0] = topTagEfficiency_massWindowOptimize, argv[1] = signal sample (string), argv[2] = value of pt cut (string), argv[3] = Ngen_ZPrime
int main(int argc, char *argv[]){
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(0000000000);
  gStyle->SetTitleBorderSize(0);
  //gStyle->SetTitleAlign(0); 

  gSystem->Load("libFWCoreFWLite.so"); 
  gSystem->Load("libDataFormatsFWLite.so");
  AutoLibraryLoader::enable();

  //using file arguments
  string InputSignalFileName = "rootFiles_" + (string) argv[1] +  ".txt";
  string OutputFileName = "topTagEfficiency_massWindowOptimize_QCD_" + (string) argv[1] + "_jetPt" + (string) argv[2] + "+.root";
  
  double ptCut;
  stringstream convert((string) argv[2]);
  if ( !(convert >> ptCut) )//give the value to ptCut using the characters in the string
    ptCut = 0;

  double N_gen_ZPrime;
  stringstream convert2((string) argv[3]);
  if ( !(convert2 >> N_gen_ZPrime) )//give the value to N_gen_ZPrime using the characters in the string
    N_gen_ZPrime = 0;

  cout<<"The samples being analyzed are 300+ GeV pt QCD and "<<(string) argv[1]<<", both with a pt cut of "<<ptCut<<" GeV."<<endl;

  //QCD dataset weights
  double luminosity = 20.0; //fb^-1

  double sigma_300to470 = 7475000; //fb
  double sigma_470to600 = 587100; //fb
  double sigma_600to800 = 167000; //fb
  double sigma_800to1000 = 28250; //fb
  double sigma_1000to1400 = 8195; //fb
  double sigma_1400to1800 = 734.6; //fb
  double sigma_1800to2400 = 102; //fb
  double sigma_2400to3200 = 6.44; //fb
  double sigma_3200toInf = 0.163; //fb

  double N_gen_300to470 = 1498032;  //number of generated events in the pt 300 to 470 dataset
  double N_gen_470to600 = 1500297;  //number of generated events in the pt 470 to 600 dataset 
  double N_gen_600to800 = (1465278*150)/151;  //number of generated events in the pt 600 to 800 dataset 
  double N_gen_800to1000 = 1500369;  //number of generated events in the pt 800 to 1000 dataset 
  double N_gen_1000to1400 = 1500642;  //number of generated events in the pt 1000 to 1400 dataset 
  double N_gen_1400to1800 = 1500040;  //number of generated events in the pt 1400 to 1800 dataset 
  double N_gen_1800to2400 = 2933522; //number of generated events in the pt 1800 to 2400 dataset
  double N_gen_2400to3200 = (2820065*140)/151; //number of generated events in the pt 2400 to 3200 dataset
  double N_gen_3200toInf = 2457079; //number of generated events in the pt 3200+ dataset
    
  double w_300to470 = (luminosity * sigma_300to470)/N_gen_300to470;
  double w_470to600 = (luminosity * sigma_470to600)/N_gen_470to600;
  double w_600to800 = (luminosity * sigma_600to800)/N_gen_600to800;
  double w_800to1000 = (luminosity * sigma_800to1000)/N_gen_800to1000;
  double w_1000to1400 = (luminosity * sigma_1000to1400)/N_gen_1000to1400;
  double w_1400to1800 = (luminosity * sigma_1400to1800)/N_gen_1400to1800;
  double w_1800to2400 = (luminosity * sigma_1800to2400)/N_gen_1800to2400;
  double w_2400to3200 =(luminosity * sigma_2400to3200)/N_gen_2400to3200;
  double w_3200toInf =(luminosity * sigma_3200toInf)/N_gen_3200toInf;

  //ZPrime weights - normalizing to 1 pb
  double sigma_ZPrime = 1000.0; //fb
  double w_ZPrime = (luminosity * sigma_ZPrime)/N_gen_ZPrime;
  
  /////////////////////////////////                                                                                                                                                         
  //// No Mass Grooming Techniques
  /////////////////////////////////  

  /////jet mass histograms
  TH1F *hist_ZPrime_noBtag_ungroomed_jetMass_preMassWindowCut = new TH1F("hist_ZPrime_noBtag_ungroomed_jetMass_preMassWindowCut","Jet Mass - 13 TeV (4 TeV Narrow Z Prime to t#bar{t});Jet Mass (GeV); Events",80,0,800);
  TH1F *hist_300toInf_QCD_noBtag_ungroomed_jetMass_preMassWindowCut = new TH1F("hist_300toInf_QCD_noBtag_ungroomed_jetMass_preMassWindowCut","Jet Mass - 13 TeV (QCD);Jet Mass (GeV); Events",80,0,800);

  TH1F *hist_ZPrime_noBtag_ungroomed_jetMass_noTopTagCut = new TH1F("hist_ZPrime_noBtag_ungroomed_jetMass_noTopTagCut","Jet Mass - 13 TeV (4 TeV Narrow Z Prime to t#bar{t});Jet Mass (GeV); Events",80,0,800);
  TH1F *hist_300toInf_QCD_noBtag_ungroomed_jetMass_noTopTagCut = new TH1F("hist_300toInf_QCD_noBtag_ungroomed_jetMass_noTopTagCut","Jet Mass - 13 TeV (QCD);Jet Mass (GeV); Events",80,0,800);

  /*  
  hist_ZPrime_noBtag_ungroomed_jetMass_preMassWindowCut->Sumw2(); 
  hist_1800to2400_QCD_noBtag_ungroomed_jetMass_preMassWindowCut->Sumw2();
  hist_2400to3200_QCD_noBtag_ungroomed_jetMass_preMassWindowCut->Sumw2();
  hist_300toInf_QCD_noBtag_ungroomed_jetMass_preMassWindowCut->Sumw2();
  */

  /////////////////////////////////                                                                                                                                                         
  //// CA8 Subjets
  /////////////////////////////////  

  /////jet mass histograms
  TH1F *hist_ZPrime_noBtag_subjets_jetMass_preMassWindowCut = new TH1F("hist_ZPrime_noBtag_subjets_jetMass_preMassWindowCut","Jet Mass - 13 TeV (4 TeV Narrow Z Prime to t#bar{t});Jet Mass (GeV); Events",80,0,800);
  TH1F *hist_300toInf_QCD_noBtag_subjets_jetMass_preMassWindowCut = new TH1F("hist_300toInf_QCD_noBtag_subjets_jetMass_preMassWindowCut","Jet Mass - 13 TeV (QCD);Jet Mass (GeV); Events",80,0,800);

  TH1F *hist_ZPrime_noBtag_subjets_jetMass_noTopTagCut = new TH1F("hist_ZPrime_noBtag_subjets_jetMass_noTopTagCut","Jet Mass - 13 TeV (4 TeV Narrow Z Prime to t#bar{t});Jet Mass (GeV); Events",80,0,800);
  TH1F *hist_300toInf_QCD_noBtag_subjets_jetMass_noTopTagCut = new TH1F("hist_300toInf_QCD_noBtag_subjets_jetMass_noTopTagCut","Jet Mass - 13 TeV (QCD);Jet Mass (GeV); Events",80,0,800);

  /*  
  hist_ZPrime_noBtag_subjets_jetMass_preMassWindowCut->Sumw2(); 
  hist_1800to2400_QCD_noBtag_subjets_jetMass_preMassWindowCut->Sumw2();
  hist_2400to3200_QCD_noBtag_subjets_jetMass_preMassWindowCut->Sumw2();
  hist_300toInf_QCD_noBtag_subjets_jetMass_preMassWindowCut->Sumw2();
  */
  
  /////////////////////////////////
  //// AK8 Filtered Jets      
  /////////////////////////////////  

  /////jet mass histograms
  TH1F *hist_ZPrime_noBtag_filtered_AK8jetMass_preMassWindowCut = new TH1F("hist_ZPrime_noBtag_filtered_AK8jetMass_preMassWindowCut","Jet Mass - 13 TeV (4 TeV Narrow Z Prime to t#bar{t});Jet Mass (GeV); Events",80,0,800);
  TH1F *hist_300toInf_QCD_noBtag_filtered_AK8jetMass_preMassWindowCut = new TH1F("hist_300toInf_QCD_noBtag_filtered_AK8jetMass_preMassWindowCut","Jet Mass - 13 TeV (QCD);Jet Mass (GeV); Events",80,0,800);

  TH1F *hist_ZPrime_noBtag_filtered_AK8jetMass_noTopTagCut = new TH1F("hist_ZPrime_noBtag_filtered_AK8jetMass_noTopTagCut","Jet Mass - 13 TeV (4 TeV Narrow Z Prime to t#bar{t});Jet Mass (GeV); Events",80,0,800);
  TH1F *hist_300toInf_QCD_noBtag_filtered_AK8jetMass_noTopTagCut = new TH1F("hist_300toInf_QCD_noBtag_filtered_AK8jetMass_noTopTagCut","Jet Mass - 13 TeV (QCD);Jet Mass (GeV); Events",80,0,800);

  /*
  hist_ZPrime_noBtag_filtered_AK8jetMass_preMassWindowCut->Sumw2();
  hist_1800to2400_QCD_noBtag_filtered_AK8jetMass_preMassWindowCut->Sumw2();
  hist_2400to3200_QCD_noBtag_filtered_AK8jetMass_preMassWindowCut->Sumw2();
  hist_300toInf_QCD_noBtag_filtered_AK8jetMass_preMassWindowCut->Sumw2();
  */

  /////////////////////////////////
  //// AK8 Pruned Jets 
  /////////////////////////////////  

  /////jet mass histograms
  TH1F *hist_ZPrime_noBtag_pruned_AK8jetMass_preMassWindowCut = new TH1F("hist_ZPrime_noBtag_pruned_AK8jetMass_preMassWindowCut","Jet Mass - 13 TeV (4 TeV Narrow Z Prime to t#bar{t});Jet Mass (GeV); Events",80,0,800);
  TH1F *hist_300toInf_QCD_noBtag_pruned_AK8jetMass_preMassWindowCut = new TH1F("hist_300toInf_QCD_noBtag_pruned_AK8jetMass_preMassWindowCut","Jet Mass - 13 TeV (QCD);Jet Mass (GeV); Events",80,0,800);

  TH1F *hist_ZPrime_noBtag_pruned_AK8jetMass_noTopTagCut = new TH1F("hist_ZPrime_noBtag_pruned_AK8jetMass_noTopTagCut","Jet Mass - 13 TeV (4 TeV Narrow Z Prime to t#bar{t});Jet Mass (GeV); Events",80,0,800);
  TH1F *hist_300toInf_QCD_noBtag_pruned_AK8jetMass_noTopTagCut = new TH1F("hist_300toInf_QCD_noBtag_pruned_AK8jetMass_noTopTagCut","Jet Mass - 13 TeV (QCD);Jet Mass (GeV); Events",80,0,800);

  /*
  hist_ZPrime_noBtag_pruned_AK8jetMass_preMassWindowCut->Sumw2();
  hist_1800to2400_QCD_noBtag_pruned_AK8jetMass_preMassWindowCut->Sumw2();
  hist_2400to3200_QCD_noBtag_pruned_AK8jetMass_preMassWindowCut->Sumw2();
  hist_300toInf_QCD_noBtag_pruned_AK8jetMass_preMassWindowCut->Sumw2();
  */

  /////////////////////////////////
  //// AK8 Trimmed Jets  
  /////////////////////////////////  

  /////jet mass histograms
  TH1F *hist_ZPrime_noBtag_trimmed_AK8jetMass_preMassWindowCut = new TH1F("hist_ZPrime_noBtag_trimmed_AK8jetMass_preMassWindowCut","Jet Mass - 13 TeV (4 TeV Narrow Z Prime to t#bar{t});Jet Mass (GeV); Events",80,0,800);
  TH1F *hist_300toInf_QCD_noBtag_trimmed_AK8jetMass_preMassWindowCut = new TH1F("hist_300toInf_QCD_noBtag_trimmed_AK8jetMass_preMassWindowCut","Jet Mass - 13 TeV (QCD);Jet Mass (GeV); Events",80,0,800);

  TH1F *hist_ZPrime_noBtag_trimmed_AK8jetMass_noTopTagCut = new TH1F("hist_ZPrime_noBtag_trimmed_AK8jetMass_noTopTagCut","Jet Mass - 13 TeV (4 TeV Narrow Z Prime to t#bar{t});Jet Mass (GeV); Events",80,0,800);
  TH1F *hist_300toInf_QCD_noBtag_trimmed_AK8jetMass_noTopTagCut = new TH1F("hist_300toInf_QCD_noBtag_trimmed_AK8jetMass_noTopTagCut","Jet Mass - 13 TeV (QCD);Jet Mass (GeV); Events",80,0,800);

  /*
  hist_ZPrime_noBtag_trimmed_AK8jetMass_preMassWindowCut->Sumw2();
  hist_1800to2400_QCD_noBtag_trimmed_AK8jetMass_preMassWindowCut->Sumw2();
  hist_2400to3200_QCD_noBtag_trimmed_AK8jetMass_preMassWindowCut->Sumw2();
  hist_300toInf_QCD_noBtag_trimmed_AK8jetMass_preMassWindowCut->Sumw2();
  */


  //filling histograms - jet mass and top tagging efficiency vs npv (denominator)  
  ///////////////////
  ////Signal
  ///////////////////   
  vector<string> ZPrimeFileNames;

  string line;
  ifstream ZPrimeFile (InputSignalFileName);
  if (ZPrimeFile.is_open()){
      while ( getline (ZPrimeFile,line) )
	{
	  ZPrimeFileNames.push_back(line);
	}
      ZPrimeFile.close();
    }
  
  //fileNames.push_back("/uscms_data/d3/camclean/CSA14/topTaggingEfficiency/CMSSW_7_0_6_patch1/src/Analysis/analyzeMiniAOD/RSGluonToTT_M_4000_08_19_2014/res/miniAOD*.root");

  fwlite::ChainEvent ev_ZPrime(ZPrimeFileNames);

  for( ev_ZPrime.toBegin(); ! ev_ZPrime.atEnd(); ++ev_ZPrime) {
    fwlite::Handle<int> h_jet1tagEff;
    fwlite::Handle<int> h_AK8jet1tagEff;

    fwlite::Handle<int> h_jet2tagEff;
    fwlite::Handle<int> h_AK8jet2tagEff;
    
    fwlite::Handle<unsigned int> h_npv;

    fwlite::Handle<double> h_jet1ptEff;
    fwlite::Handle<double> h_jet1NsubjEff;
    fwlite::Handle<double> h_jet1minmassEff;
    fwlite::Handle<double> h_jet1topMassEff ;
    fwlite::Handle<double> h_AK8jet1filteredMassEff;
    fwlite::Handle<double> h_AK8jet1prunedMassEff;
    fwlite::Handle<double> h_AK8jet1trimmedMassEff;

    fwlite::Handle<double> h_jet2ptEff;
    fwlite::Handle<double> h_jet2NsubjEff;
    fwlite::Handle<double> h_jet2minmassEff;
    fwlite::Handle<double> h_jet2topMassEff ;
    fwlite::Handle<double> h_AK8jet2filteredMassEff;
    fwlite::Handle<double> h_AK8jet2prunedMassEff;
    fwlite::Handle<double> h_AK8jet2trimmedMassEff;

    fwlite::Handle<vector<reco::Candidate::PolarLorentzVector>> h_jet1SubjetP4;
    fwlite::Handle<vector<reco::Candidate::PolarLorentzVector>> h_jet2SubjetP4;

    h_jet1tagEff.getByLabel(ev_ZPrime,"miniAOD","jet1tagEff","MiniAOD");
    h_jet2tagEff.getByLabel(ev_ZPrime,"miniAOD","jet2tagEff","MiniAOD");
    h_AK8jet1tagEff.getByLabel(ev_ZPrime,"miniAOD","AK8jet1tagEff","MiniAOD");
    h_AK8jet2tagEff.getByLabel(ev_ZPrime,"miniAOD","AK8jet2tagEff","MiniAOD");

    h_npv.getByLabel(ev_ZPrime,"miniAOD","npv","MiniAOD");

    h_jet1ptEff.getByLabel(ev_ZPrime,"miniAOD","jet1ptEff","MiniAOD");
    h_jet1NsubjEff.getByLabel(ev_ZPrime,"miniAOD","jet1NsubjEff","MiniAOD");
    h_jet1minmassEff.getByLabel(ev_ZPrime,"miniAOD","jet1minmassEff","MiniAOD");
    h_jet1topMassEff.getByLabel(ev_ZPrime,"miniAOD","jet1topMassEff","MiniAOD");
    h_AK8jet1filteredMassEff.getByLabel(ev_ZPrime,"miniAOD","AK8jet1filteredMassEff","MiniAOD");
    h_AK8jet1prunedMassEff.getByLabel(ev_ZPrime,"miniAOD","AK8jet1prunedMassEff","MiniAOD");
    h_AK8jet1trimmedMassEff.getByLabel(ev_ZPrime,"miniAOD","AK8jet1trimmedMassEff","MiniAOD");

    h_jet2ptEff.getByLabel(ev_ZPrime,"miniAOD","jet2ptEff","MiniAOD");
    h_jet2NsubjEff.getByLabel(ev_ZPrime,"miniAOD","jet2NsubjEff","MiniAOD");
    h_jet2minmassEff.getByLabel(ev_ZPrime,"miniAOD","jet2minmassEff","MiniAOD");
    h_jet2topMassEff.getByLabel(ev_ZPrime,"miniAOD","jet2topMassEff","MiniAOD");
    h_AK8jet2filteredMassEff.getByLabel(ev_ZPrime,"miniAOD","AK8jet2filteredMassEff","MiniAOD");
    h_AK8jet2prunedMassEff.getByLabel(ev_ZPrime,"miniAOD","AK8jet2prunedMassEff","MiniAOD");
    h_AK8jet2trimmedMassEff.getByLabel(ev_ZPrime,"miniAOD","AK8jet2trimmedMassEff","MiniAOD");

    h_jet1SubjetP4.getByLabel(ev_ZPrime,"miniAOD","jet1SubjetP4","MiniAOD");
    h_jet2SubjetP4.getByLabel(ev_ZPrime,"miniAOD","jet2SubjetP4","MiniAOD");

    const std::vector<reco::Candidate::PolarLorentzVector>* jet1SubjetP4 = h_jet1SubjetP4.product();
    const std::vector<reco::Candidate::PolarLorentzVector>* jet2SubjetP4 = h_jet2SubjetP4.product();

    int jet1SubjetSize =  jet1SubjetP4->size();
    int jet2SubjetSize =  jet2SubjetP4->size();
    double subjet1Mass = 0;
    double subjet2Mass = 0;

    if (jet1SubjetSize > 2){
      subjet1Mass = (jet1SubjetP4->at(1)+jet1SubjetP4->at(2)+jet1SubjetP4->at(0)).M();
    }
    
    if (jet2SubjetSize > 2){
      subjet2Mass = (jet2SubjetP4->at(1)+jet2SubjetP4->at(2)+jet2SubjetP4->at(0)).M();
    }
  
    //jet mass histograms - after Nsubj and minmass top tagging cuts
    //jet 1
    if(*h_jet1tagEff != -1 && *h_jet1ptEff > ptCut && *h_jet1NsubjEff >= 3 && *h_jet1minmassEff > 50){

      hist_ZPrime_noBtag_ungroomed_jetMass_preMassWindowCut->Fill(*h_jet1topMassEff,w_ZPrime);

      if(jet1SubjetSize > 2){
	hist_ZPrime_noBtag_subjets_jetMass_preMassWindowCut->Fill(subjet1Mass,w_ZPrime);
      }

      if(*h_AK8jet1tagEff != 0){
	if(h_AK8jet1filteredMassEff.isValid()){
	  hist_ZPrime_noBtag_filtered_AK8jetMass_preMassWindowCut->Fill(*h_AK8jet1filteredMassEff,w_ZPrime);
	}
	if(h_AK8jet1prunedMassEff.isValid()){
	  hist_ZPrime_noBtag_pruned_AK8jetMass_preMassWindowCut->Fill(*h_AK8jet1prunedMassEff,w_ZPrime);
	}
	if(h_AK8jet1trimmedMassEff.isValid()){
	  hist_ZPrime_noBtag_trimmed_AK8jetMass_preMassWindowCut->Fill(*h_AK8jet1trimmedMassEff,w_ZPrime);
	}
      }
    }
 
    //jet 2
    if(*h_jet2tagEff != -1 && *h_jet2ptEff > ptCut && *h_jet2NsubjEff >= 3 && *h_jet2minmassEff > 50){

      hist_ZPrime_noBtag_ungroomed_jetMass_preMassWindowCut->Fill(*h_jet2topMassEff,w_ZPrime);

      if(jet2SubjetSize > 2){
        hist_ZPrime_noBtag_subjets_jetMass_preMassWindowCut->Fill(subjet2Mass,w_ZPrime);
      }

      if(*h_AK8jet2tagEff != 0){
	if(h_AK8jet2filteredMassEff.isValid()){
          hist_ZPrime_noBtag_filtered_AK8jetMass_preMassWindowCut->Fill(*h_AK8jet2filteredMassEff,w_ZPrime);
        }
	if(h_AK8jet2prunedMassEff.isValid()){
	  hist_ZPrime_noBtag_pruned_AK8jetMass_preMassWindowCut->Fill(*h_AK8jet2prunedMassEff,w_ZPrime);
	}
	if(h_AK8jet2trimmedMassEff.isValid()){
	  hist_ZPrime_noBtag_trimmed_AK8jetMass_preMassWindowCut->Fill(*h_AK8jet2trimmedMassEff,w_ZPrime);
	}
      }
    }

    //jet mass histograms - no top tagging cuts
    //jet 1
    if(*h_jet1tagEff != -1 && *h_jet1ptEff > ptCut){

      hist_ZPrime_noBtag_ungroomed_jetMass_noTopTagCut->Fill(*h_jet1topMassEff,w_ZPrime);

      if(jet1SubjetSize > 2){
        hist_ZPrime_noBtag_subjets_jetMass_noTopTagCut->Fill(subjet1Mass,w_ZPrime);
      }

      if(*h_AK8jet1tagEff != 0){
	if(h_AK8jet1filteredMassEff.isValid()){
	  hist_ZPrime_noBtag_filtered_AK8jetMass_noTopTagCut->Fill(*h_AK8jet1filteredMassEff,w_ZPrime);
	}
	if(h_AK8jet1prunedMassEff.isValid()){
	  hist_ZPrime_noBtag_pruned_AK8jetMass_noTopTagCut->Fill(*h_AK8jet1prunedMassEff,w_ZPrime);
	}
	if(h_AK8jet1trimmedMassEff.isValid()){
	  hist_ZPrime_noBtag_trimmed_AK8jetMass_noTopTagCut->Fill(*h_AK8jet1trimmedMassEff,w_ZPrime);
	}
      }
    }
 
    //jet 2
    if(*h_jet2tagEff != -1 && *h_jet2ptEff > ptCut){

      hist_ZPrime_noBtag_ungroomed_jetMass_noTopTagCut->Fill(*h_jet2topMassEff,w_ZPrime);

      if(jet2SubjetSize > 2){
        hist_ZPrime_noBtag_subjets_jetMass_noTopTagCut->Fill(subjet2Mass,w_ZPrime);
      }

      if(*h_AK8jet2tagEff != 0){
	if(h_AK8jet2filteredMassEff.isValid()){
          hist_ZPrime_noBtag_filtered_AK8jetMass_noTopTagCut->Fill(*h_AK8jet2filteredMassEff,w_ZPrime);
        }
	if(h_AK8jet2prunedMassEff.isValid()){
	  hist_ZPrime_noBtag_pruned_AK8jetMass_noTopTagCut->Fill(*h_AK8jet2prunedMassEff,w_ZPrime);
	}
	if(h_AK8jet2trimmedMassEff.isValid()){
	  hist_ZPrime_noBtag_trimmed_AK8jetMass_noTopTagCut->Fill(*h_AK8jet2trimmedMassEff,w_ZPrime);
	}
      }
    }
  }

  ///////////////////
  ////Background
  ///////////////////

  ////300 to 470 pt QCD
  vector<string> QCDFileNames_300to470;

  string QCDline_300to470;
  ifstream QCDFile_300to470 ("rootFiles_QCD_pt300to470_13TeV.txt");
  if (QCDFile_300to470.is_open()){
      while ( getline (QCDFile_300to470,QCDline_300to470) )
	{
	  QCDFileNames_300to470.push_back(QCDline_300to470);
	}
      QCDFile_300to470.close();
    }
  
  //fileNames.push_back("/uscms_data/d3/camclean/CSA14/topTaggingEfficiency/CMSSW_7_0_6_patch1/src/Analysis/analyzeMiniAOD/RSGluonToTT_M_4000_08_19_2014/res/miniAOD*.root");

  fwlite::ChainEvent ev_300to470_QCD(QCDFileNames_300to470);

  for( ev_300to470_QCD.toBegin(); ! ev_300to470_QCD.atEnd(); ++ev_300to470_QCD) {
    fwlite::Handle<int> h_jet1tagEff;
    fwlite::Handle<int> h_AK8jet1tagEff;

    fwlite::Handle<int> h_jet2tagEff;
    fwlite::Handle<int> h_AK8jet2tagEff;
    
    fwlite::Handle<unsigned int> h_npv;

    fwlite::Handle<double> h_jet1ptEff;
    fwlite::Handle<double> h_jet1NsubjEff;
    fwlite::Handle<double> h_jet1minmassEff;
    fwlite::Handle<double> h_jet1topMassEff ;
    fwlite::Handle<double> h_AK8jet1filteredMassEff;
    fwlite::Handle<double> h_AK8jet1prunedMassEff;
    fwlite::Handle<double> h_AK8jet1trimmedMassEff;

    fwlite::Handle<double> h_jet2ptEff;
    fwlite::Handle<double> h_jet2NsubjEff;
    fwlite::Handle<double> h_jet2minmassEff;
    fwlite::Handle<double> h_jet2topMassEff ;
    fwlite::Handle<double> h_AK8jet2filteredMassEff;
    fwlite::Handle<double> h_AK8jet2prunedMassEff;
    fwlite::Handle<double> h_AK8jet2trimmedMassEff;

    fwlite::Handle<vector<reco::Candidate::PolarLorentzVector>> h_jet1SubjetP4;
    fwlite::Handle<vector<reco::Candidate::PolarLorentzVector>> h_jet2SubjetP4;

    h_jet1tagEff.getByLabel(ev_300to470_QCD,"miniAOD","jet1tagEff","MiniAOD");
    h_jet2tagEff.getByLabel(ev_300to470_QCD,"miniAOD","jet2tagEff","MiniAOD");
    h_AK8jet1tagEff.getByLabel(ev_300to470_QCD,"miniAOD","AK8jet1tagEff","MiniAOD");
    h_AK8jet2tagEff.getByLabel(ev_300to470_QCD,"miniAOD","AK8jet2tagEff","MiniAOD");

    h_npv.getByLabel(ev_300to470_QCD,"miniAOD","npv","MiniAOD");

    h_jet1ptEff.getByLabel(ev_300to470_QCD,"miniAOD","jet1ptEff","MiniAOD");
    h_jet1NsubjEff.getByLabel(ev_300to470_QCD,"miniAOD","jet1NsubjEff","MiniAOD");
    h_jet1minmassEff.getByLabel(ev_300to470_QCD,"miniAOD","jet1minmassEff","MiniAOD");
    h_jet1topMassEff.getByLabel(ev_300to470_QCD,"miniAOD","jet1topMassEff","MiniAOD");
    h_AK8jet1filteredMassEff.getByLabel(ev_300to470_QCD,"miniAOD","AK8jet1filteredMassEff","MiniAOD");
    h_AK8jet1prunedMassEff.getByLabel(ev_300to470_QCD,"miniAOD","AK8jet1prunedMassEff","MiniAOD");
    h_AK8jet1trimmedMassEff.getByLabel(ev_300to470_QCD,"miniAOD","AK8jet1trimmedMassEff","MiniAOD");

    h_jet2ptEff.getByLabel(ev_300to470_QCD,"miniAOD","jet2ptEff","MiniAOD");
    h_jet2NsubjEff.getByLabel(ev_300to470_QCD,"miniAOD","jet2NsubjEff","MiniAOD");
    h_jet2minmassEff.getByLabel(ev_300to470_QCD,"miniAOD","jet2minmassEff","MiniAOD");
    h_jet2topMassEff.getByLabel(ev_300to470_QCD,"miniAOD","jet2topMassEff","MiniAOD");
    h_AK8jet2filteredMassEff.getByLabel(ev_300to470_QCD,"miniAOD","AK8jet2filteredMassEff","MiniAOD");
    h_AK8jet2prunedMassEff.getByLabel(ev_300to470_QCD,"miniAOD","AK8jet2prunedMassEff","MiniAOD");
    h_AK8jet2trimmedMassEff.getByLabel(ev_300to470_QCD,"miniAOD","AK8jet2trimmedMassEff","MiniAOD");

    h_jet1SubjetP4.getByLabel(ev_300to470_QCD,"miniAOD","jet1SubjetP4","MiniAOD");
    h_jet2SubjetP4.getByLabel(ev_300to470_QCD,"miniAOD","jet2SubjetP4","MiniAOD");

    const std::vector<reco::Candidate::PolarLorentzVector>* jet1SubjetP4 = h_jet1SubjetP4.product();
    const std::vector<reco::Candidate::PolarLorentzVector>* jet2SubjetP4 = h_jet2SubjetP4.product();

    int jet1SubjetSize =  jet1SubjetP4->size();
    int jet2SubjetSize =  jet2SubjetP4->size();
    double subjet1Mass = 0;
    double subjet2Mass = 0;

    if (jet1SubjetSize > 2){
      subjet1Mass = (jet1SubjetP4->at(1)+jet1SubjetP4->at(2)+jet1SubjetP4->at(0)).M();
    }
    
    if (jet2SubjetSize > 2){
      subjet2Mass = (jet2SubjetP4->at(1)+jet2SubjetP4->at(2)+jet2SubjetP4->at(0)).M();
    }
  
    //jet mass histograms - after Nsubj and minmass top tagging cuts
    //jet 1
    if(*h_jet1tagEff != -1 && *h_jet1ptEff > ptCut && *h_jet1NsubjEff >= 3 && *h_jet1minmassEff > 50){

      hist_300toInf_QCD_noBtag_ungroomed_jetMass_preMassWindowCut->Fill(*h_jet1topMassEff,w_300to470);

      if(jet1SubjetSize > 2){
	hist_300toInf_QCD_noBtag_subjets_jetMass_preMassWindowCut->Fill(subjet1Mass,w_300to470);
      }

      if(*h_AK8jet1tagEff != 0){
	if(h_AK8jet1filteredMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_filtered_AK8jetMass_preMassWindowCut->Fill(*h_AK8jet1filteredMassEff,w_300to470);
	}
	if(h_AK8jet1prunedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_pruned_AK8jetMass_preMassWindowCut->Fill(*h_AK8jet1prunedMassEff,w_300to470);
	}
	if(h_AK8jet1trimmedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_trimmed_AK8jetMass_preMassWindowCut->Fill(*h_AK8jet1trimmedMassEff,w_300to470);
	}
      }
    }
 
    //jet 2
    if(*h_jet2tagEff != -1 && *h_jet2ptEff > ptCut && *h_jet2NsubjEff >= 3 && *h_jet2minmassEff > 50){

      hist_300toInf_QCD_noBtag_ungroomed_jetMass_preMassWindowCut->Fill(*h_jet2topMassEff,w_300to470);

      if(jet2SubjetSize > 2){
        hist_300toInf_QCD_noBtag_subjets_jetMass_preMassWindowCut->Fill(subjet2Mass,w_300to470);
      }

      if(*h_AK8jet2tagEff != 0){
	if(h_AK8jet2filteredMassEff.isValid()){
          hist_300toInf_QCD_noBtag_filtered_AK8jetMass_preMassWindowCut->Fill(*h_AK8jet2filteredMassEff,w_300to470);
        }
	if(h_AK8jet2prunedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_pruned_AK8jetMass_preMassWindowCut->Fill(*h_AK8jet2prunedMassEff,w_300to470);
	}
	if(h_AK8jet2trimmedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_trimmed_AK8jetMass_preMassWindowCut->Fill(*h_AK8jet2trimmedMassEff,w_300to470);
	}
      }
    }

    //jet mass histograms - no top tagging cuts
    //jet 1
    if(*h_jet1tagEff != -1 && *h_jet1ptEff > ptCut){

      hist_300toInf_QCD_noBtag_ungroomed_jetMass_noTopTagCut->Fill(*h_jet1topMassEff,w_300to470);

      if(jet1SubjetSize > 2){
        hist_300toInf_QCD_noBtag_subjets_jetMass_noTopTagCut->Fill(subjet1Mass,w_300to470);
      }

      if(*h_AK8jet1tagEff != 0){
	if(h_AK8jet1filteredMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_filtered_AK8jetMass_noTopTagCut->Fill(*h_AK8jet1filteredMassEff,w_300to470);
	}
	if(h_AK8jet1prunedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_pruned_AK8jetMass_noTopTagCut->Fill(*h_AK8jet1prunedMassEff,w_300to470);
	}
	if(h_AK8jet1trimmedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_trimmed_AK8jetMass_noTopTagCut->Fill(*h_AK8jet1trimmedMassEff,w_300to470);
	}
      }
    }
 
    //jet 2
    if(*h_jet2tagEff != -1 && *h_jet2ptEff > ptCut){

      hist_300toInf_QCD_noBtag_ungroomed_jetMass_noTopTagCut->Fill(*h_jet2topMassEff,w_300to470);

      if(jet2SubjetSize > 2){
        hist_300toInf_QCD_noBtag_subjets_jetMass_noTopTagCut->Fill(subjet2Mass,w_300to470);
      }

      if(*h_AK8jet2tagEff != 0){
	if(h_AK8jet2filteredMassEff.isValid()){
          hist_300toInf_QCD_noBtag_filtered_AK8jetMass_noTopTagCut->Fill(*h_AK8jet2filteredMassEff,w_300to470);
        }
	if(h_AK8jet2prunedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_pruned_AK8jetMass_noTopTagCut->Fill(*h_AK8jet2prunedMassEff,w_300to470);
	}
	if(h_AK8jet2trimmedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_trimmed_AK8jetMass_noTopTagCut->Fill(*h_AK8jet2trimmedMassEff,w_300to470);
	}
      }
    }
  }

  ////470 to 600 pt QCD
  vector<string> QCDFileNames_470to600;

  string QCDline_470to600;
  ifstream QCDFile_470to600 ("rootFiles_QCD_pt470to600_13TeV.txt");
  if (QCDFile_470to600.is_open()){
      while ( getline (QCDFile_470to600,QCDline_470to600) )
	{
	  QCDFileNames_470to600.push_back(QCDline_470to600);
	}
      QCDFile_470to600.close();
    }
  
  //fileNames.push_back("/uscms_data/d3/camclean/CSA14/topTaggingEfficiency/CMSSW_7_0_6_patch1/src/Analysis/analyzeMiniAOD/RSGluonToTT_M_4000_08_19_2014/res/miniAOD*.root");

  fwlite::ChainEvent ev_470to600_QCD(QCDFileNames_470to600);

  for( ev_470to600_QCD.toBegin(); ! ev_470to600_QCD.atEnd(); ++ev_470to600_QCD) {
    fwlite::Handle<int> h_jet1tagEff;
    fwlite::Handle<int> h_AK8jet1tagEff;

    fwlite::Handle<int> h_jet2tagEff;
    fwlite::Handle<int> h_AK8jet2tagEff;
    
    fwlite::Handle<unsigned int> h_npv;

    fwlite::Handle<double> h_jet1ptEff;
    fwlite::Handle<double> h_jet1NsubjEff;
    fwlite::Handle<double> h_jet1minmassEff;
    fwlite::Handle<double> h_jet1topMassEff ;
    fwlite::Handle<double> h_AK8jet1filteredMassEff;
    fwlite::Handle<double> h_AK8jet1prunedMassEff;
    fwlite::Handle<double> h_AK8jet1trimmedMassEff;

    fwlite::Handle<double> h_jet2ptEff;
    fwlite::Handle<double> h_jet2NsubjEff;
    fwlite::Handle<double> h_jet2minmassEff;
    fwlite::Handle<double> h_jet2topMassEff ;
    fwlite::Handle<double> h_AK8jet2filteredMassEff;
    fwlite::Handle<double> h_AK8jet2prunedMassEff;
    fwlite::Handle<double> h_AK8jet2trimmedMassEff;

    fwlite::Handle<vector<reco::Candidate::PolarLorentzVector>> h_jet1SubjetP4;
    fwlite::Handle<vector<reco::Candidate::PolarLorentzVector>> h_jet2SubjetP4;

    h_jet1tagEff.getByLabel(ev_470to600_QCD,"miniAOD","jet1tagEff","MiniAOD");
    h_jet2tagEff.getByLabel(ev_470to600_QCD,"miniAOD","jet2tagEff","MiniAOD");
    h_AK8jet1tagEff.getByLabel(ev_470to600_QCD,"miniAOD","AK8jet1tagEff","MiniAOD");
    h_AK8jet2tagEff.getByLabel(ev_470to600_QCD,"miniAOD","AK8jet2tagEff","MiniAOD");

    h_npv.getByLabel(ev_470to600_QCD,"miniAOD","npv","MiniAOD");

    h_jet1ptEff.getByLabel(ev_470to600_QCD,"miniAOD","jet1ptEff","MiniAOD");
    h_jet1NsubjEff.getByLabel(ev_470to600_QCD,"miniAOD","jet1NsubjEff","MiniAOD");
    h_jet1minmassEff.getByLabel(ev_470to600_QCD,"miniAOD","jet1minmassEff","MiniAOD");
    h_jet1topMassEff.getByLabel(ev_470to600_QCD,"miniAOD","jet1topMassEff","MiniAOD");
    h_AK8jet1filteredMassEff.getByLabel(ev_470to600_QCD,"miniAOD","AK8jet1filteredMassEff","MiniAOD");
    h_AK8jet1prunedMassEff.getByLabel(ev_470to600_QCD,"miniAOD","AK8jet1prunedMassEff","MiniAOD");
    h_AK8jet1trimmedMassEff.getByLabel(ev_470to600_QCD,"miniAOD","AK8jet1trimmedMassEff","MiniAOD");

    h_jet2ptEff.getByLabel(ev_470to600_QCD,"miniAOD","jet2ptEff","MiniAOD");
    h_jet2NsubjEff.getByLabel(ev_470to600_QCD,"miniAOD","jet2NsubjEff","MiniAOD");
    h_jet2minmassEff.getByLabel(ev_470to600_QCD,"miniAOD","jet2minmassEff","MiniAOD");
    h_jet2topMassEff.getByLabel(ev_470to600_QCD,"miniAOD","jet2topMassEff","MiniAOD");
    h_AK8jet2filteredMassEff.getByLabel(ev_470to600_QCD,"miniAOD","AK8jet2filteredMassEff","MiniAOD");
    h_AK8jet2prunedMassEff.getByLabel(ev_470to600_QCD,"miniAOD","AK8jet2prunedMassEff","MiniAOD");
    h_AK8jet2trimmedMassEff.getByLabel(ev_470to600_QCD,"miniAOD","AK8jet2trimmedMassEff","MiniAOD");

    h_jet1SubjetP4.getByLabel(ev_470to600_QCD,"miniAOD","jet1SubjetP4","MiniAOD");
    h_jet2SubjetP4.getByLabel(ev_470to600_QCD,"miniAOD","jet2SubjetP4","MiniAOD");

    const std::vector<reco::Candidate::PolarLorentzVector>* jet1SubjetP4 = h_jet1SubjetP4.product();
    const std::vector<reco::Candidate::PolarLorentzVector>* jet2SubjetP4 = h_jet2SubjetP4.product();

    int jet1SubjetSize =  jet1SubjetP4->size();
    int jet2SubjetSize =  jet2SubjetP4->size();
    double subjet1Mass = 0;
    double subjet2Mass = 0;

    if (jet1SubjetSize > 2){
      subjet1Mass = (jet1SubjetP4->at(1)+jet1SubjetP4->at(2)+jet1SubjetP4->at(0)).M();
    }
    
    if (jet2SubjetSize > 2){
      subjet2Mass = (jet2SubjetP4->at(1)+jet2SubjetP4->at(2)+jet2SubjetP4->at(0)).M();
    }
  
    //jet mass histograms - after Nsubj and minmass top tagging cuts
    //jet 1
    if(*h_jet1tagEff != -1 && *h_jet1ptEff > ptCut && *h_jet1NsubjEff >= 3 && *h_jet1minmassEff > 50){

      hist_300toInf_QCD_noBtag_ungroomed_jetMass_preMassWindowCut->Fill(*h_jet1topMassEff,w_470to600);

      if(jet1SubjetSize > 2){
	hist_300toInf_QCD_noBtag_subjets_jetMass_preMassWindowCut->Fill(subjet1Mass,w_470to600);
      }

      if(*h_AK8jet1tagEff != 0){
	if(h_AK8jet1filteredMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_filtered_AK8jetMass_preMassWindowCut->Fill(*h_AK8jet1filteredMassEff,w_470to600);
	}
	if(h_AK8jet1prunedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_pruned_AK8jetMass_preMassWindowCut->Fill(*h_AK8jet1prunedMassEff,w_470to600);
	}
	if(h_AK8jet1trimmedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_trimmed_AK8jetMass_preMassWindowCut->Fill(*h_AK8jet1trimmedMassEff,w_470to600);
	}
      }
    }
 
    //jet 2
    if(*h_jet2tagEff != -1 && *h_jet2ptEff > ptCut && *h_jet2NsubjEff >= 3 && *h_jet2minmassEff > 50){

      hist_300toInf_QCD_noBtag_ungroomed_jetMass_preMassWindowCut->Fill(*h_jet2topMassEff,w_470to600);

      if(jet2SubjetSize > 2){
        hist_300toInf_QCD_noBtag_subjets_jetMass_preMassWindowCut->Fill(subjet2Mass,w_470to600);
      }

      if(*h_AK8jet2tagEff != 0){
	if(h_AK8jet2filteredMassEff.isValid()){
          hist_300toInf_QCD_noBtag_filtered_AK8jetMass_preMassWindowCut->Fill(*h_AK8jet2filteredMassEff,w_470to600);
        }
	if(h_AK8jet2prunedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_pruned_AK8jetMass_preMassWindowCut->Fill(*h_AK8jet2prunedMassEff,w_470to600);
	}
	if(h_AK8jet2trimmedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_trimmed_AK8jetMass_preMassWindowCut->Fill(*h_AK8jet2trimmedMassEff,w_470to600);
	}
      }
    }

    //jet mass histograms - no top tagging cuts
    //jet 1
    if(*h_jet1tagEff != -1 && *h_jet1ptEff > ptCut){

      hist_300toInf_QCD_noBtag_ungroomed_jetMass_noTopTagCut->Fill(*h_jet1topMassEff,w_470to600);

      if(jet1SubjetSize > 2){
        hist_300toInf_QCD_noBtag_subjets_jetMass_noTopTagCut->Fill(subjet1Mass,w_470to600);
      }

      if(*h_AK8jet1tagEff != 0){
	if(h_AK8jet1filteredMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_filtered_AK8jetMass_noTopTagCut->Fill(*h_AK8jet1filteredMassEff,w_470to600);
	}
	if(h_AK8jet1prunedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_pruned_AK8jetMass_noTopTagCut->Fill(*h_AK8jet1prunedMassEff,w_470to600);
	}
	if(h_AK8jet1trimmedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_trimmed_AK8jetMass_noTopTagCut->Fill(*h_AK8jet1trimmedMassEff,w_470to600);
	}
      }
    }
 
    //jet 2
    if(*h_jet2tagEff != -1 && *h_jet2ptEff > ptCut){

      hist_300toInf_QCD_noBtag_ungroomed_jetMass_noTopTagCut->Fill(*h_jet2topMassEff,w_470to600);

      if(jet2SubjetSize > 2){
        hist_300toInf_QCD_noBtag_subjets_jetMass_noTopTagCut->Fill(subjet2Mass,w_470to600);
      }

      if(*h_AK8jet2tagEff != 0){
	if(h_AK8jet2filteredMassEff.isValid()){
          hist_300toInf_QCD_noBtag_filtered_AK8jetMass_noTopTagCut->Fill(*h_AK8jet2filteredMassEff,w_470to600);
        }
	if(h_AK8jet2prunedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_pruned_AK8jetMass_noTopTagCut->Fill(*h_AK8jet2prunedMassEff,w_470to600);
	}
	if(h_AK8jet2trimmedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_trimmed_AK8jetMass_noTopTagCut->Fill(*h_AK8jet2trimmedMassEff,w_470to600);
	}
      }
    }
  }

  ////600 to 800 pt QCD
  vector<string> QCDFileNames_600to800;

  string QCDline_600to800;
  ifstream QCDFile_600to800 ("rootFiles_QCD_pt600to800_13TeV.txt");
  if (QCDFile_600to800.is_open()){
      while ( getline (QCDFile_600to800,QCDline_600to800) )
	{
	  QCDFileNames_600to800.push_back(QCDline_600to800);
	}
      QCDFile_600to800.close();
    }
  
  //fileNames.push_back("/uscms_data/d3/camclean/CSA14/topTaggingEfficiency/CMSSW_7_0_6_patch1/src/Analysis/analyzeMiniAOD/RSGluonToTT_M_4000_08_19_2014/res/miniAOD*.root");

  fwlite::ChainEvent ev_600to800_QCD(QCDFileNames_600to800);

  for( ev_600to800_QCD.toBegin(); ! ev_600to800_QCD.atEnd(); ++ev_600to800_QCD) {
    fwlite::Handle<int> h_jet1tagEff;
    fwlite::Handle<int> h_AK8jet1tagEff;

    fwlite::Handle<int> h_jet2tagEff;
    fwlite::Handle<int> h_AK8jet2tagEff;
    
    fwlite::Handle<unsigned int> h_npv;

    fwlite::Handle<double> h_jet1ptEff;
    fwlite::Handle<double> h_jet1NsubjEff;
    fwlite::Handle<double> h_jet1minmassEff;
    fwlite::Handle<double> h_jet1topMassEff ;
    fwlite::Handle<double> h_AK8jet1filteredMassEff;
    fwlite::Handle<double> h_AK8jet1prunedMassEff;
    fwlite::Handle<double> h_AK8jet1trimmedMassEff;

    fwlite::Handle<double> h_jet2ptEff;
    fwlite::Handle<double> h_jet2NsubjEff;
    fwlite::Handle<double> h_jet2minmassEff;
    fwlite::Handle<double> h_jet2topMassEff ;
    fwlite::Handle<double> h_AK8jet2filteredMassEff;
    fwlite::Handle<double> h_AK8jet2prunedMassEff;
    fwlite::Handle<double> h_AK8jet2trimmedMassEff;

    fwlite::Handle<vector<reco::Candidate::PolarLorentzVector>> h_jet1SubjetP4;
    fwlite::Handle<vector<reco::Candidate::PolarLorentzVector>> h_jet2SubjetP4;

    h_jet1tagEff.getByLabel(ev_600to800_QCD,"miniAOD","jet1tagEff","MiniAOD");
    h_jet2tagEff.getByLabel(ev_600to800_QCD,"miniAOD","jet2tagEff","MiniAOD");
    h_AK8jet1tagEff.getByLabel(ev_600to800_QCD,"miniAOD","AK8jet1tagEff","MiniAOD");
    h_AK8jet2tagEff.getByLabel(ev_600to800_QCD,"miniAOD","AK8jet2tagEff","MiniAOD");

    h_npv.getByLabel(ev_600to800_QCD,"miniAOD","npv","MiniAOD");

    h_jet1ptEff.getByLabel(ev_600to800_QCD,"miniAOD","jet1ptEff","MiniAOD");
    h_jet1NsubjEff.getByLabel(ev_600to800_QCD,"miniAOD","jet1NsubjEff","MiniAOD");
    h_jet1minmassEff.getByLabel(ev_600to800_QCD,"miniAOD","jet1minmassEff","MiniAOD");
    h_jet1topMassEff.getByLabel(ev_600to800_QCD,"miniAOD","jet1topMassEff","MiniAOD");
    h_AK8jet1filteredMassEff.getByLabel(ev_600to800_QCD,"miniAOD","AK8jet1filteredMassEff","MiniAOD");
    h_AK8jet1prunedMassEff.getByLabel(ev_600to800_QCD,"miniAOD","AK8jet1prunedMassEff","MiniAOD");
    h_AK8jet1trimmedMassEff.getByLabel(ev_600to800_QCD,"miniAOD","AK8jet1trimmedMassEff","MiniAOD");

    h_jet2ptEff.getByLabel(ev_600to800_QCD,"miniAOD","jet2ptEff","MiniAOD");
    h_jet2NsubjEff.getByLabel(ev_600to800_QCD,"miniAOD","jet2NsubjEff","MiniAOD");
    h_jet2minmassEff.getByLabel(ev_600to800_QCD,"miniAOD","jet2minmassEff","MiniAOD");
    h_jet2topMassEff.getByLabel(ev_600to800_QCD,"miniAOD","jet2topMassEff","MiniAOD");
    h_AK8jet2filteredMassEff.getByLabel(ev_600to800_QCD,"miniAOD","AK8jet2filteredMassEff","MiniAOD");
    h_AK8jet2prunedMassEff.getByLabel(ev_600to800_QCD,"miniAOD","AK8jet2prunedMassEff","MiniAOD");
    h_AK8jet2trimmedMassEff.getByLabel(ev_600to800_QCD,"miniAOD","AK8jet2trimmedMassEff","MiniAOD");

    h_jet1SubjetP4.getByLabel(ev_600to800_QCD,"miniAOD","jet1SubjetP4","MiniAOD");
    h_jet2SubjetP4.getByLabel(ev_600to800_QCD,"miniAOD","jet2SubjetP4","MiniAOD");

    const std::vector<reco::Candidate::PolarLorentzVector>* jet1SubjetP4 = h_jet1SubjetP4.product();
    const std::vector<reco::Candidate::PolarLorentzVector>* jet2SubjetP4 = h_jet2SubjetP4.product();

    int jet1SubjetSize =  jet1SubjetP4->size();
    int jet2SubjetSize =  jet2SubjetP4->size();
    double subjet1Mass = 0;
    double subjet2Mass = 0;

    if (jet1SubjetSize > 2){
      subjet1Mass = (jet1SubjetP4->at(1)+jet1SubjetP4->at(2)+jet1SubjetP4->at(0)).M();
    }
    
    if (jet2SubjetSize > 2){
      subjet2Mass = (jet2SubjetP4->at(1)+jet2SubjetP4->at(2)+jet2SubjetP4->at(0)).M();
    }
  
    //jet mass histograms - after Nsubj and minmass top tagging cuts
    //jet 1
    if(*h_jet1tagEff != -1 && *h_jet1ptEff > ptCut && *h_jet1NsubjEff >= 3 && *h_jet1minmassEff > 50){

      hist_300toInf_QCD_noBtag_ungroomed_jetMass_preMassWindowCut->Fill(*h_jet1topMassEff,w_600to800);

      if(jet1SubjetSize > 2){
	hist_300toInf_QCD_noBtag_subjets_jetMass_preMassWindowCut->Fill(subjet1Mass,w_600to800);
      }

      if(*h_AK8jet1tagEff != 0){
	if(h_AK8jet1filteredMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_filtered_AK8jetMass_preMassWindowCut->Fill(*h_AK8jet1filteredMassEff,w_600to800);
	}
	if(h_AK8jet1prunedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_pruned_AK8jetMass_preMassWindowCut->Fill(*h_AK8jet1prunedMassEff,w_600to800);
	}
	if(h_AK8jet1trimmedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_trimmed_AK8jetMass_preMassWindowCut->Fill(*h_AK8jet1trimmedMassEff,w_600to800);
	}
      }
    }
 
    //jet 2
    if(*h_jet2tagEff != -1 && *h_jet2ptEff > ptCut && *h_jet2NsubjEff >= 3 && *h_jet2minmassEff > 50){

      hist_300toInf_QCD_noBtag_ungroomed_jetMass_preMassWindowCut->Fill(*h_jet2topMassEff,w_600to800);

      if(jet2SubjetSize > 2){
        hist_300toInf_QCD_noBtag_subjets_jetMass_preMassWindowCut->Fill(subjet2Mass,w_600to800);
      }

      if(*h_AK8jet2tagEff != 0){
	if(h_AK8jet2filteredMassEff.isValid()){
          hist_300toInf_QCD_noBtag_filtered_AK8jetMass_preMassWindowCut->Fill(*h_AK8jet2filteredMassEff,w_600to800);
        }
	if(h_AK8jet2prunedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_pruned_AK8jetMass_preMassWindowCut->Fill(*h_AK8jet2prunedMassEff,w_600to800);
	}
	if(h_AK8jet2trimmedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_trimmed_AK8jetMass_preMassWindowCut->Fill(*h_AK8jet2trimmedMassEff,w_600to800);
	}
      }
    }

    //jet mass histograms - no top tagging cuts
    //jet 1
    if(*h_jet1tagEff != -1 && *h_jet1ptEff > ptCut){

      hist_300toInf_QCD_noBtag_ungroomed_jetMass_noTopTagCut->Fill(*h_jet1topMassEff,w_600to800);

      if(jet1SubjetSize > 2){
        hist_300toInf_QCD_noBtag_subjets_jetMass_noTopTagCut->Fill(subjet1Mass,w_600to800);
      }

      if(*h_AK8jet1tagEff != 0){
	if(h_AK8jet1filteredMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_filtered_AK8jetMass_noTopTagCut->Fill(*h_AK8jet1filteredMassEff,w_600to800);
	}
	if(h_AK8jet1prunedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_pruned_AK8jetMass_noTopTagCut->Fill(*h_AK8jet1prunedMassEff,w_600to800);
	}
	if(h_AK8jet1trimmedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_trimmed_AK8jetMass_noTopTagCut->Fill(*h_AK8jet1trimmedMassEff,w_600to800);
	}
      }
    }
 
    //jet 2
    if(*h_jet2tagEff != -1 && *h_jet2ptEff > ptCut){

      hist_300toInf_QCD_noBtag_ungroomed_jetMass_noTopTagCut->Fill(*h_jet2topMassEff,w_600to800);

      if(jet2SubjetSize > 2){
        hist_300toInf_QCD_noBtag_subjets_jetMass_noTopTagCut->Fill(subjet2Mass,w_600to800);
      }

      if(*h_AK8jet2tagEff != 0){
	if(h_AK8jet2filteredMassEff.isValid()){
          hist_300toInf_QCD_noBtag_filtered_AK8jetMass_noTopTagCut->Fill(*h_AK8jet2filteredMassEff,w_600to800);
        }
	if(h_AK8jet2prunedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_pruned_AK8jetMass_noTopTagCut->Fill(*h_AK8jet2prunedMassEff,w_600to800);
	}
	if(h_AK8jet2trimmedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_trimmed_AK8jetMass_noTopTagCut->Fill(*h_AK8jet2trimmedMassEff,w_600to800);
	}
      }
    }
  }

  ////800 to 1000 pt QCD
  vector<string> QCDFileNames_800to1000;

  string QCDline_800to1000;
  ifstream QCDFile_800to1000 ("rootFiles_QCD_pt800to1000_13TeV.txt");
  if (QCDFile_800to1000.is_open()){
      while ( getline (QCDFile_800to1000,QCDline_800to1000) )
	{
	  QCDFileNames_800to1000.push_back(QCDline_800to1000);
	}
      QCDFile_800to1000.close();
    }
  
  //fileNames.push_back("/uscms_data/d3/camclean/CSA14/topTaggingEfficiency/CMSSW_7_0_6_patch1/src/Analysis/analyzeMiniAOD/RSGluonToTT_M_4000_08_19_2014/res/miniAOD*.root");

  fwlite::ChainEvent ev_800to1000_QCD(QCDFileNames_800to1000);

  for( ev_800to1000_QCD.toBegin(); ! ev_800to1000_QCD.atEnd(); ++ev_800to1000_QCD) {
    fwlite::Handle<int> h_jet1tagEff;
    fwlite::Handle<int> h_AK8jet1tagEff;

    fwlite::Handle<int> h_jet2tagEff;
    fwlite::Handle<int> h_AK8jet2tagEff;
    
    fwlite::Handle<unsigned int> h_npv;

    fwlite::Handle<double> h_jet1ptEff;
    fwlite::Handle<double> h_jet1NsubjEff;
    fwlite::Handle<double> h_jet1minmassEff;
    fwlite::Handle<double> h_jet1topMassEff ;
    fwlite::Handle<double> h_AK8jet1filteredMassEff;
    fwlite::Handle<double> h_AK8jet1prunedMassEff;
    fwlite::Handle<double> h_AK8jet1trimmedMassEff;

    fwlite::Handle<double> h_jet2ptEff;
    fwlite::Handle<double> h_jet2NsubjEff;
    fwlite::Handle<double> h_jet2minmassEff;
    fwlite::Handle<double> h_jet2topMassEff ;
    fwlite::Handle<double> h_AK8jet2filteredMassEff;
    fwlite::Handle<double> h_AK8jet2prunedMassEff;
    fwlite::Handle<double> h_AK8jet2trimmedMassEff;

    fwlite::Handle<vector<reco::Candidate::PolarLorentzVector>> h_jet1SubjetP4;
    fwlite::Handle<vector<reco::Candidate::PolarLorentzVector>> h_jet2SubjetP4;

    h_jet1tagEff.getByLabel(ev_800to1000_QCD,"miniAOD","jet1tagEff","MiniAOD");
    h_jet2tagEff.getByLabel(ev_800to1000_QCD,"miniAOD","jet2tagEff","MiniAOD");
    h_AK8jet1tagEff.getByLabel(ev_800to1000_QCD,"miniAOD","AK8jet1tagEff","MiniAOD");
    h_AK8jet2tagEff.getByLabel(ev_800to1000_QCD,"miniAOD","AK8jet2tagEff","MiniAOD");

    h_npv.getByLabel(ev_800to1000_QCD,"miniAOD","npv","MiniAOD");

    h_jet1ptEff.getByLabel(ev_800to1000_QCD,"miniAOD","jet1ptEff","MiniAOD");
    h_jet1NsubjEff.getByLabel(ev_800to1000_QCD,"miniAOD","jet1NsubjEff","MiniAOD");
    h_jet1minmassEff.getByLabel(ev_800to1000_QCD,"miniAOD","jet1minmassEff","MiniAOD");
    h_jet1topMassEff.getByLabel(ev_800to1000_QCD,"miniAOD","jet1topMassEff","MiniAOD");
    h_AK8jet1filteredMassEff.getByLabel(ev_800to1000_QCD,"miniAOD","AK8jet1filteredMassEff","MiniAOD");
    h_AK8jet1prunedMassEff.getByLabel(ev_800to1000_QCD,"miniAOD","AK8jet1prunedMassEff","MiniAOD");
    h_AK8jet1trimmedMassEff.getByLabel(ev_800to1000_QCD,"miniAOD","AK8jet1trimmedMassEff","MiniAOD");

    h_jet2ptEff.getByLabel(ev_800to1000_QCD,"miniAOD","jet2ptEff","MiniAOD");
    h_jet2NsubjEff.getByLabel(ev_800to1000_QCD,"miniAOD","jet2NsubjEff","MiniAOD");
    h_jet2minmassEff.getByLabel(ev_800to1000_QCD,"miniAOD","jet2minmassEff","MiniAOD");
    h_jet2topMassEff.getByLabel(ev_800to1000_QCD,"miniAOD","jet2topMassEff","MiniAOD");
    h_AK8jet2filteredMassEff.getByLabel(ev_800to1000_QCD,"miniAOD","AK8jet2filteredMassEff","MiniAOD");
    h_AK8jet2prunedMassEff.getByLabel(ev_800to1000_QCD,"miniAOD","AK8jet2prunedMassEff","MiniAOD");
    h_AK8jet2trimmedMassEff.getByLabel(ev_800to1000_QCD,"miniAOD","AK8jet2trimmedMassEff","MiniAOD");

    h_jet1SubjetP4.getByLabel(ev_800to1000_QCD,"miniAOD","jet1SubjetP4","MiniAOD");
    h_jet2SubjetP4.getByLabel(ev_800to1000_QCD,"miniAOD","jet2SubjetP4","MiniAOD");

    const std::vector<reco::Candidate::PolarLorentzVector>* jet1SubjetP4 = h_jet1SubjetP4.product();
    const std::vector<reco::Candidate::PolarLorentzVector>* jet2SubjetP4 = h_jet2SubjetP4.product();

    int jet1SubjetSize =  jet1SubjetP4->size();
    int jet2SubjetSize =  jet2SubjetP4->size();
    double subjet1Mass = 0;
    double subjet2Mass = 0;

    if (jet1SubjetSize > 2){
      subjet1Mass = (jet1SubjetP4->at(1)+jet1SubjetP4->at(2)+jet1SubjetP4->at(0)).M();
    }
    
    if (jet2SubjetSize > 2){
      subjet2Mass = (jet2SubjetP4->at(1)+jet2SubjetP4->at(2)+jet2SubjetP4->at(0)).M();
    }
  
    //jet mass histograms - after Nsubj and minmass top tagging cuts
    //jet 1
    if(*h_jet1tagEff != -1 && *h_jet1ptEff > ptCut && *h_jet1NsubjEff >= 3 && *h_jet1minmassEff > 50){

      hist_300toInf_QCD_noBtag_ungroomed_jetMass_preMassWindowCut->Fill(*h_jet1topMassEff,w_800to1000);

      if(jet1SubjetSize > 2){
	hist_300toInf_QCD_noBtag_subjets_jetMass_preMassWindowCut->Fill(subjet1Mass,w_800to1000);
      }

      if(*h_AK8jet1tagEff != 0){
	if(h_AK8jet1filteredMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_filtered_AK8jetMass_preMassWindowCut->Fill(*h_AK8jet1filteredMassEff,w_800to1000);
	}
	if(h_AK8jet1prunedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_pruned_AK8jetMass_preMassWindowCut->Fill(*h_AK8jet1prunedMassEff,w_800to1000);
	}
	if(h_AK8jet1trimmedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_trimmed_AK8jetMass_preMassWindowCut->Fill(*h_AK8jet1trimmedMassEff,w_800to1000);
	}
      }
    }
 
    //jet 2
    if(*h_jet2tagEff != -1 && *h_jet2ptEff > ptCut && *h_jet2NsubjEff >= 3 && *h_jet2minmassEff > 50){

      hist_300toInf_QCD_noBtag_ungroomed_jetMass_preMassWindowCut->Fill(*h_jet2topMassEff,w_800to1000);

      if(jet2SubjetSize > 2){
        hist_300toInf_QCD_noBtag_subjets_jetMass_preMassWindowCut->Fill(subjet2Mass,w_800to1000);
      }

      if(*h_AK8jet2tagEff != 0){
	if(h_AK8jet2filteredMassEff.isValid()){
          hist_300toInf_QCD_noBtag_filtered_AK8jetMass_preMassWindowCut->Fill(*h_AK8jet2filteredMassEff,w_800to1000);
        }
	if(h_AK8jet2prunedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_pruned_AK8jetMass_preMassWindowCut->Fill(*h_AK8jet2prunedMassEff,w_800to1000);
	}
	if(h_AK8jet2trimmedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_trimmed_AK8jetMass_preMassWindowCut->Fill(*h_AK8jet2trimmedMassEff,w_800to1000);
	}
      }
    }

    //jet mass histograms - no top tagging cuts
    //jet 1
    if(*h_jet1tagEff != -1 && *h_jet1ptEff > ptCut){

      hist_300toInf_QCD_noBtag_ungroomed_jetMass_noTopTagCut->Fill(*h_jet1topMassEff,w_800to1000);

      if(jet1SubjetSize > 2){
        hist_300toInf_QCD_noBtag_subjets_jetMass_noTopTagCut->Fill(subjet1Mass,w_800to1000);
      }

      if(*h_AK8jet1tagEff != 0){
	if(h_AK8jet1filteredMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_filtered_AK8jetMass_noTopTagCut->Fill(*h_AK8jet1filteredMassEff,w_800to1000);
	}
	if(h_AK8jet1prunedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_pruned_AK8jetMass_noTopTagCut->Fill(*h_AK8jet1prunedMassEff,w_800to1000);
	}
	if(h_AK8jet1trimmedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_trimmed_AK8jetMass_noTopTagCut->Fill(*h_AK8jet1trimmedMassEff,w_800to1000);
	}
      }
    }
 
    //jet 2
    if(*h_jet2tagEff != -1 && *h_jet2ptEff > ptCut){

      hist_300toInf_QCD_noBtag_ungroomed_jetMass_noTopTagCut->Fill(*h_jet2topMassEff,w_800to1000);

      if(jet2SubjetSize > 2){
        hist_300toInf_QCD_noBtag_subjets_jetMass_noTopTagCut->Fill(subjet2Mass,w_800to1000);
      }

      if(*h_AK8jet2tagEff != 0){
	if(h_AK8jet2filteredMassEff.isValid()){
          hist_300toInf_QCD_noBtag_filtered_AK8jetMass_noTopTagCut->Fill(*h_AK8jet2filteredMassEff,w_800to1000);
        }
	if(h_AK8jet2prunedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_pruned_AK8jetMass_noTopTagCut->Fill(*h_AK8jet2prunedMassEff,w_800to1000);
	}
	if(h_AK8jet2trimmedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_trimmed_AK8jetMass_noTopTagCut->Fill(*h_AK8jet2trimmedMassEff,w_800to1000);
	}
      }
    }
  }

  ////1000 to 1400 pt QCD
  vector<string> QCDFileNames_1000to1400;

  string QCDline_1000to1400;
  ifstream QCDFile_1000to1400 ("rootFiles_QCD_pt1000to1400_13TeV.txt");
  if (QCDFile_1000to1400.is_open()){
      while ( getline (QCDFile_1000to1400,QCDline_1000to1400) )
	{
	  QCDFileNames_1000to1400.push_back(QCDline_1000to1400);
	}
      QCDFile_1000to1400.close();
    }
  
  //fileNames.push_back("/uscms_data/d3/camclean/CSA14/topTaggingEfficiency/CMSSW_7_0_6_patch1/src/Analysis/analyzeMiniAOD/RSGluonToTT_M_4000_08_19_2014/res/miniAOD*.root");

  fwlite::ChainEvent ev_1000to1400_QCD(QCDFileNames_1000to1400);

  for( ev_1000to1400_QCD.toBegin(); ! ev_1000to1400_QCD.atEnd(); ++ev_1000to1400_QCD) {
    fwlite::Handle<int> h_jet1tagEff;
    fwlite::Handle<int> h_AK8jet1tagEff;

    fwlite::Handle<int> h_jet2tagEff;
    fwlite::Handle<int> h_AK8jet2tagEff;
    
    fwlite::Handle<unsigned int> h_npv;

    fwlite::Handle<double> h_jet1ptEff;
    fwlite::Handle<double> h_jet1NsubjEff;
    fwlite::Handle<double> h_jet1minmassEff;
    fwlite::Handle<double> h_jet1topMassEff ;
    fwlite::Handle<double> h_AK8jet1filteredMassEff;
    fwlite::Handle<double> h_AK8jet1prunedMassEff;
    fwlite::Handle<double> h_AK8jet1trimmedMassEff;

    fwlite::Handle<double> h_jet2ptEff;
    fwlite::Handle<double> h_jet2NsubjEff;
    fwlite::Handle<double> h_jet2minmassEff;
    fwlite::Handle<double> h_jet2topMassEff ;
    fwlite::Handle<double> h_AK8jet2filteredMassEff;
    fwlite::Handle<double> h_AK8jet2prunedMassEff;
    fwlite::Handle<double> h_AK8jet2trimmedMassEff;

    fwlite::Handle<vector<reco::Candidate::PolarLorentzVector>> h_jet1SubjetP4;
    fwlite::Handle<vector<reco::Candidate::PolarLorentzVector>> h_jet2SubjetP4;

    h_jet1tagEff.getByLabel(ev_1000to1400_QCD,"miniAOD","jet1tagEff","MiniAOD");
    h_jet2tagEff.getByLabel(ev_1000to1400_QCD,"miniAOD","jet2tagEff","MiniAOD");
    h_AK8jet1tagEff.getByLabel(ev_1000to1400_QCD,"miniAOD","AK8jet1tagEff","MiniAOD");
    h_AK8jet2tagEff.getByLabel(ev_1000to1400_QCD,"miniAOD","AK8jet2tagEff","MiniAOD");

    h_npv.getByLabel(ev_1000to1400_QCD,"miniAOD","npv","MiniAOD");

    h_jet1ptEff.getByLabel(ev_1000to1400_QCD,"miniAOD","jet1ptEff","MiniAOD");
    h_jet1NsubjEff.getByLabel(ev_1000to1400_QCD,"miniAOD","jet1NsubjEff","MiniAOD");
    h_jet1minmassEff.getByLabel(ev_1000to1400_QCD,"miniAOD","jet1minmassEff","MiniAOD");
    h_jet1topMassEff.getByLabel(ev_1000to1400_QCD,"miniAOD","jet1topMassEff","MiniAOD");
    h_AK8jet1filteredMassEff.getByLabel(ev_1000to1400_QCD,"miniAOD","AK8jet1filteredMassEff","MiniAOD");
    h_AK8jet1prunedMassEff.getByLabel(ev_1000to1400_QCD,"miniAOD","AK8jet1prunedMassEff","MiniAOD");
    h_AK8jet1trimmedMassEff.getByLabel(ev_1000to1400_QCD,"miniAOD","AK8jet1trimmedMassEff","MiniAOD");

    h_jet2ptEff.getByLabel(ev_1000to1400_QCD,"miniAOD","jet2ptEff","MiniAOD");
    h_jet2NsubjEff.getByLabel(ev_1000to1400_QCD,"miniAOD","jet2NsubjEff","MiniAOD");
    h_jet2minmassEff.getByLabel(ev_1000to1400_QCD,"miniAOD","jet2minmassEff","MiniAOD");
    h_jet2topMassEff.getByLabel(ev_1000to1400_QCD,"miniAOD","jet2topMassEff","MiniAOD");
    h_AK8jet2filteredMassEff.getByLabel(ev_1000to1400_QCD,"miniAOD","AK8jet2filteredMassEff","MiniAOD");
    h_AK8jet2prunedMassEff.getByLabel(ev_1000to1400_QCD,"miniAOD","AK8jet2prunedMassEff","MiniAOD");
    h_AK8jet2trimmedMassEff.getByLabel(ev_1000to1400_QCD,"miniAOD","AK8jet2trimmedMassEff","MiniAOD");

    h_jet1SubjetP4.getByLabel(ev_1000to1400_QCD,"miniAOD","jet1SubjetP4","MiniAOD");
    h_jet2SubjetP4.getByLabel(ev_1000to1400_QCD,"miniAOD","jet2SubjetP4","MiniAOD");

    const std::vector<reco::Candidate::PolarLorentzVector>* jet1SubjetP4 = h_jet1SubjetP4.product();
    const std::vector<reco::Candidate::PolarLorentzVector>* jet2SubjetP4 = h_jet2SubjetP4.product();

    int jet1SubjetSize =  jet1SubjetP4->size();
    int jet2SubjetSize =  jet2SubjetP4->size();
    double subjet1Mass = 0;
    double subjet2Mass = 0;

    if (jet1SubjetSize > 2){
      subjet1Mass = (jet1SubjetP4->at(1)+jet1SubjetP4->at(2)+jet1SubjetP4->at(0)).M();
    }
    
    if (jet2SubjetSize > 2){
      subjet2Mass = (jet2SubjetP4->at(1)+jet2SubjetP4->at(2)+jet2SubjetP4->at(0)).M();
    }
  
    //jet mass histograms - after Nsubj and minmass top tagging cuts
    //jet 1
    if(*h_jet1tagEff != -1 && *h_jet1ptEff > ptCut && *h_jet1NsubjEff >= 3 && *h_jet1minmassEff > 50){

      hist_300toInf_QCD_noBtag_ungroomed_jetMass_preMassWindowCut->Fill(*h_jet1topMassEff,w_1000to1400);

      if(jet1SubjetSize > 2){
	hist_300toInf_QCD_noBtag_subjets_jetMass_preMassWindowCut->Fill(subjet1Mass,w_1000to1400);
      }

      if(*h_AK8jet1tagEff != 0){
	if(h_AK8jet1filteredMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_filtered_AK8jetMass_preMassWindowCut->Fill(*h_AK8jet1filteredMassEff,w_1000to1400);
	}
	if(h_AK8jet1prunedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_pruned_AK8jetMass_preMassWindowCut->Fill(*h_AK8jet1prunedMassEff,w_1000to1400);
	}
	if(h_AK8jet1trimmedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_trimmed_AK8jetMass_preMassWindowCut->Fill(*h_AK8jet1trimmedMassEff,w_1000to1400);
	}
      }
    }
 
    //jet 2
    if(*h_jet2tagEff != -1 && *h_jet2ptEff > ptCut && *h_jet2NsubjEff >= 3 && *h_jet2minmassEff > 50){

      hist_300toInf_QCD_noBtag_ungroomed_jetMass_preMassWindowCut->Fill(*h_jet2topMassEff,w_1000to1400);

      if(jet2SubjetSize > 2){
        hist_300toInf_QCD_noBtag_subjets_jetMass_preMassWindowCut->Fill(subjet2Mass,w_1000to1400);
      }

      if(*h_AK8jet2tagEff != 0){
	if(h_AK8jet2filteredMassEff.isValid()){
          hist_300toInf_QCD_noBtag_filtered_AK8jetMass_preMassWindowCut->Fill(*h_AK8jet2filteredMassEff,w_1000to1400);
        }
	if(h_AK8jet2prunedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_pruned_AK8jetMass_preMassWindowCut->Fill(*h_AK8jet2prunedMassEff,w_1000to1400);
	}
	if(h_AK8jet2trimmedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_trimmed_AK8jetMass_preMassWindowCut->Fill(*h_AK8jet2trimmedMassEff,w_1000to1400);
	}
      }
    }

    //jet mass histograms - no top tagging cuts
    //jet 1
    if(*h_jet1tagEff != -1 && *h_jet1ptEff > ptCut){

      hist_300toInf_QCD_noBtag_ungroomed_jetMass_noTopTagCut->Fill(*h_jet1topMassEff,w_1000to1400);

      if(jet1SubjetSize > 2){
        hist_300toInf_QCD_noBtag_subjets_jetMass_noTopTagCut->Fill(subjet1Mass,w_1000to1400);
      }

      if(*h_AK8jet1tagEff != 0){
	if(h_AK8jet1filteredMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_filtered_AK8jetMass_noTopTagCut->Fill(*h_AK8jet1filteredMassEff,w_1000to1400);
	}
	if(h_AK8jet1prunedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_pruned_AK8jetMass_noTopTagCut->Fill(*h_AK8jet1prunedMassEff,w_1000to1400);
	}
	if(h_AK8jet1trimmedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_trimmed_AK8jetMass_noTopTagCut->Fill(*h_AK8jet1trimmedMassEff,w_1000to1400);
	}
      }
    }
 
    //jet 2
    if(*h_jet2tagEff != -1 && *h_jet2ptEff > ptCut){

      hist_300toInf_QCD_noBtag_ungroomed_jetMass_noTopTagCut->Fill(*h_jet2topMassEff,w_1000to1400);

      if(jet2SubjetSize > 2){
        hist_300toInf_QCD_noBtag_subjets_jetMass_noTopTagCut->Fill(subjet2Mass,w_1000to1400);
      }

      if(*h_AK8jet2tagEff != 0){
	if(h_AK8jet2filteredMassEff.isValid()){
          hist_300toInf_QCD_noBtag_filtered_AK8jetMass_noTopTagCut->Fill(*h_AK8jet2filteredMassEff,w_1000to1400);
        }
	if(h_AK8jet2prunedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_pruned_AK8jetMass_noTopTagCut->Fill(*h_AK8jet2prunedMassEff,w_1000to1400);
	}
	if(h_AK8jet2trimmedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_trimmed_AK8jetMass_noTopTagCut->Fill(*h_AK8jet2trimmedMassEff,w_1000to1400);
	}
      }
    }
  }

  ////1400 to 1800 pt QCD
  vector<string> QCDFileNames_1400to1800;

  string QCDline_1400to1800;
  ifstream QCDFile_1400to1800 ("rootFiles_QCD_pt1400to1800_13TeV.txt");
  if (QCDFile_1400to1800.is_open()){
      while ( getline (QCDFile_1400to1800,QCDline_1400to1800) )
	{
	  QCDFileNames_1400to1800.push_back(QCDline_1400to1800);
	}
      QCDFile_1400to1800.close();
    }
  
  //fileNames.push_back("/uscms_data/d3/camclean/CSA14/topTaggingEfficiency/CMSSW_7_0_6_patch1/src/Analysis/analyzeMiniAOD/RSGluonToTT_M_4000_08_19_2014/res/miniAOD*.root");

  fwlite::ChainEvent ev_1400to1800_QCD(QCDFileNames_1400to1800);

  for( ev_1400to1800_QCD.toBegin(); ! ev_1400to1800_QCD.atEnd(); ++ev_1400to1800_QCD) {
    fwlite::Handle<int> h_jet1tagEff;
    fwlite::Handle<int> h_AK8jet1tagEff;

    fwlite::Handle<int> h_jet2tagEff;
    fwlite::Handle<int> h_AK8jet2tagEff;
    
    fwlite::Handle<unsigned int> h_npv;

    fwlite::Handle<double> h_jet1ptEff;
    fwlite::Handle<double> h_jet1NsubjEff;
    fwlite::Handle<double> h_jet1minmassEff;
    fwlite::Handle<double> h_jet1topMassEff ;
    fwlite::Handle<double> h_AK8jet1filteredMassEff;
    fwlite::Handle<double> h_AK8jet1prunedMassEff;
    fwlite::Handle<double> h_AK8jet1trimmedMassEff;

    fwlite::Handle<double> h_jet2ptEff;
    fwlite::Handle<double> h_jet2NsubjEff;
    fwlite::Handle<double> h_jet2minmassEff;
    fwlite::Handle<double> h_jet2topMassEff ;
    fwlite::Handle<double> h_AK8jet2filteredMassEff;
    fwlite::Handle<double> h_AK8jet2prunedMassEff;
    fwlite::Handle<double> h_AK8jet2trimmedMassEff;

    fwlite::Handle<vector<reco::Candidate::PolarLorentzVector>> h_jet1SubjetP4;
    fwlite::Handle<vector<reco::Candidate::PolarLorentzVector>> h_jet2SubjetP4;

    h_jet1tagEff.getByLabel(ev_1400to1800_QCD,"miniAOD","jet1tagEff","MiniAOD");
    h_jet2tagEff.getByLabel(ev_1400to1800_QCD,"miniAOD","jet2tagEff","MiniAOD");
    h_AK8jet1tagEff.getByLabel(ev_1400to1800_QCD,"miniAOD","AK8jet1tagEff","MiniAOD");
    h_AK8jet2tagEff.getByLabel(ev_1400to1800_QCD,"miniAOD","AK8jet2tagEff","MiniAOD");

    h_npv.getByLabel(ev_1400to1800_QCD,"miniAOD","npv","MiniAOD");

    h_jet1ptEff.getByLabel(ev_1400to1800_QCD,"miniAOD","jet1ptEff","MiniAOD");
    h_jet1NsubjEff.getByLabel(ev_1400to1800_QCD,"miniAOD","jet1NsubjEff","MiniAOD");
    h_jet1minmassEff.getByLabel(ev_1400to1800_QCD,"miniAOD","jet1minmassEff","MiniAOD");
    h_jet1topMassEff.getByLabel(ev_1400to1800_QCD,"miniAOD","jet1topMassEff","MiniAOD");
    h_AK8jet1filteredMassEff.getByLabel(ev_1400to1800_QCD,"miniAOD","AK8jet1filteredMassEff","MiniAOD");
    h_AK8jet1prunedMassEff.getByLabel(ev_1400to1800_QCD,"miniAOD","AK8jet1prunedMassEff","MiniAOD");
    h_AK8jet1trimmedMassEff.getByLabel(ev_1400to1800_QCD,"miniAOD","AK8jet1trimmedMassEff","MiniAOD");

    h_jet2ptEff.getByLabel(ev_1400to1800_QCD,"miniAOD","jet2ptEff","MiniAOD");
    h_jet2NsubjEff.getByLabel(ev_1400to1800_QCD,"miniAOD","jet2NsubjEff","MiniAOD");
    h_jet2minmassEff.getByLabel(ev_1400to1800_QCD,"miniAOD","jet2minmassEff","MiniAOD");
    h_jet2topMassEff.getByLabel(ev_1400to1800_QCD,"miniAOD","jet2topMassEff","MiniAOD");
    h_AK8jet2filteredMassEff.getByLabel(ev_1400to1800_QCD,"miniAOD","AK8jet2filteredMassEff","MiniAOD");
    h_AK8jet2prunedMassEff.getByLabel(ev_1400to1800_QCD,"miniAOD","AK8jet2prunedMassEff","MiniAOD");
    h_AK8jet2trimmedMassEff.getByLabel(ev_1400to1800_QCD,"miniAOD","AK8jet2trimmedMassEff","MiniAOD");

    h_jet1SubjetP4.getByLabel(ev_1400to1800_QCD,"miniAOD","jet1SubjetP4","MiniAOD");
    h_jet2SubjetP4.getByLabel(ev_1400to1800_QCD,"miniAOD","jet2SubjetP4","MiniAOD");

    const std::vector<reco::Candidate::PolarLorentzVector>* jet1SubjetP4 = h_jet1SubjetP4.product();
    const std::vector<reco::Candidate::PolarLorentzVector>* jet2SubjetP4 = h_jet2SubjetP4.product();

    int jet1SubjetSize =  jet1SubjetP4->size();
    int jet2SubjetSize =  jet2SubjetP4->size();
    double subjet1Mass = 0;
    double subjet2Mass = 0;

    if (jet1SubjetSize > 2){
      subjet1Mass = (jet1SubjetP4->at(1)+jet1SubjetP4->at(2)+jet1SubjetP4->at(0)).M();
    }
    
    if (jet2SubjetSize > 2){
      subjet2Mass = (jet2SubjetP4->at(1)+jet2SubjetP4->at(2)+jet2SubjetP4->at(0)).M();
    }
  
    //jet mass histograms - after Nsubj and minmass top tagging cuts
    //jet 1
    if(*h_jet1tagEff != -1 && *h_jet1ptEff > ptCut && *h_jet1NsubjEff >= 3 && *h_jet1minmassEff > 50){

      hist_300toInf_QCD_noBtag_ungroomed_jetMass_preMassWindowCut->Fill(*h_jet1topMassEff,w_1400to1800);

      if(jet1SubjetSize > 2){
	hist_300toInf_QCD_noBtag_subjets_jetMass_preMassWindowCut->Fill(subjet1Mass,w_1400to1800);
      }

      if(*h_AK8jet1tagEff != 0){
	if(h_AK8jet1filteredMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_filtered_AK8jetMass_preMassWindowCut->Fill(*h_AK8jet1filteredMassEff,w_1400to1800);
	}
	if(h_AK8jet1prunedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_pruned_AK8jetMass_preMassWindowCut->Fill(*h_AK8jet1prunedMassEff,w_1400to1800);
	}
	if(h_AK8jet1trimmedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_trimmed_AK8jetMass_preMassWindowCut->Fill(*h_AK8jet1trimmedMassEff,w_1400to1800);
	}
      }
    }
 
    //jet 2
    if(*h_jet2tagEff != -1 && *h_jet2ptEff > ptCut && *h_jet2NsubjEff >= 3 && *h_jet2minmassEff > 50){

      hist_300toInf_QCD_noBtag_ungroomed_jetMass_preMassWindowCut->Fill(*h_jet2topMassEff,w_1400to1800);

      if(jet2SubjetSize > 2){
        hist_300toInf_QCD_noBtag_subjets_jetMass_preMassWindowCut->Fill(subjet2Mass,w_1400to1800);
      }

      if(*h_AK8jet2tagEff != 0){
	if(h_AK8jet2filteredMassEff.isValid()){
          hist_300toInf_QCD_noBtag_filtered_AK8jetMass_preMassWindowCut->Fill(*h_AK8jet2filteredMassEff,w_1400to1800);
        }
	if(h_AK8jet2prunedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_pruned_AK8jetMass_preMassWindowCut->Fill(*h_AK8jet2prunedMassEff,w_1400to1800);
	}
	if(h_AK8jet2trimmedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_trimmed_AK8jetMass_preMassWindowCut->Fill(*h_AK8jet2trimmedMassEff,w_1400to1800);
	}
      }
    }

    //jet mass histograms - no top tagging cuts
    //jet 1
    if(*h_jet1tagEff != -1 && *h_jet1ptEff > ptCut){

      hist_300toInf_QCD_noBtag_ungroomed_jetMass_noTopTagCut->Fill(*h_jet1topMassEff,w_1400to1800);

      if(jet1SubjetSize > 2){
        hist_300toInf_QCD_noBtag_subjets_jetMass_noTopTagCut->Fill(subjet1Mass,w_1400to1800);
      }

      if(*h_AK8jet1tagEff != 0){
	if(h_AK8jet1filteredMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_filtered_AK8jetMass_noTopTagCut->Fill(*h_AK8jet1filteredMassEff,w_1400to1800);
	}
	if(h_AK8jet1prunedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_pruned_AK8jetMass_noTopTagCut->Fill(*h_AK8jet1prunedMassEff,w_1400to1800);
	}
	if(h_AK8jet1trimmedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_trimmed_AK8jetMass_noTopTagCut->Fill(*h_AK8jet1trimmedMassEff,w_1400to1800);
	}
      }
    }
 
    //jet 2
    if(*h_jet2tagEff != -1 && *h_jet2ptEff > ptCut){

      hist_300toInf_QCD_noBtag_ungroomed_jetMass_noTopTagCut->Fill(*h_jet2topMassEff,w_1400to1800);

      if(jet2SubjetSize > 2){
        hist_300toInf_QCD_noBtag_subjets_jetMass_noTopTagCut->Fill(subjet2Mass,w_1400to1800);
      }

      if(*h_AK8jet2tagEff != 0){
	if(h_AK8jet2filteredMassEff.isValid()){
          hist_300toInf_QCD_noBtag_filtered_AK8jetMass_noTopTagCut->Fill(*h_AK8jet2filteredMassEff,w_1400to1800);
        }
	if(h_AK8jet2prunedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_pruned_AK8jetMass_noTopTagCut->Fill(*h_AK8jet2prunedMassEff,w_1400to1800);
	}
	if(h_AK8jet2trimmedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_trimmed_AK8jetMass_noTopTagCut->Fill(*h_AK8jet2trimmedMassEff,w_1400to1800);
	}
      }
    }
  }

  ////1800 to 2400 pt QCD
  vector<string> QCDFileNames_1800to2400;

  string QCDline_1800to2400;
  ifstream QCDFile_1800to2400 ("rootFiles_QCD_pt1800to2400_13TeV.txt");
  if (QCDFile_1800to2400.is_open()){
      while ( getline (QCDFile_1800to2400,QCDline_1800to2400) )
	{
	  QCDFileNames_1800to2400.push_back(QCDline_1800to2400);
	}
      QCDFile_1800to2400.close();
    }
  
  //fileNames.push_back("/uscms_data/d3/camclean/CSA14/topTaggingEfficiency/CMSSW_7_0_6_patch1/src/Analysis/analyzeMiniAOD/RSGluonToTT_M_4000_08_19_2014/res/miniAOD*.root");

  fwlite::ChainEvent ev_1800to2400_QCD(QCDFileNames_1800to2400);

  for( ev_1800to2400_QCD.toBegin(); ! ev_1800to2400_QCD.atEnd(); ++ev_1800to2400_QCD) {
    fwlite::Handle<int> h_jet1tagEff;
    fwlite::Handle<int> h_AK8jet1tagEff;

    fwlite::Handle<int> h_jet2tagEff;
    fwlite::Handle<int> h_AK8jet2tagEff;
    
    fwlite::Handle<unsigned int> h_npv;

    fwlite::Handle<double> h_jet1ptEff;
    fwlite::Handle<double> h_jet1NsubjEff;
    fwlite::Handle<double> h_jet1minmassEff;
    fwlite::Handle<double> h_jet1topMassEff ;
    fwlite::Handle<double> h_AK8jet1filteredMassEff;
    fwlite::Handle<double> h_AK8jet1prunedMassEff;
    fwlite::Handle<double> h_AK8jet1trimmedMassEff;

    fwlite::Handle<double> h_jet2ptEff;
    fwlite::Handle<double> h_jet2NsubjEff;
    fwlite::Handle<double> h_jet2minmassEff;
    fwlite::Handle<double> h_jet2topMassEff ;
    fwlite::Handle<double> h_AK8jet2filteredMassEff;
    fwlite::Handle<double> h_AK8jet2prunedMassEff;
    fwlite::Handle<double> h_AK8jet2trimmedMassEff;

    fwlite::Handle<vector<reco::Candidate::PolarLorentzVector>> h_jet1SubjetP4;
    fwlite::Handle<vector<reco::Candidate::PolarLorentzVector>> h_jet2SubjetP4;

    h_jet1tagEff.getByLabel(ev_1800to2400_QCD,"miniAOD","jet1tagEff","MiniAOD");
    h_jet2tagEff.getByLabel(ev_1800to2400_QCD,"miniAOD","jet2tagEff","MiniAOD");
    h_AK8jet1tagEff.getByLabel(ev_1800to2400_QCD,"miniAOD","AK8jet1tagEff","MiniAOD");
    h_AK8jet2tagEff.getByLabel(ev_1800to2400_QCD,"miniAOD","AK8jet2tagEff","MiniAOD");

    h_npv.getByLabel(ev_1800to2400_QCD,"miniAOD","npv","MiniAOD");

    h_jet1ptEff.getByLabel(ev_1800to2400_QCD,"miniAOD","jet1ptEff","MiniAOD");
    h_jet1NsubjEff.getByLabel(ev_1800to2400_QCD,"miniAOD","jet1NsubjEff","MiniAOD");
    h_jet1minmassEff.getByLabel(ev_1800to2400_QCD,"miniAOD","jet1minmassEff","MiniAOD");
    h_jet1topMassEff.getByLabel(ev_1800to2400_QCD,"miniAOD","jet1topMassEff","MiniAOD");
    h_AK8jet1filteredMassEff.getByLabel(ev_1800to2400_QCD,"miniAOD","AK8jet1filteredMassEff","MiniAOD");
    h_AK8jet1prunedMassEff.getByLabel(ev_1800to2400_QCD,"miniAOD","AK8jet1prunedMassEff","MiniAOD");
    h_AK8jet1trimmedMassEff.getByLabel(ev_1800to2400_QCD,"miniAOD","AK8jet1trimmedMassEff","MiniAOD");

    h_jet2ptEff.getByLabel(ev_1800to2400_QCD,"miniAOD","jet2ptEff","MiniAOD");
    h_jet2NsubjEff.getByLabel(ev_1800to2400_QCD,"miniAOD","jet2NsubjEff","MiniAOD");
    h_jet2minmassEff.getByLabel(ev_1800to2400_QCD,"miniAOD","jet2minmassEff","MiniAOD");
    h_jet2topMassEff.getByLabel(ev_1800to2400_QCD,"miniAOD","jet2topMassEff","MiniAOD");
    h_AK8jet2filteredMassEff.getByLabel(ev_1800to2400_QCD,"miniAOD","AK8jet2filteredMassEff","MiniAOD");
    h_AK8jet2prunedMassEff.getByLabel(ev_1800to2400_QCD,"miniAOD","AK8jet2prunedMassEff","MiniAOD");
    h_AK8jet2trimmedMassEff.getByLabel(ev_1800to2400_QCD,"miniAOD","AK8jet2trimmedMassEff","MiniAOD");

    h_jet1SubjetP4.getByLabel(ev_1800to2400_QCD,"miniAOD","jet1SubjetP4","MiniAOD");
    h_jet2SubjetP4.getByLabel(ev_1800to2400_QCD,"miniAOD","jet2SubjetP4","MiniAOD");

    const std::vector<reco::Candidate::PolarLorentzVector>* jet1SubjetP4 = h_jet1SubjetP4.product();
    const std::vector<reco::Candidate::PolarLorentzVector>* jet2SubjetP4 = h_jet2SubjetP4.product();

    int jet1SubjetSize =  jet1SubjetP4->size();
    int jet2SubjetSize =  jet2SubjetP4->size();
    double subjet1Mass = 0;
    double subjet2Mass = 0;

    if (jet1SubjetSize > 2){
      subjet1Mass = (jet1SubjetP4->at(1)+jet1SubjetP4->at(2)+jet1SubjetP4->at(0)).M();
    }
    
    if (jet2SubjetSize > 2){
      subjet2Mass = (jet2SubjetP4->at(1)+jet2SubjetP4->at(2)+jet2SubjetP4->at(0)).M();
    }
  
    //jet mass histograms - after Nsubj and minmass top tagging cuts
    //jet 1
    if(*h_jet1tagEff != -1 && *h_jet1ptEff > ptCut && *h_jet1NsubjEff >= 3 && *h_jet1minmassEff > 50){

      hist_300toInf_QCD_noBtag_ungroomed_jetMass_preMassWindowCut->Fill(*h_jet1topMassEff,w_1800to2400);

      if(jet1SubjetSize > 2){
	hist_300toInf_QCD_noBtag_subjets_jetMass_preMassWindowCut->Fill(subjet1Mass,w_1800to2400);
      }

      if(*h_AK8jet1tagEff != 0){
	if(h_AK8jet1filteredMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_filtered_AK8jetMass_preMassWindowCut->Fill(*h_AK8jet1filteredMassEff,w_1800to2400);
	}
	if(h_AK8jet1prunedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_pruned_AK8jetMass_preMassWindowCut->Fill(*h_AK8jet1prunedMassEff,w_1800to2400);
	}
	if(h_AK8jet1trimmedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_trimmed_AK8jetMass_preMassWindowCut->Fill(*h_AK8jet1trimmedMassEff,w_1800to2400);
	}
      }
    }
 
    //jet 2
    if(*h_jet2tagEff != -1 && *h_jet2ptEff > ptCut && *h_jet2NsubjEff >= 3 && *h_jet2minmassEff > 50){

      hist_300toInf_QCD_noBtag_ungroomed_jetMass_preMassWindowCut->Fill(*h_jet2topMassEff,w_1800to2400);

      if(jet2SubjetSize > 2){
        hist_300toInf_QCD_noBtag_subjets_jetMass_preMassWindowCut->Fill(subjet2Mass,w_1800to2400);
      }

      if(*h_AK8jet2tagEff != 0){
	if(h_AK8jet2filteredMassEff.isValid()){
          hist_300toInf_QCD_noBtag_filtered_AK8jetMass_preMassWindowCut->Fill(*h_AK8jet2filteredMassEff,w_1800to2400);
        }
	if(h_AK8jet2prunedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_pruned_AK8jetMass_preMassWindowCut->Fill(*h_AK8jet2prunedMassEff,w_1800to2400);
	}
	if(h_AK8jet2trimmedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_trimmed_AK8jetMass_preMassWindowCut->Fill(*h_AK8jet2trimmedMassEff,w_1800to2400);
	}
      }
    }

    //jet mass histograms - no top tagging cuts
    //jet 1
    if(*h_jet1tagEff != -1 && *h_jet1ptEff > ptCut){

      hist_300toInf_QCD_noBtag_ungroomed_jetMass_noTopTagCut->Fill(*h_jet1topMassEff,w_1800to2400);

      if(jet1SubjetSize > 2){
        hist_300toInf_QCD_noBtag_subjets_jetMass_noTopTagCut->Fill(subjet1Mass,w_1800to2400);
      }

      if(*h_AK8jet1tagEff != 0){
	if(h_AK8jet1filteredMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_filtered_AK8jetMass_noTopTagCut->Fill(*h_AK8jet1filteredMassEff,w_1800to2400);
	}
	if(h_AK8jet1prunedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_pruned_AK8jetMass_noTopTagCut->Fill(*h_AK8jet1prunedMassEff,w_1800to2400);
	}
	if(h_AK8jet1trimmedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_trimmed_AK8jetMass_noTopTagCut->Fill(*h_AK8jet1trimmedMassEff,w_1800to2400);
	}
      }
    }
 
    //jet 2
    if(*h_jet2tagEff != -1 && *h_jet2ptEff > ptCut){

      hist_300toInf_QCD_noBtag_ungroomed_jetMass_noTopTagCut->Fill(*h_jet2topMassEff,w_1800to2400);

      if(jet2SubjetSize > 2){
        hist_300toInf_QCD_noBtag_subjets_jetMass_noTopTagCut->Fill(subjet2Mass,w_1800to2400);
      }

      if(*h_AK8jet2tagEff != 0){
	if(h_AK8jet2filteredMassEff.isValid()){
          hist_300toInf_QCD_noBtag_filtered_AK8jetMass_noTopTagCut->Fill(*h_AK8jet2filteredMassEff,w_1800to2400);
        }
	if(h_AK8jet2prunedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_pruned_AK8jetMass_noTopTagCut->Fill(*h_AK8jet2prunedMassEff,w_1800to2400);
	}
	if(h_AK8jet2trimmedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_trimmed_AK8jetMass_noTopTagCut->Fill(*h_AK8jet2trimmedMassEff,w_1800to2400);
	}
      }
    }
  }

  ////2400 to 3200 pt QCD
  vector<string> QCDFileNames_2400to3200;

  string QCDline_2400to3200;
  ifstream QCDFile_2400to3200 ("rootFiles_QCD_pt2400to3200_13TeV.txt");
  if (QCDFile_2400to3200.is_open()){
    while ( getline (QCDFile_2400to3200,QCDline_2400to3200) )
      {
	QCDFileNames_2400to3200.push_back(QCDline_2400to3200);
      }
    QCDFile_2400to3200.close();
  }

  //fileNames.push_back("/uscms_data/d3/camclean/CSA14/topTaggingEfficiency/CMSSW_7_0_6_patch1/src/Analysis/analyzeMiniAOD/RSGluonToTT_M_4000_08_19_2014/res/miniAOD*.root");                               

  fwlite::ChainEvent ev_2400to3200_QCD(QCDFileNames_2400to3200);

  for( ev_2400to3200_QCD.toBegin(); ! ev_2400to3200_QCD.atEnd(); ++ev_2400to3200_QCD) {
    fwlite::Handle<int> h_jet1tagEff;
    fwlite::Handle<int> h_AK8jet1tagEff;

    fwlite::Handle<int> h_jet2tagEff;
    fwlite::Handle<int> h_AK8jet2tagEff;
    
    fwlite::Handle<unsigned int> h_npv;

    fwlite::Handle<double> h_jet1ptEff;
    fwlite::Handle<double> h_jet1NsubjEff;
    fwlite::Handle<double> h_jet1minmassEff;
    fwlite::Handle<double> h_jet1topMassEff ;
    fwlite::Handle<double> h_AK8jet1filteredMassEff;
    fwlite::Handle<double> h_AK8jet1prunedMassEff;
    fwlite::Handle<double> h_AK8jet1trimmedMassEff;

    fwlite::Handle<double> h_jet2ptEff;
    fwlite::Handle<double> h_jet2NsubjEff;
    fwlite::Handle<double> h_jet2minmassEff;
    fwlite::Handle<double> h_jet2topMassEff ;
    fwlite::Handle<double> h_AK8jet2filteredMassEff;
    fwlite::Handle<double> h_AK8jet2prunedMassEff;
    fwlite::Handle<double> h_AK8jet2trimmedMassEff;

    fwlite::Handle<vector<reco::Candidate::PolarLorentzVector>> h_jet1SubjetP4;
    fwlite::Handle<vector<reco::Candidate::PolarLorentzVector>> h_jet2SubjetP4;

    h_jet1tagEff.getByLabel(ev_2400to3200_QCD,"miniAOD","jet1tagEff","MiniAOD");
    h_jet2tagEff.getByLabel(ev_2400to3200_QCD,"miniAOD","jet2tagEff","MiniAOD");
    h_AK8jet1tagEff.getByLabel(ev_2400to3200_QCD,"miniAOD","AK8jet1tagEff","MiniAOD");
    h_AK8jet2tagEff.getByLabel(ev_2400to3200_QCD,"miniAOD","AK8jet2tagEff","MiniAOD");

    h_npv.getByLabel(ev_2400to3200_QCD,"miniAOD","npv","MiniAOD");

    h_jet1ptEff.getByLabel(ev_2400to3200_QCD,"miniAOD","jet1ptEff","MiniAOD");
    h_jet1NsubjEff.getByLabel(ev_2400to3200_QCD,"miniAOD","jet1NsubjEff","MiniAOD");
    h_jet1minmassEff.getByLabel(ev_2400to3200_QCD,"miniAOD","jet1minmassEff","MiniAOD");
    h_jet1topMassEff.getByLabel(ev_2400to3200_QCD,"miniAOD","jet1topMassEff","MiniAOD");
    h_AK8jet1filteredMassEff.getByLabel(ev_2400to3200_QCD,"miniAOD","AK8jet1filteredMassEff","MiniAOD");
    h_AK8jet1prunedMassEff.getByLabel(ev_2400to3200_QCD,"miniAOD","AK8jet1prunedMassEff","MiniAOD");
    h_AK8jet1trimmedMassEff.getByLabel(ev_2400to3200_QCD,"miniAOD","AK8jet1trimmedMassEff","MiniAOD");

    h_jet2ptEff.getByLabel(ev_2400to3200_QCD,"miniAOD","jet2ptEff","MiniAOD");
    h_jet2NsubjEff.getByLabel(ev_2400to3200_QCD,"miniAOD","jet2NsubjEff","MiniAOD");
    h_jet2minmassEff.getByLabel(ev_2400to3200_QCD,"miniAOD","jet2minmassEff","MiniAOD");
    h_jet2topMassEff.getByLabel(ev_2400to3200_QCD,"miniAOD","jet2topMassEff","MiniAOD");
    h_AK8jet2filteredMassEff.getByLabel(ev_2400to3200_QCD,"miniAOD","AK8jet2filteredMassEff","MiniAOD");
    h_AK8jet2prunedMassEff.getByLabel(ev_2400to3200_QCD,"miniAOD","AK8jet2prunedMassEff","MiniAOD");
    h_AK8jet2trimmedMassEff.getByLabel(ev_2400to3200_QCD,"miniAOD","AK8jet2trimmedMassEff","MiniAOD");

    h_jet1SubjetP4.getByLabel(ev_2400to3200_QCD,"miniAOD","jet1SubjetP4","MiniAOD");
    h_jet2SubjetP4.getByLabel(ev_2400to3200_QCD,"miniAOD","jet2SubjetP4","MiniAOD");

    const std::vector<reco::Candidate::PolarLorentzVector>* jet1SubjetP4 = h_jet1SubjetP4.product();
    const std::vector<reco::Candidate::PolarLorentzVector>* jet2SubjetP4 = h_jet2SubjetP4.product();

    int jet1SubjetSize =  jet1SubjetP4->size();
    int jet2SubjetSize =  jet2SubjetP4->size();
    double subjet1Mass = 0;
    double subjet2Mass = 0;

    if (jet1SubjetSize > 2){
      subjet1Mass = (jet1SubjetP4->at(1)+jet1SubjetP4->at(2)+jet1SubjetP4->at(0)).M();
    }
    
    if (jet2SubjetSize > 2){
      subjet2Mass = (jet2SubjetP4->at(1)+jet2SubjetP4->at(2)+jet2SubjetP4->at(0)).M();
    }
  
    //jet mass histograms - after Nsubj and minmass top tagging cuts
    //jet 1
    if(*h_jet1tagEff != -1 && *h_jet1ptEff > ptCut && *h_jet1NsubjEff >= 3 && *h_jet1minmassEff > 50){

      hist_300toInf_QCD_noBtag_ungroomed_jetMass_preMassWindowCut->Fill(*h_jet1topMassEff,w_2400to3200);

      if(jet1SubjetSize > 2){
	hist_300toInf_QCD_noBtag_subjets_jetMass_preMassWindowCut->Fill(subjet1Mass,w_2400to3200);
      }

      if(*h_AK8jet1tagEff != 0){
	if(h_AK8jet1filteredMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_filtered_AK8jetMass_preMassWindowCut->Fill(*h_AK8jet1filteredMassEff,w_2400to3200);
	}
	if(h_AK8jet1prunedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_pruned_AK8jetMass_preMassWindowCut->Fill(*h_AK8jet1prunedMassEff,w_2400to3200);
	}
	if(h_AK8jet1trimmedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_trimmed_AK8jetMass_preMassWindowCut->Fill(*h_AK8jet1trimmedMassEff,w_2400to3200);
	}
      }
    }
 
    //jet 2
    if(*h_jet2tagEff != -1 && *h_jet2ptEff > ptCut && *h_jet2NsubjEff >= 3 && *h_jet2minmassEff > 50){

      hist_300toInf_QCD_noBtag_ungroomed_jetMass_preMassWindowCut->Fill(*h_jet2topMassEff,w_2400to3200);

      if(jet2SubjetSize > 2){
        hist_300toInf_QCD_noBtag_subjets_jetMass_preMassWindowCut->Fill(subjet2Mass,w_2400to3200);
      }

      if(*h_AK8jet2tagEff != 0){
	if(h_AK8jet2filteredMassEff.isValid()){
          hist_300toInf_QCD_noBtag_filtered_AK8jetMass_preMassWindowCut->Fill(*h_AK8jet2filteredMassEff,w_2400to3200);
        }
	if(h_AK8jet2prunedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_pruned_AK8jetMass_preMassWindowCut->Fill(*h_AK8jet2prunedMassEff,w_2400to3200);
	}
	if(h_AK8jet2trimmedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_trimmed_AK8jetMass_preMassWindowCut->Fill(*h_AK8jet2trimmedMassEff,w_2400to3200);
	}
      }
    }

    //jet mass histograms - no top tagging cuts
    //jet 1
    if(*h_jet1tagEff != -1 && *h_jet1ptEff > ptCut){

      hist_300toInf_QCD_noBtag_ungroomed_jetMass_noTopTagCut->Fill(*h_jet1topMassEff,w_2400to3200);

      if(jet1SubjetSize > 2){
        hist_300toInf_QCD_noBtag_subjets_jetMass_noTopTagCut->Fill(subjet1Mass,w_2400to3200);
      }

      if(*h_AK8jet1tagEff != 0){
	if(h_AK8jet1filteredMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_filtered_AK8jetMass_noTopTagCut->Fill(*h_AK8jet1filteredMassEff,w_2400to3200);
	}
	if(h_AK8jet1prunedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_pruned_AK8jetMass_noTopTagCut->Fill(*h_AK8jet1prunedMassEff,w_2400to3200);
	}
	if(h_AK8jet1trimmedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_trimmed_AK8jetMass_noTopTagCut->Fill(*h_AK8jet1trimmedMassEff,w_2400to3200);
	}
      }
    }
 
    //jet 2
    if(*h_jet2tagEff != -1 && *h_jet2ptEff > ptCut){

      hist_300toInf_QCD_noBtag_ungroomed_jetMass_noTopTagCut->Fill(*h_jet2topMassEff,w_2400to3200);

      if(jet2SubjetSize > 2){
        hist_300toInf_QCD_noBtag_subjets_jetMass_noTopTagCut->Fill(subjet2Mass,w_2400to3200);
      }

      if(*h_AK8jet2tagEff != 0){
	if(h_AK8jet2filteredMassEff.isValid()){
          hist_300toInf_QCD_noBtag_filtered_AK8jetMass_noTopTagCut->Fill(*h_AK8jet2filteredMassEff,w_2400to3200);
        }
	if(h_AK8jet2prunedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_pruned_AK8jetMass_noTopTagCut->Fill(*h_AK8jet2prunedMassEff,w_2400to3200);
	}
	if(h_AK8jet2trimmedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_trimmed_AK8jetMass_noTopTagCut->Fill(*h_AK8jet2trimmedMassEff,w_2400to3200);
	}
      }
    }
  }

  ////3200+ pt QCD
  vector<string> QCDFileNames_3200toInf;

  string QCDline_3200toInf;
  ifstream QCDFile_3200toInf ("rootFiles_QCD_pt3200toInf_13TeV.txt");
  if (QCDFile_3200toInf.is_open()){
    while ( getline (QCDFile_3200toInf,QCDline_3200toInf) )
      {
	QCDFileNames_3200toInf.push_back(QCDline_3200toInf);
      }
    QCDFile_3200toInf.close();
  }

  //fileNames.push_back("/uscms_data/d3/camclean/CSA14/topTaggingEfficiency/CMSSW_7_0_6_patch1/src/Analysis/analyzeMiniAOD/RSGluonToTT_M_4000_08_19_2014/res/miniAOD*.root");                               

  fwlite::ChainEvent ev_3200toInf_QCD(QCDFileNames_3200toInf);

  for( ev_3200toInf_QCD.toBegin(); ! ev_3200toInf_QCD.atEnd(); ++ev_3200toInf_QCD) {
    fwlite::Handle<int> h_jet1tagEff;
    fwlite::Handle<int> h_AK8jet1tagEff;

    fwlite::Handle<int> h_jet2tagEff;
    fwlite::Handle<int> h_AK8jet2tagEff;
    
    fwlite::Handle<unsigned int> h_npv;

    fwlite::Handle<double> h_jet1ptEff;
    fwlite::Handle<double> h_jet1NsubjEff;
    fwlite::Handle<double> h_jet1minmassEff;
    fwlite::Handle<double> h_jet1topMassEff ;
    fwlite::Handle<double> h_AK8jet1filteredMassEff;
    fwlite::Handle<double> h_AK8jet1prunedMassEff;
    fwlite::Handle<double> h_AK8jet1trimmedMassEff;

    fwlite::Handle<double> h_jet2ptEff;
    fwlite::Handle<double> h_jet2NsubjEff;
    fwlite::Handle<double> h_jet2minmassEff;
    fwlite::Handle<double> h_jet2topMassEff ;
    fwlite::Handle<double> h_AK8jet2filteredMassEff;
    fwlite::Handle<double> h_AK8jet2prunedMassEff;
    fwlite::Handle<double> h_AK8jet2trimmedMassEff;

    fwlite::Handle<vector<reco::Candidate::PolarLorentzVector>> h_jet1SubjetP4;
    fwlite::Handle<vector<reco::Candidate::PolarLorentzVector>> h_jet2SubjetP4;

    h_jet1tagEff.getByLabel(ev_3200toInf_QCD,"miniAOD","jet1tagEff","MiniAOD");
    h_jet2tagEff.getByLabel(ev_3200toInf_QCD,"miniAOD","jet2tagEff","MiniAOD");
    h_AK8jet1tagEff.getByLabel(ev_3200toInf_QCD,"miniAOD","AK8jet1tagEff","MiniAOD");
    h_AK8jet2tagEff.getByLabel(ev_3200toInf_QCD,"miniAOD","AK8jet2tagEff","MiniAOD");

    h_npv.getByLabel(ev_3200toInf_QCD,"miniAOD","npv","MiniAOD");

    h_jet1ptEff.getByLabel(ev_3200toInf_QCD,"miniAOD","jet1ptEff","MiniAOD");
    h_jet1NsubjEff.getByLabel(ev_3200toInf_QCD,"miniAOD","jet1NsubjEff","MiniAOD");
    h_jet1minmassEff.getByLabel(ev_3200toInf_QCD,"miniAOD","jet1minmassEff","MiniAOD");
    h_jet1topMassEff.getByLabel(ev_3200toInf_QCD,"miniAOD","jet1topMassEff","MiniAOD");
    h_AK8jet1filteredMassEff.getByLabel(ev_3200toInf_QCD,"miniAOD","AK8jet1filteredMassEff","MiniAOD");
    h_AK8jet1prunedMassEff.getByLabel(ev_3200toInf_QCD,"miniAOD","AK8jet1prunedMassEff","MiniAOD");
    h_AK8jet1trimmedMassEff.getByLabel(ev_3200toInf_QCD,"miniAOD","AK8jet1trimmedMassEff","MiniAOD");

    h_jet2ptEff.getByLabel(ev_3200toInf_QCD,"miniAOD","jet2ptEff","MiniAOD");
    h_jet2NsubjEff.getByLabel(ev_3200toInf_QCD,"miniAOD","jet2NsubjEff","MiniAOD");
    h_jet2minmassEff.getByLabel(ev_3200toInf_QCD,"miniAOD","jet2minmassEff","MiniAOD");
    h_jet2topMassEff.getByLabel(ev_3200toInf_QCD,"miniAOD","jet2topMassEff","MiniAOD");
    h_AK8jet2filteredMassEff.getByLabel(ev_3200toInf_QCD,"miniAOD","AK8jet2filteredMassEff","MiniAOD");
    h_AK8jet2prunedMassEff.getByLabel(ev_3200toInf_QCD,"miniAOD","AK8jet2prunedMassEff","MiniAOD");
    h_AK8jet2trimmedMassEff.getByLabel(ev_3200toInf_QCD,"miniAOD","AK8jet2trimmedMassEff","MiniAOD");

    h_jet1SubjetP4.getByLabel(ev_3200toInf_QCD,"miniAOD","jet1SubjetP4","MiniAOD");
    h_jet2SubjetP4.getByLabel(ev_3200toInf_QCD,"miniAOD","jet2SubjetP4","MiniAOD");

    const std::vector<reco::Candidate::PolarLorentzVector>* jet1SubjetP4 = h_jet1SubjetP4.product();
    const std::vector<reco::Candidate::PolarLorentzVector>* jet2SubjetP4 = h_jet2SubjetP4.product();

    int jet1SubjetSize =  jet1SubjetP4->size();
    int jet2SubjetSize =  jet2SubjetP4->size();
    double subjet1Mass = 0;
    double subjet2Mass = 0;

    if (jet1SubjetSize > 2){
      subjet1Mass = (jet1SubjetP4->at(1)+jet1SubjetP4->at(2)+jet1SubjetP4->at(0)).M();
    }
    
    if (jet2SubjetSize > 2){
      subjet2Mass = (jet2SubjetP4->at(1)+jet2SubjetP4->at(2)+jet2SubjetP4->at(0)).M();
    }
  
    //jet mass histograms - after Nsubj and minmass top tagging cuts
    //jet 1
    if(*h_jet1tagEff != -1 && *h_jet1ptEff > ptCut && *h_jet1NsubjEff >= 3 && *h_jet1minmassEff > 50){

      hist_300toInf_QCD_noBtag_ungroomed_jetMass_preMassWindowCut->Fill(*h_jet1topMassEff,w_3200toInf);

      if(jet1SubjetSize > 2){
	hist_300toInf_QCD_noBtag_subjets_jetMass_preMassWindowCut->Fill(subjet1Mass,w_3200toInf);
      }

      if(*h_AK8jet1tagEff != 0){
	if(h_AK8jet1filteredMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_filtered_AK8jetMass_preMassWindowCut->Fill(*h_AK8jet1filteredMassEff,w_3200toInf);
	}
	if(h_AK8jet1prunedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_pruned_AK8jetMass_preMassWindowCut->Fill(*h_AK8jet1prunedMassEff,w_3200toInf);
	}
	if(h_AK8jet1trimmedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_trimmed_AK8jetMass_preMassWindowCut->Fill(*h_AK8jet1trimmedMassEff,w_3200toInf);
	}
      }
    }
 
    //jet 2
    if(*h_jet2tagEff != -1 && *h_jet2ptEff > ptCut && *h_jet2NsubjEff >= 3 && *h_jet2minmassEff > 50){

      hist_300toInf_QCD_noBtag_ungroomed_jetMass_preMassWindowCut->Fill(*h_jet2topMassEff,w_3200toInf);

      if(jet2SubjetSize > 2){
        hist_300toInf_QCD_noBtag_subjets_jetMass_preMassWindowCut->Fill(subjet2Mass,w_3200toInf);
      }

      if(*h_AK8jet2tagEff != 0){
	if(h_AK8jet2filteredMassEff.isValid()){
          hist_300toInf_QCD_noBtag_filtered_AK8jetMass_preMassWindowCut->Fill(*h_AK8jet2filteredMassEff,w_3200toInf);
        }
	if(h_AK8jet2prunedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_pruned_AK8jetMass_preMassWindowCut->Fill(*h_AK8jet2prunedMassEff,w_3200toInf);
	}
	if(h_AK8jet2trimmedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_trimmed_AK8jetMass_preMassWindowCut->Fill(*h_AK8jet2trimmedMassEff,w_3200toInf);
	}
      }
    }

    //jet mass histograms - no top tagging cuts
    //jet 1
    if(*h_jet1tagEff != -1 && *h_jet1ptEff > ptCut){

      hist_300toInf_QCD_noBtag_ungroomed_jetMass_noTopTagCut->Fill(*h_jet1topMassEff,w_3200toInf);

      if(jet1SubjetSize > 2){
        hist_300toInf_QCD_noBtag_subjets_jetMass_noTopTagCut->Fill(subjet1Mass,w_3200toInf);
      }

      if(*h_AK8jet1tagEff != 0){
	if(h_AK8jet1filteredMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_filtered_AK8jetMass_noTopTagCut->Fill(*h_AK8jet1filteredMassEff,w_3200toInf);
	}
	if(h_AK8jet1prunedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_pruned_AK8jetMass_noTopTagCut->Fill(*h_AK8jet1prunedMassEff,w_3200toInf);
	}
	if(h_AK8jet1trimmedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_trimmed_AK8jetMass_noTopTagCut->Fill(*h_AK8jet1trimmedMassEff,w_3200toInf);
	}
      }
    }
 
    //jet 2
    if(*h_jet2tagEff != -1 && *h_jet2ptEff > ptCut){

      hist_300toInf_QCD_noBtag_ungroomed_jetMass_noTopTagCut->Fill(*h_jet2topMassEff,w_3200toInf);

      if(jet2SubjetSize > 2){
        hist_300toInf_QCD_noBtag_subjets_jetMass_noTopTagCut->Fill(subjet2Mass,w_3200toInf);
      }

      if(*h_AK8jet2tagEff != 0){
	if(h_AK8jet2filteredMassEff.isValid()){
          hist_300toInf_QCD_noBtag_filtered_AK8jetMass_noTopTagCut->Fill(*h_AK8jet2filteredMassEff,w_3200toInf);
        }
	if(h_AK8jet2prunedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_pruned_AK8jetMass_noTopTagCut->Fill(*h_AK8jet2prunedMassEff,w_3200toInf);
	}
	if(h_AK8jet2trimmedMassEff.isValid()){
	  hist_300toInf_QCD_noBtag_trimmed_AK8jetMass_noTopTagCut->Fill(*h_AK8jet2trimmedMassEff,w_3200toInf);
	}
      }
    }
  }

  TFile *f = new TFile(OutputFileName.c_str(),"recreate");
  hist_ZPrime_noBtag_ungroomed_jetMass_preMassWindowCut->Write(); 
  hist_300toInf_QCD_noBtag_ungroomed_jetMass_preMassWindowCut->Write();

  hist_ZPrime_noBtag_subjets_jetMass_preMassWindowCut->Write();
  hist_300toInf_QCD_noBtag_subjets_jetMass_preMassWindowCut->Write();

  hist_ZPrime_noBtag_filtered_AK8jetMass_preMassWindowCut->Write();
  hist_300toInf_QCD_noBtag_filtered_AK8jetMass_preMassWindowCut->Write();

  hist_ZPrime_noBtag_pruned_AK8jetMass_preMassWindowCut->Write();
  hist_300toInf_QCD_noBtag_pruned_AK8jetMass_preMassWindowCut->Write();

  hist_ZPrime_noBtag_trimmed_AK8jetMass_preMassWindowCut->Write();
  hist_300toInf_QCD_noBtag_trimmed_AK8jetMass_preMassWindowCut->Write();

  hist_ZPrime_noBtag_ungroomed_jetMass_noTopTagCut->Write(); 
  hist_300toInf_QCD_noBtag_ungroomed_jetMass_noTopTagCut->Write();

  hist_ZPrime_noBtag_subjets_jetMass_noTopTagCut->Write();
  hist_300toInf_QCD_noBtag_subjets_jetMass_noTopTagCut->Write();

  hist_ZPrime_noBtag_filtered_AK8jetMass_noTopTagCut->Write();
  hist_300toInf_QCD_noBtag_filtered_AK8jetMass_noTopTagCut->Write();

  hist_ZPrime_noBtag_pruned_AK8jetMass_noTopTagCut->Write();
  hist_300toInf_QCD_noBtag_pruned_AK8jetMass_noTopTagCut->Write();

  hist_ZPrime_noBtag_trimmed_AK8jetMass_noTopTagCut->Write();
  hist_300toInf_QCD_noBtag_trimmed_AK8jetMass_noTopTagCut->Write();

  f->Close();

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
