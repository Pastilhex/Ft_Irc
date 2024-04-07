/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ircserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialves-m <ialves-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:07:13 by ialves-m          #+#    #+#             */
/*   Updated: 2024/04/07 11:11:44 by ialves-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ircserv.hpp"

std::string getCurrentDateTime()
{
    char buffer[80];
    std::time_t rawtime;
    std::tm* timeinfo;

    std::time(&rawtime);
    timeinfo = std::localtime(&rawtime);

    std::strftime(buffer, 80, "%H:%M:%S %b %d %Y", timeinfo);

    return std::string(buffer);
}

bool isCMD(std::string message, std::string cmd)
{
	size_t cmdPos = message.find(cmd);

	 if (cmdPos == 0 || (cmdPos != std::string::npos && (cmdPos == 1 || (cmdPos > 1 && message[cmdPos - 1] == '\n'))))
		return true;
	return false;
}

std::string getInput(std::string message, std::string cmd)
{
	int msgSize = cmd.size() + 1;
	return message.substr(message.find(cmd) + msgSize, message.find_first_of(" \n\r\t", message.find(cmd) + msgSize) - (message.find(cmd) + msgSize));
}