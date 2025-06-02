#pragma once
#include <cstdint>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <variant>
#include <vector>

namespace Saturn {
    using i16 = int16_t;
    using i32 = int32_t;
    using i64 = int64_t;
    using u16 = uint16_t;
    using u32 = uint32_t;
    using u64 = uint64_t;
    using f32 = float;
    using f64 = double;
    using byte = uint8_t;
    using sbyte = int8_t;
    using String = std::string;
    using CString = const char*;
    using WString = std::wstring;

    template<typename T>
    using Ref = std::shared_ptr<T>;
    template<typename T, typename... Args>
        requires std::is_constructible_v<T, Args...>
    Ref<T> createRef(Args&&... args) {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    using Weak = std::weak_ptr<T>;
    template<typename T>
    Weak<T> fromRef(const Ref<T>& ref) {
        return ref;
    }

    template<typename T>
    using Unique = std::unique_ptr<T>;
    template<typename T, typename... Args>
        requires std::is_constructible_v<T, Args...>
    Unique<T> createUnique(Args&&... args) {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    using Nullable = std::optional<T>;
    template<typename T, typename... Args>
        requires std::is_constructible_v<T, Args...>
    Nullable<T> createNullable(Args&&... args) {
        return std::make_optional<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    bool isNull(const Nullable<T>& opt) {
        return !opt.has_value();
    }

    template<typename T>
    T valueOrDefault(const Nullable<T>& opt, const T& defaultValue) {
        return opt.value_or(defaultValue);
    }

    template<typename... Types>
    using Multiple = std::variant<Types...>;

    template<typename Variant>
    constexpr size_t getActiveIndex(const Variant& v) {
        return v.index();
    }

    template<typename T, typename Variant>
    bool holdsType(const Variant& v) {
        return std::holds_alternative<T>(v);
    }

    template<typename T>
    using Vector = std::vector<T>;

    template<typename TKey, typename TValue>
    using Map = std::map<TKey, TValue>;

    template<typename TKey, typename TValue>
    using UnorderedMap = std::unordered_map<TKey, TValue>;

    template<typename TKey, typename TValue>
    using UnorderedSet = std::unordered_set<TKey, TValue>;
}
