/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtanaka <jtanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 01:03:47 by jtanaka           #+#    #+#             */
/*   Updated: 2020/12/21 05:58:34 by jtanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"

void	parse_flag(const char **format, t_fmt *fmt_data)
{
	while (**format && (**format == '0' || **format == '-' ||
						**format == '#' || **format == '+' ||
						**format == ' '))
	{
		if (**format == '0')
			fmt_data->flag |= FLAG_ZEROS;
		if (**format == '-')
			fmt_data->flag |= FLAG_LEFT;
		if (**format == '#')
			fmt_data->flag |= FLAG_BASE;
		if (**format == '+')
			fmt_data->flag |= FLAG_SIGN;
		if (**format == ' ')
			fmt_data->flag |= FLAG_SPACE;
		(*format)++;
	}
	if (fmt_data->flag & FLAG_LEFT && fmt_data->flag & FLAG_ZEROS)
		fmt_data->flag &= ~FLAG_ZEROS;
	if (fmt_data->flag & FLAG_SIGN && fmt_data->flag & FLAG_SPACE)
		fmt_data->flag &= ~FLAG_SPACE;
}

void	parse_width(const char **format, t_fmt *fmt_data, va_list *ap)
{
	int width;

	if (**format == '*')
	{
		width = va_arg(*ap, int);
		if (width < 0)
		{
			fmt_data->flag |= FLAG_LEFT;
			fmt_data->flag &= ~FLAG_ZEROS;
			width = -width;
		}
		fmt_data->width = width;
		(*format)++;
	}
	else if (ft_isdigit(**format))
	{
		width = ft_atoi(*format);
		fmt_data->width = width;
		(*format) += num_len(*format);
	}
}

void	parse_precision(const char **format, t_fmt *fmt_data, va_list *ap)
{
	long long precision;

	if (**format == '.')
	{
		(*format)++;
		if (**format == '*')
		{
			precision = va_arg(*ap, int);
			if (precision >= 0)
				fmt_data->precision = precision;
			(*format)++;
		}
		else if (**format == '-')
		{
			(*format)++;
			(*format) += num_len(*format);
		}
		else
		{
			fmt_data->precision = ft_atoi(*format);
			(*format) += num_len(*format);
		}
	}
}

void	parse_length(const char **format, t_fmt *fmt_data)
{
	if (**format == 'l')
	{
		(*format)++;
		if (**format == 'l')
		{
			fmt_data->length = LEN_LL;
			(*format)++;
		}
		else
			fmt_data->length = LEN_L;
	}
	if (**format == 'h')
	{
		(*format)++;
		if (**format == 'h')
		{
			fmt_data->length = LEN_HH;
			(*format)++;
		}
		else
			fmt_data->length = LEN_H;
	}
}

void	parse_type(const char **format, t_fmt *fmt_data)
{
	if (**format == 'd' || **format == 'i')
		fmt_data->type = TYPE_INT;
	else if (**format == 'u')
		fmt_data->type = TYPE_UINT;
	else if (**format == 'x')
		fmt_data->type = TYPE_HEX_LOW;
	else if (**format == 'X')
		fmt_data->type = TYPE_HEX_UP;
	else if (**format == 'c')
		fmt_data->type = TYPE_CHAR;
	else if (**format == 's')
		fmt_data->type = TYPE_STRING;
	else if (**format == 'p')
		fmt_data->type = TYPE_POINTER;
	else if (**format == '%')
		fmt_data->type = TYPE_PERCENT;
	else
		return ;
	if (is_integer_type(fmt_data->type))
		if (fmt_data->precision != -1)
			fmt_data->flag &= ~FLAG_ZEROS;
	if (is_integer_type(fmt_data->type) || fmt_data->type == TYPE_POINTER)
		if (fmt_data->precision == -1)
			fmt_data->precision = 1;
	(*format)++;
}
