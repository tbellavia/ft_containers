#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <stddef.h>
#include <iterator>
#include "traits.hpp"
//#include "../map.hpp"

namespace ft {
	/**
	 * Forward declarations
	 * 
	 */
    template<typename Category, typename T, typename Distance = ptrdiff_t , typename Pointer = T*, typename Reference = T&>
    struct iterator {
        typedef Category        iterator_category;
        typedef T               value_type;
        typedef Distance        difference_type;
        typedef Pointer         pointer;
        typedef Reference       reference;
    };

    /**
     * Iterator traits
     *
     * Define a traits for iterators.
     *
     */
    template<typename Iterator>
    struct iterator_traits {
        typedef typename Iterator::iterator_category    iterator_category;
        typedef typename Iterator::value_type           value_type;
        typedef typename Iterator::difference_type      difference_type;
        typedef typename Iterator::pointer              pointer;
        typedef typename Iterator::reference            reference;
    };

    template<typename T>
    struct iterator_traits<T *> {
        typedef std::random_access_iterator_tag         iterator_category;
        typedef T                                       value_type;
        typedef ptrdiff_t                               difference_type;
        typedef T                                       *pointer;
        typedef T                                       &reference;
    };

    template<typename T>
    struct iterator_traits<const T *> {
        typedef std::random_access_iterator_tag         iterator_category;
        typedef T                                       value_type;
        typedef ptrdiff_t                               difference_type;
        typedef const T                                 *pointer;
        typedef const T                                 &reference;
    };


    template<class InputIterator>
    typename iterator_traits<InputIterator>::difference_type
    distance(InputIterator first, InputIterator last, std::input_iterator_tag){
        typename iterator_traits<InputIterator>::difference_type n = 0;

        while ( first != last ){
            ++first;
            ++n;
        }
        return n;
    }

    template<class RandomAccessIterator>
    typename iterator_traits<RandomAccessIterator>::difference_type
    distance(RandomAccessIterator first, RandomAccessIterator last, std::random_access_iterator_tag){
        return last - first;
    }

    template<class Iterator>
    typename iterator_traits<Iterator>::difference_type
    distance(Iterator first, Iterator last){
        return ft::distance(first, last, typename iterator_traits<Iterator>::iterator_category());
    }

    /* Reverse iterator */
    template<class Iter>
    class reverse_iterator : public ft::iterator<
            typename ft::iterator_traits<Iter>::iterator_category,
            typename ft::iterator_traits<Iter>::value_type,
            typename ft::iterator_traits<Iter>::difference_type,
            typename ft::iterator_traits<Iter>::pointer,
            typename ft::iterator_traits<Iter>::reference>
    {
    private:
        Iter                                            current;
        typedef iterator_traits<Iter>                   _traits_type;
    public:
        typedef Iter                                    iterator_type;
        typedef typename _traits_type::difference_type	difference_type;
        typedef typename _traits_type::pointer		    pointer;
        typedef typename _traits_type::reference		reference;

        reverse_iterator() : current() { }
        explicit reverse_iterator(iterator_type x) : current( x ) { }

        template<class Iter_>
        reverse_iterator(reverse_iterator<Iter_> const &x) : current(x.base()) { }


        template<class Iter_>
        reverse_iterator &operator=(reverse_iterator<Iter_> const &x){
            current = x.base();
            return *this;
        }
//        ~reverse_iterator() { }

        iterator_type base() const
        { return current; }

        reference operator*() const {
            iterator_type tmp = current;
            return *--tmp;
        }

        pointer operator->() const {
            iterator_type tmp = current;

            --tmp;
            return to_pointer(tmp);
        }

        /* Arithmetic */
        reverse_iterator &operator++(){
            --current;
            return *this;
        }

        reverse_iterator operator++(int){
            reverse_iterator tmp = *this;
            --current;
            return tmp;
        }

        reverse_iterator &operator--(){
            ++current;
            return *this;
        }

        reverse_iterator operator--(int){
            reverse_iterator tmp = *this;
            ++current;
            return tmp;
        }

        reverse_iterator operator+(difference_type n) const {
            return reverse_iterator(current - n);
        }

        reverse_iterator &operator+=(difference_type n) {
            current -= n;
            return *this;
        }

        reverse_iterator operator-(difference_type n) const {
            return reverse_iterator(current + n);
        }

        reverse_iterator &operator-=(difference_type n) {
            current += n;
            return *this;
        }

        reference operator[](difference_type n) const {
            return *(*this + n);
        }

    private:
        template<class T>
        static pointer to_pointer(T p){
            return p.operator->();
        }

        template<class T>
        static T* to_pointer(T* p){
            return p;
        }
    };

    template<class Iter>
    inline bool operator==(reverse_iterator<Iter> const &x, reverse_iterator<Iter> const &y)
    { return x.base() == y.base(); }

    template<class Iter>
    inline bool operator<(reverse_iterator<Iter> const &x, reverse_iterator<Iter> const &y)
    { return x.base() > y.base(); }

    template<class Iter>
    inline bool operator<=(reverse_iterator<Iter> const &x, reverse_iterator<Iter> const &y)
    { return x.base() >= y.base(); }

    template<class Iter>
    inline bool operator!=(reverse_iterator<Iter> const &x, reverse_iterator<Iter> const &y)
    { return x.base() != y.base(); }

    template<class Iter>
    inline bool operator>(reverse_iterator<Iter> const &x, reverse_iterator<Iter> const &y)
    { return x.base() < y.base(); }

    template<class Iter>
    inline bool operator>=(reverse_iterator<Iter> const &x, reverse_iterator<Iter> const &y)
    { return x.base() <= y.base(); }

    /* Overload to compare reverse_iterator with const reverse_iterator */

    template<class IterL, class IterR>
    inline bool operator==(reverse_iterator<IterL> const &x, reverse_iterator<IterR> const &y)
    { return x.base() == y.base(); }

    template<class IterL, class IterR>
    inline bool operator<(reverse_iterator<IterL> const &x, reverse_iterator<IterR> const &y)
    { return x.base() > y.base(); }

    template<class IterL, class IterR>
    inline bool operator<=(reverse_iterator<IterL> const &x, reverse_iterator<IterR> const &y)
    { return x.base() >= y.base(); }

    template<class IterL, class IterR>
    inline bool operator!=(reverse_iterator<IterL> const &x, reverse_iterator<IterR> const &y)
    { return x.base() != y.base(); }

    template<class IterL, class IterR>
    inline bool operator>(reverse_iterator<IterL> const &x, reverse_iterator<IterR> const &y)
    { return x.base() < y.base(); }

    template<class IterL, class IterR>
    inline bool operator>=(reverse_iterator<IterL> const &x, reverse_iterator<IterR> const &y)
    { return x.base() <= y.base(); }

    template<class Iterator>
    inline typename reverse_iterator<Iterator>::difference_type
    operator-(reverse_iterator<Iterator> const &x, reverse_iterator<Iterator> const &y){
        return y.base() - x.base();
    }

    template<class IteratorL, class IteratorR>
    inline typename reverse_iterator<IteratorL>::difference_type
    operator-(reverse_iterator<IteratorL> const &x, reverse_iterator<IteratorR> const &y){
        return y.base() - x.base();
    }

    template<class Iterator>
    inline reverse_iterator<Iterator>
    operator+(typename reverse_iterator<Iterator>::difference_type n, reverse_iterator<Iterator> const &i){
        return reverse_iterator<Iterator>( i.base() - n );
    }

	/**
	 * Random Access Iterator
	 * 
	 */

	template<class Iterator>
	class normal_iterator : public ft::iterator<std::bidirectional_iterator_tag, Iterator> {
		private:
			typedef ft::iterator_traits<Iterator>				_traits_type;
		public:
            typedef Iterator                                    iterator_type;
			typedef typename _traits_type::iterator_category	iterator_category;
			typedef typename _traits_type::value_type			value_type;
			typedef typename _traits_type::difference_type		difference_type;
			typedef typename _traits_type::reference			reference;
			typedef typename _traits_type::pointer				pointer;

			/* Constructors */
			normal_iterator() : m_current( iterator_type() ) { }
			explicit normal_iterator(iterator_type const &p) : m_current( p ) { }

            template<class Iter>
			normal_iterator(normal_iterator<Iter> const &it) : m_current( it.base() ) { }

//            template<class Iter>
//			normal_iterator &operator=(normal_iterator<Iter> const &it) {
//				m_current = it.base();
//				return *this;
//			}
			~normal_iterator() {}

			/* Accesses operators */
			const iterator_type &base() const { return m_current; }
			reference operator*() const { return *m_current; }
			pointer operator->() const { return m_current; }
			reference operator[](difference_type offset) const { return m_current[offset]; }

			/* Increment / Decrement */
			normal_iterator &operator++() { m_current++; return *this; };
			normal_iterator operator++(int) { normal_iterator tmp = *this; ++(*this); return tmp; }
			normal_iterator &operator--() { m_current--; return *this; }
			normal_iterator operator--(int) { normal_iterator tmp = *this; --(*this); return tmp; }

			/* Arithmetic */
			normal_iterator &operator+=(difference_type offset) { m_current += offset; return *this; }
			normal_iterator &operator-=(difference_type offset) { m_current -= offset; return *this; }
			
			normal_iterator operator+(difference_type offset) const { return normal_iterator( m_current + offset ); }
			normal_iterator operator-(difference_type offset) const { return normal_iterator( m_current - offset ); }
		private:
			iterator_type m_current;
	};

    /* normal_iterator_comparison */
    template<class Iter>
    inline bool operator==(normal_iterator<Iter> const &x, normal_iterator<Iter> const &y)
    { return x.base() == y.base(); }

    template<class Iter>
    inline bool operator<(normal_iterator<Iter> const &x, normal_iterator<Iter> const &y)
    { return x.base() < y.base(); }

    template<class Iter>
    inline bool operator<=(normal_iterator<Iter> const &x, normal_iterator<Iter> const &y)
    { return x.base() <= y.base(); }

    template<class Iter>
    inline bool operator!=(normal_iterator<Iter> const &x, normal_iterator<Iter> const &y)
    { return x.base() != y.base(); }

    template<class Iter>
    inline bool operator>(normal_iterator<Iter> const &x, normal_iterator<Iter> const &y)
    { return x.base() > y.base(); }

    template<class Iter>
    inline bool operator>=(normal_iterator<Iter> const &x, normal_iterator<Iter> const &y)
    { return x.base() >= y.base(); }

    /* Overload to compare reverse_iterator with const reverse_iterator */

    template<class IterL, class IterR>
    inline bool operator==(normal_iterator<IterL> const &x, normal_iterator<IterR> const &y)
    { return x.base() == y.base(); }

    template<class IterL, class IterR>
    inline bool operator<(normal_iterator<IterL> const &x, normal_iterator<IterR> const &y)
    { return x.base() < y.base(); }

    template<class IterL, class IterR>
    inline bool operator<=(normal_iterator<IterL> const &x, normal_iterator<IterR> const &y)
    { return x.base() <= y.base(); }

    template<class IterL, class IterR>
    inline bool operator!=(normal_iterator<IterL> const &x, normal_iterator<IterR> const &y)
    { return x.base() != y.base(); }

    template<class IterL, class IterR>
    inline bool operator>(normal_iterator<IterL> const &x, normal_iterator<IterR> const &y)
    { return x.base() > y.base(); }

    template<class IterL, class IterR>
    inline bool operator>=(normal_iterator<IterL> const &x, normal_iterator<IterR> const &y)
    { return x.base() >= y.base(); }

    template<class Iterator>
    inline typename normal_iterator<Iterator>::difference_type
    operator-(normal_iterator<Iterator> const &x, normal_iterator<Iterator> const &y){
        return x.base() - y.base();
    }

    template<class IteratorL, class IteratorR>
    inline typename normal_iterator<IteratorL>::difference_type
    operator-(normal_iterator<IteratorL> const &x, normal_iterator<IteratorR> const &y){
        return x.base() - y.base();
    }

    template<class Iterator>
    inline normal_iterator<Iterator>
    operator+(typename normal_iterator<Iterator>::difference_type n, normal_iterator<Iterator> const &i){
        return normal_iterator<Iterator>( i.base() + n );
    }
}

#endif
