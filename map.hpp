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
		private:
			/**
			 * Forward declarations.
			 * 
			 */
			struct rb_node;
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


		/**
		 * Private declarations.
		 * 
		 */
		private:
			rb_node					*m_root;
			allocator_type			m_alloc;
			rb_node::allocator_type m_rb_alloc;

		/**
		 * Private implementations.
		 * 
		 */
		private:
			rb_node *create_node(){
				rb_node *node = m_rb_alloc.allocate( 1 );

				m_rb_alloc.construct( node );
				return node;
			}

			rb_node *create_node( const value_type &data ){
				rb_node *node = m_rb_alloc.allocate( 1 );

				m_rb_alloc.construct( node, data );
				return node;
			}

			rb_node *create_node( const value_type &data, rb_node *parent ){
				rb_node *node = m_rb_alloc.allocate( 1 );

				m_rb_alloc.construct( node, data, parent );
				return node;
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
				rb_color	color;

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
					: data( value_type() ), parent( nullptr ), left( nullptr ), right( nullptr ), color( rb_color::RED ) { }

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
					: data( __data ), parent( nullptr ), left( nullptr ), right( nullptr ), color( rb_color::RED ) { }

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
					: data( __data ), parent( __parent ), left( nullptr ), right( nullptr ), color( rb_color::RED ) { }

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
