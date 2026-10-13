// SPDX-License-Identifier: Proprietary
// oneo/media/backends.hpp - backend seams for the mediad core (host-mockable).
//
// Target impls: GStreamer->PipeWire engine, BlueZ AVRCP/A2DP, udev/automount
// watcher - all Linux-only (CMake if(UNIX AND NOT APPLE)). Host: fakes.
// Callbacks are delivered on the loop thread (impls post() from their threads).
#pragma once

#include "oneo/core/result.hpp"
#include "oneo/media/types.hpp"

#include <chrono>
#include <cstdint>
#include <functional>
#include <string>

namespace oneo::media {

/// Local file playback (MP3/FLAC/AAC, REQ-029) into the "media" audio role.
class IPlaybackEngine {
public:
    struct Events {
        std::function<void(PlaybackState)> onState;
        std::function<void(std::chrono::milliseconds)> onPosition;
        std::function<void()> onEndOfStream;
        std::function<void(const core::Error&)> onError;
    };
    virtual ~IPlaybackEngine() = default;
    virtual void setEvents(Events events) = 0;
    virtual core::Result<void> load(const std::string& filePath) = 0;
    virtual core::Result<void> play() = 0;
    virtual core::Result<void> pause() = 0;
    virtual core::Result<void> stop() = 0;
    /// Per-stream volume (REQ-205), 0..kMaxVolume.
    virtual core::Result<void> setVolume(std::uint8_t volume) = 0;
};

/// Bluetooth audio source (A2DP sink + AVRCP controller, REQ-032..034).
class IBluetoothAudio {
public:
    struct Events {
        std::function<void(bool connected)> onConnected;
        std::function<void(PlaybackState)> onState;     ///< includes phone-initiated control
        std::function<void(const TrackInfo&)> onTrack;  ///< AVRCP metadata
    };
    virtual ~IBluetoothAudio() = default;
    virtual void setEvents(Events events) = 0;
    virtual bool connected() const = 0;
    virtual core::Result<void> play() = 0;
    virtual core::Result<void> pause() = 0;
    virtual core::Result<void> next() = 0;
    virtual core::Result<void> previous() = 0;
};

/// USB mass-storage presence (REQ-031, REQ-207).
class IUsbWatcher {
public:
    /// mountPoint empty on removal.
    using Handler = std::function<void(bool present, const std::string& mountPoint)>;
    virtual ~IUsbWatcher() = default;
    virtual core::Result<void> start(Handler handler) = 0;
    virtual void stop() = 0;
};

}  // namespace oneo::media
