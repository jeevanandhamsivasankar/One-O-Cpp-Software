// SPDX-License-Identifier: Proprietary
// oneo/system/types.hpp - system service value types (REQ-009, 016-018, 048-050).
#pragma once

#include <cstdint>
#include <string>
#include <string_view>

namespace oneo::system {

/// Well-known setting keys owned by oneo-system. Values: see software.md section 7.
namespace keys {
inline constexpr std::string_view kLocale = "hmi.locale";                  ///< string "en-US" | "de-DE"
inline constexpr std::string_view kUnits = "hmi.units";                    ///< string "metric" | "imperial"
inline constexpr std::string_view kThemeMode = "hmi.themeMode";            ///< string "auto" | "day" | "night"
inline constexpr std::string_view kLockoutKph = "safety.lockoutKph";       ///< double, default 8.0
inline constexpr std::string_view kMediaVolume = "media.volume";           ///< int 0..100
inline constexpr std::string_view kMediaLastSource = "media.lastSource";   ///< string "usb" | "bluetooth"
inline constexpr std::string_view kPhoneLastDevice = "phone.lastDevice";   ///< string BT address
}  // namespace keys

/// Per-key driving-lockout rule (REQ-048, REQ-408), independent of the caller.
/// Locked while driving: every "hmi.*" key and safety.lockoutKph.
/// Exempt: media.volume, media.lastSource, phone.lastDevice (persisted by
/// services; volume is never locked). Unknown keys are rejected as NotFound first.
constexpr bool lockedWhileDriving(std::string_view key) noexcept {
    constexpr std::string_view hmiPrefix = "hmi.";
    return key.substr(0, hmiPrefix.size()) == hmiPrefix || key == keys::kLockoutKph;
}

inline constexpr double kDefaultLockoutKph = 8.0;  ///< REQ-049

enum class Theme : std::uint8_t { Day = 0, Night = 1 };

/// Driver-distraction state (ADR-004). locked = speed > threshold OR speed invalid (REQ-050).
struct LockoutState {
    bool locked{true};          ///< fail-safe default
    bool speedValid{false};
    double thresholdKph{kDefaultLockoutKph};
};

enum class HealthState : std::uint8_t { Unknown = 0, Running = 1, Restarting = 2, Failed = 3 };

/// Per-service health row for the diagnostics screen (REQ-009, REQ-007).
struct ServiceHealth {
    std::string unit;  ///< e.g. "oneo-mediad.service"
    HealthState state{HealthState::Unknown};
    std::uint32_t restarts{0};
    std::string lastFault;  ///< empty if none
};

struct VersionInfo {
    std::string component;  ///< "image", "oneo-app", "kernel", "bsp"
    std::string version;
};

}  // namespace oneo::system
