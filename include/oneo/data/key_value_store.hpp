// SPDX-License-Identifier: Proprietary
// oneo/data/key_value_store.hpp - persistent settings storage (REQ-108, REQ-109).
//
// Used only by oneo-system (sole owner of persistent settings, ADR-004).
// Contract: writes are buffered in memory and flushed debounced (>= 2 s) as
// temp file + fsync + rename, so power loss leaves the old or new file, never a
// torn one. Impl uses std::filesystem/fstream (+ fsync behind a platform shim).
#pragma once

#include "oneo/core/result.hpp"

#include <cstdint>
#include <map>
#include <string>
#include <variant>

namespace oneo::data {

using Value = std::variant<bool, std::int64_t, double, std::string>;
using ValueMap = std::map<std::string, Value>;

class IKeyValueStore {
public:
    virtual ~IKeyValueStore() = default;

    /// Load from disk. Missing file -> empty map (Ok). Corrupt file -> IoError
    /// after falling back to the last good copy or defaults (caller logs).
    virtual core::Result<ValueMap> load() = 0;

    /// Stage a change; returns immediately. Persisted by the next debounced flush.
    virtual core::Result<void> set(const std::string& key, const Value& value) = 0;
    virtual core::Result<void> erase(const std::string& key) = 0;

    /// Force pending changes to disk now (orderly shutdown, suspend).
    virtual core::Result<void> flush() = 0;
};

}  // namespace oneo::data
