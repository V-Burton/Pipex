NAME    =    pipex

NAME_BONUS = pipex

FILES 	= main.c \
			parsing.c \
			init.c \
			execution.c \
			free.c \

FILES_BONUS = main_bonus.c \
			parsing_bonus.c \
			init_bonus.c \
			execution_bonus.c \
			free_bonus.c \

PATH_BONUS = bonus/

PATH_LIBFT	= libft/

PATH_PRINTF = ft_printf/

######### Compileur and various options ########

CC    =    cc

CFLAGS    =    -Werror -Wall -Wextra -g3

AR    =		ar

ARFLAGS =    rcs

SANITY    =    -fsanitize=address -g3

RM 		:= 	rm -rf

########## Rules and dependency ###########

HFILES    =    pipex.h

HFILES_BONUS = pipex_bonus.h

ODIR    =    ./OBJS/

ODIR_BONUS = ./OBJS/

HDIR    =    ./

SRCS    =    $(FILES)

SRCS_BONUS = $(FILES_BONUS)

OBJS    =    $(addprefix $(ODIR), $(FILES:.c=.o))

OBJS_BONUS    =    $(addprefix $(ODIR_BONUS), $(FILES_BONUS:.c=.o))

all    :     mklib $(ODIR) $(NAME) bonus

$(NAME)    :$(OBJS) ${PATH_LIBFT}libft.a ${PATH_PRINTF}libftprintf.a
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS) ${PATH_LIBFT}libft.a ${PATH_PRINTF}libftprintf.a

$(ODIR)    :
			mkdir $(ODIR)

$(ODIR)%.o   :    %.c $(HFILES)
				$(CC) $(CFLAGS) -o $@ -c $<

$(ODIR_BONUS)    :
				mkdir $(ODIR_BONUS)

$(ODIR_BONUS)%.o   :    %.c $(HFILES_BONUS)
						$(CC) $(CFLAGS) -o $@ -c $<

mklib:
			make -j -C ${PATH_LIBFT}
			make -j -C ${PATH_PRINTF}

bonus : 	fclean mklib $(OBJS_BONUS) ${PATH_LIBFT}libft.a ${PATH_PRINTF}libftprintf.a
			$(CC) $(CFLAGS) -o $(NAME_BONUS) $(OBJS_BONUS) ${PATH_LIBFT}libft.a ${PATH_PRINTF}libftprintf.a

clean    :
		-rm -rf $(OBJS)
		-rm -rf $(ODIR)
		make clean -C ${PATH_LIBFT}
		make clean -C ${PATH_PRINTF}

fclean    :    clean
		-rm $(NAME)
		make fclean -C ${PATH_LIBFT}
		make fclean -C ${PATH_PRINTF}

re    :    
	make fclean
	make all

clearm    : 
	clear
	make

.PHONY    :    all clean fclean re