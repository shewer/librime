//
// Copyright RIME Developers
// Distributed under the BSD License
//
// 2013-01-06 GONG Chen <chen.sst@gmail.com>
//
#include <rime/candidate.h>

namespace rime {

static an<Candidate>
UnpackShadowCandidate(const an<Candidate>& cand) {
  auto shadow = As<ShadowCandidate>(cand);
  return shadow ? shadow->item() : cand;
}

an<Candidate>
Candidate::GetGenuineCandidate(const an<Candidate>& cand) {
  auto uniquified = As<UniquifiedCandidate>(cand);
  return UnpackShadowCandidate(uniquified ? uniquified->items().front() : cand);
}

vector<of<Candidate>>
Candidate::GetGenuineCandidates(const an<Candidate>& cand) {
  vector<of<Candidate>> result;
  if (auto uniquified = As<UniquifiedCandidate>(cand)) {
    for (const auto& item : uniquified->items()) {
      result.push_back(UnpackShadowCandidate(item));
    }
  }
  else {
    result.push_back(UnpackShadowCandidate(cand));
  }
  return result;
}

int Candidate::compare(const an<Candidate>& other) {
  if (! other )
    return -1;
  int k = 0;
  // the one nearer to the beginning of segment comes first
  k = start_ - other->start_;
  if (k != 0)
    return k;
  // then the longer comes first
  k = end_ - other->end_;
  if (k != 0)
    return -k;
  // compare quality
  double qdiff = quality_ - other->quality_;
  if (qdiff != 0.)
    return (qdiff > 0.) ? -1 : 1;
  // draw
  return 0;
}

}  // namespace rime
