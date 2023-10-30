/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 09:03:44 by mevangel          #+#    #+#             */
/*   Updated: 2023/10/30 02:01:39 by mevangel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <sys/wait.h>

void	ft_display_corrext_usage(void);
void	ft_error_exit(char *perr_msg);
void	ft_close_fds(void);
int		ft_open_file(int argc, char **argv, int option);
int		ft_read_line(char **line);

#endif //PIPEX_H