// SPDX-License-Identifier: Proprietary
// oneo/core/lockout.hpp - driving-lockout state as seen by a service core (REQ-408).
//
// oneo-system is the single lockout authority (org.oneo.System DrivingLocked).
// Other cores (vehicle, phone) get the state only through this interface, so
// domain modules stay independent and enforce lockout service-side, regardless
// of caller. Target impl: adapter backed by the org.oneo.System DrivingLocked
// proxy. Host: settable fake. Loop-thread confined.
#pragma once

#include "oneo/core/subscription.hpp"

#include <functional>

namespace oneo::core {

class ILockoutSource {
public:
    using Handler = std::function<void(bool locked)>;

    virtual ~ILockoutSource() = default;

    /// Fail-safe: true until the first DrivingLocked value has been received and
    /// whenever org.oneo.System is not on the bus (unknown = locked, REQ-050).
    virtual bool locked() const = 0;

    /// Called on every change of locked(), on the loop thread.
    virtual Subscription subscribe(Handler handler) = 0;
};

}  // namespace oneo::core
