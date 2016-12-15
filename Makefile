##
## Makefile for Makefile in /home/mcnama_d/code
##
## Made by Duncan McNAMARA
## Login   <mcnama_d@epitech.net>
##
## Started on  Tue Jan  6 23:34:58 2015 Duncan McNAMARA
## Last update Sat Jun 13 22:23:35 2015 Quentin Richard
##

SRC		=	src/main.cpp		\
			src/Error.cpp		\
			src/AEntity.cpp		\
			src/Character.cpp	\
			src/Save.cpp		\
			src/Box.cpp		\
			src/Bonus.cpp		\
			src/Thread.cpp		\
			src/Mutex.cpp		\
			src/Map.cpp		\
			src/MapFunctions.cpp	\
			src/Menu.cpp		\
			src/CondVar.cpp		\
			src/MenuLvls.cpp	\
			src/Process.cpp		\
			src/Texture.cpp		\
			src/GameEngine.cpp	\
			src/GraphEngine.cpp	\
			src/Music.cpp		\
			src/Sound.cpp		\
			src/ThreadPool.cpp	\
			src/Work.cpp		\
			src/Explosion.cpp	\
			src/EditBox.cpp		\
			src/EditEngine.cpp	\
			src/Bomb.cpp		\
			src/Police.cpp		\
			src/Ai.cpp


XML_LIB		=	xml/tinystr.cpp		\
			xml/tinyxml.cpp		\
			xml/tinyxmlerror.cpp	\
			xml/tinyxmlparser.cpp

OBJ		=	$(SRC:.cpp=.o)

OBJ_ARM		=	$(SRC_ARM:.c=.o)

OBJ_XML		=	$(XML_LIB:.cpp=.o)

RM		=	rm -f

CXX		=	clang++

LIBFLAGS	=	-L../LibBomberman_linux_x64/libs -lgdl_gl -lGL -ldl -lrt -lm -lfbxsdk -lSDL2 -lpthread -lGLEW -lsfml-audio -ldl

CXXFLAGS	=	-I../LibBomberman_linux_x64/includes -Iinc -Ixml -std=c++11 -W -Wextra -Wall -g3

EXPORT 		=	export LD_LIBRARY_PATH=./../LibBomberman_linux_x64/libs/

NAME		=	bomberman

all		:	$(NAME)

$(NAME)		:	$(OBJ_XML) $(OBJ)
			$(CXX) $(OBJ_XML) $(OBJ) $(LIBFLAGS) -o $(NAME) $(XMLFLAGS)
			$(EXPORT)

clean		:
			$(RM) $(OBJ) $(OBJ_ARM) $(OBJ_XML)

fclean		:	clean
			$(RM) $(NAME)

re		:	fclean all

.PHONY		: 	all clean fclean re
