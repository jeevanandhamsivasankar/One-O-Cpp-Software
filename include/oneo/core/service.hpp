// SPDX-License-Identifier: Proprietary
// oneo/core/service.hpp - common daemon skeleton contracts (ADR-004).
//
// Each oneo-* daemon: main() builds an IServiceRuntime (systemd on target, stub on
// host), creates its core service + backends + D-Bus adapter, then runs the loop.
#pragma once

#include "oneo/core/event_loop.hpp"
#include "oneo/core/result.hpp"

#include <string>
#include <string_view>

namespace oneo::core {

enum class LogLevel { Debug, Info, Warning, Error, Critical };

/// Structured logger (journald on target, stderr on host). Thread-safe.
class ILogger {
public:
    virtual ~ILogger() = default;
    virtual void log(LogLevel level, std::string_view component, std::string_view message) = 0;
};

/// Process supervision hooks (sd_notify on target, no-op/recorder on host).
class IServiceRuntime {
public:
    virtual ~IServiceRuntime() = default;
    /// READY=1 once the D-Bus name is owned and initial state is published.
    virtual void notifyReady() = 0;
    /// STATUS=... free-text status line.
    virtual void notifyStatus(std::string_view status) = 0;
    /// STOPPING=1 at start of orderly shutdown.
    virtual void notifyStopping() = 0;
    /// Watchdog interval requested by the supervisor (0 = disabled). The skeleton
    /// pings at half this period from the loop thread, so a stuck loop is restarted.
    virtual Duration watchdogInterval() const = 0;
    virtual void pingWatchdog() = 0;
};

/// A runnable unit inside a daemon (core service or D-Bus adapter).
/// start()/stop() are called on the loop thread by the composition root, in
/// dependency order (backends -> core -> adapter) and reverse order on stop.
class IComponent {
public:
    virtual ~IComponent() = default;
    virtual std::string_view name() const = 0;
    virtual Result<void> start() = 0;
    /// Must cancel pending operations (Completion with ErrorCode::Cancelled).
    virtual void stop() = 0;
};

}  // namespace oneo::core
