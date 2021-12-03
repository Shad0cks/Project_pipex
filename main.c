#include "header.h"

int get_fd(char *path, int mode)
{
    if (mode == 0)
    {
        if (access(path, F_OK))
        {
            write(STDERR, "pipex : infile not found !\n", 28);
            exit(EXIT_FAILURE);
        }
        return(open(path, O_RDONLY));
    }
    if (access(path , F_OK)) 
    {
        write(STDERR, "pipex : outfile not found !\n", 29);
        exit(EXIT_FAILURE);    
    }
    else 
        return (open(path, O_WRONLY));
}

char *get_path(char *cmd, char **env)
{
    int i;
    char *path_variable;
    char *temp;
    char *path;

    i = 0;
    while(env[i] && ft_strncmp(env[i], "PATH=", 5))
        i++;
    if (!env[i])
		return (cmd);
    path_variable = env[i] + 5;
    while(path_variable && ft_strchr(path_variable, ':') > -1)
    {
        temp = ft_strdup(path_variable, ft_strchr(path_variable, ':'));
        free(temp);
        path = ft_strjoin(temp, cmd);
        if (access(path, F_OK) == 0)
			return (path);
        free(path);
        path_variable += ft_strchr(path_variable, ':') + 1;
    }
    return (cmd);
}

void execmd(char **env, char *cmd)
{
    char    *path;
    char    **args_cmd;
    char *true_cmd;

    args_cmd = ft_split(cmd, ' ');
    true_cmd = ft_strjoin("/", args_cmd[0]);
    path = get_path(true_cmd, env);
    free(true_cmd);
    execve(path, args_cmd, env);
    perror("somthing went wrong ");
    exit(EXIT_FAILURE);
}

void pipe_sync(char **env, char *cmd, int fdin)
{
    pid_t	pid;
	int		fd[2];

    if(pipe(fd) == -1)
        exit(-1);
    pid = fork();
    if(pid)
    {
        close(fd[1]);
        dup2(fd[0], STDIN);
        waitpid(pid, NULL, 0);
    }
    else
    {
        close(fd[0]);
        dup2(fd[1], STDOUT);
        if (fdin == STDIN)
            exit(-1);
        execmd(env, cmd);
    }
}

int main(int argc, char *argv[], char *env[])
{
    int fdin;
    int fdout;

    if (argc == 5)
    {
        fdin = get_fd(argv[1], 0);
        fdout = get_fd(argv[4], 1);
        dup2(fdin, STDIN);
        dup2(fdout, STDOUT);
        pipe_sync(env, argv[2], fdin);
        execmd(env, argv[3]);
    }
    else
        write(STDERR, "pipex : invalid number of arguments !\n", 38);
    return (0);
}
