#include "minishell.h"

void    execute_red(t_list *cmds, t_list *red, t_env **menv)
{
    if (!red)
    {
        if(fork()==0)
            run_cmd(menv, ((t_cmd *)cmds->content)->args);
        else
            wait(0);
        return;
    }
    if (((t_redir *)red->content)->type == TOK_RINPUT)
    {
        int fd;
        int backup;

        fd = open(((t_redir *)red->content)->filepath, O_RDONLY, 0755);
        backup = dup(0);
        dup2(fd, 0);
        execute_red(cmds,red->next, menv);
        dup2(backup, 0);
        close(fd);
    }
    else if(((t_redir *)red->content)->type == TOK_DRINPUT)
    {
        int fd[2];
        int backup;

        pipe(fd);
        backup = dup(0);
        ft_putstr_fd(((t_redir *)red->content)->filepath,fd[1]);
        dup2(fd[0], 0);
        execute_red(cmds,red->next, menv);
        dup2(backup, 0);
        close(fd[0]);
        close(fd[1]);
    }
    else if(((t_redir *)red->content)->type == TOK_ROUTPUT)
    {
        int fd;
        int backup;

        fd = open(((t_redir *)red->content)->filepath, O_WRONLY | O_CREAT | O_TRUNC, 0755);
        backup = dup(1);
        dup2(fd, 1);
        execute_red(cmds,red->next, menv);
        dup2(backup, 1);
        close(fd);
    }
    else if(((t_redir *)red->content)->type == TOK_DROUTPUT)
    {
        int fd;
        int backup;

        fd = open(((t_redir *)red->content)->filepath, O_WRONLY | O_CREAT | O_APPEND, 0755);
        backup = dup(1);
        dup2(fd, 1);
        execute_red(cmds,red->next, menv);
        dup2(backup, 1);
        close(fd);
    }

}