/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/06 14:29:51 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*i;

	if (!lst)
		return (lst);
	i = lst;
	while (i->next)
		i = i->next;
	return (i);
}

/*
#include "test/test.h"
#include <stdlib.h>

FT_EXPORT_TEST(lstlast, {
	int x = 64;
	int y = 256;
	int z = 1;
	t_list *l1 = ft_lstnew(&x);
	ASSERT(l1->next == 0);
	ASSERT(*(int*)l1->content == 64);
	t_list *l2 = ft_lstnew(&y);
	ASSERT(l2->next == 0);
	ASSERT(*(int*)l2->content == 256);
	t_list *l3 = ft_lstnew(&z);
	ASSERT(l3->next == 0);
	ASSERT(*(int*)l3->content == 1);

	ft_lstadd_back(&l1, l2);
	ASSERT(l1->next == l2);
	ASSERT(ft_lstlast(l1) == l2);

	ft_lstadd_back(&l1, l3);
	ASSERT(l1->next->next == l3);
	ASSERT(ft_lstlast(l1) == l3);

	free(l1);
	free(l2);
	free(l3);
})
*/
