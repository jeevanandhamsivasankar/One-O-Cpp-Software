// SPDX-License-Identifier: Proprietary
// oneo/phone/phone_service.hpp - IPhoneService, exported as org.oneo.Phone.
//
// Lockout (REQ-401, REQ-048, REQ-408): the core gets lockout state only via an
// injected core::ILockoutSource (backed by org.oneo.System DrivingLocked; unknown =
// locked) and rejects startDiscovery(), pair(), confirmPairing() and removeDevice()
// with DrivingLocked while locked, regardless of caller. connect(), calls and
// contacts are allowed while driving. Loop-thread confined.
#pragma once

#include "oneo/core/result.hpp"
#include "oneo/core/subscription.hpp"
#include "oneo/phone/types.hpp"

#include <cstdint>
#include <functional>
#include <string>
#include <vector>

namespace oneo::phone {

class IPhoneService {
public:
    struct Observer {
        std::function<void(const std::vector<Device>&)> onDevices;
        std::function<void(PairingState)> onPairingState;
        std::function<void(const PairingRequest&)> onPairingRequest;  ///< show code, ask user
        std::function<void(const std::vector<Call>&)> onCalls;
        std::function<void(std::uint32_t contactCount)> onContactsSynced;  ///< PBAP done (REQ-046)
    };

    virtual ~IPhoneService() = default;

    virtual std::vector<Device> devices() const = 0;  ///< paired + discovered
    virtual PairingState pairingState() const = 0;
    virtual std::vector<Call> calls() const = 0;
    virtual core::Subscription subscribe(Observer observer) = 0;

    // Pairing (REQ-038/039/401/408). Discovery auto-stops after 60 s, and is
    // stopped and any pending pairing cancelled when lockout becomes locked.
    /// DrivingLocked while locked.
    virtual core::Result<void> startDiscovery() = 0;
    virtual void stopDiscovery() = 0;
    /// DrivingLocked while locked.
    virtual void pair(const std::string& address, core::Completion<void> done) = 0;
    /// User answer to onPairingRequest; nothing is accepted without it (REQ-406).
    /// DrivingLocked while locked.
    virtual core::Result<void> confirmPairing(const std::string& address, bool accept) = 0;
    /// DrivingLocked while locked.
    virtual core::Result<void> removeDevice(const std::string& address) = 0;
    /// Allowed while driving (reconnect, REQ-040).
    virtual void connect(const std::string& address, core::Completion<void> done) = 0;

    // Calls (REQ-041..043). Audio routing/ducking is WirePlumber policy (REQ-044/045).
    virtual void dial(const std::string& number, core::Completion<std::uint32_t> done) = 0;
    virtual core::Result<void> answer(std::uint32_t callId) = 0;
    virtual core::Result<void> reject(std::uint32_t callId) = 0;
    virtual core::Result<void> hangup(std::uint32_t callId) = 0;

    // Contacts / log (REQ-046/047). Served from the local PBAP cache.
    virtual std::vector<Contact> searchContacts(const std::string& query, std::uint32_t limit) const = 0;
    virtual std::vector<CallLogEntry> callLog(std::uint32_t limit) const = 0;
};

}  // namespace oneo::phone
