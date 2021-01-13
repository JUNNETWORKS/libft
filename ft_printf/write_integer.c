/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_integer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtanaka <jtanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 02:37:07 by jtanaka           #+#    #+#             */
/*   Updated: 2020/12/18 02:16:50 by jtanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"

int		write_integer(t_fmt *fmt_data, long long n)
{
	char		*num;
	int			write_size;
	int			prefix_size;

	prefix_size = 0;
	if (fmt_itoa(n, fmt_data, &num, 0) < 0)
		return (0);
	if (n < 0 && !is_unsigned_type(fmt_data->type))
		(fmt_data->is_minus)++;
	fmt_data->is_zero = !n;
	if (will_output_sign(fmt_data))
		prefix_size++;
	if (will_output_base(fmt_data))
		prefix_size += 2;
	write_size = output_fmt_nbr(num, fmt_data, prefix_size);
	free(num);
	return (write_size);
}

int		fmt_itoa(long long n, t_fmt *fmt_data, char **num, long long len)
{
	unsigned long long	un;
	unsigned long long	base;

	len++;
	base = get_base_from_type(fmt_data->type);
	un = (is_unsigned_type(fmt_data->type) || n >= 0) ? n : -n;
	if (un >= base)
		if ((len = fmt_itoa(un / base, fmt_data, num, len)) < 0)
			return (-1);
	if (un < base)
	{
		if (!(*num = malloc(len + 1)))
			return (-1);
		(*num)[len] = '\0';
		fmt_data->digit = len;
		len = 0;
	}
	if (fmt_data->type == TYPE_HEX_UP)
		(*num)[len++] = "0123456789ABCDEF"[un % base];
	else
		(*num)[len++] = "0123456789abcdef"[un % base];
	return (len);
}

int		output_fmt_nbr(char *num, t_fmt *fmt_data, int prefix_size)
{
	int		zeros;
	int		spaces;

	zeros = 0;
	spaces = 0;
	if (fmt_data->precision == 0 && fmt_data->is_zero)
		fmt_data->digit = 0;
	if (fmt_data->precision > fmt_data->digit)
		zeros = fmt_data->precision - fmt_data->digit;
	if (fmt_data->width > (zeros + prefix_size + fmt_data->digit))
		spaces = fmt_data->width - (zeros + prefix_size + fmt_data->digit);
	if (fmt_data->flag & FLAG_ZEROS && fmt_data->precision <= 1)
	{
		zeros += spaces;
		spaces = 0;
	}
	return (write_fmt_nbr(num, fmt_data, spaces, zeros));
}

int		write_fmt_nbr(char *num, t_fmt *fmt_data, int spaces, int zeros)
{
	int		write_size;

	write_size = 0;
	if (!(fmt_data->flag & FLAG_LEFT))
		write_size += write_c_n_times(' ', spaces);
	write_size += write(1, get_sign_prefix(fmt_data),
						will_output_sign(fmt_data));
	write_size += write(1, fmt_data->type == TYPE_HEX_UP ? "0X" : "0x",
						will_output_base(fmt_data) ? 2 : 0);
	write_size += write_c_n_times('0', zeros);
	write_size += write(1, num, fmt_data->digit);
	if (fmt_data->flag & FLAG_LEFT)
		write_size += write_c_n_times(' ', spaces);
	return (write_size);
}
