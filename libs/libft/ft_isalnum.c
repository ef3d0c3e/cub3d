/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/04 11:54:01 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int c)
{
	return ((c >= '0' && c <= '9')
		|| (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z'));
}

/*
#include "test/test.h"

FT_EXPORT_TEST(isalnum, {
	ASSERT(ft_isalnum('0') == 1);
	ASSERT(ft_isalnum('1') == 1);
	ASSERT(ft_isalnum('2') == 1);
	ASSERT(ft_isalnum('3') == 1);
	ASSERT(ft_isalnum('4') == 1);
	ASSERT(ft_isalnum('5') == 1);
	ASSERT(ft_isalnum('6') == 1);
	ASSERT(ft_isalnum('7') == 1);
	ASSERT(ft_isalnum('8') == 1);
	ASSERT(ft_isalnum('9') == 1);
	ASSERT(ft_isalnum('a') == 1);
	ASSERT(ft_isalnum('A') == 1);
	ASSERT(ft_isalnum('z') == 1);
	ASSERT(ft_isalnum('Z') == 1);
	ASSERT(ft_isalnum('~') != 1);
	ASSERT(ft_isalnum(' ') != 1);
	ASSERT(ft_isalnum(256) != 1);
	ASSERT(ft_isalnum(-5) != 1);
})
*/
