CXX = c++
CXXFLAGS = -Wall -Werror -Wextra -std=c++98 -g # -fsanitize=address

#SRCS = main.cpp
SRCS = test.cpp
HEADERS = vector.hpp stack.hpp map.hpp

STL_NAME = stl_containers
FT_NAME = ft_containers

all: $(STL_NAME)

$(STL_NAME) $(FT_NAME): $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(STL_NAME) $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(FT_NAME) -DFT $(SRCS)

re: fclean all

clean: fclean

fclean:
	rm -f $(STL_NAME)
	rm -f $(FT_NAME)