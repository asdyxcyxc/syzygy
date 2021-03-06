// Copyright 2012 Google Inc. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// Declares a partial PdbMutatorInterface implementation that provides an
// implementation for the 'name' member function.

#ifndef SYZYGY_PDB_MUTATORS_NAMED_MUTATOR_H_
#define SYZYGY_PDB_MUTATORS_NAMED_MUTATOR_H_

#include "syzygy/pdb/pdb_mutator.h"

namespace pdb {
namespace mutators {

// Implements the 'name' member function of PdbMutatorInterface.
// The user must define the static variable:
//
//   const char DerivedType::kMutatorName[];
//
// @tparam DerivedType the type of the derived class.
template<class DerivedType>
class NamedPdbMutatorImpl : public PdbMutatorInterface {
 public:
  // Gets the name of this mutator.
  // @returns the name of this mutator.
  virtual const char* name() const override {
    return DerivedType::kMutatorName;
  }
};

}  // namespace mutators
}  // namespace pdb

#endif  // SYZYGY_PDB_MUTATORS_NAMED_MUTATOR_H_
