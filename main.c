/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:09:57 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/01/16 12:55:14 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	init_pipex(t_struct *pipex)
{
	pipex->in_fd = 0;
	pipex->out_fd = 0;
	pipex->here_doc = 0;
	pipex->cmd_paths = NULL;
	pipex->cmd_args = NULL;
	pipex->cmd_count = 0;
	pipex->count = 0;
}

static void	execute_cmd(t_struct *pipex, char **envp)
{
	char	**cmd;

	cmd = ft_split(pipex->cmd_args[pipex->count], ' ');
	execve(pipex->cmd_paths[pipex->count], cmd, envp);
	free_arr(cmd);
	exit_error(5, pipex);
}

static void	execute(t_struct *pipex, char **envp)
{
	int	pfd[2];
	int	pid;

	if (pipe(pfd) < 0)
		exit_error(2, pipex);
	pid = fork();
	if (pid < 0)
		exit_error(3, pipex);
	if (pid == 0)
	{
		close(pfd[0]);
		dup2(pfd[1], STDOUT_FILENO);
		close(pfd[1]);
		execute_cmd(pipex, envp);
	}
	else
	{
		close(pfd[1]);
		dup2(pfd[0], STDIN_FILENO);
		close(pfd[0]);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_struct	pipex;

	if (ac < 5)
		exit_error(1, &pipex);
	init_pipex(&pipex);
	open_files(&pipex, ac, av);
	get_paths(&pipex, av, envp);
	get_cmds(&pipex, av);
	pipex.count = 0;
	dup2(pipex.in_fd, STDIN_FILENO);
	while (pipex.count < pipex.cmd_count - 1)
	{
		execute(&pipex, envp);
		pipex.count++;
	}
	dup2(pipex.out_fd, STDOUT_FILENO);
	unlink("here_doc");
	execute_cmd(&pipex, envp);
	exit_error(5, &pipex);
}
