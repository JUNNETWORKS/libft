/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtanaka <jtanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 07:20:53 by jtanaka           #+#    #+#             */
/*   Updated: 2020/12/18 02:13:41 by jtanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf(const char *format, ...)
{
	int		write_size;
	va_list	ap;

	write_size = 0;
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			write_size += parse_and_write(&format, &ap);
		}
		else
		{
			write_size += write(1, format, 1);
			format++;
		}
	}
	return (write_size);
}

int		parse_and_write(const char **format, va_list *ap)
{
	t_fmt	fmt_data;

	initialize_t_fmt(&fmt_data);
	parse_flag(format, &fmt_data);
	parse_width(format, &fmt_data, ap);
	parse_precision(format, &fmt_data, ap);
	parse_length(format, &fmt_data);
	parse_type(format, &fmt_data);
	return (write_fmt_data(&fmt_data, ap));
}

int		write_fmt_data(t_fmt *fmt_data, va_list *ap)
{
	long long	n;

	if (fmt_data->type == TYPE_PERCENT)
		return (write_percent(fmt_data));
	if (fmt_data->type == TYPE_CHAR)
		return (fmt_data->length == LEN_L ? write_wchr(fmt_data, ap) :
			write_char(fmt_data, ap));
	else if (fmt_data->type == TYPE_STRING)
		return (fmt_data->length == LEN_L ? write_wstr(fmt_data, ap) :
			write_string(fmt_data, ap));
	else if (fmt_data->type == TYPE_UINT || fmt_data->type == TYPE_HEX_LOW ||
			fmt_data->type == TYPE_HEX_UP || fmt_data->type == TYPE_INT)
	{
		n = fmt_va_arg(fmt_data, ap);
		return (write_integer(fmt_data, n));
	}
	else if (fmt_data->type == TYPE_POINTER)
	{
		n = va_arg(*ap, long);
		return (write_integer(fmt_data, n));
	}
	return (0);
}
