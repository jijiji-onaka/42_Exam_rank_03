/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 15:35:29 by tjinichi          #+#    #+#             */
/*   Updated: 2020/11/17 16:16:58 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_paint.h"

int				output_rectangle(FILE *fp, char *zone, t_zone zone_info)
{
	int	i;

	i = 0;
	while (i < zone_info.height)
	{
		write(1, zone + (i * zone_info.width), zone_info.width);
		write(1, "\n", 1);
		i++;
	}
	free_and_close(&zone, fp);
	return (NO_ERROR);
}

static int		empty_or_filled_rectangle(int x, int y, t_rec rec)
{
	double	distance;

	distance = sqrtf(powf(x - rec.center_x, 2.0) + powf(y - rec.center_y, 2.0));
	if (distance <= rec.radius)
	{
		if (rec.radius - distance < 1)
			return (EMPTY_REC);
		return (FILLED_REC);
	}
	return (NO_REC);
}

void			create_output(char **zone, t_rec rec, t_zone *zone_info)
{
	int		y;
	int		x;
	int		rc;

	y = 0;
	while (y < zone_info->height)
	{
		x = 0;
		while (x < zone_info->width)
		{
			rc = empty_or_filled_rectangle(x, y, rec);
			if ((rec.type == 'c' && rc == EMPTY_REC) || \
					(rec.type == 'C' && rc))
				(*zone)[y * zone_info->width + x] = rec.character;
			x++;
		}
		y++;
	}
}
