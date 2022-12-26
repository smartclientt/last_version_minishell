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

void	ft_heredocs(const char *file)
{
	t_string	*input;
	const   char		*buffer;
	int			pipefd[2];

	signal(SIGQUIT, SIG_IGN);
	input = char_vec_new();
	while (1)
	{
		buffer = readline("> ");
		if (!buffer || ft_strncmp(buffer, file, ft_strlen(file) + 1) == 0)
			break ;
        str_concate(input, buffer);
		str_append(input, '\n');
		free(buffer);
	}
	if (pipe(pipefd))
	{
		perror("minishell");
		exit(EXIT_FAILURE);
	}
	write(pipefd[1], char_vec_to_str(input), input->size);
	dup2(pipefd[0], v_glob.g_in);
	close(pipefd[0]);
	close(pipefd[1]);
	char_vec_del(&input);
}