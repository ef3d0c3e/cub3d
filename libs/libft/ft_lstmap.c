/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/06 14:56:07 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <bits/floatn-common.h>
#include <stdio.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ret;
	t_list	*cur;

	if (!lst || !f || !del)
		return (0);
	ret = ft_lstnew(f(lst->content));
	if (!ret)
		return (ret);
	cur = ret;
	while (lst)
	{
		cur->next = ft_lstnew(f(lst->content));
		if (!cur->next)
			return (ft_lstclear(&ret, del), ret);
		cur = cur->next;
		lst = lst->next;
	}
	cur->next = 0;
	return (ret);
}
/*
#include "test/test.h"
#include <stdlib.h>

static void	*map_itoa(void *v)
{
	return ft_itoa(*(int*)v);
}

FT_EXPORT_TEST(lstmap, {
	int *x = malloc(sizeof(int));
	*x = 64;
	t_list *l1 = ft_lstnew(x);
	int *y = malloc(sizeof(int));
	*y = 256;
	t_list *l2 = ft_lstnew(y);
	int *z = malloc(sizeof(int));
	*z = 1;
	t_list *l3 = ft_lstnew(z);

	ft_lstadd_back(&l1, l2);
	ft_lstadd_back(&l1, l3);
	t_list *new = ft_lstmap(l1, map_itoa, free);

	ASSERT(ft_strncmp((char*)new->content, "64", 255) == 0);
	ASSERT(ft_strncmp((char*)new->next->content, "256", 255) == 0);
	ASSERT(ft_strncmp((char*)new->next->next->content, "1", 255) == 0);

	ft_lstclear(&new, free);
})
*/
