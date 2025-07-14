/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguan <sguan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 23:18:27 by sguan             #+#    #+#             */
/*   Updated: 2025/07/14 19:20:30 by sguan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_redirection_file(t_redirection *redir, int *fd)
{
	if (redir->type == REDIR_INPUT)
		*fd = open(redir->target, O_RDONLY);
	else if (redir->type == REDIR_OUTPUT)
		*fd = open(redir->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == REDIR_APPEND)
		*fd = open(redir->target, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (redir->type == REDIR_HEREDOC)
	{
		if (redir->heredoc_fd >= 0)
			*fd = redir->heredoc_fd;
		else
		{
			ft_dprintf(2, "minishell: error: cannot read heredoc\n");
			return (-1);
		}
	}
	else
    	return(ft_dprintf(2, "minishell: unknown redirection type\n"), -1);
	if (*fd < 0)
	{
		ft_dprintf(2, "minishell: %s: %s\n", redir->target, strerror(errno));
		return (-1);
	}
	return (0);
}

int	handle_redirections(t_redirection *redir)
{
	int	fd;
	int	target_fd;

	if (!redir)
		return (0);
	while (redir)
	{
		if (open_redirection_file(redir, &fd) < 0)
			return (-1);
		if (redir->type == REDIR_INPUT || redir->type == REDIR_HEREDOC)
			target_fd = dup2(fd, STDIN_FILENO);
		else
			target_fd = dup2(fd, STDOUT_FILENO);
		if (target_fd < 0)
		{
			ft_dprintf(2, "minishell: dup2 failed: %s\n", strerror(errno));
			close(fd);
			return (-1);
		}
		if (redir->type != REDIR_HEREDOC || fd != redir->heredoc_fd)
			close(fd);
		redir = redir->next;
	}
	return (0);
}
static int	handle_file_redirection(t_redir_type type, char *target)
{
    int	fd;
    int	flags;

    if (type == REDIR_INPUT)
        flags = O_RDONLY;
    else if (type == REDIR_OUTPUT)
        flags = O_WRONLY | O_CREAT | O_TRUNC;
    else if (type == REDIR_APPEND)
        flags = O_WRONLY | O_CREAT | O_APPEND;
    else
        return (0);
    fd = open(target, flags, 0644);
    if (fd < 0)
        return (ft_dprintf(2, "minishell: %s: %s\n", target, strerror(errno)), 1);
    close(fd);
    return (0);
}

int	handle_redirections_only(t_redirection *redir)
{
    t_redirection	*current;
    int				result;

    current = redir;
    while (current)
    {
        if (current->type == REDIR_HEREDOC)
        {
            if (current->heredoc_fd >= 0)
                close(current->heredoc_fd);
        }
        else
        {
            result = handle_file_redirection(current->type, current->target);
            if (result != 0)
                return (result);
        }
        current = current->next;
    }
    return (0);
}

