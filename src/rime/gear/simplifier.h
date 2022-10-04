//
// Copyright RIME Developers
// Distributed under the BSD License
//
// 2011-12-12 GONG Chen <chen.sst@gmail.com>
//
#ifndef RIME_SIMPLIFIER_H_
#define RIME_SIMPLIFIER_H_

#include <rime/filter.h>
#include <rime/algo/algebra.h>
#include <rime/gear/filter_commons.h>
#include <opencc/Config.hpp> // Place OpenCC #includes here to avoid VS2015 compilation errors
#include <opencc/Common.hpp>

namespace rime {

class Opencc {
 private:
   opencc::ConverterPtr converter_;
   opencc::DictPtr dict_;
 public:
  Opencc(const string& config_path);
  bool ConvertWord(const string& text, vector<string>* forms);
  bool RandomConvertText(const string& text, string* simplified);
  bool ConvertText(const string& text, string* simplified);
};

class Simplifier : public Filter, TagMatching {
 public:
  explicit Simplifier(const Ticket& ticket);

  virtual an<Translation> Apply(an<Translation> translation,
                                CandidateList* candidates);


  virtual bool AppliesToSegment(Segment* segment) {
    return TagsMatch(segment);
  }

  bool Convert(const an<Candidate>& original,
               CandidateQueue* result);

 protected:
  enum TipsLevel { kTipsNone, kTipsChar, kTipsAll };

  void Initialize();
  void PushBack(const an<Candidate>& original,
                CandidateQueue* result,
                const string& simplified);

  bool initialized_ = false;
  the<Opencc> opencc_;
  // settings
  TipsLevel tips_level_ =  kTipsNone;
  string option_name_;
  string opencc_config_;
  set<string> excluded_types_;
  bool show_in_comment_ = false;
  bool inherit_comment_ = true;
  Projection comment_formatter_;
  bool random_ = false;
};

}  // namespace rime

#endif  // RIME_SIMPLIFIER_H_
