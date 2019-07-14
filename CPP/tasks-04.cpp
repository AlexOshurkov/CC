#include "stdafx.h"
#pragma hdrstop

using namespace std;

void printPermutationImpl(stringstream& res, const string& pref, const string& str)
{
    if (str.size() > 1)
        for (size_t i = 0; i < str.size(); ++i)
            printPermutationImpl(res, pref + str.substr(i, 1), str.substr(0, i) + str.substr(i + 1));
    else
          res << pref << str << ", ";
}

string printPermutations(const string& str)
{
    stringstream ss;
    printPermutationImpl(ss, "", str);
    return ss.str();
}

void testPerm() {
    vector<string> perm{"", "1", "12", "123", "1234", "abc", "cba", "aaa"};
    for (const auto& v : perm)
        cout << "\n" << v << ": " << printPermutations(v);
}

typedef pair<size_t, size_t> minel_t;

bool testAndSetMinel(size_t val, minel_t& mv) {

    if (mv.first == 0 || val < mv.first) {
        mv.first = val;
        return true;
    }
    else if (val > mv.first && (mv.second == 0 || val < mv.second))
    {
        mv.second = val;
        return true;
    }

    return false;
}

struct Node {
    size_t v = 0;
    Node* l = nullptr;
    Node* r = nullptr;
};

size_t c = 0;

void getTwoMinElImpl(Node* node, minel_t& mv) {
    if (node == nullptr)
        return;

    ++c;

    testAndSetMinel(node->v, mv);

    if (node->l && testAndSetMinel(node->l->v, mv))
        getTwoMinElImpl(node->l, mv);

    if (node->r && testAndSetMinel(node->r->v, mv))
        getTwoMinElImpl(node->r, mv);
}

minel_t getTwoMinEl(Node* node) {
    minel_t mv{ 0, 0 };
    getTwoMinElImpl(node, mv);
    return mv;
}

void testTwoMinEl() {
    Node l3_1{ 1, 0, 0 };
    Node l3_2{ 2, 0, 0 };
    Node l3_3{ 3, 0, 0 };
    Node l3_4{ 4, 0, 0 };
    Node l3_5{ 5, 0, 0 };
    Node l3_6{ 6, 0, 0 };
    Node l3_7{ 7, 0, 0 };
    Node l3_8{ 8, 0, 0 };

    Node l2_1{ 1, &l3_1, &l3_2 };
    Node l2_2{ 3, &l3_3, &l3_4 };
    Node l2_3{ 5, &l3_5, &l3_6 };
    Node l2_4{ 7, &l3_7, &l3_8 };

    Node l1_1{ 1, &l2_1, &l2_2 };
    Node l1_2{ 5, &l2_3, &l2_4 };

    Node l0{
        1, &l1_1, &l1_2
    };
    
    minel_t mv = getTwoMinEl(&l0);
    size_t cc = c;
}



uint32_t getBitsNum(uint32_t v) {
    uint32_t nb = 0;
    while (v > 0) {
        ++nb;
        v &= v - 1;
    }

    return nb;
}

uint32_t getBitsSumFrom0(uint32_t v) {
    uint32_t sb = 0;
    for (; v > 0; --v)
        sb += getBitsNum(v);
    return sb;
}

uint32_t getQuickBitsSumFrom0(uint32_t v) {
    uint32_t rn = v + 1;  // row number, effectively v + 1
    uint32_t sb = 0;      // summ of bits
    uint32_t mc = 2;      // max combinations

    while (v > 0) {
        sb += rn / mc * (mc >> 1);
        if ((rn % mc) > (mc >> 1))
            sb += (mc >> 1) + (rn % mc) - mc;

        v >>= 1;
        mc <<= 1;
    }

    return sb;
}

void testBitsSum() {
    vector <uint32_t> cases;
    for (int i = 0; i < 1024; ++i)
        cases.push_back(i);

    bool r = true;
    for (const auto& v : cases) {
        uint32_t sb1 = getBitsSumFrom0(v);
        uint32_t sb2 = getQuickBitsSumFrom0(v);
        if (r && sb1 != sb2)
            r = false;

        cout << "\n" << v << ": " << sb1 << (sb1 == sb2 ? " == " : " != " ) << sb2 << (sb1 == sb2 ? "" : " X");
    }
    cout << "\n\n  Result: " << (r ? "Passed" : "FAILED");
}

typedef vector<int> vint_t;

void moveZero(vint_t& arr) {

    if (arr.size() < 2)
        return;

    vint_t::iterator it1 = arr.begin();
    vint_t::iterator it2 = arr.begin();

    while (it1 != arr.end()) {
        if (*it1 == 0) {
            if (*it2 != 0)
                it2 = it1;
        }
        else
        {
            if (it1 != it2)
                swap(*it1, *it2);
            ++it2;
        }

        ++it1;
    }
}

void testMoveZero() {
    vector<vint_t> cases{ 
        {1, 2, 3},
        {0, 1},
        {1, 0},
        {0,1,0},
    {0,1,0,2,0},
    {0, 1, 0, 0, 2, 3},
    {0, 1, 2, 3},
    {0, 1, 0, 0, 2, 3, 0},
    };

        for (auto& v : cases) {
            moveZero(v);
            cout << "\n case: ";

            for (const auto& vv : v)
                cout << vv << " ";
        }
}

void testCast() {

    int16_t  iv1 = -1;
    uint16_t uv1 = 65535;
    int16_t  iv2 = *reinterpret_cast<int16_t*>(&uv1);
    uint16_t uv2 = *reinterpret_cast<uint16_t*>(&iv1);
    int16_t  iv3 = (int16_t)(uv1);
    uint16_t uv3 = (uint16_t)(iv1);
    int16_t  iv4 = static_cast<int16_t>(uv1);
    uint16_t uv4 = static_cast<uint16_t>(iv1);

}

constexpr uint64_t calcFibo(size_t num) {
    uint64_t a = 0, b = 1;
    
    while (num > 0) {
        uint64_t ta = a;
        a = b;
        b = ta + b;
        --num;
    }
    return b;
}

struct cell_t {
    bool is_wall = false;
    bool is_visited = false;
    bool is_route = false;
};

const size_t R = 10;
const size_t C = 20;
cell_t board[R][C];

typedef pair<int, int> pos_t;
typedef stack<pos_t> steps_t;

bool checkBounds(pos_t pos) {
    return pos.first >= 0 && pos.first < R && pos.second >= 0 && pos.second < C;
}

pos_t findRouteImpl(pos_t start, pos_t end, pos_t cpos, steps_t& steps) {
    
    const size_t r = cpos.first;
    const size_t c = cpos.second;

    if (!checkBounds(cpos))
        return cpos;
    
    board[r][c].is_visited = true;

    if (cpos == end) {
        steps.push(cpos);
        return end;
    }

    vector<pair<int, int>> offs{ {1,0}, {0, 1 }, {-1,0}, {0, -1}  };

    for (const auto& off : offs) {
        const int off_r = off.first;
        const int off_c = off.second;
        if ((board[r + off_r][c + off_c].is_visited) ||
            board[r + off_r][c + off_c].is_wall)
            continue;
        pos_t npos(r + off_r, c + off_c);
        if (findRouteImpl(start, end, npos, steps) == end) {
            steps.push(cpos);
            return end;
        }
    }
    return cpos;
}

pos_t tryOffToStepOff(pos_t pos) {
    if (pos.first == 0 && pos.second == -1)
        return pos_t(1, 0);

    else if (pos.first == 1 && pos.second == 0)
        return pos_t(0, 1);

    else if (pos.first == 0 && pos.second == 1)
        return pos_t(-1, 0);

    else if (pos.first == -1 && pos.second == 0)
        return pos_t(0, -1);

    else 
        throw std::out_of_range("Unknown try offset");
}

pos_t findRouteImpl2(pos_t start, pos_t end, pos_t cpos, pos_t try_off, steps_t& steps) {
    return pos_t();
}

steps_t findRoute(pos_t start, pos_t end)
{
    steps_t steps;
    if (findRouteImpl2(start, end, pos_t(0, 0), pos_t(1, 0), steps) == end)
        return steps;
    else
        return steps_t();
}

void printBoard() {
    cout << string(C + 2, '-');
    for (size_t r = 0; r < R; ++r) {
        cout << "\n|";
        for (size_t c = 0; c < C; ++c)
            if (board[r][c].is_wall)
                cout << "#";
            else if (board[r][c].is_route)
                cout << "*";
            else if (board[r][c].is_visited)
                cout << "V";
            else
                cout << " ";
        cout << "|";
    }
    cout << "\n" << string(C + 2, '-');
}



void testRoute() {
    board[6][0].is_wall = true;
    board[6][1].is_wall = true;
    board[6][2].is_wall = true;
    board[6][3].is_wall = true;
    board[6][4].is_wall = true;
    board[6][5].is_wall = true;
    board[5][5].is_wall = true;
    board[4][5].is_wall = true;
    board[3][5].is_wall = true;
    board[2][5].is_wall = true;
    board[2][4].is_wall = true;
    board[2][3].is_wall = true;
    board[R - 2][C - 3].is_wall = true;
    board[R - 1][C - 3].is_wall = true;
    steps_t steps = findRoute(pos_t(0, 0), pos_t(R - 1, C - 1));

    while (!steps.empty()) {
        pos_t pos = steps.top();
        board[pos.first][pos.second].is_route = true;
        steps.pop();
    }

    printBoard();

    if (steps.empty())
        cout << "\nNo route found";
}

int main4(int, char**)
{
    //testBitsSum();
    //testPerm();
    //testMoveZero();
    //testRoute();


    return 0;
}
