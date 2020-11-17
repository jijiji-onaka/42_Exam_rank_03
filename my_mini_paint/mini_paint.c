/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_paint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 15:54:30 by tjinichi          #+#    #+#             */
/*   Updated: 2020/11/17 16:17:09 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_paint.h"

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
	return (output_rectangle(fp, zone, zone_info));
}
