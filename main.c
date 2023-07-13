/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vburton <vburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:37:45 by victor            #+#    #+#             */
/*   Updated: 2023/03/24 13:36:45 by vburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		i;
	int		save_stdin;
	t_pipex	pipex;

	i = 0;
	save_stdin = dup(STDIN_FILENO);
	if (argc != 5)
		return (ft_printf("Wrong number of arguments.\n"));
	if (ft_init(&pipex, argv, envp) == -1)
		return (ft_free(pipex.cmd), 1);
	ft_execute(pipex);
	dup2(save_stdin, STDIN_FILENO);
	close(save_stdin);
	while (i < 2)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
	ft_free(pipex.cmd);
	return (1);
}
