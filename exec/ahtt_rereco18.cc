// execution macro for testing the fwk devs
// compile:
// g++ $(root-config --cflags --evelibs) -std=c++17 -O3 -Wall -Wextra -Wpedantic -Werror -Wno-float-equal -Wno-sign-compare -I ../plugins/ -I ../src/ -o ahtt_rereco18 ahtt_rereco18.cc

#include "Dataset.h"
#include "Collection.h"
#include "Aggregate.h"
#include "Histogram.h"

#include "misc/string_io.h"
#include "misc/function_util.h"
#include "misc/numeric_vector.h"
#include "misc/spin_correlation.h"
#include "misc/input_dataset.h"

// http://tclap.sourceforge.net/
#include "tclap/CmdLine.h"

int main(int argc, char** argv) {
  TCLAP::CmdLine cmdbase("A/H -> tt analysis, 2018 dataset", ' ', "0.01");
  TCLAP::ValueArg<std::string> cmdchannel("", "channel","Analysis channel - ee, emu, mumu", false, "emu", "string", cmdbase);
  TCLAP::ValueArg<std::string> cmddataset("", "dataset","Dataset to be used -  consult the input_dataset.h plugin", false, 
                                          "TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8", "string", cmdbase);
  //TCLAP::SwitchArg cmdtest("", "test", "Dummy boolean argument", cmdbase, false);
  cmdbase.parse( argc, argv );

  // get the value parsed by each arg 
  std::string channel = cmdchannel.getValue();
  std::string dataset = cmddataset.getValue();
  //bool test = cmdtest.getValue();

  using namespace Framework;

  // dataset to consider
  Dataset<TChain> dat("mc", "Events");
  dat.set_files(file_list(dataset), 2);

  Collection<boolean, uint, unsigned long long> meta("meta", 12);
  meta.add_attribute("run", "run", 1U);
  meta.add_attribute("lumi", "luminosityBlock", 1U);
  meta.add_attribute("event", "event", 1ULL);
  meta.add_attribute("ele_23_12", "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL", true);
  meta.add_attribute("ele_23_12_dz", "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ", true);
  meta.add_attribute("mu_23_ele_12", "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL", true);
  meta.add_attribute("mu_23_ele_12_dz", "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ", true);
  meta.add_attribute("mu_12_ele_23_dz", "HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ", true);
  meta.add_attribute("mu8_ele_23_dz", "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ", true);
  meta.add_attribute("mu_17_8_dz", "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8", true);
  meta.add_attribute("ele_32", "HLT_Ele32_WPTight_Gsf", true);
  meta.add_attribute("mu_24", "HLT_IsoMu24", true);

  Collection<float> weight("weight", 2);
  weight.add_attribute("gen", "genWeight", 1.f);
  weight.add_attribute("lhe_orixwgtup", "LHEWeight_originalXWGTUP", 1.f);

  Collection<int, float> gen_particle("gen_particle", "nGenPart", 10, 256);
  gen_particle.add_attribute("mass", "GenPart_mass", 1.f);
  gen_particle.add_attribute("pt", "GenPart_pt", 1.f);
  gen_particle.add_attribute("eta", "GenPart_eta", 1.f);
  gen_particle.add_attribute("phi", "GenPart_phi", 1.f);
  gen_particle.add_attribute("pdg", "GenPart_pdgId", 1);
  gen_particle.add_attribute("status", "GenPart_status", 1);
  gen_particle.add_attribute("flag", "GenPart_statusFlags", 1);
  gen_particle.add_attribute("mother", "GenPart_genPartIdxMother", 1);
  gen_particle.transform_attribute("tt2l", [&pdgs = gen_particle.get<int>("pdg"), &idxs = gen_particle.get<int>("mother"), 
                                            &flags = gen_particle.get<int>("flag")] 
                                   (int pdg, int flag, int idx) -> int {
                                     // bitwise flag for particles which are part of a gen tt system
                                     // 1 top
                                     // 2 W+
                                     // 4 bottom
                                     // 8 antilepton - e, mu only
                                     // 16 neutrino
                                     // 32 antitop
                                     // 64 W-
                                     // 128 antibottom
                                     // 256 lepton - e, mu only
                                     // 512 antineutrino
                                     if (pdg == 6 and flag & 8192)
                                       return 1;
                                     if (pdg == -6 and flag & 8192)
                                       return 32;

                                     if (std::abs(pdg) == 24 and flag & 8192) {
                                       while (idx > -1) {
                                         if (std::abs(pdgs[idx]) == 6 and flags[idx] & 8192) {
                                           if (pdg > 0)
                                             return 2;
                                           else
                                             return 64;
                                         }

                                         idx = idxs[idx];
                                       }
                                     }

                                     if (std::abs(pdg) > 10 and std::abs(pdg) < 15) {
                                       if (std::abs(pdgs[idx]) == 24 and flags[idx] & 8192) {
                                         idx = idxs[idx];

                                         while (idx > -1) {
                                           if (std::abs(pdgs[idx]) == 6 and flags[idx] & 8192) {
                                             if (pdg % 2) {
                                               if (pdg > 0)
                                                 return 256;
                                               else 
                                                 return 8;
                                             }
                                             else {
                                               if (pdg > 0)
                                                 return 16;
                                               else 
                                                 return 512;
                                             }
                                           }

                                           idx = idxs[idx];
                                         }
                                       }
                                     }

                                     return 0;
                                   }, "pdg", "flag", "mother");

  // 4 times gen_particle to refer to the top, antitop, lepton, antilepton
  Aggregate gen_tt2l("gen_tt2l", 8, 1, gen_particle, gen_particle, gen_particle, gen_particle);
  gen_tt2l.set_indexer([] (const auto &g1, const auto &g2, const auto &g3, const auto &g4)
                       -> std::vector<std::array<int, 4>> {
                         auto top = g1.filter_equal("tt2l", 1);
                         auto antitop = g2.filter_equal("tt2l", 32);
                         auto lepton = g3.filter_equal("tt2l", 256);
                         auto antilepton = g4.filter_equal("tt2l", 8);

                         if (top.size() != 1 or antitop.size() != 1 or lepton.size() != 1 or antilepton.size() != 1)
                           return {};

                         return {{top[0], antitop[0], lepton[0], antilepton[0]}};
                       });

  gen_tt2l.add_attribute("TT_m", invariant_mass<2>(), 
                         "gen_particle::pt", "gen_particle::eta", "gen_particle::phi", "gen_particle::mass",
                         "gen_particle::pt", "gen_particle::eta", "gen_particle::phi", "gen_particle::mass");
  gen_tt2l.add_attribute("ckk", ckk<>, 
                         "gen_particle::pt", "gen_particle::eta", "gen_particle::phi", "gen_particle::mass",
                         "gen_particle::pt", "gen_particle::eta", "gen_particle::phi", "gen_particle::mass",
                         "gen_particle::pt", "gen_particle::eta", "gen_particle::phi", "gen_particle::mass",
                         "gen_particle::pt", "gen_particle::eta", "gen_particle::phi", "gen_particle::mass");
  gen_tt2l.add_attribute("crr", crr<>, 
                         "gen_particle::pt", "gen_particle::eta", "gen_particle::phi", "gen_particle::mass",
                         "gen_particle::pt", "gen_particle::eta", "gen_particle::phi", "gen_particle::mass",
                         "gen_particle::pt", "gen_particle::eta", "gen_particle::phi", "gen_particle::mass",
                         "gen_particle::pt", "gen_particle::eta", "gen_particle::phi", "gen_particle::mass");
  gen_tt2l.add_attribute("cnn", cnn<>, 
                         "gen_particle::pt", "gen_particle::eta", "gen_particle::phi", "gen_particle::mass",
                         "gen_particle::pt", "gen_particle::eta", "gen_particle::phi", "gen_particle::mass",
                         "gen_particle::pt", "gen_particle::eta", "gen_particle::phi", "gen_particle::mass",
                         "gen_particle::pt", "gen_particle::eta", "gen_particle::phi", "gen_particle::mass");
  gen_tt2l.add_attribute("cHel", cHel<>, 
                         "gen_particle::pt", "gen_particle::eta", "gen_particle::phi", "gen_particle::mass",
                         "gen_particle::pt", "gen_particle::eta", "gen_particle::phi", "gen_particle::mass",
                         "gen_particle::pt", "gen_particle::eta", "gen_particle::phi", "gen_particle::mass",
                         "gen_particle::pt", "gen_particle::eta", "gen_particle::phi", "gen_particle::mass");
  gen_tt2l.add_attribute("cHan", cHan<>, 
                         "gen_particle::pt", "gen_particle::eta", "gen_particle::phi", "gen_particle::mass",
                         "gen_particle::pt", "gen_particle::eta", "gen_particle::phi", "gen_particle::mass",
                         "gen_particle::pt", "gen_particle::eta", "gen_particle::phi", "gen_particle::mass",
                         "gen_particle::pt", "gen_particle::eta", "gen_particle::phi", "gen_particle::mass");
  gen_tt2l.add_attribute("cSca", cSca<>, 
                         "gen_particle::pt", "gen_particle::eta", "gen_particle::phi", "gen_particle::mass",
                         "gen_particle::pt", "gen_particle::eta", "gen_particle::phi", "gen_particle::mass",
                         "gen_particle::pt", "gen_particle::eta", "gen_particle::phi", "gen_particle::mass",
                         "gen_particle::pt", "gen_particle::eta", "gen_particle::phi", "gen_particle::mass");
  gen_tt2l.add_attribute("cTra", cTra<>, 
                         "gen_particle::pt", "gen_particle::eta", "gen_particle::phi", "gen_particle::mass",
                         "gen_particle::pt", "gen_particle::eta", "gen_particle::phi", "gen_particle::mass",
                         "gen_particle::pt", "gen_particle::eta", "gen_particle::phi", "gen_particle::mass",
                         "gen_particle::pt", "gen_particle::eta", "gen_particle::phi", "gen_particle::mass");

  // FIXME complete this with objects, hists etc...

  dat.associate(meta, weight, gen_particle);

  Histogram hist_0;
  hist_0.make_histogram<TH1F>(filler_first_of(gen_tt2l, "TT_m"), "gen_TT_m", "", 120, 300.f, 1500.f);
  hist_0.make_histogram<TH1F>(filler_first_of(gen_tt2l, "ckk"), "gen_ckk", "", 24, -1.f, 1.f);
  hist_0.make_histogram<TH1F>(filler_first_of(gen_tt2l, "crr"), "gen_crr", "", 24, -1.f, 1.f);
  hist_0.make_histogram<TH1F>(filler_first_of(gen_tt2l, "cnn"), "gen_cnn", "", 24, -1.f, 1.f);
  hist_0.make_histogram<TH1F>(filler_first_of(gen_tt2l, "cHel"), "gen_cHel", "", 24, -1.f, 1.f);
  hist_0.make_histogram<TH1F>(filler_first_of(gen_tt2l, "cHan"), "gen_cHan", "", 24, -1.f, 1.f);
  hist_0.make_histogram<TH1F>(filler_first_of(gen_tt2l, "cSca"), "gen_cSca", "", 24, -1.f, 1.f);
  hist_0.make_histogram<TH1F>(filler_first_of(gen_tt2l, "cTra"), "gen_cTra", "", 24, -1.f, 1.f);
  hist_0.make_histogram<TH2F>(filler_first_of(gen_tt2l, "TT_m", "cHel"), "gen_TT_m_cHel", "", 120, 300.f, 1500.f, 24, -1.f, 1.f);
  hist_0.make_histogram<TH2F>(filler_first_of(gen_tt2l, "TT_m", "cHan"), "gen_TT_m_cHan", "", 120, 300.f, 1500.f, 24, -1.f, 1.f);
  hist_0.make_histogram<TH2F>(filler_first_of(gen_tt2l, "TT_m", "cSca"), "gen_TT_m_cSca", "", 120, 300.f, 1500.f, 24, -1.f, 1.f);
  hist_0.make_histogram<TH2F>(filler_first_of(gen_tt2l, "TT_m", "cTra"), "gen_TT_m_cTra", "", 120, 300.f, 1500.f, 24, -1.f, 1.f);
  hist_0.make_histogram<TH2F>(filler_first_of(gen_tt2l, "TT_m", "ckk"), "gen_TT_m_ckk", "", 120, 300.f, 1500.f, 24, -1.f, 1.f);
  hist_0.make_histogram<TH2F>(filler_first_of(gen_tt2l, "TT_m", "crr"), "gen_TT_m_crr", "", 120, 300.f, 1500.f, 24, -1.f, 1.f);
  hist_0.make_histogram<TH2F>(filler_first_of(gen_tt2l, "TT_m", "cnn"), "gen_TT_m_cnn", "", 120, 300.f, 1500.f, 24, -1.f, 1.f);
  hist_0.make_histogram<TH3F>(filler_first_of(gen_tt2l, "ckk", "crr", "cnn"), "gen_cii", "", 24, -1.f, 1.f, 24, -1.f, 1.f, 24, -1.f, 1.f);
  hist_0.make_histogram<TH3F>(filler_first_of(gen_tt2l, "cHan", "cSca", "cTra"), "gen_cIii", "", 24, -1.f, 1.f, 24, -1.f, 1.f, 24, -1.f, 1.f);

  int yield = 0;
  auto f_analyze = [&channel, &yield, &meta, &weight, &gen_particle, &gen_tt2l, &hist_0] (long long entry) mutable {
    gen_particle.populate(entry);
    gen_tt2l.populate(entry);
    if (gen_tt2l.n_elements())
      hist_0.fill();

    meta.populate(entry);
    auto hlt_ee   = meta.count(any_of<2>(), "ele_23_12", "ele_23_12_dz");
    auto hlt_emu  = meta.count(any_of<4>(), "mu_23_ele_12", "mu_23_ele_12_dz", "mu_12_ele_23_dz", "mu8_ele_23_dz");
    auto hlt_mumu = meta.count(any_of(), "mu_17_8_dz");
    auto hlt_se   = meta.count(any_of(), "ele_32");
    auto hlt_smu  = meta.count(any_of(), "mu_24");

    if (channel == "ee") {
      if (hlt_emu or hlt_mumu or hlt_smu)
        return;
      if (!hlt_ee and !hlt_se)
        return;

      ++yield;
    }

    if (channel == "emu") {
      if (hlt_ee or hlt_mumu)
        return;
      if (!hlt_emu and !hlt_se and !hlt_smu)
        return;

      ++yield;
    }

    if (channel == "mumu") {
      if (hlt_emu or hlt_ee or hlt_se)
        return;
      if (!hlt_mumu and !hlt_smu)
        return;

      ++yield;
    }
  };
  dat.set_analyzer(f_analyze);
  dat.analyze();
  std::cout << yield << " pass trigger in channel " << channel << std::endl;

  hist_0.save_as(channel + "_hist_0.root");

  return 0;
}

