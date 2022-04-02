SRCS	= ft_atoi.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_itoa.c \
		ft_memccpy.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_strchr.c \
		ft_strdup.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strmapi.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strtrim.c \
		ft_striteri.c \
		ft_split.c  \
		ft_substr.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c \
		ft_utoa_base.c \
		ft_strcmp.c  \
		ft_abs.c	\
		ft_hsv_to_rgb.c \
		ft_atod.c \
		$(BONUS) \

BONUS = ft_lstadd_back.c \
			ft_lstadd_front.c \
			ft_lstclear.c \
			ft_lstdelone.c \
			ft_lstiter.c \
			ft_lstlast.c \
			ft_lstnew.c \
			ft_lstsize.c \
			ft_lstmap.c

TEST		:=	test
TEST_DIR		:=	Tests
TEST_FILES = $(wildcard $(TEST_DIR)/*.c)

OS	:= $(findstring Arch,$(file < /etc/os-release))

ifeq ($(OS),Arch)
	CC	:=	gcc
else
	CC	:= clang
endif

CFLAGS		=	-Wall -Werror -Wextra -O2
AR			=	ar rcs
RM			:= rm -rf

vpath %.c src src/hash_table Tests

NAME		=	libft.a
HEADERSDIR	:= headers
HEADERS		:= -I$(HEADERSDIR)
OBJDIR		:=	obj
OBJS		=	${SRCS:%.c=$(OBJDIR)/%.o}
TESTOBJ		= 	$(TEST_FILES:$(TEST_DIR)/%.c=$(OBJDIR)/%.o)

all:	$(NAME)

$(NAME):	$(OBJDIR) $(OBJS)
			$(AR) $(NAME) $(OBJS)

$(OBJDIR)/%.o : %.c
			$(CC) $(HEADERS) $(CFLAGS) -c $< -o $@

$(OBJDIR):
			@mkdir -p $@

clean:
			$(RM) $(OBJDIR)

fclean:	clean
			$(RM) $(NAME)
			$(RM) $(TEST)

re:		fclean all

test: $(NAME) $(TESTOBJ)
	$(CC) $(HEADERS) $(TESTOBJ) -o $(TEST) -L. -lft -lcriterion
	@./$(TEST) || exit 1
	@$(MAKE) fclean > /dev/null

.PHONY:	clean re all fclean
