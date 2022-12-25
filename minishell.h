/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shbi <shbi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 01:50:42 by shbi              #+#    #+#             */
/*   Updated: 2022/12/25 19:52:00 by shbi             ###   ########.fr       */
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

int status;

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

t_env	*env_node(char *key, char *value);
void	env_add_end(t_env **lst, t_env *new);
char	*get_key(char *env);
char	*get_value(char *env);
void	fill_env(t_env **menv, char **env);
void	create_if_no_env(t_env **menv);
void	print_env(t_env *menv);
char	*find_value_with_key(t_env *menv, char *key);
t_env	*find_key_node(t_env *menv, char *key);

// builting commands
void	b_echo(char **arg, int fd);
int		is_option(char *op);

void	b_cd(t_env **menv, char *path);
void	cd_home(t_env **menv);
void	new_pwd_and_oldpwd(t_env **menv);
void	add_oldpwd_to_env(t_env **menv, t_env *pwd);
void	add_pwd_to_env(t_env **menv);

int		is_builted(char **args);
void	exec_builted(t_env **menv, char **args);

void	b_export(t_env **menv, char **args);
int		cmp_key(char *s1, char *s2);
int		env_size(t_env *lst);
char	**key_env_to_array(t_env *menv);
char	**env_to_array(t_env *menv);
int		get_index_min(char **array, int i);
char	**sorted_array(char **array);
t_env	*print_sorted_env(t_env *menv);
int		check_export_args(char *arg);

void	b_unset(t_env **menv, char **args);
t_env	*remove_node(t_env *menv, char *key);

void	b_env(t_env *menv, char **args);

void	b_pwd(t_env	*menv);

// error case
void	error_msg(const char *error_msg);

// multi pipes
void	multi_pipes(t_env **menv, t_list *cmds, int cmd_nbr);
void	first_cmd(int fd[2], int prev_in, int prev_out);
void	between_cmd(int fd[2], int prev_in, int prev_out);
void	last_cmd(int fd[2], int prev_in, int prev_out);
void	run_cmd(t_env **menv, char **cmd);

// check cmds if valid
int		check_access_path(char *path);
void	free_path_env(char **path_env);
int		cmd_is_path(char *cmd);
char	*check_cmd_access(t_env *menv, char *cmd);

// execution
void	execution(t_env **menv, t_list *cmds, int cmd_nbr);
char	*update_cmd_path(t_env *menv, char **cmds);

// minishell loop
void	minishell_loop(t_env **menv);



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

t_token	*new_token(char *value, e_token type);
t_list	*new_node(void *content);
void	print_list(t_list *tokens);
void	print_list_tokens(t_list *tokens);
//lexer 

char	*new_word(char *str , int *i);
char	*ft_dquote(char *str,int *i);
char	*ft_squote(char *str,int *i);
t_list	*get_tokens(char *str);
t_list	*expand_dollar(t_env *menv,t_list *tokens);

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


#endif