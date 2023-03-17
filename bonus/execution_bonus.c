/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vburton <vburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:38:22 by victor            #+#    #+#             */
/*   Updated: 2023/03/17 16:13:11 by vburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_childs(t_pipex *pipex, char **cmd, char **envp, int nb_cmd, t_cmd *cmd_array);
void	ft_last_child(t_pipex *pipex, int i);


void	ft_execute(t_pipex *pipex)
{
	int	i;
	int	input;

	i = 0;
	input = open(pipex->input, O_RDONLY);
	if (input == -1)
		perror(pipex->input);
	dup2(input, STDIN_FILENO);
	close (input);	
	while (i < pipex->nb_cmd - 1)
	{
		ft_childs(pipex, pipex->cmd[i].array, pipex->envp, pipex->nb_cmd, pipex->cmd);
		i++;
	}
	if (i < pipex->nb_cmd)
		ft_last_child(pipex, i);
}

void	ft_childs(t_pipex *pipex, char **cmd, char **envp, int nb_cmd, t_cmd *cmd_array)
{
	int fd[2];
	int	pid;

	pipe(fd);
	pid = -1;
	if (access(pipex->input, X_OK) != -1)
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
		execve(cmd[0], cmd, envp);
		perror(cmd[0]);
		ft_free(cmd_array, nb_cmd);
		exit(1);
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
}

void	ft_last_child(t_pipex *pipex, int i)
{
	int	pid;
	int	output;

	output = open(pipex->output, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (output == -1)
	{
		perror(pipex->output);
		return;
	}
	dup2(output, STDOUT_FILENO);
	close(output);
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