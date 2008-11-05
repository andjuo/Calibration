// -*- C++ -*-
//
// Package:    ZJetsHamburgInterface
// Class:      ZJetsHamburgInterface
// 
/**\class ZJetsHamburgInterface ZJetsHamburgInterface.cc ZJets/ZJetsHamburgInterface/src/ZJetsHamburgInterface.cc

 Description: Creates ZJets files in "Hamburg" format for monolithic calibration

 Implementation:
    The idea is to read the ZJets files where the suitable flags that have 
    been put in place by ZJetsSelector and fill a rootfile in the custom 
    Hamburg Calibration format.
*/
//
// Original Author:  Danilo Piparo
//         Created:  Tue Apr  1 16:39:36 CEST 2008
// $Id: ZJetsHamburgInterface.cc,v 1.4 2008/10/13 14:32:10 rwolf Exp $
//
//

// system
#include <vector>
#include <map>

// CMSSW
#include "Calibration/CalibTreeMaker/interface/ZJetsHamburgInterface.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/JetReco/interface/CaloJet.h"
#include "DataFormats/METReco/interface/CaloMET.h"
#include "DataFormats/METReco/interface/CaloMETCollection.h"

ZJetsHamburgInterface::ZJetsHamburgInterface(const edm::ParameterSet& cfg)

{
    // The outfile
    m_ofilename =  cfg.getUntrackedParameter<std::string> ("ofilename");

    // Jet Algorithms
    m_calo_jet_algo = cfg.getParameter< std::string > ("calojetAlgo");
    m_gen_jet_algo = cfg.getParameter< std::string> ("genjetAlgo");

    // Z collection Name (useful to select, in some cases..)
    m_z_collection_name = cfg.getParameter< std::string > ("ZCandidates");

    // Module name FIXME: remove?
    m_selector_module_name = 
                          cfg.getParameter< std::string> ("SelectorModulename");

    // The tree
    m_CalibTree = new TTree("ZJetTree","ZJetTree");

}

//------------------------------------------------------------------------------

ZJetsHamburgInterface::~ZJetsHamburgInterface() {
}

//------------------------------------------------------------------------------


void ZJetsHamburgInterface::analyze(const edm::Event& event, 
                                    const edm::EventSetup& iSetup){
    using namespace edm;

    //DP ------------------------------------------------------

    /* 
      Fetch the algorithm names so to be able to extract the right index.
      The idea is to build a dictionary to be able to read the maps <int,int>
      written by ZJetsSelector.
      The m_useMCtruth flag determines whether the reco Zs or the Gen Zs are 
      considered. This is a residual of the asymmetries between Zs and Jets...
      ... Couldn't more simplifications...
    */

    std::map <std::string,int> calo_index_map;
    std::map <std::string,int> gen_index_map;

    std::string name="";

    // Gen Jets ------------------------------------------------------

    std::vector< edm::Handle<reco::GenJetCollection> > genjetsvec;
    event.getManyByType(genjetsvec);

    // Fill the hash map of leading jets indexs for calo jets
    for (unsigned int i=0;i<genjetsvec.size();++i){
        name=event.getProvenance(genjetsvec[i].id()).moduleLabel();
        if (name.find("gen")!=std::string::npos)
            if (gen_index_map.count(name)==0)
                gen_index_map[name]=i;
        }

    // Jet index

    edm::Handle< std::map<int,int> > gen_jets_index_map;

    event.getByLabel(m_selector_module_name.c_str(),
                     "genJetsIndexMap",
                     gen_jets_index_map);

    // From the name we fetch the algonum, from the algonum the jet index!

    int algonum=gen_index_map[m_gen_jet_algo];
    int gen_jet_index = gen_jets_index_map->find(algonum)->second;
    std::cout<< "HAMBURG: algoname = " << m_calo_jet_algo
             << " Algonum = " << algonum
             << " gen_jet_index = " << gen_jet_index << "\n";

    // End Gen Jets --------------------------------------------------


    // Calo Jets -----------------------------------------------------

    std::vector< edm::Handle<reco::CaloJetCollection> > calojetsvec;
    event.getManyByType(calojetsvec);

    // Fill the hash map of leading jets indexs for calo jets
    for (unsigned int i=0;i<calojetsvec.size();++i){
        name=event.getProvenance(calojetsvec[i].id()).moduleLabel();
        if (name.find("Calo")!=std::string::npos)
            if (calo_index_map.count(name)==0)
                calo_index_map[name]=i;
        }

    // Jet index

    edm::Handle< std::map<int,int> > calo_jets_index_map;

    event.getByLabel(m_selector_module_name.c_str(),
                     "caloJetsIndexMap",
                     calo_jets_index_map);
    
    algonum=calo_index_map[m_calo_jet_algo];
    int calo_jet_index=calo_jets_index_map->find(algonum)->second;

    // End Calo Jets -----------------------------------------------

    /* 
    Z index --------------------------------------------------------
    Remember: to fetch it we need the name of the algo. The jet of algo X might 
    be balanced while the one of algo Y not!
    */
    edm::Handle< std::map< int, int> > zs_index_map;

    event.getByLabel (m_selector_module_name.c_str(),
                      "recoZIndexMap",
                      zs_index_map);

    algonum=calo_index_map[m_calo_jet_algo];
    int z_index=zs_index_map->find(algonum)->second;

    // End Z index -------------------------------------------------

    // If the event is good..
    std::cout << "HAMBURG: 3 indeces: "<< z_index << " "<< gen_jet_index << " "
              << calo_jet_index << "\n";
    if (z_index!=-1 and gen_jet_index!=-1 and calo_jet_index!=-1){

        // The Z ----------------------------------------------------------

        Handle<reco::CandidateCollection> zs;
        event.getByLabel(m_z_collection_name, zs);

        const reco::Candidate* z = &(*zs)[z_index];
        m_zpt=z->pt();
        m_zphi=z->phi();
        m_zeta=z->eta();
        m_zEt=z->et();
        m_zE=z->energy();

        // End of the Z ---------------------------------------------------

        // JETS -----------------------------------------------------------

        // CaloJets:
        Handle<reco::CaloJetCollection> calojets;
        event.getByLabel(m_calo_jet_algo, calojets);

        // Fetch the leading Jet
        const reco::CaloJet* calo_leading_jet = &(*calojets)[calo_jet_index];

        // Take the information out!
        m_jcalpt  = calo_leading_jet->pt();
        m_jcalphi = calo_leading_jet->phi();
        m_jcaleta = calo_leading_jet->eta();
        m_jcalet  = calo_leading_jet->et();
        m_jcale   = calo_leading_jet->energy();

        //  The gen jets      ----------------------------------
        Handle<reco::GenJetCollection> genjets;
        event.getByLabel(m_gen_jet_algo,genjets);

        const reco::GenJet* gen_leading_jet = &(*genjets)[gen_jet_index];

        m_jgenpt  = gen_leading_jet->pt();
        m_jgenphi = gen_leading_jet->phi();
        m_jgeneta = gen_leading_jet->eta();
        m_jgenet  = gen_leading_jet->et();
        m_jgene   = gen_leading_jet->energy();

        // Calotowers ------------------------------------------

        int jtow=0;

	// uncomment for CMSSW_2_1_X compatibility
        std::vector <CaloTowerPtr>jetTowers=calo_leading_jet->getCaloConstituents();
        m_NobjTowCal=jetTowers.size();
        for(std::vector<CaloTowerPtr>::const_iterator tow = jetTowers.begin();
            tow != jetTowers.end(); ++tow, ++jtow){

	  // uncomment for CMSSW_2_0_X compatibility
//        std::vector <CaloTowerRef>jetTowers=calo_leading_jet->getConstituents();
//        m_NobjTowCal=jetTowers.size();
//        for(std::vector<CaloTowerRef>::const_iterator tow = jetTowers.begin();
//            tow != jetTowers.end(); ++tow, ++jtow){

            m_towet [jtow] = (*tow)->et();
            m_toweta[jtow] = (*tow)->eta();
            m_towphi[jtow] = (*tow)->phi();
            m_towen [jtow] = (*tow)->energy();
            m_towem [jtow] = (*tow)->emEnergy();
            m_towhd [jtow] = (*tow)->hadEnergy();
            m_towoe [jtow] = (*tow)->outerEnergy();
            m_towid_phi[jtow] = (*tow)->id().iphi();
            m_towid_eta[jtow] = (*tow)->id().ieta();
            m_towid [jtow] = (*tow)->id().rawId();
            m_townum[jtow] = jtow;
            }

        // MET -------------------------------------------------
        Handle<reco::CaloMETCollection> met;
        event.getByLabel("met",met); 

        // The MET is just one per event
        m_mcalmet=(*met)[0].pt();
        m_mcalphi=(*met)[0].phi();
        m_mcalsum=(*met)[0].sumEt();

        // And Finally, we fill the tree!

        LogInfo ("dbg") << "Filling the tree!!";
        m_CalibTree->Fill();

    }
}


//------------------------------------------------------------------------------

void ZJetsHamburgInterface::beginJob(const edm::EventSetup&){

    // Tree branches
    //tower data
    const int kMAX = 10000;
    m_towet  = new float [ kMAX ];
    m_toweta = new float [ kMAX ];
    m_towphi = new float [ kMAX ];
    m_towen  = new float [ kMAX ];
    m_towem  = new float [ kMAX ];
    m_towhd  = new float [ kMAX ];
    m_towoe  = new float [ kMAX ];
    m_towid_phi = new int[ kMAX ];
    m_towid_eta = new int[ kMAX ];
    m_towid     = new int[ kMAX ];
    m_townum    = new int[ kMAX ];

    // CaloTower branches
    m_CalibTree->Branch( "NobjTowCal",&m_NobjTowCal,"NobjTowCal/I"            );
    m_CalibTree->Branch( "TowNum",    m_townum,     "TowNum[NobjTowCal]/I"    );
    m_CalibTree->Branch( "TowId",     m_towid,      "TowId[NobjTowCal]/I"     );
    m_CalibTree->Branch( "TowId_phi", m_towid_phi,  "TowId_phi[NobjTowCal]/I" );
    m_CalibTree->Branch( "TowId_eta", m_towid_eta,  "TowId_eta[NobjTowCal]/I" );
    m_CalibTree->Branch( "TowEt",     m_towet,      "TowEt[NobjTowCal]/F"     );
    m_CalibTree->Branch( "TowEta",    m_toweta,     "TowEta[NobjTowCal]/F"    );
    m_CalibTree->Branch( "TowPhi",    m_towphi,     "TowPhi[NobjTowCal]/F"    );
    m_CalibTree->Branch( "TowE",      m_towen,      "TowE[NobjTowCal]/F"      );
    m_CalibTree->Branch( "TowEm",     m_towem,      "TowEm[NobjTowCal]/F"     );
    m_CalibTree->Branch( "TowHad",    m_towhd,      "TowHad[NobjTowCal]/F"    );
    m_CalibTree->Branch( "TowOE",     m_towoe,      "TowOE[NobjTowCal]/F"     );

    // CaloJet branches 
    m_CalibTree->Branch( "JetCalPt",  &m_jcalpt,    "JetCalPt/F"  );
    m_CalibTree->Branch( "JetCalPhi", &m_jcalphi,   "JetCalPhi/F" );
    m_CalibTree->Branch( "JetCalEta", &m_jcaleta,   "JetCalEta/F" );
    m_CalibTree->Branch( "JetCalEt",  &m_jcalet,    "JetCalEt/F"  );
    m_CalibTree->Branch( "JetCalE",   &m_jcale,     "JetCalE/F"   );

    // GenJet branches 
    m_CalibTree->Branch( "JetGenPt",  &m_jgenpt,    "JetGenPt/F"  );
    m_CalibTree->Branch( "JetGenPhi", &m_jgenphi,   "JetGenPhi/F" );
    m_CalibTree->Branch( "JetGenEta", &m_jgeneta,   "JetGenEta/F" );
    m_CalibTree->Branch( "JetGenEt",  &m_jgenet,    "JetGenEt/F"  );
    m_CalibTree->Branch( "JetGenE",   &m_jgene,     "JetGenE/F"   );

    // MET branches
    m_CalibTree->Branch( "MetCal",    &m_mcalmet,   "MetCal/F"    );
    m_CalibTree->Branch( "MetCalPhi", &m_mcalphi,   "MetCalPhi/F" );
    m_CalibTree->Branch( "MetCalSum", &m_mcalsum,   "MetCalSum/F" );

    // Zs branches
    m_CalibTree->Branch( "ZPt",  &m_zpt,  "ZPt/F"  );
    m_CalibTree->Branch( "ZPhi", &m_zphi, "ZPhi/F" );
    m_CalibTree->Branch( "ZEta", &m_zeta, "ZEta/F" );
    m_CalibTree->Branch( "ZEt",  &m_zEt,  "ZEt/F"   );
    m_CalibTree->Branch( "ZE",   &m_zE,   "ZE/F"   );



}

//------------------------------------------------------------------------------

void ZJetsHamburgInterface::endJob() {

    TFile ofile (m_ofilename.c_str(),"RECREATE");
    m_CalibTree->Write();
    ofile.Close();

    m_CalibTree->Print();

    if (m_CalibTree!=NULL)
        delete m_CalibTree;


}

//------------------------------------------------------------------------------

//define this as a plug-in
DEFINE_FWK_MODULE(ZJetsHamburgInterface);
