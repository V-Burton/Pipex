/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vburton <vburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:38:22 by victor            #+#    #+#             */
/*   Updated: 2023/03/24 13:22:35 by vburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_childs(t_pipex pipex, int input);
int		ft_last_child(t_pipex pipex);
int		ft_error(char *cmd);
void	exec_child(t_pipex pipex, int fd[2]);

void	ft_execute(t_pipex pipex)
{
	int	input;

	input = open(pipex.input, O_RDONLY);
	if (input == -1)
		perror(pipex.input);
	dup2(input, STDIN_FILENO);
	close (input);
	ft_childs(pipex, input);
	ft_last_child(pipex);
}

void	ft_childs(t_pipex pipex, int input)
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
	if (pid == 0 && (pipex.cmd[1].array[0] == NULL || \
					access(pipex.cmd[0].array[0], X_OK)))
	{
		ft_error(pipex.cmd[0].array[0]);
		ft_free(pipex.cmd);
		exit (0);
	}
	else if (pid == 0)
		exec_child(pipex, fd);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
}

void	exec_child(t_pipex pipex, int fd[2])
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close (fd[1]);
	execve(pipex.cmd[0].array[0], pipex.cmd[0].array, pipex.envp);
	perror(pipex.cmd[0].array[0]);
	ft_free(pipex.cmd);
	exit(1);
}

int	ft_last_child(t_pipex pipex)
{
	int	pid;
	int	output;
	int	check;

	output = open(pipex.output, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (output == -1)
		return (perror(pipex.output), 0);
	check = ft_error(pipex.cmd[1].array[0]);
	if (check == -1)
		return (close (output), 0);
	dup2(output, STDOUT_FILENO);
	close(output);
	pid = fork();
	if (pid == -1)
		perror(" :fork failed\n");
	if (pid == 0)
	{
		execve(pipex.cmd[1].array[0], pipex.cmd[1].array, pipex.envp);
		perror(pipex.cmd[1].array[0]);
		ft_free(pipex.cmd);
		exit(1);
	}
	return (0);
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
