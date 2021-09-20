/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkim <nkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 18:31:07 by nkim              #+#    #+#             */
/*   Updated: 2021/06/25 02:31:01 by nkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		*get_string_cnt(char const *str, char c, int address_len)
{
	int	*result;
	int	cnt;
	int	i;

	i = 0;
	if (!(result = (int *)malloc(sizeof(int) * address_len)))
		return (0);
	while (*str)
	{
		cnt = 0;
		while (*str != c && *str)
		{
			cnt++;
			str++;
		}
		if (cnt != 0)
		{
			result[i] = cnt;
			i++;
		}
		if (!(*str))
			break ;
		str++;
	}
	return (result);
}

int		get_address_cnt(char const *str, char c)
{
	int	cnt;

	cnt = 0;
	if (!c)
		return (1);
	while (*str)
	{
		if (*str != c)
		{
			cnt++;
			while (*str && *str != c)
				str++;
			str--;
		}
		str++;
	}
	return (cnt);
}

void	put_string(char **result, char const *str, char c, int address_len)
{
	int	i;
	int	flag;
	int	j;

	i = 0;
	while (*str && i < address_len)
	{
		flag = 0;
		j = 0;
		while (*str != c && *str)
		{
			flag = 1;
			result[i][j] = *str;
			j++;
			str++;
		}
		if (flag)
		{
			result[i][j] = 0;
			i++;
		}
		if (!(*str))
			break ;
		str++;
	}
}

void	free_all(char **res, int *string_len)
{
	int	i;

	i = 0;
	while (res[i])
	{
		free(res[i]);
		res[i] = 0;
		i++;
	}
	free(res);
	free(string_len);
	res = 0;
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		address_len;
	int		*string_len;
	int		i;

	if (!s)
		return (0);
	address_len = get_address_cnt(s, c);
	string_len = get_string_cnt(s, c, address_len);
	if (!string_len ||
		!(result = (char **)malloc(sizeof(char *) * (address_len + 1))))
		return (0);
	ft_memset(result, 0, sizeof(char *) * (address_len + 1));
	i = 0 - 1;
	while (++i < address_len && string_len[0])
	{
		if (!(result[i] = (char *)malloc(sizeof(char) * (string_len[i] + 1))))
		{
			free_all(result, string_len);
			return (0);
		}
	}
	free(string_len);
	put_string(result, s, c, address_len);
	return (result);
}