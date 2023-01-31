/* Image iterator.
 * @file
 * @date 2018-08-05
 * @author Anonymous
 */

#ifndef __ITERATOR_HPP__
#define __ITERATOR_HPP__

#include <cmath>
#include <iterator>
#include <type_traits>
#include <utility>

#include <boost/iterator/iterator_adaptor.hpp>

//{ image iterator
template<class Iterator>
class image_iterator : public boost::iterator_adaptor<
    image_iterator<Iterator>,
    Iterator
>
{
public:
    image_iterator(Iterator iterator, size_t w, size_t s) :
        base_class(iterator), w(w), s(s), start(iterator)
    {}
    Iterator rf() { return this->base_reference(); }

private:
    friend class boost::iterator_core_access;
    typedef boost::iterator_adaptor<
        image_iterator<Iterator>,
        Iterator
    > base_class;

    std::ptrdiff_t w, s;
    Iterator start;

    void increment()
    {
        //++this->base_reference();
        advance(1);
    }

    void decrement()
    {
        //--this->base_reference();
        advance(-1);
    }

    void advance(typename image_iterator::difference_type n)
    {
        if (n < 0) {
            n = -n;
            this->base_reference() -= (n / w) * s;
            n %= w;
            if ((this->base_reference() - start) % s < n)
                this->base_reference() -= n + s - w;
            else
                this->base_reference() -= n;
        } else {
            this->base_reference() += (n / w) * s;
            n %= w;
            if ((this->base_reference() - start) % s + n >= w)
                this->base_reference() += n + s - w;
            else
                this->base_reference() += n;
        }
    }

    typename image_iterator::difference_type distance_to(const image_iterator &it) const
    {
        std::ptrdiff_t d = it.base_reference() - this->base_reference();
        if (d >= 0) {
            return d / s * w + d % w;
        } else {
            d = -d;
            return -(d / s * w + d % w);
        }
    }
};
//}

#endif // __ITERATOR_HPP__
