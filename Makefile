CLANG = clang++
CFLAGS = -Wall -Werror -Wextra -g # -std=c++98 -fsanitize=address

SRCS = main.cpp
HEADERS = vector.hpp

NAME = ft_containers

all: $(NAME)

$(NAME): $(SRCS) $(HEADERS)
	$(CLANG) $(CFLAGS) -o $(NAME) $(SRCS)

re: fclean all

clean: fclean

fclean:
	rm -f $(NAME)