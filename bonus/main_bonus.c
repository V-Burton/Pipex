/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vburton <vburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:37:45 by victor            #+#    #+#             */
/*   Updated: 2023/03/24 17:36:07 by vburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	loop_wait(t_pipex pipex);

int	main(int argc, char **argv, char **envp)
{
	int		save_stdin;
	t_pipex	pipex;

	save_stdin = dup(STDIN_FILENO);
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
	dup2(save_stdin, STDIN_FILENO);
	close(save_stdin);
	loop_wait(pipex);
	ft_free(pipex.cmd, pipex.nb_cmd);
	if (pipex.limiter != NULL)
		free(pipex.limiter);
	return (1);
}

void	loop_wait(t_pipex pipex)
{
	int	i;

	i = 0;
	while (i < pipex.nb_cmd)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
}
