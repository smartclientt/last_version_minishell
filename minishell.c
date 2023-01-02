/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shbi <shbi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 01:50:40 by shbi              #+#    #+#             */
/*   Updated: 2023/01/02 05:18:45 by shbi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_env	*menv;

	if (ac > 1 && av[0])
	{
		write(2, "minishell: too many arguments\n", 30);
		return (1);
	}
	fill_env(&menv, env);
	minishell_loop(&menv);
	free_env(menv);
	return (0);
}

t_list	*ft_lst_del_first(t_list *tokens)
{
	t_list	*tmp;
	t_list	*del;

	tmp = tokens;
	if (((t_token *)tmp->content)->type == TOK_START)
	{
		del = tmp;
		tmp = tmp->next;
		free(del->content);
		free(del);
	}
	return (tmp);
}

// int main(int ac, char **av, char **env)
// {
//     char *cmd = "\"e\"\"c\"h\'o\' hey";
//     t_list *tokens;
//     t_list  *cmds;
// 	t_env	*menv;
// 	(void)ac;
// 	(void)av;

//     menv = NULL;
//     tokens = NULL;
// 	v_glob = (t_glob){0};
//     // if (ac > 1 && av[0])
// 	// {
// 	// 	write(2, "minishell: too many arguments\n", 30);
// 	// 	return (1);
// 	// }
// 	fill_env(&menv, env);
//     //add_history(cmd);
//     //print_env(menv);
//     tokens = get_tokens(cmd);
// 	if (!tokens || !check_grammar(tokens))
// 	{
// 		//lst_del(&token_lst, token_del);
// 		return (1);
// 	}
//     // print_list_tokens(tokens);
// 	tokens = ft_lst_del_first(tokens);
//     // tokens = expand_path(menv,tokens);
// 	tokens = expand_exit_status(tokens);
//     // print_list_tokens(tokens);
//     cmds = get_cmds(tokens);
//     // print_list(cmds);
// 	printf("-----------------------------------------------\n");
//     execution(&menv, cmds, ft_lstsize(cmds));
// 	return(v_glob.exit_status);
// }

// int main(int ac, char **av, char **env)
// {
// 	(void)ac;
// 	(void)av;
// 	t_env *menv;
// 	// char **str;

// 	// str = malloc(sizeof(char *) * 6);
// 	// str[0] = "../";
// 	// str[1] = "~";
// 	// str[2] = "";
// 	// str[3] = "";
// 	// str[4] = "";
// 	// str[5] = NULL;
// 	char **cmd1;
// 	cmd1 = malloc(sizeof(char *) * 3);
// 	cmd1[0] = "export";
// 	cmd1[1] = "saad=holly";
// 	cmd1[2] = NULL;

// 	char **cmd2;
// 	cmd2 = malloc(sizeof(char *) * 3);
// 	cmd2[0] = "cd";
// 	cmd2[1] = "dasdasdadasdadas";
// 	cmd2[2] = NULL;

// 	char **cmd3;
// 	cmd3 = malloc(sizeof(char *) * 3);
// 	cmd3[0] = "wc";
// 	cmd3[1] = NULL;
// 	cmd3[2] = NULL;

// 	char **cmd4;
// 	cmd4 = malloc(sizeof(char *) * 3);
// 	cmd4[0] = "export";
// 	cmd4[1] = "";
// 	cmd4[2] = NULL;

// 	size_t cmds_n = 4;
// 	char ***cmds = malloc(sizeof(char **) * (cmds_n + 1));
// 	cmds[0] = cmd1;
// 	cmds[1] = cmd2;
// 	cmds[2] = cmd3;
// 	cmds[3] = cmd4;
// 	cmds[4] = NULL;

// 	fill_env(&menv, env);
// 	// printf("%p\n", &menv->key);
// 	// b_export(&menv, NULL);
// 	printf("----------------------------------\n");
// 	// minishell_loop(&menv);
// 	// execution(&menv, cmds, 1);
// 	// b_export(&menv, cmd1);
// 	// b_pwd(menv);
// 	b_cd(&menv, cmd2[1]);
// 	// b_pwd(menv);
// 	// b_export(&menv, NULL);
// 	// b_pwd(menv);
// 	// b_unset(&menv, cmd2);
// 	// system("leaks minishell");
// 	// printf("**********************************\n");
// 	// execution(&menv, cmds, 3);
// 	// b_export(&menv, NULL);
// 	printf("----------------------------------\n");
// 	// execution(&menv, cmds + 1, 1);
// 	// execution(&menv, cmds + 2, 2);
// 	// execution(&menv, cmds + 3, 1);;
// 	// printf("----------------------------------\n");
// 	// b_export(&menv, NULL);
// 	// free_env(menv);
// 	system("leaks minishell");
// 	return (0);
// }
