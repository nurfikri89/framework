// -*- C++ -*-
// author: afiq anuar
// short: a listing of free functions that contains common numerical/vector operations

#ifndef FWK_NUMERIC_VECTOR_H
#define FWK_NUMERIC_VECTOR_H

#include <numeric>
#include <cmath>
#include "TLorentzVector.h"

/// poor man's std::hypot (tested with g++/clang++, fine for double: 1e-158 < i < 1e10)
template <typename Number = float>
Number quadratic_sum(Number num1, Number num2)
{
  return std::sqrt((num1 * num1) + (num2 * num2));
}



template <typename Number = float>
Number absolute_difference(Number num1, Number num2)
{
  return std::abs(num1 - num2);
}



/// actually abs(dphi)
/// initially written as acos(cos(phi1 - phi2))
/// but somehow both g++ and clang optimizes it away (even without -O)
/// in cases when deta (using absolute_difference) and dphi are both within an Aggregate
template <typename Number = float>
Number dphi(Number phi1, Number phi2) 
{
  return std::acos( std::cos(phi1 - phi2) );
}



template <typename Number = float>
Number dR(Number eta1, Number phi1, Number eta2, Number phi2) 
{
  return quadratic_sum(eta1 - eta2, dphi(phi1, phi2));
}



template <size_t ...N, typename Number>
void assign_vector(std::array<TLorentzVector, sizeof...(N)> &p4, std::array<Number, 4 * sizeof...(N)> &arg, std::index_sequence<N...>)
{
  (std::get<N>(p4).SetPtEtaPhiM(std::get<4 * N>(arg), std::get<(4 * N) + 1>(arg), std::get<(4 * N) + 2>(arg), std::get<(4 * N) + 3>(arg)), ...);
}



template <size_t ...N, typename ...Numbers>
const TLorentzVector& multivector_system(std::index_sequence<N...>, Numbers ...numbers)
{
  static_assert(sizeof...(N) > 0 and sizeof...(numbers) == sizeof...(N) and sizeof...(N) % 4 == 0, 
                "ERROR: multivector_system: arguments are interpreted as pt, eta, phi and mass of "
                "the vectors comprising the system. As such, the number of arguments must be 4N!! "
                "Provide arguments as pt1, eta1, phi1, mass1, pt2, eta2, phi2, mass2...");

  using Number = typename std::tuple_element<0, std::tuple<Numbers...>>::type;

  static TLorentzVector psum;
  static std::array<Number, sizeof...(N)> arg;
  if (((std::get<N>(arg) == numbers) and ...))
    return psum;

  ((std::get<N>(arg) = numbers), ...);

  static std::array<TLorentzVector, sizeof...(N) / 4> p4s;
  assign_vector(p4s, arg, std::make_index_sequence<sizeof...(N) / 4>{});
  psum = p4s[0];
  for (int ip4 = 1; ip4 < sizeof...(N) / 4; ++ip4)
    psum += p4s[ip4];

  return psum;
}



template <typename Number, typename ...Numbers>
Number invariant_mass_impl(Number number, Numbers ...numbers) 
{ 
  const auto &p4 = multivector_system(std::make_index_sequence<sizeof...(numbers) + 1>{}, number, numbers...);
  return p4.M();
}



template <typename Number, size_t ...N>
auto invariant_mass_helper(std::index_sequence<N...>) -> Number(*)(typename std::tuple_element<N, std::array<Number, sizeof...(N)>>::type...)
{
  return invariant_mass_impl<typename std::tuple_element<N, std::array<Number, sizeof...(N)>>::type...>;
}



template <size_t N = 2, typename Number = float>
auto invariant_mass() -> decltype(invariant_mass_helper<Number>(std::make_index_sequence<4 * N>{}))
{
  return invariant_mass_helper<Number>(std::make_index_sequence<4 * N>{});
}

#endif
