#ifndef NJet_H
#define NJet_H

#include <string>
#include <vector>
#include <iostream>

#include "TFile.h"
#include "TNamed.h"
#include "TChain.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "DataFormats/Common/interface/RefToBase.h"

#include "PhysicsTools/SelectorUtils/interface/JetIDSelectionFunctor.h"
#include "PhysicsTools/SelectorUtils/interface/PFJetIDSelectionFunctor.h"
#include "PhysicsTools/SelectorUtils/interface/strbitset.h"
#include "PhysicsTools/JetMCUtils/interface/JetMCTag.h"
#include "PhysicsTools/JetMCUtils/interface/CandMCTag.h"

#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/EcalDetId/interface/EBDetId.h"
#include "DataFormats/HcalDetId/interface/HcalDetId.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/JetReco/interface/CaloJet.h"
#include "DataFormats/METReco/interface/CaloMET.h"
#include "DataFormats/METReco/interface/CaloMETCollection.h"
#include "DataFormats/CaloTowers/interface/CaloTowerCollection.h"
#include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "DataFormats/JetReco/interface/PFJet.h"
#include "SimDataFormats/GeneratorProducts/interface/GenRunInfoProduct.h"

#include "Geometry/CaloGeometry/interface/CaloCellGeometry.h"
#include "Geometry/CaloGeometry/interface/CaloSubdetectorGeometry.h"
#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
#include "Geometry/Records/interface/IdealGeometryRecord.h"

#include "TrackingTools/TrackAssociator/interface/TrackDetectorAssociator.h"
#include "TrackingTools/TrackAssociator/interface/TrackAssociatorParameters.h"

#include "SimDataFormats/JetMatching/interface/JetMatchedPartons.h"

#include "DataFormats/MuonReco/interface/MuonSelectors.h"

#include "DataFormats/BeamSpot/interface/BeamSpot.h"

//Version > CMSSW_3_1_X
#include "SimTracker/TrackerHitAssociation/interface/TrackerHitAssociator.h"
#include "Geometry/TrackerGeometryBuilder/interface/TrackerGeometry.h"
#include "Geometry/Records/interface/TrackerDigiGeometryRecord.h"
#include "Geometry/CommonDetUnit/interface/GeomDet.h"
#include "Geometry/CommonDetUnit/interface/GeomDetType.h"
#include "Geometry/CommonDetUnit/interface/GeomDetUnit.h"
#include "Geometry/TrackerGeometryBuilder/interface/PixelGeomDetUnit.h"
#include "Geometry/TrackerGeometryBuilder/interface/PixelGeomDetType.h"
#include "DataFormats/SiPixelDetId/interface/PXBDetId.h"
#include "DataFormats/SiPixelDetId/interface/PXFDetId.h"
#include "DataFormats/SiPixelDetId/interface/PixelSubdetector.h"

#include "DataFormats/TrackingRecHit/interface/TrackingRecHitFwd.h"
#include "DataFormats/TrackingRecHit/interface/TrackingRecHit.h"

#include "TrackingTools/TrackAssociator/interface/TrackDetectorAssociator.h"
#include "SimTracker/Records/interface/TrackAssociatorRecord.h"



template <typename T> class NJet {
public:
  NJet(); 
  ~NJet(); 

  void setup(const edm::ParameterSet&, TTree*);
  void analyze(const edm::Event&, const edm::EventSetup&, TTree*);

private:
  void fillExtra(const edm::View<T>& pJets, int jtno);
  bool looseJetID(T const &jet, reco::JetID const &jetID);
  bool tightJetID(T const &jet, reco::JetID const &jetID);
  bool looseJetID(T const &jet);
  bool tightJetID(T const &jet);
  edm::InputTag jets_, jetIDs_, partMatch_, genjets_, genparticles_, met_, weight_tag;                   
  edm::InputTag ebrechits_, beamSpot_;
  edm::InputTag recTracks_, recMuons_, zspJets_;
  std::string l2name_;
  std::string l3name_;
  std::string JPTname_;
  std::string l2l3name_;
  std::string l2l3l4JWname_;
  std::string l2l3JPTname_;

  double conesize_;
  float weight_;
  TrackDetectorAssociator trackAssociator_;
  TrackAssociatorParameters parameters_;

  //tree variables:
  const int kjMAX;               // Max number of jets stored in an event
  const int kMAX;                // Max number of towers/tracks/particles stored in an event
  const int kMaxStableGenPart_;  // Max number of stable gen particles stored in an event

  // Event info
  unsigned int runNumber_;
  unsigned int luminosityBlockNumber_;
  unsigned int eventNumber_;
  bool hltPhysicsDeclared_;
  bool hltL1Jet6U_;
  bool hltDiJetAve15U_;
  bool hltDiJetAve30U_;
  bool hltDiJetAve50U_;
  bool hltDiJetAve70U_;
  bool hltDiJetAve100U_;
  bool hltDiJetAve140U_;
  int vtxNTracks_;
  float vtxPosX_, vtxPosY_, vtxPosZ_;
  float vtxNormalizedChi2_, vtxNDof_;
  bool vtxIsFake_;

  // Calo jets and jet ID
  JetIDSelectionFunctor jetIDCaloFunctorLoose_;
  JetIDSelectionFunctor jetIDCaloFunctorTight_;
  PFJetIDSelectionFunctor jetIDPFFunctorLoose_;
  PFJetIDSelectionFunctor jetIDPFFunctorTight_;

  int    minNumJets_;
  int    NobjJet;
  bool *jetIDLoose_, *jetIDTight_;
  float *jetpt, *jetphi, *jeteta, *jetet, *jete, *jetgenjetDeltaR;
  int *n90Hits_;
  float *fHad_, *fEMF_, *fHPD_, *fRBX_;
  float *jetEtWeightedSigmaPhi_, *jetEtWeightedSigmaEta_;
  float *jscalel2, *jscalel3, *jscaleZSP, *jscaleJPT, *jscalel2l3, *jscalel2l3JPT,*jscalel4JW;
  int *jetieta_, *jetiphi_;

  // Gen jets matched to calo jets
  float *genjetpt, *genjetphi, *genjeteta, *genjetet, *genjete;

  // Gen jet collection
  int    NobjGenJet;
  float *genjetcolpt, *genjetcolphi, *genjetcoleta, *genjetcolet, *genjetcole;
  float *genjetcoleme,*genjetcolhade,*genjetcolinve,*genjetcolauxe;
  int   *genjetcol_jet_idx;

  // Get jet particles
  int NobjGenJetPart;
  float *genjetparte,*genjetpartpt,*genjetparteta,*genjetpartphi;
  int *genjetpartpdg,*genjetpart_genjetcolidx;

  //duplicated for ALGO and PHYS Def
  float *genpartpt_algo, *genpartphi_algo, *genparteta_algo, *genpartet_algo, *genparte_algo, *genpartm_algo;
  int   *genpartid_algo;
  float *genpartpt_phys, *genpartphi_phys, *genparteta_phys, *genpartet_phys, *genparte_phys, *genpartm_phys;
  int   *genpartid_phys;

  int   NobjTow;
  float *towet, *toweta, *towphi, *towen, *towem, *towhd, *towoe;
  int   *towid_phi, *towid_eta, *towid, *tow_jetidx;
  float mmet, mphi, msum, weight, xsec;
  unsigned int *numBadEcalCells_, *numBadHcalCells_;
  unsigned int *numProblematicEcalCells_, *numProblematicHcalCells_;
  unsigned int *numRecoveredEcalCells_, *numRecoveredHcalCells_;

  int   NobjTrack;
  bool *trackQualityL, *trackQualityT, *trackQualityHP;
  float *trackpt, *tracketa, *trackphi, *trackp, *tracketaout, *trackphiout;
  float *trackdr, *trackdrout, *trackchi2, *trackd0, *trackz0;
  float *trackemc1, *trackemc3, *trackemc5;
  float *trackhac1, *trackhac3, *trackhac5;
  float *muDR, *muDE;
  int   *trackid, *tracktowid, *tracktowidphi, *tracktowideta, *tracknhits, *track_jetidx;

  // pthat
  float genEvtScale;

  // ECAL cells
  bool  writeEcalCells;
  int   NobjETowCal;
  int   *etowid_phi, *etowid_eta, *etowid, *etownum, *etow_towidx, *etow_jetidx;
  float *etowet, *etoweta, *etowphi, *etowe;

  // Stable gen particles
  bool    writeGenJetPart_;
  bool    writeStableGenPart_;
  int     NobjStableGenPart_;
  float * stableGenPartM_;
  float * stableGenPartE_;
  float * stableGenPartEt_;
  float * stableGenPartP_;
  float * stableGenPartPt_;
  float * stableGenPartEta_;
  float * stableGenPartPhi_;
  int   * stableGenPartPDGId_;
};

//implementation
#include "Calibration/CalibTreeMaker/interface/NJet.h"
#include "DataFormats/Common/interface/Ref.h"
#include "DataFormats/Common/interface/RefProd.h"
#include "DataFormats/Common/interface/RefToBase.h"
#include "DataFormats/JetReco/interface/JetID.h"
#include "DataFormats/METReco/interface/CaloMET.h"
#include "DataFormats/MuonReco/interface/MuonSelectors.h"
#include "DataFormats/Provenance/interface/EventAuxiliary.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "JetMETCorrections/Objects/interface/JetCorrector.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GtFdlWord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
#include "Geometry/CaloGeometry/interface/CaloSubdetectorGeometry.h"

#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Common/interface/TriggerNames.h"

template <typename T> NJet<T>::NJet()
  : kjMAX(50), kMAX(10000), kMaxStableGenPart_(1000),
    jetIDCaloFunctorLoose_(JetIDSelectionFunctor(JetIDSelectionFunctor::PURE09,JetIDSelectionFunctor::LOOSE)),
    jetIDCaloFunctorTight_(JetIDSelectionFunctor(JetIDSelectionFunctor::PURE09,JetIDSelectionFunctor::TIGHT)),
    jetIDPFFunctorLoose_(PFJetIDSelectionFunctor(PFJetIDSelectionFunctor::FIRSTDATA,PFJetIDSelectionFunctor::LOOSE)),
    jetIDPFFunctorTight_(PFJetIDSelectionFunctor(PFJetIDSelectionFunctor::FIRSTDATA,PFJetIDSelectionFunctor::TIGHT)) {



  // Event info
  runNumber_ = 0;
  luminosityBlockNumber_ = 0;
  eventNumber_ = 0;

  hltPhysicsDeclared_ = false;

  hltL1Jet6U_ = false;
  hltDiJetAve15U_ = false;
  hltDiJetAve30U_ = false;
  hltDiJetAve50U_ = false;
  hltDiJetAve70U_ = false;
  hltDiJetAve100U_ = false;
  hltDiJetAve140U_ = false;

  vtxNTracks_ = 0;
  vtxPosX_ = 0.;
  vtxPosY_ = 0.;
  vtxPosZ_ = 0.;
  vtxNormalizedChi2_ = 0.;
  vtxNDof_ = 0.;
  vtxIsFake_ = false;


  // CaloTower branches for all jets
  NobjTow    = 0;
  towet      = new float [ kMAX ];
  toweta     = new float [ kMAX ];
  towphi     = new float [ kMAX ];
  towen      = new float [ kMAX ];
  towem      = new float [ kMAX ];
  towhd      = new float [ kMAX ];
  towoe      = new float [ kMAX ];
  towid_phi  = new int[ kMAX ];
  towid_eta  = new int[ kMAX ];
  towid      = new int[ kMAX ];
  tow_jetidx = new int[ kMAX ];
  numBadEcalCells_ = new unsigned int[ kMAX ];
  numBadHcalCells_ = new unsigned int[ kMAX ];
  numProblematicEcalCells_ = new unsigned int[ kMAX ];
  numProblematicHcalCells_ = new unsigned int[ kMAX ];
  numRecoveredEcalCells_ = new unsigned int[ kMAX ];
  numRecoveredHcalCells_ = new unsigned int[ kMAX ];


  // track branches
  NobjTrack      = 0;
  trackpt        = new float [ kMAX ];
  tracketa       = new float [ kMAX ];
  trackphi       = new float [ kMAX ];
  trackp         = new float [ kMAX ];
  trackdr        = new float [ kMAX ];
  tracketaout    = new float [ kMAX ];
  trackphiout    = new float [ kMAX ];
  trackdrout     = new float [ kMAX ];
  trackemc1      = new float [ kMAX ];
  trackemc3      = new float [ kMAX ];
  trackemc5      = new float [ kMAX ];
  trackhac1      = new float [ kMAX ];
  trackhac3      = new float [ kMAX ];
  trackhac5      = new float [ kMAX ];
  tracktowid     = new int [ kMAX ];
  tracktowidphi  = new int [ kMAX ];
  tracktowideta  = new int [ kMAX ];
  track_jetidx   = new int[ kMAX ];
  trackid        = new int[ kMAX ]; // abs(PiD) if available, guess: muons only; =0: unknown
  tracknhits     = new int[ kMAX ]; 
  trackQualityL  = new bool[kMAX];
  trackQualityT  = new bool[kMAX];
  trackQualityHP = new bool[kMAX];
  trackchi2      = new float[ kMAX ];
  muDR           = new float[ kMAX ];
  muDE           = new float[ kMAX ];
  trackd0      = new float[ kMAX ];
  trackz0      = new float[ kMAX ];

  //All calo jets
  minNumJets_     = 0;
  NobjJet         = 0;
  jetpt           = new float [ kjMAX ];
  jetphi          = new float [ kjMAX ];
  jeteta          = new float [ kjMAX ];
  jetet           = new float [ kjMAX ];
  jete            = new float [ kjMAX ];
  jetgenjetDeltaR = new float [ kjMAX ];

  // Jet IDs
  n90Hits_ = new int[kjMAX];
  fHad_ = new float[kjMAX];
  fEMF_ = new float[kjMAX];
  fHPD_ = new float[kjMAX];
  fRBX_ = new float[kjMAX];
  jetIDLoose_ = new bool[kjMAX];
  jetIDTight_ = new bool[kjMAX];
  for(int i = 0; i < kjMAX; i++) {
    jetIDLoose_[i] = false;
    jetIDTight_[i] = false;
  }

  // Jet shape
  jetEtWeightedSigmaPhi_ = new float[kjMAX];
  jetEtWeightedSigmaEta_ = new float[kjMAX];

  // Correction factors
  jscaleZSP       = new float [ kjMAX ];
  jscalel2        = new float [ kjMAX ];
  jscalel3        = new float [ kjMAX ];
  jscaleJPT       = new float [ kjMAX ];
  jscalel2l3      = new float [ kjMAX ];
  jscalel2l3JPT   = new float [ kjMAX ];
  jscalel4JW      = new float [ kjMAX ];
  for(int i = 0; i < kjMAX; i++) {
    jscaleZSP[i]      = 1.;
    jscalel2[i]       = 1.;
    jscalel3[i]       = 1.;
    jscaleJPT[i]      = 1.;
    jscalel2l3[i]     = 1.;
    jscalel2l3JPT[i]  = 1.;
    jscalel4JW[i]     = 1.;
  }
  jetieta_       = new int [ kjMAX ];
  jetiphi_       = new int [ kjMAX ];

  // Gen jets (matched to calo jets)
  genjetpt       = new float [ kjMAX ];
  genjetphi      = new float [ kjMAX ];
  genjeteta      = new float [ kjMAX ];
  genjetet       = new float [ kjMAX ];
  genjete        = new float [ kjMAX ];
  for(int i = 0; i < kjMAX; i++) {
    genjetpt[i]  = 0.;
    genjetphi[i] = 0.;
    genjeteta[i] = 0.;
    genjetet[i]  = 0.;
    genjete[i]   = 0.;
  }

  // Gen jet collection
  NobjGenJet        = 0;
  genjetcolpt       = new float [ kjMAX ];
  genjetcolphi      = new float [ kjMAX ];
  genjetcoleta      = new float [ kjMAX ];
  genjetcolet       = new float [ kjMAX ];
  genjetcole        = new float [ kjMAX ];
  genjetcoleme      = new float [ kjMAX ];
  genjetcolhade     = new float [ kjMAX ];
  genjetcolinve     = new float [ kjMAX ];
  genjetcolauxe     = new float [ kjMAX ];
  genjetcol_jet_idx = new int   [ kjMAX ];
  for(int i = 0; i < kjMAX; i++) {
    genjetcolpt[i]       = 0.;
    genjetcolphi[i]      = 0.;
    genjetcoleta[i]      = 0.;
    genjetcolet[i]       = 0.;
    genjetcole[i]        = 0.;
    genjetcoleme[i]      = 0.;
    genjetcolhade[i]     = 0.;
    genjetcolinve[i]     = 0.;
    genjetcolauxe[i]     = 0.;
    genjetcol_jet_idx[i] = -1;
  }
  // Gen jet particles
  NobjGenJetPart = 0;
  genjetparte              = new float [ kMAX ];
  genjetpartpt             = new float [ kMAX ];
  genjetparteta            = new float [ kMAX ];
  genjetpartphi            = new float [ kMAX ];
  genjetpartpdg            = new int [ kMAX ];
  genjetpart_genjetcolidx  = new int [ kMAX ];
  for(int i = 0; i < kMAX; ++i) {
    genjetparte[i]             = 0;
    genjetpartpt[i]            = 0;
    genjetparteta[i]           = 0;
    genjetpartphi[i]           = 0;
    genjetpartpdg[i]           = 0;
    genjetpart_genjetcolidx[i] = -1;
  }
    
  // Matched gen particles
  // Alogrithmic matching
  genpartpt_algo     = new float [ kjMAX ];
  genpartphi_algo    = new float [ kjMAX ];
  genparteta_algo    = new float [ kjMAX ];
  genpartet_algo     = new float [ kjMAX ];
  genparte_algo      = new float [ kjMAX ];
  genpartm_algo      = new float [ kjMAX ];
  genpartid_algo     = new int   [ kjMAX ];

  // Physical matching
  genpartpt_phys      = new float [ kjMAX ];
  genpartphi_phys     = new float [ kjMAX ];
  genparteta_phys     = new float [ kjMAX ];
  genpartet_phys      = new float [ kjMAX ];
  genparte_phys       = new float [ kjMAX ];
  genpartm_phys       = new float [ kjMAX ];
  genpartid_phys      = new int   [ kjMAX ];

  for(int i = 0; i < kjMAX; i++) {
    genpartpt_algo[i]     = 0.;
    genpartphi_algo[i]    = 0.;
    genparteta_algo[i]    = 0.;
    genpartet_algo[i]     = 0.;
    genparte_algo[i]      = 0.;
    genpartm_algo[i]      = 0.;
    genpartid_algo[i]     = 0;
    genpartpt_phys[i]      = 0.;
    genpartphi_phys[i]     = 0.;
    genparteta_phys[i]     = 0.;
    genpartet_phys[i]      = 0.;
    genparte_phys[i]       = 0.;
    genpartm_phys[i]       = 0.;
    genpartid_phys[i]      = 0;
  }

  //met
  mmet = 0;
  mphi = 0;
  msum = 0;

  // GenEventScale (pthat)
  genEvtScale = 0.;

  //EventWeight
  weight = 1.;
  xsec = 0;

  //ecal cells data
  NobjETowCal = 0;
  etowet      = new float [ kMAX ];
  etoweta     = new float [ kMAX ];
  etowphi     = new float [ kMAX ];
  etowe       = new float [ kMAX ];
  etowid_phi  = new int[ kMAX ];
  etowid_eta  = new int[ kMAX ];
  etowid      = new int[ kMAX ];
  etownum     = new int[ kMAX ];
  etow_towidx = new int[ kMAX ];
  etow_jetidx = new int[ kMAX ];

  // stable gen particles data
  NobjStableGenPart_   = 0;
  stableGenPartM_      = new float[ kMaxStableGenPart_ ];
  stableGenPartE_      = new float[ kMaxStableGenPart_ ];
  stableGenPartEt_     = new float[ kMaxStableGenPart_ ];
  stableGenPartP_      = new float[ kMaxStableGenPart_ ];
  stableGenPartPt_     = new float[ kMaxStableGenPart_ ];
  stableGenPartEta_    = new float[ kMaxStableGenPart_ ];
  stableGenPartPhi_    = new float[ kMaxStableGenPart_ ];
  stableGenPartPDGId_  = new int[ kMaxStableGenPart_ ];
  for(int i = 0; i < kMaxStableGenPart_; i++) {
    stableGenPartM_[i]      = 0.;
    stableGenPartE_[i]      = 0.;
    stableGenPartEt_[i]     = 0.;
    stableGenPartP_[i]      = 0.;
    stableGenPartPt_[i]     = 0.;
    stableGenPartEta_[i]    = 0.;
    stableGenPartPhi_[i]    = 0.;
    stableGenPartPDGId_[i]  = 0;
  }
} 



template <typename T> NJet<T>::~NJet() {
  delete [] towet;     
  delete [] toweta;    
  delete [] towphi;    
  delete [] towen;     
  delete [] towem;     
  delete [] towhd;     
  delete [] towoe;     
  delete [] towid_phi; 
  delete [] towid_eta; 
  delete [] towid;     
  delete [] tow_jetidx;
  delete [] numBadEcalCells_;
  delete [] numBadHcalCells_;
  delete [] numProblematicEcalCells_;
  delete [] numProblematicHcalCells_;
  delete [] numRecoveredEcalCells_;
  delete [] numRecoveredHcalCells_;

  delete [] trackpt;
  delete [] tracketa;
  delete [] trackphi;
  delete [] trackp;
  delete [] trackdr;
  delete [] tracketaout;
  delete [] trackphiout;
  delete [] trackdrout;
  delete [] trackemc1;
  delete [] trackemc3;
  delete [] trackemc5;
  delete [] trackhac1;
  delete [] trackhac3;
  delete [] trackhac5;
  delete [] tracktowid;    
  delete [] tracktowidphi; 
  delete [] tracktowideta; 
  delete [] track_jetidx;  
  delete [] trackid;
  delete [] tracknhits;    
  delete [] trackQualityL; 
  delete [] trackQualityT; 
  delete [] trackQualityHP;
  delete [] trackchi2;     
  delete [] muDR;          
  delete [] muDE;     
  delete [] trackd0;     
  delete [] trackz0;          

  delete [] jetpt;          
  delete [] jetphi;         
  delete [] jeteta;         
  delete [] jetet;          
  delete [] jete;        
  delete [] jetgenjetDeltaR;

  delete [] n90Hits_;
  delete [] fHad_;
  delete [] fEMF_;
  delete [] fHPD_;
  delete [] fRBX_;
  delete [] jetIDLoose_;
  delete [] jetIDTight_;
  
  delete [] jetEtWeightedSigmaPhi_;
  delete [] jetEtWeightedSigmaEta_;

  delete [] jscaleZSP;    
  delete [] jscalel2;     
  delete [] jscalel3;     
  delete [] jscaleJPT;    
  delete [] jscalel2l3;   
  delete [] jscalel2l3JPT;
  delete [] jscalel4JW;

  delete [] jetieta_;   
  delete [] jetiphi_;

  delete [] genjetpt; 
  delete [] genjetphi;
  delete [] genjeteta;
  delete [] genjetet; 
  delete [] genjete;  

  delete [] genjetcolpt;      
  delete [] genjetcolphi;     
  delete [] genjetcoleta;     
  delete [] genjetcolet;      
  delete [] genjetcole;       
  delete [] genjetcoleme;       
  delete [] genjetcolhade;       
  delete [] genjetcolinve;       
  delete [] genjetcolauxe;       
  delete [] genjetcol_jet_idx;  

  delete [] genjetparte;
  delete [] genjetpartpt;
  delete [] genjetparteta;
  delete [] genjetpartphi;
  delete [] genjetpartpdg;
  delete [] genjetpart_genjetcolidx;

  delete [] genpartpt_algo;
  delete [] genpartphi_algo;
  delete [] genparteta_algo;
  delete [] genpartet_algo;
  delete [] genparte_algo;
  delete [] genpartm_algo;
  delete [] genpartid_algo;

  delete [] genpartpt_phys;
  delete [] genpartphi_phys;
  delete [] genparteta_phys;
  delete [] genpartet_phys;
  delete [] genparte_phys;
  delete [] genpartm_phys;
  delete [] genpartid_phys;

  delete [] etowet;
  delete [] etoweta;
  delete [] etowphi;
  delete [] etowe;
  delete [] etowid_phi;
  delete [] etowid_eta;
  delete [] etowid;
  delete [] etownum;
  delete [] etow_towidx;
  delete [] etow_jetidx;

  delete [] stableGenPartM_;
  delete [] stableGenPartE_;
  delete [] stableGenPartEt_;
  delete [] stableGenPartP_;
  delete [] stableGenPartPt_;
  delete [] stableGenPartEta_;
  delete [] stableGenPartPhi_;
  delete [] stableGenPartPDGId_;
} 



template <typename T> void NJet<T>::setup(const edm::ParameterSet& cfg, TTree* CalibTree)
{
  // Read parameters
  minNumJets_         = cfg.getParameter<int>("NJet_MinNumJets");
  jets_               = cfg.getParameter<edm::InputTag>("NJet_Jets");
  jetIDs_             = cfg.getParameter<edm::InputTag>("NJet_JetIDs");
  partMatch_          = cfg.getParameter<edm::InputTag>("NJet_PartonMatch");
  genjets_            = cfg.getParameter<edm::InputTag>("NJet_GenJets");
  genparticles_       = cfg.getParameter<edm::InputTag>("NJet_GenParticles");
  met_                = cfg.getParameter<edm::InputTag>("NJet_MET");
  weight_             = (float)(cfg.getParameter<double> ("NJet_Weight"));
  weight_tag          = cfg.getParameter<edm::InputTag> ("NJet_Weight_Tag");
  recTracks_          = cfg.getParameter<edm::InputTag>("NJetRecTracks");
  recMuons_           = cfg.getParameter<edm::InputTag>("NJetRecMuons");
  conesize_           = cfg.getParameter<double>("NJetConeSize");
  zspJets_            = cfg.getParameter<edm::InputTag>("NJetZSPJets");
  writeGenJetPart_    = cfg.getParameter<bool>("WriteGenJetParticles");
  writeStableGenPart_ = cfg.getParameter<bool>("WriteStableGenParticles");
  beamSpot_           = cfg.getParameter<edm::InputTag>("BeamSpot");
  l2name_ = cfg.getParameter<std::string>("NJet_L2JetCorrector");
  l3name_ = cfg.getParameter<std::string>("NJet_L3JetCorrector");
  JPTname_ = cfg.getParameter<std::string>("NJet_JPTZSPCorrector");
  l2l3name_ = cfg.getParameter<std::string>("NJet_L2L3JetCorrector");
  l2l3l4JWname_ = cfg.getParameter<std::string>("NJet_L2L3L4JWJetCorrector");
  l2l3JPTname_ = cfg.getParameter<std::string>("NJet_L2L3JetCorrectorJPT");
  edm::ParameterSet parameters = cfg.getParameter<edm::ParameterSet>("TrackAssociatorParameters");
  parameters_.loadParameters( parameters );
  trackAssociator_.useDefaultPropagator();


  // Set up branches

  // Event info
  CalibTree->Branch("RunNumber",&runNumber_,"RunNumber/i");
  CalibTree->Branch("LumiBlockNumber",&luminosityBlockNumber_,"LumiBlockNumber/i");
  CalibTree->Branch("EventNumber",&eventNumber_,"EventNumber/i");

  CalibTree->Branch("HltPhysicsDelcared",&hltPhysicsDeclared_,"HltPhysicsDelcared/O");
  CalibTree->Branch("HltL1Jet6U",&hltL1Jet6U_,"HltL1Jet6U/O");
  CalibTree->Branch("HltDiJetAve15U",&hltDiJetAve15U_,"HltDiJetAve15U/O");
  CalibTree->Branch("HltDiJetAve30U",&hltDiJetAve30U_,"HltDiJetAve30U/O");
  CalibTree->Branch("HltDiJetAve50U",&hltDiJetAve50U_,"HltDiJetAve50U/O");
  CalibTree->Branch("HltDiJetAve70U",&hltDiJetAve70U_,"HltDiJetAve70U/O");
  CalibTree->Branch("HltDiJetAve100U",&hltDiJetAve100U_,"HltDiJetAve100U/O");
  CalibTree->Branch("HltDiJetAve140U",&hltDiJetAve140U_,"HltDiJetAve140U/O");

  CalibTree->Branch("VtxNTracks",&vtxNTracks_,"VtxNTracks/I");
  CalibTree->Branch("VtxPosX",&vtxPosX_,"VtxPosX/F");
  CalibTree->Branch("VtxPosY",&vtxPosY_,"VtxPosY/F");
  CalibTree->Branch("VtxPosZ",&vtxPosZ_,"VtxPosZ/F");
  CalibTree->Branch("VtxNormalizedChi2",&vtxNormalizedChi2_,"VtxNormalizedChi2/F");
  CalibTree->Branch("VtxNDof",&vtxNDof_,"VtxNDof/F");
  CalibTree->Branch("VtxIsFake",&vtxIsFake_,"VtxIsFake/O");

  // CaloTower branches for all jets
  CalibTree->Branch( "NobjTow",&NobjTow,"NobjTow/I"             );
  CalibTree->Branch( "TowId",     towid,      "TowId[NobjTow]/I"    );
  CalibTree->Branch( "TowId_phi", towid_phi,  "TowId_phi[NobjTow]/I");
  CalibTree->Branch( "TowId_eta", towid_eta,  "TowId_eta[NobjTow]/I");
  CalibTree->Branch( "TowEt",     towet,      "TowEt[NobjTow]/F"    );
  CalibTree->Branch( "TowEta",    toweta,     "TowEta[NobjTow]/F"   );
  CalibTree->Branch( "TowPhi",    towphi,     "TowPhi[NobjTow]/F"   );
  CalibTree->Branch( "TowE",      towen,      "TowE[NobjTow]/F"     );
  CalibTree->Branch( "TowEm",     towem,      "TowEm[NobjTow]/F"    );
  CalibTree->Branch( "TowHad",    towhd,      "TowHad[NobjTow]/F"   );
  CalibTree->Branch( "TowOE",     towoe,      "TowOE[NobjTow]/F"    );
  CalibTree->Branch( "Tow_jetidx",tow_jetidx, "Tow_jetidx[NobjTow]/I");
  CalibTree->Branch( "TowNumBadEcalCells",numBadEcalCells_,"TowNumBadEcalCells[NobjTow]/i");
  CalibTree->Branch( "TowNumBadHcalCells",numBadHcalCells_,"TowNumBadHcalCells[NobjTow]/i");
  CalibTree->Branch( "TowNumProblematicEcalCells",numProblematicEcalCells_,"TowNumProblematicEcalCells[NobjTow]/i");
  CalibTree->Branch( "TowNumProblematicHcalCells",numProblematicHcalCells_,"TowNumProblematicHcalCells[NobjTow]/i");
  CalibTree->Branch( "TowNumRecoveredEcalCells",numRecoveredEcalCells_,"TowNumRecoveredEcalCells[NobjTow]/i");
  CalibTree->Branch( "TowNumRecoveredHcalCells",numRecoveredHcalCells_,"TowNumRecoveredHcalCells[NobjTow]/i");

  // track branchesw
   CalibTree->Branch( "NobjTrack",  &NobjTrack, "NobjTrack/I"             );
   CalibTree->Branch( "TrackTowId", tracktowid, "TrackTowId[NobjTrack]/I" );
   CalibTree->Branch( "TrackTowIdPhi", tracktowidphi, "TrackTowIdPhi[NobjTrack]/I" );
   CalibTree->Branch( "TrackTowIdEta", tracktowideta, "TrackTowIdEta[NobjTrack]/I" );
   CalibTree->Branch( "TrackId",    trackid,    "TrackId[NobjTrack]/I"    );
   CalibTree->Branch( "TrackNHits", tracknhits, "TrackNHits[NobjTrack]/I" );
   CalibTree->Branch( "TrackQualityL",trackQualityL,"TrackQualityL[NobjTrack]/O");
   CalibTree->Branch( "TrackQualityT",trackQualityT,"TrackQualityT[NobjTrack]/O");
   CalibTree->Branch( "TrackQualityHP",trackQualityHP,"TrackQualityHP[NobjTrack]/O");
   CalibTree->Branch( "TrackChi2",  trackchi2,  "TrackChi2[NobjTrack]/F"  );
   CalibTree->Branch( "TrackPt",    trackpt,    "TrackPt[NobjTrack]/F"    );
   CalibTree->Branch( "TrackEta",   tracketa,   "TrackEta[NobjTrack]/F"   );
   CalibTree->Branch( "TrackPhi",   trackphi,   "TrackPhi[NobjTrack]/F"   );
   CalibTree->Branch( "TrackP" ,    trackp,     "TrackP[NobjTrack]/F"     );
   CalibTree->Branch( "TrackDR" ,   trackdr,    "TrackDR[NobjTrack]/F"    );
   CalibTree->Branch( "TrackPhiOut",trackphiout,"TrackPhiout[NobjTrack]/F");
   CalibTree->Branch( "TrackEtaOut",tracketaout,"TrackEtaout[NobjTrack]/F");
   CalibTree->Branch( "TrackDROut", trackdrout, "TrackDRout[NobjTrack]/F" );
   CalibTree->Branch( "TrackEMC1",  trackemc1,  "TrackEMC1[NobjTrack]/F"  );
   CalibTree->Branch( "TrackEMC3",  trackemc3,  "TrackEMC3[NobjTrack]/F"  );
   CalibTree->Branch( "TrackEMC5",  trackemc5,  "TrackEMC5[NobjTrack]/F"  );
   CalibTree->Branch( "TrackHAC1",  trackhac1,  "TrackHAC1[NobjTrack]/F"  );
   CalibTree->Branch( "TrackHAC3",  trackhac3,  "TrackHAC3[NobjTrack]/F"  );
   CalibTree->Branch( "TrackHAC5",  trackhac5,  "TrackHAC5[NobjTrack]/F"  );
   CalibTree->Branch( "Track_jetidx",track_jetidx, "Track_jetidx[NobjTrack]/I");
   CalibTree->Branch( "MuDR", muDR,  "MuDR[NobjTrack]/F"  );
   CalibTree->Branch( "MuDE", muDE,  "MuDE[NobjTrack]/F"  );
   CalibTree->Branch( "TrackD0",  trackd0,  "TrackD0[NobjTrack]/F"  );
   CalibTree->Branch( "TrackZ0",  trackz0,  "TrackZ0[NobjTrack]/F"  );

  //All calo jets
  CalibTree->Branch( "NobjJet",            &NobjJet,         "NobjJet/I"             );
  CalibTree->Branch( "JetPt",               jetpt,           "JetPt[NobjJet]/F" );
  CalibTree->Branch( "JetPhi",              jetphi,          "JetPhi[NobjJet]/F");
  CalibTree->Branch( "JetEta",              jeteta,          "JetEta[NobjJet]/F");
  CalibTree->Branch( "JetEt",               jetet,           "JetEt[NobjJet]/F" );
  CalibTree->Branch( "JetE",                jete,            "JetE[NobjJet]/F"  );
  CalibTree->Branch( "JetN90Hits",n90Hits_,"JetN90Hits[NobjJet]/I");
  CalibTree->Branch( "JetHad",fHad_,"JetHad[NobjJet]/F");  
  CalibTree->Branch( "JetEMF",fEMF_,"JetEMF[NobjJet]/F");  
  CalibTree->Branch( "JetFHPD",fHPD_,"JetFHPD[NobjJet]/F");
  CalibTree->Branch( "JetFRBX",fRBX_,"JetFRBX[NobjJet]/F");
  CalibTree->Branch( "JetIDLoose",jetIDLoose_,"JetIDLoose[NobjJet]/O");
  CalibTree->Branch( "JetIDTight",jetIDTight_,"JetIDTight[NobjJet]/O");
  CalibTree->Branch( "JetEtWeightedSigmaPhi",jetEtWeightedSigmaPhi_,"JetEtWeightedSigmaPhi[NobjJet]/F" );
  CalibTree->Branch( "JetEtWeightedSigmaEta",jetEtWeightedSigmaEta_,"JetEtWeightedSigmaEta[NobjJet]/F" );
  CalibTree->Branch( "JetCorrZSP",          jscaleZSP,       "JetCorrZSP[NobjJet]/F" );
  CalibTree->Branch( "JetCorrL2",           jscalel2,        "JetCorrL2[NobjJet]/F" );
  CalibTree->Branch( "JetCorrL3",           jscalel3,        "JetCorrL3[NobjJet]/F" );
  CalibTree->Branch( "JetCorrJPT",          jscaleJPT,       "JetCorrJPT[NobjJet]/F" );
  CalibTree->Branch( "JetCorrL2L3",         jscalel2l3,      "JetCorrL2L3[NobjJet]/F" );
  CalibTree->Branch( "JetCorrL2L3JPT",      jscalel2l3JPT,   "JetCorrL2L3JPT[NobjJet]/F" );
  CalibTree->Branch( "JetCorrL4JW",         jscalel4JW,      "JetCorrL4JW[NobjJet]/F" );
  CalibTree->Branch( "JetIEta",jetieta_,"JetIEta[NobjJet]/I");
  CalibTree->Branch( "JetIPhi",jetiphi_,"JetIPhi[NobjJet]/I");

  // Gen jets (matched to calo jets)
  CalibTree->Branch( "JetGenJetDeltaR",     jetgenjetDeltaR, "JetGenJetDeltaR[NobjJet]/F"  );
  CalibTree->Branch( "GenJetPt",            genjetpt,       "GenJetPt[NobjJet]/F" );
  CalibTree->Branch( "GenJetPhi",           genjetphi,      "GenJetPhi[NobjJet]/F");
  CalibTree->Branch( "GenJetEta",           genjeteta,      "GenJetEta[NobjJet]/F");
  CalibTree->Branch( "GenJetEt",            genjetet,       "GenJetEt[NobjJet]/F" );
  CalibTree->Branch( "GenJetE",             genjete,        "GenJetE[NobjJet]/F"  );
    
  // Gen jet collection
  CalibTree->Branch( "NobjGenJet",     &NobjGenJet,        "NobjGenJet/I"                 );
  CalibTree->Branch( "GenJetColPt",     genjetcolpt,       "GenJetColPt[NobjGenJet]/F"    );
  CalibTree->Branch( "GenJetColPhi",    genjetcolphi,      "GenJetColPhi[NobjGenJet]/F"   );
  CalibTree->Branch( "GenJetColEta",    genjetcoleta,      "GenJetColEta[NobjGenJet]/F"   );
  CalibTree->Branch( "GenJetColEt",     genjetcolet,       "GenJetColEt[NobjGenJet]/F"    );
  CalibTree->Branch( "GenJetColE",      genjetcole,        "GenJetColE[NobjGenJet]/F"     );
  CalibTree->Branch( "GenJetColEmE",    genjetcoleme,      "GenJetColEmE[NobjGenJet]/F"     );
  CalibTree->Branch( "GenJetColHadE",   genjetcolhade,     "GenJetColHadE[NobjGenJet]/F"     );
  CalibTree->Branch( "GenJetColInvE",   genjetcolinve,     "GenJetColInvE[NobjGenJet]/F"     );
  CalibTree->Branch( "GenJetColAuxE",   genjetcolauxe,     "GenJetColAuxE[NobjGenJet]/F"     );
  CalibTree->Branch( "GenJetColJetIdx", genjetcol_jet_idx, "GenJetColJetIdx[NobjGenJet]/I");
  // Gen Jet constituents(particles)
  if(writeGenJetPart_) {
    CalibTree->Branch("NobjGenJetPart",&NobjGenJetPart,"NobjGenJetPart/I");
    CalibTree->Branch("GenJetPartE",genjetparte,"GenJetPartE[NobjGenJetPart]/F");
    CalibTree->Branch("GenJetPartPt",genjetpartpt,"GenJetPartPt[NobjGenJetPart]/F");
    CalibTree->Branch("GenJetPartEta",genjetparteta,"GenJetPartEta[NobjGenJetPart]/F");
    CalibTree->Branch("GenJetPartPhi",genjetpartphi,"GenJetPartPhi[NobjGenJetPart]/F"); 
    CalibTree->Branch("GenJetPartPDG",genjetpartpdg,"GenJetPartPDG[NobjGenJetPart]/I"); 
    CalibTree->Branch("GenJetPartGenJetColIdx",genjetpart_genjetcolidx,"GenJetPartGenJetColIdx[NobjGenJetPart]/I"); 
  }
  // Matched gen particles
  // Alogrithmic matching
  // GenPart_algo branches        );
  CalibTree->Branch( "GenPartPt_algo", genpartpt_algo, "GenPartPt_algo[NobjJet]/F" );
  CalibTree->Branch( "GenPartPhi_algo",genpartphi_algo,"GenPartPhi_algo[NobjJet]/F");
  CalibTree->Branch( "GenPartEta_algo",genparteta_algo,"GenPartEta_algo[NobjJet]/F");
  CalibTree->Branch( "GenPartEt_algo", genpartet_algo, "GenPartEt_algo[NobjJet]/F" );
  CalibTree->Branch( "GenPartE_algo",  genparte_algo,  "GenPartE_algo[NobjJet]/F"  );
  CalibTree->Branch( "GenPartM_algo",  genpartm_algo,  "GenPartM_algo[NobjJet]/F"  );
  CalibTree->Branch( "GenPartId_algo", genpartid_algo, "GenPartId_algo[NobjJet]/I" );
  // Physical matching
  // GenPart_phys branches        );
  CalibTree->Branch( "GenPartPt_phys", genpartpt_phys, "GenPartPt_phys[NobjJet]/F" );
  CalibTree->Branch( "GenPartPhi_phys",genpartphi_phys,"GenPartPhi_phys[NobjJet]/F");
  CalibTree->Branch( "GenPartEta_phys",genparteta_phys,"GenPartEta_phys[NobjJet]/F");
  CalibTree->Branch( "GenPartEt_phys", genpartet_phys, "GenPartEt_phys[NobjJet]/F" );
  CalibTree->Branch( "GenPartE_phys",  genparte_phys,  "GenPartE_phys[NobjJet]/F"  );
  CalibTree->Branch( "GenPartM_phys",  genpartm_phys,  "GenPartM_phys[NobjJet]/F"  );
  CalibTree->Branch( "GenPartId_phys", genpartid_phys, "GenPartId_phys[NobjJet]/I" );

  // GenEventScale (pthat)
  CalibTree->Branch( "GenEvtScale",&genEvtScale,"GenEvtScale/F");
  
  //met
  CalibTree->Branch( "Met",   &mmet,"Met/F"   );
  CalibTree->Branch( "MetPhi",&mphi,"MetPhi/F");
  CalibTree->Branch( "MetSum",&msum,"MetSum/F");

  //EventWeight
  CalibTree->Branch( "Weight",&weight,"Weight/F"   );
  //CrossSection
  CalibTree->Branch( "CrossSection",&xsec,"CrossSection/F"   );

  // stable gen particles data
  if( writeStableGenPart_ ) {
    CalibTree->Branch("NobjStableGenPart",&NobjStableGenPart_, "NobjStableGenPart/I"                    );
    CalibTree->Branch("StableGenPartM",    stableGenPartM_,    "StableGenPartM[NobjStableGenPart]/F"    ); 
    CalibTree->Branch("StableGenPartE",    stableGenPartE_,    "StableGenPartE[NobjStableGenPart]/F"    ); 
    CalibTree->Branch("StableGenPartEt",   stableGenPartEt_,   "StableGenPartEt[NobjStableGenPart]/F"   ); 
    CalibTree->Branch("StableGenPartP",    stableGenPartP_,    "StableGenPartP[NobjStableGenPart]/F"    ); 
    CalibTree->Branch("StableGenPartPt",   stableGenPartPt_,   "StableGenPartPt[NobjStableGenPart]/F"   ); 
    CalibTree->Branch("StableGenPartEta",  stableGenPartEta_,  "StableGenPartEta[NobjStableGenPart]/F"  ); 
    CalibTree->Branch("StableGenPartPhi",  stableGenPartPhi_,  "StableGenPartPhi[NobjStableGenPart]/F"  ); 
    CalibTree->Branch("StableGenPartPDGId",stableGenPartPDGId_,"StableGenPartPDGId[NobjStableGenPart]/I"); 
  }
}


template <typename T> void NJet<T>::analyze(const edm::Event& evt, const edm::EventSetup& setup, TTree* CalibTree)
{
  // Event
  edm::EventAuxiliary aux = evt.eventAuxiliary();
  runNumber_             = aux.run();
  luminosityBlockNumber_ = aux.luminosityBlock();
  eventNumber_           = aux.event();

  // HLT trigger: "Physics declared" bit
  edm::Handle<L1GlobalTriggerReadoutRecord> gtrr_handle;
  evt.getByLabel("gtDigis", gtrr_handle);
  L1GlobalTriggerReadoutRecord const* gtrr = gtrr_handle.product();
 
  L1GtFdlWord fdlWord = gtrr->gtFdlWord();
  if( fdlWord.physicsDeclared() == 1 ) hltPhysicsDeclared_ = true;


  // HLT Trigger
  edm::Handle<edm::TriggerResults> triggerResults;

  if( evt.getByLabel(edm::InputTag("TriggerResults::HLT"),triggerResults) ) {
    const edm::TriggerNames & trigNames = evt.triggerNames(*triggerResults);
    size_t id = 0;

    hltL1Jet6U_ = false;
/*     id = trigNames.triggerIndex("HLT_L1Jet6U"); */
/*     if( id != trigNames.size() ) */
/*       if( triggerResults->accept(id) ) hltL1Jet6U_ = true; */
    
    hltDiJetAve15U_ = false;
    id = trigNames.triggerIndex("HLT_DiJetAve15U_v3");
    if( id != trigNames.size() )
      if( triggerResults->accept(id) ) hltDiJetAve15U_ = true;
    
    hltDiJetAve30U_ = false;
    id = trigNames.triggerIndex("HLT_DiJetAve30U_v3");
    if( id != trigNames.size()  )
      if( triggerResults->accept(id) ) hltDiJetAve30U_ = true;

    hltDiJetAve50U_ = false;
    id = trigNames.triggerIndex("HLT_DiJetAve50U_v3");
    if( id != trigNames.size()  )
      if( triggerResults->accept(id) ) hltDiJetAve50U_ = true;

    hltDiJetAve70U_ = false;
    id = trigNames.triggerIndex("HLT_DiJetAve70U_v3");
    if( id != trigNames.size()  )
      if( triggerResults->accept(id) ) hltDiJetAve70U_ = true;
    
    hltDiJetAve100U_ = false;
    id = trigNames.triggerIndex("HLT_DiJetAve100U_v3");
    if( id != trigNames.size()  )
      if( triggerResults->accept(id) ) hltDiJetAve100U_ = true;

    hltDiJetAve140U_ = false;
    id = trigNames.triggerIndex("HLT_DiJetAve140U_v3");
    if( id != trigNames.size()  )
      if( triggerResults->accept(id) ) hltDiJetAve140U_ = true;
  }


  // Vertex info
  edm::Handle<reco::VertexCollection> offlinePrimaryVertices;
  evt.getByLabel("offlinePrimaryVertices",offlinePrimaryVertices);
  if( offlinePrimaryVertices->size() ) {
    const reco::Vertex *vtx = &(offlinePrimaryVertices->front());
    vtxNTracks_ = vtx->tracksSize();
    vtxPosX_ = vtx->x();
    vtxPosY_ = vtx->y();
    vtxPosZ_ = vtx->z();
    vtxNormalizedChi2_ = vtx->normalizedChi2();
    vtxNDof_ = vtx->ndof();
    vtxIsFake_ = vtx->isFake();
  } else {
    vtxNTracks_ = 0;
    vtxPosX_ = -10000.;
    vtxPosY_ = -10000.;
    vtxPosZ_ = -10000.;
    vtxNormalizedChi2_ = 10000.;
    vtxNDof_ = 0;
    vtxIsFake_ = true;
  }

  //BeamSpot
  edm::Handle<reco::BeamSpot> beamSpotHandle;
  evt.getByLabel(beamSpot_,beamSpotHandle);
  reco::BeamSpot myBeamSpot = *beamSpotHandle;
  
  const math::XYZPointD & myPosition=myBeamSpot.position();

  edm::Handle< edm::View<T> > pJets;
  evt.getByLabel(jets_, pJets);

  edm::Handle<reco::JetIDValueMap> pJetIDMap;
  evt.getByLabel(jetIDs_,pJetIDMap);

  edm::Handle<CaloMETCollection> recmets;
  evt.getByLabel(met_, recmets);

  edm::Handle<reco::GenJetCollection> genJets;
  evt.getByLabel(genjets_,genJets);
  reco::GenJetCollection::const_iterator genJet;

  edm::Handle<reco::GenParticleCollection> genParticles;
  evt.getByLabel(genparticles_,genParticles);
  reco::GenParticleCollection::const_iterator genParticle;
  
  edm::Handle<JetMatchedPartonsCollection> matchedParticleMap;
  evt.getByLabel(partMatch_, matchedParticleMap); 


  // get calo jet after zsp collection
  edm::Handle<CaloJetCollection> zspJets;
  evt.getByLabel(zspJets_, zspJets);
  reco::CaloJetCollection::const_iterator zspJet;

  // Get pthat
  edm::Handle<GenEventInfoProduct> genInfoHandle;
  evt.getByLabel("generator", genInfoHandle); 
  weight = weight_;
  if( genInfoHandle.isValid() ) {
    genEvtScale = static_cast<float>(genInfoHandle->binningValues()[0]); 
    if(weight_ <= 0)
      {
	weight = static_cast<float>(genInfoHandle->weight());
      }
  }
  
  edm::Handle<GenRunInfoProduct> genInfoProduct;
  evt.getRun().getByLabel("generator", genInfoProduct );
  if( genInfoHandle.isValid() ) {
    xsec = genInfoProduct->crossSection();
  } else {
    xsec = 0;
  }

  
  //get tower geometry
  edm::ESHandle<CaloGeometry> geometry;
  setup.get<CaloGeometryRecord>().get(geometry);
  const CaloSubdetectorGeometry* towerGeometry = geometry->getSubdetectorGeometry(DetId::Calo, CaloTowerDetId::SubdetId);
  
  //std::string l2l3PFlowname = "L2L3JetCorrectorSC5PF";

  const JetCorrector* correctorL2   = JetCorrector::getJetCorrector (l2name_,setup);   //Define the jet corrector
  const JetCorrector* correctorL3   = JetCorrector::getJetCorrector (l3name_,setup);   //Define the jet corrector
  const JetCorrector* correctorL2L3  = JetCorrector::getJetCorrector (l2l3name_, setup); //Define the jet corrector
  const JetCorrector* correctorL2L3L4JW  = JetCorrector::getJetCorrector (l2l3l4JWname_, setup); //Define the jet corrector

  NobjTow=0;
  NobjETowCal = 0;
  NobjJet = pJets->size();
  if( NobjJet >= minNumJets_ ) {
    if(NobjJet > kjMAX) NobjJet = kjMAX;
    //unsigned int towno = 0;   // Calo tower counting index
    unsigned int icell = 0;   // Ecal cell counting index

    // Loop over calo jets
    for (unsigned int jtno = 0; (int)jtno<NobjJet; ++jtno) {
      // Write jet kinematics
      jetpt[  jtno ] = (*pJets)[jtno].pt();
      jetphi[ jtno ] = (*pJets)[jtno].phi();
      jeteta[ jtno ] = (*pJets)[jtno].eta();
      jetet[  jtno ] = (*pJets)[jtno].et();
      jete[   jtno ] = (*pJets)[jtno].energy();

      // JetID
      if( pJetIDMap.isValid() ) { // For calo and JPT jets
	reco::JetID pJetID = (*pJetIDMap)[pJets->refAt(jtno)];
	jetIDLoose_[jtno] = looseJetID((*pJets)[jtno],pJetID);
	jetIDTight_[jtno] = tightJetID((*pJets)[jtno],pJetID);
	n90Hits_[jtno] = static_cast<int>(pJetID.n90Hits);
	fHPD_[jtno] = pJetID.fHPD;
	fRBX_[jtno] = pJetID.fRBX;
      } else { // For PF jets
 	jetIDTight_[jtno] = tightJetID((*pJets)[jtno]);
	jetIDLoose_[jtno] = looseJetID((*pJets)[jtno]);
      }
      // L2L3 correction
      jscalel2[jtno]   = correctorL2  ->correction( (*pJets)[jtno].p4());  //calculate the correction
      jscalel3[jtno]   = correctorL3  ->correction( jscalel2[jtno] * (*pJets)[jtno].p4());  //calculate the correction
      jscalel2l3[jtno] = correctorL2L3->correction( (*pJets)[jtno].p4());  //calculate the correction
      jscalel4JW[jtno] = correctorL2L3L4JW->correction((*pJets)[jtno]) / jscalel2l3[jtno];  //calculate the correction

      // JPT correction (uses ZSP corrected jets)
//       for(zspJet = zspJets->begin(); zspJet != zspJets->end(); ++zspJet) {
// 	if( deltaR(zspJet->eta(),zspJet->phi(),(*pJets)[jtno].eta() , (*pJets)[jtno].phi()) < 0.01)//no change in R by ZSP or JPT
//  	  {
//  	    jscaleZSP[jtno]     = zspJet->et()/ (*pJets)[jtno].et();
//  	    jscaleJPT[jtno]     = correctorJPT ->correction((*zspJet),evt,setup);  //calculate the correction
//  	    jscalel2l3JPT[jtno] = correctorL2L3JPT  ->correction(zspJet->p4() * jscaleJPT[jtno] );  //calculate the correction
//  	  }
//       }

      //jet position 
      // only eta and phi coordinate of poI is used so it's fine to 
      // initialize poI with the jet momentum
      const GlobalPoint poI((*pJets)[jtno].px(),(*pJets)[jtno].py(),(*pJets)[jtno].pz());
      CaloTowerDetId towerId = towerGeometry->getClosestCell(poI);    
      jetieta_[jtno] = towerId.ieta();
      jetiphi_[jtno] = towerId.iphi();


      if( genJets.isValid() ) {
	// Find closest genjet (DeltaR) to the current calo jet
	double closestDeltaR    = 1000;
	int    closestGenJetIdx = -1;
	for(size_t gjidx = 0; gjidx < genJets->size(); gjidx++) {
	  double deltaRtmp  = deltaR( (*genJets)[gjidx].eta(), (*genJets)[gjidx].phi(),
				      (*pJets)[jtno].eta(),    (*pJets)[jtno].phi()     );
	 
	  if( deltaRtmp < closestDeltaR ) {
	    closestDeltaR    = deltaRtmp;
	    closestGenJetIdx = gjidx;
	  }
	}
	jetgenjetDeltaR[ jtno ] = closestDeltaR;
       
	if( closestGenJetIdx > -1 ) {
	  genjetpt[  jtno ] = (*genJets)[closestGenJetIdx].pt();
	  genjetphi[ jtno ] = (*genJets)[closestGenJetIdx].phi();
	  genjeteta[ jtno ] = (*genJets)[closestGenJetIdx].eta();
	  genjetet[  jtno ] = (*genJets)[closestGenJetIdx].et();
	  genjete[   jtno ] = (*genJets)[closestGenJetIdx].energy();
	} else {
	  genjetpt[  jtno ] = 0.;
	  genjetphi[ jtno ] = 0.;
	  genjeteta[ jtno ] = 0.;
	  genjetet[  jtno ] = 0.;
	  genjete[   jtno ] = 0.;
	}
      }

      jetEtWeightedSigmaPhi_[jtno] = (*pJets)[jtno].phiphiMoment() > 0 ? sqrt((*pJets)[jtno].phiphiMoment()) : 0;
      jetEtWeightedSigmaEta_[jtno] = (*pJets)[jtno].etaetaMoment() > 0 ? sqrt((*pJets)[jtno].etaetaMoment()) : 0;

      fillExtra(*pJets, jtno);
      //// GenParticle Matching ALGO and PHYSICS
      if( matchedParticleMap.isValid() ) {
	double gppt_algo = 0;
	double gpphi_algo = 0;
	double gpeta_algo = 0;
	double gpet_algo = 0;
	double gpe_algo = 0;
	double gpm_algo = 0;
	int gpid_algo = 0;
      
	double gppt_phys = 0;
	double gpphi_phys = 0;
	double gpeta_phys = 0;
	double gpet_phys = 0;
	double gpe_phys = 0;
	double gpm_phys = 0;
	int gpid_phys = 0;
      
	const MatchedPartons aMatch = (*matchedParticleMap)[edm::RefToBase<reco::Jet>(pJets->refAt(jtno))];
	
	GenParticleRef theAlgoDef = aMatch.algoDefinitionParton();
	if (theAlgoDef.isNonnull()) {
	  
	  gppt_algo = theAlgoDef->pt();
	  gpphi_algo = theAlgoDef->phi();
	  gpeta_algo = theAlgoDef->eta();
	  gpet_algo = theAlgoDef->et();
	  gpe_algo = theAlgoDef->energy();
	  gpm_algo = theAlgoDef->mass();
	  gpid_algo = theAlgoDef->pdgId();
	}
	
	GenParticleRef thePhyDef = aMatch.physicsDefinitionParton();
	if (thePhyDef.isNonnull()) {
	  //          cout<<"matched parton PhysDef:        "<< thePhyDef->et() <<" "<< thePhyDef->eta()<<" "<< thePhyDef->phi()<<endl;
	  gppt_phys = thePhyDef->pt();
	  gpphi_phys = thePhyDef->phi();
	  gpeta_phys = thePhyDef->eta();
	  gpet_phys = thePhyDef->et();
	  gpe_phys = thePhyDef->energy();
	  gpm_phys = thePhyDef->mass();
	  gpid_phys = thePhyDef->pdgId();
	  
	}
	
	genpartpt_algo[  jtno ] = gppt_algo;
	genpartphi_algo[ jtno ] = gpphi_algo ;
	genparteta_algo[ jtno ] = gpeta_algo ;
	genpartet_algo[  jtno ] = gpet_algo ;
	genparte_algo[   jtno ] = gpe_algo ;
	genpartm_algo[   jtno ] = gpm_algo ;
	genpartid_algo[  jtno ] = gpid_algo ;
      
	
	genpartpt_phys[  jtno ] = gppt_phys;
	genpartphi_phys[ jtno ] = gpphi_phys ;
	genparteta_phys[ jtno ] = gpeta_phys ;
	genpartet_phys[  jtno ] = gpet_phys ;
	genparte_phys[   jtno ] = gpe_phys ;
	genpartm_phys[   jtno ] = gpm_phys ;
	genpartid_phys[  jtno ] = gpid_phys ;
	
      } // End of loop over calo jets
    }
    NobjETowCal = icell;


    typedef CaloMETCollection::const_iterator cmiter;
    for( cmiter i=recmets->begin(); i!=recmets->end(); i++) {
      mmet = i->pt();
      mphi = i->phi();
      msum = i->sumEt();
      break;
    }

    //Tracks
    edm::Handle<reco::TrackCollection> tracks;
    evt.getByLabel(recTracks_,tracks);

    //Muons
    edm::Handle<reco::MuonCollection> muons;
    //edm::Handle<reco::TrackCollection> muons;
    evt.getByLabel(recMuons_,muons);

    // see here for detailed track cluster matching and jet track association
    //   -> CMSSW/TrackingTools/TrackAssociator/test/CaloMatchingExample.cc

    int iTrack = 0;
    for(reco::TrackCollection::const_iterator it = tracks->begin(); it != tracks->end(); ++it) {
      // skip low Pt tracks
      if (it->pt() < 1) continue;
      TrackDetMatchInfo info = trackAssociator_.associate(evt, setup, *it, parameters_);

      for (unsigned int jtno = 0; (int)jtno<NobjJet; ++jtno)
	{
	  bool saveTrack = false;
	  double dRin   = deltaR(*it,(*pJets)[jtno]);
	  double outeta = info.trkGlobPosAtEcal.eta();
	  double outphi = info.trkGlobPosAtEcal.phi();
	  double dRout  = deltaR((*pJets)[jtno].eta(),(*pJets)[jtno].phi(),outeta,outphi);
	  if (dRin < conesize_  || dRout < conesize_){
	    saveTrack=true;
	  }
	  if (saveTrack){
	    trackpt[iTrack]     = it->pt();
	    tracketa[iTrack]    = it->eta();
	    trackphi[iTrack]    = it->phi();
	    trackp[iTrack]      = it->p();
	    trackdr[iTrack]     = dRin;
	    trackdrout[iTrack]  = dRout;
	    tracketaout[iTrack] = outeta;
	    trackphiout[iTrack] = outphi;
	    trackemc1[iTrack]   = info.nXnEnergy(TrackDetMatchInfo::EcalRecHits, 0);
	    trackemc3[iTrack]   = info.nXnEnergy(TrackDetMatchInfo::EcalRecHits, 1);
	    trackemc5[iTrack]   = info.nXnEnergy(TrackDetMatchInfo::EcalRecHits, 2);
	    trackhac1[iTrack]   = info.nXnEnergy(TrackDetMatchInfo::HcalRecHits, 0);
	    trackhac3[iTrack]   = info.nXnEnergy(TrackDetMatchInfo::HcalRecHits, 1);
	    trackhac5[iTrack]   = info.nXnEnergy(TrackDetMatchInfo::HcalRecHits, 2);
	    DetId centerId = info.findMaxDeposition(TrackDetMatchInfo::HcalRecHits);
	    HcalDetId HcalCenterId(centerId);
	    tracktowidphi[iTrack] = HcalCenterId.iphi();
	    tracktowideta[iTrack] = HcalCenterId.ieta();
	    tracktowid[iTrack]    = centerId.rawId();
	    track_jetidx[iTrack]  = jtno;
	    trackchi2[iTrack]     = it->normalizedChi2();
	    tracknhits[iTrack]    = it->numberOfValidHits();
	    trackd0[iTrack]       = it->dxy(myPosition);
	    trackz0[iTrack]       = it->dz(myPosition);

   
	    //if(it->quality(reco::TrackBase::undefQuality)) trackQuality[iTrack] = -1;
	    if(it->quality(reco::TrackBase::loose))  trackQualityL[iTrack] = true;
	    else  trackQualityL[iTrack] = false;
	    if(it->quality(reco::TrackBase::tight))  trackQualityT[iTrack] = true;
	    else  trackQualityT[iTrack] = false;
	    if(it->quality(reco::TrackBase::highPurity)) trackQualityHP[iTrack] = true;
	    else  trackQualityHP[iTrack] = false;
	    //if(it->quality(reco::TrackBase::confirmed))  trackQuality[iTrack] = 3;
	    //if(it->quality(reco::TrackBase::goodIterative))  trackQuality[iTrack] = 4;
	    //if(it->quality(reco::TrackBase::qualitySize))  trackQuality[iTrack] = 5;
 
	    //Match track with muons
	    muDR[iTrack] = -1;
	    muDE[iTrack] = -1;
	    bool muonMatch = false;
	    for(reco::MuonCollection::const_iterator im = muons->begin(); im != muons->end(); ++im) {
	      //for(reco::TrackCollection::const_iterator im = muons->begin(); im != muons->end(); ++im) {
	      if(muon::isGoodMuon(*im, muon::AllGlobalMuons) && muon::isGoodMuon(*im, muon::TMLastStationLoose)) continue;
	      double dRm = deltaR(*im,*it);
	      double dE = fabs( (im->pt()-it->pt())/it->pt() );
	      muDR[iTrack] = dRm;
	      muDE[iTrack] = dE;
	      if (dRm<0.1 && dE < 0.2) muonMatch = true;
	    }
	    if (muonMatch) {
	      trackid[iTrack] = 13;
	    } else {
	      trackid[iTrack] = 0;
	    }
	    ++iTrack;
	  }
	}
    }
    NobjTrack=iTrack;



    /////////// Write genjet collection ///////////////////

    if( genJets.isValid() ) {
      // Loop over genjets
      NobjGenJet = genJets->size();
      int gjpidx = 0;
      if(NobjGenJet > kjMAX) NobjGenJet = kjMAX;
     
      for(int gjidx = 0; gjidx < NobjGenJet; gjidx++) {
	const reco::GenJet& genJet =  (*genJets)[gjidx];
	// Write genjet kinematics
	genjetcolpt[  gjidx ] = genJet.pt();
	genjetcolphi[ gjidx ] = genJet.phi();
	genjetcoleta[ gjidx ] = genJet.eta();
	genjetcolet[  gjidx ] = genJet.et();
	genjetcole[   gjidx ] = genJet.energy();
       	genjetcoleme[   gjidx ] = genJet.emEnergy();
       	genjetcolhade[   gjidx ] = genJet.hadEnergy();
	genjetcolinve[   gjidx ] = genJet.invisibleEnergy();
	genjetcolauxe[   gjidx ] = genJet.auxiliaryEnergy();
	// Find closest calojet to this genjet
	// Note: NobjJet was set above to min( pJets->size(), kjMAX )
	double closestDeltaR = 1000;
	int    closestJetIdx = 0;
	for(int cjidx = 0; cjidx < NobjJet; cjidx++) {
	  double deltaRtmp = deltaR( genJet.eta(), genJet.phi(),
				     pJets->at(cjidx).eta(),    pJets->at(cjidx).phi()     );
	 
	  if( deltaRtmp < closestDeltaR ) {
	    closestDeltaR = deltaRtmp;
	    closestJetIdx = cjidx;
	  }
	}
	genjetcol_jet_idx[gjidx] = closestJetIdx;

	if( writeGenJetPart_ ) {
	  for(unsigned int igp = 0, ngp = genJet.nConstituents() ;
	      igp < ngp ; ++igp) {
	    if(gjpidx >= kMAX) break;
	    const GenParticle* gp = genJet.getGenConstituent(igp);
	    genjetparte[gjpidx]             = gp->energy();
	    genjetpartpt[gjpidx]            = gp->pt();
	    genjetparteta[gjpidx]           = gp->eta();
	    genjetpartphi[gjpidx]           = gp->phi();
	    genjetpartpdg[gjpidx]           = gp->pdgId();
	    genjetpart_genjetcolidx[gjpidx] = gjidx;
	    ++gjpidx;
	  }
	} // End of loop over genjets
	NobjGenJetPart = gjpidx; 
      }
    }
    
    /////////// Write uncharged stable genparticles ///////////////////
    
    // Loop over genparticles
    if( writeStableGenPart_  && genParticles.isValid() ) {
      NobjStableGenPart_ = 0;
      genParticle = genParticles->begin();
      for(; genParticle != genParticles->end(); genParticle++) {
	// Write only stable particles
	if( genParticle->status() != 1 ) continue;
	// Write only neutral particles
	if( genParticle->charge() != 0 ) continue;
      
	stableGenPartM_[NobjStableGenPart_]     = genParticle->mass();
	stableGenPartE_[NobjStableGenPart_]     = genParticle->energy();
	stableGenPartEt_[NobjStableGenPart_]    = genParticle->et();
	stableGenPartP_[NobjStableGenPart_]     = genParticle->p();
	stableGenPartPt_[NobjStableGenPart_]    = genParticle->pt();
	stableGenPartEta_[NobjStableGenPart_]   = genParticle->eta();
	stableGenPartPhi_[NobjStableGenPart_]   = genParticle->phi();
	stableGenPartPDGId_[NobjStableGenPart_] = genParticle->pdgId();
      
	NobjStableGenPart_++;
	if( NobjStableGenPart_ == kMaxStableGenPart_ ) break;
      } // End of loop over genparticles  
    }

    CalibTree->Fill();
  }
}

template <> void NJet<reco::CaloJet>::fillExtra(const edm::View<reco::CaloJet>& pJets, int jtno)
{
  fEMF_[ jtno ] = pJets[jtno].emEnergyFraction();
  fHad_[ jtno ] = pJets[jtno].energyFractionHadronic();

  std::vector<CaloTowerPtr> j_towers = pJets[jtno].getCaloConstituents();
  int towno = NobjTow;
  NobjTow+=j_towers.size();
  for (std::vector<CaloTowerPtr>::const_iterator tow = j_towers.begin(); 
       tow != j_towers.end(); ++tow, ++towno){
    
    towet[towno]     = (*tow)->et();
    toweta[towno]    = (*tow)->eta();
    towphi[towno]    = (*tow)->phi();
    towen[towno]     = (*tow)->energy();
    towem[towno]     = (*tow)->emEnergy();
    towhd[towno]     = (*tow)->hadEnergy();
    towoe[towno]     = (*tow)->outerEnergy();
    towid_phi[towno] = (*tow)->id().iphi();
    towid_eta[towno] = (*tow)->id().ieta();
    towid[towno]     = (*tow)->id().rawId();
    tow_jetidx[towno]= jtno;
    
    numBadEcalCells_[towno] = (*tow)->numBadEcalCells();
    numBadHcalCells_[towno] = (*tow)->numBadHcalCells();
    numProblematicEcalCells_[towno] = (*tow)->numProblematicEcalCells();
    numProblematicHcalCells_[towno] = (*tow)->numProblematicHcalCells();
    numRecoveredEcalCells_[towno] = (*tow)->numRecoveredEcalCells();
    numRecoveredHcalCells_[towno] = (*tow)->numRecoveredHcalCells();
  } // End loop over towers
}

template <typename T> void NJet<T>::fillExtra(const edm::View<T>& pJets, int jtno)
{
}


// JetID for calo jets
template <> bool NJet<reco::CaloJet>::looseJetID(reco::CaloJet const &jet, reco::JetID const &jetID) {
  return jetIDCaloFunctorLoose_(jet,jetID);
}
template <typename T> bool NJet<T>::looseJetID(T const &jet, reco::JetID const &jetID) {
  return false;
}

template <> bool NJet<reco::CaloJet>::tightJetID(reco::CaloJet const &jet, reco::JetID const &jetID) {
  return jetIDCaloFunctorTight_(jet,jetID);
}
template <typename T> bool NJet<T>::tightJetID(T const &jet, reco::JetID const &jetID) {
  return false;
}

// JetID for pf jets
template <> bool NJet<reco::PFJet>::looseJetID(reco::PFJet const &jet) {
  pat::strbitset ret = jetIDPFFunctorLoose_.getBitTemplate();
  return jetIDPFFunctorLoose_(jet,ret);
}
template <typename T> bool NJet<T>::looseJetID(T const &jet) {
  return false;
}

template <> bool NJet<reco::PFJet>::tightJetID(reco::PFJet const &jet) {
  pat::strbitset ret = jetIDPFFunctorTight_.getBitTemplate();
  return jetIDPFFunctorTight_(jet,ret);
}
template <typename T> bool NJet<T>::tightJetID(T const &jet) {
  return false;
}

#endif

