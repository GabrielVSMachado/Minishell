NAME	= minishell
RM		= rm -rf
ARCH	:= $(findstring Arch,$(file < /etc/os-release))

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

#Libs
LIBFT	=	libft.a
LIBS	=	-L$(LIBFTDIR) -lft -lreadline

vpath %.c $(SRCDIR) $(SRCDIR)/parsing

HEADERDIR_LIBFT	= $(LIBFTDIR)/headers
HEADERS	= -I$(HEADERDIR) -I$(HEADERDIR_LIBFT)
SRC = main.c
OBJ = $(SRC:%.c=$(OBJDIR)/%.o)

all:	$(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(HEADERS) $(OBJ) -o $@ $(LIBS)

$(OBJDIR)/%.o: %.c $(OBJDIR)
	$(CC) $(HEADERS) -c $< -o $@

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

.PHONY: all re fclean clean
