/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 14:59:55 by aaammari          #+#    #+#             */
/*   Updated: 2021/11/21 20:37:18 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int c)
{
	return ((c <= '9' && c >= '0')
		|| ((c <= 'z' && c >= 'a') || (c <= 'Z' && c >= 'A')));
}