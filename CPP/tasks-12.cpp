#include "stdafx.h"
#pragma hdrstop

mutex mtx;

static void workerFunc(string s, int n) {

    for (int i = 0; i < n; ++i) {
        {
            lock_guard<mutex> l(mtx);
            cout << "\n workeraFunc: " << s << ", " << i;
        }
        this_thread::sleep_for(200ms);
    }
}

struct worker_t {
    string str = "worker msg";
    void workerFunc(string s, int n) {
        for (int i = 0; i < n; ++i) {
            {
                lock_guard<mutex> l(mtx);
                cout << "\n worker_t::workeraFunc: " << s << " msg: " << str << ", " << i;
            }
            this_thread::sleep_for(300ms);
        }
    }

    void operator()(string s, int n) {
        workerFunc(s, n);
    }
};

typedef void(worker_t::* pworker_t)(string, int);
static void testThreads() {
    cout << "\n >>> testThreads <<<";

    worker_t wr1;

    auto func1 = bind(&worker_t::workerFunc, wr1, placeholders::_1, placeholders::_2);
    auto func2 = &workerFunc;

    // thread 1
    thread th1(workerFunc, "thread 1", 5);
    thread th2(workerFunc, "thread 2", 7);
    thread th3(&worker_t::workerFunc, wr1, "thread 3", 4);
    thread th4(wr1, "thread 4", 4);

    th1.join();
    th2.join();
    th3.join();
    th4.join();

    func1("standalone call 1", 3);
    func2("standalone call 2", 3);
    wr1("standalone call 3", 3);

}

static SLNode* reverseSL(SLNode* node) {
    SLNode* pnode = nullptr;

    while (node != nullptr) {
        SLNode* nnode = node->next;
        node->next = pnode;
        pnode = node;
        node = nnode;
    }
    return pnode;
}

static void testReverseSL() {
    cout << "\n >>> testReverseSL <<<";
    SLNode* list = createSLList({ 1,2 });
    cout << "\n Created list: ";
    printSLList(list);
    SLNode* rlist = reverseSL(list);
    cout << "\n Reversed list: ";
    printSLList(rlist);

}

/*
2234 blah....
A1235 Blah blah
B1234 xyz xyz
A1234 Blah blah
1345 xyz


// 1 - print all number id
  2234 blah...template
  1345 xyz
// 2 -

A1234 Blah blah
A1235 Blah blah
B1234 xyz xyz
*/

struct mykv_t {
    string key;
    string val;

    bool operator<(const mykv_t& kv) const {

        return val < kv.val || key < kv.key;
    }

};

static vector<mykv_t> parse(const string& str) {

    vector<mykv_t> kv_u; // unsorted
    vector<mykv_t> kv_s; // sorted, O(log n)

    stringstream ss(str);
    while (!ss.eof()) {
        string sline;
        std::getline(ss, sline);
        auto spacepos = sline.find(' ');
        auto skey = sline.substr(0, spacepos);
        auto sval = sline.substr(spacepos + 1);

        if (skey[0] >= '0' && skey[0] <= '9')
            kv_u.push_back({ skey, sval });
        else
            kv_s.push_back({ skey, sval });
    }

    sort(begin(kv_s), end(kv_s)); 
    kv_u.insert(end(kv_u), begin(kv_s), end(kv_s));
    return kv_u;
}

static void testParse() {
    cout << "\n >>> testParse <<<";
    string str = "2234 blah blah\n"
        "A1235 Blah blah\n"
        "B1234 xyz xyz\n"
        "A1234 Blah blah\n"
        "1345 xyz";

    vector<mykv_t> kv = parse(str);
    for (const auto& v : kv)
        cout << "\n key: " << v.key << ", val: " << v.val;
}


static SLNode* sumSLNodes(SLNode* l1, SLNode* l2) {


    SLNode* rlist = nullptr;
    SLNode* rhead = nullptr;
    auto oversum = 0;
    printSLList(l1);
    cout << " + ";
    printSLList(l2);
    l1 = reverseSL(l1);
    l2 = reverseSL(l2);

    while (l1 != nullptr || l2 != nullptr || oversum != 0) {

        auto tsum = 0;

        if (rlist == nullptr) {
            rlist = new SLNode();
            rhead = rlist;
        }
        else {
            rlist->next = new SLNode();
            rlist = rlist->next;
        }


        if (l1 != nullptr)
            tsum += l1->val;

        if (l2 != nullptr)
            tsum += l2->val;

        tsum += oversum;
        rlist->val = tsum % 10;
        oversum = tsum / 10;

        if (l1 != nullptr)
            l1 = l1->next;

        if (l2 != nullptr)
            l2 = l2->next;
    }

    return reverseSL(rhead);
}

static void testSumSL() {
    SLNode* l1 = createSLList({ 9,9,8,9,9,9,9 });
    SLNode* l2 = createSLList({ 1  });
    cout << "\n >>> testSumSL <<< \n";

    SLNode* rlist = sumSLNodes(l1, l2);
    cout << " = ";
    printSLList(rlist);
}

class InitManager
{
public:
    typedef std::function<void()> myfunc_t;

    static void Add(myfunc_t function)
    {
        functions.push_back(function);
    }

    static void Init()
    {
        for (auto f : functions)
        {
            f();
        }
    }

private:
    InitManager() {};
    ~InitManager() {};

    static std::vector<myfunc_t> functions;
};

std::vector<InitManager::myfunc_t> InitManager::functions;

class Clock
{
public:
    Clock()
    {

    };
    ~Clock() {};

private:
    void Init() { printf("Clock\n"); };
};

class Dma
{
public:
    Dma() {};
    ~Dma() {};

private:
    void Init() { printf("DMA\n"); };
};

class Spi
{
public:
    Spi() {};
    ~Spi() {};

private:
    void Init() { printf("Spi\n"); };
};


class A {
    int a;
};

class B {
    int b;
};

class C : public A, public B {
    int c;
};

class base {
public:
    virtual ~base() {};
};

class ch1 : public base {

};
class ch2 : public base {

};
void testInherit() {
    cout << "\n >>> testInherit <<<";

    C* pc = new C();
    B* pb = (B*)pc;
    A* pa = (A*)pc;

    base* pch1 = new ch1();
    base* pch2 = new ch2();

    cout << "\npa: " << pa;
    cout << "\npb: " << pb;
    cout << "\npc: " << pc;

    cout << "\n pa == pc --> " << (pa == pc);
    cout << "\n pb == pc --> " << (pb == pc);

    cout << "\n dynamic pch1 --> ch1: " << dynamic_cast<ch1*>(pch1);
    cout << "\n dynamic pch1 --> ch2: " << dynamic_cast<ch2*>(pch1);
    cout << "\n dynamic pch2 --> ch1: " << dynamic_cast<ch1*>(pch2);
    cout << "\n dynamic pch2 --> ch2: " << dynamic_cast<ch2*>(pch2);

    cout << "\n static pch1 --> ch1: " << static_cast<ch1*>(pch1);
    cout << "\n static pch1 --> ch2: " << static_cast<ch2*>(pch1);
    cout << "\n static pch2 --> ch1: " << static_cast<ch1*>(pch2);
    cout << "\n static pch2 --> ch2: " << static_cast<ch2*>(pch2);

    cout << "\n typeinfo(pch1) == typeinfo(ch1): " << (typeid(pch1) == typeid(ch1));
    cout << "\n typeinfo(pch1) == typeinfo(pch2): " << (typeid(pch1) == typeid(pch2));
};

void makeShuffledArrayOfDoubles(vector<int>& arr) {
    
    size_t size = arr.size();

    for (size_t pos = 0; pos < size; ++pos) {
        arr.push_back(arr[pos] * 2);
    }

    random_shuffle(arr.begin(), arr.end());
}

bool checkShuffledArray(const vector<int>& arrIn, vector<int>& arrOut) {

    multiset<int> sarr{ arrIn.begin(), arrIn.end() };
    auto pos = sarr.begin();

    while (pos != sarr.end()) {
        multiset<int>::iterator it = *pos > 0 ? sarr.find(*pos * 2) : sarr.find(*pos / 2);
        if (it != sarr.end()) {
            arrOut.push_back(*pos > 0 ? *pos : *it);
            int v1 = *pos;
            int v2 = *it;
            sarr.erase(v1);
            sarr.erase(v2);
            pos = sarr.begin();

            continue;
        }
        ++pos;
    }

    return sarr.empty();
}

void testShuffledArray() {
    vector<int> arr = { 1, 3, 5, -3, -2 };

    printVector<int>(arr);
    makeShuffledArrayOfDoubles(arr);
    cout << " --> ";
    printVector<int>(arr);

    vector<int> oarr;
    cout << "\nCheck shuffled: " << checkShuffledArray(arr, oarr);
    cout << " --> ";
    printVector(oarr);
}


int nums = 0;
void maxSubsetSumImpl(int& ts, int tts, const vector<int>& arr, size_t pos) {

    if (pos >= arr.size())
        return;

    int nums = 0;
    ++nums;

    // cout << string(nums * 2, ' ') 
    //     << "arr[pos]: " << arr[pos] 
    //     << ", pos: " << pos  
    //     << ", ts: " << ts ;

    if (arr[pos] + tts > ts)
        ts = arr[pos] + tts;
    tts += arr[pos];

    //cout << ", tts: " << tts
    //    << endl;

    for (pos += 2; pos < arr.size(); ++pos)
        maxSubsetSumImpl(ts, tts, arr, pos);
    --nums;
}

// Complete the maxSubsetSum function below.
int maxSubsetSum(vector<int> arr) {

    int ts = 0;

    cout << "1" << endl;
    if (arr.size() > 0)
        maxSubsetSumImpl(ts, 0, arr, 0);

    cout << "2" << endl;
    if (arr.size() > 1)
        maxSubsetSumImpl(ts, 0, arr, 1);

    return ts;
}
int FindMaxSum(vector<int> arr)
{
    if (arr.empty())
        return 0;

    if (arr.size() == 1)
        return arr[0];

    int incl = arr[0];
    int excl = 0;
    int excl_new;

    for (int i = 1; i < arr.size(); i++)
    {
        cout << "i: " << i << ", incl: " << incl << ", excl: " << excl << endl;
        excl_new = (incl > excl) ? incl : excl;
        cout << "i: " << i << ", incl: " << incl << ", excl_new: " << excl_new << endl;

        incl = excl + arr[i];
        excl = excl_new;
    }

    cout << "incl: " << incl << ", excl: " << excl << endl;
    return ((incl > excl) ? incl : excl);
}

void testMaxSubSum()
{   
    string s;

    //ifstream file("d:\\a\\test.txt");

    //std::getline(file, s);
    vector<string> svec = SplitString(s);
    vector<int> vec;
    for (auto& v : svec)
        vec.push_back(stoi(v));

    cout << "maxSubsetSum: " << FindMaxSum({7, -2, -3, 4, 5, -1}) << endl;

}

class Base
{
    virtual void func() = 0;
};

class Child : public Base
{
    void func()
    {
        cout << "Child";
    }

    virtual ~Child()
    {
        cout << "Child dtor";
    }
};


void moveZeros(vector<int>& vec) {
    
    auto rit1 = vec.rbegin();
    auto rit2 = rit1;

    while (rit1 != vec.rend()) {

        if (rit1 > rit2 && *rit1 != 0 && *rit2 == 0) {
            std::swap(*rit1, *rit2);
            ++rit2;
        }

        else if (*rit2 !=0)
            ++rit2;

        ++rit1;
    }
}

void testMoveZeros() {

    cout << "*** " << __func__ << " ***" << std::endl;

    vector<vector<int>> vvec{
        {},
        {0},
        {1,2},
        {1,0},
        {0,1},
        {0,1,2},
        {1,0,2},
        {1,2,0},
        {0,1,0,0,2,3,0},
        {1,2,0,3,4},
        {0,0,0,0,1}
    };


    for (auto& vcase : vvec)
    {
        printVector(vcase);
        cout << " --> ";
        moveZeros(vcase);
        printVector(vcase);
        cout << "\n";
    }
}

int main12(int argc, char** argv)
{
    cout << "*** main-12 ***\n";
    //testThreads();
    //testReverseSL();
    //testParse();
    //testSumSL();
    //testInherit();
    //testShuffledArray();
    //testMaxSubSum();
    testMoveZeros();
    return 0;

}