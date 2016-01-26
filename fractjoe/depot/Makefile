NAME=fractol
CC=gcc
CFLAGS=-Wall -Wextra -Werror
DIR_LFT=libft/
LIBFT=-L libft -lft -I libft/includes
MLXLIB=-L/usr/X11/lib -lmlx -lXext -lX11 -I /usr/X11/include/
INCLUDES=-I ./ -I libft/includes  -I /usr/X11/include/

SRC = main.c \
	  mlx_function.c \
	  init.c \
	  GUI/input_hooks.c \
	  GUI/key_input.c \
	  GUI/key_hooks.c \
	  GRAFX/graphics.c \
	  GRAFX/equations.c \
	  GRAFX/color.c \
	  GRAFX/color_fn.c \
	  GRAFX/display.c \
	  GRAFX/thread.c \
	  GRAFX/complex.c \
	  GRAFX/function.c \
	  GRAFX/drawing.c

OBJ = $(SRC:.c=.o)

.PHONY: all clean fclean
.SILENT:

all: $(NAME)

$(NAME): $(OBJ)
		echo "\t\xF0\x9F\x8F\x81   Compiling \033[35m$(NAME) \033[0mDONE!"
		(make -C $(DIR_LFT))
		$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFT) $(MLXLIB)


%.o: %.c fractol.h
		echo "\t\xF0\x9F\x94\xA7   Building \033[34m $@ \033[0m"
		$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
		echo "\t\xF0\x9F\x92\xA3   Cleaning"
		(make -C $(DIR_LFT) $@)
		rm -f $(OBJ)

fclean: clean
		echo "\t\xF0\x9F\x9A\xBD   Full Clean"
		(make -C $(DIR_LFT) $@)
		rm -f $(NAME)

re: fclean all
