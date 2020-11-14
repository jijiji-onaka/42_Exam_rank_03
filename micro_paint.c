/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro_paint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 01:02:18 by tjinichi          #+#    #+#             */
/*   Updated: 2020/11/15 01:13:57 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "micro_paint.h"

int	main(int argc, char *argv[])
{
	FILE		*fp;
	char		*zone;
	t_zone		zone_info;

	zone_info = (t_zone){0};
	if (argc != 2)
		return (error_return(ERR_ARG));
	if (!(fp = fopen(argv[1], "r")))
		return (error_return(ERR_FILE));
	if (!(zone = parse_zone(fp, &zone_info)))
	{
		free_and_close(&zone, fp);
		return (error_return(ERR_FILE));
	}
	if (!parse_rec(fp, &zone, &zone_info))
	{
		free_and_close(&zone, fp);
		return (error_return(ERR_FILE));
	}
	output_rectangle(zone, zone_info);
	free_and_close(&zone, fp);
	return (NO_ERROR);
}
