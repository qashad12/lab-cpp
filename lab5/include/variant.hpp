/* Variant classes.
 * @file
 * @date 2018-08-12
 * @author Anonymous
 */

#ifndef __VARIANT_HPP__
#define __VARIANT_HPP__

#include <map>
#include <memory>
#include <variant>
#include <vector>

#include <boost/variant.hpp>

 //{ number
using number = std::variant<int, float>;
//}

//{ array
using array = std::vector<number>;
//}

//{ recursive_array
struct recursive_array :
    public std::vector<
        std::variant<number,
            std::shared_ptr<recursive_array>
        >
    >
{
    using vector::vector;
};
//}

//{ recursive_array2
struct recursive_array2 :
    public std::vector<
        std::variant<number,
            boost::recursive_wrapper<recursive_array2>
        >
    >
{
    using vector::vector;
};
//}

//{ variant_decorator
template<typename... Args>
struct variant_decorator : public std::variant<Args...>
{
    using variant_decorator::variant::variant;

    template<class T>
    T &as()
    {
        return const_cast<T &>(__as<T>());
    }

    template<class T>
    T const &as() const
    {
        return __as<T>();
    }

private:
    template <class T>
    T const &__as() const
    {
        if constexpr (std::disjunction_v<std::is_same<boost::recursive_wrapper<T>, Args>...>)
        {
            return std::get<boost::recursive_wrapper<T>>(*this).get();
        }
        else
        {
            return std::get<T>(*this);
        }
    }
};
//}

//{ recursive_map
struct recursive_map :
    public std::map<
        std::string,
        variant_decorator<
            int,
            std::string,
            boost::recursive_wrapper<recursive_map>, bool
        >
    >
{
    using map::map;
};
//}

#endif // __VARIANT_HPP__
