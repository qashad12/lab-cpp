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
class image_iterator: public boost::iterator_adaptor<image_iterator<Iterator>,Iterator>
{
public:
    int width;
    int stride;
    Iterator row;
    image_iterator(Iterator it, size_t width, size_t stride) :
        boost::iterator_adaptor<image_iterator<Iterator>, Iterator>(it),
        width(width),
        stride(stride)
    {
        row = this->base_reference();
    }

private:
    friend class boost::iterator_core_access;

    void increment() { advance(1); }
    void decrement() { advance(-1); }

    void advance(typename image_iterator::difference_type n)
    {
        double d = this->base_reference() - row + n;
        std::ptrdiff_t delta = floor(d / width);
        std::ptrdiff_t col = d - delta * width;
        this->base_reference() += delta * stride + col - (this->base_reference() - row);
        row += delta * stride;
    }

    typename image_iterator::difference_type distance_to(const image_iterator& i) const
    {
        auto d = (i.base_reference() - i.row) - (this->base_reference() - row);
        auto e = i.row - row;
        return e / stride * width + d;
    }

};
//}

#endif // __ITERATOR_HPP__
