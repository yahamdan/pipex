/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahamdan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 12:25:42 by yahamdan          #+#    #+#             */
/*   Updated: 2023/02/25 18:47:00 by yahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_path(char **env)
{
	int		i;
	int		b;
	char	*tmp;
	char	**path;

	i = 0;
	b = 0;
	tmp = NULL;
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
		{
			tmp = &env[i][b + 5];
			break ;
		}
		i++;
	}
	path = ft_split(tmp, ':');
	return (path);
}

char	*get_p(char **av, char **env, int j)
{
	int		i;
	char	**path;
	char	*command;
	char	**p;

	i = 0;
	p = ft_split(av[j], ' ');
	if (!p[0])
		ft_exit(1);
	path = get_path(env);
	if (!path)
		exit(1);
	if (p[0][0] == '/')
		return (p[0]);
	command = cmd_join(path, p);
	return (command);
}

char	*cmd_join(char **path, char **p)
{
	int		i;
	char	*cmd;
	char	*command;

	i = 0;
	while (path[i])
	{
		cmd = tf_strjoin(path[i], "/");
		command = tf_strjoin(cmd, p[0]);
		free(cmd);
		if (access(command, X_OK) != -1)
		{
			ft_free(path);
			ft_free(p);
			return (command);
		}
		free(command);
		i++;
	}
	write(2, p[0], ft_strlen(p[0]));
	ft_exit(1);
	return (NULL);
}

void	ft_free(char **av)
{
	int	i;

	i = 0;
	while (av[i])
		free(av[i++]);
	free(av);
}

void	ft_exit(int nb)
{
	if (nb == 0)
		write(2, "ERORR : bad arguments\n", 22);
	else if (nb == 1)
		write(2, " : command not found\n", 21);
	else if (nb == 2)
		write(2, "ERORR : open failed\n", 20);
	else if (nb == 3)
		write(2, "ERORR : execve failed\n", 21);
	exit(1);
}
