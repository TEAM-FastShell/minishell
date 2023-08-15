/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youyoon <youyoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 21:58:35 by youyoon           #+#    #+#             */
/*   Updated: 2022/11/18 22:08:51 by youyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*cur;

	if (!lst || !del)
		return ;
	else
	{
		cur = *lst;
		while (cur)
		{
			tmp = cur;
			cur = cur->next;
			ft_lstdelone(tmp, del);
		}
		*lst = 0;
	}
}
