/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khmessah <khmessah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 20:35:06 by khmessah          #+#    #+#             */
/*   Updated: 2024/07/29 10:14:12 by khmessah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_tild(t_info *info)
{
	t_list	*tmp_list;
	char	*tmp_env;
	char	*str;

	tmp_list = info->list;
	while (tmp_list)
	{
		if (tmp_list->type == WORD && (!ft_strcmp(tmp_list->txt, "~")
				|| ft_strcmp(tmp_list->txt, "~") == 47))
		{
			tmp_env = getenv("HOME");
			str = allocate(info, ft_strlen(tmp_env) + ft_strlen(tmp_list->txt));
			tmp_list->txt = ft_strjoin(tmp_env, tmp_list->txt + 1, info);
		}
		tmp_list = tmp_list->next;
	}
}

void	append_fake_var(t_info *info, char **line, char *str, int *i)
{
	if (str[*i] == '\'')
	{
		*line = ft_strjoin(*line, ft_substr(str, *i + 1,
					until_del(str + *i + 1), info), info);
		*i += until_del(str + *i + 1) + 1;
	}
	else
	{
		*line = ft_strjoin(*line, ft_substr(str, *i, 1, info), info);
		(*i)++;
	}
}

void	append_dollar2(char *str, int *i, t_info *info, char **line)
{
	if (str[*i] == '$' && str[*i + 1] == '$')
	{
		*line = ft_strjoin(*line, ft_substr(str, *i, 2, info), info);
		*i += 2;
	}
}

char	*mini_expand(char *str, t_info *info, int *expanded)
{
	int			i;
	char		*line;
	t_variable	*var;

	i = 0;
	line = NULL;
	if (!str[i])
		return (ft_strdup1(""));
	while (str[i])
	{
		append_dollar2(str, &i, info, &line);
		if (str[i] == '$' && alpha_n(str[i + 1]))
		{
			*expanded = 1;
			var = check_variable(info->env,
					ft_substr(str, i + 1, dollar_len(str + i + 1), info), NULL);
			if (var)
				line = ft_strjoin(line, var->valeur, info);
			i += dollar_len(str + i + 1) + 1;
		}
		else if (str[i] != '$' || (str[i] == '$' && !alpha_n(str[i + 1])))
			append_fake_var(info, &line, str, &i);
	}
	return (line);
}
