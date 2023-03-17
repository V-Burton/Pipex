/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vburton <vburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:44:24 by victor            #+#    #+#             */
/*   Updated: 2023/03/08 16:55:59 by vburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_get_cmd(t_pipex *pipex, char **argv, int argc);
char	*ft_grep_path(char **envp);
void	ft_get_cmd_path(t_cmd *cmd, char **path_array);

void	ft_init(t_pipex	*pipex, int argc, char **argv, char **envp)
{
	int		i;
	char	*path;
	char	**path_array;

	i = 0;
	pipex->nb_cmd = argc - 3;
	pipex->input = argv[1];
	pipex->output = argv[argc - 1];
	pipex->envp = envp;
	pipex->cmd = malloc(sizeof(t_cmd) * (pipex->nb_cmd));
	ft_get_cmd(pipex, argv, argc);
	path = ft_grep_path(envp);
	path_array = ft_split(path, ':');
	if (!path_array)
		path_array = NULL ;
	while (i < pipex->nb_cmd)
	{
		ft_get_cmd_path(&pipex->cmd[i], path_array);
		i++;
	}
	ft_free_split(path_array);
}
