#ifndef ONIDEV_CORE_SIGNAL_H_INCLUDED
#define ONIDEV_CORE_SIGNAL_H_INCLUDED

#include <functional>
#include "signal.incl"

namespace od
{
   
template <typename... Args>
class Signal
{
    // http://stackoverflow.com/questions/21192659/variadic-templates-and-stdbind
    template<class T, int... Is>
    void connect_member(void (T::*field)(Args...), T* t, int_sequence<Is...>)
    {
        _slot = std::bind(field, t, placeholder_template<Is>{}...);
    }
    
public:
    typedef std::function<void(Args...)> Slot;
    
    template<class T>
    void connect(void (T::*field)(Args...), T* t)
    {
        connect_member(field, t, make_int_sequence<sizeof...(Args)>{});
    }
    void connect(Slot const& slot) const
    {
        _slot = slot;
    }
    void disconnect() const
    {
        _slot = Slot();
    }
    void emit(Args&&... args)
    {
        if(_slot)
            _slot(std::forward<Args>(args)...);
    }
    Signal& operator=(Signal const& other)
    {
        disconnect();
    }

private:
    mutable Slot _slot;
};

}

#endif
