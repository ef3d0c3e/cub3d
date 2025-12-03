/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/04 11:54:01 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

/*
#include "test/test.h"

FT_EXPORT_TEST(isdigit, {
	ASSERT(ft_isdigit('0') == 1);
	ASSERT(ft_isdigit('1') == 1);
	ASSERT(ft_isdigit('2') == 1);
	ASSERT(ft_isdigit('3') == 1);
	ASSERT(ft_isdigit('4') == 1);
	ASSERT(ft_isdigit('5') == 1);
	ASSERT(ft_isdigit('6') == 1);
	ASSERT(ft_isdigit('7') == 1);
	ASSERT(ft_isdigit('8') == 1);
	ASSERT(ft_isdigit('9') == 1);
	ASSERT(ft_isdigit('a') != 1);
	ASSERT(ft_isdigit('~') != 1);
	ASSERT(ft_isdigit(' ') != 1);
	ASSERT(ft_isdigit(256) != 1);
	ASSERT(ft_isdigit(-5) != 1);
})
*/
