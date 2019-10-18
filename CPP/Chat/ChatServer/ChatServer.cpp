
#include "../common/chat_server.hpp"

int main()
{
	io_context io;

	ChatServer cs(io);
	
	if (cs.listen())
	{
		cout << "\nServer started on port: " << TCP_PORT;
		io.run();
	}

}

