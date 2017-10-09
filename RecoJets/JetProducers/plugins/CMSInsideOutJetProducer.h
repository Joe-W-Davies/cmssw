#ifndef RecoJets_JetAlgorithms_InsideOutProducer_H
#define RecoJets_JetAlgorithms_InsideOutProducer_H
/*
 * CMS Inside-Out jet producer
 *
 * Produces jets build w/ the inside-out algorithm to seed
 * the PFRecoTauAlgorithm
 *
 * Author:  Evan Friis, UC Davis evan.friis@cern.ch
 *
 * Adapted from code in RecoJets/JetProducers::BaseJetProducer
 *
 */



#include "RecoJets/JetProducers/plugins/VirtualJetProducer.h"
#include "RecoJets/JetAlgorithms/interface/CMSInsideOutAlgorithm.h"


class CMSInsideOutJetProducer : public VirtualJetProducer
{

public:
  //
  // construction/destruction
  //
  explicit CMSInsideOutJetProducer(const edm::ParameterSet& iConfig);
  ~CMSInsideOutJetProducer() override;

  void produce( edm::Event & iEvent, const edm::EventSetup & iSetup ) override;

  
protected:

  //
  // member functions
  //

  void runAlgorithm( edm::Event& iEvent, const edm::EventSetup& iSetup ) override;

  CMSInsideOutAlgorithm alg_;
};

#endif
