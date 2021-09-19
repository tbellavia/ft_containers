#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "iterator/vector_iterator.hpp"

namespace ft {
	/**
	 * Iterator traits
	 * 
	 * Iterator traits specialization
	 * 
	 */
	template<typename T>
	struct ft::iterator_traits<ft::_vector::const_random_access_iterator<T> > : ft::true_type {};

	template<typename T>
	struct ft::iterator_traits<ft::_vector::random_access_iterator<T> > : ft::true_type {};

	template<typename T>
	struct ft::iterator_traits<ft::_vector::const_reverse_iterator<T> > : ft::true_type {};

	template<typename T>
	struct ft::iterator_traits<ft::_vector::reverse_iterator<T> > : ft::true_type {};

	template<typename T>
	struct ft::iterator_traits<T*> : ft::true_type {};
}

#endif
