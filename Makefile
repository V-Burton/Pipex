NAME    =    pipex

NAME_BONUS = pipex

FILES 	= main.c \
			parsing.c \
			init.c \
			execution.c \
			free.c

FILES_BONUS = main_bonus.c \
			parsing_bonus.c \
			init_bonus.c \
			execution_bonus.c \
			free_bonus.c

PATH_LIBFT	= libft/

PATH_PRINTF = ft_printf/

PATH_BONUS = bonus/

######### Compileur and various options ########

CC    =    cc

CFLAGS    =    -Werror -Wall -Wextra -g3

AR    =		ar

ARFLAGS =    rcs

SANITY    =    -fsanitize=address -g3

RM 		:= 	rm -rf

########## Rules and dependency ###########

HFILES    =    pipex.h

HFILES_BONUS = $(PATH_BONUS)pipex_bonus.h

ODIR    =    ./OBJS/

ODIR_B	= OBJS_B/

HDIR    =    ./

SRCS    =   $(FILES)

SRCSB	=	$(FILES_BONUS)

OBJS    =    $(addprefix $(ODIR), $(FILES:.c=.o))

OBJS_B	=    $(addprefix $(PATH_BONUS)$(ODIR_B), $(FILES_BONUS:.c=.o))

all    :     mklib $(ODIR) $(NAME)

$(NAME)    :$(OBJS) ${PATH_LIBFT}libft.a ${PATH_PRINTF}libftprintf.a
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS) ${PATH_LIBFT}libft.a ${PATH_PRINTF}libftprintf.a

$(ODIR)    :
			mkdir $(ODIR)

$(ODIR)%.o   :    %.c $(HFILES)
				$(CC) $(CFLAGS) -o $@ -c $<

$(ODIR_B)	:
			mkdir $(PATH_BONUS)$(ODIR_B)

$(ODIR_B)%.o   :    %.c $(HFILES_BONUS)
				$(CC) $(CFLAGS) -o $@ -c $<

bonus	: $(ODIR_B) $(OBJS_B) ${PATH_LIBFT}libft.a ${PATH_PRINTF}libftprintf.a
			$(CC) $(CFLAGS) $(PATH_BONUS)-o $(NAME_BONUS) $(OBJS_B) ${PATH_LIBFT}libft.a ${PATH_PRINTF}libftprintf.a


mklib	:
			make -j -C ${PATH_LIBFT}
			make -j -C ${PATH_PRINTF}

clean    :
		-rm -rf $(OBJS)
		-rm -rf $(ODIR)
		-rm -rf $(PATH_BONUS)$(OBJS_B)
		-rm -rf $(PATH_BONUS)$(ODIR_B)
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