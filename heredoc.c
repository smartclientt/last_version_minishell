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

char	*ft_heredocs(char *file)
{
	t_string	    *input;
	char		*buffer;
	char *result;
	// int			    pipefd[2];

	input = new_string("");
	while (1)
	{
		buffer = readline("> ");
		if (!buffer || ft_strncmp(buffer, file, ft_strlen(file) + 1) == 0)
			break ;
        input = str_concate(input, buffer);
		input = str_append(input, '\n');
		free(buffer);
	}
	// if (pipe(pipefd))
	// {
	// 	perror("minishell");
	// 	exit(1);
	// }
	// write(1, ((t_string *)input)->content, input->size);
	// dup2(pipefd[0], v_glob.g_in);
	// close(pipefd[0]);
	// close(pipefd[1]);
	// free_string(&input);
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