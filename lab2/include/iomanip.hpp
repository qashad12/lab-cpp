/* Custom manipulators.
 * @file
 * @date 2018-08-05
 * @author Anonymous
 */

#ifndef __IOMANIP_HPP__
#define __IOMANIP_HPP__

#include <iostream>

namespace {
    class __endm {
        friend std::ostream &operator <<(std::ostream &out, const __endm &) {
            return out << "[eol]\n";
        }
    };

    class __squares {
        std::ostream *save;

        friend __squares &operator <<(std::ostream &out, __squares &sq) {
            sq.save = &out;
            return sq;
        }

        template <class value_type>
        friend std::ostream &operator <<(__squares &sq, const value_type &val) {
            return *sq.save << '[' << val << ']';
        }
    };

    class __add_base;

    template <class value_type>
    struct __add_impl {
        const value_type &save;
        std::ostream *stream;

        __add_impl(const value_type &val, std::ostream *out)
            : save(val), stream(out)
        {}

        friend std::ostream &operator <<(const __add_impl<value_type> &out, const value_type &val) {
            return *out.stream << (out.save + val);
        }
    };

    class __add_base {
        std::ostream *save;

        friend __add_base &operator <<(std::ostream &out, __add_base &add) {
            add.save = &out;
            return add;
        }

        template <class value_type>
        friend __add_impl<value_type> operator <<(const __add_base &out, const value_type &val) {
            return __add_impl<value_type>(val, out.save);
        }
    };

}

[[maybe_unused]] inline __endm endm;
[[maybe_unused]] inline __squares squares;
[[maybe_unused]] inline __add_base add;

//}

#endif // __IOMANIP_HPP__
