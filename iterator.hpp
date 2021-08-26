#ifndef ITERATOR_HPP
#define ITERATOR_HPP

namespace ft {
	template<class T>
	class random_access_iterator {
		public:
			typedef std::random_access_iterator_tag iterator_category;
			typedef std::size_t						size_type;
			typedef std::ptrdiff_t					difference_type;
			typedef T								value_type;
			typedef T*								pointer;
			typedef T&								reference;

			/* Constructors */
			random_access_iterator() : m_ptr( NULL ) { }
			random_access_iterator(pointer p) : m_ptr( p ) { }
			random_access_iterator(random_access_iterator const &it) : m_ptr( it.m_ptr ) { }
			random_access_iterator &operator=(random_access_iterator const &it) {
				if ( &it == this )
					return *this;
				m_ptr = it.m_ptr;
				return *this;
				}
			~random_access_iterator() {}

			/* Accesses operators */
			reference operator*() const { return *m_ptr; }
			pointer operator->() { return m_ptr; }
			reference operator[](difference_type offset) const { return m_ptr[offset]; }

			/* Increment / Decrement */
			random_access_iterator &operator++() { m_ptr++; return *this; };
			random_access_iterator operator++(int) { random_access_iterator tmp = *this; ++(*this); return tmp; }
			random_access_iterator &operator--() { m_ptr--; return *this; }
			random_access_iterator operator--(int) { random_access_iterator tmp = *this; --(*this); return tmp; }

			/* Arithmetic */
			random_access_iterator &operator+=(difference_type offset) { m_ptr += offset; return *this; }
			random_access_iterator &operator-=(difference_type offset) { m_ptr -= offset; return *this; }
			random_access_iterator operator+(difference_type offset) { return random_access_iterator( m_ptr + offset ); }
			friend random_access_iterator operator+(difference_type offset, const random_access_iterator &it) { return random_access_iterator( it.m_ptr + offset ); }
			random_access_iterator operator-(difference_type offset) { return random_access_iterator( m_ptr - offset ); }
			friend random_access_iterator operator-(difference_type offset, const random_access_iterator &it) { return random_access_iterator( it.m_ptr - offset ); }


			/* Comparison operators */
			bool operator<(random_access_iterator const &it) const { return m_ptr < it.m_ptr; }
			bool operator>(random_access_iterator const &it) const { return m_ptr > it.m_ptr; }
			bool operator>=(random_access_iterator const &it) const { return m_ptr >= it.m_ptr; }
			bool operator<=(random_access_iterator const &it) const { return m_ptr <= it.m_ptr; }
			bool operator!=(random_access_iterator const &it) const { return m_ptr != it.m_ptr; }
			bool operator==(random_access_iterator const &it) const { return m_ptr == it.m_ptr; }
		private:
			pointer									m_ptr;
	};
	
	/**
	 * Iterator traits
	 * 
	 * Iterator traits specialisation for random_access_iterator
	 * 
	 */
	template<typename T>
	struct ft::iterator_traits<random_access_iterator<T> > : ft::true_type {};
}

#endif /* ITERATOR_HPP */
