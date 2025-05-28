#include "minishell.h"

bool	validate_in(t_redir *redir)
{
	int	fd;

	fd = open(redir->connection, O_RDONLY);
	if (fd < 0)
		return (false);
	close(fd);
	return (true);
}

bool	validate_out(t_redir *redir)
{
	int	fd;

	fd = open(redir->connection, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (false);//TODO do we need to close fd in this case?
	close(fd);
	return (true);
}

bool	validate_append(t_redir	*redir)
{
	int	fd;

	fd = open(redir->connection, O_WRONLY | O_CREAT | O_APPEND, 0644);
}
//typedef enum	e_red_type
//{
//	RED_IN,//<
//	RED_OUT,//>
//	RED_APPEND,//>>
//	RED_HEREDOC,//<<
//}	t_red_type;

bool    validate_redir(t_redir *redir_list)
{
	static t_redir_handler handlers[] = {
		[RED_IN] = validate_in,
		[RED_OUT] = validate_out,
		[RED_APPEND] = validate_append,
		[RED_HEREDOC] = NULL
	};
	t_redir_handler f;
	while (redir_list)
	{
		if (redir_list->type != RED_HEREDOC)
		{
			f = handlers[redir_list->type];
			if (!f || !f(redir_list))
				return (false);
		}
		redir_list = redir_list->next;
	}
	return (true);
}