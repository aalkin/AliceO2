// Copyright 2019-2020 CERN and copyright holders of ALICE O2.
// See https://alice-o2.web.cern.ch/copyright for details of the copyright holders.
// All rights not expressly granted are reserved.
//
// This software is distributed under the terms of the GNU General Public
// License v3 (GPL Version 3), copied verbatim in the file "COPYING".
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.
///
/// \brief Example for rewriting AOD tables
/// \author
/// \since

#include "Framework/runDataProcessing.h"
#include "Framework/AnalysisTask.h"

using namespace o2;
using namespace o2::framework;
using namespace o2::framework::expressions;

struct RewriteMcParticles {
  Produces<aod::StoredMcParticles_001From<o2::aod::Hash<"AOD1"_h>>> mcparts;
  Configurable<float> etaCut{"etaCut", 1.5f, "eta cut"};

  Filter lessThan15 = nabs(aod::mcparticle::eta) < etaCut;

  void process(soa::Filtered<aod::McParticles_001> const& mcparticles) // subscribe to full to have Eta
  {
    for (auto& particle : mcparticles) {
      mcparts(
        particle.mcCollisionId(),
        particle.pdgCode(),
        particle.statusCode(),
        particle.flags(),
        particle.mothersIds(),
        particle.daughtersIds().data(),
        particle.weight(),
        particle.px(),
        particle.py(),
        particle.pz(),
        particle.e(),
        particle.vx(),
        particle.vy(),
        particle.vz(),
        particle.vt()
        );
    }
  }
};

WorkflowSpec defineDataProcessing(ConfigContext const& cfgc)
{
  return {adaptAnalysisTask<RewriteMcParticles>(cfgc)};
}
