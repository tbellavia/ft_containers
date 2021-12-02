CXX = c++
CXXFLAGS = -Wall -Werror -Wextra -std=c++98 -g # -fsanitize=address

SRCS = main.cpp
HEADERS = vector.hpp stack.hpp map.hpp

NAME = ft_containers

all: $(NAME)

$(NAME): $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(SRCS)

re: fclean all

clean: fclean

fclean:
	rm -f $(NAME)