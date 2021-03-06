/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_linker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablizniu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 22:32:11 by ablizniu          #+#    #+#             */
/*   Updated: 2018/09/27 18:59:57 by ablizniu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

inline void		linker(t_room **room, char **line)
{
	char		**buff;
	t_room		*tmp;
	t_room		*link;

	tmp = (*room);
	link = (*room);
	buff = ft_strsplit(*line, '-');
	ft_strdel(line);
	checker_links(buff);
	(!(*room)) ? exit(0) : ((*room)->list_len = len_list(room));
	while (tmp && ft_strcmp(tmp->name, buff[0]) != 0)
		tmp = tmp->next;
	while (link && ft_strcmp(link->name, buff[1]) != 0)
		link = link->next;
	create_links(tmp, link, buff, room);
	delete_buff(buff, 2);
}

void			checker_links(char **buff)
{
	int			i;

	i = 0;
	while (buff[i] != NULL)
		i++;
	if (i != 2)
	{
		ft_putstr("Error, bad conditions "
				"of links or problem with room name. \n");
		exit(0);
	}
	if (ft_strcmp(buff[0], buff[1]) == 0)
	{
		ft_putstr("Error, bad links\n");
		exit(0);
	}
}

int				len_list(t_room **room)
{
	t_room		*tmp;
	int			i;

	i = 0;
	tmp = (*room);
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

t_room			*search_link(t_room **room, char *name)
{
	t_room		*tmp;

	tmp = (*room);
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

inline void		create_links(t_room *link1,
				t_room *link2, char **buff, t_room **room)
{
	int		i;
	int		j;
	int		k;

	norme_for_linker_allocation(&link1, &link2, (*room)->list_len, &i);
	j = link1->llr;
	while (link1 && link1->llr > 0)
	{
		if (link1->llr >= (*room)->list_len)
			error_quant_links();
		link1->llr--;
		i++;
	}
	link1->link[i] = *search_link(room, buff[1]);
	i = 0;
	k = link2->llr;
	while (link2 && link2->llr > 0)
	{
		if (link2->llr >= (*room)->list_len)
			error_quant_links();
		link2->llr--;
		i++;
	}
	link2->link[i] = *search_link(room, buff[0]);
	norme_for_linker(j, k, &link1, &link2);
}
