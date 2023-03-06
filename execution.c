/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <victor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:38:22 by victor            #+#    #+#             */
/*   Updated: 2023/03/06 19:29:22 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_childs(t_pipex *pipex);
void	ft_last_child(t_pipex *pipex);


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
		if (i == pipex->nb_cmd - 1)
			pipex->cmd++;
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
		ft_childs(pipex);
		i++;
		pipex->cmd++;
	}
	// ft_printf("path cmd = %s\n", pipex->cmd->array[0]);
	// int	j = 0;
	// while (pipex->cmd->array[j])
	// {
	// 	ft_printf("%s\n", pipex->cmd->array[j]);
	// 	j++;
	// }
	dup2(output, STDOUT_FILENO);
	close(output);
	if (i < pipex->nb_cmd)
		ft_last_child(pipex);
}

void	ft_childs(t_pipex *pipex)
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
		execve(pipex->cmd->array[0], pipex->cmd->array, pipex->envp);
		perror(pipex->cmd->array[0]);
		exit(1);
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
}

void	ft_last_child(t_pipex *pipex)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		perror(" :fork failed\n");
	if (pid == 0)
	{
		execve(pipex->cmd->array[0], pipex->cmd->array, NULL);
		perror(pipex->cmd->array[0]);
		exit(1);
	}
}