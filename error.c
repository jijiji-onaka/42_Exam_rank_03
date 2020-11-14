/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 01:03:22 by tjinichi          #+#    #+#             */
/*   Updated: 2020/11/15 01:14:19 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "micro_paint.h"

void	free_and_close(char **ptr, FILE *fp)
{
	free(*ptr);
	*ptr = NULL;
	fclose(fp);
}

int		error_return(char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	write(1, s, i);
	return (ERROR);
}

int		zone_info_OutOfRange(t_zone *zone_info)
{
	return ((zone_info->width > 0 && zone_info->width <= 300) || \
		(zone_info->height > 0 && zone_info->height <= 300));
}

int		rec_OutOfRange(t_rec rec)
{
	return ((rec.height > 0 && rec.width > 0) && \
		(rec.type == 'r' || rec.type == 'R'));
}
