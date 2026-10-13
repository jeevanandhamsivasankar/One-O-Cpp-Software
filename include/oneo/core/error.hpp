// SPDX-License-Identifier: Proprietary
// oneo/core/error.hpp - error vocabulary shared by all One-O modules.
//
// Policy (docs/architecture/software.md section 6): no exceptions cross a module
// boundary. Recoverable failures are returned as oneo::core::Error inside a
// Result<T>. Each ErrorCode maps 1:1 to a D-Bus error name org.oneo.Error.<Name>.
#pragma once

#include <cstdint>
#include <string>
#include <utility>

namespace oneo::core {

/// Stable error codes. Values are part of the D-Bus contract; append only.
enum class ErrorCode : std::uint8_t {
    InvalidArgument = 1,  ///< org.oneo.Error.InvalidArgument - bad name/value/range.
    NotAllowed = 2,       ///< org.oneo.Error.NotAllowed - not on allow-list (REQ-407) or policy.
    DrivingLocked = 3,    ///< org.oneo.Error.DrivingLocked - blocked by lockout (REQ-048, REQ-401).
    NotFound = 4,         ///< org.oneo.Error.NotFound - unknown id/device/key.
    Unavailable = 5,      ///< org.oneo.Error.Unavailable - backend/device/signal not present.
    Timeout = 6,          ///< org.oneo.Error.Timeout - no confirmation in time (REQ-027/028).
    Busy = 7,             ///< org.oneo.Error.Busy - conflicting operation in progress.
    IoError = 8,          ///< org.oneo.Error.IoError - storage/bus I/O failure.
    Cancelled = 9,        ///< org.oneo.Error.Cancelled - operation superseded or service stopping.
    Internal = 10,        ///< org.oneo.Error.Internal - bug; logged with context.
};

/// D-Bus error name suffix for a code (e.g. "Timeout").
constexpr const char* errorName(ErrorCode code) noexcept {
    switch (code) {
        case ErrorCode::InvalidArgument: return "InvalidArgument";
        case ErrorCode::NotAllowed: return "NotAllowed";
        case ErrorCode::DrivingLocked: return "DrivingLocked";
        case ErrorCode::NotFound: return "NotFound";
        case ErrorCode::Unavailable: return "Unavailable";
        case ErrorCode::Timeout: return "Timeout";
        case ErrorCode::Busy: return "Busy";
        case ErrorCode::IoError: return "IoError";
        case ErrorCode::Cancelled: return "Cancelled";
        case ErrorCode::Internal: return "Internal";
    }
    return "Internal";
}

/// Error value: machine-readable code + human-readable (non-localised) detail for logs.
struct Error {
    ErrorCode code{ErrorCode::Internal};
    std::string message;

    Error() = default;
    Error(ErrorCode c, std::string msg = {}) : code(c), message(std::move(msg)) {}
};

inline bool operator==(const Error& a, const Error& b) noexcept { return a.code == b.code; }
inline bool operator!=(const Error& a, const Error& b) noexcept { return !(a == b); }

}  // namespace oneo::core
