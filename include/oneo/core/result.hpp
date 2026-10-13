// SPDX-License-Identifier: Proprietary
// oneo/core/result.hpp - Result<T>: value-or-Error return type (C++17 stand-in for std::expected).
#pragma once

#include "oneo/core/error.hpp"

#include <functional>
#include <type_traits>
#include <utility>
#include <variant>

namespace oneo::core {

/// Holds either a T or an Error. Accessing the wrong alternative is a programming
/// error (asserts via std::get / bad_variant_access in debug; never relied on).
template <typename T>
class [[nodiscard]] Result {
    static_assert(!std::is_same_v<T, Error>, "Result<Error> is not allowed");

public:
    Result(T value) : v_(std::in_place_index<0>, std::move(value)) {}
    Result(Error error) : v_(std::in_place_index<1>, std::move(error)) {}

    bool ok() const noexcept { return v_.index() == 0; }
    explicit operator bool() const noexcept { return ok(); }

    const T& value() const& { return std::get<0>(v_); }
    T& value() & { return std::get<0>(v_); }
    T&& value() && { return std::get<0>(std::move(v_)); }

    const Error& error() const& { return std::get<1>(v_); }

    T valueOr(T fallback) const& { return ok() ? value() : std::move(fallback); }

private:
    std::variant<T, Error> v_;
};

/// Result for operations without a payload.
template <>
class [[nodiscard]] Result<void> {
public:
    Result() = default;
    Result(Error error) : err_(std::move(error)), ok_(false) {}

    bool ok() const noexcept { return ok_; }
    explicit operator bool() const noexcept { return ok_; }
    const Error& error() const& { return err_; }

private:
    Error err_{};
    bool ok_{true};
};

/// Completion callback for asynchronous operations. Always invoked exactly once,
/// on the owning event-loop thread (see IEventLoop), including on cancellation.
template <typename T>
using Completion = std::function<void(Result<T>)>;

}  // namespace oneo::core
