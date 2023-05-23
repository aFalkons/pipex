/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afalconi <afalconi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 19:33:52 by afalconi          #+#    #+#             */
/*   Updated: 2023/05/10 20:23:58 by afalconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void	list_insert(t_cmd **first, char *data, char **env, t_pipex *pip)
{
	t_cmd	*new;
	int		i;
	int		j;

	j = -1;
	i = -1;
	new = (t_cmd *) malloc(sizeof(t_cmd));
	if (new == NULL)
	{
		free(new);
	}
	new->cmd = ft_split(data, ' ');
	makepath(&new->path, env, new->cmd[0]);
	new->next = NULL;
	ft_lstadd_backv2(first, new);
}

void	ft_lstadd_backv2(t_cmd **lst, t_cmd *new)
{
	t_cmd	*last;

	if (!lst || !new)
		return ;
	if (!(*lst))
		(*lst) = new;
	else
	{
		last = ft_lstlastv2 (*lst);
		last->next = new;
	}
}

t_cmd	*ft_lstlastv2(t_cmd *lst)
{
	if (!lst)
		return (lst);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	bigif(int flag, int **fd, int j, int i)
{
	if (flag == 0)
	{
		if (fd[j][1] != fd[0][1])
		{
			close(fd[j][0]);
			close(fd[j][1]);
		}
	}
	else if (flag == 1)
	{
		if (fd[j][1] != fd[i][1] && fd[i - 1][0] != fd[j][0])
		{
			close(fd[j][0]);
			close(fd[j][1]);
		}
	}
}
