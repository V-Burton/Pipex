/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vburton <vburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:38:22 by victor            #+#    #+#             */
/*   Updated: 2023/03/17 16:10:00 by vburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_childs(t_pipex *pipex, int input);
void	ft_last_child(t_pipex *pipex);

void	ft_execute(t_pipex *pipex)
{
	int	input;

	input = open(pipex->input, O_RDONLY);
	if (input == -1)
		perror(pipex->input);
	dup2(input, STDIN_FILENO);
	close (input);
	ft_childs(pipex, input);
	ft_last_child(pipex);
}

void	ft_childs(t_pipex *pipex, int input)
{
	int	fd[2];
	int	pid;

	pipe(fd);
	pid = -1;
	if (input != -1)
	{
		pid = fork();
		if (pid == -1)
			perror(" :fork failed\n");
	}
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close (fd[1]);
		execve(pipex->cmd[0].array[0], pipex->cmd[0].array, pipex->envp);
		perror(pipex->cmd[0].array[0]);
		ft_free(pipex->cmd);
		exit(1);
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
}

void	ft_last_child(t_pipex *pipex)
{
	int	pid;
	int	output;

	output = open(pipex->output, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (output == -1)
	{
		perror(pipex->output);
		return ;
	}
	dup2(output, STDOUT_FILENO);
	close(output);
	pid = fork();
	if (pid == -1)
		perror(" :fork failed\n");
	if (pid == 0)
	{
		execve(pipex->cmd[1].array[0], pipex->cmd[1].array, pipex->envp);
		perror(pipex->cmd[1].array[0]);
		ft_free(pipex->cmd);
		exit(1);
	}
}
