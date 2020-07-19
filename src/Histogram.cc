// -*- C++ -*-
// author: afiq anuar
// short: please refer to header for information

Framework::Histogram::Histogram()
{
  TH1::AddDirectory(false);
  TH1::SetDefaultSumw2(true);
}



template <typename Weighter>
void Framework::Histogram::set_weighter(Weighter weighter_)
{
  using Traits = function_traits<decltype(weighter_)>;
  static_assert(Traits::arity == 0, 
                "ERROR: Histogram::set_weighter: the number of arguments of the Histogram weighter must be zero."
                "Use lambda captures if some dependence on event information is needed.");
  static_assert(std::is_convertible_v<typename Traits::result_type, double>, 
                "ERROR: Histogram::set_weighter: the return type needs to be convertible to double!!");

  if (!weighter)
    weighter = std::function<double()>(weighter_);
}



template <typename Hist, typename Filler, typename ...Args>
bool Framework::Histogram::make_histogram(Filler filler, const std::string &name, Args &&...args)
{
  auto iH = std::find_if(std::begin(v_hist), std::end(v_hist), [&name] (const auto &hist) {return name == std::string(hist.first->GetName());});
  if (iH != std::end(v_hist))
    return false;

  auto f_fill = [this, index = v_hist.size(), filler] () {
    using Traits = function_traits<decltype(filler)>;

    filler((typename Traits::template bare_arg<0>) v_hist[index].first.get(), weight);
  };

  v_hist.emplace_back(std::make_unique<Hist>(name.c_str(), std::forward<Args>(args)...), std::function<void()>(f_fill));
  return true;
}



void Framework::Histogram::fill()
{
  weight = (weighter) ? weighter() : 1.;

  for (auto &hist : v_hist)
    hist.second();
}



void Framework::Histogram::save_as(const std::string &name) const
{
  auto file = std::make_unique<TFile>(name.c_str(), "recreate");
  file->cd();

  for (auto &hist : v_hist)
    hist.first->Write();
}
