#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

# define ERR_ARG "Error: argument\n"
# define ERR_FILE "Error: Operation file corrupted\n"

typedef struct s_zone
{
	int w;
	int h;
	char c;
}	t_zone;

typedef struct s_rec
{
	char type;
	float x;
	float y;
	float w;
	float h;
	char c;
}	t_rec ;

void	FREE(char *s, FILE *fp)
{
	free(s);
	fclose(fp);
}

int		error(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	write(1, s, i);
	return (1);
}

int		z_outofrange(t_zone *info)
{
	return ((info->w > 0 && info->w <= 300) && (info->h > 0 && info->h <= 300));
}

int 	r_outofrange(t_rec rec)
{
	return ((rec.h > 0 && rec.w > 0) && (rec.type == 'r' || rec.type == 'R'));
}

char *parse_zone(FILE *fp, t_zone *info)
{
	int rc = fscanf(fp, "%d %d %c\n", &info->w, &info->h, &info->c);
	if (rc != 3 || rc == EOF)
		return (NULL);
	if (z_outofrange(info) == 0)
		return (NULL);
	char *zone;
	if (!(zone = malloc(info->w * info->h + 1)))
		return (NULL);
	int i = 0;
	while (i < info->w * info->h)
	{
		zone[i] = info->c;
		i++;
	}
	zone[i] = '\0';
	return (zone);
}

int		ok(int x, int y, t_rec rec)
{
	if ((x < rec.x || rec.x + rec.w < x) || (y < rec.y || rec.y + rec.h < y))
		return (0);
	if (x - rec.x < 1 || rec.x + rec.w - x < 1 || y - rec.y < 1 || rec.y + rec.h - y < 1)
		return (2);
	return (1);
}


void	create_output(char **zone, t_rec rec, t_zone *info)
{
	int x, y, rc;
	y = 0;
	while (y < info->h)
	{
		x = 0;
		while (x < info->w)
		{
			rc = ok(x, y, rec);
			if ((rec.type == 'r' && rc == 2) || (rec.type == 'R' && rc))
				(*zone)[y * info->w + x] = rec.c;
			x++;
		}
		y++;
	}
}

int	parse_rec(FILE *fp, char **zone, t_zone *info)
{
	t_rec rec = {0};

	int rc;
	while ((rc = fscanf(fp, "%c %f %f %f %f %c\n", &rec.type, &rec.x, &rec.y, &rec.w, &rec.h, &rec.c)) == 6)
	{
		if (r_outofrange(rec) == 0)
			return (0);
		create_output(zone, rec, info);
	}
	if (rc != EOF)
		return (0);
	return (1);
}

void	output(char *zone, t_zone info)
{
	int i = 0;

	while (i < info.h)
	{
		write(1, zone + (i * info.w), info.w);
		write(1, "\n", 1);
		i++;
	}
}

int main(int ac, char **av)
{
	FILE *fp;
	char *zone;
	t_zone info;

	info = (t_zone){0};
	if (ac != 2)
		return (error(ERR_ARG));
	if (!(fp = fopen(av[1], "r")))
		return (error(ERR_FILE));
	if (!(zone = parse_zone(fp, &info)))
	{
		FREE(zone, fp);
		return (error(ERR_FILE));
	}
	if (!parse_rec(fp, &zone, &info))
	{
		FREE(zone, fp);
		return (error(ERR_FILE));
	}
	output(zone, info);
	FREE(zone, fp);
	return (0);
}
