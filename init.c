/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vburton <vburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:44:24 by victor            #+#    #+#             */
/*   Updated: 2023/03/17 15:56:40 by vburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_init(t_pipex	*pipex, char **argv, char **envp)
{
	int		i;
	char	*path;
	char	**path_array;

	i = 0;
	pipex->input = argv[1];
	pipex->output = argv[4];
	pipex->envp = envp;
	pipex->cmd = malloc(sizeof(t_cmd) * 2);
	if (!pipex->cmd)
		return (-1);
	if (ft_get_cmd(pipex, argv) == -1)
		return (-1);
	path = ft_grep_path(envp);
	path_array = ft_split(path, ':');
	if (!path_array)
		path_array = NULL ;
	while (path_array != NULL && path != NULL && i < 2)
	{
		ft_get_cmd_path(&pipex->cmd[i], path_array);
		i++;
	}
	if (path_array)
		ft_free_split(path_array);
	return (0);
}
