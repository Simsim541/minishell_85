/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simoberri <simoberri@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:59:49 by mberri            #+#    #+#             */
/*   Updated: 2023/03/10 22:27:33 by simoberri        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	quotes_counter(char c, int *db, int *s)
{
	if (c == '"')
		(*db)++;
	if (c == '\'')
		(*s)++;
}

static void	j_status(char *line, int *i, int *db, int *s)
{
	while (line[*i])
	{
		if (((is_white_space(line[*i])
			|| (line[*i] == '>' || line[*i] == '<')))
			&& (!((*db) % 2) && !((*s) % 2)))
				break ;
		quotes_counter(line[*i], db, s);
		(*i)++;	
	}
}

static int	number_of_argument_with_red(char *line, int *i, int *db, int *s)
{
	int	argument;
	int	j;

	j = 0;
	argument = 0;
	while (line[*i])
	{
		quotes_counter(line[*i], db, s);
		while (is_white_space(line[*i]) && (!((*db) % 2) && !((*s) % 2)))
		{
			(*i)++;
			quotes_counter(line[*i], db, s);
		}
		while (line[*i] && (line[*i] == '>' || line[*i] == '<')
			&& (!((*db) % 2) && !((*s) % 2)))
			j = (*i)++;
		if (j)
		{
			j = *i;
			j_status(line, i, db, s);
			if (j < *i)
				j = 0;
		}
		else
		{
			j = *i;
			j_status(line, i, db, s);
			if (j < *i)
				argument++;
			j = 0;
		}
	}
	return (argument);
}

static int	count_argument(char *line)
{
	int		i;
	int		db;
	int		s;
	int		argument;

	i = 0;
	db = 0;
	s = 0;
	argument = 0;
	while (is_white_space(line[i]))
		i++;
	while (line[i])
	{
		if (((is_white_space(line[i])
		|| (line[i] == '<' || line[i] == '>')))
		&& (!(db % 2) && !(s % 2)))
		break ;
		quotes_counter(line[i], &db, &s);
		i++;
	}
	if (line[i])
		argument = number_of_argument_with_red(line, &i, &db, &s);
	return (argument);
}

void	normal_parsing(t_cmd *cmd, char *line)
{
	char	**command;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 1;
	command = ft_split(line, ' ');
	while (command[k])
		k++;
	if (k > 1)
	{
		cmd->argument = malloc(sizeof(char *) * k + 1);
		cmd->argument[k] = NULL;
	}
	cmd->cmd = ft_strtrim(command[i], '\"', '\'');
	i++;
	while (command[i])
	{
		cmd->argument[j++] = ft_strtrim(command[i], '\"', '\'');
		i++;
	}
	j = 0;
	while (command[j])
	{
		free(command[j]);
		j++;
	}
	free(command);
	cmd->redirect = NULL;
}

static void	fill_type_red(char *line, t_cmd *red, int *i)
{
	if (line[*i] == '>' && line[(*i) + 1] == '>')
		red->redirect->type = RED_DOUBLE_OUT;
	else if (line[*i] == '<' && line[(*i) + 1] == '<')
		red->redirect->type = RED_DOUBLE_INP;
	else if (line[*i] == '<' && line[(*i) + 1] == '>')
		red->redirect->type = RED_INP;
	else if (line[*i] == '>' && (line[(*i) + 1] != '>'
			&& line[(*i) + 1] != '<'))
		red->redirect->type = RED_OUT;
	else if (line[*i] == '<' && (line[(*i) + 1] != '>'
			&& line[(*i) + 1] != '<'))
		red->redirect->type = RED_INP;
}	

void	fill_redirection(t_cmd *red, char *line, int *i)
{
	int	db;
	int	s;
	char *str;

	db = 0;
	s = 0;
	fill_type_red(line, red, i);
	while (line[*i] == '>' || line[*i] == '<')
		(*i)++;
	while (is_white_space(line[*i]))
		(*i)++;
	red->redirect->index = *i;
	while (line[*i])
	{
		if (((is_white_space(line[*i])
			|| (line[*i] == '>' || line[*i] == '<'))
			&& (!(db % 2) && !(s % 2))))
			break ;
		quotes_counter(line[*i], &db, &s);
		(*i)++;
	}
	str = ft_substr(line, red->redirect->index, (*i) - red->redirect->index);
	red->redirect->file_name = ft_strtrim(str, '\"', '\'');
	red->redirect->next = init_redirecttion();
	red->redirect = red->redirect->next;
}

static void	fill_command(t_cmd *cmd, char *line, int *i)
{
	int start;
	int	db;
	int	s;
	char	*str;
	
	db = 0;
	s = 0;
	start = 0;
	while (is_white_space(line[*i]))
		(*i)++;
	start = *i;
	while (line[*i])
	{
		quotes_counter(line[*i], &db, &s);
		if (((line[*i] == '<' || line[*i] == '>') ||
			(is_white_space(line[*i])))
			&& (!(db % 2) && !(s % 2)))
			break ;
		(*i)++;
	}
	str = ft_substr(line, start, (*i) - start);
	cmd->cmd = ft_strtrim(str, '\"', '\'');
}

static void fill_arg_red(char *line, t_cmd *cmd, int *i)
{
	int db;
	char *str;
	int s;
	int start;
	int j;

	init_var(&db, &s, &start, &j);
	while (line[*i])
	{
		quotes_counter(line[*i], &db, &s);
		while (is_white_space(line[*i]) && (!(db % 2) && !(s % 2)))
			(*i)++;
		if ((line[*i] == '>' || line[*i] == '<')
			&& (!(db % 2) && !(s % 2)))
			fill_redirection(cmd, line, i);
		if (line[*i])
		{
			start = *i;
			while (line[*i])
			{
				if (((line[*i] == '>' || line[*i] == '<')
					|| (is_white_space(line[*i])))
					&& (!(db % 2) && !(s % 2)))
						break;
				(*i)++;
				quotes_counter(line[*i], &db, &s);
			}
			if (start < *i)
			{
				str = ft_substr(line, start, *i - start);
				cmd->argument[j] = ft_strtrim(str, '\"', '\'');
				j++;
			}
		}
		while (is_white_space(line[*i]))
			(*i)++;
	}
}

void	parsing_with_redirection(t_cmd *cmd, char *line)
{
	t_redirection	*begin_red;
	t_redirection	*temp;
	int				i;
	int				n_of_argument;

	i = 0;
	n_of_argument = count_argument(line);
	begin_red = cmd->redirect;
	fill_command(cmd, line, &i);
	cmd->argument = malloc(sizeof(char *) * n_of_argument + 1);
	cmd->argument[n_of_argument] = NULL;
	if (line[i])
		fill_arg_red(line, cmd, &i);
	temp = cmd->redirect;
	cmd->redirect = begin_red;
	free(temp);
}
