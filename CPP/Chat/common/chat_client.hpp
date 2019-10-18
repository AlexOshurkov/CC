#pragma once

#include "defs.hpp"

class ChatClient {
	friend class ChatServer;

public:
	ChatClient(io_context& io) :
		_io(io),
		_socket(_io)
	{

	}

	ChatClient(io_context& io, const ip::tcp::endpoint& ep) :
		_io(io),
		_socket(_io),
		_ep(ep)
	{

	}

	virtual ~ChatClient() {

			_socket.close();
	}

	bool connect(const char* srvIpAddrv) {
		
		boost::system::error_code ec;
		_ep = ip::tcp::endpoint(ip::make_address(srvIpAddrv), TCP_PORT);
		_socket.connect(_ep, ec);

		if (!ec)
			startReading();

		return !ec;
	}

	bool sendMessage(const string& msg) {

		if (!_socket.is_open())
			return false;

		boost::system::error_code ec;
		_socket.write_some(buffer(msg.c_str(), msg.size()), ec);
		return !ec;
	}

	void setOnError(function< void(ChatClient*, const boost::system::error_code&)> onErrorCb) {
		_onError = onErrorCb;
	}

protected:

	void startReading() {
		async_read_until(_socket, dynamic_buffer(_msg), '\r', 
			std::bind(&ChatClient::onMsgRead, this, std::placeholders::_1, std::placeholders::_2));
	}


	void onMsgRead(const boost::system::error_code& ec, std::size_t bytes_transferred) {

		if (ec) {
			_socket.cancel();
			_socket.close();
			if (_onError)
				_onError(this, ec);
		}
		else if (bytes_transferred > 0) {
			cout << "\n> " << _msg;
			_msg.clear();
		}

		if (_socket.is_open())
			startReading();
	}


private:
	io_context& _io;
	ip::tcp::endpoint _ep;
	ip::tcp::socket _socket;
	std::function <void(ChatClient*, const boost::system::error_code&)> _onError;

	string _msg;
	char _buf[255];	
};
