/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/06 14:27:20 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}

/*
#include "test/test.h"
#include <sys/mman.h>

FT_EXPORT_TEST(putstr_fd, {
	int fd = memfd_create("memory_buffer", 0);
	lseek(fd, 0, SEEK_SET);
	ft_putstr_fd("Hello, World!", fd);
	ft_putchar_fd(0, fd);

	char buffer[1024];
	lseek(fd, 0, SEEK_SET);
	read(fd, buffer, 1024);
	ASSERT(ft_strncmp(buffer, "Hello, World!", 255) == 0)
	close(fd);
})
*/
