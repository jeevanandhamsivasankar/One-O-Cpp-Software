// SPDX-License-Identifier: Proprietary
// oneo/media/media_service.hpp - IMediaService, exported as org.oneo.Media.
// Loop-thread confined. Source switch must be audible within 2 s (REQ-036).
#pragma once

#include "oneo/core/result.hpp"
#include "oneo/core/subscription.hpp"
#include "oneo/media/types.hpp"

#include <cstdint>
#include <functional>
#include <string>
#include <vector>

namespace oneo::media {

class IMediaService {
public:
    using NowPlayingHandler = std::function<void(const NowPlaying&)>;
    using SourcesHandler = std::function<void(const std::vector<Source>&)>;

    virtual ~IMediaService() = default;

    virtual NowPlaying nowPlaying() const = 0;
    /// Sources currently usable (USB mounted, BT A2DP connected) (REQ-031).
    virtual std::vector<Source> availableSources() const = 0;

    /// Notified on any NowPlaying change; position updates coalesced to <= 1 Hz.
    virtual core::Subscription subscribeNowPlaying(NowPlayingHandler handler) = 0;
    virtual core::Subscription subscribeSources(SourcesHandler handler) = 0;

    // Transport (REQ-033). Apply to the active source; Unavailable if none.
    virtual core::Result<void> play() = 0;
    virtual core::Result<void> pause() = 0;
    virtual core::Result<void> next() = 0;
    virtual core::Result<void> previous() = 0;

    /// Switch active source; completes when the new source is playing or failed.
    virtual void setSource(Source source, core::Completion<void> done) = 0;
    /// 0..kMaxVolume; out of range -> InvalidArgument.
    virtual core::Result<void> setVolume(std::uint8_t volume) = 0;

    /// USB library browse (REQ-030). containerId empty = root of `view`.
    /// Long lists are subject to driving lockout in the HMI (REQ-048), not here.
    virtual void browse(BrowseView view, const std::string& containerId, std::uint32_t offset,
                        std::uint32_t count, core::Completion<BrowsePage> done) = 0;
    /// Play a playable BrowseItem id (switches to Usb if needed).
    virtual void playItem(const std::string& itemId, core::Completion<void> done) = 0;
};

}  // namespace oneo::media
