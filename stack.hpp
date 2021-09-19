#ifndef STACK_HPP
#define STACK_HPP

# include "vector.hpp"

namespace ft {
	/**
	 * The documentation of this stack implementation comes frome
	 * https://www.cplusplus.com/reference/stack/stack/
	 * 
	 */
	template<class T, class Container = ft::vector<T> >
	class stack {
		public:
			typedef T			value_type;
			typedef Container	container_type;
			typedef std::size_t	size_type;
		private:
			container_type m_items;
		public:
			/**
			 * Construct stack
			 * 
			 * Constructs a stack container adaptor object.
			 * 
			 */
			explicit stack(const container_type &container = container_type()) 
				: m_items( container ) { }
			
			/**
			 * Construct a new stack object by copy
			 * 
			 */
			stack(const stack &s) : m_items( s.m_items ) {}

			/**
			 * Construct a new stack object by assignation
			 * 
			 */
			stack &operator=(const stack &s) {
				if ( &s == this )
					return *this;
				m_items = s.m_items;
				return *this;
			}
			
			/**
			 * Return size
			 * 
			 * Returns the number of elements in the stack.
			 * 
			 * This member function effectively calls member size of the underlying container object.
			 * 
			 */
			size_type size() const {
				return m_items.size();
			}

			/**
			 * Test whether container is empty
			 * 
			 * Returns whether the stack is empty: i.e. whether its size is zero.
			 * 
			 * This member function effectively calls member empty of the underlying container object.
			 * 
			 */
			bool empty() const {
				return size() == 0;
			}

			/**
			 * Access next element
			 * 
			 * Returns a reference to the top element in the stack.
			 * 
			 * Since stacks are last-in first-out containers, the top element is the last element inserted 
			 * into the stack.
			 * 
			 * This member function effectively calls member back of the underlying container object
			 * 
			 */
			value_type &top() {
				return m_items.back();
			}

			const value_type &top() const {
				return m_items.back();
			}

			/**
			 * Insert element
			 * 
			 * Inserts a new element at the top of the stack, above its current top element. 
			 * The content of this new element is initialized to a copy of val.
			 * 
			 * This member function effectively calls the member function push_back of the underlying container object.
			 * 
			 */
			void push(const value_type &val){
				m_items.push_back( val );
			}

			/**
			 * Remove top element
			 * 
			 * Removes the element on top of the stack, effectively reducing its size by one.
			 * 
			 * The element removed is the latest element inserted into the stack, whose value can be retrieved by calling member stack::top.
			 * 
			 * This calls the removed element's destructor.
			 * 
			 * This member function effectively calls the member function pop_back of the underlying container object.
			 * 
			 */
			void pop() {
				m_items.pop_back();
			}
	};

	template<class T, class Container>
	bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs){
		return lhs.m_items == rhs.m_items;
	}

	template<class T, class Container>
	bool operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs){
		return lhs.m_items != rhs.m_items;
	}

	template<class T, class Container>
	bool operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs){
		return lhs.m_items > rhs.m_items;
	}

	template<class T, class Container>
	bool operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs){
		return lhs.m_items >= rhs.m_items;
	}

	template<class T, class Container>
	bool operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs){
		return lhs.m_items < rhs.m_items;
	}

	template<class T, class Container>
	bool operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs){
		return lhs.m_items <= rhs.m_items;
	}
}

#endif
