#include "vector.hpp"
#include <vector>
#include <iostream>
#include <stdlib.h>

# define COLOR_OK "\033[1;32m"
# define COLOR_FAIL "\033[1;31m"
# define COLOR_RESET "\033[1;0m"

template<typename T>
void _report_error( T const &actual, T const &expected, std::string const &test_name ){
	std::cout << test_name << ": " << COLOR_FAIL << "[FAILED]" << COLOR_RESET << std::endl;
	std::cout << "\t" << "Expected : `" << expected << "` but got `" << actual << "`" << std::endl;
}

void _report_error( std::string const &message, std::string const &test_name ){
	std::cout << test_name << ": " << COLOR_FAIL << "[FAILED]" << COLOR_RESET << std::endl;
	std::cout << "\t" << message << std::endl;
}

void _report_success( std::string const &test_name ){
	std::cout << test_name << ": " << COLOR_OK << "[OK]" << COLOR_RESET << std::endl;
}

template<typename T>
void _assert_equal( const T & actual, const T & expected, const std::string &test_name ) {
	if ( actual == expected ){
		_report_success( test_name );
	} else {
		_report_error( actual, expected, test_name );
	}
}

template<typename InputIt, typename OutputIt>
void _assert_each_equal( InputIt actual_first, InputIt actual_last, 
							OutputIt expected_first, OutputIt expected_last, std::string const &test_name ){
	for ( ; actual_first != actual_last && expected_first != expected_last ; actual_first++, expected_first++ ){
		if ( *actual_first != *expected_first ){
			_report_error( *actual_first, *actual_last, test_name );
		}
	}
	if ( actual_first != actual_last || expected_first != expected_last ){
		_report_error("The size differ", test_name);
		return ;
	}
	_report_success( test_name );
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

	_assert_each_equal(f_vec.begin(), f_vec.end(), s_vec.begin(), s_vec.end(), "test vector resize");
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

	_assert_each_equal(f_vec.begin(), f_vec.end(), s_vec.begin(), s_vec.end(), "test vector iterator");
}

void test_vector_pop_back(){
	std::vector<int>::iterator std_it;
	ft::vector<int>::iterator ft_it;
	std::vector<int>	s_vec;
	ft::vector<int>		f_vec;

	s_vec.push_back(10);
	f_vec.push_back(10);

	s_vec.pop_back();
	f_vec.pop_back();
	_assert_equal(f_vec.size(), s_vec.size(), "test vector pop back size");
	_assert_equal(f_vec.capacity(), s_vec.capacity(), "test vector pop back capacity");

	for ( int i = 0 ; i < 10 ; i++){
		s_vec.push_back(i);
		f_vec.push_back(i);
	}

	s_vec.pop_back();
	f_vec.pop_back();
	_assert_equal(f_vec.size(), s_vec.size(), "test vector pop back size");
	_assert_equal(f_vec.capacity(), s_vec.capacity(), "test vector pop back capacity");
	_assert_each_equal(f_vec.begin(), f_vec.end(), s_vec.begin(), s_vec.end(), "test vector pop back items");
}

void test_vector_clear(){
	std::vector<int>	s_vec;
	ft::vector<int>		f_vec;

	s_vec.resize(20, 10);
	f_vec.resize(20, 10);

	_assert_equal(s_vec.size(), f_vec.size(), "test vector clear size");
	_assert_equal(s_vec.capacity(), f_vec.capacity(), "test vector clear capacity");
}

void test_vector_assign(){
	std::vector<int>::iterator std_it;
	ft::vector<int>::iterator ft_it;
	std::vector<int>	s_vec;
	ft::vector<int>		f_vec;

	f_vec.assign(10, 1);
	s_vec.assign(10, 1);
	_assert_equal(f_vec.size(), s_vec.size(), "test vector assign size");
	_assert_equal(f_vec.capacity(), s_vec.capacity(), "test vector assign capacity");
	_assert_each_equal(f_vec.begin(), f_vec.end(), s_vec.begin(), s_vec.end(), "test vector items");
}

int	main(void){
	test_vector_max_size();
	test_vector_capacity();
	test_vector_resize();
	test_vector_iterator();
	test_vector_pop_back();
	test_vector_clear();
	test_vector_assign();
}