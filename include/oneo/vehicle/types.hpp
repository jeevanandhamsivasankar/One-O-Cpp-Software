// SPDX-License-Identifier: Proprietary
// oneo/vehicle/types.hpp - vehicle signal value types (REQ-020, REQ-025, REQ-201/202).
#pragma once

#include "oneo/core/event_loop.hpp"

#include <array>
#include <cstdint>
#include <string_view>
#include <variant>

namespace oneo::vehicle {

/// Logical signals exposed to clients. DBC mapping lives in the backend, not here
/// (OEM DBC is an assumption, D-06). Append only; values are stable.
enum class SignalId : std::uint16_t {
    // Read-only (REQ-201)
    VehicleSpeed = 1,    ///< double, km/h
    Gear = 2,            ///< int32, see Gear
    DoorOpen = 3,        ///< int32 bitmask, see DoorMask
    LampWarnings = 4,    ///< int32 bitmask, see LampMask
    Ignition = 5,        ///< int32, see IgnitionState
    AmbientDark = 6,     ///< bool, true = dark (theme auto-switch REQ-016)
    HeadlightsOn = 7,    ///< bool
    // Settable, allow-listed (REQ-202, REQ-407)
    LightingMode = 100,     ///< int32, see LightingMode
    DistanceUnit = 101,     ///< int32, see DistanceUnit
    ClimateTempUnit = 102,  ///< int32, see TempUnit
    ClimateMode = 103,      ///< int32, see ClimateMode
};

/// D-Bus property name of a signal (e.g. "VehicleSpeed"); empty if unknown.
constexpr std::string_view signalName(SignalId id) noexcept {
    switch (id) {
        case SignalId::VehicleSpeed: return "VehicleSpeed";
        case SignalId::Gear: return "Gear";
        case SignalId::DoorOpen: return "DoorOpen";
        case SignalId::LampWarnings: return "LampWarnings";
        case SignalId::Ignition: return "Ignition";
        case SignalId::AmbientDark: return "AmbientDark";
        case SignalId::HeadlightsOn: return "HeadlightsOn";
        case SignalId::LightingMode: return "LightingMode";
        case SignalId::DistanceUnit: return "DistanceUnit";
        case SignalId::ClimateTempUnit: return "ClimateTempUnit";
        case SignalId::ClimateMode: return "ClimateMode";
    }
    return {};
}

inline constexpr std::array<SignalId, 11> kAllSignals{
    SignalId::VehicleSpeed, SignalId::Gear,         SignalId::DoorOpen,        SignalId::LampWarnings,
    SignalId::Ignition,     SignalId::AmbientDark,  SignalId::HeadlightsOn,    SignalId::LightingMode,
    SignalId::DistanceUnit, SignalId::ClimateTempUnit, SignalId::ClimateMode};

enum class Gear : std::int32_t { Park = 0, Reverse = 1, Neutral = 2, Drive = 3, Unknown = 15 };
enum class IgnitionState : std::int32_t { Off = 0, Accessory = 1, On = 2, Start = 3 };
enum DoorMask : std::int32_t { FrontLeft = 1, FrontRight = 2, RearLeft = 4, RearRight = 8, Trunk = 16, Hood = 32 };
enum LampMask : std::int32_t { LowBeamFault = 1, HighBeamFault = 2, IndicatorFault = 4, BrakeLampFault = 8, FogLampFault = 16 };
enum class LightingMode : std::int32_t { Off = 0, Auto = 1, Parking = 2, LowBeam = 3 };
enum class DistanceUnit : std::int32_t { Kilometres = 0, Miles = 1 };
enum class TempUnit : std::int32_t { Celsius = 0, Fahrenheit = 1 };
enum class ClimateMode : std::int32_t { Off = 0, Auto = 1, Manual = 2, Defrost = 3 };

/// Signal payload. monostate = never received.
using SignalValue = std::variant<std::monostate, bool, std::int32_t, double>;

/// One sample as published to clients (ADR-002: {value, valid, timestamp}).
struct SignalSample {
    SignalId id{SignalId::VehicleSpeed};
    SignalValue value{};
    bool valid{false};            ///< false if never received or validity timeout elapsed (REQ-025)
    core::TimePoint timestamp{};  ///< monotonic time of last reception
};

/// Static per-signal metadata (from DBC config).
struct SignalSpec {
    SignalId id{SignalId::VehicleSpeed};
    core::Duration validityTimeout{500};  ///< sample marked invalid after this without frames
    bool writable{false};                 ///< member of the write allow-list (REQ-407)
    std::int32_t minValue{0};             ///< allowed range for writable int32 signals
    std::int32_t maxValue{0};
};

}  // namespace oneo::vehicle
