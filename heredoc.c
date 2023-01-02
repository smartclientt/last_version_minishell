#include "minishell.h"

// int ft_heredoc(char *file)
// {
//     int fd;
//     char *line;

//     fd = open("/tmp/tmpfile", O_RDWR | O_CREAT);
//     while (1)
//     {
//         line =  readline(1);
//         if (ft_strncmp(line, file, ft_strlen(line) + 1));
//             break;
//         write(fd, line, ft_strlen(line) + 1);
//     }
//     return (fd);
// }
void	exit_herdoc(int sig)
{
	(void)sig;
	exit(1);
}

char	*ft_heredocs(char *file)
{
	t_string	*input;
	char		*buffer;
	char		*result;

	input = new_string("");
	// signal(SIGINT, SIG_IGN);
	if (fork() == 0)
	{
		while (1)
		{
			// signal(SIGINT, exit_herdoc);
			// signal(SIGQUIT, SIG_IGN);
			buffer = readline("> ");
			if (!buffer || ft_strncmp(buffer, file, ft_strlen(file) + 1) == 0)
				break ;
			input = str_concate(input, buffer);
			input = str_append(input, '\n');
			free(buffer);
		}
		wait(0);
	}
	free(file);
	result = ((t_string *)input)->content;
	return (result);
}

// void    check_heredoc(t_list *cmds)
// {
//     t_list *tmp;
//     t_list  *red;

//     tmp = cmds;
//     while (tmp)
//     {
//         red = ((t_cmd *)tmp->content)->redirs;
//         while(((t_redir *)red->content))
//         {
//             if(((t_redir *)red->content)->type == TOK_DRINPUT)
//             {
//                 ft_heredocs((const char *)((t_redir *)red->content)->filepath);
//                 break;
//             }
//             red = red->next;
//         }
//         tmp = tmp->next;
//     }
// }