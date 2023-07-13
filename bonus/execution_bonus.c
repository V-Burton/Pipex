/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vburton <vburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:38:22 by victor            #+#    #+#             */
/*   Updated: 2023/03/24 17:37:22 by vburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_childs(t_pipex pipex, t_cmd *cmd_array, int input, int mid_cmd);
int		ft_last_child(t_pipex pipex, t_cmd *cmd);
void	exec_child(t_pipex pipex, int nb_cmd, t_cmd *cmd_array, int fd[2]);
void	exec_last_child(t_pipex pipex, t_cmd *cmd);

void	ft_execute(t_pipex pipex)
{
	int		i;
	int		input;
	t_cmd	*copy;

	i = 0;
	copy = pipex.cmd;
	if (pipex.here_doc != 1)
	{
		input = open(pipex.input, O_RDONLY);
		if (input == -1)
			perror(pipex.input);
		else
		{
			dup2(input, STDIN_FILENO);
			close (input);
		}
	}
	while (i < pipex.nb_cmd - 1)
	{
		ft_childs(pipex, copy, input, i);
		copy++;
		i++;
	}
	ft_last_child(pipex, copy);
}

void	ft_childs(t_pipex pipex, t_cmd *cmd_array, int input, int mid_cmd)
{
	int	fd[2];
	int	pid;

	pipe(fd);
	pid = -1;
	if (input != -1 || mid_cmd > 0)
	{
		pid = fork();
		if (pid == -1)
			perror(" :fork failed\n");
	}
	if (pid == 0 && (cmd_array->array[0] == NULL || \
					access(cmd_array->array[0], X_OK)))
	{
		ft_error(cmd_array->array[0]);
		ft_free(pipex.cmd, pipex.nb_cmd);
		exit (0);
	}
	else if (pid == 0)
		exec_child(pipex, pipex.nb_cmd, cmd_array, fd);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
}

void	exec_child(t_pipex pipex, int nb_cmd, t_cmd *cmd_array, int fd[2])
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close (fd[1]);
	execve(cmd_array->array[0], cmd_array->array, pipex.envp);
	perror(cmd_array->array[0]);
	ft_free(pipex.cmd, nb_cmd);
	exit(1);
}

int	ft_last_child(t_pipex pipex, t_cmd *cmd)
{
	int	pid;
	int	output;
	int	check;

	if (pipex.here_doc != 1)
		output = open(pipex.output, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else
		output = open(pipex.output, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (output == -1)
		return (perror(pipex.output), 0);
	check = ft_error(cmd->array[0]);
	if (check == -1)
		return (close(output), 0);
	dup2(output, STDOUT_FILENO);
	close(output);
	pid = fork();
	if (pid == -1)
		perror(" :fork failed\n");
	if (pid == 0)
		exec_last_child(pipex, cmd);
	return (0);
}

void	exec_last_child(t_pipex pipex, t_cmd *cmd)
{
	execve(cmd->array[0], cmd->array, NULL);
	perror(cmd->array[0]);
	ft_free(pipex.cmd, pipex.nb_cmd);
	exit(1);
}
