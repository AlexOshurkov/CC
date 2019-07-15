#pragma once

#include "node.hpp"

namespace AO {

    template <typename T>
    class queue_t
    {
        shared_ptr<node_t<T>> first;
        shared_ptr<node_t<T>> last;

        public:

        queue_t() 
        {}

        void push_back(const T& robj)
        {
            if (first == last)
            {
                if (!first)
                    first = make_shared(node_t<T>());

                first->val = robj;
            }
            else
            {

                if (last)
                {
                    shared_ptr<node_t<T>> tnode = last;
                    last = make_shared(node_t<T>());
                    last->val = robj;
                    last->right = tnode;
                    tnode->left = last;
                }
                else
                {
                    last = make_shared(node_t<T>());
                    last->val = robj;
                    first->left = last;
                    last->right = first;
                }
            }
        }

        T& get_front()
        {
            return first->val;
        }

        void pop_front()
        {
            if (first == last)
            {
                if (first)
                {
                    first = shared_ptr<node_t<T>>();
                    last = first;
                }
            }
            else
            {
                first = first->left;
            }
        }

        bool is_empty() const
        {
            return first == last && !first;
        }
    };
}  //  namespace AO
