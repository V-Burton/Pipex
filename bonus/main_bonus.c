/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vburton <vburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:37:45 by victor            #+#    #+#             */
/*   Updated: 2023/03/21 20:15:10 by vburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc < 5)
		return (ft_printf("Five arguments are recquired.\n"));
	check_here_doc_status(&pipex, argv);
	if (pipex.here_doc == 1)
	{
		if (ft_init_here_doc(&pipex, argc, argv, envp) == -1)
		{
			if (pipex.limiter)
				free(pipex.limiter);
			return (ft_free(pipex.cmd, pipex.nb_cmd), 1);
		}
	}
	else
	{
		if (ft_init(&pipex, argc, argv, envp) == -1)
			return (ft_free(pipex.cmd, pipex.nb_cmd), 1);
	}
	ft_execute(pipex);
	ft_free(pipex.cmd, pipex.nb_cmd);
	if (pipex.limiter != NULL)
		free(pipex.limiter);
	return (1);
}
