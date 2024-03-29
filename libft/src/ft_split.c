/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 18:27:12 by pibouill          #+#    #+#             */
/*   Updated: 2023/10/26 16:26:47 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Returns an array of strings
** from the split of a string by char c
*/

static void	*free_array(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i] != NULL)
		free(arr[i++]);
	free(arr);
	return (NULL);
}

static int	word_count(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static int	word_len(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	*alloc_word(char const *s, char c)
{
	char	*new_word;
	int		i;
	int		len;

	i = 0;
	len = word_len(s, c);
	new_word = malloc(sizeof(char) * (len + 1));
	if (new_word == NULL)
		return (NULL);
	while (i < len)
	{
		new_word[i] = s[i];
		i++;
	}
	new_word[i] = '\0';
	return (new_word);
}

char	**ft_split(char const *s, char c)
{
	char	**new_arr;
	int		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	new_arr = malloc(sizeof(char *) * (word_count(s, c) + 1));
	if (new_arr == NULL)
		return (NULL);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			new_arr[i] = alloc_word(s, c);
			if (new_arr[i] == NULL)
				return (free_array(new_arr));
			i++;
		}
		while (*s && *s != c)
			s++;
	}
	new_arr[i] = 0;
	return (new_arr);
}

// int main()
// {
//     const char *s = "fs nfid isdn i sdoif nsifnd ios ni i odfis";
//     char c = ' ';
// 	int	i = 0;
//     char **words = ft_split(s, c);

//     if (words)
// 	{
// 		while (words[i])
// 		{
// 			printf("Word at index %d: %s\n", i, words[i]);
// 			free(words[i]);
// 			i++;
// 		}
// 		free(words);
//     }
//     return (0);
// }
