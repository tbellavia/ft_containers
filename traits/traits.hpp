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
	template<typename T>
	struct iterator_traits : ft::false_type { };
}

#endif /* TRAITS_HPP */
