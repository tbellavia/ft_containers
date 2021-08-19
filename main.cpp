#include "vector.hpp"
#include <vector>
#include <iostream>

int	main(void){
	std::vector<int> std_vec;
	ft::vector<int> ft_vec;

	std_vec.reserve(100);
	std::cout << "Size : " << std_vec.size() << std::endl;
	std::cout << "Capacity : " << std_vec.capacity() << std::endl;

	ft_vec.reserve(100);
	std::cout << "Size : " << ft_vec.size() << std::endl;
	std::cout << "Capacity : " << ft_vec.capacity() << std::endl;
}