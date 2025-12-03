/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/06 14:34:02 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*i;
	t_list	*tmp;

	if (!lst || !*lst || !del)
		return ;
	i = *lst;
	while (i)
	{
		del(i->content);
		tmp = i;
		i = i->next;
		free(tmp);
	}
	*lst = NULL;
}

/*
#include "test/test.h"

FT_EXPORT_TEST(lstclear, {
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

	ASSERT(l1->next == l2);
	ASSERT(l2->next == l3);

	ft_lstclear(&l1, free);
	ASSERT(l1 == NULL);
})
*/
