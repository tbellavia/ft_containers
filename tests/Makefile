CXX = c++
SRCS = time_it.cpp

.PHONY: re clean fclean
.SILENT: all re clean fclean

NAME = time_it

all: $(NAME)

 $(NAME): $(SRCS)
	$(CXX) -o $(NAME) $(SRCS)

re: fclean all

clean: fclean

fclean:
	rm -f $(NAME)