/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/05 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		++i;
	}
	return (i);
}

/*
#include "test/test.h"
#include <stdlib.h>

FT_EXPORT_TEST(lstsize, {
	int x = 64;
	int y = 256;
	t_list *l1 = ft_lstnew(&x);
	ASSERT(l1->next == 0);
	ASSERT(*(int*)l1->content == 64);
	t_list *l2 = ft_lstnew(&y);
	ASSERT(l2->next == 0);
	ASSERT(*(int*)l2->content == 256);

	ft_lstadd_back(&l1, l2);
	ASSERT(l1->next == l2);
	ASSERT(*(int*)l1->next->content == 256);

	ASSERT(ft_lstsize(l1) == 2);
	ASSERT(ft_lstsize(l2) == 1);
	free(l1);
	free(l2);
})
*/
