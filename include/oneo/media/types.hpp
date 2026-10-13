// SPDX-License-Identifier: Proprietary
// oneo/media/types.hpp - media value types (REQ-029..037, REQ-306).
#pragma once

#include <chrono>
#include <cstdint>
#include <string>
#include <vector>

namespace oneo::media {

/// R1 sources only (REQ-306). Radio deferred to R2 (REQ-305).
enum class Source : std::uint8_t { None = 0, Usb = 1, Bluetooth = 2 };

enum class PlaybackState : std::uint8_t { Stopped = 0, Playing = 1, Paused = 2, Buffering = 3, Error = 4 };

/// Browse views for USB (REQ-030).
enum class BrowseView : std::uint8_t { Folder = 0, Artist = 1, Album = 2 };

struct TrackInfo {
    std::string title;
    std::string artist;
    std::string album;
    std::chrono::milliseconds duration{0};  ///< 0 = unknown (e.g. some AVRCP sources)
    std::string itemId;                     ///< library id for USB; empty for Bluetooth
};

/// One entry in a browse listing.
struct BrowseItem {
    std::string id;         ///< opaque; pass back to browse()/playItem()
    std::string label;      ///< display text (folder, artist, album or track title)
    bool playable{false};   ///< true = track, false = container
};

struct BrowsePage {
    std::vector<BrowseItem> items;
    std::uint32_t total{0};  ///< total items in the container (for paging)
};

/// Aggregate now-playing state (REQ-035); published as D-Bus properties.
struct NowPlaying {
    Source source{Source::None};
    PlaybackState state{PlaybackState::Stopped};
    TrackInfo track;
    std::chrono::milliseconds position{0};
    std::uint8_t volume{0};  ///< 0..100, persisted via org.oneo.System (REQ-037)
};

/// Volume range.
inline constexpr std::uint8_t kMaxVolume = 100;

}  // namespace oneo::media
