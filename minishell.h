/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelousse <yelousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 01:50:42 by shbi              #+#    #+#             */
/*   Updated: 2023/01/02 05:30:17 by yelousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./libft/libft.h"
# include "./ft_printf/ft_printf.h"



// tools
int		ft_strcmp(char *s1, char *s2);
char	*ft_free(char **s);

// envirnment functions
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}			t_env;

typedef struct s_glob
{
	int	exit_status;
	int g_expand_dq;
}				t_glob;

t_glob		v_glob;
// parssssssssssiiiiiiiiiiing
typedef struct s_vector
{
	char **content;
	size_t size;
}   t_vector;

typedef struct s_string
{
	char *content;
	size_t size;
}   t_string;

typedef enum
{
	TOK_START,
	TOK_EOL,
	TOK_WORD,
	TOK_ROUTPUT,
	TOK_DROUTPUT,
	TOK_RINPUT,
	TOK_DRINPUT,
	TOK_SINQTE,
	TOK_DQUOTE,
	TOK_PIPE,
}   e_token;

typedef struct s_token
{
	char *value; // string_t
	e_token type;
}   t_token;

typedef struct s_redir
{
	e_token type;
	char *filepath; // string_t
}   t_redir;

typedef struct s_cmd
{
	char **args; // t_vector->content
	int fdin;
	int fdout;
	t_list *redirs;
}   t_cmd;

typedef struct s_tools
{
	int	prev_in;
	int	prev_out;
	int	cmd_nbr;
	int	id[100000];
	int	fd[2];
}	t_tools;

t_env	*env_node(char *key, char *value);
void	env_add_end(t_env **lst, t_env *new);
char	*get_key(char *env);
char	*get_value(char *env);
void	fill_env(t_env **menv, char **env);
void	create_if_no_env(t_env **menv);
void	print_env(t_env *menv);
char	*find_value_with_key(t_env *menv, char *key);
t_env	*find_key_node(t_env *menv, char *key);
char	*ft_heredocs(char *file);
int		execute_red(t_list *cmds, t_list *red, t_env **menv);

// builting commands
int		b_echo(char **arg, int fd);
int		is_option(char *op);

int		b_cd(t_env **menv, char *path);
int		cd_home(t_env **menv);
int		cd_oldpwd(t_env **menv);
void	new_pwd_and_oldpwd(t_env **menv);
void	add_oldpwd_to_env(t_env **menv, t_env *pwd);
void	add_pwd_to_env(t_env **menv);

int		is_builted(char **args);
int		exec_builted(t_env **menv, char **args);

int		b_export(t_env **menv, char **args);
void	new_env_value(t_env **menv, char *key, char *new_value);
int		cmp_key(char *s1, char *s2);
int		env_size(t_env *lst);
char	**key_env_to_array(t_env *menv);
char	**env_to_array(t_env *menv);
int		get_index_min(char **array, int i);
char	**sorted_array(char **array);
t_env	*print_sorted_env(t_env *menv);
int		check_export_args(char *arg);

int		b_unset(t_env **menv, char **args);
t_env	*remove_node(t_env *menv, char *key);

int		b_env(t_env *menv, char **args);

int		b_pwd(t_env	*menv);

void	b_exit(char **args, t_env *menv);
int		nbr_of_args(char **args);
int		is_nbr(char *arg);

// error case
void	error_msg(const char *error_msg);

// free functions
void	free_env(t_env *menv);
void	free_array_2d(char **str);
void	free_cmds(t_list *cmds);
void	free_redir(t_list *redir);

// multi pipes
void	multi_pipes(t_env **menv, t_list *cmds, int cmd_nbr);
void	first_cmd(int fd[2], int prev_in, int prev_out);
void	between_cmd(int fd[2], int prev_in, int prev_out);
void	last_cmd(int fd[2], int prev_in, int prev_out);
int		run_cmd(t_env **menv, char **cmd);
void	pipe_logic(t_env **menv, t_list *tmp, t_tools *tools, int i);
int		exec_no_builted(t_env **menv, char **cmd);
void	init_tools_variables(t_tools *tools, int cmd_nbr);
void	wait_exit_status(t_tools *tools);

// check cmds if valid
int		check_access_path(char *path);
void	free_path_env(char **path_env);
int		cmd_is_path(char *cmd);
char	*check_cmd_access(t_env *menv, char *cmd);

// execution
void	execution(t_env **menv, t_list *cmds, int cmd_nbr);
char	*update_cmd_path(t_env *menv, char **cmds);

void	execute_redirections(t_list *redir, int *fdin, int *fdout);
void	one_red_input(t_list *cmds, t_list *red, t_env **menv);
void	double_red_input(t_list *cmds, t_list *red, t_env **menv);
void	one_red_output(t_list *cmds, t_list *red, t_env **menv);
void	double_red_output(t_list *cmds, t_list *red, t_env **menv);
// minishell loop
void	minishell_loop(t_env **menv);

// signals
void	signal_handler(int sig);

t_token	*new_token(char *value, e_token type);
t_list	*new_node(void *content);
void	print_list(t_list *tokens);
void	print_list_tokens(t_list *tokens);
//lexer 

char	*new_word(char *str, int *i);
char	*ft_dquote(char *str,int *i);
char	*ft_squote(char *str,int *i);
// t_list	*expand_path(t_env *menv,t_list *tokens);
t_string *expand_path(t_env *menv,t_string *dst);
t_string *expand_path_dq(t_env *menv,t_string *dst);
t_list	*expand_exit_status(t_list *tokens);
t_list	*ft_lst_del_first(t_list *tokens);
int find_dollar(char *str);
t_list  *get_tokens(char *str , t_env *menv);
//grammar
int		check_grammar(t_list *tokens);

//vector

t_vector *new_vector(const char *str);
t_vector *vec_append(t_vector *vec, const char *str);
void free_vec(t_vector **vec);

// string

t_string *new_string(const char *str);
t_string *str_concate(t_string *dst, const char *str);
t_string *str_append(t_string *dst, char c);
void free_string(t_string **str);

// some function
t_list  *get_cmds(t_list *tokens);
t_redir *new_red(char *path, e_token type);
t_cmd   *new_cmd(char **args, t_list *redirs);

//expand_status
int find_dollar_status(char *str);
t_string    *add_expand(t_string *dst);
t_string    *check_expand_status(t_string *dst);

#endif