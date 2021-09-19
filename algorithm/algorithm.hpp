#ifndef _FT_ALGORITHM_HPP_
#define _FT_ALGORITHM_HPP_

namespace ft
{
	/**
	 * Lexicographical less-than comparison
	 * 
	 * Returns true if the range [first1,last1) compares lexicographically less than the range [first2,last2).
	 * 
	 * A lexicographical comparison is the kind of comparison generally used to sort 
	 * words alphabetically in dictionaries; It involves comparing sequentially 
	 * the elements that have the same position in both ranges against each other 
	 * until one element is not equivalent to the other. The result of comparing 
	 * these first non-matching elements is the result of the lexicographical comparison.
	 * 
	 * If both sequences compare equal until one of them ends, the shorter sequence is lexicographically
	 * less than the longer one.
	 * 
	 * The elements are compared using operator< for the first version, and comp for the second.
	 * Two elements, a and b are considered equivalent if (!(a<b) && !(b<a)) or if (!comp(a,b) && !comp(b,a)).
	 * 
	 * 
	 */
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

	/**
	 * Test whether the elements in two ranges are equal
	 * 
	 * Compares the elements in the range [first1,last1) with those in the range beginning at first2,
	 * and returns true if all of the elements in both ranges match.
	 * 
	 */
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
