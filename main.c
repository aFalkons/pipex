/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afalconi <afalconi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 01:26:58 by afalconi          #+#    #+#             */
/*   Updated: 2023/05/22 08:35:56 by afalconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void	makepath2(char *pathtemp, char **paths, char *j)
{
	int	i;

	i = -1;
	while (paths[++i])
	{
		pathtemp = ft_strdup(paths[i]);
		free(paths[i]);
		paths[i] = ft_strjoin(pathtemp, j);
		free(pathtemp);
	}
}

void	makepath(char **path, char **env, char *cmd)
{
	int		i;
	char	*env2;
	char	**paths;
	char	*pathtmp;

	i = -1;
	while (env[++i])
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			break ;
	paths = ft_split(&env[i][5], ':');
	makepath2(pathtmp, paths, "/");
	makepath2(pathtmp, paths, cmd);
	i = -1;
	while (paths[++i])
	{
		if (access(paths[i], X_OK) == 0)
			*path = ft_strdup(paths[i]);
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	if (access(cmd, X_OK) == 0)
		*path = ft_strdup(cmd);
}

void	setup(t_pipex *pip, char **av, t_cmd **tcmd, char **env)
{
	int		i;
	char	**tmpcmd;

	i = 1;
	if (ft_strncmp("here_doc", av[1], 8) == 0)
	{
		heredoc(pip, av);
		i++;
	}
	else
	{
		pip->file1 = ft_strdup(av[1]);
	}
	ckcmd(pip, av, env, i);
	pip->file2 = ft_strdup(av[pip->pac - 1]);
	while (av[++i] && i < (pip->pac - 1))
	{
		list_insert(tcmd, av[i], env, pip);
		pip->ncmd ++;
	}
}

void	freecose(t_pipex *pip, t_cmd *tcmd)
{
	int	i;

	i = -1;
	if (pip->ncmd != 0)
	{
		while ((tcmd)->next != NULL)
		{
			while (tcmd->cmd[++i])
				free(tcmd->cmd[i]);
			free((tcmd)->cmd);
			free((tcmd)->path);
			free((tcmd));
			tcmd = (tcmd)->next;
			i = -1;
		}
		while ((tcmd)->cmd[++i])
			free((tcmd)->cmd[i]);
		free((tcmd)->cmd);
		free((tcmd)->path);
	}
	free((tcmd));
	free(pip->file1);
	free(pip->file2);
	unlink("here_doc");
}

int	main(int ac, char **av, char **env)
{
	int		i;
	int		x;
	t_pipex	pip;
	t_cmd	*tcmd;

	if (ac < 5 || (ac < 6 && ft_strncmp("here_doc",
				av[1], ft_strlen ("here_doc")) == 0))
	{
		write(1, "Bad input\n", ft_strlen("bad input\n"));
		exit(1);
	}
	i = -1;
	pip.file1 = 0;
	tcmd = NULL;
	pip.ncmd = 0;
	pip.pac = ac;
	setup(&pip, av, &tcmd, env);
	pip.start = tcmd;
	child(&pip, env, tcmd);
	tcmd = pip.start;
	freecose(&pip, tcmd);
	return (0);
}
