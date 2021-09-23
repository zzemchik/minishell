#ifndef MINISHELL_H
# define MINISHELL_H

# define RESET		"\033[0m"
# define BLACK		"\033[1;30m"
# define RED		"\033[1;31m"
# define GREEN		"\033[1;32m"
# define YELLOW		"\033[1;33m"
# define BLUE		"\033[1;34m"
# define MAGENTA	"\033[1;35m"
# define CIAN		"\033[1;36m"
# define WHITE		"\033[1;37m"

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <time.h>
# include <fcntl.h>
# include <sys/types.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>

typedef struct			s_env_var
{
	char				*key;
	char				*value;
	struct s_env_var	*next;
}						t_env_var;

typedef struct			s_list
{
	char				*data;
	struct s_list		*next;
}						t_list;

typedef struct			s_list_list
{
	t_list				*data;
	struct s_list_list	*next;
}						t_list_list;

typedef struct			s_stack
{
	int					data;
	struct s_stack		*next;
}						t_stack;

typedef struct			s_split_quat
{
	char				*line;
	char				*str;
	int					flag;
	int					flag_ctrl_d;
	int					kall;
}						t_split_quat;

typedef struct			s_pair
{
	int					first;
	int					second;
}						t_pair;

int						g_ret_value;
int						g_out;
int						g_in;
int						g_g;
int						g_flag;
int						g_ctrl_c;
int						g_ctrl_s;
t_env_var				*g_vars_list;
t_env_var				*g_temp_vars_list;

int						is_num(char c);
void					all_zero(void);
void					exita(int code);
char					*ft_itoa(int n);
char					*give_pwd(void);
int						is_alpha(char c);
void					parser(char *buf);
void					cnf(t_list **list);
void					print_export(void);
void					skip(t_list **list);
void					unset(t_list **list);
int						key_exist(char *key);
int						pop(t_stack **stack);
void					do_bin(t_list **list);
void					export(t_list **list);
void					dequote(t_list *list);
void					free_path(char **path);
void					display_all_vars(void);
void					ctrl_c_handler(int sig);
void					print_error(char *argv);
int						ft_lstsize(t_list *lst);
void					free_pipe(int ***pipefd);
void					find_tilda(t_list *list);
int						correct_equal(char *str);
t_list					*ft_lstlast(t_list *lst);
void					free_if_exist(char *str);
void					print_list(t_list *list);
int						ft_atoi(const char *str);
t_list					*ft_lstnew(char *content);
int						ft_strlen(const char *str);
void					ft_putstr(const char *str);
char					*find_new_line(char *buff);
void					replace_vars(t_list *list);
int						to_many_operator(char *str);
char					**vars_to_array(char *name);
void					command_exit(t_list **list);
void					parse_env_vars(char **envp);
void					find_equally(t_list **list);
void					ctrl_slash_handler(int sig);
char					*ft_strdup(const char *str);
void					command_echo(t_list **list);
int						cheker_kalla(t_list **list);
int						apply_equally(t_list **list);
void					free_one_list(t_list **list);
int						free_full_list(t_list **list);
void					str_new(char **str, char *new);
void					free_vars_list(t_env_var *list);
void					push(t_stack **stack, int data);
void					sort_array(char **arr, int size);
char					*ft_strchr(const char *s, int c);
void					parser_loop_flags(t_list **list);
int						get_next_line(int fd, char **line);
void					command_cd(t_list **list, int flag);
char					*ft_split_2(t_list *list, char *str);
char					*ft_strndup(const char *str, int kk);
char					*get_value(char *key, t_env_var *vars);
void					give_pipe(t_list *list, int ***pipefd);
int						get_next_line_mini(int fd, char **line);
char					**standart_split(char const *s, char c);
char					**standart_split(char const *s, char c);
void					find_and_remove(char *key, char **value);
void					remove_value(t_env_var **list, char *key);
void					do_it_pwd(t_list **list, t_stack **stack);
void					parser_env(t_list **list, t_stack **stack);
char					*find_arrow(t_list *list, int j, char *str);
void					parser_enva(t_list **list, t_stack **stack);
int						check_last_dollar(char *temp, char **result);
t_list					*ft_split(char const *str_bed, t_list *list);
char					*ft_strtrim(char const *s1, char const *set);
void					ft_lstadd_back(t_list **lst, t_list *lst_new);
void					add_reminder(char *temp, int i, char **result);
int						ft_strcmp(const char *str_f, const char *str_s);
char					*ft_strjoin(const char *str1, const char *str2);
int						ft_strcmp_split(const char *str, const char *find);
int						standart_strcmp(const char *str1, const char *str2);
void					kill_arrow(t_list **list_new, int flag, t_list *tmp);
int						find_quat(const char *str, t_pair *p, t_list **list);
void					add_var(char *key, char *value, \
								t_env_var **list, int flag);
void					kill_arrow_help(t_list **tmp, int flag, \
										t_list **list_new, int i);
void					just_do_it(t_list **list, t_stack **stack, \
										void (*f)(t_list **list));

#endif
