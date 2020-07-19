// -*- C++ -*-
// author: afiq anuar
// short: a listing of free functions that contains common string io operations

#ifndef FWK_STRING_IO_H
#define FWK_STRING_IO_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <string>

/// string replacement
inline bool replace(std::string &str, const std::string &from, const std::string &to) {
  std::size_t start_pos = str.find(from);
  if (start_pos == std::string::npos)
    return false;
  str.replace(start_pos, from.length(), to);
  return true;
}



/// count occurences of substrings
/// credit https://stackoverflow.com/questions/22489073/counting-the-number-of-occurrences-of-a-string-within-a-string
inline int count_substring(const std::string &str, const std::string &sub) {
  int nSub = 0;
  std::string::size_type iSub = 0;
  while ((iSub = str.find(sub, iSub)) != std::string::npos) {
    ++nSub;
    iSub += sub.length();
  }

  return nSub;
}



/// number to string; to_string tend to give more precision than needed
template <typename Number> 
std::string to_str(Number num, const int prec = -1, const bool fixed = false) 
{
  std::ostringstream out_str;
  if (fixed)
    out_str << std::fixed;
  if (prec > 0)
    out_str << std::setprecision(prec);

  out_str << num; 
  return out_str.str(); 
}

#endif
