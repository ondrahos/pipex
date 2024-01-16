/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 12:41:12 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/01/16 12:55:18 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	get_path(t_struct *pipex, char *av, char **envp)
{
	char	**paths;
	int		i;
	char	**cmd;
	char	*path;
	char	*slashed;

	i = 0;
	cmd = ft_split(av, ' ');
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		slashed = ft_strjoin(paths[i], "/");
		path = ft_strjoin(slashed, cmd[0]);
		free(slashed);
		if (access(path, F_OK) == 0)
			return (pipex->cmd_paths[pipex->count++] = ft_strdup(path),
				free(path), free_arr(paths), free_arr(cmd));
		free(path);
		i++;
	}
	free_arr(cmd);
	free_arr(paths);
}

void	get_paths(t_struct *pipex, char **av, char **envp)
{
	int	i;

	i = 0;
	pipex->cmd_paths = malloc(sizeof(char *) * (pipex->cmd_count + 1));
	if (!pipex->cmd_paths)
		return ;
	if (pipex->here_doc == 1)
	{
		while (i < pipex->cmd_count)
		{
			get_path(pipex, av[3 + i], envp);
			i++;
		}
	}
	else
	{
		while (i < pipex->cmd_count)
		{
			get_path(pipex, av[2 + i], envp);
			i++;
		}
	}
	pipex->cmd_paths[i] = NULL;
}

void	get_cmds(t_struct *pipex, char **av)
{
	int	i;

	i = 0;
	pipex->cmd_args = malloc(sizeof(char *) * (pipex->cmd_count + 1));
	if (!pipex->cmd_args)
		return ;
	if (pipex->here_doc == 1)
	{
		while (i < pipex->cmd_count)
		{
			pipex->cmd_args[i] = ft_strdup(av[3 + i]);
			i++;
		}
	}
	else
	{
		while (i < pipex->cmd_count)
		{
			pipex->cmd_args[i] = ft_strdup(av[2 + i]);
			i++;
		}
	}
	pipex->cmd_args[i] = NULL;
}
