NAME	= minishell
RM		= rm -rf
ARCH	:= $(findstring Arch,$(file < /etc/os-release))
CFLAGS	= -Wall -Wextra -Werror -O2

ifeq ($(ARCH),Arch)
	CC	=	gcc
else
	CC	=	clang
endif

#Directories
OBJDIR		:=	obj
LIBFTDIR	:=	libft
SRCDIR		:=	src
HEADERDIR	:=	headers

define VPATH
	$(SRCDIR)
	$(SRCDIR)/lexer
	$(SRCDIR)/errors
	$(SRCDIR)/expand
	$(SRCDIR)/builtins/hashtable
	$(SRCDIR)/builtins
	$(SRCDIR)/parsing
	$(SRCDIR)/executor
	$(SRCDIR)/signals
endef

#Libs
LIBFT	=	$(LIBFTDIR)/libft.a
LIBS	=	-L$(LIBFTDIR) -lft -lreadline

#FILES
define FILES

	util_struct_tokens.c
	tokenizer.c
	check_tokens.c
	err.c
	expand_quotes.c
	hashtable.c
	utils_keyval_lst.c
	utils_envs.c
	expand_env_variables.c
	expand_command.c
	hashtable_utils.c
	unset.c
	env.c
	export.c
	utils_s_program.c
	parsing.c
	utils_parsing.c
	check_path.c
	utils_exec.c
	heredoc.c
	exec.c
	wait.c
	signals.c
	exit.c
	cd.c
	echo.c
	builtin.c
	pwd.c
	check_dir.c
	utils_child.c
	utils_lexer.c
endef

SRC = main.c\
	  $(FILES)


#INCLUDES
HEADERDIR_LIBFT	= $(LIBFTDIR)/headers
HEADERS	= -I $(HEADERDIR) -I $(HEADERDIR_LIBFT) -I src

#OBJECTS
OBJ = $(SRC:%.c=$(OBJDIR)/%.o)

all:	$(NAME)

$(NAME): $(OBJDIR) $(LIBFT) $(OBJ)
	$(CC) $(HEADERS) $(CFLAGS) $(OBJ) -o $@ $(LIBS)

$(OBJDIR)/%.o: %.c
	$(CC) $(HEADERS) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $@

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

clean:
	$(RM) $(OBJDIR)
	$(MAKE) clean -C $(LIBFTDIR)

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(LIBFTDIR)

re: fclean all

.PHONY: all re fclean clean test
