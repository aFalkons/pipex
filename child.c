/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afalconi <afalconi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 16:03:51 by afalconi          #+#    #+#             */
/*   Updated: 2023/05/10 18:35:13 by afalconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

// void	child(t_pipex *pip, char **env,t_cmd *tcmd)
// {
// 	int	**fd;
// 	int fdfra;
// 	int	pid;
// 	int	i;
// 	int	j;

// 	i = -1;
// 	fd = malloc(8 * pip->ncmd - 1);
// 	while(++i < pip->ncmd)
// 	{
// 		fd[i] = malloc(sizeof(int) * 2);
// 		if (pipe(fd[i]) == -1)
// 			printf("pipe error");
// 	}
// 	fdfra = open(pip->file1, O_RDONLY);
// 	i = 0;
// 	j = -1;
// 	while(i < pip->ncmd)
// 	{
// 		pid = fork();
// 		if (pid == 0)
// 		{
// 			if (i == 0)
// 			{
// 				dup2(fdfra, STDIN_FILENO);
// 				while (++j < pip->ncmd)
// 				{
// 					if (fd[j][1] != fd[0][1])
// 					{
// 						close(fd[j][0]);
// 						close(fd[j][1]);
// 					}
// 				}
// 				close(fd[0][0]);
// 				j = -1;
// 			}
// 			else
// 			{
// 				while (++j < pip->ncmd)
// 				{
// 					if (fd[j][1] != fd[i][1] && fd[i - 1][0] != fd[j][0])
// 					{
// 						close(fd[j][0]);
// 						close(fd[j][1]);
// 					}
// 				}
// 				close(fd[i][0]);
// 				close(fd[i - 1][1]);
// 				j = -1;
// 				dup2(fd[i - 1][0], STDIN_FILENO);
// 			}
// 			if (i == pip->ncmd - 1)
// 			{
// 				close(fd[i][1]);
// 				close(fdfra);
// 				fdfra = open(pip->file2, O_RDWR, O_TRUNC, O_CREAT);
// 				dup2(fdfra, STDOUT_FILENO);
// 			}
// 			else
// 			{
// 				dup2(fd[i][1], STDOUT_FILENO);
// 			}
// 			execve(tcmd->path, tcmd->cmd, env);
// 		}
// 		i++;
// 		tcmd = tcmd->next;
// 	}
// 	j = -1;
// 	while (++j < pip->ncmd)
// 	{
// 		close(fd[j][0]);
// 		close(fd[j][1]);
// 	}
// 	j = -1;
// 	while(++j < pip->ncmd)
// 		free(fd[j]);
// 	free(fd);
// 	dup2(pip->stdoutcpy, STDOUT_FILENO);
// 	dup2(pip->stdincpy, STDIN_FILENO);
// }

void	child(t_pipex *pip, char **env, t_cmd *tcmd)
{
	int	**fd;
	int	fdfra;
	int	pid;
	int	i;
	int	j;

	i = 0;
	j = -1;
	fd = malloc(8 * pip->ncmd - 1);
	setfd(fd, pip);
	fdfra = open(pip->file1, O_RDONLY);
	while (i < pip->ncmd)
	{
		pid = fork();
		if (pid == 0)
		{
			fdread(i, fd, fdfra, pip);
			fdwrite(i, fd, fdfra, pip);
			execve(tcmd->path, tcmd->cmd, env);
		}
		i++;
		tcmd = tcmd->next;
	}
	closefree(pip, fd);
}

void	setfd(int	**fd, t_pipex *pip)
{
	int	i;

	i = -1;
	while (++i < pip->ncmd)
	{
		fd[i] = malloc(sizeof(int) * 2);
		if (pipe(fd[i]) == -1)
			printf("pipe error");
	}
}

void	fdread(int i, int **fd, int fdfra, t_pipex *pip)
{
	int	j;

	j = -1;
	if (i == 0)
	{
		dup2(fdfra, STDIN_FILENO);
		while (++j < pip->ncmd)
			bigif(0, fd, j, 0);
		close(fd[0][0]);
	}
	else
	{
		while (++j < pip->ncmd)
			bigif(1, fd, j, i);
		close(fd[i][0]);
		close(fd[i - 1][1]);
		dup2(fd[i - 1][0], STDIN_FILENO);
	}
}

void	fdwrite(int i, int **fd, int fdfra, t_pipex *pip)
{
	if (i == pip->ncmd - 1)
	{
		close(fd[i][1]);
		close(fdfra);
		if (ft_strncmp("here_doc", pip->file1, ft_strlen("here_doc")) == 0)
			fdfra = open(pip->file2, O_RDWR | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);
		else
			fdfra = open(pip->file2, O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
		dup2(fdfra, STDOUT_FILENO);
	}
	else
	{
		dup2(fd[i][1], STDOUT_FILENO);
	}
}

void	closefree(t_pipex *pip, int **fd)
{
	int	j;

	j = -1;
	while (++j < pip->ncmd)
	{
		close(fd[j][0]);
		close(fd[j][1]);
	}
	j = -1;
	while (++j < pip->ncmd)
		free(fd[j]);
	free(fd);
	dup2(pip->stdoutcpy, STDOUT_FILENO);
	dup2(pip->stdincpy, STDIN_FILENO);
}
