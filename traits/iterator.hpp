#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "iterator/vector_iterator.hpp"
#include "iterator/map_iterator.hpp"

namespace ft {
	/**
	 * Iterator traits
	 * 
	 * Iterator traits specialization
	 * 
	 */
	template<typename T>
	struct ft::iterator_traits<ft::vector_::const_random_access_iterator<T> > : ft::true_type {};

	template<typename T>
	struct ft::iterator_traits<ft::vector_::random_access_iterator<T> > : ft::true_type {};

	template<typename T>
	struct ft::iterator_traits<ft::vector_::const_reverse_iterator<T> > : ft::true_type {};

	template<typename T>
	struct ft::iterator_traits<ft::vector_::reverse_iterator<T> > : ft::true_type {};

	template<typename T>
	struct ft::iterator_traits<ft::map_::const_bidirectional_iterator<T> > : ft::true_type {};

	template<typename T>
	struct ft::iterator_traits<ft::map_::bidirectional_iterator<T> > : ft::true_type {};

	template<typename T>
	struct ft::iterator_traits<ft::map_::const_reverse_iterator<T> > : ft::true_type {};

	template<typename T>
	struct ft::iterator_traits<ft::map_::reverse_iterator<T> > : ft::true_type {};

	template<typename T>
	struct ft::iterator_traits<T*> : ft::true_type {};
}

#endif
