/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 16:24:26 by moboustt          #+#    #+#             */
/*   Updated: 2021/07/06 21:17:35 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/global_utils.h"

static int	get_words(char *s, char c)
{
	int		i;
	int		words;

	i = 0;
	words = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			words++;
		i++;
	}
	return (words);
}

static int	get_chars(char *s, char c)
{
	int		i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

static char	**fill_out(char *s, char **word, char c)
{
	int		i;
	int		n_words;
	int		n;

	i = 0;
	n_words = 0;
	n = 0;
	while (s[i] && n_words < get_words(s, c))
	{
		while (s[i] == c)
			i++;
		if (s[i] != c)
			word[n_words] = ft_malloc(sizeof(char) * get_chars(&s[i], c) + 1);
		while (s[i] != c && s[i])
			word[n_words][n++] = s[i++];
		word[n_words++][n] = '\0';
		n = 0;
	}
	word[n_words] = NULL;
	return (word);
}

char		**ft_split(const char *ss, char c)
{
	char	**word;
	char	*s;

	s = (char *)ss;
	if (!ss)
	{
		word = ft_malloc(sizeof(char *));
		word = NULL;
	}
	else
	{
		word = ft_malloc((get_words(s, c) + 1) * sizeof(char *));
		word = fill_out(s, word, c);
	}
	return (word);
}
