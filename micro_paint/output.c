/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 01:09:09 by tjinichi          #+#    #+#             */
/*   Updated: 2020/11/15 01:15:51 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "micro_paint.h"

void		output_rectangle(char *zone, t_zone zone_info)
{
	int i;

	i = 0;
	while (i < zone_info.height)
	{
		write(1, zone + (i * zone_info.width), zone_info.width);
		write(1, "\n", 1);
		i++;
	}
}

static int	empty_or_filled_rectangle(int x, int y, t_rec rec)
{
	if ((x < rec.left_corner_x || rec.left_corner_x + rec.width < x) || \
			(y < rec.left_corner_y || rec.left_corner_y + rec.height < y))
		return (NO_REC);
	if ((x - rec.left_corner_x < 1 || rec.left_corner_x + rec.width - x < 1) || \
			(y - rec.left_corner_y < 1 || rec.left_corner_y + rec.height - y < 1))
		return (EMPTY_REC);
	return (FILLED_REC);
}

void		create_output(char **zone, t_rec rec, t_zone *zone_info)
{
	int	x;
	int	y;
	int rc;

	y = 0;
	while (y < zone_info->height)
	{
		x = 0;
		while (x < zone_info->width)
		{
			rc = empty_or_filled_rectangle(x, y, rec);
			if ((rec.type == 'r' && rc == 2) || \
					(rec.type == 'R' && rc >= 1))
				(*zone)[y * zone_info->width + x] = rec.character;
			x++;
		}
		y++;
	}
}
