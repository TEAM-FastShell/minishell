
#include "../../include/minishell.h"
#include "../../include/parse.h"

void	free_parse(t_parse *parse)
{
	int	i;

	if (!parse)
		return ;
	i = 0;
	while (parse->cmd[i])
		free(parse->cmd[i++]);
	i = 0;
	while (parse->env[i])
		free(parse->env[i++]);
	free(parse->env);
	free(parse->cmd);
	free(parse->buff);
	parse->quote = 0;
	parse->c_idx = 0;
	parse->b_idx = 0;
	parse->pipe_type = 0;
	parse->redir_type = 0;
	parse = NULL;
}

void	free_list(t_double_list *list)
{
	t_node	*cur;
	t_node	*del;
	int		i;

	if (!list)
		return ;
	cur = list->head;
	while (cur)
	{
		del = cur;
		cur = cur->next;
		i = 0;
		while (del->cmd_args[i] != NULL)
		{
			free(del->cmd_args[i]);
			i++;
		}
		free(del->cmd_args);
		free(del);
	}
	list->cnt = 0;
	list->cmd_cnt = 0;
	list->head = NULL;
	list->tail = NULL;
	list = NULL;
}
