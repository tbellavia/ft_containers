#ifndef VECTOR_HPP
#define VECTOR_HPP

# include <memory>
# include <limits>
# include <stdexcept>
# include <stddef.h>

namespace ft {
	/**
	 * The documentation of this vector implementation comes from
	 * https://www.cplusplus.com/reference/vector/vector/?kw=vector
	 * 
	 */
	template<class T, class Allocator = std::allocator<T> >
	class vector {
		public:
			typedef std::size_t									size_type;
			typedef std::ptrdiff_t								difference_type;
			typedef T											value_type;
			typedef Allocator									allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
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
					size_type delta = m_size - n;

					// Need reverse iterator to achieve resize
				}
				(void)n;
				(void)val;
			}
	};
}


#endif
