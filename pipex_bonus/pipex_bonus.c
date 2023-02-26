/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahamdan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:34:05 by yahamdan          #+#    #+#             */
/*   Updated: 2023/02/26 14:51:35 by yahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	heredoc(char **av)
{
	char	*line;
	int		f;

	f = open(av[1], O_CREAT | O_RDWR | O_TRUNC, 0777);
	while (1)
	{
		write(1, "here_doc> ", ft_strlen("here_doc> "));
		line = get_next_line(0);
		if (!line)
			break ;
		if (ft_strncmp(line, av[2], ft_strlen(av[2])) == 0)
		{
			free(line);
			break ;
		}
		else
			write(f, line, ft_strlen(line));
		free(line);
	}
}

void	first_child(char **av, int *fd, char **env)
{
	int		f;
	char	*cmd;
	int		id;
	int		i;

	i = 0;
	id = fork();
	if (id == 0)
	{
		if (ft_strncmp("here_doc", av[1], ft_strlen(av[1])) == 0)
			i = 1;
		f = open(av[1], O_RDWR, 0644);
		if (f < 0)
			ft_exit(2);
		cmd = get_p(av, env, 2 + i);
		dup2(fd[1], 1);
		dup2(f, 0);
		close(fd[0]);
		close(f);
		execve(cmd, ft_split(av[2 + i], ' '), env);
		ft_exit(3);
	}
	close(fd[1]);
}

void	other_childs(char **av, char **env, int i, int *fd)
{
	char	*cmd;
	int		id;

	id = fork();
	if (id == 0)
	{
		cmd = get_p(av, env, i);
		dup2(fd[0], 0);
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		execve(cmd, ft_split(av[i], ' '), env);
		ft_exit(3);
	}
	close(fd[1]);
}

void	last_child(char **av, int *fd, char **env, int i)
{
	int		f;
	char	*cmd;
	int		id;

	f = open(av[i + 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (f < 0)
		ft_exit(0);
	id = fork();
	if (id == 0)
	{
		cmd = get_p(av, env, i);
		dup2(f, 1);
		dup2(fd[0], 0);
		close(fd[1]);
		close(f);
		execve(cmd, ft_split(av[i], ' '), env);
		ft_exit(3);
	}
	unlink("here_doc");
	close(fd[0]);
	close(fd[1]);
	while (wait(NULL) != -1)
		continue ;
}

int	main(int ac, char **av, char **env)
{
	int		i;
	int		c;
	int		fd[2];
	int		fd1[2];

	i = 1;
	c = check_here_doc(ac, av);
	pipe(fd);
	while (++i < (ac - 1))
	{
		if (i == 2 + c)
		{
			fd1[0] = fd[0];
			first_child(av, fd, env);
		}
		else if (i == ac - 2)
			last_child(av, fd, env, i);
		else if (i != 2 && i != (ac - 2))
		{
			pipe(fd);
			fd1[1] = fd[1];
			other_childs(av, env, i, fd1);
			fd1[0] = fd[0];
		}
	}
}
