/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/04 11:54:01 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	else
		return (c);
}

/*
#include "test/test.h"

FT_EXPORT_TEST(toupper, {
	ASSERT(ft_toupper('a') == 'A');
	ASSERT(ft_toupper('c') == 'C');
	ASSERT(ft_toupper('t') == 'T');
	ASSERT(ft_toupper('z') == 'Z');
	ASSERT(ft_toupper('0') == '0');
	ASSERT(ft_toupper('~') == '~');
	ASSERT(ft_toupper('@') == '@');
	ASSERT(ft_toupper('A') == 'A');
	ASSERT(ft_toupper('C') == 'C');
	ASSERT(ft_toupper('T') == 'T');
	ASSERT(ft_toupper('Z') == 'Z');
	ASSERT(ft_toupper(255) == 255);
	ASSERT(ft_toupper(-255) == -255);
})
*/
