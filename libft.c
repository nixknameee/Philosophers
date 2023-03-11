/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngjokaj <ngjokaj@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 14:31:12 by ngjokaj           #+#    #+#             */
/*   Updated: 2023/03/10 13:47:17 by ngjokaj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
/*Funktion zum Konvertieren eines Strings in eine Ganzzahl (int) unter
Berücksichtigung von Vorzeichen und ignorierten Zeichen.*/

int	ft_atoi(const char *string)
{
	int	a;
	int	n;
	int	i;

	i = 0;
	a = 0;
	n = 0;
	while (string[i] && (string[i] == ' ' || string[i] == '\t'
			|| string[i] == '\n' || string[i] == '\r' || string[i] == '\v'
			|| string[i] == '\f'))
		i++;
	if (*string && string[i] == '-')
	{
		n = 1;
		i++;
	}
	else if (string[i] == '+')
		i++;
	while (string[i] != '\0' && ft_isdigit(string[i]))
		a = (a * 10) + (string[i++] - '0');
	if (n == 1)
		a = -a;
	return (a);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_strncmp(char const *s1, char const *s2, size_t size)
{
	unsigned char	a1;
	unsigned char	a2;

	while (size-- > 0)
	{
		a1 = *(unsigned char *)s1++;
		a2 = *(unsigned char *)s2++;
		if (a1 != a2)
			return (a1 - a2);
		if (a1 == '\0')
			return (0);
	}
	return (0);
}

/*wie Atoi nur mit einem long datentyp*/

int	ft_atol(const char *nptr)
{
	int			i;
	long		s;
	long long	res;

	res = 0;
	s = 1;
	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r'))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			s = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
		res = res * 10 + (nptr[i++] - '0');
	if ((!(nptr[i] >= '0' && nptr[i] <= '9') && nptr[i] != ' ' && nptr[i] != 0)
		|| (res * s) < -2147483648 || (res * s) > 2147483647 || s == -1)
		return (0);
	return ((int)(res * s));
}
