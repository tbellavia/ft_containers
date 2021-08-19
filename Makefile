CLANG = clang++
CFLAGS = -Wall -Werror -Wextra -std=c++98

SRCS = main.cpp
HEADERS = vector.hpp

NAME = ft_containers

all: $(NAME)

$(NAME): $(SRCS) $(HEADERS)
	$(CLANG) $(CFLAGS) -o $(NAME) $(SRCS)

clean: fclean

fclean:
	rm -f $(NAME)