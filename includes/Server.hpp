/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialves-m <ialves-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:50:44 by ialves-m          #+#    #+#             */
/*   Updated: 2024/04/16 16:39:45 by ialves-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _SERVER_
#define _SERVER_

#include "ircserv.hpp"
class Channel;
class Client;

class Server
{

private:
	int _socket;
	int _port;
	struct sockaddr_in _address;
	std::string _hostname;
	std::string _password;
	std::map<std::string, Channel> _channels;
	std::map<std::string, Client> _globalUsers;
	std::vector<std::string> _input;
	pollfd serverPoll;

public:
	// Constructor
	Server(std::string password);

	// Getters
	int getSocket(void);
	struct sockaddr_in getAddress(void);
	std::string getHostname(void) const;
	std::string getPassword(void);
	std::map<std::string, Channel> &getChannels(void);
	std::map<std::string, Client> &getGlobalUsers(void);
	std::string getAddressIP(void);
	std::string getClientNick(std::string &channelName, std::string &clientName);
	std::string getOpNick(std::string &channelName, std::string clientName);
	std::vector<std::string> getInput(void);
	Client &getClientBySocket(int socket, Client &client);
	bool isUserInvited(std::string user, std::string channel);

	// Setters
	void setSocket(int newSocket);
	void setAddress(struct sockaddr_in newAddress);
	void setHostname(std::string hostname);
	void setNewChannel(std::string channel_name, Channel channel);
	void setInput(std::string input);

	// Commands
	void INVITE(Client client);											// CMD channel
	void JOIN(int clientSocket, Client &client); 						// CMD channel
	void KICK(std::string message, Client client);						// CMD channel
	void LIST(int clientSocket, Client &client);
	void MODE(std::string message, Client client);						// CMD channel
	void PART(std::string message, Client &client);						// CMD channel
	void PRIVMSG(std::string message, Client client);					// CMD channel
	void TOPIC(Client &client);					// CMD channel
	void WHO(int clientSocket, const Client client);					// CMD channel

	// Utils
	bool addClientToGlobalUsers(Client client);
	bool bindSocket(const int &serverSocket, const struct sockaddr_in &serverAddress);
	bool checkConnections(const int &serverSocket);
	bool checkInput(std::vector<std::string> input, Client client);
	void connectClient(const int &serverSocket);
	void createHostname(void);
	int createSocket(void);
	struct sockaddr_in createAddress(int port);
	void handlePasswordMode(const std::vector<std::string> &mode_cmd, std::map<std::string, Channel>::iterator it, char modeFlag, Client client, char modeOption);
	void handlePrivateAccessMode(std::map<std::string, Channel>::iterator it, char modeOption, char modeFlag, Client client);
	void handleRestrictedTopicMode(std::map<std::string, Channel>::iterator it, char modeFlag, Client client, char modeOption);
	std::string handleOperatorMode(const std::vector<std::string> &mode_cmd, std::map<std::string, Channel>::iterator it, char modeFlag, Client client);
	void handleUserLimitMode(const std::vector<std::string> &mode_cmd, std::map<std::string, Channel>::iterator it, char modeFlag);
	void createNewClient(std::vector<pollfd> &fds, const int &serverSocket);
	std::vector<std::string> trimInput(std::string input);
	void removeClientFromGlobalUsers(Client client);
	bool run(void);
	void processMsg(Client &client, std::vector<pollfd> &fds, char *buffer, int bytesRead, int i);
	bool start(char *str);
	void sendWelcome(int clientSocket, Client &client);
	void updateChannel(Client client, std::string channelName);
	void broadcastKICK(Client client, std::string kicked, std::string channelName, std::string msg);
	void broadcastTOPIC(Client client, std::string channelName);
	static bool isValidPort(char *str);
};

#endif
