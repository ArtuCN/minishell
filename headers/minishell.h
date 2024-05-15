/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconti <aconti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:59:59 by ciusca            #+#    #+#             */
/*   Updated: 2024/05/15 13:15:49 by aconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <sys/types.h>
# include <signal.h>
# include <errno.h>

# define ALL_TYPES 'F'
# define RED_ARROW "\033[1;31m-> "
# define GREEN_ARROW "\033[1;32m-> "
# define MINISHELL "\e[1;96mminishell\033[0m$ "
# define DQ 34
# define SQ 39
# define PIPE 124
# define COMMAND 0
# define PARSE 1
# define SYNTAX 2

typedef struct s_red
{
	char			*redir;
	char			*file;
}			t_red;

typedef struct s_cmd
{
	char 			*pathname;
	char 			**cmd_arg;
	char			*command;  
	t_red			*red;
}			t_cmd;


typedef struct s_token
{
	char 	**index;
	int		*mat_ind;
	char	*tokens;
	int		expand;
	int		wrd;
	int		start;
	char	*temp_token;
}		t_token;

typedef struct s_garbage
{
	char				*arg;
	char				**mat;
	struct s_garbage 	*next;
}		t_garbage;

typedef struct s_shell
{
	struct s_shell 	*next;
	char			*infile;
	char 			*outfile;
	char			**redirect;
	char 			*path;
	char			*cmd_name;
	char			**mat_input;
	char			*input;
	char			**envp;
	char			**path_env;
	char			*new_input;
	int				sig_recived;
	int				n_pipes;
	char			*arrow;
	t_token			*tokens;
	t_garbage  		*collector;
	t_cmd			*cmd_table;
}		t_shell;

/* close shell */
void		close_shell(t_shell *shell);
int			collect_garbage(t_shell *shell, char *arg, char **mat);
t_garbage	*new_node(char *arg, char **mat);

/* signals */
void		get_signal();

/* lexer */
char 		*lexer(t_shell *shell);
int			count_wrds(t_shell *shell);
void		checker(t_shell *shell, t_token *token, int words);

char		*ft_readline(char *str);

/* parsing */
int			tokenizer(t_shell *shell);
int			get_path(t_shell *shell);
int			parsing(t_shell *shell);
void		print_cmd(t_shell *shell, int len);
char		*remove_redir(t_token *token);
/* parsing: count */
int			count_pipes(t_shell *shell, char *tokens);
int			count_redir(char *tokens);
/* parsing: cmd table */
int			init_cmd_table(t_shell *shell);
int			pipe_pos(t_token *token, int start);
int			find_token(char *tokens, char type);
/* parsing: fill_cmd */
int	find_start_pos(t_cmd cmd, int type, t_shell *shell, int start);


/* protected functions */
int			fork_p(void);
int			access_p(char *file, int mode);
void		wait_p(int *status);
void		pipe_p(int pipe_fds[2]);
void		execve_p(char *cmd_path, char **argv, char **envp);
void		close_fds(void);
int			ft_error(int error_type, char *str);

/* utils */
int			find_space(char *index);
int			is_redir(int c);
int			find_cmd(t_shell *shell, char *cmd);
void		print_matrix(char **mat);
int			init_structs(t_shell *shell);

#endif