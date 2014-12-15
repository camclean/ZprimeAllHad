// -*- C++ -*-
//
// Package:    Analysis/processMiniAOD
// Class:      processMiniAOD
// 
/**\class processMiniAOD processMiniAOD.cc Analysis/processMiniAOD/plugins/processMiniAOD.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  christine mclean
//         Created:  Wed, 23 Jul 2014 14:45:53 GMT
//
//


// system include files
#include <memory>
#include <vector>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/PackedGenParticle.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/JetReco/interface/CATopJetTagInfo.h"
//#include "AnalysisDataFormats/TopObjects/interface/CATopJetTagInfo.h"

#include <fastjet/JetDefinition.hh>
#include <fastjet/PseudoJet.hh>
#include "fastjet/tools/Filter.hh"
#include <fastjet/ClusterSequence.hh>
#include <fastjet/ActiveAreaSpec.hh>
#include <fastjet/ClusterSequenceArea.hh>

#include "Nsubjettiness.hh"
#include "Njettiness.hh"

using namespace fastjet;
using namespace std;

//
// class declaration
//

class processMiniAOD : public edm::EDFilter {
   public:
      explicit processMiniAOD(const edm::ParameterSet&);
      ~processMiniAOD();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      virtual void beginJob() override;
      virtual bool filter(edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;
      
      //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
      //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

      // ----------member data ---------------------------

  edm::InputTag     AK8jetSrc_;//old method - July 31, 2014
  //edm::InputTag     GenJetSrc_;
  edm::EDGetTokenT<edm::View<reco::GenParticle> > prunedGenToken_;//new method - July 31, 2014
  edm::EDGetTokenT<edm::View<reco::Vertex> > pvSrc_;
  edm::EDGetTokenT<edm::View<pat::Jet> > topTagSrc_;
  edm::EDGetTokenT<edm::View<pat::Jet> > topTagFilteredSrc_;
  edm::EDGetTokenT<edm::View<pat::Jet> > ca8JetSrc_;
  std::string               topTagName_;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
processMiniAOD::processMiniAOD(const edm::ParameterSet& iConfig):
  AK8jetSrc_      (iConfig.getParameter<edm::InputTag>("AK8jetSrc") ),
  //GenJetSrc_      (iConfig.getParameter<edm::InputTag>("GenJetSrc") )
  prunedGenToken_(consumes<edm::View<reco::GenParticle> >(iConfig.getParameter<edm::InputTag>("pruned"))),
  pvSrc_(consumes<edm::View<reco::Vertex> >(iConfig.getParameter<edm::InputTag>("pvSrc"))),
  topTagSrc_(consumes<edm::View<pat::Jet> >(iConfig.getParameter<edm::InputTag>("topTagSrc"))),
  topTagFilteredSrc_(consumes<edm::View<pat::Jet> >(iConfig.getParameter<edm::InputTag>("topTagFilteredSrc"))),
  ca8JetSrc_(consumes<edm::View<pat::Jet> >(iConfig.getParameter<edm::InputTag>("ca8JetSrc"))),
  topTagName_   (iConfig.getParameter<edm::ParameterSet>("topTagParams").getParameter<std::string>("tagName") )
{
  //register products
  produces<std::vector<double> > ("jetPt");
  produces<std::vector<double> > ("jetEta");
  produces<std::vector<double> > ("jetPhi");
  produces<std::vector<double> > ("topTagMinMass");
  produces<std::vector<double> > ("topTagBDisc");
  produces<std::vector<double> > ("topTagNSubjets");
  produces<std::vector<double> > ("topTagFilteredMinMass");
  produces<std::vector<double> > ("topTagFilteredBDisc");
  produces<std::vector<double> > ("topTagFilteredNSubjets");
  produces<std::vector<double> > ("topTagSubjetBDisc");
  produces<std::vector<double> > ("tau1");
  produces<std::vector<double> > ("tau2");
  produces<std::vector<double> > ("tau3");
  produces<std::vector<double> > ("tau4");
  produces<std::vector<double> > ("ak8PFJetsCHSPrunedLinks");
  produces<std::vector<double> > ("ak8PFJetsCHSTrimmedLinks");
  produces<std::vector<double> > ("ak8PFJetsCHSFilteredLinks");
  produces<std::vector<double> > ("jet1SubjetBDiscEff");
  produces<std::vector<double> > ("jet2SubjetBDiscEff");
  produces<std::vector<double> > ("AK8jetNSubjets");

  produces<double> ("jet1ptEff");
  produces<double> ("jet2ptEff");
  produces<double> ("jet1NsubjEff");
  produces<double> ("jet2NsubjEff");
  produces<double> ("jet1deltaReff");
  produces<double> ("jet2deltaReff");
  produces<double> ("jet1minmassEff");
  produces<double> ("jet2minmassEff");
  produces<double> ("jet1topMassEff");
  produces<double> ("jet2topMassEff");
  produces<double> ("jet1BDiscEff");
  produces<double> ("jet2BDiscEff");
  produces<double> ("jet1MaxSubjBDiscEff");
  produces<double> ("jet2MaxSubjBDiscEff");
  produces<double> ("AK8jet1MassEff");
  produces<double> ("AK8jet1filteredMassEff");
  produces<double> ("AK8jet1prunedMassEff");
  produces<double> ("AK8jet1trimmedMassEff");
  produces<double> ("AK8jet2MassEff");
  produces<double> ("AK8jet2filteredMassEff");
  produces<double> ("AK8jet2prunedMassEff");
  produces<double> ("AK8jet2trimmedMassEff");
  produces<double> ("mttgen");
  produces<double> ("mtttag");

  produces<std::vector<reco::Candidate::PolarLorentzVector> > ("AK8jetP4");
  produces<std::vector<reco::Candidate::PolarLorentzVector> > ("genTopP4");
  produces<std::vector<reco::Candidate::PolarLorentzVector> > ("topTagP4");
  produces<std::vector<reco::Candidate::PolarLorentzVector> > ("topTagFilteredP4");
  produces<std::vector<reco::Candidate::PolarLorentzVector> > ("topTagSubjetP4");

  produces<std::vector<reco::Candidate::PolarLorentzVector> > ("jet1P4");
  produces<std::vector<reco::Candidate::PolarLorentzVector> >("jet2P4");
  produces<std::vector<reco::Candidate::PolarLorentzVector> >("jet1SubjetP4");
  produces<std::vector<reco::Candidate::PolarLorentzVector> >("jet2SubjetP4");

  produces<std::vector<int> > ("genTopStatus"); 

  produces<unsigned int>    ("npv");

  produces<int> ("jet1tagEff");
  produces<int> ("jet2tagEff");
  produces<int>("genTopSize");
  produces<int> ("AK8jet1tagEff");
  produces<int> ("AK8jet2tagEff");
}


processMiniAOD::~processMiniAOD()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
processMiniAOD::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  //cout <<"PROCESS STARTED"<<endl;

  using namespace edm;
  using namespace reco;
  using namespace pat;

  typedef std::vector<reco::Candidate::PolarLorentzVector> p4_vector;
  typedef reco::Candidate::PolarLorentzVector LorentzV;

  edm::Handle<std::vector<pat::Jet> > h_AK8jet;
  //edm::Handle<std::vector<pat::PackedGenParticle> > h_gen;
  Handle<edm::View<reco::GenParticle> > h_gen;
  Handle<edm::View<reco::Vertex> > h_pv;
  Handle<edm::View<pat::Jet> > h_topTag;
  Handle<edm::View<pat::Jet> > h_topTagFiltered;
  Handle<edm::View<pat::Jet> > h_ca8Jet;

  iEvent.getByLabel( AK8jetSrc_, h_AK8jet );
  //iEvent.getByLabel( GenJetSrc_, h_gen );
  iEvent.getByToken(prunedGenToken_,h_gen);
  iEvent.getByToken(pvSrc_,h_pv);
  iEvent.getByToken(topTagSrc_, h_topTag);
  iEvent.getByToken(topTagFilteredSrc_, h_topTagFiltered);
  iEvent.getByToken(ca8JetSrc_, h_ca8Jet);

  //cout <<"Handles created"<<endl;

  std::auto_ptr<std::vector<double> > jetPt ( new std::vector<double>() );
  std::auto_ptr<std::vector<double> > jetEta ( new std::vector<double>() );
  std::auto_ptr<std::vector<double> > jetPhi ( new std::vector<double>() );
  std::auto_ptr<std::vector<double> > topTagMinMass ( new std::vector<double>() );
  std::auto_ptr<std::vector<double> > topTagBDisc ( new std::vector<double>() );
  std::auto_ptr<std::vector<double> > topTagNSubjets ( new std::vector<double>() );
  std::auto_ptr<std::vector<double> > topTagFilteredMinMass ( new std::vector<double>() );
  std::auto_ptr<std::vector<double> > topTagFilteredBDisc ( new std::vector<double>() );
  std::auto_ptr<std::vector<double> > topTagFilteredNSubjets ( new std::vector<double>() );
  std::auto_ptr<std::vector<double> > tau1 ( new std::vector<double>() );
  std::auto_ptr<std::vector<double> > tau2 ( new std::vector<double>() );
  std::auto_ptr<std::vector<double> > tau3 ( new std::vector<double>() );
  std::auto_ptr<std::vector<double> > tau4 ( new std::vector<double>() );
  std::auto_ptr<std::vector<double> > topTagSubjetBDisc( new std::vector<double>() );
  std::auto_ptr<std::vector<double> > ak8PFJetsCHSPrunedLinks( new std::vector<double>() );
  std::auto_ptr<std::vector<double> > ak8PFJetsCHSTrimmedLinks( new std::vector<double>() );
  std::auto_ptr<std::vector<double> > ak8PFJetsCHSFilteredLinks( new std::vector<double>() );
  std::auto_ptr<std::vector<double> > jet1SubjetBDiscEff( new std::vector<double>() );
  std::auto_ptr<std::vector<double> > jet2SubjetBDiscEff( new std::vector<double>() );
  std::auto_ptr<std::vector<double> > AK8jetNSubjets( new std::vector<double>() );

  std::auto_ptr<double> jet1ptEff ( new double() );
  std::auto_ptr<double> jet2ptEff ( new double() );
  std::auto_ptr<double> jet1NsubjEff ( new double() );
  std::auto_ptr<double> jet2NsubjEff ( new double() );
  std::auto_ptr<double> jet1deltaReff ( new double() );
  std::auto_ptr<double> jet2deltaReff ( new double() );
  std::auto_ptr<double> jet1minmassEff ( new double() );
  std::auto_ptr<double> jet2minmassEff ( new double() );
  std::auto_ptr<double> jet1topMassEff ( new double() );
  std::auto_ptr<double> jet2topMassEff ( new double() );
  std::auto_ptr<double> jet1BDiscEff ( new double() );
  std::auto_ptr<double> jet2BDiscEff ( new double() );
  std::auto_ptr<double> jet1MaxSubjBDiscEff ( new double() );
  std::auto_ptr<double> jet2MaxSubjBDiscEff ( new double() );
  std::auto_ptr<double> AK8jet1MassEff ( new double() );
  std::auto_ptr<double> AK8jet1filteredMassEff ( new double() );
  std::auto_ptr<double> AK8jet1prunedMassEff ( new double() );
  std::auto_ptr<double> AK8jet1trimmedMassEff ( new double() );
  std::auto_ptr<double> AK8jet2MassEff ( new double() );
  std::auto_ptr<double> AK8jet2filteredMassEff ( new double() );
  std::auto_ptr<double> AK8jet2prunedMassEff ( new double() );
  std::auto_ptr<double> AK8jet2trimmedMassEff ( new double() );
  std::auto_ptr<double> mttgen( new double() );
  std::auto_ptr<double> mtttag( new double() );

  std::auto_ptr<p4_vector> AK8jetP4( new p4_vector() );
  std::auto_ptr<p4_vector> genTopP4( new p4_vector() );
  std::auto_ptr<p4_vector> topTagP4( new p4_vector() );
  std::auto_ptr<p4_vector> topTagFilteredP4( new p4_vector() );
  std::auto_ptr<p4_vector> topTagSubjetP4( new p4_vector() );

  std::auto_ptr<p4_vector> jet1P4( new p4_vector() );
  std::auto_ptr<p4_vector> jet2P4( new p4_vector() );
  std::auto_ptr<p4_vector> jet1SubjetP4( new p4_vector() );
  std::auto_ptr<p4_vector> jet2SubjetP4( new p4_vector() );

  std::auto_ptr<std::vector<int> > genTopStatus ( new std::vector<int>() );

  std::auto_ptr<unsigned int> npv( new unsigned int() );

  std::auto_ptr<int> jet1tagEff( new int() );
  std::auto_ptr<int> jet2tagEff( new int() );
  std::auto_ptr<int> genTopSize( new int() );
  std::auto_ptr<int> AK8jet1tagEff( new int() );
  std::auto_ptr<int> AK8jet2tagEff( new int() );

  //cout <<"std::auto initializations complete"<<endl;

  Nsubjettiness Nsub1(1, Njettiness::AxesMode::kt_axes, 1.0, 0.8);
  Nsubjettiness Nsub2(2, Njettiness::AxesMode::kt_axes, 1.0, 0.8);
  Nsubjettiness Nsub3(3, Njettiness::AxesMode::kt_axes, 1.0, 0.8);
  Nsubjettiness Nsub4(4, Njettiness::AxesMode::kt_axes, 1.0, 0.8);

  //cout <<"Nsubi intitialized"<<endl;

  std::vector<const reco::GenParticle *> genTop;

  //generated top four-vectors
  if(h_gen.isValid())  {
    for ( edm::View<reco::GenParticle>::const_iterator  igen = h_gen->begin(), genEnd = h_gen->end(); igen != genEnd; ++igen ) {
      if (fabs(igen->pdgId()) == 6){
	genTop.push_back( &(*igen) );
	genTopStatus->push_back(igen->status());
	//cout<<igen->status()<<endl;
      }
    }
    
    *genTopSize = genTop.size();

    for (unsigned int i=0;i<genTop.size();i++){
      if (genTop[i]->status() == 22){
	genTopP4->push_back(genTop[i]->polarP4());
      }
    }

    if (genTop.size() >= 2){
      if ((genTop[0]->status() == 22) && (genTop[1]->status() == 22)){
	*mttgen = (genTop[0]->p4() + genTop[1]->p4()).M();
      }
    }

    /*
    if (genTop.status() == 2) {
      //mttgen = (genTop[0]->p4() + genTop[1]->p4()).M();
      genTopP4->push_back(genTop[0]->polarP4());
      genTopP4->push_back(genTop[1]->polarP4());
    }
    */
  }

  //cout <<"genTop filled"<<endl;

  // Number of reconstructed PV's
  *npv = h_pv->size();

  //initializing reco jet tag flags to be -1 
  *jet1tagEff = -1;
  *jet2tagEff = -1;

  //initializing jets for mtttag
  std::vector<const pat::Jet *> topTag1,topTag2;

  double tagParamsEff[4] = {140.0, 250.0, 3.0, 50.0}; //Mass window, Nsubj, and minMass cuts for tag algorithm

  //top tag for-loop
  for ( edm::View<pat::Jet>::const_iterator jetBegin = h_topTag->begin(), jetEnd = h_topTag->end(), ijet = jetBegin; ijet != jetEnd; ++ijet ) {
    reco::Candidate::LorentzVector uncorrJet = ijet->correctedP4(0);
    reco::Candidate::PolarLorentzVector corrJet (uncorrJet.pt(), uncorrJet.eta(), uncorrJet.phi(), uncorrJet.mass());

    double nSubjets = ijet->numberOfDaughters();

    const reco::CATopJetTagInfo * catopTag = dynamic_cast<reco::CATopJetTagInfo const *>(ijet->tagInfo(topTagName_));

    double topMassEff = catopTag->properties().topMass;
    double minMassEff = catopTag->properties().minMass;

    topTagMinMass->push_back( minMassEff);
    topTagP4->push_back( corrJet );
    topTagBDisc->push_back( ijet->bDiscriminator("combinedSecondaryVertexBJetTags") );
    topTagNSubjets->push_back( nSubjets );

    double maxSubjetBDisc = -1;

    for (int i = 0; i < nSubjets; i++ ){
      const pat::Jet* this_subjet = dynamic_cast<const pat::Jet*>((ijet->daughter(i)));

      reco::Candidate::LorentzVector uncorrSubjet = this_subjet->correctedP4(0);
      reco::Candidate::PolarLorentzVector corrSubjet (uncorrSubjet.pt(), uncorrSubjet.eta(), uncorrSubjet.phi(), uncorrSubjet.mass());

      double bDisc = this_subjet->bDiscriminator("combinedSecondaryVertexBJetTags");
      
      topTagSubjetBDisc->push_back(bDisc);
      topTagSubjetP4->push_back(corrSubjet);

      if (bDisc > maxSubjetBDisc){
	maxSubjetBDisc = bDisc;
      }
    }

    //top tagging efficiency
    if (genTop.size() >= 2) {
      int double_countEff = 0;
      double deltaPhiSqEff_0 = (genTop[0]->phi() - corrJet.phi())*(genTop[0]->phi() - corrJet.phi());
      double deltaEtaSqEff_0 = (genTop[0]->eta() - corrJet.eta())*(genTop[0]->eta() - corrJet.eta());
      double deltaReff_0 = sqrt(deltaPhiSqEff_0 + deltaEtaSqEff_0);

      //cout <<"deltaReff_0 = "<<deltaReff_0<<endl;

      if (deltaReff_0 < 0.1){
	jet1P4->push_back(corrJet);
	topTag1.push_back( &(*ijet) );
	*jet1ptEff = corrJet.pt();
       	*jet1NsubjEff = nSubjets;
	*jet1deltaReff = deltaReff_0;
	*jet1minmassEff = minMassEff;
	*jet1topMassEff = topMassEff;
	*jet1BDiscEff = ijet->bDiscriminator("combinedSecondaryVertexBJetTags");
	*jet1MaxSubjBDiscEff = maxSubjetBDisc;
	*jet1tagEff = 0;
	//cout <<h_pv->size()<<endl;
	
	for (int i = 0; i < nSubjets; i++ ){
	  const pat::Jet* this_subjet1 = dynamic_cast<const pat::Jet*>((ijet->daughter(i)));

	  reco::Candidate::LorentzVector uncorrSubjet1 = this_subjet1->correctedP4(0);
	  reco::Candidate::PolarLorentzVector corrSubjet1 (uncorrSubjet1.pt(), uncorrSubjet1.eta(), uncorrSubjet1.phi(), uncorrSubjet1.mass());

	  double bDisc1 = this_subjet1->bDiscriminator("combinedSecondaryVertexBJetTags");
	  
	  jet1SubjetP4->push_back(corrSubjet1);
	  jet1SubjetBDiscEff->push_back(bDisc1);
	 }

	if ((topMassEff > tagParamsEff[0]) && (topMassEff < tagParamsEff[1]) && (nSubjets >= tagParamsEff[2]) && (minMassEff > tagParamsEff[3])){
	  *jet1tagEff = 1;
	}
	
	double_countEff += 1;
      }
      
      double deltaPhiSqEff_1 = (genTop[1]->phi() - corrJet.phi())*(genTop[1]->phi() - corrJet.phi());
      double deltaEtaSqEff_1 = (genTop[1]->eta() - corrJet.eta())*(genTop[1]->eta() - corrJet.eta());
      double deltaReff_1 = sqrt(deltaPhiSqEff_1 + deltaEtaSqEff_1);
         
      if (deltaReff_1 < 0.1){
	jet2P4->push_back(corrJet);
	topTag2.push_back( &(*ijet) );
        //corrJet2 = corrJet;
	*jet2ptEff = corrJet.pt();
	*jet2NsubjEff = nSubjets;
	*jet2deltaReff = deltaReff_1;
	*jet2minmassEff = minMassEff;
	*jet2topMassEff = topMassEff;
	*jet2BDiscEff = ijet->bDiscriminator("combinedSecondaryVertexBJetTags");
        *jet2MaxSubjBDiscEff = maxSubjetBDisc;
	*jet2tagEff = 0;
	//cout <<h_pv->size()<<endl;
	
	for (int i = 0; i < nSubjets; i++ ){
          const pat::Jet* this_subjet2 = dynamic_cast<const pat::Jet*>((ijet->daughter(i)));

	  reco::Candidate::LorentzVector uncorrSubjet2 = this_subjet2->correctedP4(0);
	  reco::Candidate::PolarLorentzVector corrSubjet2 (uncorrSubjet2.pt(), uncorrSubjet2.eta(), uncorrSubjet2.phi(), uncorrSubjet2.mass());

          double bDisc2 = this_subjet2->bDiscriminator("combinedSecondaryVertexBJetTags");

	  jet2SubjetP4->push_back(corrSubjet2);
          jet2SubjetBDiscEff->push_back(bDisc2);
	}

	if ((topMassEff > tagParamsEff[0]) && (topMassEff < tagParamsEff[1]) && (nSubjets >= tagParamsEff[2]) && (minMassEff > tagParamsEff[3])){
	  *jet2tagEff = 1;
	}
	
	double_countEff += 1;
        }
      
      if (double_countEff > 1){
	cout <<"DOUBLE COUNTING!"<<endl;
      }
    }
  }

  if ((*jet1tagEff != -1) && (*jet2tagEff != -1)){
    *mtttag = (topTag1[0]->p4() + topTag2[0]->p4()).M();
  }

  //filtered top tag for-loop
  for ( edm::View<pat::Jet>::const_iterator jetBegin = h_topTagFiltered->begin(), jetEnd = h_topTagFiltered->end(), ijet = jetBegin; ijet != jetEnd; ++ijet ) {
    reco::Candidate::LorentzVector uncorrJet = ijet->correctedP4(0);
    reco::Candidate::PolarLorentzVector corrJet (uncorrJet.pt(), uncorrJet.eta(), uncorrJet.phi(), uncorrJet.mass());

    double nSubjets = ijet->numberOfDaughters();

    const reco::CATopJetTagInfo * catopTag = dynamic_cast<reco::CATopJetTagInfo const *>(ijet->tagInfo(topTagName_));

    //double topMassEff = catopTag->properties().topMass;
    double minMassEff = catopTag->properties().minMass;

    topTagFilteredMinMass->push_back( minMassEff);
    topTagFilteredP4->push_back( corrJet );
    topTagFilteredBDisc->push_back( ijet->bDiscriminator("combinedSecondaryVertexBJetTags") );
    topTagFilteredNSubjets->push_back( nSubjets );
  }
  
  //cout <<"-----------"<<endl;

  //initializing AK8 jet tag flags to be 0
  *AK8jet1tagEff = 0;
  *AK8jet2tagEff = 0;

  //reconstructed AK8 jet four-vectors
  for ( std::vector<pat::Jet>::const_iterator jetBegin = h_AK8jet->begin(), jetEnd = h_AK8jet->end(), ijet = jetBegin; ijet != jetEnd; ++ijet ) {
    //cout<<ijet->pt()<<" GeV"<<endl;
    jetPt->push_back(ijet->pt());
    jetEta->push_back(ijet->eta());
    jetPhi->push_back(ijet->phi());

    AK8jetNSubjets->push_back(ijet->numberOfDaughters());

    ak8PFJetsCHSPrunedLinks->push_back(ijet->userFloat("ak8PFJetsCHSPrunedLinks"));
    ak8PFJetsCHSTrimmedLinks->push_back(ijet->userFloat("ak8PFJetsCHSTrimmedLinks"));
    ak8PFJetsCHSFilteredLinks->push_back(ijet->userFloat("ak8PFJetsCHSFilteredLinks"));

    double filteredMass = ijet->userFloat("ak8PFJetsCHSFilteredLinks");
    double prunedMass= ijet->userFloat("ak8PFJetsCHSPrunedLinks");
    double trimmedMass= ijet->userFloat("ak8PFJetsCHSTrimmedLinks");

    //int floatLabelsize = (ijet->userFloatNames()).size();

     /*
    for (int i =0; i < floatLabelsize; i++){
      cout<<(ijet->userFloatNames())[i]<<endl;
    }
     */

    reco::Candidate::LorentzVector LV_AK8jet = ijet->p4();
    reco::Candidate::PolarLorentzVector PLV_AK8jet (LV_AK8jet.pt(), LV_AK8jet.eta(), LV_AK8jet.phi(), LV_AK8jet.mass());

    AK8jetP4->push_back(PLV_AK8jet);

    //matching AK8jets with top-matched jets
    if (*jet1tagEff != -1) {

      const reco::CATopJetTagInfo * catopTag1 = dynamic_cast<reco::CATopJetTagInfo const *>(topTag1[0]->tagInfo(topTagName_));
      double minMass1 = catopTag1->properties().minMass;
      double nSubjets1 = topTag1[0]->numberOfDaughters();
      double deltaPhiSqEff_1 = (topTag1[0]->phi() - ijet->phi())*(topTag1[0]->phi() - ijet->phi());
      double deltaEtaSqEff_1 = (topTag1[0]->eta() - ijet->eta())*(topTag1[0]->eta() - ijet->eta());
      double deltaReff_1 = sqrt(deltaPhiSqEff_1 + deltaEtaSqEff_1);

      if (deltaReff_1 < 0.1){

        *AK8jet1MassEff = ijet->mass();
        *AK8jet1filteredMassEff = filteredMass;
        *AK8jet1prunedMassEff = prunedMass;
        *AK8jet1trimmedMassEff = trimmedMass;
	*AK8jet1tagEff |= 1;

	//filtered mass tagging
        if ((filteredMass > tagParamsEff[0]) && (filteredMass < tagParamsEff[1]) && (nSubjets1 >= tagParamsEff[2]) && (minMass1 > tagParamsEff[3])){
          *AK8jet1tagEff |= 2;
        }
	
	//pruned mass tagging 
        if ((prunedMass > tagParamsEff[0]) && (prunedMass < tagParamsEff[1]) && (nSubjets1 >= tagParamsEff[2]) && (minMass1 > tagParamsEff[3])){
          *AK8jet1tagEff |= 4;
        }

	//trimmed mass tagging
        if ((trimmedMass > tagParamsEff[0]) && (trimmedMass < tagParamsEff[1]) && (nSubjets1 >= tagParamsEff[2]) && (minMass1 > tagParamsEff[3])){
          *AK8jet1tagEff |= 8;
	}
      }
    }

    if (*jet2tagEff != -1) {

      const reco::CATopJetTagInfo * catopTag2 = dynamic_cast<reco::CATopJetTagInfo const *>(topTag2[0]->tagInfo(topTagName_));
      double minMass2 = catopTag2->properties().minMass;
      double nSubjets2 = topTag2[0]->numberOfDaughters();
      double deltaPhiSqEff_2 = (topTag2[0]->phi() - ijet->phi())*(topTag2[0]->phi() - ijet->phi());
      double deltaEtaSqEff_2 = (topTag2[0]->eta() - ijet->eta())*(topTag2[0]->eta() - ijet->eta());
      double deltaReff_2 = sqrt(deltaPhiSqEff_2 + deltaEtaSqEff_2);

      if (deltaReff_2 < 0.1){

        *AK8jet2MassEff= ijet->mass();
        *AK8jet2filteredMassEff = filteredMass;
        *AK8jet2prunedMassEff = prunedMass;
        *AK8jet2trimmedMassEff = trimmedMass;
        *AK8jet2tagEff |= 1;

        //filtered mass tagging                                                                                                                                                                      
        if ((filteredMass > tagParamsEff[0]) && (filteredMass < tagParamsEff[1]) && (nSubjets2 >= tagParamsEff[2]) && (minMass2 > tagParamsEff[3])){
          *AK8jet2tagEff |= 2;
        }

        //pruned mass tagging                                                                                                                                                         
        if ((prunedMass > tagParamsEff[0]) && (prunedMass < tagParamsEff[1]) && (nSubjets2 >= tagParamsEff[2]) && (minMass2 > tagParamsEff[3])){
          *AK8jet2tagEff |= 4;
	}

        //trimmed mass tagging                                                                                                                                                                            
        if ((trimmedMass > tagParamsEff[0]) && (trimmedMass < tagParamsEff[1]) && (nSubjets2 >= tagParamsEff[2]) && (minMass2 > tagParamsEff[3])){
          *AK8jet2tagEff |= 8;
        }
      }
    }
  }

  //Nsubjettiness for-loop
  if(h_ca8Jet.isValid()){
    //cout<<"There are "<<h_ca8Jet->size()<<" CA8 jets."<<endl;
    int k =  0;

    for ( edm::View<pat::Jet>::const_iterator jetBegin = h_ca8Jet->begin(), jetEnd = h_ca8Jet->end(), ijet = jetBegin; ijet != jetEnd; ++ijet ) {
      k += 1;
      std::vector<fastjet::PseudoJet> FJparticles;
      
      //cout<<"There are "<<ijet->numberOfDaughters()<<" daughters in CA8 jet number "<<k <<"."<<endl;

      for (unsigned i = 0; i < ijet->numberOfDaughters() ; i++){
	
	const reco::Candidate* this_constituent = dynamic_cast<const reco::Candidate*>(ijet->daughter(i));
	
	FJparticles.push_back( fastjet::PseudoJet( this_constituent->px(),
						   this_constituent->py(),
						   this_constituent->pz(),
						   this_constituent->energy() ) );
      }
      
      fastjet::PseudoJet combJet = fastjet::join(FJparticles);
   
      tau1->push_back(Nsub1.result(combJet));
      tau2->push_back(Nsub2.result(combJet));
      tau3->push_back(Nsub3.result(combJet));
      tau4->push_back(Nsub4.result(combJet));
    }
  }
  
  iEvent.put(jetPt,"jetPt");
  iEvent.put(jetEta,"jetEta");
  iEvent.put(jetPhi,"jetPhi");
  iEvent.put(topTagMinMass ,"topTagMinMass");
  iEvent.put(topTagBDisc   ,"topTagBDisc");
  iEvent.put(topTagNSubjets,"topTagNSubjets");
  iEvent.put(topTagFilteredMinMass ,"topTagFilteredMinMass");
  iEvent.put(topTagFilteredBDisc   ,"topTagFilteredBDisc");
  iEvent.put(topTagFilteredNSubjets,"topTagFilteredNSubjets");
  iEvent.put(topTagSubjetBDisc   ,"topTagSubjetBDisc");
  iEvent.put(tau1, "tau1");
  iEvent.put(tau2, "tau2");
  iEvent.put(tau3, "tau3");
  iEvent.put(tau4, "tau4");
  iEvent.put(ak8PFJetsCHSPrunedLinks,"ak8PFJetsCHSPrunedLinks");
  iEvent.put(ak8PFJetsCHSTrimmedLinks,"ak8PFJetsCHSTrimmedLinks");
  iEvent.put(ak8PFJetsCHSFilteredLinks,"ak8PFJetsCHSFilteredLinks");
  iEvent.put(jet1SubjetBDiscEff   ,"jet1SubjetBDiscEff");
  iEvent.put(jet2SubjetBDiscEff   ,"jet2SubjetBDiscEff");
  iEvent.put(AK8jetNSubjets,"AK8jetNSubjets");

  iEvent.put(jet1ptEff, "jet1ptEff");
  iEvent.put(jet2ptEff, "jet2ptEff");
  iEvent.put(jet1NsubjEff, "jet1NsubjEff");
  iEvent.put(jet2NsubjEff, "jet2NsubjEff");
  iEvent.put(jet1deltaReff, "jet1deltaReff");
  iEvent.put(jet2deltaReff, "jet2deltaReff");
  iEvent.put(jet1minmassEff, "jet1minmassEff");
  iEvent.put(jet2minmassEff, "jet2minmassEff");
  iEvent.put(jet1topMassEff, "jet1topMassEff");
  iEvent.put(jet2topMassEff, "jet2topMassEff");
  iEvent.put(jet1BDiscEff   ,"jet1BDiscEff");
  iEvent.put(jet2BDiscEff   ,"jet2BDiscEff");
  iEvent.put(jet1MaxSubjBDiscEff   ,"jet1MaxSubjBDiscEff");
  iEvent.put(jet2MaxSubjBDiscEff   ,"jet2MaxSubjBDiscEff");
  iEvent.put(AK8jet1MassEff ,"AK8jet1MassEff");
  iEvent.put(AK8jet1filteredMassEff ,"AK8jet1filteredMassEff");
  iEvent.put(AK8jet1prunedMassEff ,"AK8jet1prunedMassEff");
  iEvent.put(AK8jet1trimmedMassEff ,"AK8jet1trimmedMassEff");
  iEvent.put(AK8jet2MassEff ,"AK8jet2MassEff");
  iEvent.put(AK8jet2filteredMassEff ,"AK8jet2filteredMassEff");
  iEvent.put(AK8jet2prunedMassEff ,"AK8jet2prunedMassEff");
  iEvent.put(AK8jet2trimmedMassEff ,"AK8jet2trimmedMassEff");
  iEvent.put(mttgen, "mttgen");
  iEvent.put(mtttag, "mtttag");

  iEvent.put(AK8jetP4,"AK8jetP4");
  iEvent.put(genTopP4,"genTopP4");
  iEvent.put(topTagP4,"topTagP4");  
  iEvent.put(topTagFilteredP4,"topTagFilteredP4");
  iEvent.put(topTagSubjetP4, "topTagSubjetP4");

  iEvent.put(jet1P4, "jet1P4");
  iEvent.put(jet2P4, "jet2P4");
  iEvent.put(jet1SubjetP4, "jet1SubjetP4");
  iEvent.put(jet2SubjetP4, "jet2SubjetP4");

  iEvent.put(genTopStatus,"genTopStatus");
  
  iEvent.put(npv,"npv");

  iEvent.put(jet1tagEff,"jet1tagEff");
  iEvent.put(jet2tagEff,"jet2tagEff");
  iEvent.put(genTopSize,"genTopSize");
  iEvent.put(AK8jet1tagEff,"AK8jet1tagEff");
  iEvent.put(AK8jet2tagEff,"AK8jet2tagEff");
  return true;
}

// ------------ method called once each job just before starting event loop  ------------
void 
processMiniAOD::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
processMiniAOD::endJob() {
}

// ------------ method called when starting to processes a run  ------------
/*
void
processMiniAOD::beginRun(edm::Run const&, edm::EventSetup const&)
{ 
}
*/
 
// ------------ method called when ending the processing of a run  ------------
/*
void
processMiniAOD::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when starting to processes a luminosity block  ------------
/*
void
processMiniAOD::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a luminosity block  ------------
/*
void
processMiniAOD::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
processMiniAOD::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}
//define this as a plug-in
DEFINE_FWK_MODULE(processMiniAOD);
