/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 16:23:12 by acoudert          #+#    #+#             */
/*   Updated: 2020/11/21 16:23:22 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	32
# endif

# include <unistd.h>
# include <stdlib.h>

enum				e_ret_val
{
	READ_LINE = 1,
	END_FILE = 0,
	ERROR = -1
};

typedef struct		s_list
{
	struct s_list	*next;
	char			*str;
	int				fd;
}					t_list;

int					get_next_line(int fd, char **line);

t_list				*ft_fd_in_lst(int fd, t_list **file_lst);
int					ft_read_line(int fd, t_list *curr);
int					ft_create_line(char **line, t_list *curr);
void				ft_free_lst(int fd, t_list **file_lst);

t_list				*ft_lstnew(int fd);
char				*ft_strchr(char *s, int c);
char				*ft_strjoin(char *s1, char *s2);
char				*ft_strdup(char *s);

#endif
