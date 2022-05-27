/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsolinis <jsolinis@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 19:10:20 by jsolinis          #+#    #+#             */
/*   Updated: 2021/09/14 18:36:33 by jsolinis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	gnl_strlen(char *s, int c)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (i);
}

int	ft_is_line_break(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s2)
		return (NULL);
	if (!s1)
		s1 = ft_empty_str(s1);
	i = -1;
	str = malloc (sizeof(char) * (gnl_strlen(s1, '\0')
				+ gnl_strlen(s2, '\0') + 1));
	while (s1[++i])
		str[i] = s1[i];
	j = 0;
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	free(s1);
	return (str);
}

char	*gnl_substr(char *s, int start, int len)
{
	char	*substr;
	int		i;
	int		k;

	substr = (char *) malloc(len + 1);
	if (!substr || !s)
		return (NULL);
	i = 0;
	k = 0;
	while (s[i])
	{
		if (i >= start && k < len)
		{
			substr[k] = s[i];
			k++;
		}
		i++;
	}
	substr[k] = '\0';
	return (substr);
}

char	*ft_substr_bis(char *s, int start, int len)
{
	char	*substr;
	int		i;
	int		k;

	if (!ft_is_line_break(s))
	{
		free(s);
		return (NULL);
	}
	substr = (char *) malloc(len + 1);
	if (!substr || !s)
		return (NULL);
	i = 0;
	k = 0;
	while (s[i])
	{
		if (i >= start && k < len)
		{
			substr[k++] = s[i];
		}
		i++;
	}
	substr[k] = '\0';
	free (s);
	return (substr);
}
