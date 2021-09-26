/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdereuse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 04:53:24 by mdereuse          #+#    #+#             */
/*   Updated: 2019/11/14 05:43:35 by mdereuse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	isblank(char c)
{
	return (c == '\t'
			|| c == '\n'
			|| c == '\v'
			|| c == '\f'
			|| c == '\r'
			|| c == ' ');
}

int			ft_atoi(const char *str)
{
	int		i;
	int		neg;
	int		result;

	i = 0;
	while (isblank(str[i]))
		i++;
	neg = str[i] == '-';
	i += (str[i] == '-' || str[i] == '+');
	result = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i] - '0';
		i++;
	}
	result = neg ? result * -1 : result;
	return (result);
}
