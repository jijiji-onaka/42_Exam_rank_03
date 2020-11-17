/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro_paint.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 01:00:41 by tjinichi          #+#    #+#             */
/*   Updated: 2020/11/17 15:50:27 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MICRO_PAINT_H
# define MICRO_PAINT_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# define INVALID 0
# define VALID 1
# define NO_ERROR 0
# define ERROR 1
# define NO_REC 0
# define FILLED_REC 1
# define EMPTY_REC 2
# define ERR_ARG "Error: argument\n"
# define ERR_FILE "Error: Operation file corrupted\n"

typedef struct	s_zone
{
	int			width;
	int			height;
	char		background_character;
}				t_zone;

typedef struct	s_rec
{
	char		type;
	double		left_corner_x;
	double		left_corner_y;
	double		width;
	double		height;
	char		character;
}				t_rec;

void			free_and_close(char **ptr, FILE *fp);
int				error_return(char *s);
int				zone_info_OutOfRange(t_zone *zone_info);
int				rec_OutOfRange(t_rec rec);
char			*parse_zone(FILE *fp, t_zone *zone_info);
int				parse_rec(FILE *fp, char **zone, t_zone *zone_info);
void			create_output(char **zone, t_rec rec, t_zone *zone_info);
int				output_rectangle(FILE *fp, char *zone, t_zone zone_info);

#endif
