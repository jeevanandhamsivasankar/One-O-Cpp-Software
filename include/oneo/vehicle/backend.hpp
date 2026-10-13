// SPDX-License-Identifier: Proprietary
// oneo/vehicle/backend.hpp - pluggable vehicle backends (REQ-021): mock or CAN.
#pragma once

#include "oneo/core/result.hpp"
#include "oneo/vehicle/types.hpp"

#include <array>
#include <cstdint>
#include <functional>
#include <vector>

namespace oneo::vehicle {

/// Classic CAN frame (platform-neutral; SocketCAN mapping lives in the impl).
struct CanFrame {
    std::uint32_t id{0};  ///< 11-bit or 29-bit identifier
    bool extended{false};
    std::uint8_t dlc{0};  ///< 0..8
    std::array<std::uint8_t, 8> data{};
};

/// Raw CAN channel. Target: SocketCAN can0 (Linux-only impl, built under
/// if(UNIX AND NOT APPLE)). Host: in-memory loopback for tests.
class ICanChannel {
public:
    using FrameHandler = std::function<void(const CanFrame&)>;
    virtual ~ICanChannel() = default;
    /// Frames are delivered on the loop thread.
    virtual core::Result<void> open(FrameHandler onFrame) = 0;
    virtual core::Result<void> send(const CanFrame& frame) = 0;
    virtual void close() = 0;
};

/// Decoded-signal backend consumed by the vehicled core. Implementations:
/// DbcCanBackend (ICanChannel + DBC codec) and MockBackend (scripted values).
/// Selected by --backend=mock|can and CMake option ONEO_VEHICLE_BACKEND.
class IVehicleBackend {
public:
    using Decoded = std::function<void(SignalId, const SignalValue&)>;
    virtual ~IVehicleBackend() = default;

    /// Static metadata incl. allow-list; read once at start.
    virtual std::vector<SignalSpec> specs() const = 0;
    /// Begin delivering decoded values on the loop thread.
    virtual core::Result<void> start(Decoded onSignal) = 0;
    virtual void stop() = 0;
    /// Encode and transmit a write. Fire-and-forget; confirmation arrives as a
    /// later Decoded callback for the same signal. Validation is done by the core.
    virtual core::Result<void> write(SignalId id, std::int32_t value) = 0;
};

}  // namespace oneo::vehicle
