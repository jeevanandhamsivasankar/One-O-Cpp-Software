// SPDX-License-Identifier: Proprietary
// oneo/vehicle/vehicle_signals.hpp - IVehicleSignals: the C++17 vehicle API (REQ-020).
//
// Implemented by the vehicled core library; exported 1:1 on D-Bus as
// org.oneo.VehicleSignals (include/oneo/dbus/org.oneo.VehicleSignals.xml).
// Loop-thread confined (software.md section 4).
#pragma once

#include "oneo/core/result.hpp"
#include "oneo/core/subscription.hpp"
#include "oneo/vehicle/types.hpp"

#include <functional>
#include <vector>

namespace oneo::vehicle {

class IVehicleSignals {
public:
    using SampleHandler = std::function<void(const SignalSample&)>;

    virtual ~IVehicleSignals() = default;

    /// Latest cached sample. Never blocks. Unknown id -> ErrorCode::NotFound.
    virtual core::Result<SignalSample> get(SignalId id) const = 0;

    /// Snapshot of all signals (used on HMI (re)connect, ADR-004 "HMI restart").
    virtual std::vector<SignalSample> snapshot() const = 0;

    /// Called on every value or validity change of `id` (not on identical repeats).
    virtual core::Subscription subscribe(SignalId id, SampleHandler handler) = 0;

    /// Request a vehicle setting change (REQ-027). Flow: lockout check via the
    /// injected core::ILockoutSource (REQ-408; every settable signal rejected while
    /// locked or lockout unknown) -> allow-list + range check (REQ-407) -> CAN
    /// write -> wait for feedback frame matching `value`.
    /// Completes with Ok when confirmed, else DrivingLocked / NotAllowed /
    /// InvalidArgument / Unavailable / Timeout / Busy (one pending request per signal).
    virtual void setSetting(SignalId id, std::int32_t value, core::Completion<void> done) = 0;
};

}  // namespace oneo::vehicle
