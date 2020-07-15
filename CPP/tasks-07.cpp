#include "stdafx.h"
#pragma hdrstop


class MemPool {

public:
	MemPool(size_t blockSize, size_t blockNum) :
		_blockSize(blockSize),
		_blockNum(blockNum)
	{
		_pdataBeg = new uint8_t[_blockSize * _blockNum];
		_pdataCur = _pdataBeg;
	}


	size_t getTotalBlocks() const {
		return _blockNum;
	}

	size_t getAllocatedBlocks() const {
		return (_pdataCur - _pdataBeg) / _blockSize - _freeBlocks.size();
	}

	size_t getFreeBlocks() const {
		return getTotalBlocks() - getAllocatedBlocks();
	}

	uint8_t* allocateBlock() {
		uint8_t* newBlock = nullptr;

		if (getFreeBlocks() == 0)
			return newBlock;

		if (_freeBlocks.empty()) {
			newBlock = _pdataCur;
			_pdataCur += _blockSize;
		}
		else
		{
			newBlock = *_freeBlocks.begin();
			_freeBlocks.erase(newBlock);
		}
		return newBlock;
	}

	bool freeBlock(uint8_t* block) {

		if (getAllocatedBlocks() == 0 || 
			block < _pdataBeg || 
			block > _pdataBeg + (_blockNum - 1) * _blockSize ||
			(block - _pdataBeg) % _blockSize != 0)
			return false;
		
		if (_pdataCur - block == 1) {
			_pdataCur -= _blockSize;
			_freeBlocks.erase(_pdataCur);
		}
		else
			_freeBlocks.insert(block);

		return true;
	}

	void PrintStat() const {
		uint8_t* tdata = _pdataBeg;

		while (tdata < _pdataCur) {
			if (_freeBlocks.empty() || _freeBlocks.find(tdata) == _freeBlocks.end())
				cout << "\n   " << hex << (size_t)tdata << dec;
			tdata += _blockSize;
		}
	}

	~MemPool() {
		delete[] _pdataBeg;
	}

private:

	uint8_t* _pdataBeg;
	uint8_t* _pdataCur;

	size_t _blockSize;
	size_t _blockNum;
	unordered_set<uint8_t*> _freeBlocks;
};


void printPoolStat(const MemPool& mp) {
	cout << "\nAllocated blocks: " << mp.getAllocatedBlocks();
	cout << "\nFree blocks     : " << mp.getFreeBlocks();
	cout << "\nList of blocks  : ";
	mp.PrintStat();
}

void testMemPool() {

	MemPool mp(0x40, 5);
	cout << "\nTotal blocks: " << mp.getTotalBlocks() << "\n";
	printPoolStat(mp);

	uint8_t* b1 = mp.allocateBlock();
	printPoolStat(mp);
	uint8_t* b2 = mp.allocateBlock();
	printPoolStat(mp);
	uint8_t* b3 = mp.allocateBlock();
	printPoolStat(mp);

	mp.freeBlock(b1);
	printPoolStat(mp);
	mp.freeBlock(b3);
	printPoolStat(mp);

	uint8_t* b11 = mp.allocateBlock();
	printPoolStat(mp);
	uint8_t* b33 = mp.allocateBlock();
	printPoolStat(mp);
}



// INCLUDE HEADER FILES NEEDED BY YOUR PROGRAM
// SOME LIBRARY FUNCTIONALITY MAY BE RESTRICTED
// DEFINE ANY FUNCTION NEEDED
// FUNCTION SIGNATURE BEGINS, THIS FUNCTION IS REQUIRED


void pure_task1()
{

}

void pure_task2()
{

}
#include <vector>
#include <string>
#include <regex>
#include <unordered_map>

using namespace std; // this is only for simplification for this time

// INCLUDE HEADER FILES NEEDED BY YOUR PROGRAM
// SOME LIBRARY FUNCTIONALITY MAY BE RESTRICTED
// DEFINE ANY FUNCTION NEEDED
// FUNCTION SIGNATURE BEGINS, THIS FUNCTION IS REQUIRED

typedef vector<string> strings_t;

struct node_t{
	int val;
	node_t* l;
	node_t* r;
	node_t* next;
};

void print_nodes(node_t* node)
{

	while (node)
	{
		cout << node->val << ", " ;
		node = node->next;
	}
}

node_t* delete_node(node_t* node, int val)
{
	node_t* nnode = 0;
	node_t* prev = 0;

	while (node != 0)
	{
		node_t* next_node = node->next;
		node->next = 0;

		if (node->val == val)
		{
			delete node;
		}
		else
		{
			if (nnode == 0)
				nnode = node;

			if (prev != 0)
				prev->next = node;

			prev = node;
		}

		node = next_node;
	}

	return nnode;
}

void testNodesDelete()
{
	node_t* n6 = new node_t{ 2, 0 };
	node_t* n5 = new node_t{ 1, n6 };
	node_t* n4 = new node_t{ 2, n5 };
	node_t* n3 = new node_t{ 4, n4 };
	node_t* n2 = new node_t{ 3, n3 };
	node_t* n1 = new node_t{ 2, n2 };

	cout << "\nNodes before: ";
	print_nodes(n1);


	cout << "\nDeleted 1: ";
	print_nodes(delete_node(n1, 2));

}

void printTree(node_t* node) {
	if (node == nullptr)
		return;

	printTree(node->l);
	cout << node->val << ", ";
	printTree(node -> r);
}

bool isBstTreeImpl(node_t* cnode, node_t*& pnode) {

	if (cnode == nullptr)
		return true;

	cout << "\npnode: " << (pnode ? pnode->val : 0);
	cout << " cnode: " << cnode->val;

	if (!isBstTreeImpl(cnode->l, pnode))
		return false;

	if (pnode != nullptr && cnode->val <= pnode->val)
		return false;

	pnode = cnode;

	return isBstTreeImpl(cnode->r, pnode);

}

bool isBstTree(node_t* node) {
	node_t* pnode = nullptr;
	return isBstTreeImpl(node, pnode);
}

void testTreeNodes() {

	node_t l21 = node_t{ 3, 0, 0, 0 };
	node_t l22 = node_t{ 7, 0, 0, 0 };
	node_t l23 = node_t{ 12, 0, 0, 0 };
	node_t l24 = node_t{ 17, 0, 0, 0 };
	node_t l11 = node_t{ 5, &l21, &l22, 0 };
	node_t l12 = node_t{ 15, &l23, &l24, 0 };
	node_t l0 = node_t{ 10, &l11, &l12, 0 };

	cout << "\nPrint tree: ";
	printTree(&l0);

	cout << "\nCheck bst: " << (isBstTree(&l0));

}

typedef function<void()> thread_method_t;

struct Runnable1 {
	void Run(const char* params) {
		for (int i = 0; i < 5; ++i) {
			cout << "\n    Runnable 1: " << (params == nullptr ? "null" : (const char*)params);
			this_thread::sleep_for(1s);
		}
	}
};

struct Runnable2 {
	void Run(const char* params) {
		for (int i = 0; i < 5; ++i) {
			cout << "\n    Runnable 2: " << (params == nullptr ? "null" : (const char*)params);
			this_thread::sleep_for(1s);
		}
	}
};

class ThreadPool {
	vector<thread> _th;
	condition_variable _cv;
	mutex _mtx;
	queue<thread_method_t> _tasks;
	bool _is_run = true;

protected:
	void worker(int i) {
		cout << "\nThread " << i << " started";
		while (_is_run) {
			unique_lock<mutex> l(_mtx);
			_cv.wait(l, [this] {return !_is_run || !_tasks.empty(); });

			while (!_tasks.empty()) {
				auto task = _tasks.front();
				_tasks.pop();
				l.unlock();
				if (task) {
					cout << "\n  Processed in thread: " << i ;
					task();
				}

				l.lock();
			}
		}
		cout << "\nThread " << i << " stopped";
	}

public:
	ThreadPool(size_t num_threads) {
		for (size_t i = 0; i < num_threads; ++i)
			_th.emplace_back(thread([this, i] { worker(i + 1);  }));
	}

	~ThreadPool() {
		_is_run = false;
		_cv.notify_all();
		for (auto& th : _th)
			th.join();
	}

	void addTask(thread_method_t tm) {
		unique_lock<mutex> l(_mtx);
		_tasks.push(thread_method_t(tm));
		_cv.notify_one();
	}

};

void testThreadPool() {
	ThreadPool tp(3);
	Runnable1 rn1;
	Runnable2 rn2;
	Runnable1 rn3;
	Runnable2 rn4;
	Runnable1 rn5;
	Runnable2 rn6;


	this_thread::sleep_for(3s);
	tp.addTask(bind(&Runnable1::Run, &rn1, "par 111"));
	this_thread::sleep_for(2s);
	tp.addTask(bind(&Runnable2::Run, &rn2, "par 222"));
	tp.addTask(bind(&Runnable1::Run, &rn3, "par 333"));
	tp.addTask(bind(&Runnable2::Run, &rn4, "par 444"));
	tp.addTask(bind(&Runnable1::Run, &rn5, "par 555"));
	tp.addTask(bind(&Runnable2::Run, &rn6, "par 666"));
	this_thread::sleep_for(3s);

}

class arg_t {

public:
	typedef vector<string> vals_t;

	const vals_t& get_vals() const { return _vals; }

	
private:

	vals_t _vals;
};

class command_t {

public:
	typedef vector<string> vals_t;
	typedef unordered_map<string, vals_t> args_t;

	vals_t get_vals(const string& key) const {

		args_t::const_iterator it = _args.find(key);

		return it == _args.end() ? vals_t() : it->second;
	}

		
private:

	args_t _args;
};

class command_handler_t {

public:

private:


	string _cmd_type;
	
};

/*
class command_line_proc_t {
public:
	//typedef decltype([](void*) {}) handler_cb_t;
	//typedef unordered_map<string, handler_cb_t> handlers_cb_t;
	bool register_handler(const string& command, handler_cb_t handler_cb) {
		_handlers_cb[command] = handler_cb;
	}

	bool process_string(const string& str) {
		
		while ()
	}

private:

	handlers_cb_t _handlers_cb;
};
*/

// FUNCTION SIGNATURE ENDS

double mysqrt(double val, double acc = 0.01) {
	if (val <= 0)
		return numeric_limits<double>::quiet_NaN();

	double a = 0, b = val < 1 ? 1 : val;
	double pivot = (a + b) / 2.0;

	while (abs(pivot * pivot - val) > acc) {

		if (pivot * pivot > val)
			b = pivot;
		else
			a = pivot;

		pivot = (a + b) / 2.0;
	}

	return pivot;
}

void testMysqrt() {

	vector<pair<double, double>> cases{ 
		{-1, numeric_limits<double>::quiet_NaN()},  
		{0, numeric_limits<double>::quiet_NaN()},
	};

	for (double cv = 0.1; cv < 1; cv += 0.1)
		cases.push_back(pair < double, double>(cv * cv, cv));

	for (double cv = 1; cv < 10; cv += 1)
		cases.push_back(pair < double, double>(cv * cv, cv));

	double acc = 0.001;

	for (const auto& v : cases) {
		double sqv = mysqrt(v.first, acc);
		cout << "\ncase: val: " << v.first << ", expected: " << v.second
			<< ", result: " << sqv << "  --> "
			<< (abs(sqv * sqv - v.first) <= acc || v.second == sqv ? "ok" : "ERROR");
	}
}

#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include <stdio.h>

/* Given a binary bitstream (a H264 bitstream for example) containing
 * several segments (H264 NALU for example) defined by start code
 * (00 00 01 or 00 00 00 01), count the number of segments, their
 * length, and offset.  Print output to stdout.
 */

 //   DLE STX 12 12 12 DLE DLE --> DLE  12 DLE ETX CRC1 CRC2

 // FSM states (max size 256)
 // num_msg = 0;
 // FSM:IDLE , FSM:MSG_SEG
 // ch != 0x00 --> dump
 // ch == 0x00 --> FSM:BEGIN_SEG, ++zero_cnt 
 // if FSM:BEGIN_SEG && ++sero_cnt > 3 --> FSM:IDLE
 // if FSM:BEGIN_SEG && zer_cnt <=0 && ch == 0x01 --> FSM:MSG_SEG
 // if FSM:MSG_SEG, if prev_st == FSM_IDLE: store offset: index - zero_cnt - 1 ;
 // 

enum FSM_STATE {
	FSM_IDLE,
	FSM_ZERO,
	FSM_ONE,
	FSM_MSG
};

void onMessage(size_t offset, size_t length) {
	std::cout << "\n New mesage found: length: " << length << ", offest: " << offset;
}

void printStream(unsigned short int* arr, size_t size) {
	FSM_STATE fstate = FSM_IDLE;
	size_t pos = 0;

	size_t plen = 0;
	size_t poffs = 0;
	int cnt_zero = 0;
	bool is_prev = false;


	while (pos < size) { // uint8_t
		const unsigned short int v = arr[pos];

		if (fstate == FSM_IDLE) {
			if (v == 0x00) {
				fstate = FSM_ZERO;
				++cnt_zero;
			}
		}
		else if (fstate == FSM_ZERO)
		{
			if (v != 0x00 && v != 0x01)
			{
				cnt_zero = 0;
				fstate = FSM_IDLE;
			}
			else if (v == 0x00) {
				++cnt_zero;
			}
			else if (v == 0x01) {
				fstate = FSM_ONE;
			}
		}
		else if (fstate == FSM_ONE) {

			if (cnt_zero >= 2)
				fstate = FSM_MSG;
			else {
				cnt_zero = 0;
				fstate = FSM_IDLE;
			}
		}
		if (fstate == FSM_MSG) {

			size_t offs = cnt_zero > 3 ? pos - 3 - 1: pos - cnt_zero - 1;

			if (is_prev)
				onMessage(poffs, offs - poffs);

			cnt_zero = 0;
			poffs = offs;
			is_prev = true;
			fstate = FSM_IDLE;
		}

		++pos;
	}

	if (pos > poffs)
		onMessage(poffs, pos - poffs);
}

/* dperi@vmware.com */

int testStream()
{
	unsigned short int b[] = { 0x00, 0x00, 0x00, 0x01, 0x67, 0x00, 0x01, 0x02, 0x03,
									 0x00, 0x00, 0x01, 0x65, 0x01, 0x00, 0x01, 0x02,
								  	 0x00, 0x00, 0x01, 0x65, 0x01, 0x00, 0x01, 0x00,
							   0x00, 0x00, 0x00, 0x01, 0x65, 0x01, 0x00, 0x00, 0x02 };
	/*
	 * above bitstream has four segments:
	 *   length: 9, offset: 0,
	 *   length: 8, offset: 9
	 *   length: 8, offset: 17
	 *   length: 9, offset: 25
	 */

	printStream(b, sizeof(b) / sizeof(b[0]));

	return 0;
}


void PrintDFS(GNode* gnode) {
	if (gnode == nullptr || gnode->isVisited)
		return;

	gnode->isVisited = true;

	for (auto& cnode : gnode->gnodes)
		PrintDFS(cnode);

	cout << gnode->val << ", ";
}

void PrintBFS(GNode* gnode) {

	queue<GNode*> cnodes;
	cnodes.push(gnode);

	while (!cnodes.empty()) {
		GNode* cnode = cnodes.front();
		cnodes.pop();

		if (cnode == nullptr || cnode->isVisited)
			continue;

		cnode->isVisited = true;
		cout << cnode->val << ", ";

		for (auto& ccnode : cnode->gnodes)
			if (!ccnode->isVisited)
				cnodes.push(ccnode);
	}
}

void testGraph() {
	//	Create a graph
	GNode g1{ false, 1 };
	GNode g2{ false, 2 };
	GNode g3{ false, 3 };
	GNode g4{ false, 4 };
	GNode g5{ false, 5 };
	GNode g6{ false, 6 };
	GNode g7{ false, 7 };
	GNode g8{ false, 8 };
	GNode g9{ false, 9 };
	GNode g10{ false, 10};

	g1.gnodes = { &g2, &g3 };
	g2.gnodes = { &g1 };
	g3.gnodes = { &g1, &g4, &g5 };
	g4.gnodes = { &g3, &g5, &g6 };
	g5.gnodes = { &g3, &g4, &g7 };
	g6.gnodes = { &g4, &g8 };
	g7.gnodes = { &g4, &g5 };
	g8.gnodes = { &g6, &g9 };
	g9.gnodes = { &g8, &g10 };
	g10.gnodes = { &g9 };

	cout << "\nPrintDFS: ";
	PrintDFS(&g1);

	//cout << "\nPrintBFS: ";
	PrintBFS(&g1);
}

string get_next_token(const string& str, string::const_iterator& it) {

	string stoken;

	while (it != str.cend()) {

		if (*it != ' ')
			stoken += *it;
		++it;

		if (stoken.find_first_of("+-*/()") != string::npos) {
			if (stoken.size() == 1)
				break;
			else {
				stoken.pop_back();
				--it;
				break;
			}
		}
	}

	return stoken;
}

int get_op_rank(char op) {
	switch (op) {
	case '+':
	case '-': return 1;
	case '*':
	case '/': return 2;
	case '^': return 3;
	default: return 0;
	}
}

double calc_opers(double v1, double v2, char op) {
	switch (op) {
	case '+': return v1 + v2;
	case '-': return v1 - v2;
	case '*': return v1 * v2;
	case '/': return v1 / v2;
	default: throw std::exception("invalid operation");
	}
}

double calc_impl(const string& str, string::const_iterator& it) {
	
	bool is_last = true;
	bool is_run = true;

	stack<double> nums;
	stack<char> ops;

	while (is_run && (it != str.end() || is_last)) {
		string stoken = get_next_token(str, it);

		if (stoken.empty() && is_last) {
			stoken = "+";
			is_last = false;
		}

		if (stoken.find_first_of("+-/*()") != string::npos) {
			if (stoken[0] == '(') {
				nums.push(calc_impl(str, it));
				continue;
			}
			else if (stoken[0] == ')') {
				stoken = '+';
				is_run = false;
			}

			while (!ops.empty() && get_op_rank(stoken[0]) <= get_op_rank(ops.top())) {
				double opers[2];
				for (int i = 0; i < 2; ++i) {
					if (nums.empty())
						throw std::exception("operands not found");

					opers[i] = nums.top();
					nums.pop();
				}
				nums.push(calc_opers(opers[1], opers[0], ops.top()));
				ops.pop();
			}
			ops.push(stoken[0]);
		}
		else {
			nums.push(stod(stoken));
		}
	}

	return nums.empty() ? numeric_limits<double>::quiet_NaN() : nums.top();
}

double calc(const string& str) {
	string::const_iterator it = str.cbegin();
	return calc_impl(str, it);
}

void testCalc() {

	vector<pair<string, string>> cases{ 
		{"  (  6  )   ", "6"},
		{"2*(4-1)+(5*(3+2))", "31"},
		{"1+5+2*3*4",  "30"},  
		{"1+5+2*3*4+3",  "33"},
		{"1+5+2*3*4-3",  "27"},
		{"1+5+2*3*4-3+5",  "32"},
		{"4+4-5*5-5+2+4-1*4/5-5+52-45-14/41+45-4*52+41+1-45 *52-4*1-214+45-45", "-2694.14"},
		{"5/7+5+6-4/4*565*45  /65-4*4/4*5 -54-45-45+2-45/4-5*4+12-4-45-45+2+45-45", "-652.69"}
	};
	for (const auto& v : cases)
		cout << "\n exp: " << v.first << " = " << calc(v.first) << " --> " << v.second;

}

int findBinBegin(const vector<int>& vals) {
	if (vals.empty())
		return -1;

	int a = 0;
	int b = vals.size() - 1;

	while (a < b) {
		if (vals[a] < vals[b])
			break;

		int p = a + ((b - a) / 2);

		if (p == a) 
			a = b;
		else
		{
			if (vals[a] > vals[p])
				b = p;
			else
				a = p;
		}
	}

	return a;
}

int getBinEl(const vector<int>& vals, int idx, int offs) {
	return offs > 0 ? vals[(idx + offs) % vals.size()] : vals[idx];
}

int binSearch(const vector<int>& vals, int val) {

	if (vals.empty())
		return -1;

	const int ofs = findBinBegin(vals);

	if (ofs == -1)
		return -1;

	int a = 0;
	int b = vals.size() - 1;

	while (a < b) {
		int p = a + (b - a) / 2;

		if (val == getBinEl(vals, p, ofs)) {
			a = p;
			break;
		}
			
		if (a == p) {
			a = b;
			break;
		}

		if (val > getBinEl(vals, p, ofs))
			a = p;
		else
			b = p;
	}

	return getBinEl(vals, a, ofs) == val ? (a + ofs) % vals.size() : -1;
}

void testBinSearch() {
	vector<vector<int>> tcases{ 
		{}, {1}, {1,2}, {2,1},
		{1,2,3,4}, {4,1,2,3}, {3,4,1,2}, {2,3,4,1},
		{1,2,3}, {3, 1,2}, {2, 3, 1},
		{1,2,3,4,5,6,7,10}, {7,1,2,3,4,5,6}, {6,7,1,2,3,4,5}, {5,6,7,1,2,3,4},
		{4,5,6,7,1,2,3}, {3,4,5,6,7,1,2}, {2,3,4,5,6,7,1} };

	//cout << "\n   search dedicated: " << 1 << ", found: [" << binSearch(tcases[2], 1) << "] ";
	//return;

	for (const auto& v : tcases) {
		cout << "\ncase: vals: ";
		for (const auto& v2 : v)
			cout << v2 << " ";

		//int ofs = findBinBegin(v);
		//cout << "\n begins: [" << ofs << "] = " << (ofs == -1 ? -1 : v[ofs]);
		//for (int i = 0; i < v.size(); ++i)
		//	cout << "\n    a[" << i << "] = " << getBinEl(v, i, ofs);

		for (const auto& v2 : v) {
			
			int res = binSearch(v, v2);
			cout << "\n   search: " << v2 << ", found: [" <<  res << "] " << (res == -1 ? "\t\tERROR" : "\t\tok");
		}

		cout << "\n   search nonexisting: " << 0 << ", found: [" << binSearch(v, 0) << "] ";
		cout << "\n   search nonexisting: " << 999 << ", found: [" << binSearch(v, 99) << "] ";

	}
}

struct data_t {
	string name;
	float age;
	int score;

	data_t() = default;

	data_t(istream& is) {
		is >> name;
		is >> age;
		is >> score;
	}

	void writeToStream(ostream& os) const {
		os << name;
		os << " " << age;
		os << " " << score << endl;
	}

	void print() const {
		cout << "\n name: " << name << ", age: " << age << ", score: " << score;
	}

	bool operator < (const data_t& dv) { return age < dv.age&& score < dv.score;  };

};

void testData() {
	vector<data_t> data;
	ifstream ss("data.txt");
	ofstream os("data-s.txt", ios_base::trunc);

	while (!ss.eof())
		data.emplace_back(ss);

	cout << "\nLoaded data:";
	for (const auto& v : data)
		v.print();

	cout << "\nSorted data:";
	sort(data.begin(), data.end());
	for (const auto& v : data) {
		v.print();
		v.writeToStream(os);
	}
}

struct myclass_t {
	void run(string s) {
		cout << "\n run: start - " << s;
		this_thread::sleep_for(4s);
		cout << "\n run: end - " << s;
	}
};

void threadFunc(string s) {
	cout << "\n threadFunc: start - " << s;
	this_thread::sleep_for(3s);
	cout << "\n threadFunc: end - " << s;
}
void testThreads() {

	thread tf1{ threadFunc, "tf1" };
	this_thread::sleep_for(100ms);
	thread tf2{ threadFunc, "tf2" };

	myclass_t mc1;
	myclass_t mc2;
	this_thread::sleep_for(100ms);
	thread tc1{ &myclass_t::run, mc1, "tc1" };
	this_thread::sleep_for(100ms);
	thread tc2{ &myclass_t::run, mc2, "tc2" };

	auto lf = [](auto s)  {
		cout << "\n lf: start - " << s;
		this_thread::sleep_for(3s);
		cout << "\n lf: end - " << s;
	} ;

	this_thread::sleep_for(100ms);
	thread lf1{ lf, "lf1" };
	this_thread::sleep_for(100ms);
	thread lf2{ lf, "lf2" };

	tf1.join();
	tf2.join();
	tc1.join();
	tc2.join();
	lf1.join();
	lf2.join();

}

#include <stdlib.h>

double** allocMatrix(size_t r, size_t c) {
	if (r <= 0 || c <= 0)
		return 0;

	double** rows = (double**)malloc(r * sizeof(double*));
	if (rows == 0)
		return 0;

	*rows = (double*)malloc(r * c * sizeof(double));
	if (*rows == 0) {
		free(rows);
		return 0;
	}

	for (size_t i = 1; i < r; ++i)
		rows[i] = &((*rows)[c * i]);

	return rows;
}

void freeMatrix(double** matrix) {
	if (matrix == 0 || *matrix == 0)
		return;

	free(*matrix);
	free(matrix);
}

void testMatrix() {

	const size_t rr = 5, cc = 5;
	double** m = allocMatrix(rr, cc);

	for (int r = 0; r < rr; ++r)
		for (int c = 0; c < cc; ++c)
			m[r][c] = r == c ? 1  : 0;


	cout << setw(3);
	for (int r = 0; r < rr; ++r) {
		cout << "\n";
		for (int c = 0; c < cc; ++c)
			cout << m[r][c] << "  ";
	}

	freeMatrix(m);
}


int main7(int argc, char** argv)
{
	cout << "\n *** main-7 ***";
	
	//testMemPool();
	//testNodesDelete();
	//testTreeNodes();
	//testThreadPool();
	//testMysqrt();
	//testStream();
	//testGraph();
	//testCalc();
	//testBinSearch();
	//testData();
	//testThreads();

	//testMatrix();
	return 0;
}
