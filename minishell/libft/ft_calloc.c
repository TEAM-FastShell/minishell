/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youyoon <youyoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 00:44:58 by youyoon           #+#    #+#             */
/*   Updated: 2023/08/26 12:50:22 by youyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*tmp;

	tmp = malloc(size * nmemb);
	if (!tmp)
		return (0);
	ft_memset(tmp, 0, size * nmemb);
	return (tmp);
}
