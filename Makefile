NAME	= minishell
RM		= rm -rf
ARCH	:= $(findstring Arch,$(file < /etc/os-release))
CFLAGS	= -Wall -Wextra -Werror -g

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
TESTDIR		:=	Tests

VPATH = $(SRCDIR):$(SRCDIR)/lexer:$(SRCDIR)/errors:$(TESTDIR)
VPATH += $(SRCDIR)/expand:$(SRCDIR)/builtins/hashtable:$(SRCDIR)/builtins

#Libs
LIBFT	=	$(LIBFTDIR)/libft.a
LIBS	=	-L$(LIBFTDIR) -lft -lreadline

#TEST
TEST	=	test

#FILES
FILES = util_struct_tokens.c\
		tokenizer.c\
		check_tokens.c\
		err.c\
		expand_quotes.c\
		hashtable.c\
		utils_keyval_lst.c\
		utils_envs.c\
		expand_env_variables.c\
		expand_command.c\
		hashtable_utils.c\
		unset.c\
		env.c\
		export.c

TEST_FILES = $(FILES)\
			tests_utils_tokenizer.c\
			tests_treat_word.c\
			tests_tokenizer.c\
			tests_check_tokens.c\
			tests_exp_quotes.c\
			tests_destroy_hashtable.c\
			tests_init_envs.c\
			tests_insert_hashtable.c\
			tests_expand_env_variables.c\
			tests_expand_command.c\
			tests_remove_key.c\
			tests_unset.c\
			tests_export_functions.c

SRC = main.c\
	  $(FILES)


#INCLUDES
HEADERDIR_LIBFT	= $(LIBFTDIR)/headers
HEADERS	= -I $(HEADERDIR) -I $(HEADERDIR_LIBFT) -I src

#OBJECTS
OBJ = $(SRC:%.c=$(OBJDIR)/%.o)
OBJ_TEST = $(TEST_FILES:%.c=$(OBJDIR)/%.o)

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
	$(RM) $(TEST)
	$(MAKE) fclean -C $(LIBFTDIR)

re: fclean all

test: $(OBJDIR) $(LIBFT) $(OBJ_TEST)
	$(CC) $(HEADERS) -g $(OBJ_TEST) -o $(TEST) $(LIBS) -lcriterion
	@./$(TEST)
	@$(MAKE) fclean >  /dev/null

.PHONY: all re fclean clean test
