/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/06 14:33:18 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*i;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	i = *lst;
	while (i->next)
		i = i->next;
	i->next = new;
}

/*
#include "test/test.h"
#include <stdlib.h>

FT_EXPORT_TEST(lstadd_back, {
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
	free(l1);
	free(l2);
})
*/
