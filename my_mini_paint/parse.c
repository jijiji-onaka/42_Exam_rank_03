/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 15:38:13 by tjinichi          #+#    #+#             */
/*   Updated: 2020/11/17 16:24:13 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_paint.h"

int				parse_rec(FILE *fp, char **zone, t_zone *zone_info)
{
	t_rec	rec;
	int		rc;

	rec = (t_rec){0};
	while ((rc = fscanf(fp, "%c %lf %lf %lf %c\n", &rec.type,
			&rec.center_x, &rec.center_y, &rec.radius, \
			&rec.character)) == REC_INFOMATION_SIZE)
	{
		if (rec_OutOfRange(rec) == INVALID)
			return (INVALID);
		create_output(zone, rec, zone_info);
	}
	if (rc != EOF)
		return (INVALID);
	return (VALID);
}

char			*parse_zone(FILE *fp, t_zone *zone_info)
{
	int		rc;
	char	*zone;
	int		i;

	rc = fscanf(fp, "%d %d %c\n", &zone_info->width, \
		&zone_info->height, &zone_info->background_character);
	if (rc != 3 || rc == EOF)
		return (NULL);
	if (zone_info_OutOfRange(zone_info) == INVALID)
		return (NULL);
	if (!(zone = malloc(zone_info->width * zone_info->height + 1)))
		return (NULL);
	i = 0;
	while (i < zone_info->width * zone_info->height)
	{
		zone[i] = zone_info->background_character;
		i++;
	}
	zone[i] = '\0';
	return (zone);
}
