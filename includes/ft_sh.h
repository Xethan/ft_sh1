/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/07 12:56:19 by ncolliau          #+#    #+#             */
/*   Updated: 2015/02/16 12:13:18 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SH_H
# define FT_SH_H

# include "libft.h"
# include "get_next_line.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>

# define C_NONE		"\033[0m"
# define C_BOLD		"\033[1m"
# define C_BLACK	"\033[30m"
# define C_RED		"\033[31m"
# define C_GREEN	"\033[32m"
# define C_BROWN	"\033[33m"
# define C_BLUE		"\033[34m"
# define C_MAGENTA	"\033[35m"
# define C_CYAN		"\033[36m"
# define C_GRAY		"\033[37m"

# define WRITE_END	1
# define READ_END	0

typedef struct stat	t_stat;

typedef struct		s_arg
{
	char			**arg;
	size_t			sz_arg;
	int				*left_fd;
	int				*right_fd;
	char			**stop;
	int				nb_stop;
	struct	s_arg	*next;
}					t_arg;

int					built_in(t_arg *plist);

int					launch_cmds(t_arg *plist, int old_pdes[2], char **path, size_t nb_path);
char				*get_stdin(char **stop, size_t nb_stop);
void				put_in_stdin(char *line);

void				fd_to_fd(t_arg *plist);
void				fd_to_pipe(t_arg *plist, int new_pdes[2]);
void				stdin_to_fd(t_arg *plist, char *line);
void				stdin_to_pipe(t_arg *plist, char *line, int new_pdes[2]);
void				left_pipe_to_fd(t_arg *plist, char *pipe);
void				left_pipe_to_pipe(t_arg *plist, int new_pdes[2], char *pipe);

t_arg				*cmd_to_list(char *cmd);
void				cmd_to_list_and_exec(char **arg, size_t sz_arg);

int					is_redir(char *s);
char				*replace_tabs(char *line);
char				**tilde_and_dollar(char **cmd, size_t sz_cmd);
int					*ft_realloc_int(int *tab, int nb);

void				access_error(int error, char *name);
int					check_access(char *bin_path);
int					find_path(char **path, size_t nb_path, char **arg);
char				*ft_strtrijoin(char *s1, char *s2, char *s3);

void				chdir_me(char *target);
void				change_dir(char **arg, size_t sz_arg);

void				up_shlvl(void);
void				ft_env(void);
void				ft_setenv(char *name, char *value);
void				ft_unsetenv(char **to_del, size_t sz_arg);

void				dup_env(char **env, int ac, char **av);
void				free_env(void);
size_t				len_env(void);
char				*find_env(char *str);
int					nb_env(char *to_find);

void				lstdel(t_arg **begin_list);

#endif
