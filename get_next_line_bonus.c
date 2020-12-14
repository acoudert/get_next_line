/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 17:05:26 by acoudert          #+#    #+#             */
/*   Updated: 2020/11/21 17:05:29 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_list		*ft_fd_in_lst(int fd, t_list **file_lst)
{
	t_list		*curr;

	if (*file_lst == 0)
		if (!(*file_lst = ft_lstnew(fd)))
			return (0);
	curr = *file_lst;
	while (curr)
	{
		if (curr->fd == fd)
			return (curr);
		else if (curr->next == 0)
			if (!(curr->next = ft_lstnew(fd)))
				return (0);
		curr = curr->next;
	}
	return (0);
}

int			ft_read_line(int fd, t_list *curr)
{
	int		bytes;
	char	*buffer;
	char	*str_to_free;

	if (!(buffer = (char*)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (ERROR);
	while (ft_strchr(curr->str, '\n') == 0)
	{
		if ((bytes = read(fd, buffer, BUFFER_SIZE)) == ERROR)
		{
			free(buffer);
			return (ERROR);
		}
		buffer[bytes] = 0;
		str_to_free = curr->str;
		if (!(curr->str = ft_strjoin(curr->str, buffer)))
			return (ERROR);
		free(str_to_free);
		if (bytes < BUFFER_SIZE)
			break ;
	}
	free(buffer);
	return (1);
}

int			ft_create_line(char **line, t_list *curr)
{
	int		i;
	char	*buffer;
	int		ret_val;

	i = 0;
	while (curr->str[i] && curr->str[i] != '\n')
		i++;
	ret_val = (curr->str[i] == '\n') ? READ_LINE : END_FILE;
	if (!(*line = (char*)malloc(sizeof(char) * (i + 1))))
		return (ERROR);
	buffer = curr->str;
	curr->str = (curr->str[i] == '\n') ? curr->str + i + 1 : curr->str + i;
	if (!(curr->str = ft_strdup(curr->str)))
		return (ERROR);
	(*line)[i] = 0;
	while (--i >= 0)
		(*line)[i] = buffer[i];
	free(buffer);
	return (ret_val);
}

void		ft_free_lst(int fd, t_list **file_lst)
{
	t_list		*curr;
	t_list		*next;

	curr = *file_lst;
	if (!curr)
		return ;
	if (curr->fd == fd)
	{
		*file_lst = (*file_lst)->next;
		(curr->str) ? free(curr->str) : 0;
		free(curr);
		return ;
	}
	while (curr && curr->next)
	{
		next = curr->next->next;
		if (curr->next->fd == fd)
		{
			(curr->next->str) ? free(curr->next->str) : 0;
			free(curr->next);
			curr->next = next;
		}
		curr = curr->next;
	}
}

int			get_next_line(int fd, char **line)
{
	static t_list		*file_lst = 0;
	t_list				*curr;
	int					ret_val;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (ERROR);
	if (!(curr = ft_fd_in_lst(fd, &file_lst)))
	{
		ft_free_lst(fd, &file_lst);
		return (ERROR);
	}
	if (ft_read_line(fd, curr) == ERROR)
	{
		ft_free_lst(fd, &file_lst);
		return (ERROR);
	}
	ret_val = ft_create_line(line, curr);
	if (ret_val == ERROR || ret_val == END_FILE)
		ft_free_lst(fd, &file_lst);
	return (ret_val);
}
