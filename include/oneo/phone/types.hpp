// SPDX-License-Identifier: Proprietary
// oneo/phone/types.hpp - phone/Bluetooth value types (REQ-038..047).
#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace oneo::phone {

/// Max stored pairings (REQ-039). Oldest-used is evicted on overflow.
inline constexpr std::size_t kMaxPairedDevices = 5;

struct Device {
    std::string address;  ///< "AA:BB:CC:DD:EE:FF"
    std::string name;
    bool paired{false};
    bool connected{false};
    bool hfp{false};   ///< hands-free profile connected
    bool a2dp{false};  ///< media profile connected
};

enum class PairingState : std::uint8_t {
    Idle = 0,
    Discovering = 1,
    AwaitingConfirmation = 2,  ///< numeric comparison shown to user (REQ-038)
    Pairing = 3,
    Failed = 4,
};

/// Pending SSP numeric-comparison request.
struct PairingRequest {
    std::string address;
    std::string name;
    std::uint32_t passkey{0};  ///< 6-digit code to display
};

enum class CallState : std::uint8_t { Idle = 0, Incoming = 1, Dialing = 2, Alerting = 3, Active = 4, Held = 5, Ended = 6 };

struct Call {
    std::uint32_t id{0};  ///< stable while the call exists
    CallState state{CallState::Idle};
    std::string number;
    std::string displayName;  ///< resolved from contacts, may be empty
};

struct Contact {
    std::string id;
    std::string name;
    std::vector<std::string> numbers;
};

enum class CallDirection : std::uint8_t { Incoming = 0, Outgoing = 1, Missed = 2 };

struct CallLogEntry {
    std::string number;
    std::string name;
    CallDirection direction{CallDirection::Incoming};
    std::chrono::system_clock::time_point time{};
};

}  // namespace oneo::phone
