/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondad <mmondad@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-27 09:14:09 by mmondad           #+#    #+#             */
/*   Updated: 2024-06-27 09:14:09 by mmondad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	len_int(long nb)
{
	int	i;

	i = 0;
	if (nb <= 0)
	{
		i++;
		nb *= -1;
	}
	while (nb > 0)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

static char	*add_to(long nb, int len)
{
	char	*str;
	int		slen;

	slen = len - 1;
	str = malloc(len + 1);
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	if (nb < 0)
	{
		str[0] = '-';
		nb *= -1;
	}
	if (nb == 0)
	{
		str[0] = '0';
		return (str);
	}
	while (nb > 0)
	{
		str[slen] = (nb % 10) + 48;
		nb /= 10;
		slen--;
	}
	return (str);
}

char	*ft_itoa(int n, t_info *info)
{
	long	nb;
	int		len;
	char	*str;

	nb = n;
	len = len_int(nb);
	str = add_to(nb, len);
	new_fnode(str, info);
	return (str);
}
