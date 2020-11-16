#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

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
	double		center_x;
	double		center_y;
	double		radius;
	char		character;
}				t_rec;

int		error(char *str)
{
	int i;

	while (str[i])
		i++;
	write(1, str, i);
	return(ERROR);
}

void	free_and_close(char **ptr, FILE *fp)
{
	free(*ptr);
	*ptr = NULL;
	fclose(fp);
}

int		zone_info_OutOfRange(t_zone *zone_info)
{
	return ((zone_info->width > 0 && zone_info->height <= 300) || \
		(zone_info->height > 0 && zone_info->height <= 300));
}

int		rec_OutOfRange(t_rec rec)
{
	return (rec.radius > 0 && (rec.type == 'c' || rec.type == 'C'));
}

char	*parse_zone(FILE *fp, t_zone *zone_info)
{
	int		rc;
	char	*zone;
	int		i;

	rc = fscanf(fp, "%d %d %c\n", &zone_info->width, \
		&zone_info->height, &zone_info->background_character);
	if (rc != 3 || rc == EOF)
		return (NULL);
	if (zone_info_OutOfRange(zone_info) == 0)
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

int		is_circle(int x, int y, t_rec rec)
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

void	create_output(char **zone, t_rec rec, t_zone *zone_info)
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
			rc = is_circle(x, y, rec);
			if ((rec.type == 'c' && rc == 2) || \
					(rec.type == 'C' && rc >= 1))
				(*zone)[y * zone_info->width + x] = rec.character;
			x++;
		}
		y++;
	}
}

int		parse_rec(FILE *fp, char **zone, t_zone *zone_info)
{
	t_rec	rec;
	int		rc;

	rec = (t_rec){0};
	while ((rc = fscanf(fp, "%c %lf %lf %lf %c\n", &rec.type,
			&rec.center_x, &rec.center_y, &rec.radius, &rec.character)) == 5)
	{
		if (rec_OutOfRange(rec) == 0)
			return (0);
		create_output(zone, rec, zone_info);
	}
	if (rc != EOF)
		return (0);
	return (1);
}

void	output_rectangle(char *zone, t_zone zone_info)
{
	int	i;

	i = 0;
	while (i < zone_info.height)
	{
		write(1, zone + (i * zone_info.width), zone_info.width);
		write(1, "\n", 1);
		i++;
	}
}

int		main(int argc, char *argv[])
{
	FILE	*fp;
	char	*zone;
	t_zone	zone_info;

	zone_info = (t_zone){0};
	if (argc != 2)
		return (error("Error: argument\n"));
	if (!(fp = fopen(argv[1], "r")))
		return (error("Error: Operation file corrupted\n"));
	if (!(zone = parse_zone(fp, &zone_info)))
	{
		free_and_close(&zone, fp);
		return (error("Error: Operation file corrupted\n"));
	}
	if (!parse_rec(fp, &zone, &zone_info))
	{
		free_and_close(&zone, fp);
		return (error("Error: Operation file corrupted\n"));
	}
	output_rectangle(zone, zone_info);
	free_and_close(&zone, fp);
	return (0);
}
