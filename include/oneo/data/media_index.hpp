// SPDX-License-Identifier: Proprietary
// oneo/data/media_index.hpp - USB media library index (REQ-029..031).
//
// Scanning and tag parsing run on a worker thread owned by the impl; completions
// are posted back to the loop thread. Index cache lives under /data/media.
#pragma once

#include "oneo/core/result.hpp"
#include "oneo/media/types.hpp"

#include <cstdint>
#include <functional>
#include <string>

namespace oneo::data {

struct ScanStats {
    std::uint32_t tracks{0};
    std::uint32_t skipped{0};  ///< unsupported or unreadable files
};

struct IndexedTrack {
    std::string filePath;
    media::TrackInfo info;
};

class IMediaIndex {
public:
    using ProgressHandler = std::function<void(std::uint32_t tracksSoFar)>;
    virtual ~IMediaIndex() = default;

    /// (Re)index a mounted volume. Cancels any running scan. Partial results are
    /// browsable while scanning. Completion: Ok(stats) or Cancelled/IoError.
    virtual void scan(const std::string& mountPoint, ProgressHandler progress,
                      core::Completion<ScanStats> done) = 0;
    /// Drop index for a removed volume; cancels a running scan.
    virtual void clear() = 0;

    virtual core::Result<media::BrowsePage> browse(media::BrowseView view, const std::string& containerId,
                                                   std::uint32_t offset, std::uint32_t count) const = 0;
    /// Resolve a playable item id to file path + tags.
    virtual core::Result<IndexedTrack> track(const std::string& itemId) const = 0;
    /// Next/previous track id in the current play context; NotFound at the ends.
    virtual core::Result<std::string> neighbour(const std::string& itemId, int step) const = 0;
};

}  // namespace oneo::data
