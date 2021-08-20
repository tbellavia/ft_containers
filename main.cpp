#include "vector.hpp"
#include <vector>
#include <iostream>

# define COLOR_OK "\033[1;32m"
# define COLOR_FAIL "\033[1;31m"
# define COLOR_RESET "\033[1;0m"

template<typename T>
void _assert_equal( const T & actual, const T & expected, const std::string &test_name ) {
	if ( actual == expected ){
		std::cout << test_name << ": " << COLOR_OK << "[OK]" << COLOR_RESET << std::endl;
	} else {
		std::cout << test_name << ": " << COLOR_FAIL << "[FAILED]" << COLOR_RESET << std::endl;
		std::cout << "\t" << "Expected : " << expected << " but got " << actual << std::endl;
	}
}

void test_vector_max_size() {
	std::vector<int> s_vec;
	ft::vector<int> f_vec;

	_assert_equal( f_vec.max_size(), s_vec.max_size(), "test_vector_max_size" );
}

void test_vector_capacity() {
	std::vector<int>	s_vec;
	ft::vector<int>		f_vec;

	_assert_equal( f_vec.capacity(), s_vec.capacity(), "test_vector_default_capacity");

	s_vec.reserve(100);
	f_vec.reserve(100);
	_assert_equal( f_vec.capacity(), s_vec.capacity(), "test_vector_reserve_capacity" );
}

int	main(void){
	test_vector_max_size();
	test_vector_capacity();
}