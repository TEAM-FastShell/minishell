  /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youyoon <youyoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 16:05:32 by youyoon           #+#    #+#             */
/*   Updated: 2023/08/23 18:00:24 by youyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include "../../../include/parse.h"

char	**set_env(char **envp)
{
	char	**ret;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	ret = (char **) malloc(sizeof(char *) * (i + 1));
	if (!(ret))
		return (NULL);
	i = -1;
	while (envp[++i])
		ret[i] = ft_strdup(envp[i]);
	ret[i] = NULL;
	return (ret);
}

char	*find_env(char *s, char **env)
{
	int		i;
	char	*ret;
	char	*env_tmp;
	char	*trim_set;

	i = 0;
	s++;
	ret = NULL;
	while (env[i] && *s)
	{
		if (!ft_strncmp(env[i], s, ft_strlen(s)))
		{
			trim_set = ft_strjoin(s, "=");
			env_tmp = ft_strtrim(env[i], trim_set);
			ret = ft_strdup(env_tmp);
			break ;
		}
		i++;
	}	
	return (ret);
}