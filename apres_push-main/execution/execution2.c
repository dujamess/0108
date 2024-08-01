/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khmessah <khmessah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 19:20:40 by khmessah          #+#    #+#             */
/*   Updated: 2024/08/01 00:11:28 by khmessah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_ex(void)
{
	int	status;

	waitpid(-1, &status, 0);
	if (WIFEXITED(status))
		g_general->exit_status = WEXITSTATUS(status);
}

void	child_process_herdoc(t_info *info, char *buffer, int *ptr)
{
	info->head_f = NULL;
	info->head_h = NULL;
	signal(SIGINT, handle_child_signal);
	while (1)
	{
		buffer = readline(">");
		if (buffer == NULL)
			break ;
		new_fnode(buffer, info);
		info->count = 0;
		info->line = buffer;
		g_general->info = info;
		if (ft_strcmp1(buffer, info->plist->reds[(*ptr) + 1]) == 0
			&& ((ft_strlen(buffer))
				== ft_strlen(info->plist->reds[(*ptr) + 1])))
			break ;
		if (!info->heredoc_f)
			buffer = expand(info, 0, 1);
		buffer = ft_strjoin1(buffer, "\n");
		new_fnode(buffer, info);
		ft_print_string(buffer, info->fd0);
	}
	free_list(info, 0);
	exit(0);
}

void	parent_process_herdoc(t_info *info, int *ptr, char *file)
{
	int	i;

	i = *ptr;
	info->plist->reds[i + 1] = file;
	if (info->plist->types[i] == HEREDOC)
		get_ex();
	info->plist->types[i] = I_RED;
	close(info->fd0);
}

void	open_herdoc(t_info *info, int *ptr, t_file **head)
{
	int		i;
	int		pid;

	i = *ptr;
	info->file = NULL;
	info->file = nom_file();
	new_fnode(info->file, info);
	new_node_file(info->file, info, head);
	info->fd0 = open(info->file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	pid = fork();
	if (pid == 0)
		child_process_herdoc(info, NULL, &i);
	else
		parent_process_herdoc(info, &i, info->file);
}

void	open_input_redirection(t_info *info, int *ptr)
{
	int		i;
	char	*str;
	int		expanded;

	expanded = 0;
	i = *ptr;
	if (info->plist->reds[i + 1])
	{
		str = mini_expand(info->plist->reds[i + 1], info, &expanded);
		if (!str || (count_words(str) > 1 && expanded))
		{
			ft_putstr("ambiguous redirect\n", 2);
			exit(1);
		}
		info->plist->reds[i + 1] = str;
		if (info->fd0 != 0)
			close(info->fd0);
		info->fd0 = open(info->plist->reds[i + 1], O_RDONLY);
		if (info->fd0 == -1)
			ft_perror();
		dup2(info->fd0, STDIN_FILENO);
		close(info->fd0);
	}
}
