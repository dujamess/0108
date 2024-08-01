/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khmessah <khmessah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 08:34:28 by mmondad           #+#    #+#             */
/*   Updated: 2024/08/02 00:44:31 by khmessah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	add_quotes(t_info *info, char *str, int len, int flag)
{
	int	i;
	int	quotes;

	i = 0;
	while (info->env->valeur[len])
	{
		if ((!len && !info->i && flag)
			|| (len && !check_escape(info->env->valeur[len])
				&& check_escape(info->env->valeur[len - 1]) && !info->i && flag)
			|| ((len && check_escape(info->env->valeur[len])
					&& !check_escape(info->env->valeur[len - 1])
					&& !info->i && flag)))
		{
			if (info->env->valeur[len] == '\"' || info->quotes == '\'')
				quotes = '\'';
			else
				quotes = '\"';
			set_val(quotes, info);
			str[i++] = quotes;
		}
		str[i++] = info->env->valeur[len++];
	}
	return (i);
}

char	*get_line(t_info *info, int j, int flag)
{
	int		len;
	char	*str;
	int		tmp;
	int		i;

	info->i = info->quotes;
	len = line_lenght(info, flag);
	tmp = info->quotes;
	info->quotes = 0;
	str = malloc(len + 1);
	if (!str)
		free_list(info, 1);
	new_fnode(str, info);
	info->count += j;
	len = 0;
	while (check_escape(info->env->valeur[len]) && info->quotes)
		len++;
	i = add_quotes(info, str, len, flag);
	if (info->quotes && !info->i)
		str[i++] = info->quotes;
	str[i] = '\0';
	info->quotes = tmp;
	return (str);
}

char	*cmp_f(t_info *info, int i, int flag, char *buffer)
{
	int		j;
	int		tmp;
	char	*str;

	tmp = i;
	while (info->env && info->env->nom)
	{
		j = 0;
		i = tmp;
		while (info->line[i + j] && info->line[i + j] == info->env->nom[j]
			&& alpha_n(info->env->nom[j]))
			j++;
		if (!info->env->nom[j]
			&& (!info->line[i + j] || !alpha_n(info->line[i + j])))
		{
			str = get_line(info, ++j, flag);
			return (str);
		}
		info->env++;
	}
	return (handel_pipes_in_parse(info, buffer));
}

char	*expand_var(int i, int flag, int singl_q, char *buffer)
{
	char		*str;
	t_variable	*denv;

	denv = g_general->info->env;
	if (!alpha_n(g_general->info->line[i])
		|| (g_general->info->quotes == '\'' && !singl_q))
		return (fake_var(g_general->info, i));
	str = cmp_f(g_general->info, i, flag, buffer);
	g_general->info->env = denv;
	return (str);
}

char	*expand(t_info *info, int i, int singl_q)
{
	char	*str;
	char	*part;

	str = NULL;
	while (info->line[info->count])
	{
		if (info->line[info->count] == '$')
			part = expand_var(info->count + 1, i, singl_q, str);
		else
			part = b_dollar(info);
		str = ft_strjoin(str, part, info);
	}
	return (str);
}
