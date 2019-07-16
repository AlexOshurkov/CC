#pragma once

#include "defines.hpp"

//  AlexOshurkov
//  Implementation of shared pointer

//  Notes:
//  m_prefcnt isn't multithread safe, we may want to add std::atomic or unique locks

namespace AO {
    
    template<typename T>
    class shared_ptr 
    {
    //  Ref counter
        unsigned long* m_prefcnt = nullptr; 
        T* m_pobj = nullptr;
        
        shared_ptr<T>(unsigned long* prefcnt, T* pobj) :
            m_prefcnt(prefcnt),
            m_pobj(pobj)
        {
            DBG_PRINT

            ++(*m_prefcnt); //  we don't check nullptr beacuse we assume there is only one way to create our shared ptr - by make_shared
        }

        template <typename T>
        friend shared_ptr<T> create_shared(T*);

    protected:

        void copy_obj(const shared_ptr<T>& robj)
        {
            m_prefcnt = robj.m_prefcnt;
            m_pobj = robj.m_pobj;

            if (robj.m_prefcnt != nullptr)
                ++(*m_prefcnt);
        }

        void move_obj(shared_ptr<T>& robj)
        {
            delete m_prefcnt;
            delete m_pobj;
            m_prefcnt = robj.m_prefcnt;
            m_pobj = robj.m_pobj;
            robj.m_prefcnt = nullptr;
            robj.m_pobj = nullptr;
        }

    public:

        shared_ptr<T>() {}  //  default constructor
        shared_ptr<T>(const shared_ptr<T>& robj)
        {
            DBG_PRINT

            copy_obj(robj);
        }

        shared_ptr<T>(shared_ptr<T>&& robj)
        {
            DBG_PRINT

            move_obj(robj);
        }

        shared_ptr<T>& operator=(const shared_ptr<T>& robj)
        {
            DBG_PRINT

            copy_obj(robj);
            return *this;
        }

        shared_ptr<T>& operator=(shared_ptr<T>&& robj)
        {
            DBG_PRINT

            move_obj(robj);
            return *this;
        }

        ~shared_ptr<T>() // we don't need virtual destructor for simple standalone class
        {
            DBG_PRINT

            if (m_prefcnt != nullptr)
            {
                --(*m_prefcnt);

                if (*m_prefcnt == 0) 
                {
                    delete m_pobj;    //  it's legal to delete "nullptr", so we can checking overhead
                    delete m_prefcnt;
                    m_pobj = nullptr;
                    m_prefcnt = nullptr;
                }
            }
        }

        T* get()
        {
            return m_pobj;
        }

        const T* get() const
        {
            return m_pobj;
        }


        T& operator*()
        {
            return *get();
        }

        T* operator -> ()
        {
            DBG_PRINT

            return get();
        }

        operator bool() const
        {
            return m_prefcnt != nullptr && m_pobj != nullptr;
        }

        bool operator==(const shared_ptr<T>& robj) const
        {
            return m_prefcnt == robj.m_prefcnt && m_pobj == robj.m_pobj;
        }
    };
   
    //  There is no support of custom allocator
    //  Main purpose of make_shared to avoid memory leaking during partial initialization of shared_ptr
    //  If something goes wrong we delete both heap allocated memory blocks
    //  This is kind of "naive" implementation based of my khowledge of its purpose


    template <typename T>
    shared_ptr<T> create_shared(T* pobj)
    {
        unsigned long* prefcnt = nullptr;

        try
        {
            prefcnt = new unsigned long(0);
            return shared_ptr<T>(prefcnt, pobj);
        }
        catch (...)
        {
            delete prefcnt;
        }

        return shared_ptr<T>();
    }

    template <typename T>
    shared_ptr<T> make_shared(const T& robj)
    {
        T* pobj = nullptr;

        try
        {
            pobj = new T(robj);
            return create_shared(pobj);
        }
        catch (...)
        {
            delete pobj;
        }

        return shared_ptr<T>();
    }

    template <typename T, typename ... Args>
    shared_ptr<T> make_shared(Args&& ... args)
    {
        T* pobj = nullptr;

        try
        {
            pobj = new T(args...);
            return create_shared(pobj);
        }
        catch (...)
        {
            delete pobj;
        }

        return shared_ptr<T>();
    }

}  //  namespace AO