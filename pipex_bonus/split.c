/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahamdan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:22:12 by yahamdan          #+#    #+#             */
/*   Updated: 2023/02/25 20:53:24 by yahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	ws(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			while (s[i] && s[i] != c)
				i++;
			count++;
		}
	}
	return (count);
}

void	free_me(char **p, int j)
{
	while (j >= 0)
		free(p[j--]);
	free(p);
}

void	splited(char *s, char **p, char c)
{
	int		i;
	int		j;
	int		x;

	i = 0;
	j = 0;
	while (s[i])
	{
		x = 0;
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			x = i;
			while (s[i] && s[i] != c)
				i++;
			p[j] = ft_substr(s, x, i - x);
			if (!p[j])
				return (free_me(p, j));
			j++;
		}
	}
	p[j] = NULL;
}

char	**ft_split(char *s, char c)
{
	char	**p;

	if (!s)
		return (NULL);
	p = malloc((ws((char *)s, c) + 1) * sizeof(char *));
	if (!p)
		return (NULL);
	splited((char *)s, p, c);
	return (p);
}
