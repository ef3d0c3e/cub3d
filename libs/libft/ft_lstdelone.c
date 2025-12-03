/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/06 14:33:43 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}

/*
#include "test/test.h"
#include <stdlib.h>

FT_EXPORT_TEST(lstdelone, {
	int *x = malloc(sizeof(int));
	*x = 64;
	int *y = malloc(sizeof(int));
	*y = 256;
	t_list *l1 = ft_lstnew(x);
	ASSERT(l1->next == 0);
	ASSERT(*(int*)l1->content == 64);
	t_list *l2 = ft_lstnew(y);
	ASSERT(l2->next == 0);
	ASSERT(*(int*)l2->content == 256);

	ft_lstadd_back(&l1, l2);
	ASSERT(l1->next == l2);
	ft_lstdelone(l1, free);
	ft_lstdelone(l2, free);
})
*/
