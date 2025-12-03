/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/05 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

/*
#include "test/test.h"
#include <stdlib.h>

static void add_one(void *x)
{
	*(int *)x += 1;
}

FT_EXPORT_TEST(lstiter, {
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
	ft_lstiter(l1, add_one);

	ASSERT(*(int*)l1->content == 65);
	ASSERT(*(int*)l2->content == 257);
	ASSERT(*(int*)l3->content == 2);

	ft_lstclear(&l1, free);
})
*/
