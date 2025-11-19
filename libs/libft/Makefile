CC 			= gcc
CFLAGS 		= -Wall -Werror -Wextra -I$(PATH_INC)

AR 			= ar rcs

RM 			= @rm -rf

PATH_SRC    = src/
PATH_OBJ 	= build/
PATH_INC 	= include/

NAME = 		libft.a
F_SRC = 	ft_isalpha.c ft_isdigit.c \
			ft_isalnum.c ft_isascii.c \
			ft_isprint.c ft_strlen.c \
			ft_memset.c ft_bzero.c \
			ft_memcpy.c ft_memmove.c \
			ft_strlcpy.c ft_strlcat.c \
			ft_toupper.c ft_tolower.c \
			ft_strchr.c ft_strrchr.c \
			ft_strncmp.c ft_memchr.c \
			ft_memcmp.c ft_strnstr.c \
			ft_atoi.c ft_calloc.c \
			ft_strdup.c  ft_putnbr_fd.c \
			ft_substr.c ft_strjoin.c \
			ft_strtrim.c ft_split.c \
			ft_itoa.c ft_strmapi.c \
			ft_striteri.c ft_putchar_fd.c \
			ft_putstr_fd.c ft_putendl_fd.c \
			ft_lstnew_bonus.c \
			ft_lstadd_front_bonus.c \
			ft_lstsize_bonus.c \
			ft_lstlast_bonus.c \
			ft_lstadd_back_bonus.c \
			ft_lstdelone_bonus.c \
			ft_lstclear_bonus.c \
			ft_lstiter_bonus.c \
			ft_lstmap_bonus.c \
			get_next_line_bonus.c \
			get_next_line_utils_bonus.c \
			ft_printf.c ft_printf_hex.c \
			ft_printf_utils.c \
			ft_memfree.c ft_memfreeptr.c \
			ft_count_elem.c \
			ft_isspace.c ft_isblank.c \
			ft_min.c ft_max.c \
			ft_atol.c

SRC =	$(addprefix $(PATH_SRC), $(F_SRC))
OBJ	=	$(patsubst $(PATH_SRC)%.c, $(PATH_OBJ)%.o, $(SRC))

all : $(NAME)

$(OBJ): | banner

$(PATH_OBJ)%.o : $(PATH_SRC)%.c
	@mkdir -p $(PATH_OBJ)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJ) 
	@$(AR) $(NAME) $(OBJ)

banner:
	@echo "Compilando libft.a..."

fclean: clean
	$(RM) $(NAME)

clean:
	$(RM) $(PATH_OBJ)

re: fclean all

.PHONY : all bonus clean fclean re