/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khmessah <khmessah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 13:01:38 by khmessah          #+#    #+#             */
/*   Updated: 2024/08/01 00:28:32 by khmessah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>

# define SYNTAX_ERROR "minishell: syntaxerror near unexpected token `"
# define UNKNOWN 0
# define WORD 1
# define PIPE 2
# define HEREDOC 3
# define A_RED 4
# define I_RED 5
# define O_RED 6

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

typedef struct s_variable
{
	char	*nom;
	char	*valeur;
	char	*env_join;
	int		flag_print;
	int		n;
	char	**env_exec;
	int		flag_ega;
}	t_variable;

typedef struct s_plist
{
	char			**parts;
	char			**reds;
	int				*types;
	int				index;
	struct s_plist	*next;
}	t_plist;

typedef struct s_list
{
	char			*txt;
	int				type;
	struct s_list	*next;
}	t_list;

typedef struct s_heapnode
{
	void				*data;
	struct s_heapnode	*next;
}	t_heapnode;

typedef struct s_pwd
{
	char	*pwd;
	char	*oldpwd;
	char	*shlvl;
	char	*user;
}	t_pwd;

typedef struct s_path
{
	char	**var_path;
}	t_path;

typedef struct s_file
{
	char			*file_name;
	struct s_file	*next;
}	t_file;

typedef struct s_info
{
	int			pipe;
	char		*line;
	t_list		*list;
	t_plist		*plist;
	t_heapnode	*head_h;
	t_variable	*env;
	t_pwd		*var;
	t_path		*path;
	t_file		*head_f;
	int			flag1;
	int			flag0;
	int			fd0;
	int			fd1;
	int			i;
	int			j;
	int			reds_l;
	int			parts_l;
	char		*tmp_line;
	int			count;
	int			quotes;
	int			flag;
	int			lst_size;
	int			heredoc_f;
	char		*file;
	int			token_type;
	int			quotes_tmp;
}	t_info;

typedef struct s_general
{
	int			exit_status;
	int			flag;
	char		*ptr;
	t_variable	*g_env;
	t_info		*info;
	int			fd0;
	int			fd1;
	int			red;
	int			error_red;
}	t_general;

extern t_general	*g_general;

typedef struct s_split
{
	int		i;
	int		j;
	int		len;
	char	tmp;
}	t_split;

		/*   length   */
void		len_f(char *s1, t_split *data, t_info *info);
int			ft_strlen(char *str);
int			until_d(char *str, t_info *info);
void		set_val(char c, t_info *info);
void		p_len(t_list *lst, t_info *info);
int			count_words(char *str);
int			line_lenght(t_info *info, int flag);
int			buffer_lenght(char *buffer);
int			until_del(char *str);
int			dollar_len(char *str);

		/*   validators   */
int			check_escape(char c);
int			check_token(char c);
int			check_sep(char c);
void		check_quotes(char *line, t_info *info);
int			alpha_n(char c);
int			check_pipe(char *str);
char		*handel_pipes_in_parse(t_info *info, char *buffer);
int			check_reds(char c);

		/*   print   */
void		ft_putstr(char *str, int fd);
void		print_error(char *msg, int ext, int fd);
void		stx_message(char *token, char c);

		/*   linked_list   */
void		add_back(t_list **list, t_list *new_node);
void		new_node(char *str, int type, t_info *info);
void		create_plist(t_info *info);
void		add_back_p(t_plist **list, t_plist *new_node);
t_plist		*new_pnode(t_info *info);
void		add_back_h(t_heapnode **list, t_heapnode *new_node);
void		new_fnode(void *data, t_info *info);

		/*    expand		*/
char		*expand(t_info *info, int i, int singl_q);
char		*exit_status(char *str, t_info *info);
char		*b_dollar(t_info *info);
char		*after_d(t_info *info);
char		*append_dollar(t_info *info);
int			dollar(char c, t_info *info);
char		*fake_var(t_info *info, int i);
int			heredoc_ex_l(char *str, int *flag, t_info *info);
char		*mini_expand(char *str, t_info *info, int *expanded);
void		expand_tild(t_info *info);

			/*		signals			*/
void		signals(void);
void		handel(int sig);

char		*ft_strjoin(char *s1, char *s2, t_info *info);
void		ft_split(t_info *info);
int			ft_strcmp(const char *s1, const char *s2);
void		free_list(t_info	*info, int i);
char		*ft_strdup(t_info *info, t_split data);
int			stx_errors(t_info info);
void		init_info(t_variable *env, t_info *info);
int			parsing(t_info *info);
char		*ft_itoa(int n, t_info *info);
char		*ft_substr(char *s, int start, int len, t_info *info);
void		handle_child_signal(int sig);

/*unset*/
void		unistial_vlag(int *flag, int size);
int			check_size_new_array(char **av, t_variable *env, int *flag);
t_variable	update_env(t_variable env_line);
int			position_var_unset(t_variable *env, char **av, int *ptr);

/*export*/
int			position_egal(char *av);
int			valid_argument(char *av);
int			size_array_env(t_variable *env);
int			ft_strncmp1(char *s1, char *s2, int n);
int			check_dans_env(char *av, t_variable *env, int n);
int			checck_plus(char *str);
int			calcul_count(char **av, t_variable *env, int count, int i);
void		remplir_encien_env(t_variable *env, t_variable *new_env, int *ptr);
void		remplir_new_env(t_variable *new_env, int *ptr, int *count);
char		*ft_substr1(char const *s, int start, int len);
void		variable_sans_egal(char *av, t_variable *new_env, int *ptr);
void		variable_new_env(t_variable *new_env,
				char *av, int *ptr, int *ptr1);
void		edit_varible(t_variable *new_env, char *av, int *ptr, int *flags);
void		variable_deja_env(t_variable *new_env, char *av);
void		export_variable(char *av, t_variable *new_env, int n, int *ptr);
void		write_command_not_found(t_info *info);
void		write_permission_denied(t_info *info);
int			number_plus(char *av);
void		ft_print_string(char *str, int fd);
char		*ft_strchr(const char *s, int c);
int			split_path(t_variable *env, t_path *path);
char		*join_commande_path1(t_path *path, char *av);
void		handle_child_signal(int sig);
void		child_process_herdoc(t_info *info, char *buffer, int *ptr);
void		echo_dernier_word(t_variable	*pwd_env,
				t_variable *my_env, t_info *info, int count);
void		parent_process_herdoc(t_info *info, int *ptr, char *file);
void		open_input_redirection(t_info *info, int *ptr);
void		cherch_input(t_info *info);
void		open_o_red(t_info *info, int *ptr);
void		output_append(t_info *info, int *ptr);
void		cherch_output(t_info *info);
void		check_commande(t_info *info, char **env);
void		dup_multiple_commande(t_info *info, int *fd, int *prev_fd);
void		parent_child_multiple(int *prev_fd, int *fd);
void		child_process(t_info *info, char **en,
				int *prev_fd, t_variable *env);
void		dup_input_1(t_info *info, int *fd);
void		child_ps_1_commande(t_info *info,
				char **en, t_variable *env, int *fd);
void		init_global_var(t_info *info);
t_variable	*check_variable(t_variable *my_env, char *variable, t_pwd *var);
void		command_builtin_redirection(t_info	*info,
				t_variable *my_env, int *ptr);
int			number_commande(t_info info);
t_variable	*env_reserver(t_variable *env_nu);
int			check_home(t_variable *my_env, t_variable *path, t_pwd *var);
int			check_pwd(t_variable *my_env,
				t_variable *pwd_env, char *pwd, t_pwd *var);
int			check_oldpwd(t_variable *pwd_env,
				t_variable *my_env, char *oldpwd, t_pwd *var);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
t_variable	*pwd_env1(t_variable *my_env, t_info *info,
				t_variable *pwd_env, char *str);
t_variable	*set_env(t_variable *my_env, char **penv);
void		sort_env(t_variable *my_env);
char		**return_env(t_variable *my_env);
void		remplir_oldpwd(t_variable *my_env, t_pwd *var);
void		remplir_shlvl(t_variable *my_env, t_pwd *var);
void		run_buil_red(t_variable *my_env, t_info *info, int *ptr);
void		free_env(t_variable *env);
int			position_egal(char *av);
int			check_is_builtin(t_info *info);
t_variable	*exec_builtin(t_variable *my_env, t_info	*info, int s);
void		print_env1(t_variable *my_env, int flag);
t_variable	*builtin_export(char **av, t_variable *env);
t_variable	*builtin_unset(char **av, t_variable *env);	
void		builtin_exit(int ac, char **av);
void		builtin_echo(int ac, char **av);
int			builtin_cd(int ac, char **av, t_variable *my_env, t_pwd *var);
t_variable	*builtin_env(char **env);
void		execution_cmd(t_variable *env, t_info *info, char **en);
int			split_path(t_variable *env, t_path *path);
t_variable	split_env(char *env_line);
void		free_d(char **str);
char		*ft_strdup1(char *s);
int			ft_atoi1(const char *str);
int			ft_strcmp1(char *s1, char *s2);
char		*ft_strchr1(const char *s, int c);
char		*ft_strncpy1(char *dest, char *src, unsigned int n);
char		*ft_strjoin1(char *s1, char *s2);
char		**ft_split1(char *s, char c);
char		*join_commande_path1(t_path *path, char *av);
char		*nom_file(void);
int			print_file_info(char *path);
void		cherch_input(t_info *info);
void		cherch_output(t_info *info);
void		check_execve(t_info *info, char **env, char *s);
void		add_back_file(t_file **list, t_file *new_node);
void		new_node_file(void *data, t_info *info, t_file **head);
void		open_herdoc_in_main(t_info	info, t_file **head);
void		open_herdoc(t_info *info, int *ptr, t_file **head);
void		free_vars(t_variable *list);
void		*allocate(t_info *info, size_t size);
char		*ft_itoa1(int n, t_info *info);
void		builtin_pwd(char *var);
void		fonct_sort_env( t_variable *my_env);
void		ft_stat(t_info *info, char *s);
void		edit_varible1(t_variable *new_env, int *ptrn, char *av, int *ptrk);
void		augment_level_shlvl(t_variable *env, t_info *info);
void		save_pwd(t_info *info);
void		ft_perror(void);
void		free_all(t_info *info);
int			check_reds(char c);
void		b_dollar_copy(t_info *info, char *str);
void		else_export(t_variable *new_env, char *av, int *n, int *k);
void		edit_varible2(t_variable *new_env, int k, int n);
void		run_builtin_final(t_variable **my_env, t_info *info, int count);
int			check_size_max(char *str);
int			skip_sero(char *str);
int			error_cd(char **av);
int			skip_sero(char *str);
void		check_error_max_exit(char **av);
int			ft_isdigit1(char *c);
void		exit_error(char **av);
#endif
