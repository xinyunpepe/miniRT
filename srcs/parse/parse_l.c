/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_l.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xli <xli@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 11:47:16 by xli               #+#    #+#             */
/*   Updated: 2021/05/12 14:39:56 by xli              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	parse_l_norm_0(t_light *light, char *str, int ct)
{
	double	sign;

	sign = 1.0;
	while (*str && ft_isdigit(*str) == 0 && *str != '.' && *str != '-')
		str++;
	if (*str == 0)
		error_exit("brightness for light not found\n");
	if (*str == '-')
		sign *= -1.0;
	light->brightness = sign * ft_atodouble(&str);
	if (light->brightness < 0.0 || light->brightness > 1.0)
		error_exit("brightness for light out of range\n");
	while (++ct < 3)
	{
		while (*str && ft_isdigit(*str) == 0 && *str != '.' && *str != '-')
			str++;
		if (*str == 0)
			error_exit("color for light invalid\n");
		light->color[ct] = ft_atoi_max(&str);
		if (light->color[ct] < 0 || light->color[ct] > 255)
			error_exit("color for light out of range\n");
	}
}

static void	parse_l_norm_1(t_light *light)
{
	int	ct;

	ct = -1;
	while (++ct < 3)
		light->color[ct] = (int)((double)light->color[ct] * light->brightness);
}

void	parse_l(t_parse *parse, char *str)
{
	int		ct;
	t_light	*light;
	double	sign;

	light = init_light();
	ft_lstadd_back(&(parse->light), ft_lstnew(light));
	ct = -1;
	while (++ct < 3)
	{
		sign = 1.0;
		while (*str && ft_isdigit(*str) == 0 && *str != '.' && *str != '-')
			str++;
		if (*str == 0)
			error_exit("coordinate for light invalid\n");
		if (*str == '-')
		{
			sign *= -1.0;
			if (!(ft_isdigit(*(++str))))
				error_exit("negative number in wrong format\n");
		}
		light->coordinate[ct] = sign * ft_atodouble(&str);
	}
	parse_l_norm_0(light, str, -1);
	parse_l_norm_1(light);
}
