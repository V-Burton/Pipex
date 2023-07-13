/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vburton <vburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:38:24 by victor            #+#    #+#             */
/*   Updated: 2023/03/24 17:24:53 by vburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

void	ft_free(t_cmd *cmd, int nb_cmd)
{
	int	i;

	i = 0;
	if (cmd)
	{
		while (i < nb_cmd)
		{
			ft_free_split(cmd[i].array);
			i++;
		}
		free(cmd);
	}
}

int	ft_error(char *cmd)
{
	if (cmd && access(cmd, X_OK))
	{
		ft_printf("%s : Command not found\n", cmd);
		return (-1);
	}
	else if (!cmd)
	{
		ft_printf(" : Command not found\n");
		return (-1);
	}
	return (0);
}
