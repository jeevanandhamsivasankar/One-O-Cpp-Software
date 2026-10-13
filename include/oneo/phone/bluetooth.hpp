// SPDX-License-Identifier: Proprietary
// oneo/phone/bluetooth.hpp - backend seams for phoned (BlueZ / oFono / obexd).
//
// Target impls talk to BlueZ/oFono/obexd over D-Bus (Linux-only, CMake
// if(UNIX AND NOT APPLE)). Host: scripted fakes. Events arrive on the loop thread.
#pragma once

#include "oneo/core/result.hpp"
#include "oneo/phone/types.hpp"

#include <cstdint>
#include <functional>
#include <string>
#include <vector>

namespace oneo::phone {

/// BlueZ adapter/device management + SSP agent.
class IBluetoothAdapter {
public:
    struct Events {
        std::function<void(const Device&)> onDeviceChanged;
        std::function<void(const std::string& address)> onDeviceRemoved;
        std::function<void(const PairingRequest&)> onConfirmationRequested;  ///< agent RequestConfirmation
    };
    virtual ~IBluetoothAdapter() = default;
    virtual void setEvents(Events events) = 0;
    virtual std::vector<Device> knownDevices() const = 0;
    virtual core::Result<void> setDiscovering(bool on) = 0;
    virtual void pair(const std::string& address, core::Completion<void> done) = 0;
    virtual core::Result<void> replyConfirmation(const std::string& address, bool accept) = 0;
    virtual core::Result<void> remove(const std::string& address) = 0;
    virtual void connect(const std::string& address, core::Completion<void> done) = 0;
};

/// oFono HFP hands-free voice calls.
class IHandsFree {
public:
    using CallsHandler = std::function<void(const std::vector<Call>&)>;
    virtual ~IHandsFree() = default;
    virtual void setHandler(CallsHandler handler) = 0;
    virtual void dial(const std::string& number, core::Completion<std::uint32_t> done) = 0;
    virtual core::Result<void> answer(std::uint32_t callId) = 0;
    virtual core::Result<void> hangup(std::uint32_t callId) = 0;  ///< also rejects incoming
};

/// obexd PBAP client.
class IPhonebookClient {
public:
    struct Phonebook {
        std::vector<Contact> contacts;
        std::vector<CallLogEntry> callLog;
    };
    virtual ~IPhonebookClient() = default;
    virtual void sync(const std::string& address, core::Completion<Phonebook> done) = 0;
    virtual void cancel() = 0;
};

}  // namespace oneo::phone
