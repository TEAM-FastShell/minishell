/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokklee <seokklee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 14:58:32 by seokklee          #+#    #+#             */
/*   Updated: 2023/09/12 10:32:08 by seokklee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	connect_fd(t_data *data)
{
	if (data->input_fd != STDIN_FILENO && data->input_fd > 0)
	{
		dup2(data->input_fd, STDIN_FILENO);
		ft_close(data->input_fd);
	}
	if (data->output_fd != STDOUT_FILENO && data->output_fd > 0)
	{
		dup2(data->output_fd, STDOUT_FILENO);
		ft_close(data->output_fd);
	}
}
