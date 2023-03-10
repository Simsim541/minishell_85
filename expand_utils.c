/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simoberri <simoberri@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 15:00:09 by aaammari          #+#    #+#             */
/*   Updated: 2023/03/10 01:23:34 by simoberri        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_d(char *str, char *cmdline, int *i, int status)
{
	if (str[*i] == '$')
		return (check_dollar(str, i, status, cmdline));
	return (0);
}

void	fillcmd_and_incj(char *cmdline, int *j, int *l, int *i)
{
	if (*l == -1)
		cmdline[(*j)++] = '$';
	else if (*l == -2)
	{
		(*i)++;
		return ;
	}	
	else
		*j += *l;
}

/*int	check_digit(char *str, char *cmdline)
{
	int	i;

	i = 1;
	if (ft_isdigit(str[0]))
	{
		while (str[i] && str[i] != ' ' && str[i] != '$')
		{
			cmdline[i - 1] = str[i];
			i++;
		}
	}
	return (i);
}*/
