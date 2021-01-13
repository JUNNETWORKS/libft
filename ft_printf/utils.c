/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtanaka <jtanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 02:39:12 by jtanaka           #+#    #+#             */
/*   Updated: 2020/12/17 23:53:51 by jtanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		write_c_n_times(char c, int n)
{
	int i;

	i = 0;
	if (n <= 0)
		return (0);
	while (i++ < n)
		write(1, &c, 1);
	return (n);
}

size_t	ft_wcslen(wchar_t *s)
{
	size_t	len;

	len = 0;
	while (s[len] != L'\0')
	{
		if (s[++len] == L'\0')
			return (len);
		if (s[++len] == L'\0')
			return (len);
		if (s[++len] == L'\0')
			return (len);
		len++;
	}
	return (len);
}
