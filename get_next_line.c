/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adunal <adunal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 17:43:44 by adunal            #+#    #+#             */
/*   Updated: 2022/12/09 18:12:53 by adunal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*newlinedansonra_line(char *str)
{
	int		i;
	int		j;
	char	*yeni_str;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	yeni_str = (char *)malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!yeni_str)
		return (NULL);
	i++;
	while (str[i])
		yeni_str[j++] = str[i++];
	yeni_str[j] = '\0';
	free(str);
	return (yeni_str);
}

char	*newlinedanonce_line(char *str)
{
	int		i;
	char	*yeni_str;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	yeni_str = (char *)malloc(sizeof(char) * (i + 2));
	if (!yeni_str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		yeni_str[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		yeni_str[i] = str[i];
		i++;
	}
	yeni_str[i] = '\0';
	return (yeni_str);
}

char	*put_line(int fd, char *line)
{
	char	*buff;
	int		read_value;

	buff = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	read_value = 1;
	while (!ft_strchr(line, '\n') && read_value != 0)
	{
		read_value = read(fd, buff, BUFFER_SIZE);
		if (read_value == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[read_value] = '\0';
		line = ft_strjoin(line, buff);
	}
	free(buff);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*s;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = put_line(fd, line);
	if (line)
	{
		s = newlinedanonce_line(line);
		line = newlinedansonra_line(line);
		return (s);
	}
	return (NULL);
}
/*
int	main(void)
{
	int		fd;
	char	*s;
	

	fd = open("my.txt", O_RDONLY);
	s = get_next_line(fd);

	while (s)
	{
		printf("%s", s);
		s = get_next_line(fd);
	}
}
*/
/*
int	main()
{
	int		fd;
	char	*s;
	
	fd = open("my.txt", O_RDONLY);
	s = get_next_line(fd);
	printf("%s", s);
	s = get_next_line(fd);
	printf("%s", s);
}
*/