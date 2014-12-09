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

void topTagEfficiency_8TeV_13TeV_compare(){
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(0000000000);
  gStyle->SetTitleBorderSize(0);

  TFile *f13 = new TFile("RSGttbar_topTagEff_13TeV.root");
  f13->ls();

  TFile *f8 = new TFile("SMttbar_topTagEff_8TeV.root");
  f8->ls();

  TH1F * hist_topTagEffPt = (TH1F*)f13->Get("hist_topTagEffPt");
  TH1F * hist_topTagEffNpv = (TH1F*)f13->Get("hist_topTagEffNpv");
  TH1F * hist_topTagEffNpv_400 = (TH1F*)f13->Get("hist_topTagEffNpv_400");
  TH1F * hist_jet1pt = (TH1F*)f13->Get("hist_jet1pt");
  TH1F * hist_npv1 = (TH1F*)f13->Get("hist_npv1");

  TH1F * h_topTagEffPt = (TH1F*)f8->Get("h_topTagEffPt");
  TH1F * h_topTagEffNpv = (TH1F*)f8->Get("h_topTagEffNpv");
  TH1F * h_topTagEffNpv_400 = (TH1F*)f8->Get("h_topTagEffNpv_400");
  TH1F * h_topTagEffPtDenom = (TH1F*)f8->Get("h_topTagEffPtDenom");
  TH1F * h_topTagEffNpvDenom = (TH1F*)f8->Get("h_topTagEffNpvDenom");

  TCanvas* c1 = new TCanvas("Pt efficiency");
  hist_topTagEffPt->Draw();
  hist_topTagEffPt->SetTitle("Top Tagging Efficiency vs Pt");
  h_topTagEffPt->Draw("ESAME");
  h_topTagEffPt->SetLineColor(2);
  h_topTagEffPt->SetMarkerColor(2);

  //legend
  TLegend *legend_topTagEffPt = new TLegend(0.6,0.75,0.9,0.9);
  legend_topTagEffPt->AddEntry(h_topTagEffPt,"#sqrt{s} = 8 TeV, SM t#bar{t}","LPE");
  legend_topTagEffPt->AddEntry(hist_topTagEffPt,"#sqrt{s} = 13 TeV, RS Gluon to t#bar{t}","LPE");
  legend_topTagEffPt->SetFillColor(kWhite); 
  legend_topTagEffPt->Draw("Same");

  TCanvas* c2 = new TCanvas("Npv efficiency");
  hist_topTagEffNpv->Draw();
  hist_topTagEffNpv->SetLineColor(1);
  hist_topTagEffNpv->SetTitle("Top Tagging Efficiency vs Npv - No Pt Cut");
  h_topTagEffNpv->Draw("ESAME");
  h_topTagEffNpv->SetLineColor(2);
  h_topTagEffNpv->SetMarkerColor(2);

  //legend
  TLegend *legend_topTagEffNpv = new TLegend(0.6,0.75,0.9,0.9);
  legend_topTagEffNpv->AddEntry(h_topTagEffNpv,"#sqrt{s} = 8 TeV, SM t#bar{t}","LPE");
  legend_topTagEffNpv->AddEntry(hist_topTagEffNpv,"#sqrt{s} = 13 TeV, RS Gluon to t#bar{t}","LPE");
  legend_topTagEffNpv->SetFillColor(kWhite);
  legend_topTagEffNpv->Draw("Same");

  TCanvas* c3 = new TCanvas("Npv_400 efficiency");
  hist_topTagEffNpv_400->Draw();
  hist_topTagEffNpv_400->SetLineColor(1);
  hist_topTagEffNpv_400->SetTitle("Top Tagging Efficiency vs Npv - Pt > 400 GeV");
  h_topTagEffNpv_400->Draw("ESAME");
  h_topTagEffNpv_400->SetLineColor(2);
  h_topTagEffNpv_400->SetMarkerColor(2);

  //legend
  TLegend *legend_topTagEffNpv_400 = new TLegend(0.6,0.75,0.9,0.9);
  legend_topTagEffNpv_400->AddEntry(h_topTagEffNpv_400,"#sqrt{s} = 8 TeV, SM t#bar{t}","LPE");
  legend_topTagEffNpv_400->AddEntry(hist_topTagEffNpv_400,"#sqrt{s} = 13 TeV, RS Gluon to t#bar{t}","LPE");
  legend_topTagEffNpv_400->SetFillColor(kWhite);
  legend_topTagEffNpv_400->Draw("Same");

  TCanvas* c4 = new TCanvas("13 TeV Pt Spectrum");
  hist_jet1pt->Draw();
  hist_jet1pt->SetTitle("13 TeV Jet Pt Spectrum - 4 TeV RS Gluon to TTbar;Jet Pt;Events");
  hist_jet1pt->SetTitleOffset(1.2);

  TCanvas* c5 = new TCanvas("13 TeV Npv Spectrum");
  hist_npv1->Draw();
  hist_npv1->SetTitle("13 TeV Pileup - 4 TeV RS Gluon to TTbar;Pileup;Events");
  hist_npv1->SetTitleOffset(1.2);

  TCanvas* c6 = new TCanvas("8 TeV Pt Spectrum");
  h_topTagEffPtDenom->Draw();
  h_topTagEffPtDenom->SetTitle("8 TeV Jet Pt Spectrum - SM TTbar;Jet Pt;Events");
  h_topTagEffPtDenom->SetTitleOffset(1.2);
    
  TCanvas* c7 = new TCanvas("8 TeV Npv Spectrum");
  h_topTagEffNpvDenom->Draw();
  h_topTagEffNpvDenom->SetTitle("8 TeV Pileup - SM TTbar;Pileup;Events");
  h_topTagEffNpvDenom->SetTitleOffset(1.2);

  c1->SaveAs("topTagEfficiencyPtCompare_Sept08.pdf");
  c2->SaveAs("topTagEfficiencyNpvCompare_Sept08.pdf");
  c3->SaveAs("topTagEfficiencyNpvCompare_400_Sept08.pdf");
  c4->SaveAs("RSGluonToTTbar_JetPtSpectrum_13TeV.pdf");
  c5->SaveAs("RSGluonToTTbar_Npv_13Tev.pdf");
  c6->SaveAs("SMttbar_JetPtSpectrum_8TeV.pdf");
  c7->SaveAs("SMttbar_Npv_8Tev.pdf");
}
