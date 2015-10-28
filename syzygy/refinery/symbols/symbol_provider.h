// Copyright 2015 Google Inc. All Rights Reserved.
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

#ifndef SYZYGY_REFINERY_SYMBOLS_SYMBOL_PROVIDER_H_
#define SYZYGY_REFINERY_SYMBOLS_SYMBOL_PROVIDER_H_

#include "base/macros.h"
#include "base/containers/hash_tables.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/strings/string16.h"
#include "syzygy/pe/pe_file.h"
#include "syzygy/refinery/core/address.h"
#include "syzygy/refinery/symbols/simple_cache.h"
#include "syzygy/refinery/types/type_repository.h"

namespace refinery {

// Fwd.
class ProcessState;

// The SymbolProvider provides symbol information. See DiaSymbolProvider for an
// alternative.
class SymbolProvider : public base::RefCounted<SymbolProvider> {
 public:
  SymbolProvider();
  ~SymbolProvider();

  // Retrieves or creates a TypeRepository for the module within @p
  // process_state corresponding to @p va.
  // @param va virtual address within a module for which to get a
  //     TypeRepository.
  // @param process_state the process state within which to interpret @p va.
  // @param type_repo on success, returns a type repository for the module. On
  //     failure, contains nullptr.
  // @returns true on success, false on failure.
  bool FindOrCreateTypeRepository(const Address va,
                                  ProcessState* process_state,
                                  scoped_refptr<TypeRepository>* type_repo);

  // Retrieves or creates a TypeRepository for the module  corresponding to @p
  // signature.
  // @param signature the signature of the module for which to get a type
  //     repository.
  // @param type_repo on success, returns a type repository for the module. On
  //     failure, contains nullptr.
  // @returns true on success, false on failure.
  bool FindOrCreateTypeRepository(const pe::PEFile::Signature& signature,
                                  scoped_refptr<TypeRepository>* type_repo);

  // Retrieves or creates a TypeNameIndex for the module within @p
  // process_state corresponding to @p va.
  // @param va virtual address within a module for which to get a
  //     TypeRepository.
  // @param process_state the process state within which to interpret @p va.
  // @param type_repo on success, returns a typename index for the module. On
  //     failure, contains nullptr.
  // @returns true on success, false on failure.
  bool FindOrCreateTypeNameIndex(const Address va,
                                 ProcessState* process_state,
                                 scoped_refptr<TypeNameIndex>* typename_index);

  // Retrieves or creates a TypeNameIndex for the module  corresponding to @p
  // signature.
  // @param signature the signature of the module for which to get a type
  //     repository.
  // @param type_repo on success, returns a typename index for the module. On
  //     failure, contains nullptr.
  // @returns true on success, false on failure.
  bool FindOrCreateTypeNameIndex(const pe::PEFile::Signature& signature,
                                 scoped_refptr<TypeNameIndex>* typename_index);

 private:
  static void GetCacheKey(const pe::PEFile::Signature& signature,
                          base::string16* cache_key);

  // Creates a type repository (without caching it).
  bool CreateTypeRepository(const pe::PEFile::Signature& signature,
                            scoped_refptr<TypeRepository>* type_repo);

  // Creates a type name index (without caching it).
  bool CreateTypeNameIndex(const pe::PEFile::Signature& signature,
                           scoped_refptr<TypeNameIndex>* index);

  // Caching for type repositories and typename indices. The cache key is
  // "<basename>:<size>:<checksum>:<timestamp>". The caches may contain
  // negative entries (indicating a failed attempt at creating a session) in the
  // form of null pointers.
  SimpleCache<TypeRepository> type_repos_;
  SimpleCache<TypeNameIndex> typename_indices_;

  DISALLOW_COPY_AND_ASSIGN(SymbolProvider);
};

}  // namespace refinery

#endif  // SYZYGY_REFINERY_SYMBOLS_SYMBOL_PROVIDER_H_
