/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vburton <vburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:38:24 by victor            #+#    #+#             */
/*   Updated: 2023/03/22 00:52:31 by vburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_split(char **array)
{
	int	i;

	i = 0;
	if (array)
	{
		while (array[i])
		{
			free(array[i]);
			i++;
		}
		free(array);
	}
}

void	ft_free(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd)
	{
		while (i < 2)
		{
			ft_free_split(cmd[i].array);
			i++;
		}
		free(cmd);
	}
}

void	ft_error(char *cmd)
{
	if (ft_strcmp(cmd, ".") == 0)
		ft_printf("%s : filename argument required\n", cmd);
	else if (ft_strcmp(cmd, "./") == 0)
		ft_printf("%s : no such file or directory\n", cmd);
	else
		ft_printf("%s : Command not found\n", cmd);
}
