#ifndef TRAITS_HPP
#define TRAITS_HPP

namespace ft {
	template<bool B, class T = void>
	struct enable_if { };

	template<class T>
	struct enable_if<true, T> {
		typedef T type;
	};

	struct true_type {
		static const bool value = true;
	};

	struct false_type {
		static const bool value = false;
	};

	template<typename T>
	struct iterator_traits : ft::false_type { };
}

#endif /* TRAITS_HPP */
