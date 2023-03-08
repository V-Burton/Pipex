/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vburton <vburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:38:22 by victor            #+#    #+#             */
/*   Updated: 2023/03/08 18:09:08 by vburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_childs(char **cmd, char **envp, t_pipex *pipex);
void	ft_last_child(t_pipex *pipex, int i);


void	ft_execute(t_pipex *pipex)
{
	int	i;
	int	input;
	int	output;

	i = 0;
	input = open(pipex->input, O_RDONLY);
	if (input == -1)
	{
		perror(pipex->input);
		i++;
	}
	output = open(pipex->output, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (output == -1)
	{
		perror(pipex->output);
		pipex->nb_cmd--;
	}
	if (i == 0)
	{
		dup2(input, STDIN_FILENO);
		close (input);
	}		
	while (i < pipex->nb_cmd - 1)
	{		
		ft_childs(pipex->cmd[i].array, pipex->envp, pipex);
		i++;
	}
	dup2(output, STDOUT_FILENO);
	close(output);
	if (i < pipex->nb_cmd)
		ft_last_child(pipex, i);
}

void	ft_childs(char **cmd, char **envp, t_pipex *pipex)
{
	int fd[2];
	int	pid;

	pipe(fd);
	pid = fork();
	if (pid == -1)
		perror(" :fork failed\n");
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close (fd[1]);
		execve(cmd[0], cmd, envp);
		perror(cmd[0]);
		ft_free(pipex->cmd, pipex->nb_cmd);
		exit(1);
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
}

void	ft_last_child(t_pipex *pipex, int i)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		perror(" :fork failed\n");
	if (pid == 0)
	{
		execve(pipex->cmd[i].array[0], pipex->cmd[i].array, NULL);
		perror(pipex->cmd[i].array[0]);
		ft_free(pipex->cmd, pipex->nb_cmd);
		exit(1);
	}
}