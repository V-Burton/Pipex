/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <victor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:37:42 by victor            #+#    #+#             */
/*   Updated: 2023/03/06 16:11:39 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_get_cmd(t_pipex *pipex, char **argv, int argc)
{
	int	i;
	t_cmd	*cmd;

	i = pipex->nb_cmd;
	cmd = pipex->cmd;
	while (i < argc - 1)
	{
		cmd->array = ft_split(argv[i], ' ');
		i++;
		cmd++;
	}
}

char	*ft_grep_path(char **envp)
{
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			return (*envp + 5);
		envp++;
	}
	return (NULL);
}

void	ft_get_cmd_path(t_cmd *cmd, char **path_array)
{
	int		i;
	char	*buffer;
	char 	*path_join;

	i = 0;
	if (access(cmd->array[0], X_OK) == 0)
		return ;
	while (path_array[i])
	{
		buffer = ft_strjoin(path_array[i], "/");
		path_join = ft_strjoin(buffer, cmd->array[0]);
		free(buffer);
		if (access(path_join, X_OK) == 0)
		{
			free(cmd->array[0]);
			cmd->array[0] = ft_strdup(path_join);
			free(path_join);
			return ;
		}
		i++;
	}
}