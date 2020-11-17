/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 15:03:37 by tjinichi          #+#    #+#             */
/*   Updated: 2020/11/17 16:23:27 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_paint.h"

void			free_and_close(char **ptr, FILE *fp)
{
	free(*ptr);
	*ptr = NULL;
	fclose(fp);
}

int				error_return(char *str)
{
	size_t i;

	i = 0;
	while (str[i])
		i++;
	write(1, str, i);
	return (ERROR);
}

int				zone_info_OutOfRange(t_zone *zone_info)
{
	return ((zone_info->width > 0 && zone_info->height <= 300) || \
		(zone_info->height > 0 && zone_info->height <= 300));
}

int				rec_OutOfRange(t_rec rec)
{
	return (rec.radius > 0 && (rec.type == 'c' || rec.type == 'C'));
}
