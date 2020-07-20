#ifndef FWK_HISTOGRAM_H
#define FWK_HISTOGRAM_H

// -*- C++ -*-
// author: afiq anuar
// short: an interface for creating, filling and saving of histograms from groups

#include "Heap.h"

#include "TFile.h"

#include "TH1.h"
#include "TH1I.h"
#include "TH1F.h"
#include "TH1D.h"

#include "TH2.h"
#include "TH2I.h"
#include "TH2F.h"
#include "TH2D.h"

#include "TH3.h"
#include "TH3I.h"
#include "TH3F.h"
#include "TH3D.h"

namespace Framework {
  class Histogram {
  public:
    /// constructor
    Histogram();

    /// provide the weight function
    /// signature: no argument and returns a double for the weight
    template <typename Weighter>
    void set_weighter(Weighter weighter_);

    /// make a histogram and its filling function
    /// the filling function takes two arguments
    /// a pointer to the histogram, and the associated weight to be filled
    /// both of which are handled by this class
    template <typename Hist, typename Filler, typename ...Args>
    bool make_histogram(Filler filler, const std::string &name, Args &&...args);

    /// compute the weight and fill all held histograms
    void fill();

    /// save all held histograms into a ROOT file
    void save_as(const std::string &name) const;

  protected:
    /// the weight to be used when filling the histograms
    double weight;

    /// how to compute the weights
    std::function<double()> weighter;

    /// all histograms and its filling function
    std::vector<std::pair<std::unique_ptr<TH1>, std::function<void()>>> v_hist;
  };
}

#include "Histogram.cc"

#endif
