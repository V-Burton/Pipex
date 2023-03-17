/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vburton <vburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:37:45 by victor            #+#    #+#             */
/*   Updated: 2023/03/17 16:13:25 by vburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5)
		return (ft_printf("Wrong number of arguments.\n"));
	ft_init(&pipex, argc, argv, envp);
	ft_execute(&pipex);
	ft_free(pipex.cmd, pipex.nb_cmd);
	return (1);

}
