// SPDX-License-Identifier: Proprietary
// oneo/ipc/bus_names.hpp - D-Bus names/paths shared by service adapters
// (sdbus-c++) and HMI proxies (QtDBus). Must match include/oneo/dbus/*.xml.
#pragma once

#include "oneo/core/error.hpp"

#include <string>
#include <string_view>

namespace oneo::ipc {

inline constexpr std::string_view kVehicleService = "org.oneo.VehicleSignals";
inline constexpr std::string_view kVehiclePath = "/org/oneo/VehicleSignals";
inline constexpr std::string_view kMediaService = "org.oneo.Media";
inline constexpr std::string_view kMediaPath = "/org/oneo/Media";
inline constexpr std::string_view kPhoneService = "org.oneo.Phone";
inline constexpr std::string_view kPhonePath = "/org/oneo/Phone";
inline constexpr std::string_view kSystemService = "org.oneo.System";
inline constexpr std::string_view kSystemPath = "/org/oneo/System";

/// Interface name == bus name for every service; contract version property.
inline constexpr unsigned kInterfaceVersion = 1;

/// Coalescing window for PropertiesChanged emission (ADR-002).
inline constexpr unsigned kCoalesceMs = 50;

inline constexpr std::string_view kErrorPrefix = "org.oneo.Error.";

/// Full D-Bus error name, e.g. "org.oneo.Error.Timeout".
inline std::string dbusErrorName(core::ErrorCode code) {
    return std::string(kErrorPrefix) + core::errorName(code);
}

}  // namespace oneo::ipc
