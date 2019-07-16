#include <iostream>
#include <vector>

#include "lib/shared_ptr.hpp" //  import from local path 
#include "lib/queue.hpp"

namespace AO {

    using std::cout;
    using std::vector;

struct testClass {

    int _vi = 0;

    testClass(int vi) :
        _vi(vi) 
    {
        cout << "\n ctor(" << _vi << ")";
    }

    void show()
    {
        cout << "\n    show: " << _vi;
    }

    ~testClass()
    {
        cout << "\n dtor(" << _vi << ")";
    }
};

void testSharedPtr() {

    DBG_PRINT;

    shared_ptr<testClass> pc1 = AO::make_shared<testClass>(1);
    pc1->show();
    vector<AO::shared_ptr<testClass> > vec;
    vector<AO::shared_ptr<testClass> > vec2;
    vec.push_back(pc1);
    vec.push_back(AO::make_shared<testClass>(2));
    vec.emplace_back(AO::make_shared<testClass>(3));
    shared_ptr<testClass>&& rrobj = AO::make_shared<testClass>(4);
    vec.push_back(rrobj);
    pc1 = AO::make_shared<testClass>(5);
    pc1->show();

    shared_ptr <testClass> pc2 = pc1;
    shared_ptr <testClass> pc3;

    testClass tc(6);

    shared_ptr <testClass> pc4 = make_shared(tc);
    pc4->show();

    shared_ptr <testClass> pc5 = make_shared(testClass(7));
    pc5->show();

    if (pc2 && !pc3)
        cout << "\n check operator bool: ok";
    else
        cout << "\n check operator bool: FAIL";
    
    if (pc2 == pc1 && pc2 != pc3 && pc3 == pc3)
        cout << "\n check operator == : ok";
    else
        cout << "\n check operator == : FAIL";
}

void testQueue()
{
    queue_t<int> q1;

    int i = 0;
    for (i = 1; i <= 5; ++i)
        q1.push_back(i);

    for (i = 3; i > 0; --i);
        q1.pop_front();;

    for (i = 10; i <= 15; ++i)
        q1.push_back(i);

    while (!q1.is_empty())
    {
        cout << "\n 2 " << q1.get_front();
        q1.pop_front();
    }
}

} // namesapce AO