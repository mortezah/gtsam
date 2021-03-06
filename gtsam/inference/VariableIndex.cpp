/* ----------------------------------------------------------------------------

 * GTSAM Copyright 2010, Georgia Tech Research Corporation,
 * Atlanta, Georgia 30332-0415
 * All Rights Reserved
 * Authors: Frank Dellaert, et al. (see THANKS for the full author list)

 * See LICENSE for the license information

 * -------------------------------------------------------------------------- */

/**
 * @file    VariableIndex.cpp
 * @author  Richard Roberts
 * @date    March 26, 2013
 */

#include <iostream>

#include <gtsam/inference/VariableIndex.h>

namespace gtsam {

using namespace std;

/* ************************************************************************* */
bool VariableIndex::equals(const VariableIndex& other, double tol) const {
  return this->nEntries_ == other.nEntries_ && this->nFactors_ == other.nFactors_
    && this->index_ == other.index_;
}

/* ************************************************************************* */
void VariableIndex::print(const string& str, const KeyFormatter& keyFormatter) const {
  cout << str;
  cout << "nEntries = " << nEntries() << ", nFactors = " << nFactors() << "\n";
  BOOST_FOREACH(KeyMap::value_type key_factors, index_) {
    cout << "var " << keyFormatter(key_factors.first) << ":";
    BOOST_FOREACH(const size_t factor, key_factors.second)
      cout << " " << factor;
    cout << "\n";
  }
  cout.flush();
}

/* ************************************************************************* */
void VariableIndex::outputMetisFormat(ostream& os) const {
  os << size() << " " << nFactors() << "\n";
  // run over variables, which will be hyper-edges.
  BOOST_FOREACH(KeyMap::value_type key_factors, index_) {
    // every variable is a hyper-edge covering its factors
    BOOST_FOREACH(const size_t factor, key_factors.second)
      os << (factor+1) << " "; // base 1
    os << "\n";
  }
  os << flush;
}

}
