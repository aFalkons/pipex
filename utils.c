/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afalconi <afalconi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 06:59:05 by afalconi          #+#    #+#             */
/*   Updated: 2023/05/22 09:51:56 by afalconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*ret;

	if (!s1 || !s2)
		return (0);
	i = 0;
	j = 0;
	ret = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!ret)
		return (0);
	while (s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		ret[i] = s2[j];
		i++;
		j++;
	}
	ret[i] = '\0';
	return (ret);
}

static int	count_words(const char *str, char c)
{
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	while (*str)
	{
		if (*str == '\'')
		{
			while (*(str++))
			{
				if (*str == '\'')
					break ;
			}
		}
		if (*str != c && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		else if (*str == c)
			trigger = 0;
		str++;
	}
	return (i);
}

static char	*word_dup(const char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

// char	**ft_split(char *s, char c)
// {
// 	int		i;
// 	int		j;
// 	int		index;
// 	char	**split;
// 	int		ck;

// 	split = malloc((count_words(s, c) + 1) * sizeof(char *));
// 	if (!s || !split)
// 		return (0);
// 	i = -1;
// 	j = 0;
// 	index = -1;
// 	while (++i <= ft_strlen(s))
// 	{
// 		if (s[i] == '\'')
// 		{
// 			index = i + 1;
// 			i++;
// 			while (s[i] != '\'')
// 			{
// 				i++;
// 				if (!s[i])
// 				{
// 					write(1, "bad input\n", ft_strlen("bad input\n"));
// 					exit(1);
// 				}
// 			}
// 			split[j++] = word_dup(s, index, i);
// 			index = -1;
// 			i++;
// 		}
// 		if (s[i] != c && index < 0)
// 			index = i;
// 		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
// 		{
// 			split[j++] = word_dup(s, index, i);
// 			index = -1;
// 		}
// 	}
// 	split[j] = 0;
// 	return (split);
// }

char	**ft_split(char *s, char c)
{
	int		i;
	int		j;
	int		index;
	char	**split;

	split = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!s || !split)
		return (0);
	i = -1;
	j = 0;
	index = -1;
	while (++i <= ft_strlen(s))
	{
		if (s[i] == '\'')
			sp2(s, &i, &j, split);
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
		{
			split[j++] = word_dup(s, index, i);
			index = -1;
		}
	}
	split[j] = 0;
	return (split);
}

void	sp2(char *s, int *i, int *j, char **split)
{
	int	index;

	index = *i + 1;
	(*i)++;
	while (s[*i] != '\'')
	{
		(*i)++;
		if (!s[*i])
		{
			write(1, "bad input\n", ft_strlen("bad input\n"));
			exit(1);
		}
	}
	split[*j] = word_dup(s, index, *i);
	(*j)++;
	(*i)++;
}
