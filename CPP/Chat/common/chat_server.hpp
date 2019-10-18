#pragma once

#include <map>
#include <mutex>
#include <thread>
#include "defs.hpp"
#include "chat_client.hpp"


class ChatServer : public ChatClient {

	mutex _mtx;

public:

	ChatServer(io_context& io) :
		ChatClient(io, ip::tcp::endpoint(ip::tcp::v4(), TCP_PORT)),
		_acp(_io)
	{

	}

	bool listen() {

		try {
			_acp.open(_ep.protocol());
			_acp.bind(_ep);
			_acp.listen();
			startAccept();

		}
		catch (const boost::system::system_error& ec) {
			cout << "\nerror: " << ec.what();
			return false;
		}
		
		return true;
	}

protected:

	void startAccept() {
		ChatClient* cl = new ChatClient(_io);
		//_acp.async_accept(cl->_socket, std::bind(&ChatServer::onAccept, this, std::placeholders::_1, cl));
		_acp.async_accept(cl->_socket, [this, cl](const auto& ec) { this->onAccept(ec, cl);  });
	}

	void onAccept(const boost::system::error_code& error, ChatClient* cl) {
		string rclinfo =  cl->_socket.remote_endpoint().address().to_string()
			+ ":"
			+ std::to_string(cl->_socket.remote_endpoint().port());

		cout << "\nGot new connection [" << _clients.size() + 1 << "]: " << rclinfo;

		{
			unique_lock<mutex> l(_mtx);
			_clients[cl] = rclinfo;
		}

		cl->sendMessage("Hello from server\r");
		cl->startReading();
		cl->setOnError(std::bind(&ChatServer::onClientError, this, std::placeholders::_1, std::placeholders::_2));

		startAccept();
	}


	void onClientError(ChatClient* cl, const boost::system::error_code& ec) {

		
		cout << "\nClient error[" << _clients.size() <<"]: " << _clients[cl] << " (" << ec.message() << ")";
		_clients.erase(cl);

	}

private:

	map<ChatClient*, string> _clients;
	ip::tcp::acceptor _acp;
};