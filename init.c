/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <victor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:44:24 by victor            #+#    #+#             */
/*   Updated: 2023/03/16 18:05:35 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_init(t_pipex	*pipex, char **argv, char **envp)
{
	int		i;
	char	*path;
	char	**path_array;

	i = 0;
	pipex->input = argv[1];
	pipex->output = argv[4];
	pipex->envp = envp;
	pipex->cmd = malloc(sizeof(t_cmd) * 2);
	ft_get_cmd(pipex, argv);
	path = ft_grep_path(envp);
	path_array = ft_split(path, ':');
	if (!path_array)
		path_array = NULL ;
	while (path != NULL && i < 2)
	{
		ft_get_cmd_path(&pipex->cmd[i], path_array);
		i++;
	}
	if (path_array)
		ft_free_split(path_array);
}
