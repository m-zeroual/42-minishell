// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   parsing_single_double_quotes.c                     :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/05/29 23:29:29 by esalim            #+#    #+#             */
// /*   Updated: 2023/06/04 23:50:55 by esalim           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../../includes/parsing_single_double_quotes.h"

// char	*get_variable_name(char **line)
// {
// 	int		j;
// 	char	*var;
// 	char	*tmp;

// 	j = 0;
// 	while ((*line)[j] && (ft_isalnum((*line)[j]) || (*line)[j] == '_'))
// 		j++;
// 	var = ft_calloc(j + 1, sizeof(*var));
// 	if (!var)
// 		return (0);
// 	j = 0;
// 	while (**line && (ft_isalnum(**line) || **line == '_'))
// 		var[j++] = *((*line)++);
// 	if (!*var)
// 		return (free(var), NULL);
// 	tmp = ft_strdup(var);
// 	free(var);
// 	return (tmp);
// }

// void	search_and_replace(char *src, char search, char replace)
// {
// 	int	i;

// 	if (!src)
// 		return ;
// 	i = -1;
// 	while (src[++i])
// 		if (src[i] == search)
// 			src[i] = replace;
// }

// void	replace_chars(char	*str)
// {
// 	search_and_replace(str, '"', -3);
//     search_and_replace(str, '\'', -2);
//     search_and_replace(str, '>', -4);
//     search_and_replace(str, '<', -5);
//     search_and_replace(str, '|', -6);
//     search_and_replace(str, '$', -7);
// }

// char	*get_value(t_data	*data, char separ)
// {
// 	char	*val;
// 	char	*str;
// 	char	*tmp;

// 	tmp = data->line;
// 		ft_printf("hello world 445\n");

// 	val = get_variable_name(&data->line);
// 	if (!val)
// 		return (0);
// 	str = ft_getenv(data->shell->env, val);
// 	free(val);
// 	if (!str)
// 	{
// 		if (ft_check_var_exist(data->shell->env, val) == -1)
// 			return (0);
// 		str = ft_strdup("");
// 	}
// 	replace_chars(str);
//     if ((separ == '"' && data->a) || ft_isalnum(*(tmp - 2)))
//             search_and_replace(str, ' ', -9);
// 	val = handle_line(data);
// 	free(str);
// 	str = ft_strtrim(val, " \004\004");
// 	free(val);

// 		ft_printf("hello world 442451245\n");
// 	return (str);
// }

// void	expanding_variables(t_data	*data, char separ)
// {
// 	char	*str;
// 	int		i;

// 	i = 0;
// 	str = get_value(data, separ);
// 	if (!str)
// 		return ;
// 	while (str[i])
// 		data->dest[data->index++] = str[i++];
// 	free(str);
// }

// int	check_conditions(t_data	*data, char separator)
// {
// 	static int	isheredoc;
// 	static int	check;
// 	char		*var_name;
// 	int			i;

// 	if ((separator == '"' || !data->a) && *data->line == '$' && *(data->line + 1) && data->line++)
// 	{
// 		if (check)
// 		{
// 			check = 0;
// 			if (isheredoc)
// 			{
// 				isheredoc = 0;
// 				data->dest[data->index++] = '$';
// 				if (separator && data->a)
// 					data->dest[data->index++] = -42;
// 			}
// 			else
// 			{
// 				data->dest[data->index++] = '$';
// 				var_name = get_variable_name(&data->line);
// 				i = 0;
// 				while (var_name[i])
// 					data->dest[data->index++] = var_name[i++];
// 				free(var_name);
// 				data->dest[data->index++] = -22;
// 			}
// 		}
// 		else if (((separator == '"' && data->a) || (!separator && !data->a)) && *data->line && *data->line == '?')
// 		{
// 			var_name = ft_itoa(data->shell->status);
// 			data->line++;
// 			i = 0;
// 			while (var_name[i])
// 				data->dest[data->index++] = var_name[i++];
// 			free(var_name);
// 		}
// 		else if (((separator == '"' && data->a) || (!separator && !data->a)) && (ft_isalpha(*data->line) || *data->line == '_'))
// 			expanding_variables(data, separator);
// 		else if (ft_isdigit(*data->line) || ft_strchr("$@*#-", *data->line))
// 			data->line++;
// 		else
// 			data->dest[data->index++] = '$';
// 	}
// 	else if (!data->a && *data->line == '|' && data->line++)
// 	{
// 		data->dest[data->index++] = SEPARATOR;
// 		data->dest[data->index++] = PIPE;
// 		data->dest[data->index++] = SEPARATOR;
// 		isheredoc = 0;
// 		check = 0;
// 	}
// 	else if (!data->a && *data->line == '<' && data->line++)
// 	{
// 		data->dest[data->index++] = SEPARATOR;
// 		data->dest[data->index++] = INPUT_REDIRECT;
// 		data->dest[data->index++] = SEPARATOR;
// 		if (*data->line == '<')
// 			isheredoc = 1;
// 		check = 1;
// 	}
// 	else if (!data->a && *data->line == '>' && data->line++)
// 	{
// 		data->dest[data->index++] = SEPARATOR;
// 		data->dest[data->index++] = OUTPUT_REDIRECT;
// 		data->dest[data->index++] = SEPARATOR;
// 		check = 1;
// 		isheredoc = 0;
// 	}
// 	else if (!data->a && (*data->line == ' ' || *data->line == '\t') && data->line++)
// 		data->dest[data->index++] = SEPARATOR;
// 	else
// 	{
// 		if (isheredoc && separator && data->a)
// 		{
// 			data->dest[data->index++] = -42;
// 			isheredoc = 0;
// 			check = 0;
// 		}
// 		data->dest[data->index++] = *(data->line++);
// 		if (*data->line)
// 		{
// 			isheredoc = 0;
// 			check = 0;
// 		}
// 	}
// 	return (data->index);
// }

// int	set_dest(t_data *data)
// {
// 	int		separ_index;
// 	char	separator;

// 	separ_index = get_separator(data->line, &separator);
// 	while (separ_index-- > 0 && *data->line && *data->line != separator)
// 	{
// 		if (!data->a && *(data->line) == ' ')
// 			data->dest[data->index++] = SEPARATOR;
// 		data->index = check_conditions(data, 0);
// 		if (!data->a && *(data->line - 1) == ' ' && *data->line != ' ')
// 			data->dest[data->index++] = SEPARATOR;
// 	}
// 	if (*data->line && *data->line == separator && data->line++)
// 		data->a = !data->a;
// 	if ((data->index == 1 && ((!ft_strncmp(data->line - 1, "\"\"\0", 3) || !ft_strncmp(data->line - 1, "''", 3)) \
// 		|| (!ft_strncmp(data->line - 1, "\"\" ", 3) || !ft_strncmp(data->line - 1, "'' ", 3)))) \
// 		|| !ft_strncmp(data->line - 2, " \"\" ", 4) || !ft_strncmp(data->line - 2, " '' ", 4) \
// 		|| !ft_strncmp(data->line - 2, " \"\"", 4) || !ft_strncmp(data->line - 2, " ''", 4))
// 		data->dest[data->index++] = 1;
// 	while (*data->line && *data->line != separator)
// 	{
// 		if (!data->a && *data->line == ' ')
// 			data->dest[data->index++] = SEPARATOR;
// 		data->index = check_conditions(data, separator);
// 		if (!data->a && *(data->line - 1) == ' ' && *data->line != ' ')
// 			data->dest[data->index++] = SEPARATOR;
// 	}
// 	if (*data->line && *data->line == separator && *data->line++)
// 		data->a = !data->a;
// 	return (data->index);
// }

// char	*handle_line(t_data	*data)
// {
// 	char	*tmp;

// 	if (!data->line || !*(data->line))
// 		return (0);
// 	data->dest = ft_calloc((ft_strlen(data->line) * 100) + 1, sizeof(*data->dest));
// 	if (!data->dest)
// 		return (NULL);
// 	data->index = 0;
// 	data->a = 0;
// 	data->dest[data->index++] = SEPARATOR;
// 	while (*data->line)
// 		data->index = set_dest(data);
// 	if (!data->a && !*data->line)
// 		data->dest[data->index++] = SEPARATOR;
// 	if (data->a)
// 	{
// 		ft_printf("minishell: unexpected EOF while looking for matching\n");
// 		return (free(data->dest), data->shell->status = 2, NULL);
// 	}
// 	tmp = ft_strdup(data->dest);
// 	return (free(data->dest), data->a = 0,tmp);
// }

// void	replace_chars_rev(char *str)
// {
// 	search_and_replace(str, -3, '"');
//     search_and_replace(str, -2, '\'');
//     search_and_replace(str, -4, '>');
//     search_and_replace(str, -5, '<');
//     search_and_replace(str, -6, '|');
//     search_and_replace(str, -7, '$');
//     search_and_replace(str, -9, ' ');
// }

// char	**split_line(t_data	*data)
// {
// 	char	*line_after_handling;
// 	char	**str;
// 	char	*tmp_line;

// 	tmp_line = data->line;
// 	line_after_handling = handle_line(data);
// 		ft_printf("hello world testing\n");
// 	free(tmp_line);
// 	if (!line_after_handling)
// 		return (0);
// 	replace_chars_rev(line_after_handling);
// 	str = ft_split(line_after_handling, SEPARATOR);
// 	free(line_after_handling);
// 	if (!str)
// 		return (0);

// 	return (str);
// }

// char	**parsing_single_double_quotes(t_shell *shell, char *args)
// {
// 	char	*line;
// 	t_data	data;

// 	if (!args)
// 		return (0);
// 	line = ft_strtrim(args, " \t\n");
// 	if (!line)
// 		return (0);
// 	data.shell = shell;
// 	data.line = line;
// 	return (split_line(&data));
// }



/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_single_double_quotes.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 23:29:29 by esalim            #+#    #+#             */
/*   Updated: 2023/06/03 19:29:41 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing_single_double_quotes.h"

char	*get_variable_name(char **line)
{
	int		j;
	char	*var;
	char	*tmp;

	j = 0;
	while ((*line)[j] && (ft_isalnum((*line)[j]) || (*line)[j] == '_'))
		j++;
	var = ft_calloc(j + 1, sizeof(*var));
	if (!var)
		return (0);
	j = 0;
	while (**line && (ft_isalnum(**line) || **line == '_'))
		var[j++] = *((*line)++);
	if (!*var)
		return (free(var), NULL);
	tmp = ft_strdup(var);
	free(var);
	return (tmp);
}

void	search_and_replace(char *src, char search, char replace)
{
	int	i;

	if (!src)
		return ;
	i = -1;
	while (src[++i])
		if (src[i] == search)
			src[i] = replace;
}

char	*get_value(t_shell *shell, char **line, char separ, int *a)
{
	char	*val;
	char	*str;
	char	*tmp;

	tmp = *line;
	val = get_variable_name(line);
	if (!val)
		return (0);
	str = ft_getenv(shell->env, val);
	free(val);
	if (!str)
	{
		if (ft_check_var_exist(shell->env, val) == -1)
			return (0);
		str = ft_strdup("");
	}
	search_and_replace(str, '"', -3);
	search_and_replace(str, '\'', -2);
	search_and_replace(str, '>', -4);
	search_and_replace(str, '<', -5);
	search_and_replace(str, '|', -6);
	search_and_replace(str, '$', -7);
	if ((separ == '"' && *a) || ft_isalnum(*(tmp - 2)))
		search_and_replace(str, ' ', -9);
	val = handle_line(shell, str);
	free(str);
	str = ft_strtrim(val, " \004\004");
	free(val);
	if (!str)
		return (0);
	return (str);
}

void	expanding_variables(t_shell *shell, char **dest, char **line, int *j, char separ, int *a)
{
	char	*str;
	int		i;

	i = 0;
	str = get_value(shell, line, separ, a);
	if (!str)
		return ;
	while (str[i])
		(*dest)[(*j)++] = str[i++];
	free(str);
}

char*	get_rediretion_name(char **line)
{
	char	*dest;
	int		i;

	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] != ' ')
			break;
		i++;
	}
	while ((*line)[i] && (*line)[i] != ' ')
		i++;
	dest = ft_calloc(i + 1, sizeof(*dest));
	if (!dest)
		return (0);
	i = 0;
	while (**line)
	{
		if (**line != ' ')
			break;
		(*line)++;
	}
	i = 0;
	while (**line && **line != ' ')
		dest[i++] = *((*line)++);
	return (dest);
}

int	is_a_redirct(char *dest, int j)
{
	while (dest[--j])
	{
		if (dest[j] == INPUT_REDIRECT || dest[j] == OUTPUT_REDIRECT)
			return (1);
		else if (dest[j] != SEPARATOR)
			return (0);
	}
	return (0);
}

int	check_conditions(t_shell *shell, char **dest, char **line, int *a, int j, char separator)
{
	static int isheredoc;
	static int check;

	if ((separator == '"' || !*a) && **line == '$' && *((*line) + 1) && (*line)++)
	{
		if (check)
		{
			check = 0;
			if (isheredoc)
			{
				isheredoc = 0;
				(*dest)[j++] = '$';
				if (separator && *a)
					(*dest)[j++] = -42;
			}
			else
			{
				(*dest)[j++] = '$';
				char *var_name = get_variable_name(line);
				int	q = 0;
				while (var_name[q])
					(*dest)[j++] = var_name[q++];
				free(var_name);
				(*dest)[j++] = -22;
			}
		}
		else if (((separator == '"' && *a) || (!separator && !*a)) && **line && **line == '?')
		{
			char *str = ft_itoa(shell->status);
			(*line)++;
			int i = 0;
			while (str[i])
				(*dest)[j++] = str[i++];
			free(str);
		}
		else if (((separator == '"' && *a) || (!separator && !*a)) && (ft_isalpha(**line) || **line == '_'))
			expanding_variables(shell, dest, line, &j, separator, a);
		else if (ft_isdigit(**line) || ft_strchr("$@*#-", **line))
			(*line)++;
		else
			(*dest)[j++] = '$';
	}
    else if (!*a && **line == '|' && (*line)++)
    {
        (*dest)[j++] = SEPARATOR;
		(*dest)[j++] = PIPE;
        (*dest)[j++] = SEPARATOR;
		isheredoc = 0;
		check = 0;
    }
	else if (!*a && **line == '<' && (*line)++)
    {
        (*dest)[j++] = SEPARATOR;
		(*dest)[j++] = INPUT_REDIRECT;
        (*dest)[j++] = SEPARATOR;
		if (**line == '<')
			isheredoc = 1;
		check = 1;
    }
	else if (!*a && **line == '>' && (*line)++)
    {
        (*dest)[j++] = SEPARATOR;
		(*dest)[j++] = OUTPUT_REDIRECT;
        (*dest)[j++] = SEPARATOR;
		check = 1;
		isheredoc = 0;
    }
	else if (!*a && (**line == ' ' || **line == '\t') && (*line)++)
        (*dest)[j++] = SEPARATOR;
    else
	{
		if (isheredoc && separator && *a)
		{
			(*dest)[j++] = -42;
			isheredoc = 0;
			check = 0;
		}
		(*dest)[j++] = *((*line)++);
		if (**line)
		{
			isheredoc = 0;
			check = 0;
		}
	}
	return (j);
}

void	check_errors(char **dest, char **line, int *index)
{
	if ((*index == 1 && ((!ft_strncmp((*line) - 1, "\"\"\0", 3) \
		|| !ft_strncmp((*line) - 1, "''", 3)) \
		|| (!ft_strncmp((*line) - 1, "\"\" ", 3) \
		|| !ft_strncmp((*line) - 1, "'' ", 3)))) \
		|| !ft_strncmp((*line) - 2, " \"\" ", 4) \
		|| !ft_strncmp((*line) - 2, " '' ", 4) \
		|| !ft_strncmp((*line) - 2, " \"\"", 4) \
		|| !ft_strncmp((*line) - 2, " ''", 4))
        (*dest)[(*index)++] = 1;
}

int	set_dest(t_shell *shell, char **dest, char **line, int *a)
{
	int		separ_index;
	char	separator;

	separ_index = get_separator(*line, &separator);
	while (separ_index-- > 0 && **line && **line != separator)
	{
		if (!*a && **line == ' ')
			(*dest)[shell->index++] = SEPARATOR;
		shell->index = check_conditions(shell, dest, line, a, shell->index, 0);
		if (!*a && *(*line - 1) == ' ' && **line != ' ')
			(*dest)[shell->index++] = SEPARATOR;
	}
	if (**line && **line == separator && (*line)++)
		*a = !*a;
	check_errors(dest, line, &shell->index);
	while (**line && **line != separator)
	{
		if (!*a && **line == ' ')
			(*dest)[shell->index++] = SEPARATOR;
		shell->index = check_conditions(shell, dest, line, a, shell->index, separator);
		if (!*a && **(line - 1) == ' ' && **line != ' ')
            (*dest)[shell->index++] = SEPARATOR;
	}
	if (**line && **line == separator && (*line)++)
		*a = !*a;
	return (shell->index);
}

char	*handle_line(t_shell *shell, char *line)
{
	char	*dest;
	int		a;
	char	*tmp;

	if (!line || !*line)
		return (0);
	dest = ft_calloc((ft_strlen(line) * 100) + 1, sizeof(*dest));
	if (!dest)
		return (NULL);
	shell->index = 0;
	a = 0;
	dest[shell->index++] = SEPARATOR;
	while (*line)
		shell->index = set_dest(shell, &dest, &line, &a);
	if (!a && !*line)
		dest[shell->index++] = SEPARATOR;
	if (a)
	{
		ft_printf("minishell: unexpected EOF while looking for matching\n");
		free(dest);
		shell->status = 2;
		return (0);
	}
	tmp = ft_strdup(dest);
	free(dest);
	a = 0;
	return (tmp);
}

char	**split_line(t_shell *shell, char *line)
{
	char	*line_after_handling;
	char	**str;
	char	*tmp_line;

	tmp_line = line;
	line_after_handling = handle_line(shell, line);
	free(tmp_line);
	if (!line_after_handling)
		return (0);
	search_and_replace(line_after_handling, -3, '"');
	search_and_replace(line_after_handling, -2, '\'');
	search_and_replace(line_after_handling, -4, '>');
	search_and_replace(line_after_handling, -5, '<');
	search_and_replace(line_after_handling, -6, '|');
	search_and_replace(line_after_handling, -7, '$');
	search_and_replace(line_after_handling, -9, ' ');
	search_and_replace(line_after_handling, -10, 0);
	str = ft_split(line_after_handling, SEPARATOR);
	free(line_after_handling);
	if (!str)
		return (0);
	return (str);
}

char	**parsing_single_double_quotes(t_shell *shell, char *args)
{
	char	*line;

	if (!args)
		return (0);
	line = ft_strtrim(args, " \t\n");
	if (!line)
		return (0);
	return (split_line(shell, line));
}
