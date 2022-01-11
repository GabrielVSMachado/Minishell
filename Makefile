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
OBJDIR		=	obj
LIBFTDIR	=	libft
SRCDIR		=	src
HEADERDIR	=	headers
TESTDIR		=	Tests

vpath %.c $(SRCDIR) $(SRCDIR)/builtins/ $(TESTDIR)

#Libs
LIBFT	=	libft.a
LIBS	=	-L$(LIBFTDIR) -lft -lreadline

#TEST
TEST	=	test

#FILES
FILES = pwd.c

TEST_FILES = $(FILES)\
			 pwd_test.c

SRC = main.c $(FILES)


#INCLUDES
HEADERDIR_LIBFT	= $(LIBFTDIR)/headers
HEADERS	= -I$(HEADERDIR) -I$(HEADERDIR_LIBFT)

#OBJECTS
OBJ = $(SRC:%.c=$(OBJDIR)/%.o)
OBJ_TEST = $(TEST_FILES:%.c=$(OBJDIR)/%.o)

all:	$(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(HEADERS) $(CFLAGS) $(OBJ) -o $@ $(LIBS)

$(OBJDIR)/%.o: %.c $(OBJDIR)
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

test: $(LIBFT) $(OBJ_TEST)
	$(CC) $(HEADERS) $(OBJ_TEST) -o $(TEST) $(LIBS) -lcriterion
	@./$(TEST)
	@$(MAKE) fclean >  /dev/null

.PHONY: all re fclean clean test
