// SPDX-License-Identifier: Proprietary
// oneo/core/event_loop.hpp - single-threaded event loop and clock abstractions.
//
// Threading model (software.md section 4): every daemon runs ONE loop thread.
// All core-library objects are confined to it; worker threads hand results back
// with post(). Implementations: sd-event/sdbus-c++ (target), ManualEventLoop (tests).
#pragma once

#include "oneo/core/subscription.hpp"

#include <chrono>
#include <functional>

namespace oneo::core {

using Clock = std::chrono::steady_clock;
using TimePoint = Clock::time_point;
using Duration = std::chrono::milliseconds;

/// Monotonic time source; injectable so timeouts are deterministic in tests.
class IClock {
public:
    virtual ~IClock() = default;
    virtual TimePoint now() const = 0;
};

/// Event loop owned by the daemon's composition root.
class IEventLoop {
public:
    using Task = std::function<void()>;

    virtual ~IEventLoop() = default;

    /// Thread-safe. Queue task to run on the loop thread (FIFO). Never runs inline.
    virtual void post(Task task) = 0;

    /// Loop thread only. One-shot timer after delay. Cancel by destroying the handle.
    virtual Subscription addTimer(Duration delay, Task task) = 0;

    /// Loop thread only. Periodic timer; first fire after one period.
    virtual Subscription addPeriodicTimer(Duration period, Task task) = 0;

    /// True when called from the loop thread (for debug assertions).
    virtual bool isLoopThread() const = 0;

    /// Clock used by this loop's timers.
    virtual const IClock& clock() const = 0;
};

}  // namespace oneo::core
