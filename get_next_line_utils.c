/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 16:47:25 by acoudert          #+#    #+#             */
/*   Updated: 2020/11/21 16:22:26 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_lstnew(int fd)
{
	t_list	*curr;

	if (!(curr = (t_list*)malloc((sizeof(t_list)))))
		return (0);
	if (!(curr->str = (char*)malloc(sizeof(char) * 1)))
	{
		free(curr);
		return (0);
	}
	curr->next = 0;
	*(curr->str) = 0;
	curr->fd = fd;
	return (curr);
}

char	*ft_strchr(char *s, int c)
{
	char			*s_cpy;
	char			c_cpy;

	if (!s)
		return (0);
	s_cpy = s;
	c_cpy = (char)c;
	while (*s_cpy != c_cpy && *s_cpy)
		s_cpy++;
	return ((*s_cpy == c_cpy) ? s_cpy : 0);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i_s1;
	int		i_s2;
	char	*str;

	if (!s1 || !s2)
		return (0);
	i_s1 = 0;
	while (s1[i_s1])
		i_s1++;
	i_s2 = 0;
	while (s2[i_s2])
		i_s2++;
	if (!(str = (char*)malloc(sizeof(char) * (i_s1 + i_s2 + 1))))
		return (0);
	i_s1 = -1;
	while (s1[++i_s1])
		str[i_s1] = s1[i_s1];
	i_s2 = -1;
	while (s2[++i_s2])
		str[i_s1 + i_s2] = s2[i_s2];
	str[i_s1 + i_s2] = 0;
	return (str);
}

char	*ft_strdup(char *s)
{
	int		i;
	char	*s_dup;

	i = 0;
	while (s[i])
		i++;
	if (!(s_dup = (char*)malloc(sizeof(char) * i + 1)))
		return (0);
	i = 0;
	while (s[i])
	{
		s_dup[i] = s[i];
		i++;
	}
	s_dup[i] = 0;
	return (s_dup);
}
