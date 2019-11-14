#include "../includes/header.h"

static	unsigned short	find_cidr(char *mask)
{
	unsigned short	CIDR;
	int				tab_bytes[4];
	int				i;

	CIDR = 0;
	i = 0;
	sscanf(mask, "%d.%d.%d.%d", &tab_bytes[0], &tab_bytes[1], &tab_bytes[2], &tab_bytes[3]);
	while (i < 4)
	{
		if (tab_bytes[i] == 0)
			CIDR += 0;
		else if (tab_bytes[i] == 128)
			CIDR += 1;
		else if (tab_bytes[i] == 192)
			CIDR += 2;
		else if (tab_bytes[i] == 224)
			CIDR += 3;
		else if (tab_bytes[i] == 240)
			CIDR += 4;
		else if (tab_bytes[i] == 248)
			CIDR += 5;
		else if (tab_bytes[i] == 252)
			CIDR += 6;
		else if (tab_bytes[i] == 254)
			CIDR += 7;
		else if (tab_bytes[i] == 255)
			CIDR += 8;
		else
		{
			CIDR = -1;
			break;
		}
		i++;
	}
	return (CIDR);
}

int main(int argc, char **argv)
{
	unsigned short 	CIDR;

	if (argc == 2)
	{
		CIDR = find_cidr(argv[1]);
		if (CIDR < 1 || CIDR > 32)
			printf("Subnet mask incorrect\n");
		else
			printf("CIDR : \\%d\n", CIDR);
	}
	else
		printf("Error number of arguments\n");
	return (0);
}