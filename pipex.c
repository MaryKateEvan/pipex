/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 09:03:17 by mevangel          #+#    #+#             */
/*   Updated: 2023/10/30 02:00:47 by mevangel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "minilib/minilib.h"

static char	*ft_find_exec_path(char *cmd, char **envp)
{
	char	**find_path;
	char	*first_half;
	char	*path;
	int		i;

	i = -1;
	if (!envp || !*envp)
		return (ft_strdup("~/"));
	if (ft_strncmp(cmd, "./", 2) == 0)
		return (ft_strdup("/bin/sh"));
	while (*envp && ft_strncmp(*envp, "PATH=", 5))
		envp++;
	if (!(*envp))
		return (NULL);
	find_path = ft_split(*envp + 5, ':');
	while (find_path && find_path[++i])
	{
		first_half = ft_strjoin(find_path[i], "/");
		path = ft_strjoin(first_half, cmd);
		if (access(path, F_OK | X_OK) == 0)
			return (ft_free_2darr(find_path), free(first_half), path);
		free(path);
		free(first_half);
	}
	return (ft_free_2darr(find_path), NULL);
}

static void	ft_execute_cmd(char *cmd, char **envp)
{
	char	**to_exec;
	char	*exec_path;

	to_exec = ft_split(cmd, ' ');
	if (!to_exec)
		ft_error_exit("malloc in ft_split failed");
	if (*cmd == '\0' || !to_exec[0])
	{
		ft_putstr_fd("Error: Empty argument\n", 2);
		ft_close_fds();
		ft_free_2darr(to_exec);
		exit(EXIT_SUCCESS);
	}
	exec_path = ft_find_exec_path(to_exec[0], envp);
	if (!(*to_exec) || !exec_path)
	{
		ft_free_2darr(to_exec);
		ft_error_exit(cmd);
	}
	if (execve(exec_path, to_exec, envp) == -1)
	{
		free(exec_path);
		ft_free_2darr(to_exec);
		ft_error_exit("execve failed");
	}
}

static void	ft_iterate_commands(char *cmd, char **envp)
{
	int		fd[2];
	pid_t	id;

	if (pipe(fd) == -1)
		ft_error_exit("pipe failed");
	id = fork();
	if (id == -1)
		ft_error_exit("fork failed");
	if (id == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		ft_execute_cmd(cmd, envp);
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	if (ft_strnstr(cmd, "sleep", 5))
		waitpid(id, NULL, 0);
	else
		waitpid(id, NULL, WNOHANG);
}

static void	ft_here_doc(char *limiter)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
		ft_error_exit("pipe failed");
	while (ft_read_line(&line) && ft_strncmp(line, limiter, ft_strlen(line)))
	{
		ft_putstr_fd(line, fd[1]);
		free(line);
	}
	dup2(fd[0], STDIN_FILENO);
	free(limiter);
	free(line);
	close(fd[0]);
	close(fd[1]);
}

int	main(int argc, char **argv, char **envp)
{
	int	in_file;
	int	out_file;
	int	i;

	i = 1;
	if (argc < 5 || ((ft_strncmp(argv[1], "here_doc", 9) == 0) && (argc < 6)))
		ft_display_corrext_usage();
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		out_file = ft_open_file(argc, argv, 1);
		ft_here_doc(ft_strjoin(argv[2], "\n"));
		i++;
	}
	else
	{
		in_file = ft_open_file(argc, argv, 2);
		out_file = ft_open_file(argc, argv, 3);
		dup2(in_file, STDIN_FILENO);
	}
	while (++i < argc - 2)
		ft_iterate_commands(argv[i], envp);
	dup2(out_file, STDOUT_FILENO);
	ft_close_fds();
	ft_execute_cmd(argv[argc - 2], envp);
	return (EXIT_SUCCESS);
}
