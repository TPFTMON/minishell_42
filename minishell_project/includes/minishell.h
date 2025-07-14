/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 07:40:31 by abaryshe          #+#    #+#             */
/*   Updated: 2025/07/13 16:44:13 by sguan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "have_fun.h"
#ifndef MINISHELL_H
# define MINISHELL_H

// <<<<<<<<<<<<<<<<<<<<< INCLUDES >>>>>>>>>>>>>>>>>>>>>

# include "libft.h"
# include "ms_structs.h"
# include <asm-generic/signal-defs.h> // !
# include <bits/sigaction.h>          // !
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h> // For PATH_MAX
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h> // For bool type
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>

// <<<<<<<<<<<<<<<<<<<<< MACROS >>>>>>>>>>>>>>>>>>>>>

extern volatile sig_atomic_t	g_received_signal_value;

# define SUCCESS 0
# define FAIL -1

// EXIT error codes:
# define CRITICAL_ERROR 1
# define SYNTAX_ERROR 2
// ...
# define EXIT_CD_CMD_N_FOUND 127
# define EXIT_CD_SIGINT 130

# define EXIT_MSG_OK "\e[0;32mexiting the minishell\n\e[0m"

# define ERROR_MSG_CRITICAL "\e[1;31mCritical\e[0m \e[0;31merror\e[0m: memory failure.\n"
# define ERROR_MSG_SINGLE_QUOTE "\e[1;31mSyntax\e[0m \e[0;31merror\e[0m: unclosed single quotes (\').\n"
# define ERROR_MSG_DOUBLE_QUOTE "\e[1;31mSyntax\e[0m \e[0;31merror\e[0m: unclosed double quotes (\").\n"
# define ERROR_MSG_REDIR "\e[1;31mSyntax\e[0m \e[0;31merror\e[0m: redirection doesn't have a target.\n"
# define ERROR_MSG_PIPE "\e[1;31mSyntax\e[0m \e[0;31merror\e[0m: wrong pipe placement.\n"
# define ERROR_MSG_UNEXPECTED_TOKEN "\e[1;31mSyntax\e[0m \e[0;31merror\e[0m: syntax error near unexpected token.\n"
# define ERROR_MSG_UNIQUE "\e[1;31mSyntax\e[0m \e[0;31merror\e[0m: an unique error occured.\n"

# define WARNING_MSG_HEREDOC_EOF "\e[1;33mHeredoc\e[0m \e[0;33mwarning\e[0m: EOF was encountered instead of a delimiter.\n"

// <<<<<<<<<<<<<<<<<<<<< FUNCTIONS >>>>>>>>>>>>>>>>>>>>>

//  -------------------- core --------------------
// initialization.c:
t_shell_data					*init_shell_data(char const **envp);

// signals.c:
int								setup_signals(void);
void							process_pending_signal(t_shell_data *shell);

// cleanup.c:
void							free_redir_list(t_redirection **redirections);
void							free_cmd(t_command *cmd);
void							free_cmd_list(t_command **pipeline_head);
void							free_command_list(t_command *cmd);
void							*free_string_array(char **envp_copy);
void							*free_shell(t_shell_data *shell);

// prompt.c:

// -------------------- execution --------------------
char							*get_env_value(char **envp, const char *name);
int								set_env_value(char ***envp, char *key,
									char *value);
char							**add_env_value(char ***envp, char *key,
									char *value);

int								is_builtin(const char *cmd);
int								execute_builtin(t_shell_data *shell,
									char **args);

int								builtin_cd(char **args, char ***envp);
int								builtin_echo(char **args);
int								builtin_env(char **envp, char **args);
int								builtin_exit(t_shell_data *shell, char **args);
int								builtin_export(char **args, char ***envp);
int								builtin_pwd(char **args);
int								builtin_unset(char **args, char ***envp);

int								count_commands(t_command *cmd);
int								setup_pipeline(t_pipex *pipex);
void							free_pipex(t_pipex *pipex);
void							close_all_pipes(t_pipex *pipex);
int								handle_fork_failure(t_pipex *pipex,
									int created_pids);

int								execute_single_external(t_shell_data *shell,
									t_command *cmd);
int								execute_builtin_with_redir(t_shell_data *shell,
									char **argv, t_redirection *redirections);
int								execute_pipeline(t_shell_data *shell,
									t_command *cmd);
int								executor(t_shell_data *shell, t_command *cmd);

int								find_command_path(t_command *cmd, char **envp);
int								count_commands(t_command *cmd);

int								handle_redirections(t_redirection *redir);
int								handle_redirections_only(t_redirection *redir);

// -------------------- parsing --------------------

//                <C>   core_parsing   <C>
// parse_input.c:
t_command						*parse_input(char *input, t_shell_data *shell);

// cleanup_pars.c:
void							free_token_list(t_token **tokens);
void							free_parsing(t_token **tokens,
									t_command **commands);
void							free_str_buffer(t_str_buffer *buf);

// codes.c:
void							set_last_exit_status(t_shell_data *shell);

//                 <L>   lexer   <L>
// lexer.c:
t_token							*lex_input(char *input, t_shell_data *shell);
t_token							*tokenize_input(t_token **tokens, char *input,
									t_shell_data *shell);

// is_character.c:
int								is_metacharacter(int ch, int expanded);

// tokens_utils.c:
t_token							*init_token(t_token_type type, char *content,
									t_shell_data *shell);
void							add_token_back(t_token **tokens,
									t_token *new_token);

// tokens.c:
void							create_word_token(t_token **token, char *input,
									int *i, t_shell_data *shell);
void							create_word(t_str_buffer *buf, char *input,
									int *i, t_shell_data *shell);
void							create_redir_pipe_token(t_token **token,
									char *input, int *i, t_shell_data *shell);
t_token							*get_next_token(char *input, int *i,
									t_shell_data *shell);

// str_buffer.c:
t_str_buffer					*init_str_buffer(size_t initial_capacity);
int								append_char_buffer(t_str_buffer *buf, char c);
int								append_str_buffer(t_str_buffer *buf,
									const char *str_to_append);

// append_quotes.c:
void							append_double_quotes(t_str_buffer *buf,
									char *input, int *i, t_shell_data *shell);
void							append_single_quotes(t_str_buffer *buf,
									char *input, int *i, t_shell_data *shell);

// expand_env_var.c:
void							expand_env_var(t_str_buffer *buf, char *input,
									int *i, t_shell_data *shell);
void							append_env_name(t_str_buffer *buf, char *input,
									int *i, t_shell_data *shell);
char							*get_env_name(char *input, int *i,
									t_shell_data *shell);
char							*get_env_val(char *name_to_find,
									t_shell_data *shell);
void							append_last_exit_status(t_str_buffer *buf,
									t_shell_data *shell);

// errors_lexer.c:
void							print_lexer_errors(t_internal_code error_code);

//                <P>   parser   <P>
// parser.c:
t_command						*build_cmd_list(t_token **tokens,
									t_shell_data *shell);
t_command						*get_next_cmd(t_token **token_now,
									t_shell_data *shell);

// command_utils.c:
t_command						*init_cmd(t_shell_data *shell);
void							add_cmd_back(t_command **pipeline_head,
									t_command *new_cmd);

// process_redir.c:
int								is_redir_token(t_token_type type);
void							add_redir_back(t_redirection **redirections,
									t_redirection *new_redir);
t_redir_type					convert_token_type_to_redir_type(t_token_type token_type);
t_redirection					*create_redirection(t_token **token_now,
									t_token_type token_type,
									t_shell_data *shell);
void							process_redir_token(t_command *cmd,
									t_token **token_now, t_shell_data *shell);

// process_word.c:
void							add_to_argv(t_command *cmd, char *str_to_add,
									t_shell_data *shell);
void							process_word_token(t_command *cmd,
									t_token **token_now, t_shell_data *shell);

// process_heredocs.c:
int								process_heredocs(t_command **pipeline_head,
									t_shell_data *shell);
int								process_single_heredoc(t_redirection *redir,
									t_shell_data *shell);

// errors_parser.c:
void							print_and_set_parser_errors(t_shell_data *shell);

//                <T>   testing   <T>
// print_token.c:
void							print_token(t_token *token);
void							print_token_list(t_token **tokens);

// print_buffer.c:
void							print_str_buffer(t_str_buffer *buf);

// print_cmd.c:
void							print_redir_list(t_redirection *redirections);
void							print_cmd(t_command *cmd, size_t i);
void							print_cmd_list(t_command **pipeline_head);

#endif
