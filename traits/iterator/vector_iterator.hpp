#ifndef _FT_VECTOR_ITERATOR_HPP_
#define _FT_VECTOR_ITERATOR_HPP_

namespace ft {
	namespace vector_ {
		template<class T>
		class iterator;

		template<class T>
		class const_iterator {
			private:
				typedef ft::iterator_traits<T>						_traits_type;
			public:
				typedef typename _traits_type::iterator_category	iterator_category;
				typedef typename _traits_type::value_type			value_type;
				typedef typename _traits_type::difference_type		difference_type;
				typedef typename _traits_type::reference			reference;
				typedef typename _traits_type::pointer				pointer;

				/* Constructors */
				const_iterator() : m_ptr( NULL ) { }
				const_iterator(pointer p) : m_ptr( p ) { }
				const_iterator(const_iterator const &it) : m_ptr( it.m_ptr ) { }
				const_iterator(iterator<T> const &it) : m_ptr( it.operator->() ) { }
				const_iterator &operator=(const_iterator const &it) {
					if ( &it == this )
						return *this;
					m_ptr = it.m_ptr;
					return *this;
				}
				~const_iterator() {}

				/* Accesses operators */
				value_type base() const { return m_ptr; }
				reference operator*() const { return *m_ptr; }
				pointer operator->() { return m_ptr; }
				pointer operator->() const { return m_ptr; }
				reference operator[](difference_type offset) const { return m_ptr[offset]; }

				/* Increment / Decrement */
				const_iterator &operator++() { m_ptr++; return *this; };
				const_iterator operator++(int) { const_iterator tmp = *this; ++(*this); return tmp; }
				const_iterator &operator--() { m_ptr--; return *this; }
				const_iterator operator--(int) { const_iterator tmp = *this; --(*this); return tmp; }

				/* Arithmetic */
				const_iterator &operator+=(difference_type offset) { m_ptr += offset; return *this; }
				const_iterator &operator-=(difference_type offset) { m_ptr -= offset; return *this; }
				
				const_iterator operator+(difference_type offset) { return const_iterator( m_ptr + offset ); }
				friend const_iterator operator+(difference_type offset, const const_iterator &it) { return const_random_access_iterator( it.m_ptr + offset ); }

				const_iterator operator-(difference_type offset) { return const_iterator( m_ptr - offset ); }
				friend const_iterator operator-(difference_type offset, const const_iterator &it) { return const_random_access_iterator( it.m_ptr - offset ); }
				difference_type operator-(const_iterator other) { return m_ptr - other.m_ptr; }


				/* Comparison operators */
				bool operator<(const_iterator const &it) const { return m_ptr < it.m_ptr; }
				bool operator>(const_iterator const &it) const { return m_ptr > it.m_ptr; }
				bool operator>=(const_iterator const &it) const { return m_ptr >= it.m_ptr; }
				bool operator<=(const_iterator const &it) const { return m_ptr <= it.m_ptr; }
				bool operator!=(const_iterator const &it) const { return m_ptr != it.m_ptr; }
				bool operator==(const_iterator const &it) const { return m_ptr == it.m_ptr; }
			private:
				pointer m_ptr;
		};

		template<class T>
		class iterator {
			private:
				typedef ft::iterator_traits<T>						_traits_type;
			public:
				typedef typename _traits_type::iterator_category	iterator_category;
				typedef typename _traits_type::value_type			value_type;
				typedef typename _traits_type::difference_type		difference_type;
				typedef typename _traits_type::reference			reference;
				typedef typename _traits_type::pointer				pointer;

				/* Constructors */
				iterator() : m_ptr( NULL ) { }
				iterator(pointer p) : m_ptr( p ) { }
				iterator(iterator const &it) : m_ptr( it.m_ptr ) { }
				iterator &operator=(iterator const &it) {
					if ( &it == this )
						return *this;
					m_ptr = it.m_ptr;
					return *this;
				}
				~iterator() {}

				/* Accesses operators */
				value_type base() const { return m_ptr; }
				reference operator*() const { return *m_ptr; }
				pointer operator->() { return m_ptr; }
				pointer operator->() const { return m_ptr; }
				reference operator[](difference_type offset) const { return m_ptr[offset]; }

				/* Increment / Decrement */
				iterator &operator++() { m_ptr++; return *this; };
				iterator operator++(int) { iterator tmp = *this; ++(*this); return tmp; }
				iterator &operator--() { m_ptr--; return *this; }
				iterator operator--(int) { iterator tmp = *this; --(*this); return tmp; }

				/* Arithmetic */
				iterator &operator+=(difference_type offset) { m_ptr += offset; return *this; }
				iterator &operator-=(difference_type offset) { m_ptr -= offset; return *this; }
				
				iterator operator+(difference_type offset) { return iterator( m_ptr + offset ); }
				friend iterator operator+(difference_type offset, const iterator &it) { return random_access_iterator( it.m_ptr + offset ); }

				iterator operator-(difference_type offset) { return iterator( m_ptr - offset ); }
				friend iterator operator-(difference_type offset, const iterator &it) { return random_access_iterator( it.m_ptr - offset ); }
				difference_type operator-(iterator other) { return m_ptr - other.m_ptr; }


				/* Comparison operators */
				bool operator<(iterator const &it) const { return m_ptr < it.m_ptr; }
				bool operator>(iterator const &it) const { return m_ptr > it.m_ptr; }
				bool operator>=(iterator const &it) const { return m_ptr >= it.m_ptr; }
				bool operator<=(iterator const &it) const { return m_ptr <= it.m_ptr; }
				bool operator!=(iterator const &it) const { return m_ptr != it.m_ptr; }
				bool operator==(iterator const &it) const { return m_ptr == it.m_ptr; }
			private:
				pointer m_ptr;
		};

		template<typename T>
		class reverse_iterator {
			private:
				typedef ft::iterator_traits<T>						_traits_type;
			public:
				typedef typename _traits_type::iterator_category	iterator_category;
				typedef typename _traits_type::value_type			value_type;
				typedef typename _traits_type::difference_type		difference_type;
				typedef typename _traits_type::reference			reference;
				typedef typename _traits_type::pointer				pointer;

				/* Constructors */
				reverse_iterator() : m_ptr( NULL ) { }
				reverse_iterator(pointer p) : m_ptr( p ) { }
				reverse_iterator(reverse_iterator const &it) : m_ptr( it.m_ptr ) { }
				reverse_iterator(iterator<T> const &it) : m_ptr( it.operator->() ) {}
				reverse_iterator(const_iterator<T> const &it) : m_ptr( it.operator->() ) {}
				reverse_iterator &operator=(reverse_iterator const &it) {
					if ( &it == this )
						return *this;
					m_ptr = it.m_ptr;
					return *this;
				}
				~reverse_iterator() {}

				/* Accesses operators */
				value_type base() const { return m_ptr; }
				reference operator*() const { return *m_ptr; }
				pointer operator->() const { return m_ptr; }
				reference operator[](difference_type offset) const { return m_ptr[offset]; }

				/* Increment / Decrement (which is inverted with reverse iterator) */
				reverse_iterator &operator++() { m_ptr--; return *this; };
				reverse_iterator operator++(int) { reverse_iterator tmp = *this; ++(*this); return tmp; }
				reverse_iterator &operator--() { m_ptr++; return *this; }
				reverse_iterator operator--(int) { reverse_iterator tmp = *this; --(*this); return tmp; }

				/* Arithmetic */
				reverse_iterator &operator+=(difference_type offset) { m_ptr -= offset; return *this; }
				reverse_iterator &operator-=(difference_type offset) { m_ptr += offset; return *this; }
				
				reverse_iterator operator+(difference_type offset) { return reverse_iterator( m_ptr - offset ); }
				friend reverse_iterator operator+(difference_type offset, const reverse_iterator &it) { return reverse_iterator( it.m_ptr - offset ); }

				reverse_iterator operator-(difference_type offset) { return reverse_iterator( m_ptr + offset ); }
				friend reverse_iterator operator-(difference_type offset, const reverse_iterator &it) { return reverse_iterator( it.m_ptr + offset ); }
				difference_type operator-(reverse_iterator other) { return m_ptr + other.m_ptr; }

				/* Comparison operators */
				bool operator<(reverse_iterator const &it) const { return m_ptr > it.m_ptr; }
				bool operator>(reverse_iterator const &it) const { return m_ptr < it.m_ptr; }
				bool operator>=(reverse_iterator const &it) const { return m_ptr <= it.m_ptr; }
				bool operator<=(reverse_iterator const &it) const { return m_ptr >= it.m_ptr; }
				bool operator!=(reverse_iterator const &it) const { return m_ptr != it.m_ptr; }
				bool operator==(reverse_iterator const &it) const { return m_ptr == it.m_ptr; }
			private:
				pointer	m_ptr;
		};

		template<typename T>
		class const_reverse_iterator {
			private:
				typedef ft::iterator_traits<T>						_traits_type;
			public:
				typedef typename _traits_type::iterator_category	iterator_category;
				typedef typename _traits_type::value_type			value_type;
				typedef typename _traits_type::difference_type		difference_type;
				typedef typename _traits_type::reference			reference;
				typedef typename _traits_type::pointer				pointer;

				/* Constructors */
				const_reverse_iterator() : m_ptr( NULL ) { }
				const_reverse_iterator(pointer p) : m_ptr( p ) { }
				const_reverse_iterator(const_reverse_iterator const &it) : m_ptr( it.m_ptr ) { }
				const_reverse_iterator(reverse_iterator<T> const &it) : m_ptr( it.operator->() ) {}
				const_reverse_iterator(iterator<T> const &it) : m_ptr( it.operator->() ) {}
				const_reverse_iterator(const_iterator<T> const &it) : m_ptr( it.operator->() ) {}
				const_reverse_iterator &operator=(const_reverse_iterator const &it) {
					if ( &it == this )
						return *this;
					m_ptr = it.m_ptr;
					return *this;
				}
				~const_reverse_iterator() {}

				/* Accesses operators */
				value_type base() const { return m_ptr; }
				reference operator*() const { return *m_ptr; }
				pointer operator->() const { return m_ptr; }
				reference operator[](difference_type offset) const { return m_ptr[offset]; }

				/* Increment / Decrement (which is inverted with reverse iterator) */
				const_reverse_iterator &operator++() { m_ptr--; return *this; };
				const_reverse_iterator operator++(int) { const_reverse_iterator tmp = *this; ++(*this); return tmp; }
				const_reverse_iterator &operator--() { m_ptr++; return *this; }
				const_reverse_iterator operator--(int) { const_reverse_iterator tmp = *this; --(*this); return tmp; }

				/* Arithmetic */
				const_reverse_iterator &operator+=(difference_type offset) { m_ptr -= offset; return *this; }
				const_reverse_iterator &operator-=(difference_type offset) { m_ptr += offset; return *this; }
				
				const_reverse_iterator operator+(difference_type offset) { return const_reverse_iterator( m_ptr - offset ); }
				friend const_reverse_iterator operator+(difference_type offset, const const_reverse_iterator &it) { return const_reverse_iterator( it.m_ptr - offset ); }

				const_reverse_iterator operator-(difference_type offset) { return const_reverse_iterator( m_ptr + offset ); }
				friend const_reverse_iterator operator-(difference_type offset, const const_reverse_iterator &it) { return const_reverse_iterator( it.m_ptr + offset ); }
				difference_type operator-(const_reverse_iterator other) { return m_ptr + other.m_ptr; }

				/* Comparison operators */
				bool operator<(const_reverse_iterator const &it) const { return m_ptr > it.m_ptr; }
				bool operator>(const_reverse_iterator const &it) const { return m_ptr < it.m_ptr; }
				bool operator>=(const_reverse_iterator const &it) const { return m_ptr <= it.m_ptr; }
				bool operator<=(const_reverse_iterator const &it) const { return m_ptr >= it.m_ptr; }
				bool operator!=(const_reverse_iterator const &it) const { return m_ptr != it.m_ptr; }
				bool operator==(const_reverse_iterator const &it) const { return m_ptr == it.m_ptr; }
			private:
				pointer	m_ptr;
		};
	}
}

#endif
