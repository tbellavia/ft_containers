#include <memory>
#include <iostream>

class IntVector {
	private:
		static const size_t GROWTH_FACTOR = 2;
		std::allocator<int> m_alloc;
		size_t				m_capacity;
		size_t				m_size;
		int					*m_items;
	public:
		IntVector() : m_capacity( GROWTH_FACTOR ), m_size( 0 ),
					  m_items( m_alloc.allocate( m_capacity ) ) {}

		~IntVector(){
			m_alloc.deallocate( m_items, m_capacity );
		}

		size_t size() const {
			return m_size;
		}

		size_t capacity() const {
			return m_capacity;
		}

		const int *data() const {
			return m_items;
		}

		void push_back( int value ) {
			if ( m_size == m_capacity ) {
				int *tmp;
				
				m_capacity *= GROWTH_FACTOR;
				tmp = m_alloc.allocate( m_capacity );

				for ( size_t index = 0 ; index < m_size ; index++ ){
					m_alloc.construct( &tmp[index], m_items[index] );
				}
				m_alloc.deallocate( m_items, m_capacity / GROWTH_FACTOR );
				m_items = tmp;
			}
			m_alloc.construct( &m_items[m_size], value );
			m_size++;
		}

		friend std::ostream &operator<<( std::ostream &os, const IntVector &vec ){
			const int *items = vec.data();
			size_t size = vec.size();
	
			for ( size_t index = 0 ; index < size ; index++ ){
				os << items[index];
				

				if ( index + 1 != size ){
					os << ", ";
				}
			}
			return os;
		}
};

int		main(void){
	IntVector vec;

	for ( size_t index = 0 ; index < 100 ; index++ ){
		vec.push_back( index );
	}

	std::cout << "Size : " << vec.size() << std::endl;
	std::cout << "Capacity : " << vec.capacity() << std::endl;
	std::cout << vec << std::endl;
	return (0);
}
