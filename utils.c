/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:55:35 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/01/16 12:55:09 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_error(int n, t_struct *pipex)
{
	if (n == 1)
	{
		perror("Error: Invalid number of arguments.\n");
		exit(EXIT_FAILURE);
	}
	else if (n == 2)
		perror("Error: Pipe has failed to open.\n");
	else if (n == 3)
		perror("Error: Forking has failed.\n");
	else if (n == 4)
		perror("Error: Opening of a filed has failed.\n");
	else if (n == 5)
		perror("Error: Command not found.\n");
	free_arr(pipex->cmd_args);
	free_arr(pipex->cmd_paths);
	close(pipex->in_fd);
	close(pipex->out_fd);
	unlink("here_doc");
	exit(EXIT_FAILURE);
}

void	free_arr(char **arr)
{
	int	i;

	if (arr == NULL)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

static void	read_heredoc(char *limiter, t_struct *pipex)
{
	int		fd;
	char	*line;

	fd = open("here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd < 0)
		exit_error(4, pipex);
	line = NULL;
	while (1)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (line == NULL || ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
			break ;
		write(fd, line, ft_strlen(line));
		free(line);
	}
	if (line != NULL)
		free(line);
	close(fd);
}

void	open_files(t_struct *pipex, int ac, char **av)
{
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		if (ac < 6)
			exit_error(1, pipex);
		pipex->here_doc = 1;
		read_heredoc(av[2], pipex);
		pipex->in_fd = open("here_doc", O_RDONLY, 0777);
		pipex->out_fd = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (pipex->in_fd < 0 || pipex->out_fd < 0)
			exit_error(4, pipex);
		pipex->cmd_count = ac - 4;
	}
	else
	{
		pipex->in_fd = open(av[1], O_RDONLY, 0777);
		pipex->out_fd = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (pipex->in_fd < 0 || pipex->out_fd < 0)
			exit_error(4, pipex);
		pipex->cmd_count = ac - 3;
	}
}
