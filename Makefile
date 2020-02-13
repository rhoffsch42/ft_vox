# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/05/15 17:38:19 by rhoffsch          #+#    #+#              #
#    Updated: 2020/02/12 16:55:49 by rhoffsch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	octree
CC				=	g++ -std=c++11
CFLAGS			=	-Wall -Wextra -Werror -MMD -fsanitize=address #-Wpadded

INCLUDE			=	-I ${GLEW_DIR}/include \
					-I ${GLFW_DIR}/include \
					-I $(SGL_DIR)/include \
					-I include


GLEW			=	${GLEW_DIR}/lib/libGLEW.dylib
GLFW			=	${GLFW_DIR}/lib/libglfw.dylib

FRAMEWORKS		=	-framework OpenGL
CC_NEEDS		=	$(FRAMEWORKS) $(GLFW) $(GLEW)

SRC_FILE		=	main.cpp

HDR_FILE		=	octree.h

SRC_DIR			=	src
OBJ_DIR			=	obj
HDR_DIR			=	include
SRC				=	$(addprefix $(SRC_DIR)/, $(SRC_FILE))
OBJ				=	$(patsubst %.cpp, $(OBJ_DIR)/%.o, $(SRC_FILE))
DPD				=	$(patsubst %.cpp, $(OBJ_DIR)/%.d, $(SRC_FILE))
HDR				=	$(addprefix $(HDR_DIR)/, $(HDR_FILE))

DEPENDS			=	$(OBJ:.o=.d)

.PHONY: all clean fclean re tests run

release:
	make -j all

all: $(NAME)
	@echo $(NAME) > .gitignore

$(NAME): $(OBJ)
	@ $(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBS) $(FRAMEWORKS) $(GLFW) $(GLEW)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp Makefile | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re:
	@make fclean
	@make release

run: all
	@echo ""
	./$(NAME)
	@echo ""
	@echo "exitcode: $$?"

-include $(DPD)
