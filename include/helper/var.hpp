#ifndef VARIABLE_PROPERTY_HPP
#define VARIABLE_PROPERTY_HPP

#include <functional>

template <typename T>
class Var
{
public:
    Var(
        std::function<void(T)> setter,
        std::function<T()> getter
    )   :   _setter(setter), _getter(getter)
    {
    }

    operator T() const 
    { 
        return _getter(); 
    }

    Var<T>& operator =(const T &value)
    {
        _setter(value);
        return *this;
    }

    T& value() 
    { 
        return _value; 
    }

private:
    std::function<void(T)> _setter;
    std::function<T()> _getter;
    T _value;
};

#endif /* end of include guard :  VARIABLE_PROPERTY_HPP */
