/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/05 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	putnbr_fd_impl(int n, int fd)
{
	if (n >= 10 || n <= -10)
		putnbr_fd_impl(n / 10, fd);
	ft_putchar_fd((n % 10) * ((n >= 0) - (n < 0)) + '0', fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
		ft_putchar_fd('-', fd);
	putnbr_fd_impl(n, fd);
}

/*
#include "test/test.h"
#include <sys/mman.h>
#include <unistd.h>

FT_EXPORT_TEST(putnbr_fd, {
	int fd = memfd_create("memory_buffer", 0);
	lseek(fd, 0, SEEK_SET);
	ft_putnbr_fd(2147483647, fd);
	ft_putchar_fd('\n', fd);
	ft_putnbr_fd(-2147483648, fd);
	ft_putchar_fd('\n', fd);
	ft_putnbr_fd(0, fd);
	ft_putchar_fd(0, fd);

	char buffer[1024];
	lseek(fd, 0, SEEK_SET);
	read(fd, buffer, 1024);
	ASSERT(ft_strncmp(buffer, "2147483647\n-2147483648\n0", 255) == 0)
	close(fd);
})
*/
