/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/05 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void *content)
{
	t_list	*head;

	head = malloc(sizeof(t_list));
	if (head)
	{
		head->content = content;
		head->next = 0;
	}
	return (head);
}

/*
#include "test/test.h"

FT_EXPORT_TEST(lstnew, {
	int x = 64;
	t_list *l = ft_lstnew(&x);
	ASSERT(l->next == 0);
	ASSERT(*(int*)l->content == 64);
	free(l);
})
*/
