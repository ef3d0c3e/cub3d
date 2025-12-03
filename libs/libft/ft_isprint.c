/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/04 11:54:01 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int c)
{
	return (c >= ' ' && c <= '~');
}

/*
#include "test/test.h"

FT_EXPORT_TEST(isprint, {
	ASSERT(ft_isprint('0') == 1);
	ASSERT(ft_isprint('1') == 1);
	ASSERT(ft_isprint('2') == 1);
	ASSERT(ft_isprint('3') == 1);
	ASSERT(ft_isprint('4') == 1);
	ASSERT(ft_isprint('5') == 1);
	ASSERT(ft_isprint('6') == 1);
	ASSERT(ft_isprint('7') == 1);
	ASSERT(ft_isprint('8') == 1);
	ASSERT(ft_isprint('9') == 1);
	ASSERT(ft_isprint('a') == 1);
	ASSERT(ft_isprint('~') == 1);
	ASSERT(ft_isprint(' ') == 1);
	ASSERT(ft_isprint(128) != 1);
	ASSERT(ft_isprint(256) != 1);
	ASSERT(ft_isprint(-5) != 1);
})
*/
