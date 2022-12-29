/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shbi <shbi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 09:27:01 by shbi              #+#    #+#             */
/*   Updated: 2022/12/29 03:53:31 by shbi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	b_env(t_env *menv, char **args)
{
	if (*args)
	{
		error_msg(": No such file or directory\n");
		return (1);
	}
	else
		print_env(menv);
	return (0);
}
