CC= gcc
FLAGS=-Wall -Wextra -Werror -g
NAME=scop 

SRC= src/main.c \
	 src/callback.c \
	 src/gl_context.c \
	 src/matrix.c \
	 src/matrix_operation.c \
	 src/matrix_transformation.c \
	 src/obj_import.c \
	 src/obj_import_init.c \
	 src/obj_import_utils.c \
	 src/bmp_import.c \
	 src/utils.c \
	 src/shader.c

OBJ= $(SRC:.c=.o)

INC=  -I includes -I includes/GLFW -I libft/includes -I src/includes
LIB=  -L libs/ -lglad -lglfw3 -L libft -lft

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
		$(CC) -o $(NAME) $(OBJ) $(LIB) $(FRWK)
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
