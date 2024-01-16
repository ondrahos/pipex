/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:11:42 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/01/16 12:56:53 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include "./libft/libft.h"

typedef struct s_struct
{
	int		in_fd;
	int		out_fd;
	int		here_doc;
	char	**cmd_paths;
	char	**cmd_args;
	int		cmd_count;
	int		count;
}	t_struct;

void	free_arr(char **arr);
void	exit_error(int n, t_struct *pipex);
void	get_paths(t_struct *pipex, char **av, char **envp);
void	get_cmds(t_struct *pipex, char **av);
void	open_files(t_struct *pipex, int ac, char **av);

#endif
