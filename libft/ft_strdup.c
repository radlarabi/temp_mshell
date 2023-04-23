/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 16:56:44 by rlarabi           #+#    #+#             */
/*   Updated: 2023/04/19 00:09:34 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*a;
	int		i;

	i = 0;
	while (s1 && s1[i])
		i++;
	a = (char *) malloc(i * sizeof(char) + 1);
	if (!a)
		return (0);
	i = -1;
	while (s1 && s1[++i])
		a[i] = s1[i];
	a[i] = '\0';
	return (a);
}