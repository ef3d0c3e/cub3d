/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/05 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

/*
#include "test/test.h"
#include <sys/mman.h>

FT_EXPORT_TEST(putchar_fd, {
	int fd = memfd_create("memory_buffer", 0);
	lseek(fd, 0, SEEK_SET);
	ft_putchar_fd('A', fd);
	ft_putchar_fd('B', fd);
	ft_putchar_fd('~', fd);

	char buffer[1024];
	lseek(fd, 0, SEEK_SET);
	read(fd, buffer, 1024);
	ASSERT(buffer[0] == 'A')
	ASSERT(buffer[1] == 'B')
	ASSERT(buffer[2] == '~')
	close(fd);
})
*/
