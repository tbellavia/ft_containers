#include "vector.hpp"
#include <vector>
#include <iostream>
#include <stdlib.h>

# define COLOR_OK "\033[1;32m"
# define COLOR_FAIL "\033[1;31m"
# define COLOR_RESET "\033[1;0m"


template<typename T>
void _report_failure( T const &actual, T const &expected, std::string const &test_name ){
	std::cout << COLOR_FAIL << "[FAIL] " << COLOR_RESET << ": " << test_name << std::endl;
	std::cout << "\t" << "Expected : `" << expected << "` but got `" << actual << "`" << std::endl;
}

void _report_failure( std::string const &message, std::string const &test_name ){
	std::cout << COLOR_FAIL << "[FAIL] " << COLOR_RESET << ": " << test_name << std::endl;
	std::cout << "\t" << message << std::endl;
}

void _report_success( std::string const &test_name ){
	std::cout << COLOR_OK << "[OK] " << COLOR_RESET << ": " << test_name << std::endl;
}

template<typename T>
void _assert_equal( const T & actual, const T & expected, const std::string &test_name ) {
	if ( actual == expected ){
		_report_success( test_name );
	} else {
		_report_failure( actual, expected, test_name );
	}
}

template<typename InputIt, typename OutputIt>
void _assert_each_equal( InputIt actual_first, InputIt actual_last, 
							OutputIt expected_first, OutputIt expected_last, std::string const &test_name ){
	
	bool error = false;

	for ( ; actual_first != actual_last && expected_first != expected_last ; actual_first++, expected_first++ ){
		if ( *actual_first != *expected_first ){
			_report_failure( *actual_first, *expected_first, test_name );
			error = true;
		}
	}
	if ( !error ){
		if ( actual_first != actual_last || expected_first != expected_last ){
			_report_failure("The size differ", test_name);
		} else {
			_report_success( test_name );
		}
	}
}

# define TEST_EACH_EQUAL(actual, expected, name) _assert_each_equal(actual.begin(), actual.end(), expected.begin(), expected.end(), name)

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
	std::vector<int>	s_fill;
	ft::vector<int>		f_fill;
	int fill[] = {1, 2, 3, 4, 5, 6};
	std::vector<int>	s_vec;
	ft::vector<int>		f_vec;
	
	for ( std::vector<int>::size_type index = 0 ; index < 10 ; index++ ){
		s_fill.push_back( index + 1 );
		f_fill.push_back( index + 1 );
	}

	f_vec.assign(10, 1);
	s_vec.assign(10, 1);
	_assert_equal(f_vec.size(), s_vec.size(), "test vector assign (fill) size");
	_assert_equal(f_vec.capacity(), s_vec.capacity(), "test vector assign (fill) capacity");
	_assert_each_equal(f_vec.begin(), f_vec.end(), s_vec.begin(), s_vec.end(), "test vector assign (fill) items");

	f_vec.assign(20, 5);
	s_vec.assign(20, 5);
	_assert_equal(f_vec.size(), s_vec.size(), "test vector assign (fill) size");
	_assert_equal(f_vec.capacity(), s_vec.capacity(), "test vector assign (fill) capacity");
	_assert_each_equal(f_vec.begin(), f_vec.end(), s_vec.begin(), s_vec.end(), "test vector assign (fill) items");

	f_vec.assign(5, 42);
	s_vec.assign(5, 42);
	_assert_equal(f_vec.size(), s_vec.size(), "test vector assign (fill) size");
	_assert_equal(f_vec.capacity(), s_vec.capacity(), "test vector assign (fill) capacity");
	_assert_each_equal(f_vec.begin(), f_vec.end(), s_vec.begin(), s_vec.end(), "test vector assign (fill) items");

	f_vec.assign( fill, fill + 6 );
	s_vec.assign( fill, fill + 6 );
	_assert_equal(f_vec.size(), s_vec.size(), "test vector assign (range) pointer size");
	_assert_equal(f_vec.capacity(), s_vec.capacity(), "test vector assign (range) pointer capacity");
	_assert_each_equal(f_vec.begin(), f_vec.end(), s_vec.begin(), s_vec.end(), "test vector assign (range) pointer items");

	f_vec.assign( f_fill.begin(), f_fill.end() );
	s_vec.assign( s_fill.begin(), s_fill.end() );
	_assert_equal(f_vec.size(), s_vec.size(), "test vector assign (range) iterator size");
	_assert_equal(f_vec.capacity(), s_vec.capacity(), "test vector assign (range) iterator capacity");
	_assert_each_equal(f_vec.begin(), f_vec.end(), s_vec.begin(), s_vec.end(), "test vector assign (range) iterator items");
}

void test_vector_insert(){
	{
		ft::vector<int>::iterator it;
		std::vector<int>	s_vec;
		ft::vector<int>		f_vec;

		// Reallocation
		it = f_vec.insert(f_vec.begin(), 42);
		s_vec.insert(s_vec.begin(), 42);
		_assert_each_equal(f_vec.begin(), f_vec.end(), s_vec.begin(), s_vec.end(), "test vectir insert items");
		_assert_equal(f_vec.capacity(), s_vec.capacity(), "test vector insert capacity");
		_assert_equal(f_vec.size(), s_vec.size(), "test vector insert size");
		_assert_equal(*it, 42, "test vector insert iterator");

		s_vec.assign(20, 5);
		f_vec.assign(20, 5);

		it = f_vec.insert(f_vec.begin(), 10);
		s_vec.insert(s_vec.begin(), 10);

		// Begin
		_assert_each_equal(f_vec.begin(), f_vec.end(), s_vec.begin(), s_vec.end(), "test vector insert items");
		_assert_equal(f_vec.capacity(), s_vec.capacity(), "test vector insert capacity");
		_assert_equal(f_vec.size(), s_vec.size(), "test vector insert size");
		_assert_equal(*it, 10, "test vector insert iterator");

		// End
		it = f_vec.insert(f_vec.end(), 100);
		s_vec.insert(s_vec.end(), 100);

		_assert_each_equal(f_vec.begin(), f_vec.end(), s_vec.begin(), s_vec.end(), "test vector insert items");
		_assert_equal(f_vec.capacity(), s_vec.capacity(), "test vector insert capacity");
		_assert_equal(f_vec.size(), s_vec.size(), "test vector insert size");
		_assert_equal(*it, 100, "test vector insert iterator");

		// Middle
		it = f_vec.insert(f_vec.begin() + (f_vec.size() / 2), 1000);
		s_vec.insert(s_vec.begin() + (s_vec.size() / 2), 1000);

		_assert_each_equal(f_vec.begin(), f_vec.end(), s_vec.begin(), s_vec.end(), "test vector insert items");
		_assert_equal(f_vec.capacity(), s_vec.capacity(), "test vector insert capacity");
		_assert_equal(f_vec.size(), s_vec.size(), "test vector insert size");
		_assert_equal(*it, 1000, "test vector insert iterator");
	}
	{
		std::vector<int>	s_vec;
		ft::vector<int>		f_vec;

		// Reallocation

		/**
		 * FIXME: Invalid pointer for iterator when ft::vec is default constructed.
		 * 
		 */
		f_vec.insert(f_vec.begin(), 10, 42);
		s_vec.insert(s_vec.begin(), 10, 42);
		_assert_each_equal(f_vec.begin(), f_vec.end(), s_vec.begin(), s_vec.end(), "test vector insert items");
		_assert_equal(f_vec.capacity(), s_vec.capacity(), "test vector insert capacity");
		_assert_equal(f_vec.size(), s_vec.size(), "test vector insert size");

		// Begin
		f_vec.insert(f_vec.begin(), 10, 142);
		s_vec.insert(s_vec.begin(), 10, 142);
		_assert_each_equal(f_vec.begin(), f_vec.end(), s_vec.begin(), s_vec.end(), "test vector insert items");
		_assert_equal(f_vec.capacity(), s_vec.capacity(), "test vector insert capacity");
		_assert_equal(f_vec.size(), s_vec.size(), "test vector insert size");
		
		// End
		f_vec.insert(f_vec.begin() + (f_vec.size() / 2), 10, 142);
		s_vec.insert(s_vec.begin() + (s_vec.size() / 2), 10, 142);
		_assert_each_equal(f_vec.begin(), f_vec.end(), s_vec.begin(), s_vec.end(), "test vector insert items");
		_assert_equal(f_vec.capacity(), s_vec.capacity(), "test vector insert capacity");
		_assert_equal(f_vec.size(), s_vec.size(), "test vector insert size");

		// Middle
		f_vec.insert(f_vec.begin() + (f_vec.size() / 2), 10, 142);
		s_vec.insert(s_vec.begin() + (s_vec.size() / 2), 10, 142);
		_assert_each_equal(f_vec.begin(), f_vec.end(), s_vec.begin(), s_vec.end(), "test vector insert items");
		_assert_equal(f_vec.capacity(), s_vec.capacity(), "test vector insert capacity");
		_assert_equal(f_vec.size(), s_vec.size(), "test vector insert size");
	}
	{
		int fill[]			= {1, 2, 3, 4, 5, 6};
		int fill2[]			= {6, 5, 4, 3, 2, 1};

		std::vector<int>	s_vec;
		std::vector<int>	vec;
		ft::vector<int>		f_vec;

		// Reallocation
		f_vec.insert(f_vec.begin(), fill, fill + 6);
		s_vec.insert(s_vec.begin(), fill, fill + 6);

		_assert_each_equal(f_vec.begin(), f_vec.end(), s_vec.begin(), s_vec.end(), "test vector insert items");
		_assert_equal(f_vec.capacity(), s_vec.capacity(), "test vector insert capacity");
		_assert_equal(f_vec.size(), s_vec.size(), "test vector insert size");

		// Begin
		f_vec.insert(f_vec.begin(), fill2, fill2 + 6);
		s_vec.insert(s_vec.begin(), fill2, fill2 + 6);

		_assert_each_equal(f_vec.begin(), f_vec.end(), s_vec.begin(), s_vec.end(), "test vector insert items");
		_assert_equal(f_vec.capacity(), s_vec.capacity(), "test vector insert capacity");
		_assert_equal(f_vec.size(), s_vec.size(), "test vector insert size");

		// End
		f_vec.insert(f_vec.end(), fill, fill + 6);
		s_vec.insert(s_vec.end(), fill, fill + 6);

		_assert_each_equal(f_vec.begin(), f_vec.end(), s_vec.begin(), s_vec.end(), "test vector insert items");
		_assert_equal(f_vec.capacity(), s_vec.capacity(), "test vector insert capacity");
		_assert_equal(f_vec.size(), s_vec.size(), "test vector insert size");

		// Middle
		f_vec.insert(f_vec.begin() + (f_vec.size() / 2), fill2, fill2 + 6);
		s_vec.insert(s_vec.begin() + (s_vec.size() / 2), fill2, fill2 + 6);

		_assert_each_equal(f_vec.begin(), f_vec.end(), s_vec.begin(), s_vec.end(), "test vector insert items");
		_assert_equal(f_vec.capacity(), s_vec.capacity(), "test vector insert capacity");
		_assert_equal(f_vec.size(), s_vec.size(), "test vector insert size");

		// Fill empty
		f_vec.insert(f_vec.begin(), fill, fill);
		s_vec.insert(s_vec.begin(), fill, fill);

		_assert_each_equal(f_vec.begin(), f_vec.end(), s_vec.begin(), s_vec.end(), "test vector insert items");
		_assert_equal(f_vec.capacity(), s_vec.capacity(), "test vector insert capacity");
		_assert_equal(f_vec.size(), s_vec.size(), "test vector insert size");
		
	}
}

void test_vector_erase(){
	typedef std::vector<int>::iterator std_iterator;
	typedef ft::vector<int>::iterator ft_iterator;
	std_iterator		s_it;
	ft_iterator			f_it;

	{
		ft::vector<int>		f_vec;
		std::vector<int>	s_vec;

		for ( int i = 0 ; i < 100 ; i++ ){
			f_vec.push_back(i);
			s_vec.push_back(i);
		}

		// Begin
		f_it = f_vec.erase(f_vec.begin());
		s_it = s_vec.erase(s_vec.begin());

		TEST_EACH_EQUAL(f_vec, s_vec, "test vector erase - items");
		_assert_equal(f_vec.size(), s_vec.size(), "test vector erase - size");
		_assert_equal(f_vec.capacity(), s_vec.capacity(), "test vector erase - capacity");
		_assert_equal(*f_it, *s_it, "test vector erase - iterator");

		// End
		f_it = f_vec.erase(f_vec.end() - 1);
		s_it = s_vec.erase(s_vec.end() - 1);

		TEST_EACH_EQUAL(f_vec, s_vec, "test vector erase - items");
		_assert_equal(f_vec.size(), s_vec.size(), "test vector erase - size");
		_assert_equal(f_vec.capacity(), s_vec.capacity(), "test vector erase - capacity");
		_assert_equal(*f_it, *s_it, "test vector erase - iterator");
		
		// Middle
		f_it = f_vec.erase(f_vec.begin() + (f_vec.size() / 2));
		s_it = s_vec.erase(s_vec.begin() + (s_vec.size() / 2));

		TEST_EACH_EQUAL(f_vec, s_vec, "test vector erase - items");
		_assert_equal(f_vec.size(), s_vec.size(), "test vector erase - size");
		_assert_equal(f_vec.capacity(), s_vec.capacity(), "test vector erase - capacity");
		_assert_equal(*f_it, *s_it, "test vector erase - iterator");
	}
	{
		ft::vector<int>		f_vec;
		std::vector<int>	s_vec;

		for ( int i = 0 ; i < 100 ; i++ ){
			f_vec.push_back(i);
			s_vec.push_back(i);
		}

		// Begin
		f_it = f_vec.erase(f_vec.begin(), f_vec.begin() + 10);
		s_it = s_vec.erase(s_vec.begin(), s_vec.begin() + 10);

		TEST_EACH_EQUAL(f_vec, s_vec, "test vector erase - items");
		_assert_equal(f_vec.size(), s_vec.size(), "test vector erase - size");
		_assert_equal(f_vec.capacity(), s_vec.capacity(), "test vector erase - capacity");
		_assert_equal(*f_it, *s_it, "test vector erase - iterator");

		// End
		f_it = f_vec.erase(f_vec.end() - 10, f_vec.end());
		s_it = s_vec.erase(s_vec.end() - 10, s_vec.end());

		TEST_EACH_EQUAL(f_vec, s_vec, "test vector erase - items");
		_assert_equal(f_vec.size(), s_vec.size(), "test vector erase - size");
		_assert_equal(f_vec.capacity(), s_vec.capacity(), "test vector erase - capacity");
		_assert_equal(*f_it, *s_it, "test vector erase - iterator");
		
		// Middle
		f_it = f_vec.erase(f_vec.begin() + (f_vec.size() / 2), f_vec.begin() + (f_vec.size() / 2) + 10);
		s_it = s_vec.erase(s_vec.begin() + (s_vec.size() / 2), s_vec.begin() + (s_vec.size() / 2) + 10);

		TEST_EACH_EQUAL(f_vec, s_vec, "test vector erase - items");
		_assert_equal(f_vec.size(), s_vec.size(), "test vector erase - size");
		_assert_equal(f_vec.capacity(), s_vec.capacity(), "test vector erase - capacity");
		_assert_equal(*f_it, *s_it, "test vector erase - iterator");

		// Zero erase
		f_it = f_vec.erase(f_vec.begin(), f_vec.begin());
		s_it = s_vec.erase(s_vec.begin(), s_vec.begin());

		TEST_EACH_EQUAL(f_vec, s_vec, "test vector erase - items");
		_assert_equal(f_vec.size(), s_vec.size(), "test vector erase - size");
		_assert_equal(f_vec.capacity(), s_vec.capacity(), "test vector erase - capacity");
		_assert_equal(*f_it, *s_it, "test vector erase - iterator");
	}
}

void test_vector_access(){
	ft::vector<int>		f_vec;
	std::vector<int>	s_vec;

	for ( int i = 0 ; i < 5 ; i++ ){
		f_vec.push_back(i);
		s_vec.push_back(i);
	}

	for ( int i = 0 ; i < 5 ; i++ ){
		_assert_equal(f_vec[i], s_vec[i], "test vector operator[]");
	}

	// Front

	_assert_equal(f_vec.front(), s_vec.front(), "test vector front - value");
	_assert_equal(&f_vec.front(), &f_vec[0], "test vector front - pointer");

	// Back
	_assert_equal(f_vec.back(), s_vec.back(), "test vector back - value");
	_assert_equal(&f_vec.back(), &f_vec[f_vec.size() - 1], "test vector back - pointer");
}

void test_vector_at(){
	ft::vector<int>		f_vec;
	std::vector<int>	s_vec;

	for ( int i = 0 ; i < 5 ; i++ ){
		f_vec.push_back(i);
		s_vec.push_back(i);
	}

	for ( int i = 0 ; i < 5 ; i++ ){
		_assert_equal(f_vec.at(i), s_vec.at(i), "test vector at - items");
	}
	try {
		f_vec.at(f_vec.size());
		_report_failure("at() does not throw any exception", "test vector at");
	} catch ( std::out_of_range &e ){
		_report_success("test vector at - exception");
	}
}

int	main(void){
	test_vector_max_size();
	test_vector_capacity();
	test_vector_resize();
	test_vector_iterator();
	test_vector_pop_back();
	test_vector_clear();
	test_vector_assign();
	test_vector_insert();
	test_vector_erase();
	test_vector_access();
	test_vector_at();
}