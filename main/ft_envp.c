/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 20:11:23 by ehakam            #+#    #+#             */
/*   Updated: 2021/07/04 20:19:20 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_variables.h"
#include "../include/error.h"
#include "../include/minishell.h"

extern t_minishell g_config;

int 	update_shlvl()
{
	int		value;
	t_var	*var;
	char 	*value_str;

	var = get_var2(g_config.envp, "SHLVL");
	value = 0;
	if (var != NULL)
		if (var->value != NULL)
			value = ft_atoi(var->value);
	value++;
	if (value == 1000)
		value_str = ft_strdup("");
	else if (value > 1000 || value < 0)
	{
		if (value == 1001)
			p_error("warning", NULL,
					"shell level (1001) too high, resetting to 1", 1);
		value_str = ft_itoa(1);
	}
	else
		value_str = ft_itoa(value);
	set_var2(g_config.envp, "SHLVL", value_str, true);
	free(value_str);
	return (0);
}

int		fill_envp(char **envp)
{
	int		i;

	i = -1;
	if (!envp)
		return (1);
	g_config.envp = new_vector();
	while (envp[++i] != NULL)
		insert(g_config.envp, new_var_s(envp[i]));
	update_status_code(0);
	update_shlvl();
	return (0);
}

char	**extract_envp(t_vector *g_env)
{
	char	**envp;
	t_var	*var;
	int		i;
	int		j;

	i = -1;
	j = 0;
	envp = (char **)malloc((g_env->size + 1) * sizeof(char *));
	while (++i < (int) g_env->size)
	{
		var = (t_var *)at(g_env, i);
		if (var->value != NULL)
			envp[j++] = var->raw;
	}
	envp[j] = NULL;
	return (envp);
}
