#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iterator>
#include "iterator/vector_iterator.hpp"
#include "iterator/map_iterator.hpp"

namespace ft {
	// Remove const qualifier
	template<typename T>
	struct remove_cv {
		typedef T	type;
	};


	template<typename T>
	struct remove_cv<const T> {
		typedef T	type;
	};

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
	struct ft::iterator_traits<T*> : ft::true_type {
		typedef iterator::random_access_iterator_tag	iterator_category;
		typedef T										value_type;
		typedef ptrdiff_t								difference_type;
		typedef T*										pointer;
		typedef T&										reference;
	};

	template<typename T>
	struct ft::iterator_traits<const T*> : ft::true_type {
		typedef iterator::random_access_iterator_tag	iterator_category;
		typedef T										value_type;
		typedef ptrdiff_t								difference_type;
		typedef const T*								pointer;
		typedef const T&								reference;
	};
}

#endif
