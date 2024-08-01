/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khmessah <khmessah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 17:53:12 by mmondad           #+#    #+#             */
/*   Updated: 2024/08/01 23:52:23 by khmessah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_global_var(t_info *info)
{
	g_general = malloc(sizeof (t_general));
	if (!g_general)
		free_list(info, 1);
	g_general->g_env = NULL;
	g_general->exit_status = 0;
}

void	init_info(t_variable *env, t_info *info)
{
	info->env = env;
	info->count = 0;
	info->lst_size = 0;
	info->head_f = NULL;
	info->quotes = 0;
	info->i = 0;
	info->list = NULL;
	info->plist = NULL;
}

void	ft_readline(t_info *info)
{
	info->line = readline ("minishell0-0$ ");
	if (info->line)
		add_history(info->line);
	if (!info->line)
	{
		info->tmp_line = NULL;
		free_all(info);
		ft_putstr("exit\n", 1);
		exit(g_general->exit_status);
	}
}

void	count_heredoc(t_list *list)
{
	int	count;

	count = 0;
	while (list)
	{
		if (list->type == HEREDOC)
			count++;
		list = list->next;
	}
	if (count > 16)
	{
		ft_putstr("minishell: maximum here-document count exceeded\n", 2);
		exit(2);
	}
}

int	parsing(t_info *info)
{
	ft_readline(info);
	info->tmp_line = info->line;
	info->heredoc_f = 0;
	info->line = expand(info, 1, 0);
	info->quotes = 0;
	check_quotes(info->line, info);
	info->quotes_tmp = info->quotes;
	info->flag = 0;
	ft_split(info);
	count_heredoc(info->list);
	expand_tild(info);
	if (!stx_errors(*info))
		create_plist(info);
	else
	{
		g_general->exit_status = 2;
		return (1);
	}
	return (0);
}
