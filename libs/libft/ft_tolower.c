/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/04 11:54:01 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	else
		return (c);
}

/*
#include "test/test.h"

FT_EXPORT_TEST(tolower, {
	ASSERT(ft_tolower('a') == 'a');
	ASSERT(ft_tolower('c') == 'c');
	ASSERT(ft_tolower('t') == 't');
	ASSERT(ft_tolower('z') == 'z');
	ASSERT(ft_tolower('0') == '0');
	ASSERT(ft_tolower('~') == '~');
	ASSERT(ft_tolower('@') == '@');
	ASSERT(ft_tolower('A') == 'a');
	ASSERT(ft_tolower('C') == 'c');
	ASSERT(ft_tolower('T') == 't');
	ASSERT(ft_tolower('Z') == 'z');
	ASSERT(ft_tolower(255) == 255);
	ASSERT(ft_tolower(-255) == -255);
})
*/
