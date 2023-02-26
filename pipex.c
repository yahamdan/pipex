/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahamdan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 17:38:15 by yahamdan          #+#    #+#             */
/*   Updated: 2023/02/25 13:13:13 by yahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child(char **av, int *fd, char **env)
{
	int		f;
	char	*cmd;

	f = open(av[1], O_RDONLY);
	if (f < 0)
		ft_exit(2);
	cmd = get_p(av, env, 2);
	dup2(fd[1], 1);
	dup2(f, 0);
	close(fd[0]);
	close(f);
	execve(cmd, ft_split(av[2], ' '), env);
	ft_exit(3);
}

void	second_child(char **av, int *fd, char **env)
{
	int		f;
	char	*cmd;

	f = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (f < 0)
		ft_exit(2);
	cmd = get_p(av, env, 3);
	dup2(f, 1);
	dup2(fd[0], 0);
	close(fd[1]);
	close(f);
	execve(cmd, ft_split(av[3], ' '), env);
	ft_exit(3);
}

void	ft_close(int *fd)
{
	close(fd[1]);
	close(fd[0]);
	while (wait(NULL) != -1)
		continue ;
	exit(0);
}

int	main(int ac, char **av, char **env)
{
	int	fd[2];
	int	id;
	int	id2;

	if (ac != 5)
		ft_exit(0);
	pipe(fd);
	id = fork();
	if (id == 0)
	{
		first_child(av, fd, env);
	}
	else
	{
		id2 = fork();
		if (id2 == 0)
			second_child(av, fd, env);
		else
			ft_close(fd);
	}
}
