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

static int error(char *s)
{
	size_t i = 0;
	while (s[i])
		i++;
	write(1, s, i);
	return (ERROR);
}
static void free_and_close(char **ptr, FILE *fp)
{
	free(*ptr);
	*ptr = NULL;
	fclose(fp);
}

static int	zone_info_OutOfRange(t_zone *zone_info)
{
	return ((zone_info->width > 0 && zone_info->width <= 300) || \
		(zone_info->height > 0 && zone_info->height <= 300));
}

static int	rec_OutOfRange(t_rec rec)
{
	return ((rec.height > 0 && rec.width > 0) && \
		(rec.type == 'r' || rec.type == 'R'));
}

static char *parse_zone(FILE *fp, t_zone *zone_info)
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

static void	create_output(char **zone, t_rec rec, t_zone *zone_info)
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

static int	parse_rec(FILE *fp, char **zone, t_zone *zone_info)
{
	int		rc;
	t_rec	rec;

	rec = (t_rec){0};
	while ((rc = fscanf(fp, "%c %lf %lf %lf %lf %c\n", &rec.type,
			&rec.left_corner_x, &rec.left_corner_y, &rec.width, &rec.height, &rec.character)) == 6)
	{
		if (rec_OutOfRange(rec) == INVALID)
			return (INVALID);
		create_output(zone, rec, zone_info);
	}
	if (rc != EOF)
		return (INVALID);
	return (VALID);
}

void	output_rectangle(char *zone, t_zone zone_info)
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

int main(int argc, char *argv[])
{
	FILE		*fp;
	char		*zone;
	t_zone		zone_info;

	zone_info = (t_zone){0};
	if (argc != 2)
		return (error(ERR_ARG));
	if (!(fp = fopen(argv[1], "r")))
		return (error(ERR_FILE));
	if (!(zone = parse_zone(fp, &zone_info)))
	{
		free_and_close(&zone, fp);
		return (error(ERR_FILE));
	}
	if (!parse_rec(fp, &zone, &zone_info))
	{
		free_and_close(&zone, fp);
		return (error(ERR_FILE));
	}
	output_rectangle(zone, zone_info);
	free_and_close(&zone, fp);
	return (NO_ERROR);
}
