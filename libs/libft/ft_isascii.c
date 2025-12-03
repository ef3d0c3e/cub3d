/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/04 11:54:01 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}

/*
#include "test/test.h"

FT_EXPORT_TEST(isascii, {
	ASSERT(ft_isascii('0') == 1);
	ASSERT(ft_isascii('1') == 1);
	ASSERT(ft_isascii('2') == 1);
	ASSERT(ft_isascii('3') == 1);
	ASSERT(ft_isascii('4') == 1);
	ASSERT(ft_isascii('5') == 1);
	ASSERT(ft_isascii('6') == 1);
	ASSERT(ft_isascii('7') == 1);
	ASSERT(ft_isascii('8') == 1);
	ASSERT(ft_isascii('9') == 1);
	ASSERT(ft_isascii('a') == 1);
	ASSERT(ft_isascii('~') == 1);
	ASSERT(ft_isascii(' ') == 1);
	ASSERT(ft_isascii(256) != 1);
	ASSERT(ft_isascii(-5) != 1);
})
*/
