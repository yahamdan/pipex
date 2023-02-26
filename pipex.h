/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahamdan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:40:24 by yahamdan          #+#    #+#             */
/*   Updated: 2023/02/25 18:49:47 by yahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

void	ft_exit(int nb);
void	ft_free(char **av);
size_t	ft_strlen(char *s);
void	heredoc(char **av);
int		ws(char *s, char c);
char	*ft_strdup(char *s1);
char	*get_next_line(int fd);
char	**get_path(char **env);
void	free_me(char **p, int j);
char	*ft_strchr(char *s, int c);
char	**ft_split(char *s, char c);
char	*ft_strjoin(char *s1, char *s2);
char	*cmd_join(char **path, char **p);
int		check_here_doc(int ac, char **av);
void	splited(char *s, char **p, char c);
char	*tf_strjoin(char *dst, char *buff);
char	*get_p(char **av, char **env, int j);
void	*ft_calloc(size_t count, size_t size);
int		ft_strncmp(char *s1, char *s2, size_t n);
char	*ft_substr(char *s, unsigned int start, size_t len);

#endif