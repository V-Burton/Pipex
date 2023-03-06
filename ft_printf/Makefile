NAME    =    libftprintf.a

CC    =    cc

CFLAGS    =    -Werror -Wall -Wextra 

AR    =		ar

ARFLAGS =    rcs

SANITY    =    -fsanitize=address

FILES 	:= ft_printf.c \
			ft_putchar.c \
			ft_putnbr.c \
			ft_putnbr_exa.c \
			ft_putstr.c \
			ft_putnbr_adresse_exa.c \
			ft_putnbr_unsigned.c

HFILES    =    ft_printf.h\

ODIR    =    ./OBJS/

HDIR    =    ./

SRCS    =    $(FILES)

OBJS    =    $(addprefix $(ODIR), $(FILES:.c=.o))

BOBJS    =    $(addprefix $(ODIR), $(BFILES:.c=.o))

all    :     $(ODIR) $(NAME)

$(NAME)    :    $(OBJS) 
	$(AR) $(ARFLAGS) $(NAME) $(OBJS) 
	ranlib $(NAME)

$(ODIR)    :
	mkdir $(ODIR)

$(ODIR)%.o    :    %.c $(HFILES)
	$(CC) $(CFLAGS) -I $(HDIR) -o $@ -c $<

clean    :
	-rm -rf $(OBJS)
	-rm -rf $(ODIR)

fclean    :    clean
	-rm $(NAME)

re    :    
	make fclean
	make all

clearm    :
	clear
	make

.PHONY    :    all clean fclean re