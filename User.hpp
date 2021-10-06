#ifndef USER_HPP
# define USER_HPP

class Server;
class Message;
class Channel;

# include <string>
# include <iostream>
# include <sstream>
# include <unistd.h>
# include <vector>
# include <queue>
# include <set>
# include <sys/socket.h>
# include <algorithm>
# include <fcntl.h>
# include "utils.hpp"
# include "Message.hpp"
# include "Server.hpp"
# include "Channel.hpp"
# include "sendError.hpp"

enum Role
{
	client,
	ChanelOperator,
	IrcOperator,
};

class User
{
	private:
		Server							*server;
		bool							enterUsername;
		bool							enterNickname;
		bool							registered;
		std::string						password;
		std::string						nickname;
		std::string						username;
		std::string						hostname;
		std::string						servername;
		std::string						realname;
		int								sockfd;
		std::queue<std::string>			messages;
		Role							role;
		std::vector<const Channel *>	channels;

		bool							isValidNick(const std::string &nick) const;
		bool							isValidChannelName(const std::string &name) const;

		void							passCmd(const Message &msg);
		int								nickCmd(const Message &msg);
		int								userCmd(const Message &msg);
		void							joinCmd(const Message &msg);
		void 							privmsgCmd(const Message &msg);

		int								checkConnection();

		User();
		User(const User& copy);
		User	&operator=(const User& other);
	public:
		User(int sockfd, Server &server);
		~User();

		const int						&getSockfd() const;
		const std::string				&getNickname() const;
		const std::string				&getServername() const;
		std::string						getPrefix() const;

		void							readMessage();
		std::vector<std::string>		parseCommand();
		int								hadleMessages();
		void							sendMessage(const std::string &msg) const;
};

#endif
