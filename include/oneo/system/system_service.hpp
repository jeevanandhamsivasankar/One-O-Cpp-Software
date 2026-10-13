// SPDX-License-Identifier: Proprietary
// oneo/system/system_service.hpp - ISystemService, exported as org.oneo.System.
//
// Owns persistent settings (via data::IKeyValueStore), the driving lockout
// (from org.oneo.VehicleSignals VehicleSpeed), theme resolution, health/fault
// state and version info. Loop-thread confined.
#pragma once

#include "oneo/core/result.hpp"
#include "oneo/core/subscription.hpp"
#include "oneo/data/key_value_store.hpp"
#include "oneo/system/types.hpp"

#include <functional>
#include <optional>
#include <string>
#include <vector>

namespace oneo::system {

/// Pure lockout rule, unit-testable in isolation (REQ-048..050).
class ILockoutPolicy {
public:
    virtual ~ILockoutPolicy() = default;
    /// speedKph empty = speed invalid/unavailable -> locked.
    virtual LockoutState evaluate(std::optional<double> speedKph, double thresholdKph) const = 0;
};

class ISystemService {
public:
    struct Observer {
        std::function<void(const std::string& key, const data::Value& value)> onSetting;
        std::function<void(const LockoutState&)> onLockout;
        std::function<void(Theme)> onTheme;  ///< resolved theme (auto uses AmbientDark, REQ-016)
        std::function<void(const std::vector<ServiceHealth>&)> onHealth;
    };

    virtual ~ISystemService() = default;

    // Settings (REQ-017/018/037/049). Unknown key -> NotFound; wrong type/range ->
    // InvalidArgument; key with lockedWhileDriving(key) while lockout().locked ->
    // DrivingLocked, regardless of caller (REQ-048, REQ-408). Exempt keys always pass.
    virtual core::Result<data::Value> getSetting(const std::string& key) const = 0;
    virtual core::Result<void> setSetting(const std::string& key, const data::Value& value) = 0;

    virtual LockoutState lockout() const = 0;
    virtual Theme theme() const = 0;

    // Health / diagnostics (REQ-007, REQ-009).
    virtual std::vector<ServiceHealth> health() const = 0;
    virtual std::vector<VersionInfo> versions() const = 0;
    /// Called by oneo-fault@.service when a unit exceeds its restart limit.
    virtual core::Result<void> reportFault(const std::string& unit, const std::string& reason) = 0;

    virtual core::Subscription subscribe(Observer observer) = 0;
};

}  // namespace oneo::system
