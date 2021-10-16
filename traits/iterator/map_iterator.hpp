#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

namespace ft {
    namespace map_ {
		template<class T>
		class bidirectional_iterator;

		template<class T>
		class const_bidirectional_iterator {
			public:
				typedef T								iterator_type;
				typedef std::bidirectional_iterator_tag iterator_category;
				typedef std::size_t						size_type;
				typedef std::ptrdiff_t					difference_type;
				typedef typename T::value_type			value_type;
				typedef T*								pointer;
				typedef T&								reference;
				typedef const T&						const_reference;
				typedef typename T::pointer				data_pointer;
				typedef typename T::const_pointer		data_const_pointer;
				typedef typename T::reference			data_reference;
				typedef typename T::const_reference		data_const_reference;

				/* Constructors */
				const_bidirectional_iterator() : m_ptr( NULL ) { }
				const_bidirectional_iterator(pointer p) : m_ptr( p ) { }
				const_bidirectional_iterator(const_bidirectional_iterator const &it) : m_ptr( it.m_ptr ) { }
				const_bidirectional_iterator(bidirectional_iterator<T> const &it) : m_ptr( it.get_ptr() ) { }
				const_bidirectional_iterator &operator=(const_bidirectional_iterator const &it) {
					if ( &it == this )
						return *this;
					m_ptr = it.m_ptr;
					return *this;
				}
				~const_bidirectional_iterator() {}

				/* Accesses operators */
				data_const_reference operator*() const { return m_ptr->data; }
				data_const_pointer operator->() const { return m_ptr->data; }

				/* Increment / Decrement */
				const_bidirectional_iterator &operator++() {
					this->increment_();
					return *this; 
				}

				const_bidirectional_iterator operator++(int) { 
					const_bidirectional_iterator tmp = *this; 
					this->increment_(); 
					return tmp; 
				}

				const_bidirectional_iterator &operator--() { m_ptr--; return *this; }
				const_bidirectional_iterator operator--(int) { const_bidirectional_iterator tmp = *this; --(*this); return tmp; }

				/* Comparison operators */
				bool operator<(const_bidirectional_iterator const &it) const { return m_ptr < it.m_ptr; }
				bool operator>(const_bidirectional_iterator const &it) const { return m_ptr > it.m_ptr; }
				bool operator>=(const_bidirectional_iterator const &it) const { return m_ptr >= it.m_ptr; }
				bool operator<=(const_bidirectional_iterator const &it) const { return m_ptr <= it.m_ptr; }
				bool operator!=(const_bidirectional_iterator const &it) const { return m_ptr != it.m_ptr; }
				bool operator==(const_bidirectional_iterator const &it) const { return m_ptr == it.m_ptr; }
			private:
				pointer m_ptr;

				void increment_(){
					if ( m_ptr->right != NULL ){
						m_ptr = m_ptr->right;
						while ( m_ptr->left != NULL )
							m_ptr = m_ptr->left;
					} else {
						pointer y = m_ptr->parent;
						while ( m_ptr == y->right ){
							m_ptr = y;
							y = y->parent;
						}
						if ( m_ptr->right != y )
							m_ptr = y;
					}
				}
		};

		template<class T>
		class bidirectional_iterator {
			public:
				typedef T								iterator_type;
				typedef std::bidirectional_iterator_tag iterator_category;
				typedef std::size_t						size_type;
				typedef std::ptrdiff_t					difference_type;
				typedef typename T::value_type			value_type;
				typedef T*								pointer;
				typedef const T*						const_pointer;
				typedef T&								reference;
				typedef const T&						const_reference;
				typedef typename T::pointer				data_pointer;
				typedef typename T::const_pointer		data_const_pointer;
				typedef typename T::reference			data_reference;
				typedef typename T::const_reference		data_const_reference;

				/* Constructors */
				bidirectional_iterator() : m_ptr( NULL ) { }
				bidirectional_iterator(pointer p) : m_ptr( p ) { }
				bidirectional_iterator(bidirectional_iterator const &it) : m_ptr( it.m_ptr ) { }
				bidirectional_iterator &operator=(bidirectional_iterator const &it) {
					if ( &it == this )
						return *this;
					m_ptr = it.m_ptr;
					return *this;
				}
				~bidirectional_iterator() {}

				/* Accesses operators */
				pointer get_ptr() const{ return m_ptr; }

				data_reference operator*() const { return m_ptr->data; }
				data_reference operator->() { return m_ptr->data; }
				data_const_pointer operator->() const { return m_ptr->data; }
				data_reference operator[](difference_type offset) const { return m_ptr[offset]; }

				/* Increment / Decrement */
				bidirectional_iterator &operator++() { m_ptr++; return *this; };
				bidirectional_iterator operator++(int) { bidirectional_iterator tmp = *this; ++(*this); return tmp; }
				bidirectional_iterator &operator--() { m_ptr--; return *this; }
				bidirectional_iterator operator--(int) { bidirectional_iterator tmp = *this; --(*this); return tmp; }

				/* Comparison operators */
				bool operator<(bidirectional_iterator const &it) const { return m_ptr < it.m_ptr; }
				bool operator>(bidirectional_iterator const &it) const { return m_ptr > it.m_ptr; }
				bool operator>=(bidirectional_iterator const &it) const { return m_ptr >= it.m_ptr; }
				bool operator<=(bidirectional_iterator const &it) const { return m_ptr <= it.m_ptr; }
				bool operator!=(bidirectional_iterator const &it) const { return m_ptr != it.m_ptr; }
				bool operator==(bidirectional_iterator const &it) const { return m_ptr == it.m_ptr; }
			private:
				pointer m_ptr;

				void increment_(){
					if ( m_ptr->right != NULL ){
						m_ptr = m_ptr->right;
						while ( m_ptr->left != NULL )
							m_ptr = m_ptr->left;
					} else {
						pointer y = m_ptr->parent;
						while ( m_ptr == y->right ){
							m_ptr = y;
							y = y->parent;
						}
						if ( m_ptr->right != y )
							m_ptr = y;
					}
				}
		};

		template<typename T>
		class reverse_iterator {
			public:
				typedef T								iterator_type;
				typedef std::bidirectional_iterator_tag iterator_category;
				typedef std::size_t						size_type;
				typedef std::ptrdiff_t					difference_type;
				typedef typename T::value_type			value_type;
				typedef T*								pointer;
				typedef T&								reference;
				typedef const T&						const_reference;
				typedef typename T::pointer				data_pointer;
				typedef typename T::const_pointer		data_const_pointer;
				typedef typename T::reference			data_reference;
				typedef typename T::const_reference		data_const_reference;

				/* Constructors */
				reverse_iterator() : m_ptr( NULL ) { }
				reverse_iterator(pointer p) : m_ptr( p ) { }
				reverse_iterator(reverse_iterator const &it) : m_ptr( it.m_ptr ) { }
				reverse_iterator(bidirectional_iterator<T> const &it) : m_ptr( it.operator->() ) {}
				reverse_iterator(const_bidirectional_iterator<T> const &it) : m_ptr( it.operator->() ) {}
				reverse_iterator &operator=(reverse_iterator const &it) {
					if ( &it == this )
						return *this;
					m_ptr = it.m_ptr;
					return *this;
				}
				~reverse_iterator() {}

				/* Accesses operators */
				iterator_type base() const { return m_ptr; }
				data_const_reference operator*() const { return *m_ptr; }
				data_const_pointer operator->() const { return m_ptr; }
				data_const_reference operator[](difference_type offset) const { return m_ptr[offset]; }

				/* Increment / Decrement (which is inverted with reverse iterator) */
				reverse_iterator &operator++() { m_ptr--; return *this; };
				reverse_iterator operator++(int) { reverse_iterator tmp = *this; ++(*this); return tmp; }
				reverse_iterator &operator--() { m_ptr++; return *this; }
				reverse_iterator operator--(int) { reverse_iterator tmp = *this; --(*this); return tmp; }

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
			public:
				typedef T								iterator_type;
				typedef std::bidirectional_iterator_tag iterator_category;
				typedef std::size_t						size_type;
				typedef std::ptrdiff_t					difference_type;
				typedef typename T::value_type			value_type;
				typedef T*								pointer;
				typedef T&								reference;
				typedef const T&						const_reference;
				typedef typename T::pointer				data_pointer;
				typedef typename T::const_pointer		data_const_pointer;
				typedef typename T::reference			data_reference;
				typedef typename T::const_reference		data_const_reference;

				/* Constructors */
				const_reverse_iterator() : m_ptr( NULL ) { }
				const_reverse_iterator(pointer p) : m_ptr( p ) { }
				const_reverse_iterator(const_reverse_iterator const &it) : m_ptr( it.m_ptr ) { }
				const_reverse_iterator(reverse_iterator<T> const &it) : m_ptr( it.operator->() ) {}
				const_reverse_iterator(bidirectional_iterator<T> const &it) : m_ptr( it.operator->() ) {}
				const_reverse_iterator(const_bidirectional_iterator<T> const &it) : m_ptr( it.operator->() ) {}
				const_reverse_iterator &operator=(const_reverse_iterator const &it) {
					if ( &it == this )
						return *this;
					m_ptr = it.m_ptr;
					return *this;
				}
				~const_reverse_iterator() {}

				/* Accesses operators */
				iterator_type base() const { return m_ptr; }
				data_const_reference operator*() const { return *m_ptr; }
				data_pointer operator->() const { return m_ptr; }
				data_const_reference operator[](difference_type offset) const { return m_ptr[offset]; }

				/* Increment / Decrement (which is inverted with reverse iterator) */
				const_reverse_iterator &operator++() { m_ptr--; return *this; };
				const_reverse_iterator operator++(int) { const_reverse_iterator tmp = *this; ++(*this); return tmp; }
				const_reverse_iterator &operator--() { m_ptr++; return *this; }
				const_reverse_iterator operator--(int) { const_reverse_iterator tmp = *this; --(*this); return tmp; }

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
