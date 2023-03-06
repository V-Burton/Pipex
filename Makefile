NAME    =    pipex

FILES 	:= main.c \
			parsing.c \
			init.c \
			execution.c \
			free.c \

PATH_LIBFT	:= libft/

PATH_PRINTF := ft_printf/

######### Compileur and various options ########

CC    =    cc

CFLAGS    =    -Werror -Wall -Wextra

AR    =		ar

ARFLAGS =    rcs

SANITY    =    -fsanitize=address -g3

RM 		:= 	rm -rf

########## Rules and dependency ###########

HFILES    =    pipex.h\

ODIR    =    ./OBJS/

HDIR    =    ./

SRCS    =    $(FILES)

OBJS    =    $(addprefix $(ODIR), $(FILES:.c=.o))

all    :     mklib $(ODIR) $(NAME)

$(NAME)    :$(OBJS) ${PATH_LIBFT}libft.a ${PATH_PRINTF}libftprintf.a
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS) ${PATH_LIBFT}libft.a ${PATH_PRINTF}libftprintf.a

$(ODIR)    :
			mkdir $(ODIR)

$(ODIR)%.o   :    %.c $(HFILES)
				$(CC) $(CFLAGS) -o $@ -c $<

mklib:
			make -j -C ${PATH_LIBFT}
			make -j -C ${PATH_PRINTF}

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