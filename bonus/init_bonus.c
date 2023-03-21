/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vburton <vburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:44:24 by victor            #+#    #+#             */
/*   Updated: 2023/03/22 00:51:55 by vburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	set_input(t_pipex *pipex, char **argv);
void	ft_initialize_path_array(t_pipex *pipex, char *path, char **path_array);

int	ft_init(t_pipex	*pipex, int argc, char **argv, char **envp)
{
	char	*path;
	char	**path_array;

	pipex->nb_cmd = argc - (3 + pipex->here_doc);
	pipex->output = argv[argc - 1];
	set_input(pipex, argv);
	pipex->envp = envp;
	pipex->cmd = malloc(sizeof(t_cmd) * (pipex->nb_cmd));
	if (pipex->cmd == NULL || ft_get_cmd(pipex, argv, argc) == -1)
		return (-1);
	path = ft_grep_path(envp);
	path_array = ft_split(path, ':');
	if (!path_array)
		path_array = NULL ;
	ft_initialize_path_array(pipex, path, path_array);
	if (path_array)
		ft_free_split(path_array);
	return (0);
}

void	set_input(t_pipex *pipex, char **argv)
{
	if (pipex->here_doc == 1)
	{
		guess_here_doc(pipex);
		pipex->input = NULL;
	}
	else
		pipex->input = argv[1];
}

void	ft_initialize_path_array(t_pipex *pipex, char *path, char **path_array)
{
	int	i;

	i = 0;
	while (path != NULL && i < pipex->nb_cmd)
	{
		if (ft_strchr(pipex->cmd[i].array[0], '.') == NULL)
			ft_get_cmd_path(&pipex->cmd[i], path_array);
		else
			ft_error(pipex->cmd[i].array[0]);
		i++;
	}
}
