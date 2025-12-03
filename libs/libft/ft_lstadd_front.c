/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/05 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

/*
#include "test/test.h"
#include <stdlib.h>

FT_EXPORT_TEST(lstadd_front, {
	int x = 64;
	int y = 256;
	t_list *l1 = ft_lstnew(&x);
	ASSERT(l1->next == 0);
	ASSERT(*(int*)l1->content == 64);
	t_list *l2 = ft_lstnew(&y);
	ASSERT(l2->next == 0);
	ASSERT(*(int*)l2->content == 256);

	t_list *front = l1;
	ft_lstadd_front(&front, l2);
	ASSERT(front == l2);
	ASSERT(front->next == l1);
	free(l1);
	free(l2);
})
*/
