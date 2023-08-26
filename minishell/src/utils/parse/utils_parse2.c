/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youyoon <youyoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 18:23:39 by youyoon           #+#    #+#             */
/*   Updated: 2023/08/26 20:20:30 by youyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include "../../../include/parse.h"

static char	*get_envv(char *envp[], char *envv)
{
	envv++;
	while (*envp && *envv)
	{
		if (!ft_strncmp(*envp, envv, ft_strlen(envv)))
		{
			return (*envp + ft_strlen(envv) + 1);
		}
		envp++;
	}
	return (NULL);
}

void	set_data_env(t_data *data)
{
	int		i;
	t_node	*cur;
	char	*tmp;
	char	*env_val;

	cur = data->list->head;
	while (cur)
	{
		i = -1;
		while (cur->cmd_args[++i])
		{
			if (!ft_strncmp(cur->cmd_args[i], "$?", \
					ft_strlen(cur->cmd_args[i])))
				continue ;
			if (ft_strchr(cur->cmd_args[i], '$'))
			{
				tmp = cur->cmd_args[i];
				env_val = get_envv(data->envp, cur->cmd_args[i]);
				// if (env_val)
				// 	cur->cmd_args[i] = ft_strdup(env_val);
				// ree(tmp);
			}
		}
		cur = cur->next;
	}
}
