// SPDX-License-Identifier: Proprietary
// oneo/core/subscription.hpp - RAII handle for observer registrations.
#pragma once

#include <functional>
#include <utility>

namespace oneo::core {

/// Move-only handle returned by every subscribe()/addTimer() style call.
/// Destroying or reset()ing it unregisters the callback; after that the callback
/// is guaranteed not to be invoked. Must be destroyed on the loop thread that
/// created it. The handle must not outlive the object it was obtained from.
class [[nodiscard]] Subscription {
public:
    Subscription() = default;
    explicit Subscription(std::function<void()> cancel) : cancel_(std::move(cancel)) {}
    ~Subscription() { reset(); }

    Subscription(const Subscription&) = delete;
    Subscription& operator=(const Subscription&) = delete;
    Subscription(Subscription&& other) noexcept : cancel_(std::exchange(other.cancel_, nullptr)) {}
    Subscription& operator=(Subscription&& other) noexcept {
        if (this != &other) {
            reset();
            cancel_ = std::exchange(other.cancel_, nullptr);
        }
        return *this;
    }

    /// Unregister now. Idempotent.
    void reset() {
        if (cancel_) {
            auto c = std::exchange(cancel_, nullptr);
            c();
        }
    }

    bool active() const noexcept { return static_cast<bool>(cancel_); }

private:
    std::function<void()> cancel_;
};

}  // namespace oneo::core
