/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 21:35:19 by mevangel          #+#    #+#             */
/*   Updated: 2023/10/30 02:05:31 by mevangel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "minilib/minilib.h"

void	ft_display_corrext_usage(void)
{
	ft_putstr_fd("Invalid syntax!\n", 2);
	ft_putstr_fd("Expected: ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2\n", 2);
	ft_putstr_fd("          ./pipex here_doc LIMITER cmd cmd1 file\n", 2);
	exit (EXIT_SUCCESS);
}

void	ft_error_exit(char *perr_msg)
{
	ft_putstr_fd("Error: ", 2);
	perror(perr_msg);
	ft_close_fds();
	exit(EXIT_FAILURE);
}

void	ft_close_fds(void)
{
	int	i;

	i = 2;
	while (++i < 20)
		close(i);
}

int	ft_open_file(int argc, char **argv, int option)
{
	int	file_fd;

	if (option == 1)
	{
		file_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0666);
	}
	else if (option == 2)
	{
		file_fd = open(argv[1], O_RDONLY);
	}
	else
	{
		file_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	}
	if (file_fd == -1)
		ft_error_exit("open failed");
	return (file_fd);
}

int	ft_read_line(char **line)
{
	char	*buffer;
	char	ret;
	int		i;
	char	c;

	i = 0;
	buffer = (char *)malloc(42000);
	if (!buffer)
		ft_error_exit("malloc failed");
	ret = read(STDIN_FILENO, &c, 1);
	while (ret > 0 && c != '\n' && c != '\0')
	{
		buffer[i++] = c;
		ret = read(STDIN_FILENO, &c, 1);
	}
	buffer[i] = '\n';
	buffer[i + 1] = '\0';
	*line = ft_strdup(buffer);
	free(buffer);
	return (i);
}
