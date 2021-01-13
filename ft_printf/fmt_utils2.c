/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmt_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtanaka <jtanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 11:03:50 by jtanaka           #+#    #+#             */
/*   Updated: 2020/12/21 06:53:24 by jtanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

bool		will_output_sign(t_fmt *fmt_data)
{
	return (fmt_data->is_minus ||
		((fmt_data->flag & FLAG_SIGN || fmt_data->flag & FLAG_SPACE) &&
			!is_unsigned_type(fmt_data->type)));
}

char		*get_sign_prefix(t_fmt *fmt_data)
{
	if (fmt_data->is_minus)
		return ("-");
	else if (fmt_data->flag & FLAG_SPACE)
		return (" ");
	else if (fmt_data->flag & FLAG_SIGN)
		return ("+");
	else
		return ("");
}

long long	fmt_va_arg(t_fmt *fmt_data, va_list *ap)
{
	long long	n;

	if (fmt_data->length == LEN_H)
	{
		if (is_unsigned_type(fmt_data->type))
			n = (unsigned short)va_arg(*ap, int);
		else
			n = (short)va_arg(*ap, int);
	}
	if (fmt_data->length == LEN_HH)
	{
		if (is_unsigned_type(fmt_data->type))
			n = (unsigned char)va_arg(*ap, int);
		else
			n = (int)va_arg(*ap, int);
	}
	if (fmt_data->length == LEN_L)
	{
		if (is_unsigned_type(fmt_data->type))
			n = (unsigned long)va_arg(*ap, long);
		else
			n = va_arg(*ap, long);
	}
	else if (fmt_data->length == LEN_LL)
		n = va_arg(*ap, long long);
	else
	{
		if (is_unsigned_type(fmt_data->type))
			n = (unsigned int)va_arg(*ap, int);
		else
			n = va_arg(*ap, int);
	}
	return (n);
}
