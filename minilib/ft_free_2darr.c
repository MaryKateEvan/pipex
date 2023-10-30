/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_2darr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 01:50:47 by mevangel          #+#    #+#             */
/*   Updated: 2023/10/30 01:51:06 by mevangel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilib.h"

void	ft_free_2darr(char **final)
{
	int	i;

	i = 0;
	while (final[i] != NULL)
	{
		free(final[i]);
		i++;
	}
	free(final);
}
