/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorCorresp.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 13:16:39 by nflan             #+#    #+#             */
/*   Updated: 2023/04/06 15:39:01 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ErrorCorresp.hpp"

ErrorCorresp::ErrorCorresp()
{
	_Corresp[STATUS100] = "100";
	_Corresp[STATUS101] = "101";
	_Corresp[STATUS200] = "200";
	_Corresp[STATUS201] = "201";
	_Corresp[STATUS202] = "202";
	_Corresp[STATUS203] = "203";
	_Corresp[STATUS204] = "204";
	_Corresp[STATUS205] = "205";
	_Corresp[STATUS206] = "206";
	_Corresp[STATUS300] = "300";
	_Corresp[STATUS301] = "301";
	_Corresp[STATUS302] = "302";
	_Corresp[STATUS303] = "303";
	_Corresp[STATUS304] = "304";
	_Corresp[STATUS305] = "305";
	_Corresp[STATUS307] = "307";
	_Corresp[STATUS400] = "400";
	_Corresp[STATUS401] = "401";
	_Corresp[STATUS402] = "402";
	_Corresp[STATUS403] = "403";
	_Corresp[STATUS404] = "404";
	_Corresp[STATUS405] = "405";
	_Corresp[STATUS406] = "406";
	_Corresp[STATUS407] = "407";
	_Corresp[STATUS408] = "408";
	_Corresp[STATUS409] = "409";
	_Corresp[STATUS410] = "410";
	_Corresp[STATUS411] = "411";
	_Corresp[STATUS412] = "412";
	_Corresp[STATUS413] = "413";
	_Corresp[STATUS414] = "414";
	_Corresp[STATUS415] = "415";
	_Corresp[STATUS416] = "416";
	_Corresp[STATUS417] = "417";
	_Corresp[STATUS500] = "500";
	_Corresp[STATUS501] = "501";
	_Corresp[STATUS502] = "502";
	_Corresp[STATUS503] = "503";
	_Corresp[STATUS504] = "504";
	_Corresp[STATUS505] = "505";
}

ErrorCorresp::~ErrorCorresp() {}

std::map<std::string, std::string>	ErrorCorresp::getCorresp()
{
	return (_Corresp);
}
