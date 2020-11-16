#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

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
	float r;
	char c;
}	t_rec;

int 	error(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	write(1, s, i);
	return (1);
}

void	FREE(char *s, FILE *fp)
{
	free(s);
	fclose(fp);
}

int	z_check(t_zone *info)
{
	return ((info->w > 0 && info->w <= 300) && (info->h > 0 && info->h <= 300));
}

int r_check(t_rec rec)
{
	return (rec.r > 0 && (rec.type == 'c' || rec.type == 'C'));
}

char *parse_zone(FILE *fp, t_zone *info)
{
	int rc = fscanf(fp, "%d %d %c\n", &info->w, &info->h, &info->c);
	if (rc != 3 || rc == EOF)
		return (NULL);
	if (z_check(info) == 0)
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

int		is(int x, int y, t_rec rec)
{
	double	distance;

	distance = sqrtf(powf(x - rec.x, 2.0) + powf(y - rec.y, 2.0));
	if (distance <= rec.r)
	{
		if (rec.r - distance < 1)
			return (2);
		return (1);
	}
	return (0);
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
			rc = is(x, y, rec);
			if ((rec.type == 'c' && rc == 2) || (rec.type == 'C' && rc))
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

	while ((rc = fscanf(fp, "%c %f %f %f %c\n", &rec.type, &rec.x, &rec.y, &rec.r, &rec.c)) == 5)
	{
		if (r_check(rec) == 0)
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
	if (ac != 2)
		return (error(ERR_ARG));
	FILE *fp;
	if (!(fp = fopen(av[1], "r")))
		return (error(ERR_FILE));
	char *zone;
	t_zone info;
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
