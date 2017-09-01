/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoini.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbogar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 16:14:28 by sbogar            #+#    #+#             */
/*   Updated: 2017/06/07 17:51:23 by sbogar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** This function returns a string which is the result of appending str2 to str1,
** with the option to free either, neither, or both of the given strings
**
**	0 == free nothing
**	1 == free str1
**	2 == free str2
**	3 == free str1 and str2
*/

char		*ft_strjoini(char *str1, char *str2, int to_free)
{
	char	*res;
	size_t	i;
	size_t	j;
	size_t	res_size;

	i = 0;
	j = 0;
	res_size = ft_strlen(str1) + ft_strlen(str2);
	res = (char*)malloc(sizeof(char) * (res_size + 1));
	ft_bzero(res, res_size + 1);
	res[res_size + 1] = 0;
	while (str1[i])
	{
		res[i] = str1[i];
		i++;
	}
	while (str2[j])
		res[i++] = str2[j++];
	if (to_free == 1 || to_free == 3)
		free(str1);
	else if (to_free == 2 || to_free == 3)
		free(str2);
	return (res);
}
