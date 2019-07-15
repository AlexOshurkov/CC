#pragma once

#include "shared_ptr.hpp"

namespace AO {

    template <typename T>
    struct node_t 
    {
        T val = T();
        shared_ptr<node_t<T>> left;
        shared_ptr<node_t<T>> right;
        
        node_t() = default;
        node_t(const node_t<T>&) = default;
        node_t(const T& val_) : val(val_) {}
    };

}  //  namespace AO
