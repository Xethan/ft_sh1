/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/13 13:22:55 by ncolliau          #+#    #+#             */
/*   Updated: 2015/02/18 15:44:32 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_sh.h"

extern char	**g_env;

int		open_it(char *file)
{
	int		fd;

	if (file[0] == '>')
		fd = open(file + 1, O_CREAT | O_RDWR | O_APPEND, 0664);
	else
		fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0664);
	return (fd);
}

void	fd_to_fd(t_arg *plist)
{
	pid_t	pid;
	size_t	i;
	size_t	j;
	int		lfd;
	int		rfd;

	i = 0;
	while (plist->left_fd && plist->left_fd[i])
	{
		j = 0;
		while (plist->right_fd && plist->right_fd[j])
		{
			if ((rfd = open_it(plist->right_fd[j])) == -1)
				return ;
			if ((lfd = open(plist->left_fd[i], O_RDONLY)) == -1)
				return ;
			pid = fork();
			if (pid > 0)
				wait(NULL);
			if (pid == 0)
			{
				dup2(lfd, STDIN_FILENO);
				dup2(rfd, STDOUT_FILENO);
				execve(plist->arg[0], plist->arg, g_env);
			}
			close(lfd);
			close(rfd);
			j++;
		}
		i++;
	}
}

void	fd_to_output(t_arg *plist, int new_pdes[2])
{
	pid_t	pid;
	size_t	i;
	int		fd;

	i = 0;
	while (plist->left_fd && plist->left_fd[i])
	{
		if ((fd = open(plist->left_fd[i], O_RDONLY)) == -1)
			return ;
		pid = fork();
		if (pid > 0)
		{
			wait(NULL);
			if (plist->next)
				close(new_pdes[WRITE_END]);
		}
		if (pid == 0)
		{
			dup2(fd, STDIN_FILENO);
			if (plist->next)
			{
				close(new_pdes[READ_END]);
				dup2(new_pdes[WRITE_END], STDOUT_FILENO);
			}
			execve(plist->arg[0], plist->arg, g_env);
		}
		close(fd);
		i++;
	}
}

void	stdin_to_fd(t_arg *plist, char *line)
{
	pid_t	pid;
	size_t	i;
	int		fd;

	i = 0;
	while (plist->right_fd && plist->right_fd[i])
	{
		if ((fd = open_it(plist->right_fd[i])) == -1)
			return ;
		pid = fork();
		if (pid > 0)
			wait(NULL);
		if (pid == 0)
		{
			put_in_stdin(line);
			dup2(fd, STDOUT_FILENO);
			execve(plist->arg[0], plist->arg, g_env);
		}
		close(fd);
		i++;
	}
}

void	stdin_to_output(t_arg *plist, char *line, int new_pdes[2])
{
	pid_t	pid;

	pid = fork();
	if (pid > 0)
	{
		wait(NULL);
		if (plist->next)
			close(new_pdes[WRITE_END]);
	}
	if (pid == 0)
	{
		put_in_stdin(line);
		if (plist->next)
		{
			close(new_pdes[READ_END]);
			dup2(new_pdes[WRITE_END], STDOUT_FILENO);
		}
		execve(plist->arg[0], plist->arg, g_env);
	}
}

void	input_to_fd(t_arg *plist, char *pipe)
{
	pid_t	pid;
	size_t	i;
	int		fd;

	i = 0;
	while (plist->right_fd && plist->right_fd[i])
	{
		if ((fd = open_it(plist->right_fd[i])) == -1)
			return ;
		pid = fork();
		if (pid > 0)
			wait(NULL);
		if (pid == 0)
		{
			if (pipe != NULL)
				put_in_stdin(pipe);
			dup2(fd, STDOUT_FILENO);
			execve(plist->arg[0], plist->arg, g_env);
		}
		close(fd);
		i++;
	}
}

void	input_to_output(t_arg *plist, int new_pdes[2], char *pipe)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_putendl_fd("Fork failed", 2);
		return ;
	}
	if (pid > 0)
	{
		wait(NULL);
		if (plist->next)
			close(new_pdes[WRITE_END]);
	}
	if (pid == 0)
	{
		if (pipe != NULL)
			put_in_stdin(pipe);
		if (plist->next)
		{
			close(new_pdes[READ_END]);
			dup2(new_pdes[WRITE_END], STDOUT_FILENO);
		}
		execve(plist->arg[0], plist->arg, g_env);
	}
}
