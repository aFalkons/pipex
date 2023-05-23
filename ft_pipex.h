/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afalconi <afalconi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 01:38:31 by afalconi          #+#    #+#             */
/*   Updated: 2023/05/23 09:37:07 by afalconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PIPEX_H
# define FT_PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include "gnl/get_next_line.h"

typedef struct s_cmd {
	char			**cmd;
	char			*path;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_pipex {
	char	*file1;
	char	*file2;
	t_cmd	*start;
	int		stdincpy;
	int		stdoutcpy;
	int		ncmd;
	int		pac;
	char	*finish;
}	t_pipex;

void		setup(t_pipex *pip, char **av, t_cmd **tcmd, char **env);
char		**ft_split(char *s, char c);
static int	count_words(const char *str, char c);
static char	*word_dup(const char *str, int start, int finish);
void		makepath(char **path, char **env, char *cmd);
char		*ft_strjoin(char *s1, char *s2);
size_t		ft_strlcpy(char *dst, char *src, size_t dstsize);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		makepath2(char *pathtemp, char **paths, char *j);
void		child(t_pipex *pip, char **env, t_cmd *tcmd);
void		freecose(t_pipex *pip, t_cmd *t_cmd);
void		ft_lstnew(t_cmd *tcmd, char **content);
void		ft_lstadd_front(t_cmd *lst, t_cmd *new);
void		list_insert(t_cmd **first, char *data, char **env, t_pipex *pip);
void		ft_lstadd_backv2(t_cmd **lst, t_cmd *new);
t_cmd		*ft_lstlastv2(t_cmd *lst);
void		closefree(t_pipex *pip, int **fd);
void		fdwrite(int i, int **fd, int fdfra, t_pipex *pip);
void		fdread(int i, int **fd, int fdfra, t_pipex *pip);
void		setfd(int	**fd, t_pipex *pip);
void		bigif(int flag, int **fd, int j, int i);
void		heredoc(t_pipex *pip, char **av);
void		ckcmd(t_pipex *pip, char **av, char **env, int pos);
void		sp2(char *s, int *i, int *j, char **split);

#endif
