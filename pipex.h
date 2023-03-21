/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vburton <vburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:37:47 by victor            #+#    #+#             */
/*   Updated: 2023/03/21 20:42:34 by vburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "ft_printf/ft_printf.h"
# include <sys/wait.h>

typedef struct s_cmd
{
	char	**array;
}			t_cmd;

typedef struct s_pipex
{
	int		*pid;
	char	*input;
	char	*output;
	char	**envp;
	t_cmd	*cmd;
}			t_pipex;

/*** init ***/
int		ft_init(t_pipex	*pipex, char **argv, char **envp);

/*** parsing ***/
int		ft_get_cmd(t_pipex *pipex, char **argv);
char	*ft_grep_path(char **envp);
void	ft_get_cmd_path(t_cmd *cmd, char **path_array);

/*** execution ***/
void	ft_execute(t_pipex pipex);

/*** free ***/
void	ft_free(t_cmd *cmd);
void	ft_free_split(char **array);

#endif