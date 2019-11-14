#include "../includes/header.h"

int		find_max_host(int CIDR)
{
	int			number_one_bit;
	int			max_bits;

	number_one_bit = 0;
	max_bits = 32;
	while (max_bits - number_one_bit != CIDR)
	{
		max_bits = 32;
		number_one_bit++;
	}
	return (number_one_bit);
}

void	find_subnet(int CIDR)
{
	int				number_one_bit;
	long int		max_hosts;
	unsigned long	mask;

	number_one_bit = find_max_host(CIDR);
	max_hosts = pow((double)2, (double)number_one_bit) - 2;
	mask = (UINT_MAX << (32 - CIDR)) & UINT_MAX;

	printf("CIDR : \\%d\n", CIDR);
	printf("Maximum hosts : %ld\n", max_hosts);
	printf("Subnet mask : %lu.%lu.%lu.%lu\n", mask >> 24, (mask >> 16) & 0xFF, (mask >> 8) & 0xFF, mask & 0xFF);
}

int main(int argc, char **argv)
{
	int CIDR;
	if (argc == 2)
	{
		CIDR = atoi(argv[1]);
		if (CIDR < 1 || CIDR > 32)
			printf("Please type a correct number\n");
		else
			find_subnet(CIDR);
	}
	else
		printf("Error number of arguments\n");
	return (0);
}