#ifndef MAP_HPP
#define MAP_HPP

# include <functional>
# include <memory>
# include "utility/pair.hpp"

namespace ft
{
	template<
		class Key,												// map::key_type
		class T,												// map::mapped_type
		class Compare = std::less<Key>,							// map::key_compare
		class Alloc = std::allocator<ft::pair<const Key, T> >	// map::allocator_type
	>
	class map {
		public:
			typedef Key										key_type;
			typedef T										mapped_type;
			typedef ft::pair<const key_type, mapped_type>	value_type;
			typedef Compare									key_compare;
			// TODO: Add value_comp
			// typedef value_compare							
			typedef Alloc									allocator_type;
			typedef allocator_type::reference				reference;
			typedef allocator_type::const_reference			const_reference;
			typedef allocator_type::pointer					pointer;
			typedef allocator_type::const_pointer			const_pointer;
			typedef std::ptrdiff_t							difference_type;
			typedef std::size_t								size_type;
	};
}


#endif
