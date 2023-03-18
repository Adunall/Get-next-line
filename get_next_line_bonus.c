/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adunal <adunal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 17:44:30 by adunal            #+#    #+#             */
/*   Updated: 2022/12/09 18:32:22 by adunal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*newlinedansonra_line(char *str)
{
	int		i;
	int		j;
	char	*newstr;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	newstr = (char *)malloc(sizeof(char) * ((ft_strlen(str) - i) + 1));
	if (!newstr)
		return (NULL);
	i++;
	while (str[i])
		newstr[j++] = str[i++];
	newstr[j] = '\0';
	free(str);
	return (newstr);
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

char	*putline(int fd, char *line)
{
	char	*buff;
	int		readss;

	buff = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	readss = 1;
	while (!ft_strchr(line, '\n') && readss != 0)
	{
		readss = read(fd, buff, BUFFER_SIZE);
		if (readss == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[readss] = '\0';
		line = ft_strjoin(line, buff);
	}
	free(buff);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*line[4096];
	char		*s;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line[fd] = putline(fd, line[fd]);
	if (line[fd])
	{
		s = newlinedanonce_line(line[fd]);
		line[fd] = newlinedansonra_line(line[fd]);
		return (s);
	}
	return (NULL);
}
/*
int main()
{
    int fd = open("my.txt", O_RDONLY);
    int fd_ = open("my2.txt", O_RDONLY);
    
    int i;
	int fd_arry[2];
	fd_arry[0] = fd;
	fd_arry[1] = fd_;
    char    **str;
    str = (char **)malloc(sizeof(char *) * 20);
    while (i < 2)
    {
		str[i] = get_next_line(fd_arry[i]);
        while(str[i])
		{
			printf("%s", str[i]);
			str[i] = get_next_line(fd_arry[i]);
		}
		i++;
    }
}
*/
