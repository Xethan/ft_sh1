/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/15 16:54:52 by ncolliau          #+#    #+#             */
/*   Updated: 2015/01/15 18:11:42 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

extern char	**g_env;

char	**dup_env(char **env)
{
	char	**cpy;
	int		i;

	i = 0;
	while (env[i] != NULL)
		i++;
	cpy = (char **)malloc((i + 1) * sizeof(char *));
	cpy[i] = NULL;
	while (i-- != 0)
		cpy[i] = ft_strdup(env[i]);
	return (cpy);
}

void	free_env(void)
{
	int		i;

	i = 0;
	while (g_env[i] != NULL)
	{
		free(g_env[i]);
		i++;
	}
	free(g_env);
}

size_t	len_env(void)
{
	size_t	i;

	i = 0;
	while (g_env[i] != NULL)
		i++;
	return (i);
}

char	*env(char *str)
{
	size_t	i;
	char	*cmp;

	i = 0;
	while (g_env[i] != NULL)
	{
		cmp = ft_strcdup(g_env[i], '=');
		if (ft_strequ(str, cmp))
		{
			free(cmp);
			return (g_env[i] + ft_strlen(str) + 1);
		}
		free(cmp);
		i++;
	}
	return (NULL);
}

int		nb_env(char *to_find)
{
	int		i;
	char	*tmp;

	i = 0;
	while (g_env[i] != NULL)
	{
		tmp = ft_strcdup(g_env[i], '=');
		if (ft_strequ(to_find, tmp))
		{
			free(tmp);
			return (i);
		}
		free(tmp);
		i++;
	}
	return (-1);
}
