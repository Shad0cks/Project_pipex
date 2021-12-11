/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeshaye <pdeshaye@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 04:51:11 by pdeshaye          #+#    #+#             */
/*   Updated: 2021/12/11 15:03:16 by pdeshaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	get_fd(char *path, int mode)
{
	if (mode == 0)
	{
		if (access(path, F_OK))
		{
			write(STDERR, "Error\ninfile not found !\n", 28);
			exit(EXIT_FAILURE);
		}
		return (open(path, O_RDONLY));
	}
	return (open(path, O_CREAT | O_WRONLY | O_TRUNC, 0777));
}

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	*path_variable;
	char	*temp;
	char	*path;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		return (cmd);
	path_variable = env[i] + 5;
	while (path_variable && ft_strchr(path_variable, ':') > -1)
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

void	execmd(char **env, char *cmd)
{
	char	*path;
	char	**args_cmd;
	char	*true_cmd;

	args_cmd = ft_split(cmd, ' ');
	true_cmd = ft_strjoin("/", args_cmd[0]);
	path = get_path(true_cmd, env);
	free(true_cmd);
	execve(path, args_cmd, env);
	perror("Error\n somthing went wrong ");
	exit(EXIT_FAILURE);
}

pid_t	pipe_sync(char **env, char *cmd, int last)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		exit(-1);
	pid = fork();
	if (pid)
	{
		close(fd[1]);
		if (!last)
			dup2(fd[0], STDIN);
		return (pid);
	}
	close(fd[0]);
	if (!last)
		dup2(fd[1], STDOUT);
	execmd(env, cmd);
	return (pid);
}

int	main(int argc, char *argv[], char *env[])
{
	int	fdin;
	int	fdout;
	int	pid[2];

	if (argc == 5)
	{
		fdin = get_fd(argv[1], 0);
		fdout = get_fd(argv[4], 1);
		if (fdin < 0 || fdout < 0)
		{
			write(STDERR, "Error\npermision acces !\n", 25);
			return (-1);
		}
		dup2(fdin, STDIN);
		dup2(fdout, STDOUT);
		pid[0] = pipe_sync(env, argv[2], 0);
		pid[1] = pipe_sync(env, argv[3], 1);
		waitpid(pid[0], 0, 0);
		waitpid(pid[1], 0, 0);
	}
	else
		write(STDERR, "Error\ninvalid number of arguments !\n", 37);
	return (0);
}
