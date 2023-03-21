/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vburton <vburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:37:45 by victor            #+#    #+#             */
/*   Updated: 2023/03/21 23:58:01 by vburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	int		i;
	t_pipex	pipex;

	i = 0;
	if (argc < 5)
		return (ft_printf("Five arguments are recquired.\n"));
	check_here_doc_status(&pipex, argv);
	if (ft_init(&pipex, argc, argv, envp) == -1)
	{
		if (pipex.limiter)
			free(pipex.limiter);
		ft_free(pipex.cmd, pipex.nb_cmd);
		exit (0);
	}
	ft_execute(pipex);
	while (i < pipex.nb_cmd)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
	ft_free(pipex.cmd, pipex.nb_cmd);
	if (pipex.limiter != NULL)
		free(pipex.limiter);
	return (1);
}
