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
  produces<std::vector<double> > ("topTagSubjetBDisc");
  produces<std::vector<double> > ("tau1");
  produces<std::vector<double> > ("tau2");
  produces<std::vector<double> > ("tau3");
  produces<std::vector<double> > ("tau4");

  produces<std::vector<reco::Candidate::PolarLorentzVector> > ("AK8jetP4");
  produces<std::vector<reco::Candidate::PolarLorentzVector> > ("genTopP4");
  produces<std::vector<reco::Candidate::PolarLorentzVector> > ("topTagP4");
  produces<std::vector<reco::Candidate::PolarLorentzVector> > ("topTagSubjetP4");

  produces<unsigned int>    ("npv");
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
  Handle<edm::View<pat::Jet> > h_ca8Jet;

  iEvent.getByLabel( AK8jetSrc_, h_AK8jet );
  //iEvent.getByLabel( GenJetSrc_, h_gen );
  iEvent.getByToken(prunedGenToken_,h_gen);
  iEvent.getByToken(pvSrc_,h_pv);
  iEvent.getByToken(topTagSrc_, h_topTag);
  iEvent.getByToken(ca8JetSrc_, h_ca8Jet);

  //cout <<"Handles created"<<endl;

  std::auto_ptr<std::vector<double> > jetPt ( new std::vector<double>() );
  std::auto_ptr<std::vector<double> > jetEta ( new std::vector<double>() );
  std::auto_ptr<std::vector<double> > jetPhi ( new std::vector<double>() );
  std::auto_ptr<std::vector<double> > topTagMinMass ( new std::vector<double>() );
  std::auto_ptr<std::vector<double> > topTagBDisc ( new std::vector<double>() );
  std::auto_ptr<std::vector<double> > topTagNSubjets ( new std::vector<double>() );
  std::auto_ptr<std::vector<double> > tau1 ( new std::vector<double>() );
  std::auto_ptr<std::vector<double> > tau2 ( new std::vector<double>() );
  std::auto_ptr<std::vector<double> > tau3 ( new std::vector<double>() );
  std::auto_ptr<std::vector<double> > tau4 ( new std::vector<double>() );

  std::auto_ptr<p4_vector> AK8jetP4( new p4_vector() );
  std::auto_ptr<p4_vector> genTopP4( new p4_vector() );
  std::auto_ptr<p4_vector> topTagP4( new p4_vector() );
  std::auto_ptr<p4_vector> topTagSubjetP4( new p4_vector() );
  std::auto_ptr<std::vector<double> > topTagSubjetBDisc( new std::vector<double>() );

  std::auto_ptr<unsigned int> npv( new unsigned int() );

  //cout <<"std::auto initializations complete"<<endl;

  Nsubjettiness Nsub1(1, Njettiness::AxesMode::kt_axes, 1.0, 0.8);
  Nsubjettiness Nsub2(2, Njettiness::AxesMode::kt_axes, 1.0, 0.8);
  Nsubjettiness Nsub3(3, Njettiness::AxesMode::kt_axes, 1.0, 0.8);
  Nsubjettiness Nsub4(4, Njettiness::AxesMode::kt_axes, 1.0, 0.8);

  //cout <<"Nsubi intitialized"<<endl;

  //reconstructed jet four-vectors
  for ( std::vector<pat::Jet>::const_iterator jetBegin = h_AK8jet->begin(), jetEnd = h_AK8jet->end(), ijet = jetBegin; ijet != jetEnd; ++ijet ) {
    //cout<<ijet->pt()<<" GeV"<<endl;
    jetPt->push_back(ijet->pt());
    jetEta->push_back(ijet->eta());
    jetPhi->push_back(ijet->phi());

    reco::Candidate::LorentzVector LV_AK8jet = ijet->p4();
    reco::Candidate::PolarLorentzVector PLV_AK8jet (LV_AK8jet.pt(), LV_AK8jet.eta(), LV_AK8jet.phi(), LV_AK8jet.mass());

    AK8jetP4->push_back(PLV_AK8jet);
  }

  //generated top four-vectors
  if(h_gen.isValid())  {
    std::vector<const reco::GenParticle *> genTop;
    for ( edm::View<reco::GenParticle>::const_iterator  igen = h_gen->begin(), genEnd = h_gen->end(); igen != genEnd; ++igen ) {
      if (fabs(igen->pdgId()) == 6){
	genTop.push_back( &(*igen) );
      }
    }
    if (genTop.size() == 2) {
      //*mttgen = (genTop[0]->p4() + genTop[1]->p4()).M();
      genTopP4->push_back(genTop[0]->polarP4());
      genTopP4->push_back(genTop[1]->polarP4());
    }
  }

  //cout <<"genTop filled"<<endl;

  // Number of reconstructed PV's
  *npv = h_pv->size();

  //top tag for-loop
  for ( edm::View<pat::Jet>::const_iterator jetBegin = h_topTag->begin(), jetEnd = h_topTag->end(), ijet = jetBegin; ijet != jetEnd; ++ijet ) {
    reco::Candidate::LorentzVector uncorrJet = ijet->correctedP4(0);
    reco::Candidate::PolarLorentzVector corrJet (uncorrJet.pt(), uncorrJet.eta(), uncorrJet.phi(), uncorrJet.mass());

    double nSubjets = ijet->numberOfDaughters();
    
    const reco::CATopJetTagInfo * catopTag = 
      dynamic_cast<reco::CATopJetTagInfo const *>(ijet->tagInfo(topTagName_));

    topTagMinMass->push_back( catopTag->properties().minMass);
    topTagP4->push_back( corrJet );
    topTagBDisc->push_back( ijet->bDiscriminator("combinedSecondaryVertexBJetTags") );
    topTagNSubjets->push_back( ijet->numberOfDaughters() );

    for (int i = 0; i < nSubjets; i++ ){
      const pat::Jet* this_subjet = dynamic_cast<const pat::Jet*>((ijet->daughter(i)));

      reco::Candidate::LorentzVector uncorrSubjet = this_subjet->correctedP4(0);
      reco::Candidate::PolarLorentzVector corrSubjet (uncorrSubjet.pt(), uncorrSubjet.eta(), uncorrSubjet.phi(), uncorrSubjet.mass());

      double bDisc = this_subjet->bDiscriminator("combinedSecondaryVertexBJetTags");

      topTagSubjetBDisc->push_back(bDisc);
      topTagSubjetP4->push_back(corrSubjet);
    }
  }

  //cout <<"topTagJets filled"<<endl;

  //Nsubjettiness for-loop
  for ( edm::View<pat::Jet>::const_iterator jetBegin = h_ca8Jet->begin(), jetEnd = h_ca8Jet->end(), ijet = jetBegin; ijet != jetEnd; ++ijet ) {

    std::vector<fastjet::PseudoJet> FJparticles;

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

  iEvent.put(jetPt,"jetPt");
  iEvent.put(jetEta,"jetEta");
  iEvent.put(jetPhi,"jetPhi");
  iEvent.put(topTagMinMass ,"topTagMinMass");
  iEvent.put(topTagBDisc   ,"topTagBDisc");
  iEvent.put(topTagNSubjets,"topTagNSubjets");
  iEvent.put(topTagSubjetBDisc   ,"topTagSubjetBDisc");
  iEvent.put(tau1, "tau1");
  iEvent.put(tau2, "tau2");
  iEvent.put(tau3, "tau3");
  iEvent.put(tau4, "tau4");

  iEvent.put(AK8jetP4,"AK8jetP4");
  iEvent.put(genTopP4,"genTopP4");
  iEvent.put(topTagP4,"topTagP4");  
  iEvent.put(topTagSubjetP4, "topTagSubjetP4");
  
  iEvent.put(npv,"npv");
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
