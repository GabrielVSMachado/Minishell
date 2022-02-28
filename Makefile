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

#Libs
LIBFT	=	$(LIBFTDIR)/libft.a
LIBS	=	-L$(LIBFTDIR) -lft -lreadline

#TEST
TEST	=	test

#FILES
FILES = util_struct_tokens.c\
		tokenizer.c\
		check_tokens.c\
		err.c

TEST_FILES = $(FILES)\
			 tests_utils_tokenizer.c\
			 tests_treat_word.c\
			 tests_tokenizer.c\
			 tests_check_tokens.c

SRC = main.c\
	  $(FILES)


#INCLUDES
HEADERDIR_LIBFT	= $(LIBFTDIR)/headers
HEADERS	= -I$(HEADERDIR) -I$(HEADERDIR_LIBFT)

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
	$(CC) $(HEADERS) $(OBJ_TEST) -o $(TEST) $(LIBS) -lcriterion
	@./$(TEST)
	@$(MAKE) fclean >  /dev/null

.PHONY: all re fclean clean test
