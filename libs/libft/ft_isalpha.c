/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/05 17:48:06 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

/*
#include "test/test.h"

FT_EXPORT_TEST(isalpha, {
		ASSERT(ft_isalpha('a') == 1);
		ASSERT(ft_isalpha('A') == 1);
		ASSERT(ft_isalpha('z') == 1);
		ASSERT(ft_isalpha('Z') == 1);
		ASSERT(ft_isalpha('0') != 1);
		ASSERT(ft_isalpha(256) != 1);
		ASSERT(ft_isalpha(-5) != 1);
})
*/
