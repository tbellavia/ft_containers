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
	struct iterator_traits<vector_::const_random_access_iterator<T> > : true_type {};

	template<typename T>
	struct iterator_traits<vector_::random_access_iterator<T> > : true_type {};

	template<typename T>
	struct iterator_traits<vector_::const_reverse_iterator<T> > : true_type {};

	template<typename T>
	struct iterator_traits<vector_::reverse_iterator<T> > : true_type {};

	template<typename T>
	struct iterator_traits<map_::const_bidirectional_iterator<T> > : true_type {};

	template<typename T>
	struct iterator_traits<map_::bidirectional_iterator<T> > : true_type {};

	template<typename T>
	struct iterator_traits<map_::const_reverse_iterator<T> > : true_type {};

	template<typename T>
	struct iterator_traits<map_::reverse_iterator<T> > : true_type {};

	template<typename T>
	struct iterator_traits<T*> : true_type {};
}

#endif
