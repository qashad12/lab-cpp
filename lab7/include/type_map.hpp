/* Map of types.
 * @file
 * @date 2018-08-25
 * @author Anonymous
 */

#ifndef __TYPE_MAP_HPP__
#define __TYPE_MAP_HPP__

#include <array>
#include <tuple>

namespace detail {
    template <class T, class Tuple>
    struct type_to_index;

    template <class T, class... Ts>
    struct type_to_index<T, std::tuple<T, Ts...>> {
        constexpr static size_t value = 0;
    };

    template <class T, class U, class... Ts>
    struct type_to_index<T, std::tuple<U, Ts...>> {
        constexpr static size_t value = 1 + type_to_index<T, std::tuple<Ts...>>::value;
    };
}


template<typename value_type, typename... Types>
class type_map : public std::array<value_type, sizeof...(Types)> {
public:
    using TypemapValueT = value_type;
    template <class T>
    value_type &as() {
        return std::get<detail::type_to_index<T, std::tuple<Types...>>::value>(*this);
    }

    template <class T>
    value_type as() const {
        return std::get<detail::type_to_index<T, std::tuple<Types...>>::value>(*this);
    }
};


namespace std {
    template <class T, class type_map>
    decltype(auto) get(type_map &x) {
        return x.template as<T>();
    }
}

#endif // __TYPE_MAP_HPP__
