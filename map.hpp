#ifndef MAP_HPP
#define MAP_HPP

# include <functional>
# include <memory>
# include "utility/pair.hpp"
# include "traits/iterator/map_iterator.hpp"

namespace ft
{
	/**
	 * 
	 * Map
	 * 
	 * Maps are associative containers that store elements formed by a combination of a
	 * key value and a mapped value, following a specific order.
	 * 
	 * In a map, the key values are generally used to sort and uniquely identify the elements,
	 * while the mapped values store the content associated to this key. The types of key and 
	 * mapped value may differ, and are grouped together in member type value_type, which is 
	 * a pair type combining both:
	 * 
	 * typedef pair<const Key, T> value_type;
	 * 
	 * Internally, the elements in a map are always sorted by its key following a specific strict 
	 * weak ordering criterion indicated by its internal comparison object (of type Compare).
	 * 
	 * map containers are generally slower than unordered_map containers to access individual 
	 * elements by their key, but they allow the direct iteration on subsets based on their order.
	 * 
	 * The mapped values in a map can be accessed directly by their corresponding 
	 * key using the bracket operator ((operator[]).
	 * 
	 * Maps are typically implemented as binary search trees.
	 * 
	 */
	template<
		class Key,												// map::key_type
		class T,												// map::mapped_type
		class Compare = std::less<Key>,							// map::key_compare
		class Alloc = std::allocator<ft::pair<const Key, T> >	// map::allocator_type
	>
	class map {
		private:
			/**
			 * Forward declaration
			 */
			struct rb_node;
		public:
			typedef Key													key_type;
			typedef T													mapped_type;
			typedef ft::pair<const key_type, mapped_type>				value_type;
			typedef Compare												key_compare;
			// TODO: Add value_comp
			// typedef value_compare							
			typedef Alloc												allocator_type;
			typedef typename allocator_type::reference					reference;
			typedef typename allocator_type::const_reference			const_reference;
			typedef typename allocator_type::pointer					pointer;
			typedef typename allocator_type::const_pointer				const_pointer;
			typedef std::ptrdiff_t										difference_type;
			typedef std::size_t											size_type;
			typedef ft::map_::bidirectional_iterator<rb_node>			iterator;
			typedef ft::map_::const_bidirectional_iterator<rb_node>		const_iterator;
			typedef ft::map_::reverse_iterator<rb_node>					reverse_iterator;
			typedef ft::map_::const_reverse_iterator<rb_node>			const_reverse_iterator;
		/**
		 * Private declarations.
		 * 
		 */
		private:
			enum rb_color { BLACK = 1, RED, SENTINEL };
			/**
			 * Internal struct representing a binary tree node.
			 * 
			 */
			struct rb_node {
				typedef ft::pair<const key_type, mapped_type>		value_type;
				typedef typename allocator_type::reference			reference;
				typedef typename allocator_type::const_reference	const_reference;
				typedef typename allocator_type::pointer			pointer;
				typedef typename allocator_type::const_pointer		const_pointer;
				typedef std::allocator<rb_node>						allocator_type;

				value_type	data;
				rb_node		*parent;
				rb_node		*left;
				rb_node		*right;
				int			color;

				/**
				 * Default constructor
				 * 
				 * Constructs a new empty node with default value_type() and all
				 * pointers to NULL.
				 * 
				 * Color is always set to RED as it will always be inserted as a RED
				 * node.
				 * 
				 */
				rb_node() 
					: data( value_type() ), parent( NULL ), left( NULL ), right( NULL ), color( RED ) { }

				/**
				 * Data constructor
				 * 
				 * Constructs a new node with data and all pointers to NULL.
				 * 
				 * Color is always set to RED as it will always be inserted as a RED
				 * node.
				 * 
				 */
				rb_node( const value_type &__data )
					: data( __data ), parent( NULL ), left( NULL ), right( NULL ), color( RED ) { }

				/**
				 * Data-Parent constructor
				 * 
				 * Constructs a new node with data and a parent, right and left 
				 * pointers are set to NULL.
				 * 
				 * Color is always set to RED as it will always be inserted as a RED
				 * node.
				 * 
				 */
				rb_node( const value_type &__data, rb_node *__parent )
					: data( __data ), parent( __parent ), left( NULL ), right( NULL ), color( RED ) { }

				/**
				 * Get the grand parent
				 * 
				 * Returns the grand parent of the current node.
				 * 
				 */
				rb_node *grand_parent() {
					if ( this->parent == NULL )
						return NULL;
					return this->parent->parent;
				}

				/**
				 * Get uncle node
				 * 
				 * Returns the uncle node of the current node.
				 * 
				 */
				rb_node *uncle() {
					rb_node *gp = this->grand_parent();

					if ( gp == NULL )
						return NULL;
					return this->parent->sibling();
				}

				/**
				 * Get the sibling node
				 * 
				 * Returns the sibling node.
				 * 
				 */
				rb_node *sibling() {
					if ( this->parent == NULL )
						return NULL;
					if ( this == this->parent->left )
						return this->parent->right;
					return this->parent->left;
				}

				bool is_sentinel() const {
					return color == SENTINEL;
				}

				bool is_left() const {
					if ( this->parent == NULL )
						return false;
					return this->parent->left == this;
				}

				bool is_right() const {
					if ( this->parent == NULL )
						return false;
					return this->parent->right == this;
				}

				void set_left( rb_node *node ){
					this->left = node;
					node->parent = this;
				}

				void set_right( rb_node *node ){
					this->right = node;
					node->parent = this;
				}

				void set_right_sentinel( rb_node *sentinel ){
					this->set_right(sentinel);
				}

				void set_left_sentinel( rb_node *sentinel ){
					this->set_left(sentinel);
				}

				void assign( rb_node *node ){
					if ( node ){
						this->parent = node->parent;
						this->left = node->left;
						this->right = node->right;
						this->color = node->color;
					}
				}

				static rb_node *create_node( allocator_type alloc = allocator_type() ){
					rb_node *node = alloc.allocate( 1 );

					alloc.construct( node );
					return node;
				}

				static rb_node *create_node( const value_type &data, allocator_type alloc = allocator_type() ){
					rb_node *node = alloc.allocate( 1 );

					alloc.construct( node, data );
					return node;
				}

				static rb_node *create_node( const value_type &data, rb_node *parent, allocator_type alloc = allocator_type() ){
					rb_node *node = alloc.allocate( 1 );

					alloc.construct( node, data, parent );
					return node;
				}

				static rb_node *create_sentinel_node( allocator_type alloc = allocator_type() ){
					rb_node *node = rb_node::create_node( alloc );

					node->color = SENTINEL;
					return node;
				}

				/**
				 * Destroy node
				 * 
				 * Call the delete operator of the node and deallocate memory.
				 */
				static void destroy_node( rb_node *node, allocator_type alloc = allocator_type() ){
					alloc.destroy( node );
					alloc.deallocate( node, 1 );
				}
			};
		
		/**
		 * Member variables
		 */
		private:
			rb_node								*m_root;
			size_type							m_size;
			key_compare							m_comp;
			allocator_type						m_alloc;
			rb_node								*m_right_sentinel;
			rb_node								*m_left_sentinel;

		/**
		 * Public member functions.
		 * 
		 */
		public:
			/**
			 * Construct map
			 * 
			 * (1) empty container constructor (default constructor)
			 * 
			 * Constructs an empty container, with no elements.
			 */
			explicit map( const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type() )
				: m_root( NULL ), m_size( 0 ), m_comp( comp ), m_alloc( alloc ), m_right_sentinel( rb_node::create_sentinel_node() ), m_left_sentinel( rb_node::create_sentinel_node() ) 
			{
				
			}
			
			template<class InputIterator>
			map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
				: m_root( NULL ), m_size( 0 ), m_comp( comp ), m_alloc( alloc ), m_right_sentinel( rb_node::create_sentinel_node() ), m_left_sentinel( rb_node::create_sentinel_node() )
			{
				for ( ; first != last ; ++first ){
					insert(*first);
				}
			}

			~map() {
				clear();
			}

			/**
			 * Insert elements
			 * 
			 * Extends the container by inserting new elements, effectively increasing the container 
			 * size by the number of elements inserted.
			 * 
			 * Because element keys in a map are unique, the insertion operation checks whether each 
			 * inserted element has a key equivalent to the one of an element already in the container, 
			 * and if so, the element is not inserted, returning an iterator to this existing element 
			 * (if the function returns a value).
			 * 
			 * For a similar container allowing for duplicate elements, see multimap.
			 * 
			 * An alternative way to insert elements in a map is by using member function map::operator[].
			 * 
			 * Internally, map containers keep all their elements sorted by their key following the criterion 
			 * specified by its comparison object. The elements are always inserted in its respective position 
			 * following this ordering.
			 * 
			 */
			ft::pair<iterator, bool> insert(const value_type &val){
				ft::pair<iterator, bool> ret;

				if ( m_root == NULL ){
					m_size++;
					m_root = rb_node::create_node( val );
					m_root->set_right_sentinel(m_right_sentinel);
					m_root->set_left_sentinel(m_left_sentinel);
					return ft::pair<iterator, bool>( iterator( m_root ), true );
				}
				ret = insert_recursive_(m_root, val);
				if ( ret.second )
					m_size++;
				return ret;
			}

			/**
			 * Access element
			 * 
			 * If k matches the key of an element in the container, the function returns a reference to its mapped value.
			 * If k does not match the key of any element in the container, the function inserts a new element with that
			 * key and returns a reference to its mapped value. Notice that this always increases the container size by
			 * one, even if no mapped value is assigned to the element (the element is constructed using its default constructor).
			 * A similar member function, map::at, has the same behavior when an element with the key exists, 
			 * but throws an exception when it does not.
			 * 
			 */
			mapped_type& operator[](const key_type& k) {
				return (*((this->insert(ft::make_pair(k,mapped_type()))).first)).second;
			}

			/**
			 * Clear content
			 * 
			 * Removes all elements from the map container (which are destroyed), leaving the container with a size of 0.
			 */
			void clear() {
				clear_recursive_(m_root);
				m_root = NULL;
			}

			/**
			 * Get iterator to element
			 * 
			 * Searches the container for an element with a key equivalent to k and returns an iterator to it if found,
			 * otherwise it returns an iterator to map::end.
			 * 
			 * Two keys are considered equivalent if the container's comparison object returns false reflexively 
			 * (i.e., no matter the order in which the elements are passed as arguments).
			 * Another member function, map::count, can be used to just check whether a particular key exists.
			 */
			iterator find(const key_type &k){
				rb_node *found = find_recursive_(k);

				if ( found == NULL )
					return end();
				return iterator( found );
			}

			/**
			 * Get iterator to element
			 * 
			 * Searches the container for an element with a key equivalent to k and returns an iterator to it if found,
			 * otherwise it returns an iterator to map::end.
			 * 
			 * Two keys are considered equivalent if the container's comparison object returns false reflexively 
			 * (i.e., no matter the order in which the elements are passed as arguments).
			 * Another member function, map::count, can be used to just check whether a particular key exists.
			 */
			const_iterator find(const key_type &k) const {
				rb_node *found = find_recursive_(k);

				if ( found == NULL )
					return end();
				return const_iterator( found );
			}

			rb_node *get_max_node_(rb_node *node){
				if ( node == NULL )
					return NULL;
				while ( node->right != NULL ){
					node = node->right;
				}
				return node;
			}

			// ft::pair<iterator,iterator> equal_range(const key_type& k) {
			// 	iterator found = this->find(k);

			// 	if ( found != this->end() ){
			// 		return ft::make_pair(found, ++found);
			// 	}
			// }

			/**
			 * Erase elements
			 * 
			 * Removes from the map container either a single element or a range of elements ([first,last)).
			 * 
			 * This effectively reduces the container size by the number of elements removed, which are destroyed.
			 */
			void erase(iterator position){
				if ( position != this->end() ){
					rb_node *target = position.base();

					if ( target->left != NULL && target->right != NULL ){
						// Case 3, node has children
						// Go to the right subtree, then find the min (go to leftmost)
						rb_node *min_node = target->right;

						// Find the leftmost child
						while ( min_node->left != NULL ){
							min_node = min_node->left;
						}
						if ( min_node->parent == target ){
							min_node->assign(target);
							if ( target->parent != NULL ){
								if ( target->is_left() ){
									target->parent->set_left(min_node);
								} else {
									target->parent->set_right(min_node);
								}
							} else {
								m_root = min_node;
							}
							min_node->right = NULL;
						} else {
							min_node->parent->left = NULL;
							min_node->assign(target);
							if ( target->parent != NULL ){
								if ( target->is_left() ){
									target->parent->set_left(min_node);
								} else {
									target->parent->set_right(min_node);
								}
							} else {
								m_root = min_node;
							}
						}
					}
					else if ( target->left != NULL ){
						// Case 2, target has one child
						if ( target->is_left() ){
							target->parent->set_left(target->left);
						} else {
							target->parent->set_right(target->left);
						}
					}
					else if ( target->right != NULL ){
						// Case 2, target has one child
						if ( target->is_left() ){
							target->parent->set_left(target->right);
						} else {
							target->parent->set_right(target->right);
						}
					}
					else {
						// Case 1, target has no children
						if ( target->is_left() ){
							target->parent->left = NULL;
						} else {
							target->parent->right = NULL;
						}
					}
					rb_node::destroy_node( target );
				}
			}

			/**
			 * Erase elements
			 * 
			 * Removes from the map container either a single element or a range of elements ([first,last)).
			 * 
			 * This effectively reduces the container size by the number of elements removed, which are destroyed.
			 */
			size_type erase(const key_type &k){
				iterator it = this->find( k );

				if ( it == this->end() )
					return 0;
				this->erase( it );
				return 1;
			}

			/**
			 * Swap content
			 * 
			 * Exchanges the content of the container by the content of x, which is another map of the same type. 
			 * Sizes may differ.
			 * 
			 * After the call to this member function, the elements in this container are those which were in x 
			 * before the call, and the elements of x are those which were in this.
			 * All iterators, references and pointers remain valid for the swapped objects.
			 * 
			 * Notice that a non-member function exists with the same name, swap, overloading that algorithm 
			 * with an optimization that behaves like this member function.
			 * 
			 */
			void swap(map &x){
				rb_node			*tmp_root = x.m_root;
				size_type		tmp_size = x.m_size;
				key_compare		tmp_comp = x.m_comp;
				allocator_type	tmp_alloc = x.m_alloc;
				rb_node			*tmp_right_sentinel = x.m_right_sentinel;
				rb_node			*tmp_left_sentinel = x.m_left_sentinel;

				x.m_root = this->m_root;
				x.m_size = this->m_size;
				x.m_comp = this->m_comp;
				x.m_alloc = this->m_alloc;
				x.m_right_sentinel = this->m_right_sentinel;
				x.m_left_sentinel = this->m_left_sentinel;
				
				this->m_root = tmp_root;
				this->m_size = tmp_size;
				this->m_comp = tmp_comp;
				this->m_alloc = tmp_alloc;
				this->m_right_sentinel = tmp_right_sentinel;
				this->m_left_sentinel = tmp_left_sentinel;
			}

			/**
			 * Return container size
			 * 
			 * Returns the number of elements in the map container.
			 */
			size_type size() const {
				return m_size;
			}

			/**
			 * Test whether container is empty
			 * 
			 * Returns whether the map container is empty (i.e. whether its size is 0).
			 * 
			 * This function does not modify the container in any way. To clear the content of a map container, 
			 * see map::clear.
			 */
			bool empty() const {
				return m_size == 0;
			}

			/**
			 * Return maximum size
			 * 
			 * Returns the maximum number of elements that the map container can hold.
			 * 
			 * This is the maximum potential size the container can reach due to known
			 * system or library implementation limitations, but the container is by 
			 * no means guaranteed to be able to reach that size: it can still fail to 
			 * allocate storage at any point before that size is reached.
			 */
			size_type max_size() const {
				return ( m_alloc.max_size() );
			}

			/**
			 * Return iterator to begining
			 * 
			 * Returns an iterator referring to the first element in the map container
			 * Because map containers keep their elements ordered at all times, begin points to the element that goes 
			 * first following the container's sorting criterion
			 * If the container is empty, the returned iterator value shall not be dereferenced.
			 * 
			 */
			iterator begin(){
				return iterator( m_left_sentinel->parent );
			}

			/**
			 * Return iterator to begining
			 * 
			 * Returns an iterator referring to the first element in the map container
			 * Because map containers keep their elements ordered at all times, begin points to the element that goes 
			 * first following the container's sorting criterion
			 * If the container is empty, the returned iterator value shall not be dereferenced.
			 * 
			 */
			const_iterator begin() const {
				return const_iterator( m_left_sentinel->parent );
			}

			/**
			 * Return reverse iterator to reverse beginning
			 * 
			 * Returns a reverse iterator pointing to the last element in the container (i.e., its reverse beginning).
			 * 
			 * Reverse iterators iterate backwards: increasing them moves them towards the beginning of the container.
			 * 
			 * rbegin points to the element preceding the one that would be pointed to by member end.
			 */ 
			reverse_iterator rbegin() {
				return reverse_iterator( m_right_sentinel->parent );
			}

			/**
			 * Return reverse iterator to reverse beginning
			 * 
			 * Returns a reverse iterator pointing to the last element in the container (i.e., its reverse beginning).
			 * 
			 * Reverse iterators iterate backwards: increasing them moves them towards the beginning of the container.
			 * 
			 * rbegin points to the element preceding the one that would be pointed to by member end.
			 */
			const_reverse_iterator rbegin() const {
				return const_reverse_iterator( m_right_sentinel->parent );
			}

			/**
			 * Return iterator to end
			 * 
			 * Returns an iterator referring to the past-the-end element in the map container.
			 * 
			 * The past-the-end element is the theoretical element that would follow the last 
			 * element in the map container. It does not point to any element, and thus shall not be dereferenced.
			 * 
			 * Because the ranges used by functions of the standard library do not include the element pointed 
			 * by their closing iterator, this function is often used in combination with map::begin to specify 
			 * a range including all the elements in the container.
			 * 
			 * If the container is empty, this function returns the same as map::begin.
			 */
			iterator end() {
				return iterator( m_right_sentinel );
			}

			/**
			 * Return iterator to end
			 * 
			 * Returns an iterator referring to the past-the-end element in the map container.
			 * 
			 * The past-the-end element is the theoretical element that would follow the last 
			 * element in the map container. It does not point to any element, and thus shall not be dereferenced.
			 * 
			 * Because the ranges used by functions of the standard library do not include the element pointed 
			 * by their closing iterator, this function is often used in combination with map::begin to specify 
			 * a range including all the elements in the container.
			 * 
			 * If the container is empty, this function returns the same as map::begin.
			 */
			const_iterator end() const {
				return const_iterator( m_right_sentinel );
			}

			/**
			 * Return reverse iterator to reverse end
			 * 
			 * Returns a reverse iterator pointing to the theoretical element right before the first element in the map container
			 * (which is considered its reverse end).
			 * The range between map::rbegin and map::rend contains all the elements of the container (in reverse order).
			 */
			reverse_iterator rend() {
				return ( m_left_sentinel );
			}

			/**
			 * Return reverse iterator to reverse end
			 * 
			 * Returns a reverse iterator pointing to the theoretical element right before the first element in the map container
			 * (which is considered its reverse end).
			 * The range between map::rbegin and map::rend contains all the elements of the container (in reverse order).
			 */
			const_reverse_iterator rend() const {
				return ( m_left_sentinel );
			}

			/**
			 * Get allocator
			 * 
			 * Returns a copy of the allocator object associated with the map.
			 */
			allocator_type get_allocator() const {
				return m_alloc;
			}


			/**
			 * Print the binary tree structure.
			 * 
			 * Debug purpose only.
			 * 
			 * TODO: Remove before push
			 * 
			 */
			void debug_print_btree_structure(){
				debug_print_btree_structure_(m_root, 0);
			}


		/**
		 * Private implementations.
		 * 
		 */
		private:
			void debug_print_btree_structure_(rb_node *current, int space){
				if ( current != NULL ){
					space += 10;
					debug_print_btree_structure_(current->right, space);
					std::cout << std::endl;
					for ( int _ = 0 ; _ < space ; _++ ){ std::cout << " "; }
					std::cout << "( " << current->data.first << " : " << current->data.second  << ", " << (std::string[3]){ "B", "R", "S" }[current->color - 1] << " )" << std::endl;
					debug_print_btree_structure_(current->left, space);
				}
			}

			/**
			 * 
			 * Insert recursive
			 * 
			 * Insert a node recursively. It returns a pair with an iterator
			 * pointing to the node newly insrted.
			 * 
			 */
			ft::pair<iterator, bool> insert_recursive_(rb_node *current, const value_type &val){
				if ( val.first == current->data.first ){
					return ft::pair<iterator, bool>( iterator( current ), false );
				}
				if ( m_comp( val.first, current->data.first ) ){
					if ( current->left == NULL ){
						return ft::pair<iterator, bool>( iterator( current->left = rb_node::create_node( val, current ) ), true );
					} 
					else if ( current->left->is_sentinel() ){
						rb_node *node = rb_node::create_node( val, current );

						current->left = node;
						node->set_left_sentinel(m_left_sentinel);
						return ft::pair<iterator, bool>( iterator( node ), true );
					} else {
						return insert_recursive_(current->left, val);
					}
				} else {
					if ( current->right == NULL ){
						return ft::pair<iterator, bool>( iterator( current->right = rb_node::create_node( val, current ) ), true );
					} else if ( current->right->is_sentinel() ){
						rb_node *node = rb_node::create_node( val, current );

						current->right = node;
						node->set_right_sentinel(m_right_sentinel);
						return ft::pair<iterator, bool>( iterator( node ), true );
					} else {
						return insert_recursive_(current->right, val);
					}
				}
			}

			void clear_recursive_(rb_node *current){
				if ( current != NULL ){
					clear_recursive_(current->left);
					clear_recursive_(current->right);
					rb_node::destroy_node(current);
				}
			}

			rb_node *find_recursive_(const key_type &k){
				rb_node *current = m_root;

				while ( current != NULL ){
					if ( k == current->data.first ){
						return current;
					}
					if ( m_comp(k, current->data.first) ){
						current = current->left;
					} else {
						current = current->right;
					}
				}
				return NULL;
			}

			void rotate_left_(rb_node *x){
				rb_node *y = x->right;
				x->right = y->left;

				if ( y->left != NULL ){
					y->left->parent = x;
				}
				y->parent = x->parent;
				if ( x->parent == NULL ){
					m_root = y;
				}
				else if ( x == x->parent->left ){
					x->parent->left = y;
				} else {
					x->parent->right = y;
				}
				y->left = x;
				x->parent = y;
			}

			void rotate_right_(rb_node *y){
				rb_node *x = y->left;
				y->left = x->right;

				if ( x->right != NULL ){
					x->right->parent = y;
				}
				x->parent = y->parent;
				if ( y->parent == NULL ){
					m_root = x;
				}
				else if ( y == y->parent->right ){
					y->parent->right = x;
				} else {
					y->parent->left = x;
				}
				x->right = y;
				y->parent = x;
			}
	};
}


#endif
