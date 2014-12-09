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
#include<DataFormats/RecoCandidate/interface/RecoCandidate.h>
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

  TH1F *hist_ak8Filtered = new TH1F("hist_ak8Filtered","AK8 Jet Mass - #sqrt{s} = 13 TeV; Mass (GeV); Events",75,0,600);
  TH1F *hist_ak8Trimmed = new TH1F("hist_ak8Trimmed","AK8 Jet Mass; Mass (GeV); Events",75,0,600);
  TH1F *hist_ak8Pruned = new TH1F("hist_ak8Pruned","AK8 Jet Mass; Mass (GeV); Events",75,0,600);
  TH1F *hist_ak8 = new TH1F("hist_ak8","AK8 Jet Mass; Mass (GeV); Events",75,0,600);
  //hist_ak8Filtered->Sumw2();
  
  vector<string> fileNames;
  /*
  string line;
  ifstream myfile ("rootFiles_Zprime13TeV.txt");
  if (myfile.is_open()){
      while ( getline (myfile,line) ){
	fileNames.push_back(line);
      }
      myfile.close();
  }
  */
  fileNames.push_back("/uscms_data/d3/camclean/CSA14/topTaggingEfficiency/CMSSW_7_0_6_patch1/src/Analysis/processMiniAOD/test/miniAOD_Zprime13TeV_Sept_04_2014.root");
  
  fwlite::ChainEvent ev(fileNames);

  for( ev.toBegin(); ! ev.atEnd(); ++ev) {
    fwlite::Handle<vector<double>> h_ak8Filtered;
    fwlite::Handle<vector<double>> h_ak8Trimmed;
    fwlite::Handle<vector<double>> h_ak8Pruned;
    fwlite::Handle<std::vector<reco::Candidate::PolarLorentzVector> > h_ak8;

    h_ak8Filtered.getByLabel(ev,"miniAOD","ak8PFJetsCHSFilteredLinks","MiniAOD");
    h_ak8Trimmed.getByLabel(ev,"miniAOD","ak8PFJetsCHSTrimmedLinks","MiniAOD");
    h_ak8Pruned.getByLabel(ev,"miniAOD","ak8PFJetsCHSPrunedLinks","MiniAOD");
    h_ak8.getByLabel(ev,"miniAOD","AK8jetP4","MiniAOD");

    const std::vector<double>* ak8Filtered = h_ak8Filtered.product();
    const std::vector<double>* ak8Trimmed = h_ak8Trimmed.product();
    const std::vector<double>* ak8Pruned = h_ak8Pruned.product();
    const std::vector<reco::Candidate::PolarLorentzVector>* ak8 = h_ak8.product();

    for(unsigned int i=0;i<(ak8Filtered->size());i++){
      hist_ak8Filtered->Fill(ak8Filtered->at(i));
    }

    for(unsigned int i=0;i<(ak8Trimmed->size());i++){
      hist_ak8Trimmed->Fill(ak8Trimmed->at(i));
    }

    for(unsigned int i=0;i<(ak8Pruned->size());i++){
      hist_ak8Pruned->Fill(ak8Pruned->at(i));
    }

    for(unsigned int i=0;i<(ak8->size());i++){
      hist_ak8->Fill((ak8->at(i)).M());
    }
  }

  TCanvas* c1 = new TCanvas("canvas1");
  hist_ak8Filtered->Draw();
  hist_ak8Filtered->SetLineColor(2);
  hist_ak8Trimmed->Draw("SAME");
  hist_ak8Trimmed->SetLineColor(3);
  hist_ak8Pruned->Draw("SAME");
  hist_ak8Pruned->SetLineColor(4);
  hist_ak8->Draw("SAME");

  //legend                                                                                                                                                                                                 
  TLegend *legend = new TLegend(0.6,0.6,0.85,0.85);
  legend->AddEntry(hist_ak8,"Jet Mass - No Grooming","L");
  legend->AddEntry(hist_ak8Filtered,"Filtered Jet Mass","L");
  legend->AddEntry(hist_ak8Trimmed,"Trimmed Jet Mass","L");
  legend->AddEntry(hist_ak8Pruned,"Pruned Jet Mass","L");
  legend->SetFillColor(kWhite);
  legend->Draw("Same");

  c1->SaveAs("AK8jetsGroomedMassCompare_Sept06.pdf");
  
}
