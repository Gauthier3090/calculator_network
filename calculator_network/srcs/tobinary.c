#include "../includes/header.h"

void	to_binary(int nbr)
{
	int tab[8] = {0,0,0,0,0,0,0,0};
	int	i;

	if (nbr < 0)
		return ;
	i = 0;
	while (nbr > 0)
	{
		tab[i] = nbr % 2;
		nbr = nbr / 2;
		i++;
	}
	i = 8;
	while (i > 0)
		printf("%d", tab[--i]);
	printf("\n");
}

int		main(int argc, char **argv)
{
	int nbr;
	if (argc == 2)
	{
		nbr = atoi(argv[1]);
		if (nbr < 0 || nbr > 255)
			printf("Please type a correct number\n");
		else if (nbr == 0)
			printf("00000000\n");
		else
			to_binary(nbr);
	}
	else
		printf("Error numbers of arguments\n");
	return (0);
}