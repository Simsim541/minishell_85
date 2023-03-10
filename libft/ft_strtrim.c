/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simoberri <simoberri@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 10:07:18 by aaammari          #+#    #+#             */
/*   Updated: 2023/03/10 23:28:24 by simoberri        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>
#include"libft.h"

char	*ft_strtrim(char const *s1, char a, char b)
{
	int	len;
	int	x;
	char *set;

	if (!s1)
		return (0);
	len = ft_strlen(s1);
	len--;
	x = len;
	while (s1[len] && len >= 0)
	{
		if (s1[len] == a)
		{
			set = ft_strdup("\"");
			break;
		}
		else if (s1[len] == b)
		{
			set = ft_strdup("\'");
			break;
		}
		len--;
	}
	if (len >= 0)
	{
		while (s1 && ft_strchr(set, *s1))
			s1++;
		while (x && ft_strchr(set, s1[x]))
			x--;
	}
	return (ft_substr(s1, 0, x + 1));
}
