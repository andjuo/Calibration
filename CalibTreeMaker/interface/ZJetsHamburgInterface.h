// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

// Root Includes
#include "TTree.h"
#include "TFile.h"

class ZJetsHamburgInterface : public edm::EDAnalyzer {
   public:
    explicit ZJetsHamburgInterface(const edm::ParameterSet&);
    ~ZJetsHamburgInterface();

   private:
    virtual void beginJob(const edm::EventSetup&) ;
    virtual void analyze(const edm::Event&, const edm::EventSetup&);
    virtual void endJob() ;

    // ----------member data ---------------------------
    /// Tree where the information in the final format is stored
    TTree* m_CalibTree;

    /// A bool that allows us to use MC truth
    bool m_useMCtruth;

    // Variables to fill the tree, not many details on them...

    int m_NobjTowCal;

    float* m_towet;
    float* m_toweta;
    float* m_towphi;
    float* m_towen;
    float* m_towem;
    float* m_towhd;
    float* m_towoe;

    int* m_towid_phi;
    int* m_towid_eta;
    int* m_towid;
    int* m_townum;

    float m_jcalpt, m_jcalphi, m_jcaleta, m_jcalet, m_jcale;
    float m_jgenpt, m_jgenphi, m_jgeneta, m_jgenet, m_jgene;
    float m_mcalmet, m_mcalphi, m_mcalsum;

    float m_zpt, m_zphi, m_zeta, m_zEt, m_zE;

    /// Out rootfile name
    std::string m_ofilename;

    /// Calo jet algorithm name
    std::string m_calo_jet_algo;
    
    /// Gen jet algorithm name
    std::string m_gen_jet_algo;

    /// Z collection name
    std::string m_z_collection_name;

    /// Selector module name
    std::string m_selector_module_name;
};
