/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:07:58 by mgruson           #+#    #+#             */
/*   Updated: 2023/03/16 13:05:08 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>

class utils
{
	private:
	utils();
	utils(utils const &obj);
	~utils();
	utils &operator=(utils const &obj);
	
	public:
	static int countSubstringOccurrences(const std::string& str, const std::string& subStr);

};

#endif