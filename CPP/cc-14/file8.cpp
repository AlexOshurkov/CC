#include "precomp.hpp"
#pragma hdrstop

using namespace std;

void ReverseString(string& str)
{
	if (str.empty())
		return;

	string::iterator beg = str.begin();
	string::iterator end = --str.end();

	while (beg < end)
	{
		swap(*beg, *end);
		++beg;
		--end;
	}
}

size_t StrLen(const char* str)
{
	if (str == nullptr)
		return 0;

	const char* beg = str;
	while (*str)
		++str;

	return str - beg;
}

const char* ReverseStringRaw(const char* sstr)
{
	if (sstr == nullptr)
		nullptr;

	size_t len = StrLen(sstr);
	char* str = new char[len];
	memset(str, 0, len + 1);
	memcpy(str, sstr, len);
	char* beg = str;
	char* end = beg + len - 1;

	while (beg < end)
	{
		char ch = *beg;
		*beg = *end;
		*end = ch;
		++beg;
		--end;
	}

	return str;
}

void ReverseStringTest()
{
	string s1;
	string s2 = "ab";
	string s3 = "abc";

	const char* rs1 = nullptr;
	const char* rs2 = "";
	const char* rs3 = "ab";
	const char* rs4 = "abc";

	ReverseString(s1);
	ReverseString(s2);
	ReverseString(s3);

	rs1 = ReverseStringRaw(rs1);
	rs2 = ReverseStringRaw(rs2);
	rs3 = ReverseStringRaw(rs3);
	rs4 = ReverseStringRaw(rs4);
}

struct MyClassHash;
struct MyClassEqual;

class MyClass
{
	string str;
	int v;
	friend struct MyClassHash;
	friend struct MyClassEqual;
public:

	MyClass() = default;
	MyClass(string str_, int v_) : str(str_), v(v_) {}	
};

struct MyClassHash
{
	size_t operator()(const MyClass& val) const
	{
		return val.v;
	}
};

struct MyClassEqual
{
	bool operator()(const MyClass& l, const MyClass& r) const
	{
		return l.v == r.v;
	}
};

static void TestHash()
{
	unordered_set<string> us1;
	us1.insert("a");
	us1.insert("b");
	us1.insert("c");
	
	typedef unordered_set<MyClass, MyClassHash, MyClassEqual> us2_t;
	us2_t us2;
	us2.insert(MyClass("a", 1));
	us2.insert(MyClass("b", 2));
	us2.insert(MyClass("c", 3));

	us2_t::iterator it1 = us2.find(MyClass("a", 1));
	us2_t::iterator it2 = us2.find(MyClass("a", 2));
	us2_t::iterator it3 = us2.find(MyClass("a", 3));
	us2_t::iterator it4 = us2.find(MyClass("a", 4));

	size_t hash_val1 = hash<string>()("a");
	size_t hash_val3 = hash<int>()(1);
}

string GetNextPerm(string str)
{
	string::reverse_iterator rit1 = str.rbegin();
	string::reverse_iterator rit2 = str.rend();
	while (rit1 != str.rend())
	{
		if (rit2 != str.rend() && *rit1 < *rit2)
		{
			swap(*rit1, *rit2);
			return str;
		}

		rit2 = rit1;
		++rit1;
	}

	return str;
}

void TestPerm(string s)  // bad
{
    size_t cnt = 0;
	do
	{
		cout << ++cnt << ". " << s << endl;		
	} while (next_permutation(s.begin(), s.end()));
}

struct Node {
	Node* next;
	Node* prev;
	int value;
	int key;
	Node(Node* p, Node* n, int k, int val) :prev(p), next(n), key(k), value(val) {};
	Node(int k, int val) :prev(NULL), next(NULL), key(k), value(val) {};
};

class Cache {

protected:
	map<int, Node*> mp; //map the key to the node in the linked list
	int cp;  //capacity
	Node* tail; // double linked list tail pointer
	Node* head; // double linked list head pointer
	virtual void set(int, int) = 0; //set function
	virtual int get(int) = 0; //get function

};

class LRUCache : public Cache
{
public:

    void push_front(Node* node)
    {
        head = new Node(nullptr, head, node->key, node->value);

        if (head->next != nullptr)
            head->next->prev = head;

        if (head->next == nullptr)
            tail = head;
    }

    void remove_node(Node* node)
    {
        if (node == nullptr)
            return;

        if (node->prev == nullptr && node->next == nullptr)
        {
            delete node;
            head = tail = nullptr;
        }
        else if (node->next == nullptr)
        {
            node->prev->next = node->next;
            tail = tail->prev;
            delete node;
        }
    }

    Node* front_node() const
    {
        return head;
    }

    Node* back_node() const
    {
        return tail;
    }

public:

    LRUCache(int cap) 
    {
        cp = cap;
        head = tail = nullptr;
    }

    void set(int key, int val)
    {
        map<int, Node*>::iterator it = mp.find(key);

        if (mp.size() == cp)
        {
            mp.erase(back_node()->key);
            remove_node(back_node());
        }

        if (it == mp.end())
        {
            push_front(new Node(nullptr, head, key, val));
            mp[head->key] = head;
        }
        else
        {
            Node* curnode = it->second;

            if (curnode == front_node())
                front_node()->value = val;
            else
            {
                mp.erase(curnode->key);
                push_front(new Node(nullptr, head, curnode->key, curnode->value));
                mp[front_node()->key] = front_node();
                remove_node(curnode);
            }
        }
    }

    int get(int key)
    {
        map<int, Node*>::iterator it = mp.find(key);

        if (it == mp.end())
            return -1;
        else
        {
            Node* curnode = it->second;

            if (curnode != front_node())
            {
                mp.erase(curnode->key);
                push_front(new Node(nullptr, head, curnode->key, curnode->value));
                mp[front_node()->key] = front_node();
                remove_node(curnode);
            }

            return front_node()->value;
        }
    }
};


void TestCache()
{
    for (int i = 0; i < 100; i++)
        for (int j = 0; j < 1100; j++)
        {
            void* p = new char[100];
            cout << "\n" << j;
            for (int k = 0; k < 10000; k++)
                ;// size_t rv = random_device()();
        }

    LRUCache ch(5);
    
    ch.set(1, 11);
    ch.set(2, 22);
    ch.set(3, 33);

    ch.set(4, 44);
    ch.set(5, 55);
    ch.set(6, 66);

}

#include <boost/asio.hpp>
#include <boost/bind.hpp>
using namespace boost;
using namespace asio;

class Server
{
    ip::udp::socket sock;
    ip::udp::endpoint endp;
    char buf[50000];

protected:

    void start_recv()
    {
        sock.async_receive_from(asio::buffer(buf), endp,
            boost::bind(&Server::handle_receive, this,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));

    }

    void handle_receive(const boost::system::error_code& error, std::size_t bytes_transferred)
    {
        cout << "Message from (" << endp.address().to_string() << ":" << endp.port() <<"): " << buf << endl << "bytes: " << bytes_transferred << endl;
        start_recv();
    }

public:

    Server(io_service& io) : sock(io, ip::udp::endpoint(ip::address_v4::from_string("127.0.0.1"), 2000))
    {
        start_recv();
    }
};

class Client
{
    ip::udp::socket sock;

public:

    Client(io_service& io) : sock(io)
    {

    }

    void send(string str)
    {
        boost::system::error_code ec;
        ip::udp::endpoint endp(ip::address_v4::from_string("127.0.0.1"), 2000);
        sock.connect(endp, ec);
        sock.send(asio::buffer(str),0, ec);
    }

};

#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

class server
{
public:
    server(boost::asio::io_service& io_service, short port)
        : io_service_(io_service),
        socket_(io_service, udp::endpoint(udp::v4(), port))
    {
        socket_.async_receive_from(
            boost::asio::buffer(data_, max_length), sender_endpoint_,
            boost::bind(&server::handle_receive_from, this,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
    }

    void handle_receive_from(const boost::system::error_code& error,
        size_t bytes_recvd)
    {
        if (!error && bytes_recvd > 0)
        {
            socket_.async_send_to(
                boost::asio::buffer(data_, bytes_recvd), sender_endpoint_,
                boost::bind(&server::handle_send_to, this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
        }
        else
        {
            socket_.async_receive_from(
                boost::asio::buffer(data_, max_length), sender_endpoint_,
                boost::bind(&server::handle_receive_from, this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
        }
    }

    void handle_send_to(const boost::system::error_code& error, size_t bytes_sent)
    {
        socket_.async_receive_from(
            boost::asio::buffer(data_, max_length), sender_endpoint_,
            boost::bind(&server::handle_receive_from, this,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
    }

private:
    boost::asio::io_service& io_service_;
    udp::socket socket_;
    udp::endpoint sender_endpoint_;
    enum { max_length = 1024 };
    char data_[max_length];
};

int magn(int argc, char* argv[])
{
    try
    {
       // if (argc != 2)
      //  {
      //      std::cerr << "Usage: async_udp_echo_server <port>\n";
      //      return 1;
     //   }

        boost::asio::io_service io_service;

        using namespace std; // For atoi.
        server s(io_service, 100);

        io_service.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}

struct MyStruct
{
    string name;
};

struct class2
{
    int val;
    class2(int v) : val(v) {
        cout << "ctor: " << val << endl; 
    };
    ~class2()  {
        cout << "dtor: " << val << endl;
    };

};

void func(unique_ptr<class2>& p)
{
    cout << "v: " << p->val << endl;
}

void TestConvert()
{
    int val1 = 123;
    long val2 = 0x12345678L;
    long long val3 = 0x1234567812345678LL;
    float val4 = 123.456f;
    double val5 = 123.456;
    
    string s1 = std::to_string(val1);
    string s2 = std::to_string(val2);
    string s3 = std::to_string(val3);
    string s4 = std::to_string(val4);
    string s5 = std::to_string(val5);

    int sval1 = std::stoi(s1);
    long sval2 = std::stol(s2);
    long long sval3 = std::stoll(s3);
    float sval4 = std::stof(s4);
    double sval5 = std::stod(s5);

    
}

extern "C"
void TestCFunc(const char* name);

extern "C"
void TestToCFunc(const char* str)
{
    cout << "\nHi from C++, " << str << endl << flush;
}

template <size_t MAX = 100>
void PrintNumbers()
{
    for (size_t i = 1; i <= MAX; ++i)
        cout << endl << setw(4) << right << i << ". " << flush;
}

int main8(int, char**)
{
 
    PrintNumbers<23>();
 //   io_service io;
 //   Server srv(io);
 //   Client cl(io);
 //   string s(32, 'A');
 //   cl.send(s);
 //   cl.send("hello world 2");
  //  cl.send("hello world 3");

   // io.run();

	return 0;
}

std::condition_variable cv;
std::mutex cv_m; // This mutex is used for three purposes:
                 // 1) to synchronize accesses to i
                 // 2) to synchronize accesses to std::cerr
                 // 3) for the condition variable cv
int i = 0;

void waits()
{
    std::unique_lock<std::mutex> lk(cv_m);
    std::cerr << "Waiting... \n";
    cv.wait(lk, [] {return i == 1; });
    std::cerr << "...finished waiting. i == 1\n";
}

void signals()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    {
        std::lock_guard<std::mutex> lk(cv_m);
        std::cerr << "Notifying...\n";
    }
    cv.notify_all();

    std::this_thread::sleep_for(std::chrono::seconds(1));

    {
        std::lock_guard<std::mutex> lk(cv_m);
        std::cerr << "Notifying again...\n";
        i = 1;
    }
    cv.notify_all();
}

int main8()
{
    std::thread t1(waits), t2(waits), t3(waits), t4(signals);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    return 0;
}

