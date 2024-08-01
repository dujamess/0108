/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khmessah <khmessah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 15:11:43 by khmessah          #+#    #+#             */
/*   Updated: 2024/08/01 18:21:15 by khmessah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*s1;

	s1 = (unsigned char *)s;
	while (n > 0)
	{
		*s1++ = '\0';
		n--;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	s;

	if (size && nmemb > (4294967295) / size)
		return (0);
	s = nmemb * size;
	ptr = malloc(s);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, s);
	return (ptr);
}

void	run_multiple_commande(t_info *info, t_variable *env, int *fd, char **en)
{
	while (info->plist->next)
	{
		child_process(info, en, fd, env);
		info->plist = info->plist->next;
	}
}

void	wait_function(int fd, pid_t pid)
{
	int	status;

	close(fd);
	waitpid(pid, &status, 0);
	while (wait(NULL) != -1)
		;
	if (status == 131)
	{
		printf("Quit (core dumped)\n");
		g_general->exit_status = 131;
		return ;
	}
	if (status == 2)
		printf("\n");
	if (WIFEXITED(status))
		g_general->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_general->exit_status = 128 + WTERMSIG(status);
}

void	execution_cmd(t_variable *env, t_info *info, char **en)
{
	int		fd[2];
	pid_t	pid;

	fd[0] = -1;
	fd[1] = -1;
	info->fd0 = 0;
	info->fd1 = 1;
	run_multiple_commande(info, env, fd, en);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		child_ps_1_commande(info, en, env, fd);
	}
	else
	{
		close(fd[1]);
		wait_function(fd[0], pid);
	}
}
