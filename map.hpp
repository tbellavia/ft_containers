#ifndef MAP_HPP
#define MAP_HPP

# include <functional>
# include <memory>
# include "utility/pair.hpp"
# include "traits/iterator/map_iterator.hpp"

namespace ft
{
	template<
		class Key,												// map::key_type
		class T,												// map::mapped_type
		class Compare = std::less<Key>,							// map::key_compare
		class Alloc = std::allocator<ft::pair<const Key, T> >	// map::allocator_type
	>
	class map {
		private:
			/**
			 * Forward declarations.
			 * 
			 */
			struct rb_node;
		public:
			typedef Key											key_type;
			typedef T											mapped_type;
			typedef ft::pair<const key_type, mapped_type>		value_type;
			typedef Compare										key_compare;
			// TODO: Add value_comp
			// typedef value_compare							
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef std::ptrdiff_t								difference_type;
			typedef std::size_t									size_type;
			typedef ft::map_::random_access_iterator<rb_node>			iterator;
			typedef ft::map_::const_random_access_iterator<rb_node>	const_iterator;
			typedef ft::map_::reverse_iterator<rb_node>				reverse_iterator;
			typedef ft::map_::const_reverse_iterator<rb_node>			const_reverse_iterator;
		/**
		 * Private declarations.
		 * 
		 */
		private:
			rb_node					*m_root;
			size_type				m_size;
			key_compare				m_comp;
			allocator_type			m_alloc;
			typename rb_node::allocator_type m_rb_alloc;

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
				: m_root( nullptr ), m_size( 0 ), m_comp( comp ), m_alloc( alloc ), m_rb_alloc( std::allocator<rb_node>() ) { }
			

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
				if ( m_root == nullptr ){
					return ft::pair<iterator, bool>( iterator( m_root = this->create_node_(val) ), true );
				}
				return insert_recursive_(m_root, val);
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
				if ( current != nullptr ){
					space += 10;
					debug_print_btree_structure_(current->right, space);
					std::cout << std::endl;
					for ( int _ = 0 ; _ < space ; _++ ){ std::cout << " "; }
					std::cout << "( " << current->data.first << " : " << current->data.second  << ", " << ((current->color == BLACK) ? "B" : "R") << " )" << std::endl;
					debug_print_btree_structure_(current->left, space);
				}
			}

			ft::pair<iterator, bool> insert_recursive_(rb_node *current, const value_type &val){
				if ( current != nullptr ){
					if ( val.first == current->data.first ){
						return ft::pair<iterator, bool>( iterator( current ), false );
					}
					if ( m_comp( val.first, current->data.first ) ){
						if ( current->left == NULL ){
							return ft::pair<iterator, bool>( iterator( current->left = this->create_node_(val, current) ), true );
						} else {
							return insert_recursive_(current->left, val);
						}
					} else {
						if ( current->right == NULL ){
							return ft::pair<iterator, bool>( iterator( current->right = this->create_node_(val, current) ), true );
						} else {
							return insert_recursive_(current->right, val);
						}
					}
				}
				return ft::pair<iterator, bool>( iterator( current ), false );
			}

			rb_node *create_node_(){
				rb_node *node = m_rb_alloc.allocate( 1 );

				m_rb_alloc.construct( node );
				return node;
			}

			rb_node *create_node_( const value_type &data ){
				rb_node *node = m_rb_alloc.allocate( 1 );

				m_rb_alloc.construct( node, data );
				return node;
			}

			rb_node *create_node_( const value_type &data, rb_node *parent ){
				rb_node *node = m_rb_alloc.allocate( 1 );

				m_rb_alloc.construct( node, data, parent );
				return node;
			}

			void rotate_left_(rb_node *x){
				rb_node *y = x->right;
				x->right = y->left;

				if ( y->left != nullptr ){
					y->left->parent = x;
				}
				y->parent = x->parent;
				if ( x->parent == nullptr ){
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

				if ( x->right != nullptr ){
					x->right->parent = y;
				}
				x->parent = y->parent;
				if ( y->parent == nullptr ){
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

			enum rb_color { BLACK = 1, RED };
			/**
			 * Internal struct representing a binary tree node.
			 * 
			 */
			struct rb_node {
				value_type	data;
				rb_node		*parent;
				rb_node		*left;
				rb_node		*right;
				int			color;

				/**
				 * Default constructor
				 * 
				 * Constructs a new empty node with default value_type() and all
				 * pointers to nullptr.
				 * 
				 * Color is always set to RED as it will always be inserted as a RED
				 * node.
				 * 
				 */
				rb_node() 
					: data( value_type() ), parent( nullptr ), left( nullptr ), right( nullptr ), color( RED ) { }

				/**
				 * Data constructor
				 * 
				 * Constructs a new node with data and all pointers to nullptr.
				 * 
				 * Color is always set to RED as it will always be inserted as a RED
				 * node.
				 * 
				 */
				rb_node( const value_type &__data )
					: data( __data ), parent( nullptr ), left( nullptr ), right( nullptr ), color( RED ) { }

				/**
				 * Data-Parent constructor
				 * 
				 * Constructs a new node with data and a parent, right and left 
				 * pointers are set to nullptr.
				 * 
				 * Color is always set to RED as it will always be inserted as a RED
				 * node.
				 * 
				 */
				rb_node( const value_type &__data, rb_node *__parent )
					: data( __data ), parent( __parent ), left( nullptr ), right( nullptr ), color( RED ) { }

				/**
				 * Get the grand parent
				 * 
				 * Returns the grand parent of the current node.
				 * 
				 */
				rb_node *grand_parent() {
					if ( this->parent == nullptr )
						return nullptr;
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

					if ( gp == nullptr )
						return nullptr;
					return this->parent->sibling();
				}

				/**
				 * Get the sibling node
				 * 
				 * Returns the sibling node.
				 * 
				 */
				rb_node *sibling() {
					if ( this->parent == nullptr )
						return nullptr;
					if ( this == this->parent->left )
						return this->parent->right;
					return this->parent->left;
				}

				typedef std::allocator<rb_node> allocator_type;
			};
	};
}


#endif
