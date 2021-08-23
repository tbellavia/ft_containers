#include "vector.hpp"
#include <vector>
#include <iostream>
#include <stdlib.h>

# define COLOR_OK "\033[1;32m"
# define COLOR_FAIL "\033[1;31m"
# define COLOR_RESET "\033[1;0m"

template<typename T>
void _assert_equal( const T & actual, const T & expected, const std::string &test_name ) {
	if ( actual == expected ){
		std::cout << test_name << ": " << COLOR_OK << "[OK]" << COLOR_RESET << std::endl;
	} else {
		std::cout << test_name << ": " << COLOR_FAIL << "[FAILED]" << COLOR_RESET << std::endl;
		std::cout << "\t" << "Expected : `" << expected << "` but got `" << actual << "`" << std::endl;
		exit(EXIT_FAILURE);
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

void test_vector_resize(){
	std::vector<int>::iterator std_it;
	ft::vector<int>::iterator ft_it;
	std::vector<int>	s_vec;
	ft::vector<int>		f_vec;

	for ( int index = 0 ; index < 5 ; index++ ){
		f_vec.push_back(index);
		s_vec.push_back(index);
	}

	f_vec.resize(2, 10);
	s_vec.resize(2, 10);
	_assert_equal(f_vec.size(), s_vec.size(), "test vector resize size");
	_assert_equal(f_vec.capacity(), s_vec.capacity(), "test vector resize capacity");

	f_vec.resize(20, 10);
	s_vec.resize(20, 10);
	_assert_equal(f_vec.size(), s_vec.size(), "test vector resize size");
	_assert_equal(f_vec.capacity(), s_vec.capacity(), "test vector resize capacity");

	for ( 
		ft_it = f_vec.begin(), std_it = s_vec.begin() ; ft_it != f_vec.end() || std_it != s_vec.end() ; 
		ft_it++, std_it++ ){
		_assert_equal(*ft_it, *std_it, "test vector resize");
	}
}

void test_vector_iterator(){
	std::vector<int>::iterator std_it;
	ft::vector<int>::iterator ft_it;
	std::vector<int>	s_vec;
	ft::vector<int>		f_vec;

	
	for ( int i = 0 ; i < 10 ; i++){
		s_vec.push_back(i);
		f_vec.push_back(i);
	}


	for ( 
		ft_it = f_vec.begin(), std_it = s_vec.begin() ; ft_it != f_vec.end() || std_it != s_vec.end() ; 
		ft_it++, std_it++ ){
		_assert_equal(*ft_it, *std_it, "test vector iterator");
	}
}

int	main(void){
	test_vector_max_size();
	test_vector_capacity();
	test_vector_resize();
	test_vector_iterator();
}