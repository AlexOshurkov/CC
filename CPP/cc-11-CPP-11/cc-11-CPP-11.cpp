// cc-11-CPP-11.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

struct str1_t
{
	int mul(int a, int b) 
	{ 
		return f(a, b);
	}
	function<int(int, int)> f;
};

//	Non-static member's initializer
class class1_t
{
	int a = 9;
public:

	class1_t() = default;
	virtual int mul(int aa, int b) { return a * b;  }
	virtual int sqr(int a) { return a / 2; }

	explicit class1_t(int) 
	{
		cout << "int" << endl;
	}


	explicit  class1_t(bool)
	{
		cout << "bool" << endl;
	}
};

enum class type_t : unsigned short 
{
	param1,
	param2

};

	template<class... Types>
	tuple<Types...> make_tuplet(Types&&... t)	// this definition is somewhat simplified (see standard 20.5.2.2)
	{
		return tuple<Types...>(t...);
	}

	int pmul(int a, int b) { return a * b; }

template <typename T>
void qsort(vector<T>& v, long b = 0, long e = 0)
{
	if (b == 0 && e == 0 && !v.empty())
		qsort(v, 0, v.size() - 1);

	long i = b;
	long j = e;
	T mv = v[(b + e) / 2];

	while (i < j)
	{

		while (v[i] < mv) i++;
		while (v[j] > mv) j--;

		if (i <= j)
			swap(v[i++], v[j--]);
	} 

	if (b < j) qsort(v, b, j);
	if (e > i) qsort(v, i, e);
}


void read_udp()
{
	using namespace boost;
	using namespace asio;
	using namespace ip;

	io_service io;
	udp::socket sk(io, udp::endpoint(udp::v4(), 3333));

	unsigned char buf[100];
	size_t size = sk.receive(buffer(buf, 100));
	cout << "\nReceived " << size << " UDP bytes";
}

void read_tcp()
{
	using namespace boost;
	using namespace asio;
	using namespace ip;

	while (true)
	{
		io_service io;
		//tcp::socket sk(io);
		//tcp::acceptor ac(io, tcp::endpoint(tcp::v4(), 3434));
		//cout << "\nWaiting TCP connection...";
		//ac.accept(sk);
		//cout << "\nAccept TCP connection: " << sk.remote_endpoint().address().to_string() << ":" << sk.remote_endpoint().port();
		uint8_t ch;
		uint32_t num = 0;
		cout << endl;
		string scmd;
		system::error_code ec;
		//socket_base::message_flags fl = socket_base::message_end_of_record;
		serial_port sk(io);
		sk.open("COM4", ec);
		if (ec)
		{
			cout << "\nFailed to open COM port";
			continue;
		}

		serial_port::baud_rate br(9600);
		serial_port::flow_control fc(serial_port::flow_control::none);
		serial_port::stop_bits sb(serial_port::stop_bits::one);
		serial_port::character_size cs = serial_port::character_size(8);

		sk.set_option(br);
		sk.set_option(fc);
		sk.set_option(sb);
		sk.set_option(cs);

		while (num = read(sk, buffer(&ch, 1), ec) && ec == 0)
		{
			if (ch == '\r')
				continue;

			if (ch == '\n')
			{
				string ans;
				cout << "\nRecv cmd: " << scmd;

				if (scmd == "OK")
					ans = "OK";

				else if (scmd == "VERSION")
					ans = "AK10350219";

				else if (scmd == "VERSION_DATE")
					ans = "ICL_SW VER 4.2.0 jun 27 2011";

				else if (scmd == "READ 1" || scmd == "READ_LAST" )
					ans = "0.001072,0.00172,0.08,0.08,-0.00023,-2.691354,0.00105,0.00172,0.08, 0.08, -0.00184, -2.691376, 2, 7, 2012, 12, 32, 12.4, 0xff";

				else if (scmd == "CLOCK")
					ans = "11,  22 , 2015,33, 44, 55";

				else if (scmd == "SETUP_PROBE 1")
					ans = "\"PSER1\", 23.7, 23.75, 35, 1, \"FGPCB1\", \"--------\", \"no description\"";

				else if (scmd == "SETUP_PROBE 2")
					ans = "\"PSER2\", 24.7, 24.75, 36, 1, \"FGPCB2\", \"--------\", \"no description\"";

				else
				{
					cout << "\n !!! Unknown cmd";
				}

				if (!ans.empty())
					write(sk, buffer(ans + "\r\n"), ec);

				continue;

			}

			ch = toupper(ch);
			scmd += ch;
		}
	}
}

condition_variable_any vm1;
condition_variable_any vm2;
condition_variable_any vm3;

std::mutex mx1;
std::mutex mx2;
std::mutex mx3;



void thread1(void)
{
	int  i = 0;
	while (i++ < 10)
	{
		mx1.lock();
		vm1.wait(mx1);
		mx1.unlock();
		cout << "\nthread 1";
		vm2.notify_one();
	}
}

void thread2(void)
{
	int  i = 0;
	while (i++ < 10)
	{
		mx2.lock();
		vm2.wait(mx2);
		mx2.unlock();
		cout << "\nthread 2";
		vm3.notify_one();
	}
}

void thread3(void)
{
	int  i = 0;
	while (i++ < 10)
	{
		mx3.lock();
		vm3.wait(mx3);
		mx3.unlock();

		cout << "\nthread 3";
		vm1.notify_one();
	}
}

void test_case1()
{
	vector <size_t> v(100000, 0);

	size_t s = v.size();
	size_t i = 0;
	for (size_t& n : v)
	{
		if (i == 101 || i == 55077 || i == 77099)
			i++;
		
		n = i++;

	}

	size_t cnt = v[0];
	for (size_t& n : v)
		if ((n & 1) == (cnt & 1))
			cnt++;
		else
		{
			cout << "\nMissed num = " << cnt;
			cnt += 2;
		}
}

void testptr(int* pint)
{
	*pint = 123;
}

int _tmain(int argc, _TCHAR* argv[])
{
	unsigned short p = (unsigned short)type_t::param1;

	int pint = 333;
	testptr(&pint);

	vector<int> v1 = { 1, 3, 5, 7 };
	vector<string> v2 = { "First", "Second" };
	list<pair<string, string>> l1 = { { "One", "1" } };
	v1 = { 1, 13, 17, 19 };

	for (const string& val : v2)
		cout << val << endl;
	
	float fv1 { 7.3f };
	
	auto mf = [](int& x) { x *= 2; };
	for_each(v1.begin(), v1.end(), mf );

	class1_t cl2 = class1_t(true);
	class1_t cl3 = class1_t(1);
	class1_t cl4 = class1_t(short(1));

	typedef tuple<string, double, int> mytup_t;


	string s = "Hello";
	vector<int> v = { 1, 22, 3, 4, 5 };
	auto x = make_tuplet(s, v, 1.2);

	auto mt1 = make_tuple("one", 1.1, 1);
	mytup_t mt2 = mt1;

	class1_t cl5;
	str1_t str1;

	auto f1 = bind(pmul, _1,_2);
	auto f2 = bind(&class1_t::mul, cl5, _1, _2);
	str1.f = f2;

	int m = f1(4, 5);
	m = f2(5, 6);
	m = str1.mul(10, 3);

 
	auto pt1 = chrono::steady_clock::now();
	this_thread::sleep_for(seconds(1));
	auto pt2 = chrono::steady_clock::now();
	auto td = (pt2 - pt1);
	
	string sraw = R"(This is raw string \n\t)";
	cout << sraw;

	ifstream inpf ("c:\\file2.txt");
	inpf.setf(ios_base::skipws);
	vector<long long> nums{istream_iterator<long long>(inpf), istream_iterator<long long>() };

	size_t size;
	size = sizeof(long);
	
	set<string> l;
		
	while (!inpf.fail())
	{
		string s;
		inpf >> s;
		l.insert(s);
	}


	vector<int> v3;

	for (int i = 0; i < 2000; i++)
		v3.push_back(rand_int(0, 1000000));

	qsort(v3);
	bool issort = is_sorted(v3.begin(), v3.end());
	qsort(v3);
	issort = is_sorted(v3.begin(), v3.end());

	thread udp_rd = thread(read_udp);

	using namespace boost;
	using namespace asio;
	using namespace ip;

	io_service io;
	udp::socket sk(io, udp::v4());
	sk.connect(udp::endpoint(ip::address_v4::from_string("127.0.0.1"), 3333));

	vector<unsigned char> buf(100, 'a');
	this_thread::sleep_for(seconds(1));
	sk.send(asio::buffer(buf));
	udp_rd.join();

	thread tcp_rd = thread(read_tcp);
	tcp_rd.join();
//	tcp::socket sk2(io, tcp::v4());
//	sk2.connect(tcp::endpoint(ip::address_v4::from_string("127.0.0.1"), 3434));
//	sk2.send(buffer(buf, 10));

	tcp_rd.join();

	thread th1 = thread(thread1);
	thread th2 = thread(thread2);
	thread th3 = thread(thread3);

	mx1.lock();
	vm1.notify_one();
	mx1.unlock();

	vector<int> v_1{ 1, 3, 5, 7, 9 };
	vector<int> v_2{ -1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	vector<int> v_3;

	vector<int>::const_iterator it1 = v_1.begin();
	vector<int>::const_iterator it2 = v_2.begin();

	while (it1 != v_1.end() && it2 != v_2.end())
		if (*it1 < *it2)
			it1++;
		else if (*it2 < *it1)
			it2++;
		else
		{
			v_3.push_back(*it1);
			it1++;
			it2++;
		}
	
	vector<int> v_4;
	for (int i = 0; i < 1; i++)
		v_4.push_back(rand_int(0, 100));

	this_thread::sleep_for(seconds(1));

	bool le = is_littelendian();

	string sp1{ "7262" };
	string sp2 = sp1;
	int n = atoi(sp1.c_str());

	size_t cnt = 1;
	do
	{
		cout << endl << cnt++ << ". " << sp1 << (sp1 == sp2 ? " == " : " != ") << sp2;
		next_perm(sp2);
	}
	//while (next_permutation(sp1.begin(), sp1.end()));
	while (next_perm(sp1));

	for (size_t p = 0; p <= 100; p++)
		cout << endl<< p << " --> " << fib2(p);


	//test_case1();
	//this_thread::sleep_for(seconds(100));

	return 0;
}

