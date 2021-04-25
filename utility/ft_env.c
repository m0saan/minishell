/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 17:13:38 by ehakam            #+#    #+#             */
/*   Updated: 2021/04/25 17:52:18 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env.h"

static char *ft_substr(char *str, int from, int to)
{
	int		i;
	int		len;
	char	*sub;
	
	i = 0;
	if (!str)
		return (NULL);
	len = strlen(str);
	if (from < 0 || from >= to || from >= len || to > len)
		return (NULL);
	sub = (char *)malloc((to - from + 1) * sizeof(char));
	while (from < to)
		sub[i++] = str[from++];
	sub[i] = '\0';
	return (sub);
}

static int index_of(char *str, char c)
{
	int		i;
	if (!str)
		return (-1);
	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (i);
	return (-1);
}

t_var	*new_var()
{
	t_var *var;
	
	var = (t_var *)malloc(sizeof(t_var));
	return (var);
}

t_var	*new_var_v(char *key, char *value)
{
	t_var *var;
	
	var = (t_var *)malloc(sizeof(t_var));
	var->key = key;
	var->value = value;
	return (var);
}

t_var	*split_key_value(struct s_var *var, char *var_str)
{
	int		index_of_eq;

	if ((index_of_eq = index_of(var_str, '=')) == -1)
	{
		var->key = strdup(var_str);
		var->value = NULL;
		return (var);
	}
	var->key = ft_substr(var_str, 0, index_of_eq);
	var->value = ft_substr(var_str, index_of_eq + 1, strlen(var_str));
	return (var);
}

t_var	*split_key_value_v(struct s_var *var, char *var_str)
{
	int		index_of_eq;
	if ((index_of_eq = index_of(var_str, '=')) == -1)
		return (new_var_v(strdup(var_str), NULL));
	return (new_var_v(ft_substr(var_str, 0, index_of_eq),
			ft_substr(var_str, index_of_eq + 1, strlen(var_str))));
}

t_bool	equals(void *item1, void *item2)
{
	t_var *var1 = (t_var *)item1;
	t_var *var2 = (t_var *)item2;
	return (strcmp(var1->key, var2->key) == 0);
}



// int main(void)
// {
// 	char *str = "hakam=jdhfjdhsfsh=fhsdfhdsjf000";
// 	int i = index_of(str, '=');
	
// 	printf("==> |%s|\n", ft_substr(str, i + 1, strlen(str)));
// 	return (0);
// }