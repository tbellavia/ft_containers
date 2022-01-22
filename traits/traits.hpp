#ifndef TRAITS_HPP
#define TRAITS_HPP

namespace ft {	
	template<bool B, class T = void>
	struct enable_if { };

	template<class T>
	struct enable_if<true, T> {
		typedef T type;
	};

	/**
	 * True type
	 * 
	 * Define the value true within the true_type struct.
	 * 
	 */
	struct true_type {
		static const bool value = true;
	};

	/**
	 * False type
	 * 
	 * Define the value false within the false_type struct.
	 * 
	 */
	struct false_type {
		static const bool value = false;
	};

	/**
	 * Iterator traits
	 * 
	 * Define a traits for iterators.
	 * 
	 */
	template<typename Iterator>
	struct iterator_traits {
		typedef typename Iterator::iterator_category	iterator_category;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
	};

	template<typename T>
	struct iterator_traits<T*> {
		typedef std::random_access_iterator_tag	iterator_category;
		typedef T								value_type;
		typedef ptrdiff_t						difference_type;
		typedef T*								pointer;
		typedef T&								reference;
	};

	template<typename T>
	struct iterator_traits<const T*> {
		typedef std::random_access_iterator_tag	iterator_category;
		typedef T								value_type;
		typedef ptrdiff_t						difference_type;
		typedef const T*						pointer;
		typedef const T&						reference;
	};

	/**
	 * Is iterator
	 * 
	 * Define a way to check if it is iterator
	 */
	template<typename T>
	struct is_iterator : ft::false_type { };
}

#endif /* TRAITS_HPP */
