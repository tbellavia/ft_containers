#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "iterator/vector_iterator.hpp"

namespace ft {
	/**
	 * Iterator traits
	 * 
	 * Iterator traits specialisation for random_access_iterator
	 * 
	 */
	template<typename T>
	struct ft::iterator_traits<const_random_access_iterator<T> > : ft::true_type {};

	template<typename T>
	struct ft::iterator_traits<random_access_iterator<T> > : ft::true_type {};

	template<typename T>
	struct ft::iterator_traits<const_reverse_iterator<T> > : ft::true_type {};

	template<typename T>
	struct ft::iterator_traits<reverse_iterator<T> > : ft::true_type {};

	template<typename T>
	struct ft::iterator_traits<T*> : ft::true_type {};
}

#endif
