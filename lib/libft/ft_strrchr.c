/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberila <mberila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:31:45 by mberila           #+#    #+#             */
/*   Updated: 2025/01/24 10:55:00 by mberila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	const char	*last_oc;
	char		last;

	last_oc = NULL;
	last = (char) c;
	while (*str != '\0')
	{
		if (*str == last)
			last_oc = str;
		str++;
	}
	if (last == '\0')
		return ((char *)str);
	return ((char *)last_oc);
}
