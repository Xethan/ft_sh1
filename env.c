/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/12 15:32:34 by ncolliau          #+#    #+#             */
/*   Updated: 2015/01/12 15:33:27 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

void	disp_env(char **env, t_env var)
{
	int		i;

	i = 0;
	while (i != var.sz)
	{
		ft_putendl(env[i]);
		i++;
	}
}