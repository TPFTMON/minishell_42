/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 04:44:08 by abaryshe          #+#    #+#             */
/*   Updated: 2025/06/27 00:38:07 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*get_next_token(char *input, int *i, t_shell_data *shell)
{
	t_token	*new_token;
  // A. Check for Operator Tokens
	if (is_metacharacter(input[*i], 0))
	{
		create_redir_pipe_token(&new_token, input, &i);
		if (!new_token)
			shell->last_exit_status = CRITICAL_ERROR;
		return (new_token);
	}

  // B. If not an operator, it must be a WORD token.
  //    This word can be composed of multiple adjacent segments. Including expandable values.
	create_word_token(&new_token, input, &i, shell);
	if (!new_token)
		shell->last_exit_status = CRITICAL_ERROR;
	return (new_token);
}

t_token	*tokenize_input(char *input, t_token *tokens, t_shell_data *shell)
{
	int		i;
	int		input_len;
	t_token	*new_token;

	i = 0;
	input_len = ft_strlen(input);
	while (i < input_len)
	{
		while (ft_isspace(input[i]))
			i++;
		if (i >= input_len)
			break ;
		new_token = get_next_token(input, &i, shell);
		if (new_token->type == TOKEN_ERROR)
		{
			ft_print_error(NULL, "Error: syntax\n");
			free_token_list(tokens);
			return (NULL);
		}
		add_token_back(&tokens, new_token);
	}
	return (tokens);
}

t_token	*lex_input(char *input, t_shell_data *shell)
{
	t_token	*tokens;
	int		status;

	if (!input || input[0] == '\0')
		return (NULL);
	tokens = NULL;
	tokenize_input(input, &tokens, shell);
	if (shell->last_exit_status != 0)
	{
		if (tokens)
			free_token_list(tokens);
		return (NULL);
	}
	return (tokens);
}

// t_token	*get_next_token(char *input, int *i, t_shell_data *shell)
// {
// 	t_token	*new_token;
// 	  // A. Check for Operator Tokens (easiest case)
//   //    Check for 2-character operators first!
//   if line starts with ">>" at index i:
//     create TOKEN_REDIR_APPEND with value ">>"
//     i += 2
//     return new_token
//   if line starts with "<<" at index i:
//     create TOKEN_REDIR_HEREDOC with value "<<"
//     i += 2
//     return new_token
//   if line starts with ">" at index i:
//     create TOKEN_REDIR_OUT with value ">"
//     i += 1
//     return new_token
//   if line starts with "<" at index i:
//     create TOKEN_REDIR_IN with value "<"
//     i += 1
//     return new_token
//   if line starts with "|" at index i:
//     create TOKEN_PIPE with value "|"
//     i += 1
//     return new_token

//   // B. If not an operator, it must be a WORD token.
//   //    This word can be composed of multiple adjacent segments.
//   create an empty, resizable string_buffer

//   while line[i] exists AND is not a delimiter (whitespace or operator):
//     // Inside this loop, we consume one segment (quoted or unquoted)
//     // and append it to our string_buffer.

//     if line[i] is a single quote ('):
//       // Find the closing single quote
//       j = i + 1
//       while line[j] exists AND line[j] is not a single quote:
//         j++

//       if line[j] is not a single quote: // Unclosed quote
//         print_error("unclosed single quote")
//         free(string_buffer)
//         return ERROR_TOKEN

//       // Append content between quotes to string_buffer
//       append substring(line from i+1 to j-1) to string_buffer
//       i = j + 1 // Move index past the closing quote

//     else if line[i] is a double quote ("):
//       // Find the closing double quote
//       j = i + 1
//       while line[j] exists AND line[j] is not a double quote:
//         j++

//       if line[j] is not a double quote: // Unclosed quote
//         print_error("unclosed double quote")
//         free(string_buffer)
//         return ERROR_TOKEN

//       // Append content between quotes to string_buffer
//       append substring(line from i+1 to j-1) to string_buffer
//       i = j + 1 // Move index past the closing quote

//     else: // It's an unquoted segment
//       // Find the end of this unquoted segment
//       j = i
//       while line[j] exists AND is not a delimiter AND is not a quote:
//         j++

//       // Append the unquoted segment to string_buffer
//       append substring(line from i to j-1) to string_buffer
//       i = j // Move index to the end of the segment

//   // The loop has ended, so we've hit a delimiter or end of string.
//   // The accumulated string_buffer is the value of our WORD token.
//   create TOKEN_WORD with value from string_buffer
//   free(string_buffer)
// 	return (new_token);
// }

// t_token	*tokenize_input(char *input, t_token *tokens, t_shell_data *shell)
// {
	// int		i;
	// int		input_len;
	// t_token	*new_token;
//
	// i = 0;
	// input_len = ft_strlen(input);
	// while (i < input_len)
	// {
		// while (ft_isspace(input[i]))
			// i++;
		// if (i >= input_len)
			// break ;
		// new_token = get_next_token(input, &i, shell);
		// if (new_token->type == TOKEN_ERROR)
		// {
			// ft_print_error(NULL, "Error: syntax\n");
			// free_token_list(tokens);
			// return (NULL);
		// }
		// add_token_back(tokens, new_token);
	// }
	// return (tokens);
// }
