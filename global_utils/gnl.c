/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 20:07:58 by ehakam            #+#    #+#             */
/*   Updated: 2021/07/06 20:33:39 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/global_utils.h"

int	get_next_line(char **line)
{
	char	*buffer;
	int		ret;

	buffer = (char *)ft_malloc(2);
	*line = (char *)ft_malloc(1);
	*line[0] = '\0';
	ret = 1;
	while (ret)
	{
		ret = read(0, buffer, 1);
		if (ret)
		{
			if (buffer[0] == '\n' || ret == EOF)
				break ;
			*line = strjoin_c(*line, buffer[0], true);
		}
	}
	free(buffer);
	return (ret);
}
