#include "precomp.hpp"
#pragma hdrstop

#include <Windows.h>

using namespace std;

int CountBits(size_t val)
{
    int count = 0;
    while (val > 0)
    {
        val &= val - 1;
        ++count;
    }

    return count;
}

size_t SortBits(size_t val)
{
    return (1 << CountBits(val)) - 1;
}

void TestCountBits()
{
    int i1 = SortBits(0);
    int i2 = SortBits(1);
    int i3 = SortBits(0b11111111);
    int i4 = SortBits(0b010101);
    int i5 = SortBits(0b101010);
    int i6 = SortBits(0b10000000);

}

void TestDoubleFileValues()
{
    vector<double> vals{ istream_iterator<double>{ifstream(R"(c:\file.dat)")}, 
        istream_iterator<double>{} };

    ofstream outf(R"(c:\file2.dat)");

    for (const auto& v : vals)
        outf << v * 2 << " ";
}

size_t BinSearch(const vector<int> vals, int val)
{
    const size_t size = vals.size();

    if (vals.empty() || val < vals[0] || val > vals[size - 1])
        return size;

    size_t beg = 0;
    size_t end = size - 1;

    while (beg <= end)
    {
        size_t curr = (beg + end) / 2;

        if (end - beg > 1)
        {
            if (vals[curr] == val)
                return curr;

            else if (val > vals[curr])
                beg = curr;

            else if (val < vals[curr])
                end = curr;
        }
        else
        {
            if (val == vals[beg])
                return beg;

            else if (val == vals[end])
                return end;

            break;
        }
    }

    return size;
}

void TestBinSearch()
{
    vector<int> vals{ 1 };// , 3, 5, 7, 9, 11, 15 };

    //vals.clear();
    //for (size_t i = 1; i < 1000; i += 2)
     //   vals.push_back(i);

    size_t s1 = BinSearch(vals, 0);
    size_t s3 = BinSearch(vals, 11);
    size_t s4 = BinSearch(vals, 1);
    size_t s5 = BinSearch(vals, 2);
    size_t s6 = BinSearch(vals, 10);

    size_t t1 = BinSearch(vals, 1);
    size_t t2 = BinSearch(vals, 3);
    size_t t3 = BinSearch(vals, 5);
    size_t t4 = BinSearch(vals, 7);
    size_t t5 = BinSearch(vals, 9);
    size_t t6 = BinSearch(vals, 11);
    size_t t7 = BinSearch(vals, 15);

    size_t i1 = BinSearch(vals, 1000);
    size_t i2 = BinSearch(vals, 999);
    size_t i3 = BinSearch(vals, 998);
    size_t i4 = BinSearch(vals, 777);
    size_t i5 = BinSearch(vals, 2);
    size_t i6 = BinSearch(vals, 3);

}

struct Shared
{
    shared_mutex smtx;
    int val;

    int read()
    {
        shared_lock<shared_mutex> l(smtx);
        return val;
    }

    void write(int v)
    {
        unique_lock<shared_mutex> l(smtx);
        val = v;

    }

};


int main(int argc, char**)
{
    Shared sh1;

    sh1.write(11);
    int t = sh1.read();

    return 0;
}
