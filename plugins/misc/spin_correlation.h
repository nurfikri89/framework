#ifndef FWK_SPIN_CORRELATION_H
#define FWK_SPIN_CORRELATION_H

// -*- C++ -*-
// author: afiq anuar
// short: for computing ttbar spin correlation variables except dphi

#include "misc/function_util.h"
#include "TLorentzVector.h"

template <typename Number = float>
const std::vector<std::pair<std::string, Number>>& 
compute_spin_correlation(Number pTop_pt, Number pTop_eta, Number pTop_phi, Number pTop_m,
                         Number aTop_pt, Number aTop_eta, Number aTop_phi, Number aTop_m,
                         Number pLep_pt, Number pLep_eta, Number pLep_phi, Number pLep_m,
                         Number aLep_pt, Number aLep_eta, Number aLep_phi, Number aLep_m)
{
  static std::vector<std::pair<std::string, Number>> m_spin_corr;
  static int initialize = 0;
  if (initialize == 0) {
    m_spin_corr.reserve(96); // exact size
    m_spin_corr.emplace_back("cLab", -9999.);

    m_spin_corr.emplace_back("kdx", -9999.);
    m_spin_corr.emplace_back("kdy", -9999.);
    m_spin_corr.emplace_back("kdz", -9999.);

    m_spin_corr.emplace_back("rdx", -9999.);
    m_spin_corr.emplace_back("rdy", -9999.);
    m_spin_corr.emplace_back("rdz", -9999.);

    m_spin_corr.emplace_back("ndx", -9999.);
    m_spin_corr.emplace_back("ndy", -9999.);
    m_spin_corr.emplace_back("ndz", -9999.);

    m_spin_corr.emplace_back("b1k", -9999.);
    m_spin_corr.emplace_back("b2k", -9999.);

    m_spin_corr.emplace_back("b1j", -9999.);
    m_spin_corr.emplace_back("b2j", -9999.);

    m_spin_corr.emplace_back("b1r", -9999.);
    m_spin_corr.emplace_back("b2r", -9999.);

    m_spin_corr.emplace_back("b1q", -9999.);
    m_spin_corr.emplace_back("b2q", -9999.);

    m_spin_corr.emplace_back("b1n", -9999.);
    m_spin_corr.emplace_back("b2n", -9999.);

    m_spin_corr.emplace_back("b1x", -9999.);
    m_spin_corr.emplace_back("b2x", -9999.);

    m_spin_corr.emplace_back("b1y", -9999.);
    m_spin_corr.emplace_back("b2y", -9999.);

    m_spin_corr.emplace_back("b1z", -9999.);
    m_spin_corr.emplace_back("b2z", -9999.);

    m_spin_corr.emplace_back("bPkk", -9999.);
    m_spin_corr.emplace_back("bMkk", -9999.);

    m_spin_corr.emplace_back("bPjj", -9999.);
    m_spin_corr.emplace_back("bMjj", -9999.);

    m_spin_corr.emplace_back("bPrr", -9999.);
    m_spin_corr.emplace_back("bMrr", -9999.);

    m_spin_corr.emplace_back("bPqq", -9999.);
    m_spin_corr.emplace_back("bMqq", -9999.);

    m_spin_corr.emplace_back("bPnn", -9999.);
    m_spin_corr.emplace_back("bMnn", -9999.);

    m_spin_corr.emplace_back("bPxx", -9999.);
    m_spin_corr.emplace_back("bMxx", -9999.);

    m_spin_corr.emplace_back("bPyy", -9999.);
    m_spin_corr.emplace_back("bMyy", -9999.);

    m_spin_corr.emplace_back("bPzz", -9999.);
    m_spin_corr.emplace_back("bMzz", -9999.);

    m_spin_corr.emplace_back("ckk", -9999.);
    m_spin_corr.emplace_back("crr", -9999.);
    m_spin_corr.emplace_back("cnn", -9999.);

    m_spin_corr.emplace_back("crk", -9999.);
    m_spin_corr.emplace_back("ckr", -9999.);

    m_spin_corr.emplace_back("cnr", -9999.);
    m_spin_corr.emplace_back("crn", -9999.);

    m_spin_corr.emplace_back("cnk", -9999.);
    m_spin_corr.emplace_back("ckn", -9999.);

    m_spin_corr.emplace_back("cPrk", -9999.);
    m_spin_corr.emplace_back("cMrk", -9999.);

    m_spin_corr.emplace_back("cPnr", -9999.);
    m_spin_corr.emplace_back("cMnr", -9999.);

    m_spin_corr.emplace_back("cPnk", -9999.);
    m_spin_corr.emplace_back("cMnk", -9999.);

    m_spin_corr.emplace_back("cxx", -9999.);
    m_spin_corr.emplace_back("cyy", -9999.);
    m_spin_corr.emplace_back("czz", -9999.);

    m_spin_corr.emplace_back("cyx", -9999.);
    m_spin_corr.emplace_back("cxy", -9999.);

    m_spin_corr.emplace_back("czy", -9999.);
    m_spin_corr.emplace_back("cyz", -9999.);

    m_spin_corr.emplace_back("czx", -9999.);
    m_spin_corr.emplace_back("cxz", -9999.);

    m_spin_corr.emplace_back("cPyx", -9999.);
    m_spin_corr.emplace_back("cMyx", -9999.);

    m_spin_corr.emplace_back("cPzy", -9999.);
    m_spin_corr.emplace_back("cMzy", -9999.);

    m_spin_corr.emplace_back("cPzx", -9999.);
    m_spin_corr.emplace_back("cMzx", -9999.);

    m_spin_corr.emplace_back("cHel", -9999.);

    m_spin_corr.emplace_back("cHan", -9999.);
    m_spin_corr.emplace_back("cSca", -9999.);
    m_spin_corr.emplace_back("cTra", -9999.);

    m_spin_corr.emplace_back("crkP", -9999.);
    m_spin_corr.emplace_back("cnrP", -9999.);
    m_spin_corr.emplace_back("cnkP", -9999.);

    m_spin_corr.emplace_back("crkM", -9999.);
    m_spin_corr.emplace_back("cnrM", -9999.);
    m_spin_corr.emplace_back("cnkM", -9999.);

    m_spin_corr.emplace_back("cXxx", -9999.);
    m_spin_corr.emplace_back("cYyy", -9999.);
    m_spin_corr.emplace_back("cZzz", -9999.);

    m_spin_corr.emplace_back("cyxP", -9999.);
    m_spin_corr.emplace_back("czyP", -9999.);
    m_spin_corr.emplace_back("czxP", -9999.);

    m_spin_corr.emplace_back("cyxM", -9999.);
    m_spin_corr.emplace_back("czyM", -9999.);
    m_spin_corr.emplace_back("czxM", -9999.);

    m_spin_corr.emplace_back("kNorm", -9999.);
    m_spin_corr.emplace_back("rNorm", -9999.);
    m_spin_corr.emplace_back("nNorm", -9999.);

    m_spin_corr.emplace_back("phi0", -9999.);
    m_spin_corr.emplace_back("phi1", -9999.);

    ++initialize;
  }

  static std::array<Number, 16> arg;
  if (arg[0]  == pTop_pt and arg[1]  == pTop_eta and arg[2]  == pTop_phi and arg[3]  == pTop_m and 
      arg[4]  == aTop_pt and arg[5]  == aTop_eta and arg[6]  == aTop_phi and arg[7]  == aTop_m and 
      arg[8]  == pLep_pt and arg[9]  == pLep_eta and arg[10] == pLep_phi and arg[11] == pLep_m and 
      arg[12] == aLep_pt and arg[13] == aLep_eta and arg[14] == aLep_phi and arg[15] == aLep_m)
    return m_spin_corr;

  arg[0]  = pTop_pt; arg[1]  = pTop_eta; arg[2]  = pTop_phi; arg[3]  = pTop_m;
  arg[4]  = aTop_pt; arg[5]  = aTop_eta; arg[6]  = aTop_phi; arg[7]  = aTop_m;
  arg[8]  = pLep_pt; arg[9]  = pLep_eta; arg[10] = pLep_phi; arg[11] = pLep_m;
  arg[12] = aLep_pt; arg[13] = aLep_eta; arg[14] = aLep_phi; arg[15] = aLep_m;

  static TLorentzVector p4_pTop, p4_aTop, p4_pLep, p4_aLep;
  p4_pTop.SetPtEtaPhiM(arg[0],  arg[1],  arg[2],  arg[3]);
  p4_aTop.SetPtEtaPhiM(arg[4],  arg[5],  arg[6],  arg[7]);
  p4_pLep.SetPtEtaPhiM(arg[8],  arg[9],  arg[10], arg[11]);
  p4_aLep.SetPtEtaPhiM(arg[12], arg[13], arg[14], arg[15]);

  // computes spin correlation variables
  static const int icLab = index_with_key(m_spin_corr, "cLab");
  m_spin_corr[icLab].second = p4_aLep.Vect().Unit().Dot( p4_pLep.Vect().Unit() );

  // the various spin corr vars with boosting: Bernreuther 1508.05271
  // xyz coordinate system
  static const TVector3 xBase(1., 0., 0.);
  static const TVector3 yBase(0., 1., 0.);
  static const TVector3 zBase(0., 0., 1.);

  const TLorentzVector p4_TT( p4_pTop + p4_aTop );

  // should be const-ized, but Boost() doesn't work with copy ctors...
  TLorentzVector b4_pTop( p4_pTop );
  b4_pTop.Boost( -1. * p4_TT.BoostVector() );

  TLorentzVector b4_aTop( p4_aTop );
  b4_aTop.Boost( -1. * p4_TT.BoostVector() );

  TLorentzVector b4_aLep( p4_aLep );
  b4_aLep.Boost( -1. * p4_TT.BoostVector() );
  b4_aLep.Boost( -1. * b4_pTop.BoostVector() );

  TLorentzVector b4_pLep( p4_pLep );
  b4_pLep.Boost( -1. * p4_TT.BoostVector() );
  b4_pLep.Boost( -1. * b4_aTop.BoostVector() );

  // calculating the top-beam angle for pTop only (defining pP as the +z beam proton)
  const Number c_pTP = b4_pTop.Vect().Unit().Dot(zBase);
  const Number s_pTP = std::sqrt(1. - (c_pTP * c_pTP));

  // the signs needed to account for Bose symmetry
  const Number sY = (c_pTP >= 0.) ? 1. : -1.;
  const Number sD = ( std::abs(p4_pTop.Rapidity()) >= std::abs(p4_aTop.Rapidity()) ) ? 1. : -1.;

  // define the base vectors a
  // j and q base are the k* and r* respectively
  // b is always -a
  const TVector3 kBase = b4_pTop.Vect().Unit();
  const TVector3 jBase = sD * kBase;
  const TVector3 rBase = ( (sY / s_pTP) * (zBase - (c_pTP * kBase)) ).Unit();
  const TVector3 qBase = sD * rBase;
  const TVector3 nBase = ( (sY / s_pTP) * zBase.Cross(kBase) ).Unit();

  // for resolution studies
  // naming eg ndx for n dot x -> x component of the n axis
  static const int ikdx = index_with_key(m_spin_corr, "kdx");
  static const int ikdy = index_with_key(m_spin_corr, "kdy");
  static const int ikdz = index_with_key(m_spin_corr, "kdz");

  static const int irdx = index_with_key(m_spin_corr, "rdx");
  static const int irdy = index_with_key(m_spin_corr, "rdy");
  static const int irdz = index_with_key(m_spin_corr, "rdz");

  static const int indx = index_with_key(m_spin_corr, "ndx");
  static const int indy = index_with_key(m_spin_corr, "ndy");
  static const int indz = index_with_key(m_spin_corr, "ndz");

  m_spin_corr[ikdx].second = kBase.x();
  m_spin_corr[ikdy].second = kBase.y();
  m_spin_corr[ikdz].second = kBase.z();

  m_spin_corr[irdx].second = rBase.x();
  m_spin_corr[irdy].second = rBase.y();
  m_spin_corr[irdz].second = rBase.z();

  m_spin_corr[indx].second = nBase.x();
  m_spin_corr[indy].second = nBase.y();
  m_spin_corr[indz].second = nBase.z();

  // find the polarization angles along bases
  static const int ib1k = index_with_key(m_spin_corr, "b1k");
  static const int ib2k = index_with_key(m_spin_corr, "b2k");

  static const int ib1j = index_with_key(m_spin_corr, "b1j");
  static const int ib2j = index_with_key(m_spin_corr, "b2j");

  static const int ib1r = index_with_key(m_spin_corr, "b1r");
  static const int ib2r = index_with_key(m_spin_corr, "b2r");

  static const int ib1q = index_with_key(m_spin_corr, "b1q");
  static const int ib2q = index_with_key(m_spin_corr, "b2q");

  static const int ib1n = index_with_key(m_spin_corr, "b1n");
  static const int ib2n = index_with_key(m_spin_corr, "b2n");

  static const int ib1x = index_with_key(m_spin_corr, "b1x");
  static const int ib2x = index_with_key(m_spin_corr, "b2x");

  static const int ib1y = index_with_key(m_spin_corr, "b1y");
  static const int ib2y = index_with_key(m_spin_corr, "b2y");

  static const int ib1z = index_with_key(m_spin_corr, "b1z");
  static const int ib2z = index_with_key(m_spin_corr, "b2z");

  m_spin_corr[ib1k].second = b4_aLep.Vect().Unit().Dot( kBase );
  m_spin_corr[ib2k].second = b4_pLep.Vect().Unit().Dot( -1. * kBase );

  m_spin_corr[ib1j].second = b4_aLep.Vect().Unit().Dot( jBase );
  m_spin_corr[ib2j].second = b4_pLep.Vect().Unit().Dot( -1. * jBase );

  m_spin_corr[ib1r].second = b4_aLep.Vect().Unit().Dot( rBase );
  m_spin_corr[ib2r].second = b4_pLep.Vect().Unit().Dot( -1. * rBase );

  m_spin_corr[ib1q].second = b4_aLep.Vect().Unit().Dot( qBase );
  m_spin_corr[ib2q].second = b4_pLep.Vect().Unit().Dot( -1. * qBase );

  m_spin_corr[ib1n].second = b4_aLep.Vect().Unit().Dot( nBase );
  m_spin_corr[ib2n].second = b4_pLep.Vect().Unit().Dot( -1. * nBase );

  m_spin_corr[ib1x].second = b4_aLep.Vect().Unit().Dot( xBase );
  m_spin_corr[ib2x].second = b4_pLep.Vect().Unit().Dot( -1. * xBase );

  m_spin_corr[ib1y].second = b4_aLep.Vect().Unit().Dot( yBase );
  m_spin_corr[ib2y].second = b4_pLep.Vect().Unit().Dot( -1. * yBase );

  m_spin_corr[ib1z].second = b4_aLep.Vect().Unit().Dot( zBase );
  m_spin_corr[ib2z].second = b4_pLep.Vect().Unit().Dot( -1. * zBase );

  // sums and differences of the polarization angles
  static const int ibPkk = index_with_key(m_spin_corr, "bPkk");
  static const int ibMkk = index_with_key(m_spin_corr, "bMkk");

  static const int ibPjj = index_with_key(m_spin_corr, "bPjj");
  static const int ibMjj = index_with_key(m_spin_corr, "bMjj");

  static const int ibPrr = index_with_key(m_spin_corr, "bPrr");
  static const int ibMrr = index_with_key(m_spin_corr, "bMrr");

  static const int ibPqq = index_with_key(m_spin_corr, "bPqq");
  static const int ibMqq = index_with_key(m_spin_corr, "bMqq");

  static const int ibPnn = index_with_key(m_spin_corr, "bPnn");
  static const int ibMnn = index_with_key(m_spin_corr, "bMnn");

  static const int ibPxx = index_with_key(m_spin_corr, "bPxx");
  static const int ibMxx = index_with_key(m_spin_corr, "bMxx");

  static const int ibPyy = index_with_key(m_spin_corr, "bPyy");
  static const int ibMyy = index_with_key(m_spin_corr, "bMyy");

  static const int ibPzz = index_with_key(m_spin_corr, "bPzz");
  static const int ibMzz = index_with_key(m_spin_corr, "bMzz");

  m_spin_corr[ibPkk].second = m_spin_corr[ib1k].second + m_spin_corr[ib2k].second;
  m_spin_corr[ibMkk].second = m_spin_corr[ib1k].second - m_spin_corr[ib2k].second;

  m_spin_corr[ibPjj].second = m_spin_corr[ib1j].second + m_spin_corr[ib2j].second;
  m_spin_corr[ibMjj].second = m_spin_corr[ib1j].second - m_spin_corr[ib2j].second;

  m_spin_corr[ibPrr].second = m_spin_corr[ib1r].second + m_spin_corr[ib2r].second;
  m_spin_corr[ibMrr].second = m_spin_corr[ib1r].second - m_spin_corr[ib2r].second;

  m_spin_corr[ibPqq].second = m_spin_corr[ib1q].second + m_spin_corr[ib2q].second;
  m_spin_corr[ibMqq].second = m_spin_corr[ib1q].second - m_spin_corr[ib2q].second;

  m_spin_corr[ibPnn].second = m_spin_corr[ib1n].second + m_spin_corr[ib2n].second;
  m_spin_corr[ibMnn].second = m_spin_corr[ib1n].second - m_spin_corr[ib2n].second;

  m_spin_corr[ibPxx].second = m_spin_corr[ib1x].second + m_spin_corr[ib2x].second;
  m_spin_corr[ibMxx].second = m_spin_corr[ib1x].second - m_spin_corr[ib2x].second;

  m_spin_corr[ibPyy].second = m_spin_corr[ib1y].second + m_spin_corr[ib2y].second;
  m_spin_corr[ibMyy].second = m_spin_corr[ib1y].second - m_spin_corr[ib2y].second;

  m_spin_corr[ibPzz].second = m_spin_corr[ib1z].second + m_spin_corr[ib2z].second;
  m_spin_corr[ibMzz].second = m_spin_corr[ib1z].second - m_spin_corr[ib2z].second;

  // Cab = -9<cab>
  static const int ickk = index_with_key(m_spin_corr, "ckk");
  static const int icrr = index_with_key(m_spin_corr, "crr");
  static const int icnn = index_with_key(m_spin_corr, "cnn");

  static const int icrk = index_with_key(m_spin_corr, "crk");
  static const int ickr = index_with_key(m_spin_corr, "ckr");

  static const int icnr = index_with_key(m_spin_corr, "cnr");
  static const int icrn = index_with_key(m_spin_corr, "crn");

  static const int icnk = index_with_key(m_spin_corr, "cnk");
  static const int ickn = index_with_key(m_spin_corr, "ckn");

  static const int icxx = index_with_key(m_spin_corr, "cxx");
  static const int icyy = index_with_key(m_spin_corr, "cyy");
  static const int iczz = index_with_key(m_spin_corr, "czz");

  static const int icyx = index_with_key(m_spin_corr, "cyx");
  static const int icxy = index_with_key(m_spin_corr, "cxy");

  static const int iczy = index_with_key(m_spin_corr, "czy");
  static const int icyz = index_with_key(m_spin_corr, "cyz");

  static const int iczx = index_with_key(m_spin_corr, "czx");
  static const int icxz = index_with_key(m_spin_corr, "cxz");

  m_spin_corr[ickk].second = m_spin_corr[ib1k].second * m_spin_corr[ib2k].second;
  m_spin_corr[icrr].second = m_spin_corr[ib1r].second * m_spin_corr[ib2r].second;
  m_spin_corr[icnn].second = m_spin_corr[ib1n].second * m_spin_corr[ib2n].second;

  m_spin_corr[icrk].second = m_spin_corr[ib1r].second * m_spin_corr[ib2k].second;
  m_spin_corr[ickr].second = m_spin_corr[ib1k].second * m_spin_corr[ib2r].second;

  m_spin_corr[icnr].second = m_spin_corr[ib1n].second * m_spin_corr[ib2r].second;
  m_spin_corr[icrn].second = m_spin_corr[ib1r].second * m_spin_corr[ib2n].second;

  m_spin_corr[icnk].second = m_spin_corr[ib1n].second * m_spin_corr[ib2k].second;
  m_spin_corr[ickn].second = m_spin_corr[ib1k].second * m_spin_corr[ib2n].second;

  m_spin_corr[icxx].second = m_spin_corr[ib1x].second * m_spin_corr[ib2x].second;
  m_spin_corr[icyy].second = m_spin_corr[ib1y].second * m_spin_corr[ib2y].second;
  m_spin_corr[iczz].second = m_spin_corr[ib1z].second * m_spin_corr[ib2z].second;

  m_spin_corr[icyx].second = m_spin_corr[ib1y].second * m_spin_corr[ib2x].second;
  m_spin_corr[icxy].second = m_spin_corr[ib1x].second * m_spin_corr[ib2y].second;

  m_spin_corr[iczy].second = m_spin_corr[ib1z].second * m_spin_corr[ib2y].second;
  m_spin_corr[icyz].second = m_spin_corr[ib1y].second * m_spin_corr[ib2z].second;

  m_spin_corr[iczx].second = m_spin_corr[ib1z].second * m_spin_corr[ib2x].second;
  m_spin_corr[icxz].second = m_spin_corr[ib1x].second * m_spin_corr[ib2z].second;

  // sums and differences of cij
  static const int icPrk = index_with_key(m_spin_corr, "cPrk");
  static const int icMrk = index_with_key(m_spin_corr, "cMrk");

  static const int icPnr = index_with_key(m_spin_corr, "cPnr");
  static const int icMnr = index_with_key(m_spin_corr, "cMnr");

  static const int icPnk = index_with_key(m_spin_corr, "cPnk");
  static const int icMnk = index_with_key(m_spin_corr, "cMnk");

  static const int icPyx = index_with_key(m_spin_corr, "cPyx");
  static const int icMyx = index_with_key(m_spin_corr, "cMyx");

  static const int icPzy = index_with_key(m_spin_corr, "cPzy");
  static const int icMzy = index_with_key(m_spin_corr, "cMzy");

  static const int icPzx = index_with_key(m_spin_corr, "cPzx");
  static const int icMzx = index_with_key(m_spin_corr, "cMzx");

  m_spin_corr[icPrk].second = m_spin_corr[icrk].second + m_spin_corr[ickr].second;
  m_spin_corr[icMrk].second = m_spin_corr[icrk].second - m_spin_corr[ickr].second;

  m_spin_corr[icPnr].second = m_spin_corr[icnr].second + m_spin_corr[icrn].second;
  m_spin_corr[icMnr].second = m_spin_corr[icnr].second - m_spin_corr[icrn].second;

  m_spin_corr[icPnk].second = m_spin_corr[icnk].second + m_spin_corr[ickn].second;
  m_spin_corr[icMnk].second = m_spin_corr[icnk].second - m_spin_corr[ickn].second;

  m_spin_corr[icPyx].second = m_spin_corr[icyx].second + m_spin_corr[icxy].second;
  m_spin_corr[icMyx].second = m_spin_corr[icyx].second - m_spin_corr[icxy].second;

  m_spin_corr[icPzy].second = m_spin_corr[iczy].second + m_spin_corr[icyz].second;
  m_spin_corr[icMzy].second = m_spin_corr[iczy].second - m_spin_corr[icyz].second;

  m_spin_corr[icPzx].second = m_spin_corr[iczx].second + m_spin_corr[icxz].second;
  m_spin_corr[icMzx].second = m_spin_corr[iczx].second - m_spin_corr[icxz].second;

  // opening angle between the spin vectors
  static const int icHel = index_with_key(m_spin_corr, "cHel");
  m_spin_corr[icHel].second = b4_aLep.Vect().Unit().Dot( b4_pLep.Vect().Unit() );

  // cHel with one spin vector flipped about a given axis
  // useful to measure Cii = 1.5(Di - D)
  // where Di is the coeff for these flipped cHel
  static const int icHan = index_with_key(m_spin_corr, "cHan");
  static const int icSca = index_with_key(m_spin_corr, "cSca");
  static const int icTra = index_with_key(m_spin_corr, "cTra");

  m_spin_corr[icHan].second = 0. + m_spin_corr[ickk].second - m_spin_corr[icrr].second - m_spin_corr[icnn].second;
  m_spin_corr[icSca].second = 0. - m_spin_corr[ickk].second + m_spin_corr[icrr].second - m_spin_corr[icnn].second;
  m_spin_corr[icTra].second = 0. - m_spin_corr[ickk].second - m_spin_corr[icrr].second + m_spin_corr[icnn].second;

  // cHel with one of the spin vectors having two of its components swapped
  // in other words, flipped about the bisector of the i and j axes
  // useful to measure Cij + Cji = -3Dij - Ckk for axes i, j and k
  static const int icrkP = index_with_key(m_spin_corr, "crkP");
  static const int icnrP = index_with_key(m_spin_corr, "cnrP");
  static const int icnkP = index_with_key(m_spin_corr, "cnkP");

  m_spin_corr[icnrP].second = 0. - m_spin_corr[ickk].second - m_spin_corr[icnr].second - m_spin_corr[icrn].second;
  m_spin_corr[icnkP].second = 0. - m_spin_corr[icnk].second - m_spin_corr[icrr].second - m_spin_corr[ickn].second;
  m_spin_corr[icrkP].second = 0. - m_spin_corr[icrk].second - m_spin_corr[ickr].second - m_spin_corr[icnn].second;

  // the above naturally lends itself to a measurement of Cij - Cji
  // with swapping and also sign flipping
  static const int icrkM = index_with_key(m_spin_corr, "crkM");
  static const int icnrM = index_with_key(m_spin_corr, "cnrM");
  static const int icnkM = index_with_key(m_spin_corr, "cnkM");

  m_spin_corr[icnrM].second = 0. - m_spin_corr[ickk].second - m_spin_corr[icnr].second + m_spin_corr[icrn].second;
  m_spin_corr[icnkM].second = 0. - m_spin_corr[icnk].second - m_spin_corr[icrr].second + m_spin_corr[ickn].second;
  m_spin_corr[icrkM].second = 0. - m_spin_corr[icrk].second + m_spin_corr[ickr].second - m_spin_corr[icnn].second;

  // the flipped cHel in the xyz system
  static const int icXxx = index_with_key(m_spin_corr, "cXxx");
  static const int icYyy = index_with_key(m_spin_corr, "cYyy");
  static const int icZzz = index_with_key(m_spin_corr, "cZzz");

  m_spin_corr[icXxx].second = 0. + m_spin_corr[icxx].second - m_spin_corr[icyy].second - m_spin_corr[iczz].second;
  m_spin_corr[icYyy].second = 0. - m_spin_corr[icxx].second + m_spin_corr[icyy].second - m_spin_corr[iczz].second;
  m_spin_corr[icZzz].second = 0. - m_spin_corr[icxx].second - m_spin_corr[icyy].second + m_spin_corr[iczz].second;

  static const int icyxP = index_with_key(m_spin_corr, "cyxP");
  static const int iczyP = index_with_key(m_spin_corr, "czyP");
  static const int iczxP = index_with_key(m_spin_corr, "czxP");

  m_spin_corr[iczyP].second = 0. - m_spin_corr[icxx].second - m_spin_corr[iczy].second - m_spin_corr[icyz].second;
  m_spin_corr[iczxP].second = 0. - m_spin_corr[iczx].second - m_spin_corr[icyy].second - m_spin_corr[icxz].second;
  m_spin_corr[icyxP].second = 0. - m_spin_corr[icyx].second - m_spin_corr[icxy].second - m_spin_corr[iczz].second;

  static const int icyxM = index_with_key(m_spin_corr, "cyxM");
  static const int iczyM = index_with_key(m_spin_corr, "czyM");
  static const int iczxM = index_with_key(m_spin_corr, "czxM");

  m_spin_corr[iczyM].second = 0. - m_spin_corr[icxx].second - m_spin_corr[iczy].second + m_spin_corr[icyz].second;
  m_spin_corr[iczxM].second = 0. - m_spin_corr[iczx].second - m_spin_corr[icyy].second + m_spin_corr[icxz].second;
  m_spin_corr[icyxM].second = 0. - m_spin_corr[icyx].second + m_spin_corr[icxy].second - m_spin_corr[iczz].second;

  // these are the O_CP1 and O_CP2 as in page 18 (why not O_CP3 with n base too)
  static const int ikNorm = index_with_key(m_spin_corr, "kNorm");
  static const int irNorm = index_with_key(m_spin_corr, "rNorm");
  static const int inNorm = index_with_key(m_spin_corr, "nNorm");

  const TVector3 llNorm = b4_aLep.Vect().Unit().Cross( b4_pLep.Vect().Unit() );
  m_spin_corr[ikNorm].second =  llNorm.Dot( kBase );
  m_spin_corr[irNorm].second =  llNorm.Dot( rBase );
  m_spin_corr[inNorm].second =  llNorm.Dot( nBase );

  // angles as in 1702.06063; phi0 = phi* and phi1 = phi*_CP
  // sensitive to CP mixtures (shows up as a phase in the distributions)
  static const int iphi0 = index_with_key(m_spin_corr, "phi0");
  static const int iphi1 = index_with_key(m_spin_corr, "phi1");

  const TVector3 t3_aLep = ( b4_aLep.Vect().Unit() - (m_spin_corr[ib1k].second * kBase) ).Unit();
  const TVector3 t3_pLep = ( b4_pLep.Vect().Unit() - (-1. * m_spin_corr[ib2k].second * kBase) ).Unit();

  m_spin_corr[iphi0].second = std::acos(t3_aLep.Dot(t3_pLep));
  m_spin_corr[iphi1].second = (m_spin_corr[ikNorm].second < 0.) ? (2. * M_PI) - m_spin_corr[iphi0].second : m_spin_corr[iphi0].second;

  return m_spin_corr;
}



template <typename Number = float>
Number cLab(Number pTop_pt, Number pTop_eta, Number pTop_phi, Number pTop_m,
            Number aTop_pt, Number aTop_eta, Number aTop_phi, Number aTop_m,
            Number pLep_pt, Number pLep_eta, Number pLep_phi, Number pLep_m,
            Number aLep_pt, Number aLep_eta, Number aLep_phi, Number aLep_m)
{
  const auto &map = compute_spin_correlation(pTop_pt, pTop_eta, pTop_phi, pTop_m,
                                             aTop_pt, aTop_eta, aTop_phi, aTop_m,
                                             pLep_pt, pLep_eta, pLep_phi, pLep_m,
                                             aLep_pt, aLep_eta, aLep_phi, aLep_m);

  static const int i = index_with_key(map, "cLab");
  return map[i].second;
}



template <typename Number = float>
Number b1k(Number pTop_pt, Number pTop_eta, Number pTop_phi, Number pTop_m,
           Number aTop_pt, Number aTop_eta, Number aTop_phi, Number aTop_m,
           Number pLep_pt, Number pLep_eta, Number pLep_phi, Number pLep_m,
           Number aLep_pt, Number aLep_eta, Number aLep_phi, Number aLep_m)
{
  const auto &map = compute_spin_correlation(pTop_pt, pTop_eta, pTop_phi, pTop_m,
                                             aTop_pt, aTop_eta, aTop_phi, aTop_m,
                                             pLep_pt, pLep_eta, pLep_phi, pLep_m,
                                             aLep_pt, aLep_eta, aLep_phi, aLep_m);

  static const int i = index_with_key(map, "b1k");
  return map[i].second;
}



template <typename Number = float>
Number b2k(Number pTop_pt, Number pTop_eta, Number pTop_phi, Number pTop_m,
           Number aTop_pt, Number aTop_eta, Number aTop_phi, Number aTop_m,
           Number pLep_pt, Number pLep_eta, Number pLep_phi, Number pLep_m,
           Number aLep_pt, Number aLep_eta, Number aLep_phi, Number aLep_m)
{
  const auto &map = compute_spin_correlation(pTop_pt, pTop_eta, pTop_phi, pTop_m,
                                             aTop_pt, aTop_eta, aTop_phi, aTop_m,
                                             pLep_pt, pLep_eta, pLep_phi, pLep_m,
                                             aLep_pt, aLep_eta, aLep_phi, aLep_m);

  static const int i = index_with_key(map, "b2k");
  return map[i].second;
}



template <typename Number = float>
Number b1r(Number pTop_pt, Number pTop_eta, Number pTop_phi, Number pTop_m,
           Number aTop_pt, Number aTop_eta, Number aTop_phi, Number aTop_m,
           Number pLep_pt, Number pLep_eta, Number pLep_phi, Number pLep_m,
           Number aLep_pt, Number aLep_eta, Number aLep_phi, Number aLep_m)
{
  const auto &map = compute_spin_correlation(pTop_pt, pTop_eta, pTop_phi, pTop_m,
                                             aTop_pt, aTop_eta, aTop_phi, aTop_m,
                                             pLep_pt, pLep_eta, pLep_phi, pLep_m,
                                             aLep_pt, aLep_eta, aLep_phi, aLep_m);

  static const int i = index_with_key(map, "b1r");
  return map[i].second;
}



template <typename Number = float>
Number b2r(Number pTop_pt, Number pTop_eta, Number pTop_phi, Number pTop_m,
           Number aTop_pt, Number aTop_eta, Number aTop_phi, Number aTop_m,
           Number pLep_pt, Number pLep_eta, Number pLep_phi, Number pLep_m,
           Number aLep_pt, Number aLep_eta, Number aLep_phi, Number aLep_m)
{
  const auto &map = compute_spin_correlation(pTop_pt, pTop_eta, pTop_phi, pTop_m,
                                             aTop_pt, aTop_eta, aTop_phi, aTop_m,
                                             pLep_pt, pLep_eta, pLep_phi, pLep_m,
                                             aLep_pt, aLep_eta, aLep_phi, aLep_m);

  static const int i = index_with_key(map, "b2r");
  return map[i].second;
}



template <typename Number = float>
Number b1n(Number pTop_pt, Number pTop_eta, Number pTop_phi, Number pTop_m,
           Number aTop_pt, Number aTop_eta, Number aTop_phi, Number aTop_m,
           Number pLep_pt, Number pLep_eta, Number pLep_phi, Number pLep_m,
           Number aLep_pt, Number aLep_eta, Number aLep_phi, Number aLep_m)
{
  const auto &map = compute_spin_correlation(pTop_pt, pTop_eta, pTop_phi, pTop_m,
                                             aTop_pt, aTop_eta, aTop_phi, aTop_m,
                                             pLep_pt, pLep_eta, pLep_phi, pLep_m,
                                             aLep_pt, aLep_eta, aLep_phi, aLep_m);

  static const int i = index_with_key(map, "b1n");
  return map[i].second;
}



template <typename Number = float>
Number b2n(Number pTop_pt, Number pTop_eta, Number pTop_phi, Number pTop_m,
           Number aTop_pt, Number aTop_eta, Number aTop_phi, Number aTop_m,
           Number pLep_pt, Number pLep_eta, Number pLep_phi, Number pLep_m,
           Number aLep_pt, Number aLep_eta, Number aLep_phi, Number aLep_m)
{
  const auto &map = compute_spin_correlation(pTop_pt, pTop_eta, pTop_phi, pTop_m,
                                             aTop_pt, aTop_eta, aTop_phi, aTop_m,
                                             pLep_pt, pLep_eta, pLep_phi, pLep_m,
                                             aLep_pt, aLep_eta, aLep_phi, aLep_m);

  static const int i = index_with_key(map, "b2n");
  return map[i].second;
}



template <typename Number = float>
Number b1j(Number pTop_pt, Number pTop_eta, Number pTop_phi, Number pTop_m,
           Number aTop_pt, Number aTop_eta, Number aTop_phi, Number aTop_m,
           Number pLep_pt, Number pLep_eta, Number pLep_phi, Number pLep_m,
           Number aLep_pt, Number aLep_eta, Number aLep_phi, Number aLep_m)
{
  const auto &map = compute_spin_correlation(pTop_pt, pTop_eta, pTop_phi, pTop_m,
                                             aTop_pt, aTop_eta, aTop_phi, aTop_m,
                                             pLep_pt, pLep_eta, pLep_phi, pLep_m,
                                             aLep_pt, aLep_eta, aLep_phi, aLep_m);

  static const int i = index_with_key(map, "b1j");
  return map[i].second;
}



template <typename Number = float>
Number b2j(Number pTop_pt, Number pTop_eta, Number pTop_phi, Number pTop_m,
           Number aTop_pt, Number aTop_eta, Number aTop_phi, Number aTop_m,
           Number pLep_pt, Number pLep_eta, Number pLep_phi, Number pLep_m,
           Number aLep_pt, Number aLep_eta, Number aLep_phi, Number aLep_m)
{
  const auto &map = compute_spin_correlation(pTop_pt, pTop_eta, pTop_phi, pTop_m,
                                             aTop_pt, aTop_eta, aTop_phi, aTop_m,
                                             pLep_pt, pLep_eta, pLep_phi, pLep_m,
                                             aLep_pt, aLep_eta, aLep_phi, aLep_m);

  static const int i = index_with_key(map, "b2j");
  return map[i].second;
}



template <typename Number = float>
Number b1q(Number pTop_pt, Number pTop_eta, Number pTop_phi, Number pTop_m,
           Number aTop_pt, Number aTop_eta, Number aTop_phi, Number aTop_m,
           Number pLep_pt, Number pLep_eta, Number pLep_phi, Number pLep_m,
           Number aLep_pt, Number aLep_eta, Number aLep_phi, Number aLep_m)
{
  const auto &map = compute_spin_correlation(pTop_pt, pTop_eta, pTop_phi, pTop_m,
                                             aTop_pt, aTop_eta, aTop_phi, aTop_m,
                                             pLep_pt, pLep_eta, pLep_phi, pLep_m,
                                             aLep_pt, aLep_eta, aLep_phi, aLep_m);

  static const int i = index_with_key(map, "b1q");
  return map[i].second;
}



template <typename Number = float>
Number b2q(Number pTop_pt, Number pTop_eta, Number pTop_phi, Number pTop_m,
           Number aTop_pt, Number aTop_eta, Number aTop_phi, Number aTop_m,
           Number pLep_pt, Number pLep_eta, Number pLep_phi, Number pLep_m,
           Number aLep_pt, Number aLep_eta, Number aLep_phi, Number aLep_m)
{
  const auto &map = compute_spin_correlation(pTop_pt, pTop_eta, pTop_phi, pTop_m,
                                             aTop_pt, aTop_eta, aTop_phi, aTop_m,
                                             pLep_pt, pLep_eta, pLep_phi, pLep_m,
                                             aLep_pt, aLep_eta, aLep_phi, aLep_m);

  static const int i = index_with_key(map, "b2q");
  return map[i].second;
}



template <typename Number = float>
Number ckk(Number pTop_pt, Number pTop_eta, Number pTop_phi, Number pTop_m,
           Number aTop_pt, Number aTop_eta, Number aTop_phi, Number aTop_m,
           Number pLep_pt, Number pLep_eta, Number pLep_phi, Number pLep_m,
           Number aLep_pt, Number aLep_eta, Number aLep_phi, Number aLep_m)
{
  const auto &map = compute_spin_correlation(pTop_pt, pTop_eta, pTop_phi, pTop_m,
                                             aTop_pt, aTop_eta, aTop_phi, aTop_m,
                                             pLep_pt, pLep_eta, pLep_phi, pLep_m,
                                             aLep_pt, aLep_eta, aLep_phi, aLep_m);

  static const int i = index_with_key(map, "ckk");
  return map[i].second;
}



template <typename Number = float>
Number crr(Number pTop_pt, Number pTop_eta, Number pTop_phi, Number pTop_m,
           Number aTop_pt, Number aTop_eta, Number aTop_phi, Number aTop_m,
           Number pLep_pt, Number pLep_eta, Number pLep_phi, Number pLep_m,
           Number aLep_pt, Number aLep_eta, Number aLep_phi, Number aLep_m)
{
  const auto &map = compute_spin_correlation(pTop_pt, pTop_eta, pTop_phi, pTop_m,
                                             aTop_pt, aTop_eta, aTop_phi, aTop_m,
                                             pLep_pt, pLep_eta, pLep_phi, pLep_m,
                                             aLep_pt, aLep_eta, aLep_phi, aLep_m);

  static const int i = index_with_key(map, "crr");
  return map[i].second;
}



template <typename Number = float>
Number cnn(Number pTop_pt, Number pTop_eta, Number pTop_phi, Number pTop_m,
           Number aTop_pt, Number aTop_eta, Number aTop_phi, Number aTop_m,
           Number pLep_pt, Number pLep_eta, Number pLep_phi, Number pLep_m,
           Number aLep_pt, Number aLep_eta, Number aLep_phi, Number aLep_m)
{
  const auto &map = compute_spin_correlation(pTop_pt, pTop_eta, pTop_phi, pTop_m,
                                             aTop_pt, aTop_eta, aTop_phi, aTop_m,
                                             pLep_pt, pLep_eta, pLep_phi, pLep_m,
                                             aLep_pt, aLep_eta, aLep_phi, aLep_m);

  static const int i = index_with_key(map, "cnn");
  return map[i].second;
}



template <typename Number = float>
Number cPrk(Number pTop_pt, Number pTop_eta, Number pTop_phi, Number pTop_m,
            Number aTop_pt, Number aTop_eta, Number aTop_phi, Number aTop_m,
            Number pLep_pt, Number pLep_eta, Number pLep_phi, Number pLep_m,
            Number aLep_pt, Number aLep_eta, Number aLep_phi, Number aLep_m)
{
  const auto &map = compute_spin_correlation(pTop_pt, pTop_eta, pTop_phi, pTop_m,
                                             aTop_pt, aTop_eta, aTop_phi, aTop_m,
                                             pLep_pt, pLep_eta, pLep_phi, pLep_m,
                                             aLep_pt, aLep_eta, aLep_phi, aLep_m);

  static const int i = index_with_key(map, "cPrk");
  return map[i].second;
}



template <typename Number = float>
Number cMrk(Number pTop_pt, Number pTop_eta, Number pTop_phi, Number pTop_m,
            Number aTop_pt, Number aTop_eta, Number aTop_phi, Number aTop_m,
            Number pLep_pt, Number pLep_eta, Number pLep_phi, Number pLep_m,
            Number aLep_pt, Number aLep_eta, Number aLep_phi, Number aLep_m)
{
  const auto &map = compute_spin_correlation(pTop_pt, pTop_eta, pTop_phi, pTop_m,
                                             aTop_pt, aTop_eta, aTop_phi, aTop_m,
                                             pLep_pt, pLep_eta, pLep_phi, pLep_m,
                                             aLep_pt, aLep_eta, aLep_phi, aLep_m);

  static const int i = index_with_key(map, "cMrk");
  return map[i].second;
}



template <typename Number = float>
Number cPnr(Number pTop_pt, Number pTop_eta, Number pTop_phi, Number pTop_m,
            Number aTop_pt, Number aTop_eta, Number aTop_phi, Number aTop_m,
            Number pLep_pt, Number pLep_eta, Number pLep_phi, Number pLep_m,
            Number aLep_pt, Number aLep_eta, Number aLep_phi, Number aLep_m)
{
  const auto &map = compute_spin_correlation(pTop_pt, pTop_eta, pTop_phi, pTop_m,
                                             aTop_pt, aTop_eta, aTop_phi, aTop_m,
                                             pLep_pt, pLep_eta, pLep_phi, pLep_m,
                                             aLep_pt, aLep_eta, aLep_phi, aLep_m);

  static const int i = index_with_key(map, "cPnr");
  return map[i].second;
}



template <typename Number = float>
Number cMnr(Number pTop_pt, Number pTop_eta, Number pTop_phi, Number pTop_m,
            Number aTop_pt, Number aTop_eta, Number aTop_phi, Number aTop_m,
            Number pLep_pt, Number pLep_eta, Number pLep_phi, Number pLep_m,
            Number aLep_pt, Number aLep_eta, Number aLep_phi, Number aLep_m)
{
  const auto &map = compute_spin_correlation(pTop_pt, pTop_eta, pTop_phi, pTop_m,
                                             aTop_pt, aTop_eta, aTop_phi, aTop_m,
                                             pLep_pt, pLep_eta, pLep_phi, pLep_m,
                                             aLep_pt, aLep_eta, aLep_phi, aLep_m);

  static const int i = index_with_key(map, "cMnr");
  return map[i].second;
}



template <typename Number = float>
Number cPnk(Number pTop_pt, Number pTop_eta, Number pTop_phi, Number pTop_m,
            Number aTop_pt, Number aTop_eta, Number aTop_phi, Number aTop_m,
            Number pLep_pt, Number pLep_eta, Number pLep_phi, Number pLep_m,
            Number aLep_pt, Number aLep_eta, Number aLep_phi, Number aLep_m)
{
  const auto &map = compute_spin_correlation(pTop_pt, pTop_eta, pTop_phi, pTop_m,
                                             aTop_pt, aTop_eta, aTop_phi, aTop_m,
                                             pLep_pt, pLep_eta, pLep_phi, pLep_m,
                                             aLep_pt, aLep_eta, aLep_phi, aLep_m);

  static const int i = index_with_key(map, "cPnk");
  return map[i].second;
}



template <typename Number = float>
Number cMnk(Number pTop_pt, Number pTop_eta, Number pTop_phi, Number pTop_m,
            Number aTop_pt, Number aTop_eta, Number aTop_phi, Number aTop_m,
            Number pLep_pt, Number pLep_eta, Number pLep_phi, Number pLep_m,
            Number aLep_pt, Number aLep_eta, Number aLep_phi, Number aLep_m)
{
  const auto &map = compute_spin_correlation(pTop_pt, pTop_eta, pTop_phi, pTop_m,
                                             aTop_pt, aTop_eta, aTop_phi, aTop_m,
                                             pLep_pt, pLep_eta, pLep_phi, pLep_m,
                                             aLep_pt, aLep_eta, aLep_phi, aLep_m);

  static const int i = index_with_key(map, "cMnk");
  return map[i].second;
}



template <typename Number = float>
Number cHel(Number pTop_pt, Number pTop_eta, Number pTop_phi, Number pTop_m,
            Number aTop_pt, Number aTop_eta, Number aTop_phi, Number aTop_m,
            Number pLep_pt, Number pLep_eta, Number pLep_phi, Number pLep_m,
            Number aLep_pt, Number aLep_eta, Number aLep_phi, Number aLep_m)
{
  const auto &map = compute_spin_correlation(pTop_pt, pTop_eta, pTop_phi, pTop_m,
                                             aTop_pt, aTop_eta, aTop_phi, aTop_m,
                                             pLep_pt, pLep_eta, pLep_phi, pLep_m,
                                             aLep_pt, aLep_eta, aLep_phi, aLep_m);

  static const int i = index_with_key(map, "cHel");
  return map[i].second;
}



template <typename Number = float>
Number cHan(Number pTop_pt, Number pTop_eta, Number pTop_phi, Number pTop_m,
            Number aTop_pt, Number aTop_eta, Number aTop_phi, Number aTop_m,
            Number pLep_pt, Number pLep_eta, Number pLep_phi, Number pLep_m,
            Number aLep_pt, Number aLep_eta, Number aLep_phi, Number aLep_m)
{
  const auto &map = compute_spin_correlation(pTop_pt, pTop_eta, pTop_phi, pTop_m,
                                             aTop_pt, aTop_eta, aTop_phi, aTop_m,
                                             pLep_pt, pLep_eta, pLep_phi, pLep_m,
                                             aLep_pt, aLep_eta, aLep_phi, aLep_m);

  static const int i = index_with_key(map, "cHan");
  return map[i].second;
}



template <typename Number = float>
Number cSca(Number pTop_pt, Number pTop_eta, Number pTop_phi, Number pTop_m,
            Number aTop_pt, Number aTop_eta, Number aTop_phi, Number aTop_m,
            Number pLep_pt, Number pLep_eta, Number pLep_phi, Number pLep_m,
            Number aLep_pt, Number aLep_eta, Number aLep_phi, Number aLep_m)
{
  const auto &map = compute_spin_correlation(pTop_pt, pTop_eta, pTop_phi, pTop_m,
                                             aTop_pt, aTop_eta, aTop_phi, aTop_m,
                                             pLep_pt, pLep_eta, pLep_phi, pLep_m,
                                             aLep_pt, aLep_eta, aLep_phi, aLep_m);

  static const int i = index_with_key(map, "cSca");
  return map[i].second;
}



template <typename Number = float>
Number cTra(Number pTop_pt, Number pTop_eta, Number pTop_phi, Number pTop_m,
            Number aTop_pt, Number aTop_eta, Number aTop_phi, Number aTop_m,
            Number pLep_pt, Number pLep_eta, Number pLep_phi, Number pLep_m,
            Number aLep_pt, Number aLep_eta, Number aLep_phi, Number aLep_m)
{
  const auto &map = compute_spin_correlation(pTop_pt, pTop_eta, pTop_phi, pTop_m,
                                             aTop_pt, aTop_eta, aTop_phi, aTop_m,
                                             pLep_pt, pLep_eta, pLep_phi, pLep_m,
                                             aLep_pt, aLep_eta, aLep_phi, aLep_m);

  static const int i = index_with_key(map, "cTra");
  return map[i].second;
}



template <typename Number = float>
Number crkP(Number pTop_pt, Number pTop_eta, Number pTop_phi, Number pTop_m,
            Number aTop_pt, Number aTop_eta, Number aTop_phi, Number aTop_m,
            Number pLep_pt, Number pLep_eta, Number pLep_phi, Number pLep_m,
            Number aLep_pt, Number aLep_eta, Number aLep_phi, Number aLep_m)
{
  const auto &map = compute_spin_correlation(pTop_pt, pTop_eta, pTop_phi, pTop_m,
                                             aTop_pt, aTop_eta, aTop_phi, aTop_m,
                                             pLep_pt, pLep_eta, pLep_phi, pLep_m,
                                             aLep_pt, aLep_eta, aLep_phi, aLep_m);

  static const int i = index_with_key(map, "crkP");
  return map[i].second;
}



template <typename Number = float>
Number crkM(Number pTop_pt, Number pTop_eta, Number pTop_phi, Number pTop_m,
            Number aTop_pt, Number aTop_eta, Number aTop_phi, Number aTop_m,
            Number pLep_pt, Number pLep_eta, Number pLep_phi, Number pLep_m,
            Number aLep_pt, Number aLep_eta, Number aLep_phi, Number aLep_m)
{
  const auto &map = compute_spin_correlation(pTop_pt, pTop_eta, pTop_phi, pTop_m,
                                             aTop_pt, aTop_eta, aTop_phi, aTop_m,
                                             pLep_pt, pLep_eta, pLep_phi, pLep_m,
                                             aLep_pt, aLep_eta, aLep_phi, aLep_m);

  static const int i = index_with_key(map, "crkM");
  return map[i].second;
}



template <typename Number = float>
Number cnrP(Number pTop_pt, Number pTop_eta, Number pTop_phi, Number pTop_m,
            Number aTop_pt, Number aTop_eta, Number aTop_phi, Number aTop_m,
            Number pLep_pt, Number pLep_eta, Number pLep_phi, Number pLep_m,
            Number aLep_pt, Number aLep_eta, Number aLep_phi, Number aLep_m)
{
  const auto &map = compute_spin_correlation(pTop_pt, pTop_eta, pTop_phi, pTop_m,
                                             aTop_pt, aTop_eta, aTop_phi, aTop_m,
                                             pLep_pt, pLep_eta, pLep_phi, pLep_m,
                                             aLep_pt, aLep_eta, aLep_phi, aLep_m);

  static const int i = index_with_key(map, "cnrP");
  return map[i].second;
}



template <typename Number = float>
Number cnrM(Number pTop_pt, Number pTop_eta, Number pTop_phi, Number pTop_m,
            Number aTop_pt, Number aTop_eta, Number aTop_phi, Number aTop_m,
            Number pLep_pt, Number pLep_eta, Number pLep_phi, Number pLep_m,
            Number aLep_pt, Number aLep_eta, Number aLep_phi, Number aLep_m)
{
  const auto &map = compute_spin_correlation(pTop_pt, pTop_eta, pTop_phi, pTop_m,
                                             aTop_pt, aTop_eta, aTop_phi, aTop_m,
                                             pLep_pt, pLep_eta, pLep_phi, pLep_m,
                                             aLep_pt, aLep_eta, aLep_phi, aLep_m);

  static const int i = index_with_key(map, "cnrM");
  return map[i].second;
}



template <typename Number = float>
Number cnkP(Number pTop_pt, Number pTop_eta, Number pTop_phi, Number pTop_m,
            Number aTop_pt, Number aTop_eta, Number aTop_phi, Number aTop_m,
            Number pLep_pt, Number pLep_eta, Number pLep_phi, Number pLep_m,
            Number aLep_pt, Number aLep_eta, Number aLep_phi, Number aLep_m)
{
  const auto &map = compute_spin_correlation(pTop_pt, pTop_eta, pTop_phi, pTop_m,
                                             aTop_pt, aTop_eta, aTop_phi, aTop_m,
                                             pLep_pt, pLep_eta, pLep_phi, pLep_m,
                                             aLep_pt, aLep_eta, aLep_phi, aLep_m);

  static const int i = index_with_key(map, "cnkP");
  return map[i].second;
}



template <typename Number = float>
Number cnkM(Number pTop_pt, Number pTop_eta, Number pTop_phi, Number pTop_m,
            Number aTop_pt, Number aTop_eta, Number aTop_phi, Number aTop_m,
            Number pLep_pt, Number pLep_eta, Number pLep_phi, Number pLep_m,
            Number aLep_pt, Number aLep_eta, Number aLep_phi, Number aLep_m)
{
  const auto &map = compute_spin_correlation(pTop_pt, pTop_eta, pTop_phi, pTop_m,
                                             aTop_pt, aTop_eta, aTop_phi, aTop_m,
                                             pLep_pt, pLep_eta, pLep_phi, pLep_m,
                                             aLep_pt, aLep_eta, aLep_phi, aLep_m);

  static const int i = index_with_key(map, "cnkM");
  return map[i].second;
}




template <typename Number = float>
Number phi0(Number pTop_pt, Number pTop_eta, Number pTop_phi, Number pTop_m,
            Number aTop_pt, Number aTop_eta, Number aTop_phi, Number aTop_m,
            Number pLep_pt, Number pLep_eta, Number pLep_phi, Number pLep_m,
            Number aLep_pt, Number aLep_eta, Number aLep_phi, Number aLep_m)
{
  const auto &map = compute_spin_correlation(pTop_pt, pTop_eta, pTop_phi, pTop_m,
                                             aTop_pt, aTop_eta, aTop_phi, aTop_m,
                                             pLep_pt, pLep_eta, pLep_phi, pLep_m,
                                             aLep_pt, aLep_eta, aLep_phi, aLep_m);

  static const int i = index_with_key(map, "phi0");
  return map[i].second;
}



template <typename Number = float>
Number phi1(Number pTop_pt, Number pTop_eta, Number pTop_phi, Number pTop_m,
            Number aTop_pt, Number aTop_eta, Number aTop_phi, Number aTop_m,
            Number pLep_pt, Number pLep_eta, Number pLep_phi, Number pLep_m,
            Number aLep_pt, Number aLep_eta, Number aLep_phi, Number aLep_m)
{
  const auto &map = compute_spin_correlation(pTop_pt, pTop_eta, pTop_phi, pTop_m,
                                             aTop_pt, aTop_eta, aTop_phi, aTop_m,
                                             pLep_pt, pLep_eta, pLep_phi, pLep_m,
                                             aLep_pt, aLep_eta, aLep_phi, aLep_m);

  static const int i = index_with_key(map, "phi1");
  return map[i].second;
}

#endif
