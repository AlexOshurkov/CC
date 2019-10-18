#include "..//common/chat_client.hpp"



int main()
{
	io_context io;

	ChatClient cl(io);

	if (cl.connect("192.168.0.108"))
	{
		cl.sendMessage("Hello from client\r");
		io.run_for(10s);
	}
    
}

