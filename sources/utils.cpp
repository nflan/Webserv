/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:09:06 by mgruson           #+#    #+#             */
/*   Updated: 2023/03/16 12:10:12 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "utils.hpp"

utils::utils()
{
	std::cout << "utils Default Constructor called" << std::endl;
}
utils::utils(utils const &obj)
{
	*this = obj;
}
utils::~utils()
{
	std::cout << "utils Destructor called" << std::endl;
}
utils &utils::operator=(utils const &obj)
{
	std::cout << "utils Copy assignment operator called" << std::endl;
	return *this;
}

static int countSubstringOccurrences(const std::string& str, const std::string& subStr)
{
    int count = 0;
    size_t pos = 0;
    while ((pos = str.find(subStr, pos)) != std::string::npos) {
        ++count;
        pos += subStr.length();
    }
    return count;
}
