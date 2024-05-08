/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sendGoodbye.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialves-m <ialves-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 20:23:27 by lpicoli-          #+#    #+#             */
/*   Updated: 2024/05/08 20:54:55 by ialves-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ircserv.hpp"

void Bot::sendGoodbye(Server server, Channel &channel, Client &client)
{
	std::string goodbyeMsg = +"👋 Goodbye " + client.getNick() + "! We'll miss you here at " + channel.getName() + ". ";
	goodbyeMsg += "If you ever want to come back, know that you're always welcome! 🌟";
	goodbyeMsg += " Until then, take care and see you soon! 👋😢\r\n";
	SEND(client.getSocket(), ":Marvin!" + client.getUsername() + "@" + server.getHostname() + " PRIVMSG " + channel.getName() + " :" + goodbyeMsg, "Error sending PART message to client.");
}
