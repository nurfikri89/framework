// execution macro for testing the fwk devs
// compile:
// g++ $(root-config --cflags --evelibs) -std=c++17 -O3 -Wall -Wextra -Wpedantic -Werror -Wno-float-equal -Wno-sign-compare -I ../plugins/ -I ../src/ -o bpark_tt3l bpark_tt3l.cc

#include "../src/Dataset.h"
#include "../src/Collection.h"
#include "../src/Aggregate.h"
#include "../src/Histogram.h"

#include "misc/string_io.h"
#include "misc/function_util.h"
#include "misc/numeric_vector.h"
#include "misc/input_dataset.h"

// http://tclap.sourceforge.net/
#include "tclap/CmdLine.h"

int main(int argc, char** argv) {
  TCLAP::CmdLine cmdbase("b parking tt -> 3l differential analysis, 2018 dataset", ' ', "0.01");
  //TCLAP::ValueArg<std::string> cmdchannel("", "channel","Analysis channel - ee, emu, mumu", false, "emu", "string", cmdbase);
  TCLAP::ValueArg<std::string> cmddataset("", "dataset","Dataset to be used -  consult the input_dataset.h plugin", false, 
                                          "TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8", "string", cmdbase);
  //TCLAP::SwitchArg cmdtest("", "test", "Dummy boolean argument", cmdbase, false);
  cmdbase.parse( argc, argv );

  // get the value parsed by each arg 
  //std::string channel = cmdchannel.getValue();
  std::string dataset = cmddataset.getValue();
  //bool test = cmdtest.getValue();

  using namespace Framework;

  Dataset<TChain> dat(dataset, "Events");
  dat.set_files(file_list(dataset), 10);

  std::vector<std::string> hlt;
  Collection<boolean, uint, unsigned long long> meta("meta", 43);
  meta.add_attribute("run", "run", 1U);
  meta.add_attribute("lumi", "luminosityBlock", 1U);
  meta.add_attribute("event", "event", 1ULL);
  for (uint ip = 0; ip < 5; ++ip) {
    hlt.emplace_back("HLT_Mu7_IP4_part" + to_str(ip));
    meta.add_attribute(hlt.back(), hlt.back(), true);

    hlt.emplace_back("HLT_Mu8_IP3_part" + to_str(ip));
    meta.add_attribute(hlt.back(), hlt.back(), true);

    hlt.emplace_back("HLT_Mu8_IP5_part" + to_str(ip));
    meta.add_attribute(hlt.back(), hlt.back(), true);

    hlt.emplace_back("HLT_Mu8_IP6_part" + to_str(ip));
    meta.add_attribute(hlt.back(), hlt.back(), true);

    hlt.emplace_back("HLT_Mu9_IP4_part" + to_str(ip));
    meta.add_attribute(hlt.back(), hlt.back(), true);

    hlt.emplace_back("HLT_Mu9_IP5_part" + to_str(ip));
    meta.add_attribute(hlt.back(), hlt.back(), true);

    hlt.emplace_back("HLT_Mu9_IP6_part" + to_str(ip));
    meta.add_attribute(hlt.back(), hlt.back(), true);

    hlt.emplace_back("HLT_Mu12_IP6_part" + to_str(ip));
    meta.add_attribute(hlt.back(), hlt.back(), true);
  }
  //hlt.emplace_back("HLT_Ele32_WPTight_Gsf");
  //meta.add_attribute(hlt.back(), hlt.back(), true);

  Collection<float> weight("weight", 2);
  weight.add_attribute("gen", "genWeight", 1.f);
  weight.add_attribute("lhe_orixwgtup", "LHEWeight_originalXWGTUP", 1.f);

  Collection<boolean, int, float> electron("electron", "nElectron", 10, 16);
  electron.add_attribute("pt", "Electron_pt", 1.f);
  electron.add_attribute("eta", "Electron_eta", 1.f);
  electron.add_attribute("phi", "Electron_phi", 1.f);
  electron.transform_attribute("abs_pteta", absolute_difference<>, "pt", "eta");
  electron.transform_attribute("abs_ptphi", absolute_difference<>, "pt", "phi");
  electron.add_attribute("charge", "Electron_charge", 1);
  electron.add_attribute("deta_sc", "Electron_deltaEtaSC", 1.f);
  electron.transform_attribute("sc_eta", std::plus<float>(), "deta_sc", "eta");
  electron.add_attribute("id_cutbased", "Electron_cutBased", 1);
  electron.transform_attribute("mass", [] (float pt) { return 0.f * pt; }, "pt"); // too lazy to figure out what naod mass is

  Collection<boolean, int, float> muon("muon", "nMuon", 12, 16);
  muon.add_attribute("pt", "Muon_pt", 1.f);
  muon.add_attribute("eta", "Muon_eta", 1.f);
  muon.add_attribute("phi", "Muon_phi", 1.f);
  muon.add_attribute("charge", "Muon_charge", 1);
  muon.add_attribute("sip3d", "Muon_sip3d", 1.f);
  muon.add_attribute("ip3d", "Muon_ip3d", 1.f);
  muon.add_attribute("dxy", "Muon_dxy", 1.f);
  muon.add_attribute("dxyErr", "Muon_dxyErr", 1.f);
  muon.transform_attribute("sip2d", [] (float dxy, float dxyErr) { return std::abs(dxy / dxyErr); }, "dxy", "dxyErr");
  muon.add_attribute("dxybs", "Muon_dxybs", 1.f);
  muon.add_attribute("id_cutloose", "Muon_looseId", true);
  muon.transform_attribute("mass", [] (float pt) { return 0.f * pt; }, "pt"); // too lazy to figure out what naod mass is

  dat.associate(meta, weight, electron, muon);

  auto f_tt3l_idx = [] (auto &ge, auto &gu, auto &gb) -> std::vector<std::array<int, 3>> {
    if (ge.n_elements() < 1 or gu.n_elements() < 2)
      return {};

    auto idxe = ge.sort_descending("pt");
    auto idxu = gu.indices();
    idxu.clear();

    auto ipdb = gb.sort_absolute_descending("sip3d");
    for (int iu = 1; iu < ipdb.size(); ++iu)
      idxu.emplace_back(ipdb[iu]);

    gu.update_indices(idxu);
    idxu = gu.sort_descending("pt");
    idxu.emplace_back(ipdb[0]);
    gu.update_indices(idxu);

    return {{idxe[0], idxu[0], ipdb[0]}};
  };

  Aggregate euu("euu", 18, 1, electron, muon, muon);
  euu.set_indexer(f_tt3l_idx);
  euu.add_attribute("e_pt", identity<>, "electron::pt");
  euu.add_attribute("e_eta", identity<>, "electron::eta");
  euu.add_attribute("e_phi", identity<>, "electron::phi");

  euu.add_attribute("u_pt", [] (float f1, float) {return f1;}, "muon::pt", "muon::pt");
  euu.add_attribute("u_eta", [] (float f1, float) {return f1;}, "muon::eta", "muon::eta");
  euu.add_attribute("u_phi", [] (float f1, float) {return f1;}, "muon::phi", "muon::phi");

  euu.add_attribute("b_pt", [] (float, float f2) {return f2;}, "muon::pt", "muon::pt");
  euu.add_attribute("b_eta", [] (float, float f2) {return f2;}, "muon::eta", "muon::eta");
  euu.add_attribute("b_phi", [] (float, float f2) {return f2;}, "muon::phi", "muon::phi");

  euu.add_attribute("eu_deta", absolute_difference<>, "electron::eta", "muon::eta");
  euu.add_attribute("eu_dphi", dphi<>, "electron::phi", "muon::phi");
  euu.transform_attribute("eu_dR", quadratic_sum<>, "eu_deta", "eu_dphi");
  euu.add_attribute("eu_charge", std::plus<int>(), "electron::charge", "muon::charge");
  euu.add_attribute("eu_mass", invariant_mass<2>(),
                    "electron::pt", "electron::eta", "electron::phi", "electron::mass", 
                    "muon::pt", "muon::eta", "muon::phi", "muon::mass");
  euu.add_attribute("lb_deta", [] (float eeta, int eq, float ueta, int uq, float beta, int bq) {
      if (eq * bq < 0)
        return absolute_difference(eeta, beta);
      else if (uq * bq < 0)
        return absolute_difference(ueta, beta);

      return -9999.f;
    }, "electron::eta", "electron::charge", "muon::eta", "muon::charge", "muon::eta", "muon::charge");
  euu.add_attribute("lb_dphi", [] (float ephi, int eq, float uphi, int uq, float bphi, int bq) {
      if (eq * bq < 0)
        return dphi(ephi, bphi);
      else if (uq * bq < 0)
        return dphi(uphi, bphi);

      return -9999.f;
    }, "electron::phi", "electron::charge", "muon::phi", "muon::charge", "muon::phi", "muon::charge");
  euu.add_attribute("lb_mass", [] (float ept, float eeta, float ephi, float em, int eq,
                                   float upt, float ueta, float uphi, float um, int uq,
                                   float bpt, float beta, float bphi, float bm, int bq) -> float {
                      static TLorentzVector p1, p2;
                      p1.SetPtEtaPhiM(bpt, beta, bphi, bm);

                      if (eq * bq < 0)
                        p2.SetPtEtaPhiM(ept, eeta, ephi, em);
                      else if (uq * bq < 0)
                        p2.SetPtEtaPhiM(upt, ueta, uphi, um);
                      else
                        return -9999.f;

                      return (p1 + p2).M();
                    }, 
                    "electron::pt", "electron::eta", "electron::phi", "electron::mass", "electron::charge", 
                    "muon::pt", "muon::eta", "muon::phi", "muon::mass", "muon::charge",
                    "muon::pt", "muon::eta", "muon::phi", "muon::mass", "muon::charge");

  euu.add_attribute("eub_mass", invariant_mass<3>(),
                    "electron::pt", "electron::eta", "electron::phi", "electron::mass", 
                    "muon::pt", "muon::eta", "muon::phi", "muon::mass",
                    "muon::pt", "muon::eta", "muon::phi", "muon::mass");

  Histogram hist_1;
  hist_1.make_histogram<TH1I>(filler_count(electron), "ele_nele_1", "", 10, 0, 10);
  hist_1.make_histogram<TH1I>(filler_count(muon), "muo_nmuo_1", "", 10, 0, 10);
  hist_1.make_histogram<TH2I>(filler_count(electron, muon), "euu_nele_nmuo_1", "", 10, 0, 10, 10, 0, 10);

  hist_1.make_histogram<TH1F>(filler_first_of(electron, "pt"), "ele_pt_1_1", "", 20, 0.f, 300.f);
  hist_1.make_histogram<TH1F>(filler_all_of(electron, "pt"), "ele_pt_a_1", "", 20, 0.f, 300.f);
  hist_1.make_histogram<TH1F>(filler_first_of(electron, "eta"), "ele_eta_1_1", "", 20, -2.5f, 2.5f);
  hist_1.make_histogram<TH1F>(filler_all_of(electron, "eta"), "ele_eta_a_1", "", 20, -2.5f, 2.5f);
  hist_1.make_histogram<TH2F>(filler_first_of(electron, "pt", "eta"), "ele_pt_eta_1_1", "", 20, 0.f, 300.f, 20, -2.5f, 2.5f);
  hist_1.make_histogram<TH2F>(filler_all_of(electron, "pt", "eta"), "ele_pt_eta_a_1", "", 20, 0.f, 300.f, 20, -2.5f, 2.5f);
  hist_1.make_histogram<TH1F>(filler_first_of(electron, "abs_pteta"), "ele_pteta_1_1", "", 20, 0.f, 300.f);
  hist_1.make_histogram<TH1F>(filler_all_of(electron, "abs_pteta"), "ele_pteta_a_1", "", 20, 0.f, 300.f);
  hist_1.make_histogram<TH1F>(filler_first_of(electron, "abs_ptphi"), "ele_ptphi_1_1", "", 20, 0.f, 300.f);
  hist_1.make_histogram<TH1F>(filler_all_of(electron, "abs_ptphi"), "ele_ptphi_a_1", "", 20, 0.f, 300.f);

  hist_1.make_histogram<TH1F>(filler_first_of(muon, "pt"), "muo_pt_1_1", "", 20, 0.f, 300.f);
  hist_1.make_histogram<TH1F>(filler_all_of(muon, "pt"), "muo_pt_a_1", "", 20, 0.f, 300.f);
  hist_1.make_histogram<TH1F>(filler_first_of(muon, "eta"), "muo_eta_1_1", "", 20, -2.5f, 2.5f);
  hist_1.make_histogram<TH1F>(filler_all_of(muon, "eta"), "muo_eta_a_1", "", 20, -2.5f, 2.5f);
  hist_1.make_histogram<TH2F>(filler_first_of(muon, "pt", "eta"), "muo_pt_eta_1_1", "", 20, 0.f, 300.f, 20, -2.5f, 2.5f);
  hist_1.make_histogram<TH2F>(filler_all_of(muon, "pt", "eta"), "muo_pt_eta_a_1", "", 20, 0.f, 300.f, 20, -2.5f, 2.5f);

  hist_1.make_histogram<TH1F>(filler_first_of(euu, "eu_dphi"), "eu_dphi_1", "", 20, 0.f, M_PI);
  hist_1.make_histogram<TH1F>(filler_first_of(euu, "eu_deta"), "eu_deta_1", "", 20, 0.f, 6.f);
  hist_1.make_histogram<TH1F>(filler_first_of(euu, "eu_mass"), "eu_mass_1", "", 20, 0.f, 300.f);
  hist_1.make_histogram<TH2F>(filler_first_of(euu, "eu_deta", "eu_dphi"), "eu_deta_dphi_1", "", 20, 0.f, 6.f, 20, 0.f, M_PI);

  hist_1.make_histogram<TH1F>(filler_first_of(euu, "lb_dphi"), "lb_dphi_1", "", 20, 0.f, M_PI);
  hist_1.make_histogram<TH1F>(filler_first_of(euu, "lb_deta"), "lb_deta_1", "", 20, 0.f, 6.f);
  hist_1.make_histogram<TH1F>(filler_first_of(euu, "lb_mass"), "lb_mass_1", "", 20, 0.f, 300.f);
  hist_1.make_histogram<TH2F>(filler_first_of(euu, "lb_deta", "lb_dphi"), "lb_deta_dphi_1", "", 20, 0.f, 6.f, 20, 0.f, M_PI);

  hist_1.make_histogram<TH1F>(filler_first_of(euu, "eub_mass"), "eub_mass_1", "", 100, 0.f, 1000.f);

  //const auto printer = [] (auto &p) {std::cout << p << " ";};
  //const auto printer4 = [] (auto &p1, auto &p2, auto &p3, auto &p4) {std::cout << p1 << " " << p2 << " " << p3 << " " << p4 << " :: ";};
  //const auto printer3 = [] (auto &p1, auto &p2, auto &p3) {std::cout << p1 << " " << p2 << " " << p3 << " :: ";};
  //const auto printer5 = [] (auto &p1, auto &p2, auto &p3, auto &p4, auto &p5) {
  //  std::cout << p1 << " " << p2 << " " << p3 << " " << p4 << " " << p5 << " :: ";
  //};

  std::array<int, 2> pass_trigger_3l = {0, 0};
  auto f_analyze = [&pass_trigger_3l, &hlt, &meta, &weight, &electron, &muon, &euu, &hist_1/*, &printer3, &printer5*/] (long long entry) mutable {
    meta.populate(entry);

    bool pass_trigger = false;
    for (auto &path : hlt) {
      auto bit = meta.filter_equal(path, true);
      //std::cout << path << "\n";
      //meta.iterate(printer, -1, -1, path);

      if (bit.size())
        pass_trigger = true;
    }

    if (pass_trigger)
      pass_trigger_3l[0] += 1;
    else
      return;

    weight.populate(entry);

    muon.populate(entry);
    muon.update_indices( muon.filter_greater("pt", 5.f) );
    muon.update_indices( muon.filter_in("eta", -2.4f, 2.4f) );
    muon.update_indices( muon.filter_equal("id_cutloose", true) );
    if (muon.n_elements() < 2)
      return;

    electron.populate(entry);
    electron.update_indices( electron.filter_greater("pt", 5.f) );
    electron.update_indices( electron.filter_in("sc_eta", -2.4f, 2.4f) );
    electron.update_indices( electron.filter_greater("id_cutbased", 0) );
    if (electron.n_elements() < 1)
      return;

    pass_trigger_3l[1] += 1;

    euu.populate(entry);
    if (euu.n_elements()) {
      hist_1.fill();
      /*
      std::cout << "electron \n";
      electron.iterate(printer5, -1, -1, "pt", "eta", "phi", "abs_pteta", "abs_ptphi");
      std::cout << "\nmuon \n";
      muon.update_indices(muon.sort_absolute_descending("sip3d"));
      muon.iterate(printer5, -1, -1, "pt", "eta", "phi", "charge", "sip3d");
      std::cout << "\neuu e u b eu \n";
      euu.iterate(printer3, -1, -1, "e_pt", "e_eta", "e_phi");
      euu.iterate(printer3, -1, -1, "u_pt", "u_eta", "u_phi");
      euu.iterate(printer3, -1, -1, "b_pt", "b_eta", "b_phi");
      euu.iterate(printer3, -1, -1, "eu_deta", "eu_dphi", "eu_dR");
      std::cout << "\n\n";
      */
    }
  };

  dat.set_analyzer(f_analyze);
  dat.analyze();
  std::cout << pass_trigger_3l[0] << " pass trigger\n";
  std::cout << pass_trigger_3l[1] << " also contain euu triplet" << std::endl;

  hist_1.save_as("smtt_bpark_euu.root");

  return 0;
}

