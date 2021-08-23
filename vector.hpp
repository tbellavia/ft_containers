#ifndef VECTOR_HPP
#define VECTOR_HPP

# include <memory>
# include <iterator>
# include <limits>
# include <stdexcept>
# include <stddef.h>
# include <iostream>

namespace ft {
	/**
	 * The documentation of this vector implementation comes from
	 * https://www.cplusplus.com/reference/vector/vector/?kw=vector
	 * 
	 */
	template<class T, class Allocator = std::allocator<T> >
	class vector {
		public:
			template<class TIt>
			class _iterator {
				public:
					typedef std::random_access_iterator_tag iterator_category;
					typedef std::size_t						size_type;
					typedef std::ptrdiff_t					difference_type;
					typedef TIt								value_type;
					typedef TIt*								pointer;
					typedef TIt&								reference;

					/* Constructors */
					_iterator() : m_ptr( NULL ) { }
					_iterator(pointer p) : m_ptr( p ) { }
					_iterator(_iterator const &it) : m_ptr( it.m_ptr ) { }
					_iterator &operator=(_iterator const &it) {
						if ( &it == this )
							return *this;
						m_ptr = it.m_ptr;
						return *this;
					 }
					~_iterator() {}

					/* Accesses operators */
					reference operator*() const { return *m_ptr; }
					pointer operator->() { return m_ptr; }
					reference operator[](difference_type offset) const { return m_ptr[offset]; }

					/* Increment / Decrement */
					_iterator &operator++() { m_ptr++; return *this; };
					_iterator operator++(int) { _iterator tmp = *this; ++(*this); return tmp; }
					_iterator &operator--() { m_ptr--; return *this; }
					_iterator operator--(int) { _iterator tmp = *this; --(*this); return tmp; }

					/* Arithmetic */
					_iterator &operator+=(difference_type offset) { m_ptr += offset; return *this; }
					_iterator &operator-=(difference_type offset) { m_ptr -= offset; return *this; }
					_iterator operator+(difference_type offset) { return _iterator( m_ptr + offset ); }
					friend _iterator operator+(difference_type offset, const _iterator &it) { return _iterator( it.m_ptr + offset ); }
					_iterator operator-(difference_type offset) { return _iterator( m_ptr - offset ); }
					friend _iterator operator-(difference_type offset, const _iterator &it) { return _iterator( it.m_ptr - offset ); }


					/* Comparison operators */
					bool operator<(_iterator const &it) const { return m_ptr < it.m_ptr; }
					bool operator>(_iterator const &it) const { return m_ptr > it.m_ptr; }
					bool operator>=(_iterator const &it) const { return m_ptr >= it.m_ptr; }
					bool operator<=(_iterator const &it) const { return m_ptr <= it.m_ptr; }
					bool operator!=(_iterator const &it) const { return m_ptr != it.m_ptr; }
					bool operator==(_iterator const &it) const { return m_ptr == it.m_ptr; }
				private:
					pointer									m_ptr;
			};

			typedef std::size_t									size_type;
			typedef std::ptrdiff_t								difference_type;
			typedef T											value_type;
			typedef Allocator									allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef _iterator<T>								iterator;
			typedef _iterator<const T>							const_iterator;
		private:
			const static size_type	GROWTH_FACTOR = 2;
			Allocator				m_alloc;
			size_type				m_capacity;
			size_type				m_size;
			T						*m_items;
		public:
			vector() :
				m_capacity( 0 ), 
				m_size( 0 ),
				m_items( 0 ) {}

			~vector() {
				if ( m_items != NULL ){
					for ( size_type index = 0 ; index < m_size ; index++ ){
						m_alloc.destroy( &m_items[index] );
					}
					m_alloc.deallocate( m_items, m_capacity );
				}
			}

			/**
			 * Return size
			 * 
			 * Returns the number of elements in the vector.
			 * This is the number of actual objects held in the vector,
			 * which is not necessarily equal to its storage capacity.
			 * 
			 */
			size_type size() const {
				return m_size;
			}

			/**
			 * Return capacity
			 * 
			 * Returns the size of the storage space currently allocated
			 * for the vector, expressed in terms of elements.
			 * 
			 * This capacity is not necessarily equal to the vector size.
			 * It can be equal or greater, with the extra space allowing
			 * to accommodate for growth without the need to reallocate on each insertion.
			 * 
			 * Notice that this capacity does not suppose a limit on the size of the vector.
			 * When this capacity is exhausted and more is needed,
			 * it is automatically expanded by the container (reallocating it storage space). 
			 * The theoretical limit on the size of a vector is given by member max_size.
			 * 
			 * The capacity of a vector can be explicitly altered by calling member vector::reserve.
			 */
			size_type capacity() const {
				return m_capacity;
			}

			/**
			 * Return maximum size
			 * 
			 * Returns the maximum number of elements that the vector can hold.
			 * 
			 * This is the maximum potential size the container can reach 
			 * due to known system or library implementation limitations, 
			 * but the container is by no means guaranteed to be able to reach 
			 * that size: it can still fail to allocate storage at any point before that size is reached.
			 * 
			 */
			size_type max_size() const {
				return ( m_alloc.max_size() );
			}

			/**
			 * Test whether vector is empty
			 * 
			 * Returns whether the vector is empty (i.e. whether its size is 0).
			 * This function does not modify the container in any way.
			 * To clear the content of a vector, see vector::clear.
			 * 
			 */
			bool empty() const {
				return m_size == 0;
			}

			/**
			 * Request a change in capacity
			 * 
			 * Requests that the vector capacity be at least enough to contain n elements.
			 * 
			 * If n is greater than the current vector capacity, 
			 * the function causes the container to reallocate its storage increasing its capacity to n (or greater).
			 * 
			 * In all other cases, the function call does not cause a reallocation and the vector capacity is not affected.
			 * 
			 * This function has no effect on the vector size and cannot alter its elements.
			 * 
			 */
			void reserve( size_type n ) {
				if ( n > this->max_size() ){
					throw std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size");
				}
				if ( n > m_capacity ){
					T *tmp = m_alloc.allocate( n );

					if ( m_items != NULL ){
						for ( size_type index = 0 ; index < m_size ; index++ ){
							m_alloc.construct( &tmp[index], m_items[index] );
						}
						m_alloc.deallocate( m_items, m_capacity );
					}
					m_items = tmp;
					m_capacity = n;
				}
			}

			/**
			 * Change size
			 * 
			 * Resizes the container so that it contains n elements.
			 * 
			 * If n is smaller than the current container size, the content is reduced to its first n elements, 
			 * removing those beyond (and destroying them).
			 * 
			 * If n is greater than the current container size, 
			 * the content is expanded by inserting at the end as many elements as needed to reach a size of n. 
			 * If val is specified, the new elements are initialized as copies of val, otherwise, they are value-initialized.
			 * 
			 * If n is also greater than the current container capacity, an automatic reallocation of the allocated storage space takes place.
			 * 
			 * Notice that this function changes the actual content of the container by inserting or erasing elements from it.
			 * 
			 */
			void resize( size_type n, value_type val = value_type() ){
				if ( n < m_size ){
					for ( size_type index = n ; index < m_size ; index++ ){
						m_alloc.destroy( &m_items[index] );
					}
					m_size = n;
				} else {
					if ( n > m_capacity ){
						reserve(n);
					}
					for ( size_type index = m_size ; index < n ; index++ ){
						m_alloc.construct( &m_items[index], val );
					}
					m_size = n;
				}
			}

			/**
			 * Add element at the end
			 * 
			 * Adds a new element at the end of the vector, after its current last element. 
			 * The content of val is copied (or moved) to the new element.
			 * 
			 * This effectively increases the container size by one, which causes an automatic
			 * reallocation of the allocated storage space if -and only if- the new vector size 
			 * surpasses the current vector capacity.
			 * 
			 */
			void push_back( const value_type &val ){
				if ( m_size == m_capacity ){
					value_type alloc_size;

					if ( m_size == 0 )
						alloc_size = 1;
					else
						alloc_size = m_capacity * GROWTH_FACTOR;
					value_type *tmp = m_alloc.allocate( alloc_size );

					for ( size_type index = 0 ; index < m_size ; index++ ){
						m_alloc.construct( &tmp[index], m_items[index] );
					}
					m_alloc.deallocate( m_items, m_capacity );
					m_items = tmp;
					m_capacity = alloc_size;
				}
				m_items[m_size++] = val;
			}

			/**
			 * Delete last element
			 * 
			 * Removes the last element in the vector, effectively reducing the container size by one.
			 * This destroys the removed element.
			 * 
			 */
			void pop_back() {
				if ( m_size != 0 ){
					m_alloc.destroy( &m_items[--m_size] );
				}
			}

			
			/**
			 * Return iterator to beginning
			 * 
			 * Returns an iterator pointing to the first element in the vector.
			 * Notice that, unlike member vector::front, which returns a reference
			 * to the first element, this function returns a random access iterator pointing to it.	
			 * If the container is empty, the returned iterator value shall not be dereferenced.
			 * 
			 */
			iterator begin() {
				return iterator( &m_items[0] );
			}

			const_iterator begin() const {
				return const_iterator( &m_items[0] );
			}

			/**
			 * Return iterator to end
			 * 
			 * Returns an iterator referring to the past-the-end element in the vector container.
			 * 
			 * The past-the-end element is the theoretical element that would follow 
			 * the last element in the vector. It does not point to any element, and thus shall not be dereferenced.
			 * Because the ranges used by functions of the standard library do not include 
			 * the element pointed by their closing iterator, this function is often used in 
			 * combination with vector::begin to specify a range including all the elements in the container.
			 * 
			 * If the container is empty, this function returns the same as vector::begin.
			 * 
			 */
			iterator end() {
				return iterator( &m_items[m_size] );
			}

			const_iterator end() const {
				return const_iterator( &m_items[m_size] );
			}
	};
}


#endif /* VECTOR_HPP */
