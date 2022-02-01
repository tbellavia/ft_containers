CXX = c++
CXXFLAGS = -Wall -Werror -Wextra -std=c++98

SRCS = test.cpp
HEADERS =	vector.hpp \
			stack.hpp \
			map.hpp \
			./utility/pair.hpp \
			./traits/iterator.hpp \
			./traits/traits.hpp \
			./algorithm/algorithm.hpp


STL_NAME = stl_containers
FT_NAME = ft_containers

 all: $(STL_NAME) $(FT_NAME)

 $(STL_NAME): $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(STL_NAME) $(SRCS)

$(FT_NAME): $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(FT_NAME) -DFT $(SRCS)

re: fclean all

clean: fclean

fclean:
	rm -f $(STL_NAME)
	rm -f $(FT_NAME)