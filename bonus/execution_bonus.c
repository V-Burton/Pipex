/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vburton <vburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:38:22 by victor            #+#    #+#             */
/*   Updated: 2023/03/22 00:45:07 by vburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_childs(char **envp, int nb_cmd, t_cmd *cmd_array, int input);
void	ft_last_child(t_pipex pipex, t_cmd *cmd);

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
		dup2(input, STDIN_FILENO);
		close (input);
	}
	while (i < pipex.nb_cmd - 1)
	{
		ft_childs(pipex.envp, pipex.nb_cmd, copy, input);
		copy++;
		i++;
	}
	ft_last_child(pipex, copy);
}

void	ft_childs(char **envp, int nb_cmd, t_cmd *cmd_array, int input)
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
		execve(cmd_array->array[0], cmd_array->array, envp);
		ft_free(cmd_array, nb_cmd);
		exit(1);
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
}

void	ft_last_child(t_pipex pipex, t_cmd *cmd)
{
	int	pid;
	int	output;

	output = open(pipex.output, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (output == -1)
	{
		perror(pipex.output);
		return ;
	}
	dup2(output, STDOUT_FILENO);
	close(output);
	pid = fork();
	if (pid == -1)
		perror(" :fork failed\n");
	if (pid == 0)
	{
		execve(cmd->array[0], cmd->array, NULL);
		dup2(2, output);
		ft_free(pipex.cmd, pipex.nb_cmd);
		exit(1);
	}
}
