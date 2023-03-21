/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vburton <vburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 19:13:09 by vburton           #+#    #+#             */
/*   Updated: 2023/03/21 22:38:35 by vburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	check_here_doc_status(t_pipex *pipex, char **argv)
{
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		pipex->here_doc = 1;
		pipex->limiter = ft_strjoin(argv[2], "\n");
	}
	else
	{
		pipex->here_doc = 0;
		pipex->limiter = NULL;
	}
}

int	guess_here_doc(t_pipex *pipex)
{
	int		fd[2];
	int		pid;

	if (pipe(fd) == -1)
		return (1);
	pid = fork();
	if (pid == -1)
		perror("An error as occured while attempting to fork");
	if (pid == 0)
		fils_here_doc(pipex, fd);
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		waitpid(pid, NULL, 0);
	}
	return (0);
}

void	fils_here_doc(t_pipex *pipex, int *fd)
{
	char	*next_line;

	close (fd[0]);
	write(1, "pipe heredoc>", 13);
	while (1)
	{
		next_line = get_next_line(STDIN_FILENO);
		if (!next_line || ft_strcmp(next_line, pipex->limiter) == 0)
		{
			free(next_line);
			close (fd[1]);
			break ;
		}
		write(1, "pipe heredoc>", 13);
		write(fd[1], next_line, ft_strlen(next_line));
		free(next_line);
	}
	free(pipex->limiter);
	pipex->limiter = NULL;
	close (fd[1]);
	exit(0);
}
