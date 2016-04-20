CC= gcc
FLAGS=-Wall -Wextra -I./includes/ -I./includes/GLFW -g -DGLFW_USE_CHDIR=0
NAME=scop 

SRC= main.c \
	 callback.c \
	 gl_context.c \
	 matrix.c \
	 parsing.c \
	 bmp_import.c \
	 shader.c

OBJ= $(SRC:.c=.o)

INC=  -I libft/includes
LIB=  -L./libs/ -lglad -lglfw3 -L libft -lft

FRWK=   -framework AGL \
		-framework Cocoa \
		-framework OpenGL \
		-framework IOKit \
		-framework CoreFoundation \
		-framework CoreVideo \
		-framework OpenCL

.PHONY: clean fclean re
.SILENT:

all:$(NAME) 

$(NAME): $(OBJ)
		$(CC) -o $(NAME) $(OBJ) $(LIB) $(FRWK) $(INC) $(FLAGS)
		echo "\t\xF0\x9F\x8F\x81   Compiling \033[35m$(NAME) \033[0mDONE!"

%.o: %.c
		echo "\t\xF0\x9F\x94\xA7   Building \033[34m $@ \033[0m" 
		$(CC) -c $(FLAGS) $(INC) -o $@ $<

clean:
		echo "\t\xF0\x9F\x92\xA3   Cleaning"
		rm -rf $(OBJ)

fclean: clean
		echo "\t\xF0\x9F\x9A\xBD   Full Clean"
		rm -rf $(NAME)

re: fclean all
