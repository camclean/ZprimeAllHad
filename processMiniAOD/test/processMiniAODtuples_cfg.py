import FWCore.ParameterSet.Config as cms

process = cms.Process("MiniAOD")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.options = cms.untracked.PSet( 
    wantSummary = cms.untracked.bool(True),
    allowUnscheduled = cms.untracked.bool(True) 
    )

process.MessageLogger.cerr.FwkReport.reportEvery = 100

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )

tracks                = 'unpackedTracksAndVertices'
vertices              = 'unpackedTracksAndVertices'
pfcandidates          = 'packedPFCandidates'
genjetparticles       = 'packedGenParticles'
importantgenparticles = 'prunedGenParticles'
mergedvertices        = 'unpackedTracksAndVertices'
mergedvertices2       = 'secondary'
primaryvertices       = 'offlineSlimmedPrimaryVertices'

#print 'Test 1'

###############################################################################
#INPUT

process.source = cms.Source("PoolSource",
                                # replace 'myfile.root' with the source file you want to use
       fileNames = cms.untracked.vstring(
       #'dcap:///pnfs/cms/WAX/11/store/user/lpctlbsm/srappocc/TTJets_TuneZ2_7TeV-madgraph-tauola/ttbsm_v8_Summer11-PU_S4_START42_V11-v1/5c91b0700768331a44f51c8a9892d391/ttbsm_42x_mc_1_2_RlY.root'
       #'dcap:///pnfs/cms/WAX/11/store/user/lpctlbsm/weizou/WprimeToTBbar_M-2000_TuneZ2_7TeV-pythia6/ttbsm_v8_Summer11-PU_S4_-START42_V11-v1/2bcf344afee8f9cb5489a05cc32c05cf/ttbsm_42x_mc_1_1_J1v.root'
        #    '/store/results/B2G/TT_8TeV-mcatnlo/StoreResults-Summer12_DR53X-PU_S10_START53_V7A-v1_TLBSM_53x_v2-c04f3b4fa74c8266c913b71e0c74901d/TT_8TeV-mcatnlo/USER/StoreResults-Summer12_DR53X-PU_S10_START53_V7A-v1_TLBSM_53x_v2-c04f3b4fa74c8266c913b71e0c74901d/0000/FEBBE69C-1942-E211-9959-002354EF3BE2.root',
        #'/store/user/lpctlbsm/jdolen/TT_CT10_TuneZ2star_8TeV-powheg-tauola/Summer12_DR53X-PU_S10_START53_V7A-v2_TLBSM_53x_v3_bugfix_v1/99bd99199697666ff01397dad5652e9e/tlbsm_53x_v3_mc_1912_2_rsE.root'
        #'file:/eos/uscms/store/user/chmclean/TT_Tune4C_13TeV-pythia8-tauola/miniAOD_TT_09_01_2014/92bfc1aa0ef8c674e0edabb945b19298/miniAOD-prod_PAT_52_1_Xsd.root'
        #'/store/user/chmclean/TT_Tune4C_13TeV-pythia8-tauola/miniAOD_TT_09_01_2014/92bfc1aa0ef8c674e0edabb945b19298/miniAOD-prod_PAT_52_1_Xsd.root'
        #'/store/user/chmclean/QCD_Pt-1800to2400_Tune4C_13TeV_pythia8/miniAOD_QCD_Pt-1800to2400_09_01_2014/92bfc1aa0ef8c674e0edabb945b19298/miniAOD-prod_PAT_100_1_Es8.root'
        'file:/eos/uscms/store/user/camclean/QCD_Pt-15to3000_Tune4C_Flat_13TeV_pythia8/miniAOD_QCD_Pt-15to3000_Tune4C_Flat_13TeV_pythia8_10_01_2014/92bfc1aa0ef8c674e0edabb945b19298/miniAOD-prod_PAT_1209_1_2eT.root'
        )
                            )
##############################################################################                                                                                                                              
#OUTPUT                                                                                                                                                                                                     
process.out = cms.OutputModule("PoolOutputModule",
                               fileName = cms.untracked.string("miniAOD.root"),
                               SelectEvents   = cms.untracked.PSet( SelectEvents = cms.vstring('p') ),
                               outputCommands = cms.untracked.vstring('drop *',
                                                                      'keep *_*miniAOD*_*_*'
                                                                      )
                               )

###############################################################################
#SETUP

process.load('PhysicsTools.PatAlgos.producersLayer1.patCandidates_cff')
process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.StandardSequences.Geometry_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'START70_V6::All'

process.load('RecoJets.Configuration.RecoPFJets_cff')
process.load('RecoJets.Configuration.RecoGenJets_cff')
process.fixedGridRhoFastjetAll.pfCandidatesTag = pfcandidates

from RecoJets.JetProducers.SubJetParameters_cfi import SubJetParameters
from RecoJets.JetProducers.CaloJetParameters_cfi import *
from RecoJets.JetProducers.PFJetParameters_cfi import *
from RecoJets.JetProducers.CATopJetParameters_cfi import *
from RecoJets.JetProducers.AnomalousCellParameters_cfi import *
from RecoJets.JetProducers.GenJetParameters_cfi import *
from RecoJets.JetProducers.caTopTaggers_cff import *
from PhysicsTools.PatAlgos import *


############################################################################## 
#GENJETS

from RecoJets.JetProducers.ca4GenJets_cfi import ca4GenJets
from RecoJets.JetProducers.ak5GenJets_cfi import ak5GenJets

process.ca8GenJets = ca4GenJets.clone( rParam = cms.double(0.8),
                                          src = cms.InputTag(genjetparticles))

process.ca8GenJetsPruned = ca4GenJets.clone(
  rParam = cms.double(0.8),
  src = cms.InputTag(genjetparticles),
  usePruning = cms.bool(True),
  zcut = cms.double(0.1),
  rcut_factor = cms.double(0.5),
  nFilt = cms.int32(2),
  writeCompound = cms.bool(True),
  #jetCollInstanceName=cms.string("SubJets")
  )

##############################################################################
# RECO

process.chs = cms.EDFilter("CandPtrSelector",
                           src = cms.InputTag("packedPFCandidates"),
                           cut = cms.string("fromPV"))
chsstring = 'chs'

process.ak4PFJets.src = pfcandidates
process.ak5PFJets.src = pfcandidates
process.ca4PFJets.src = pfcandidates
process.kt6PFJets.src = pfcandidates

process.ca8PFJets  = process.ca4PFJets.clone(rParam = 0.8,  doAreaFastjet = True)

# CATopJet PF Jets with adjacency 
#process.cmsTopTagCHS = cmsTopTagPFJetsCHS.clone()
process.cmsTopTagCHS = cms.EDProducer(
    "CATopJetProducer",
    PFJetParameters.clone( src = cms.InputTag(chsstring),
                           doAreaFastjet = cms.bool(True),
                           doRhoFastjet = cms.bool(False),
                           jetPtMin = cms.double(100.0)
                           ),
    AnomalousCellParameters,
    CATopJetParameters.clone( jetCollInstanceName = cms.string("SubJets"), 
                              verbose = cms.bool(False),
                              algorithm = cms.int32(1), # 0 = KT, 1 = CA, 2 = anti-KT
                              tagAlgo = cms.int32(0), #0=legacy top
                              useAdjacency = cms.int32(2), # modified adjacency
                              centralEtaCut = cms.double(2.5), # eta for defining "central" jets
                              sumEtBins = cms.vdouble(0,1600,2600), # sumEt bins over which cuts vary. vector={bin 0 lower bound, bin 1 lower bound, ...}
                              rBins = cms.vdouble(0.8,0.8,0.8), # Jet distance paramter R. R values depend on sumEt bins.
                              ptFracBins = cms.vdouble(0.05,0.05,0.05), # minimum fraction of central jet pt for subjets (deltap)
                              deltarBins = cms.vdouble(0.19,0.19,0.19), # Applicable only if useAdjacency=1. deltar adjacency values for each sumEtBin
                              nCellBins = cms.vdouble(1.9,1.9,1.9), 
                            ),
    jetAlgorithm = cms.string("CambridgeAachen"),
    rParam = cms.double(0.8),
    writeCompound = cms.bool(True)
    )

process.CATopTagInfos = cms.EDProducer("CATopJetTagger",
                                    src = cms.InputTag("cmsTopTagCHS"),
                                    TopMass = cms.double(171),
                                    TopMassMin = cms.double(0.),
                                    TopMassMax = cms.double(250.),
                                    WMass = cms.double(80.4),
                                    WMassMin = cms.double(0.0),
                                    WMassMax = cms.double(200.0),
                                    MinMassMin = cms.double(0.0),
                                    MinMassMax = cms.double(200.0),
                                    verbose = cms.bool(False)
                                    )
##############################################################################
#PAT JETS
from PhysicsTools.PatAlgos.tools.jetTools import *
from PhysicsTools.PatAlgos.mcMatchLayer0.jetFlavourId_cff import patJetFlavourAssociation
#from RecoParticleFlow.PFProducer import *

#import RecoEgamma.EgammaElectronProducers.gedGsfElectronFinalizer_cfi
#import RecoParticleFlow.PFProducer.pfLinker_cfi
#import RecoParticleFlow.PFProducer.particleFlowTmpPtrs_cfi

#process.particleFlow = RecoParticleFlow.PFProducer.pfLinker_cfi.pfLinker.clone()
#process.particleFlow.PFCandidate = [cms.InputTag("particleFlowTmp")]

process.load('RecoBTag.Configuration.RecoBTag_cff')
process.load('RecoJets.Configuration.RecoJetAssociations_cff')
process.load('PhysicsTools.PatAlgos.slimming.unpackedTracksAndVertices_cfi')

# fix JTA (see https://github.com/cms-sw/cmssw/tree/CMSSW_7_0_X/RecoJets/JetAssociationProducers/python)

process.ak5JetTracksAssociatorAtVertexPF.jets = cms.InputTag("ak4PFJets")
process.ak5JetTracksAssociatorAtVertexPF.tracks = cms.InputTag(tracks)
process.impactParameterTagInfos.primaryVertex = cms.InputTag(vertices)
process.inclusiveSecondaryVertexFinderTagInfos.extSVCollection = cms.InputTag(mergedvertices,mergedvertices2,"")
process.combinedSecondaryVertex.trackMultiplicityMin = 1

#print 'Test 2'

#patJetsCA8PF
addJetCollection(
    process,
    labelName = 'CA8PF',
    jetSource = cms.InputTag('ca8PFJets'),
    algo = 'ca8',
    rParam = 0.8,
    jetCorrections = ('AK7PFchs', cms.vstring(['L1FastJet', 'L2Relative', 'L3Absolute']), 'None'),
    trackSource = cms.InputTag(tracks),
    pvSource = cms.InputTag(vertices),
    btagDiscriminators = ['combinedSecondaryVertexBJetTags'],
    getJetMCFlavour = False
    )
process.patJetPartonMatchCA8PF.matched=importantgenparticles
process.patJetCorrFactorsCA8PF.primaryVertices = primaryvertices
process.patJetGenJetMatchCA8PF.matched = 'ca8GenJets'#'slimmedGenJets'
process.patJetPartons.particles = importantgenparticles

# patJetsCMSTopTagCHS
addJetCollection(
    process,
    labelName = 'CMSTopTagCHS',
    jetSource = cms.InputTag('cmsTopTagCHS'),
    jetCorrections = ('AK7PFchs', cms.vstring(['L1FastJet', 'L2Relative', 'L3Absolute']), 'None'),
    trackSource = cms.InputTag(tracks),
    pvSource = cms.InputTag(vertices),
    btagDiscriminators = ['combinedSecondaryVertexBJetTags'],
    #getJetMCFlavour = False,
        # btagInfos = [
        # 'CATopTagInfos'
        #  ]   
    )
process.patJetCorrFactorsCMSTopTagCHS.primaryVertices = primaryvertices
process.patJetGenJetMatchCMSTopTagCHS.matched = 'ca8GenJetsPruned'#'slimmedGenJets'
process.patJetPartonMatchCMSTopTagCHS.matched = importantgenparticles
process.jetTracksAssociatorAtVertexCMSTopTagCHS=process.ak5JetTracksAssociatorAtVertexPF.clone(jets = cms.InputTag('cmsTopTagCHS'), coneSize = 0.8)
process.secondaryVertexTagInfosCMSTopTagCHS.trackSelection.jetDeltaRMax = cms.double(0.8) # default is 0.3                                                                                                 
process.secondaryVertexTagInfosCMSTopTagCHS.vertexCuts.maxDeltaRToJetAxis = cms.double(0.8) # default is 0.5     
process.combinedSecondaryVertexCMSTopTagCHS= process.combinedSecondaryVertex.clone()
process.combinedSecondaryVertexCMSTopTagCHS.trackSelection.jetDeltaRMax = cms.double(0.8)
process.combinedSecondaryVertexCMSTopTagCHS.trackPseudoSelection.jetDeltaRMax = cms.double(0.8)
process.combinedSecondaryVertexBJetTagsCMSTopTagCHS.jetTagComputer = cms.string('combinedSecondaryVertexCMSTopTagCHS')
process.patJetsCMSTopTagCHS.addTagInfos = True
process.patJetsCMSTopTagCHS.tagInfoSources = cms.VInputTag(
    cms.InputTag('CATopTagInfos')
    )

addJetCollection(
    process,
    labelName = 'CMSTopTagCHSSubjets',
    jetSource = cms.InputTag('cmsTopTagCHS','SubJets'),
    jetCorrections = ('AK7PFchs', cms.vstring(['L1FastJet', 'L2Relative', 'L3Absolute']), 'None'),
    trackSource = cms.InputTag(tracks),
    pvSource = cms.InputTag(vertices),
    btagDiscriminators = ['combinedSecondaryVertexBJetTags'],
    getJetMCFlavour = False,
    )

process.patJetPartonMatchCMSTopTagCHSSubjets.matched=importantgenparticles
process.patJetCorrFactorsCMSTopTagCHSSubjets.primaryVertices = primaryvertices
process.patJetGenJetMatchCMSTopTagCHSSubjets.matched = 'ca8GenJets'#slimmedGenJets'
process.patJetPartonMatchCMSTopTagCHSSubjets.matched = importantgenparticles

#print 'Test 3'

process.patJetsCMSTopTagCHSPacked = cms.EDProducer("BoostedJetMerger",
    jetSrc=cms.InputTag("patJetsCMSTopTagCHS" ),
    subjetSrc=cms.InputTag("patJetsCMSTopTagCHSSubjets")
      )

process.patMETs.addGenMET = False # There's no point in recalculating this, and we can't remake it since we don't have genParticles beyond |eta|=5 

##############################################################################  
#PRODUCER
from Analysis.BoostedTopAnalysis.CATopTagParams_cfi import caTopTagParams

process.miniAOD = cms.EDFilter('processMiniAOD',
                               AK8jetSrc = cms.InputTag('slimmedJetsAK8'),
                               pruned = cms.InputTag('prunedGenParticles'),
                               pvSrc = cms.InputTag('offlineSlimmedPrimaryVertices'),
                               topTagSrc = cms.InputTag('patJetsCMSTopTagCHSPacked'),
                               ca8JetSrc = cms.InputTag('patJetsCA8PF'),
                               topTagParams = caTopTagParams.clone(
                                    tagName = cms.string('CATop')
                                    )
                               )
#print 'Test 4'
##############################################################################  
#PATHS

print 'Making the path'

process.p = cms.Path(
    #process.ca8GenJetsPruned
   # process.chs
   # *process.cmsTopTagCHS
   # *process.CATopTagInfos
   # *process.unpackedTracksAndVertices
    #*process.combinedSecondaryVertex
   # *process.particleFlow
   # *process.ak4PFJets
   # *process.ak5JetTracksAssociatorAtVertexPF
   # *process.impactParameterTagInfos
   # *process.patJetPartonMatchCMSTopTagCHS
   # *process.patJetCorrFactorsCMSTopTagCHS
   # *process.patJetGenJetMatchCMSTopTagCHS
    #*process.jetTracksAssociatorAtVertexCMSTopTagCHS
    #*process.combinedSecondaryVertexCMSTopTagCHS
   # *process.combinedSecondaryVertexBJetTagsCMSTopTagCHS
   # *process.patJetsCMSTopTagCHS
   # *process.patJetsCMSTopTagCHSPacked
   # *process.miniAOD
    )
'''
##############################################################################  
#OUTPUT
process.out = cms.OutputModule("PoolOutputModule",
                               fileName = cms.untracked.string("miniAOD_RSGluonToTT_4TeV.root"),
                               SelectEvents   = cms.untracked.PSet( SelectEvents = cms.vstring('p') ),
                               outputCommands = cms.untracked.vstring('drop *',
                                                                      'keep *_*miniAOD*_*_*'
                                                                      )  
                               )

process.outpath = cms.EndPath(process.out)
'''
#print 'Test 5'
process.outpath = cms.EndPath(process.out)

#print 'Test 6'
#process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.out.dropMetaData = cms.untracked.string("DROPPED")
