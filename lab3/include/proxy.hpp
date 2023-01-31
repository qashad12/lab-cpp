/* Proxy object.
 * @file
 * @date 2018-08-07
 * @author Anonymous
 */

#ifndef __PROXY_HPP__
#define __PROXY_HPP__

#include <mutex>

template<class T, class MutexInjection = std::mutex>
class ptr_holder
{
public:
    ptr_holder(T* ptr): ptr_(ptr) {}

    class proxy
    {
    public:
        proxy(T *ptr, MutexInjection &mut)
            : _ptr(ptr), _lock(mut)
        {
        }

        T *operator -> () const
        {
            return this->_ptr;
        }

    private:
        T* _ptr;
        std::lock_guard<MutexInjection> _lock;
    };

    proxy operator -> () const
    {
        return proxy(ptr_, mutex_);
    }

private:
    T* ptr_;
    mutable MutexInjection mutex_;
};

#endif // __PROXY_HPP__
