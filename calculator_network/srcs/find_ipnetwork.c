# include "../includes/header.h"

int        *to_binary(int nbr)
{
    int *tab;
    int    i;

    i = 0;
    if (!(tab = calloc(8, sizeof(int))))
		return (NULL);
    while (nbr > 0)
    {
        tab[i] = nbr % 2;
        nbr = nbr / 2;
        i++;
    }
    return (tab);
}

void    	ft_rev_int_tab(int *tab, int size)
{
    int i;
    int temp;

    i = 0;
    temp = 0;
    while (i < size / 2)
    {
        temp = tab[i];
        tab[i] = tab[size - i - 1];
        tab[size - i - 1] = temp;
        i++;
    }
}

int        *find_subnet(int CIDR)
{
    unsigned long    mask;
    int                *subnet;

    if (!(subnet = calloc(4, sizeof(int))))
		return (NULL);
    mask = (UINT_MAX << (32 - CIDR)) & UINT_MAX;
    subnet[0] = mask >> 24;
    subnet[1] = (mask >> 16) & 0xFF;
    subnet[2] = (mask >> 8) & 0xFF;
	subnet[3] = mask & 0xFF;
    return (subnet);
}

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

char	**calculate_ipnetwork(int *tab_binary[4], int *tab_subnet[4])
{
	int		i;
	int 	j;
	int		tab_network[4][8];
	char	**tab;

	i = -1;
	if (!(tab = (char **)calloc(4, sizeof(char *))))
		return (NULL);
	while (++i < 4)
	{
		if (!(tab[i] = calloc(8, sizeof(char))))
			return (NULL);
		j = -1;
		while (++j < 8)
		{
			if ((tab_binary[i][j] == 0 && tab_subnet[i][j] == 1) || (tab_binary[i][j] == 1 && tab_subnet[i][j] == 0))
				tab_network[i][j] = 0;
			if (tab_binary[i][j] == 1 && tab_subnet[i][j] == 1)
				tab_network[i][j] = 1;
			if (tab_binary[i][j] == 0 && tab_subnet[i][j] == 0)
				tab_network[i][j] = 0;
			tab[i][j] = tab_network[i][j] + '0';
		}
	}
	return (tab);
}

int 		convertBinaryToDecimal(long long n)
{
    int decimalNumber = 0;
	int i = 0;
	int remainder;
    while (n!=0)
    {
        remainder = n % 10;
        n /= 10;
        decimalNumber += remainder * pow(2,i);
        ++i;
    }
    return decimalNumber;
}

int			*find_broadcast(int tab_bytes[4], int *tab_subnet)
{
	int	i;
	int	*tab_broadcast;
	int result;
	int	formule_broadcast;

	i = -1;
	if (!(tab_broadcast = calloc(4, sizeof(int))))
		return (NULL);
	while (++i < 4)
	{
		if (tab_subnet[i] == 255)
			tab_broadcast[i] = tab_bytes[i];
		else if (tab_subnet[i] == 0)
			tab_broadcast[i] = 255;
		else
		{
			formule_broadcast = 256 - tab_subnet[i];
			result = formule_broadcast;
			while (1)
			{
				result += formule_broadcast;
				if (result > tab_bytes[i])
					break ;
			}
			tab_broadcast[i] = result - 1;
		}
	}
	return (tab_broadcast);
}

void    	find_ipnetwork(char *address)
{
	char			**tab;
    int    			tab_bytes[4];
    int    			*tab_binary[4];
    int    			*tab_subnet;
    int    			*tab_subnet_binary[4];
	int				tab_network[4];
	int				*tab_broadcast;
    int    			cidr;
	int				max_hosts;
    int    			i;
	long long		binary;

    i = -1;
    sscanf(address, "%d.%d.%d.%d/%d", &tab_bytes[0], &tab_bytes[1], &tab_bytes[2], &tab_bytes[3], &cidr);
    tab_subnet = find_subnet(cidr);
    while (++i < 4)
    {
        tab_binary[i] = to_binary(tab_bytes[i]);
        tab_subnet_binary[i] = to_binary(tab_subnet[i]);
        ft_rev_int_tab(tab_binary[i], 8);
        ft_rev_int_tab(tab_subnet_binary[i], 8);
    }
	tab = calculate_ipnetwork(tab_binary, tab_subnet_binary);
	i = -1;
    while (++i < 4)
    {
		binary = (long long)atoi((const char *)tab[i]);
		tab_network[i] = convertBinaryToDecimal(binary);
    }
	max_hosts = pow((double)2, (double)find_max_host(cidr)) - 2;
	tab_broadcast = find_broadcast(tab_bytes, tab_subnet);
	printf("Network Address : %d.%d.%d.%d\n", tab_network[0], tab_network[1], tab_network[2], tab_network[3]);
	printf("Broadcast Address : %d.%d.%d.%d\n", tab_broadcast[0], tab_broadcast[1], tab_broadcast[2], tab_broadcast[3]);
	printf("Usable Host IP Range : %d.%d.%d.%d - %d.%d.%d.%d\n", tab_network[0], tab_network[1], tab_network[2], tab_network[3] + 1, tab_broadcast[0], tab_broadcast[1], tab_broadcast[2], tab_broadcast[3] - 1);
	printf("Subnet Mask : %d.%d.%d.%d\n", tab_subnet[0], tab_subnet[1], tab_subnet[2], tab_subnet[3]);
	printf("CIDR Notation : /%d\n", cidr);
	printf("Total Number of Usable Hosts : %d\n", max_hosts);
}

int 		main(int argc, char **argv)
{
	if (argc == 2)
	{
		find_ipnetwork(argv[1]);
	}
	else
		printf("Error number of arguments\n");
	return (0);
}