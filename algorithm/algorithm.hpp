#ifndef _FT_ALGORITHM_HPP_
#define _FT_ALGORITHM_HPP_

namespace ft
{
	template<class InputIterator1, class InputIterator2>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
								 InputIterator2 first2, InputIterator2 last2){
		for ( ; first1 != last1 && first2 != last2 ; ++first1, ++first2 ){
			if ( *first2 < *first1 )
				return false;
			if ( *first1 < *first2 )
				return true;
		}
		return ( first1 == last1 && first2 != last2 );
	}

	template<class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
								 InputIterator2 first2, InputIterator2 last2,
								 Compare comp){
		for ( ; first1 != last1 && first2 != last2 ; ++first1, ++first2 ){
			if ( comp(*first2, *first1) )
				return false;
			if ( comp(*first1, *first2) )
				return true;
		}
		return ( first1 == last1 && first2 != last2 );
	}

	template<class InputIterator1, class InputIterator2>
	bool equal( InputIterator1 first1, InputIterator1 last1,
				InputIterator2 first2, InputIterator2 last2){
		for ( ; first1 != last1 && first2 != last2 ; ++first1, ++first2 ){
			if ( !(*first1 == *first2) )
				return false;
		}
		return ( first1 == last1 && first2 == last2 );
	}

	template<class InputIterator1, class InputIterator2, class Predicate>
	bool equal( InputIterator1 first1, InputIterator1 last1,
				InputIterator2 first2, InputIterator2 last2,
				Predicate pred){
		for ( ; first1 != last1 && first2 != last2 ; ++first1, ++first2 ){
			if ( !pred(*first1, *first2) )
				return false;
		}
		return ( first1 == last1 && first2 == last2 );
	}
}

#endif
