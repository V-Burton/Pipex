/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vburton <vburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:44:24 by victor            #+#    #+#             */
/*   Updated: 2023/03/20 21:12:17 by vburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_init(t_pipex	*pipex, int argc, char **argv, char **envp)
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
	if (!pipex->cmd)
		return (-1);
	if (ft_get_cmd(pipex, argv, argc) == -1)
		return (-1);
	path = ft_grep_path(envp);
	path_array = ft_split(path, ':');
	if (!path_array)
		path_array = NULL ;
	while (i < pipex->nb_cmd)
	{
		ft_get_cmd_path(&pipex->cmd[i], path_array);
		i++;
	}
	if (path_array)
		ft_free_split(path_array);
	return (0);
}
