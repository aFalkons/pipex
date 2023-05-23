/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afalconi <afalconi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:33:27 by afalconi          #+#    #+#             */
/*   Updated: 2023/05/22 08:47:22 by afalconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = ft_strlen(src);
	if (dstsize > 0)
	{
		while (src[i] != '\0' && i < (dstsize - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (j);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!n)
		return (0);
	while (s1[i] && s2[i] && i < n - 1)
	{
		if (s1[i] != s2[i])
			break ;
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	heredoc(t_pipex *pip, char **av)
{
	int		fd;
	char	*str;

	str = "flavio";
	fd = open("here_doc", O_RDWR | O_TRUNC | O_CREAT,
			S_IRUSR | S_IWUSR);
	write (STDIN_FILENO, "pipe heredoc> ", 14);
	str = get_next_line(STDIN_FILENO);
	while (ft_strncmp(av[2], str, ft_strlen(av[2])) != 0
		|| ft_strlen(av[2]) != ft_strlen(str) - 1)
	{
		write (fd, str, ft_strlen(str));
		write (STDIN_FILENO, "pipe heredoc> ", 14);
		str = get_next_line(STDIN_FILENO);
	}
	close (fd);
	pip->file1 = ft_strdup("here_doc");
}

void	ckcmd(t_pipex *pip, char **av, char **env, int pos)
{
	int		i;
	int		j;
	char	*test;
	char	**cmdapp;

	i = pos;
	while (ft_strncmp(av[++i], av[pip->pac - 1],
			ft_strlen(av[pip->pac - 1])) != 0)
	{
		j = -1;
		test = NULL;
		cmdapp = ft_split(av[i], ' ');
		makepath(&test, env, cmdapp[0]);
		while (cmdapp[++j])
			free(cmdapp[j]);
		free(cmdapp);
		if (test == NULL)
		{
			write(2, "zsh: command not found: ", 24);
			write(2, av[i], ft_strlen(av[i]));
			unlink("here_doc");
			exit(1);
		}
		free(test);
	}
}
