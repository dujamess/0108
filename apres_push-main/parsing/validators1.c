/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validators1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khmessah <khmessah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 20:10:25 by khmessah          #+#    #+#             */
/*   Updated: 2024/07/29 15:32:41 by khmessah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_pipe(char *str)
{
	int	i;

	i = 0;
	while (check_escape(str[i]))
		i++;
	if (str[i] == '|' || !str[i] || str[i] == '$')
		return (1);
	return (0);
}

char	*handel_pipes_in_parse(t_info *info, char *buffer)
{
	int	pipe_f;
	int	lenght;

	while (alpha_n(info->line[++info->count]))
		;
	pipe_f = check_pipe(&info->line[info->count]);
	lenght = buffer_lenght(buffer);
	if ((!lenght && pipe_f) || (info->pipe && pipe_f))
		return ("true");
	return (NULL);
}

int	check_reds(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}
