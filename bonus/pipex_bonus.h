/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vburton <vburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:37:47 by victor            #+#    #+#             */
/*   Updated: 2023/03/24 15:08:32 by vburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "../libft/libft.h"
# include "../ft_printf/ft_printf.h"

typedef struct s_cmd
{
	char	**array;
}			t_cmd;

typedef struct s_pipex
{
	int		nb_cmd;
	int		here_doc;
	char	*limiter;
	char	*input;
	char	*output;
	char	**envp;
	t_cmd	*cmd;
}			t_pipex;

/*** init ***/
int		ft_init(t_pipex	*pipex, int argc, char **argv, char **envp);

/*** parsing ***/
int		ft_get_cmd(t_pipex *pipex, char **argv, int argc);
char	*ft_grep_path(char **envp);
void	ft_get_cmd_path(t_cmd *cmd, char **path_array);

/*** execution ***/
void	ft_execute(t_pipex pipex);

/*** free ***/
void	ft_free(t_cmd *cmd, int nb_cmd);
void	ft_free_split(char **array);
int		ft_error(char *cmd);

/*** here_doc ***/
void	check_here_doc_status(t_pipex *pipex, char **argv);
int		guess_here_doc(t_pipex *pipex);
void	fils_here_doc(t_pipex *pipex, int *fd);

#endif
