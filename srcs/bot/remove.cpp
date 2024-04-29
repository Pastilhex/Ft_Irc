/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpicoli- <lpicoli-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 19:51:44 by lpicoli-          #+#    #+#             */
/*   Updated: 2024/04/29 22:38:48 by lpicoli-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ircserv.hpp"

void Bot::remove(Server &server, Channel &channel, Client &client)
{
    std::map<std::string, Client>::iterator bot;
    
    bot = channel.getUsers().find(channel.getBot()->getNick());
    std::cout << bot->first << std::endl;
    channel.getUsers().erase(bot);

    std::string message = "🤖 Beep boop! " + client.getNick() + " thinks they can get rid of me, huh? Well, I'll be back! ";
    message += "Watch your back, " + client.getNick() + "! 😜";
    SEND(client.getSocket(), ":Marvin!"+ bot->second.getNick() + "@"\
    + server.getHostname()+" PRIVMSG "+channel.getName()+" :" + message + "\r\n", "Error sending PART message to client.");
}