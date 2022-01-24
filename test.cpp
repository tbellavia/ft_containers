//
// Created by kyoto on 23/01/2022.
//

#include <iostream>
#include <cstdio>
#include <deque>

#ifdef FT
    #include "vector.hpp"
    #include "stack.hpp"
    #include "map.hpp"
#else
    #include <vector>
    #include <stack>
    #include <map>
    namespace ft = std;
#endif

// Define greater operator
template<typename T>
struct Greater : public std::binary_function<T, T, bool>
{
    bool operator()(const T& lhs, const T& rhs) const { return lhs > rhs; }
};

// Define dummy object for testing purpose
struct Dummy {
    int m_x;

    Dummy() : m_x(42) {
//        std::cout << "Dummy()" << std::endl;
    }

    Dummy(int x) : m_x(x) {
//        std::cout << "Dummy(int)" << std::endl;
    }

    Dummy(const Dummy &x) {
        m_x = x.m_x;
//        std::cout << "Dummy(const Dummy&)" << std::endl;
    }
    Dummy &operator=(const Dummy &x) {
//        std::cout << "Dummy=(const Dummy&)" << std::endl;
        m_x = x.m_x;
        return *this;
    }

    ~Dummy() {
//        std::cout << "~Dummy()" << std::endl;
    }
};

std::ostream &operator<<(std::ostream &os, const Dummy &x){
    os << "Dummy<x=" << x.m_x << ">";
    return os;
}

template<class A, class B>
std::ostream &operator<<(std::ostream &os, const ft::pair<A, B> &p){
    os << "(" << p.first << " : " << p.second << ")";
    return os;
}

#define LOG_HELPER(line, func, msg, test) \
    std::cout << line << ": " << func << ": " << msg << ": " << test << std::endl
#define LOG(msg, test) LOG_HELPER(__LINE__, __FUNCTION__, msg, test)
#define LOG_EACH(msg, begin, end) LOG_HELPER(__LINE__, __FUNCTION__, msg, ""); show_each(begin, end)

template<typename Iter>
void show_each(Iter begin, Iter end){
    for ( ; begin != end ; ++begin )
        std::cout << *begin << " ";
    std::cout << std::endl;
}

void test_vector_default_constructor(){
    ft::vector<int> vec;

    LOG("size", vec.size());
    LOG("capacity", vec.capacity());
    LOG("iterator", (vec.begin() == vec.end()));
}

void test_vector_fill_constructor(){
    {
        ft::vector<int> vec(10, 42);

        LOG("size", vec.size());
        LOG("capacity", vec.capacity());
        LOG_EACH("iterator", vec.begin(), vec.end());
    }
    {
        ft::vector<float> vec(10, 3.1415);

        LOG("size", vec.size());
        LOG("capacity", vec.capacity());
        LOG_EACH("iterator", vec.begin(), vec.end());
    }
    {
        ft::vector<int> vec(0, 0);

        LOG("size", vec.size());
        LOG("capacity", vec.capacity());
        LOG_EACH("iterator", vec.begin(), vec.end());
    }
    {
        ft::vector<Dummy> vec(0, Dummy(1331));

        LOG("size", vec.size());
        LOG("capacity", vec.capacity());
        LOG_EACH("iterator", vec.begin(), vec.end());
    }
}

void test_vector_range_constructor(){
    {
        int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        {
            ft::vector<int> vec(array, array + 10);

            LOG("size", vec.size());
            LOG("capacity", vec.capacity());
            LOG_EACH("iterator", vec.begin(), vec.end());
        }
        {
            ft::vector<int> vec(array, array + 5);

            LOG("size", vec.size());
            LOG("capacity", vec.capacity());
            LOG_EACH("iterator", vec.begin(), vec.end());
        }
        {
            ft::vector<int> vec(array, array);

            LOG("size", vec.size());
            LOG("capacity", vec.capacity());
            LOG_EACH("iterator", vec.begin(), vec.end());
        }
    }
    {
        Dummy array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        {
            ft::vector<Dummy> vec(array, array + 10);

            LOG("size", vec.size());
            LOG("capacity", vec.capacity());
            LOG_EACH("iterator", vec.begin(), vec.end());
        }
        {
            ft::vector<Dummy> vec(array, array + 5);

            LOG("size", vec.size());
            LOG("capacity", vec.capacity());
            LOG_EACH("iterator", vec.begin(), vec.end());
        }
        {
            ft::vector<Dummy> vec(array, array);

            LOG("size", vec.size());
            LOG("capacity", vec.capacity());
            LOG_EACH("iterator", vec.begin(), vec.end());
        }
    }
}

void test_vector_copy_constructor(){
    {
        ft::vector<int>		copy;
        ft::vector<int>		vec(copy);

        LOG("size", vec.size());
        LOG("capacity", vec.capacity());
        LOG_EACH("iterator", vec.begin(), vec.end());
    }
    {
        ft::vector<int>		copy(10, 42);
        ft::vector<int>		vec(copy);

        LOG("size", vec.size());
        LOG("capacity", vec.capacity());
        LOG_EACH("iterator", vec.begin(), vec.end());
    }
    {
        ft::vector<int>		copy(100, 42);
        ft::vector<int>		vec(copy);

        LOG("size", vec.size());
        LOG("capacity", vec.capacity());
        LOG_EACH("iterator", vec.begin(), vec.end());
    }
}

void test_vector_assignment_operator(){
    // Empty, Full
    {
        ft::vector<int> one;
        ft::vector<int> two(10, 42);

        one = two;

        LOG("capacity", one.capacity());
        LOG("capacity", two.capacity());

        LOG("capacity", one.size());
        LOG("capacity", two.size());

        LOG_EACH("iterator", one.begin(), one.end());
        LOG_EACH("iterator", two.begin(), two.end());
    }

    // Full, Empty
    {
        ft::vector<int> one(10, 42);
        ft::vector<int> two;

        one = two;

        LOG("capacity", one.capacity());
        LOG("capacity", two.capacity());

        LOG("capacity", one.size());
        LOG("capacity", two.size());

        LOG_EACH("iterator", one.begin(), one.end());
        LOG_EACH("iterator", two.begin(), two.end());
    }

    // Full, Full
    {
        ft::vector<int> one(10, 42);
        ft::vector<int> two(42, 10);

        one = two;

        LOG("capacity", one.capacity());
        LOG("capacity", two.capacity());

        LOG("capacity", one.size());
        LOG("capacity", two.size());

        LOG_EACH("iterator", one.begin(), one.end());
        LOG_EACH("iterator", two.begin(), two.end());
    }

    // Empty, Empty
    {
        ft::vector<int> one;
        ft::vector<int> two;

        one = two;

        LOG("capacity", one.capacity());
        LOG("capacity", two.capacity());

        LOG("capacity", one.size());
        LOG("capacity", two.size());

        LOG_EACH("iterator", one.begin(), one.end());
        LOG_EACH("iterator", two.begin(), two.end());
    }

//    Complex object
    // Empty, Full
    {
        ft::vector<Dummy> one;
        ft::vector<Dummy> two(10, Dummy(1331));

        one = two;

        LOG("capacity", one.capacity());
        LOG("capacity", two.capacity());

        LOG("capacity", one.size());
        LOG("capacity", two.size());

        LOG_EACH("iterator", one.begin(), one.end());
        LOG_EACH("iterator", two.begin(), two.end());
    }

    // Full, Empty
    {
        ft::vector<Dummy> one(10, Dummy(1331));
        ft::vector<Dummy> two;

        one = two;

        LOG("capacity", one.capacity());
        LOG("capacity", two.capacity());

        LOG("capacity", one.size());
        LOG("capacity", two.size());

        LOG_EACH("iterator", one.begin(), one.end());
        LOG_EACH("iterator", two.begin(), two.end());
    }


    // Full, Full
    {
        ft::vector<Dummy> one(10, Dummy(1331));
        ft::vector<Dummy> two(42, Dummy(10));

        one = two;

        LOG("capacity", one.capacity());
        LOG("capacity", two.capacity());

        LOG("capacity", one.size());
        LOG("capacity", two.size());

        LOG_EACH("iterator", one.begin(), one.end());
        LOG_EACH("iterator", two.begin(), two.end());
    }

    // Empty, Empty
    {
        ft::vector<Dummy> one;
        ft::vector<Dummy> two;

        one = two;

        LOG("capacity", one.capacity());
        LOG("capacity", two.capacity());

        LOG("capacity", one.size());
        LOG("capacity", two.size());

        LOG_EACH("iterator", one.begin(), one.end());
        LOG_EACH("iterator", two.begin(), two.end());
    }
}

void test_vector_iterator(){
    {
        ft::vector<int> vec;

        for ( int i = 0 ; i < 10 ; i++){
            vec.push_back(i);
        }

        LOG_EACH("iterator", vec.begin(), vec.end());
    }
    {
        ft::vector<int> vec;
        ft::vector<int>::const_iterator begin;
        ft::vector<int>::const_iterator end;

        for ( int i = 0 ; i < 10 ; i++){
            vec.push_back(i);
        }
        begin = vec.begin();
        end = vec.end();
        LOG_EACH("iterator", begin, end);
    }
    {
        ft::vector<Dummy> vec;

        for ( int i = 0 ; i < 10 ; i++){
            vec.push_back(Dummy(i));
        }

        LOG_EACH("iterator", vec.begin(), vec.end());
    }
    {
        ft::vector<Dummy> vec;
        ft::vector<Dummy>::const_iterator begin;
        ft::vector<Dummy>::const_iterator end;

        for ( int i = 0 ; i < 10 ; i++){
            vec.push_back(Dummy(i));
        }
        begin = vec.begin();
        end = vec.end();
        LOG_EACH("iterator", begin, end);
    }
}

void test_vector_reverse_iterator(){
    {
        ft::vector<int> vec;

        for ( int i = 0 ; i < 10 ; i++){
            vec.push_back(i);
        }

        LOG_EACH("iterator", vec.rbegin(), vec.rend());
    }
    {
        ft::vector<int> vec;
        ft::vector<int>::const_reverse_iterator begin;
        ft::vector<int>::const_reverse_iterator end;

        for ( int i = 0 ; i < 10 ; i++){
            vec.push_back(i);
        }
        begin = vec.rbegin();
        end = vec.rend();
        LOG_EACH("iterator", begin, end);
    }
    {
        ft::vector<Dummy> vec;

        for ( int i = 0 ; i < 10 ; i++){
            vec.push_back(Dummy(i));
        }

        LOG_EACH("iterator", vec.rbegin(), vec.rend());
    }
    {
        ft::vector<Dummy> vec;
        ft::vector<Dummy>::const_reverse_iterator begin;
        ft::vector<Dummy>::const_reverse_iterator end;

        for ( int i = 0 ; i < 10 ; i++){
            vec.push_back(Dummy(i));
        }
        begin = vec.rbegin();
        end = vec.rend();
        LOG_EACH("iterator", begin, end);
    }
}

void test_vector_max_size(){
    LOG("max size", ft::vector<int>().max_size());
    LOG("max size", ft::vector<bool>().max_size());
    LOG("max size", ft::vector<char>().max_size());
    LOG("max size", ft::vector<std::string>().max_size());
    LOG("max size", ft::vector<Dummy>().max_size());
}

void test_vector_capacity(){
    ft::vector<int> vec;

    LOG("capacity", vec.capacity());

    vec.reserve(100);
    LOG("capacity", vec.capacity());
}

void test_vector_resize(){
    ft::vector<int> vec;

    for ( int index = 0 ; index < 5 ; index++ ){
        vec.push_back(index);
    }

    vec.resize(2, 10);
    LOG("size", vec.size());
    LOG("capacity", vec.capacity());
    LOG_EACH("iterator", vec.begin(), vec.end());

    vec.resize(20, 10);
    LOG("size", vec.size());
    LOG("capacity", vec.capacity());
    LOG_EACH("iterator", vec.begin(), vec.end());
}

void test_vector_access(){
    ft::vector<int> vec;

    for ( int i = 0 ; i < 5 ; i++ ){
        vec.push_back(i);
    }

    for ( int i = 0 ; i < 5 ; i++ ){
        LOG("bracket access", vec[i]);
    }

    LOG("front", vec.front());
    LOG("back", vec.back());
}

void test_vector_at(){
    ft::vector<int> vec;

    for ( int i = 0 ; i < 5 ; i++ ){
        vec.push_back(i);
    }

    for ( int i = 0 ; i < 5 ; i++ ){
        LOG("at access", vec.at(i));
    }
    try {
        vec.at(vec.size());
        LOG("exception", false);
    } catch ( std::out_of_range &e ){
        LOG("exception", true);
    }
}

void test_vector_assign(){
    ft::vector<int>		fill_vec;
    ft::vector<int>		vec;
    int fill[] = {1, 2, 3, 4, 5, 6};

    for ( int index = 0 ; index < 10 ; index++ ){
        fill_vec.push_back( index + 1 );
    }


    vec.assign(10, 1);
    LOG("size", vec.size());
    LOG("capacity", vec.capacity());
    LOG_EACH("iterator", vec.begin(), vec.end());

    vec.assign(20, 5);
    LOG("size", vec.size());
    LOG("capacity", vec.capacity());
    LOG_EACH("iterator", vec.begin(), vec.end());

    vec.assign(5, 42);
    LOG("size", vec.size());
    LOG("capacity", vec.capacity());
    LOG_EACH("iterator", vec.begin(), vec.end());

    vec.assign( fill, fill + 6 );
    LOG("size", vec.size());
    LOG("capacity", vec.capacity());
    LOG_EACH("iterator", vec.begin(), vec.end());

    vec.assign( fill_vec.begin(), fill_vec.end() );
    LOG("size", vec.size());
    LOG("capacity", vec.capacity());
    LOG_EACH("iterator", vec.begin(), vec.end());
}

void test_vector_pop_back(){
    ft::vector<int>		vec;

    vec.push_back(10);
    vec.pop_back();

    LOG("size", vec.size());
    LOG("capacity", vec.capacity());
    LOG_EACH("iterator", vec.begin(), vec.end());

    for ( int i = 0 ; i < 10 ; i++){
        vec.push_back(i);
    }

    vec.pop_back();
    LOG("size", vec.size());
    LOG("capacity", vec.capacity());
    LOG_EACH("iterator", vec.begin(), vec.end());
}

void test_vector_insert(){
    {
        ft::vector<int>::iterator   it;
        ft::vector<int>             vec;

        // Reallocation
        it = vec.insert(vec.begin(), 42);
        LOG("size", vec.size());
        LOG("capacity", vec.capacity());
        LOG_EACH("iterator", vec.begin(), vec.end());
        LOG("iterator", *it);

        vec.assign(20, 5);

        it = vec.insert(vec.begin(), 10);

        // Begin
        LOG("size", vec.size());
        LOG("capacity", vec.capacity());
        LOG_EACH("iterator", vec.begin(), vec.end());
        LOG("iterator", *it);

        // End
        it = vec.insert(vec.end(), 100);

        LOG("size", vec.size());
        LOG("capacity", vec.capacity());
        LOG_EACH("iterator", vec.begin(), vec.end());
        LOG("iterator", *it);

        // Middle
        it = vec.insert(vec.begin() + (vec.size() / 2), 1000);

        LOG("size", vec.size());
        LOG("capacity", vec.capacity());
        LOG_EACH("iterator", vec.begin(), vec.end());
        LOG("iterator", *it);
    }
    {
        ft::vector<int>		vec;

        // Reallocation

        /**
         * FIXME: Invalid pointer for iterator when ft::vec is default constructed.
         *
         */
        vec.insert(vec.begin(), 10, 42);
        LOG("size", vec.size());
        LOG("capacity", vec.capacity());
        LOG_EACH("iterator", vec.begin(), vec.end());

        // Begin
        vec.insert(vec.begin(), 10, 142);
        LOG("size", vec.size());
        LOG("capacity", vec.capacity());
        LOG_EACH("iterator", vec.begin(), vec.end());

        // End
        vec.insert(vec.begin() + (vec.size() / 2), 10, 142);
        LOG("size", vec.size());
        LOG("capacity", vec.capacity());
        LOG_EACH("iterator", vec.begin(), vec.end());

        // Middle
        vec.insert(vec.begin() + (vec.size() / 2), 10, 142);
        LOG("size", vec.size());
        LOG("capacity", vec.capacity());
        LOG_EACH("iterator", vec.begin(), vec.end());
    }
    {
        int fill[]			= {1, 2, 3, 4, 5, 6};
        int fill2[]			= {6, 5, 4, 3, 2, 1};

        ft::vector<int>		vec;

        // Reallocation
        vec.insert(vec.begin(), fill, fill + 6);

        LOG("size", vec.size());
        LOG("capacity", vec.capacity());
        LOG_EACH("iterator", vec.begin(), vec.end());

        // Begin
        vec.insert(vec.begin(), fill2, fill2 + 6);

        LOG("size", vec.size());
        LOG("capacity", vec.capacity());
        LOG_EACH("iterator", vec.begin(), vec.end());

        // End
        vec.insert(vec.end(), fill, fill + 6);

        LOG("size", vec.size());
        LOG("capacity", vec.capacity());
        LOG_EACH("iterator", vec.begin(), vec.end());

        // Middle
        vec.insert(vec.begin() + (vec.size() / 2), fill2, fill2 + 6);

        LOG("size", vec.size());
        LOG("capacity", vec.capacity());
        LOG_EACH("iterator", vec.begin(), vec.end());

        // Fill empty
        vec.insert(vec.begin(), fill, fill);

        LOG("size", vec.size());
        LOG("capacity", vec.capacity());
        LOG_EACH("iterator", vec.begin(), vec.end());
    }
}

void test_vector_erase(){
    ft::vector<int>::iterator it;

    {
        ft::vector<int> vec;

        for ( int i = 0 ; i < 100 ; i++ ){
            vec.push_back(i);
        }

        // Begin
        it = vec.erase(vec.begin());

        LOG("size", vec.size());
        LOG("capacity", vec.capacity());
        LOG("return", *it);
        LOG_EACH("iterator", vec.begin(), vec.end());

        // End
        it = vec.erase(vec.end() - 1);

        LOG("size", vec.size());
        LOG("capacity", vec.capacity());
        LOG("return", *it);
        LOG_EACH("iterator", vec.begin(), vec.end());

        // Middle
        it = vec.erase(vec.begin() + (vec.size() / 2));

        LOG("size", vec.size());
        LOG("capacity", vec.capacity());
        LOG("return", *it);
        LOG_EACH("iterator", vec.begin(), vec.end());
    }
    {
        ft::vector<int>		vec;

        for ( int i = 0 ; i < 100 ; i++ ){
            vec.push_back(i);
        }

        // Begin
        it = vec.erase(vec.begin(), vec.begin() + 10);

        LOG("size", vec.size());
        LOG("capacity", vec.capacity());
        LOG("return", *it);
        LOG_EACH("iterator", vec.begin(), vec.end());

        // End
        it = vec.erase(vec.end() - 10, vec.end());

        LOG("size", vec.size());
        LOG("capacity", vec.capacity());
        LOG("return", *it);
        LOG_EACH("iterator", vec.begin(), vec.end());

        // Middle
        it = vec.erase(vec.begin() + (vec.size() / 2), vec.begin() + (vec.size() / 2) + 10);

        LOG("size", vec.size());
        LOG("capacity", vec.capacity());
        LOG("return", *it);
        LOG_EACH("iterator", vec.begin(), vec.end());

        // Zero erase
        it = vec.erase(vec.begin(), vec.begin());

        LOG("size", vec.size());
        LOG("capacity", vec.capacity());
        LOG("return", *it);
        LOG_EACH("iterator", vec.begin(), vec.end());
    }
}

void test_vector_swap(){
    {
        // One empty, Two full
        ft::vector<int> one;
        ft::vector<int> two(10, 42);

        one.swap(two);

        LOG("size", one.size());
        LOG("size", two.size());

        LOG("capacity", one.capacity());
        LOG("capacity", two.capacity());

        LOG_EACH("iterator", one.begin(), one.end());
        LOG_EACH("iterator", two.begin(), two.end());
    }
    {
        // One full, Two empty
        ft::vector<int> one(10, 42);
        ft::vector<int> two;

        one.swap(two);

        LOG("size", one.size());
        LOG("size", two.size());

        LOG("capacity", one.capacity());
        LOG("capacity", two.capacity());

        LOG_EACH("iterator", one.begin(), one.end());
        LOG_EACH("iterator", two.begin(), two.end());
    }
    {
        // One full, Two full
        ft::vector<int> one(10, 42);
        ft::vector<int> two(42, 10);

        one.swap(two);

        LOG("size", one.size());
        LOG("size", two.size());

        LOG("capacity", one.capacity());
        LOG("capacity", two.capacity());

        LOG_EACH("iterator", one.begin(), one.end());
        LOG_EACH("iterator", two.begin(), two.end());
    }
    {
        // One empty, Two empty
        ft::vector<int> one;
        ft::vector<int> two;

        one.swap(two);

        LOG("size", one.size());
        LOG("size", two.size());

        LOG("capacity", one.capacity());
        LOG("capacity", two.capacity());

        LOG_EACH("iterator", one.begin(), one.end());
        LOG_EACH("iterator", two.begin(), two.end());
    }
}

void test_vector_clear(){
    {
        ft::vector<int> vec;

        vec.clear();
        LOG("size", vec.size());
        LOG("capacity", vec.capacity());
        LOG_EACH("iterator", vec.begin(), vec.end());
    }
    {
        ft::vector<int>		vec;

        vec.resize(20, 10);

        vec.clear();

        LOG("size", vec.size());
        LOG("capacity", vec.capacity());
        LOG_EACH("iterator", vec.begin(), vec.end());
    }
    {
        ft::vector<int>		vec(100, 10);

        vec.clear();

        LOG("size", vec.size());
        LOG("capacity", vec.capacity());
        LOG_EACH("iterator", vec.begin(), vec.end());
    }
}

/* Test stack */

void test_stack_push() {
    {
        ft::stack<int> stack;

        for ( int i = 0 ; i < 5 ; i++ ){
            stack.push(i);
            LOG("item", stack.top());
            LOG("size", stack.size());
        }
    }
    {
        ft::stack<int, std::deque<int> > stack;

        for ( int i = 0 ; i < 5 ; i++ ){
            stack.push(i);
            LOG("(deque) item", stack.top());
            LOG("(deque) size", stack.size());
        }
    }
}

void test_stack_empty() {
    {
        ft::stack<int> stack;

        LOG("size", stack.size());
        LOG("empty", stack.empty());
    }
    {
        ft::stack<int, std::deque<int> > stack;

        LOG("(deque) size", stack.size());
        LOG("(deque) empty", stack.empty());
    }
}

void test_stack_size() {
    {
        ft::stack<int> stack;

        LOG("size", stack.size());
        for ( int i = 0 ; i < 5 ; i++ ){
            stack.push(i);
            LOG("size", stack.size());
        }

        LOG("size", stack.size());

        for ( int i = 0 ; i < 5 ; i++ ){
            stack.pop();
            LOG("size", stack.size());
        }
    }
    {
        ft::stack<int, std::deque<int> > stack;

        LOG("(deque) size", stack.size());
        for ( int i = 0 ; i < 5 ; i++ ){
            stack.push(i);
            LOG("(deque) size", stack.size());
        }

        LOG("(deque) size", stack.size());

        for ( int i = 0 ; i < 5 ; i++ ){
            stack.pop();
            LOG("(deque) size", stack.size());
        }
    }
}

void test_stack_top() {
    {
        ft::stack<int> stack;

        for ( int i = 0 ; i < 10 ; i++ ){
            stack.push(i);
            LOG("size", stack.top());
        }
    }
    {
        ft::stack<int, std::deque<int> > stack;

        for ( int i = 0 ; i < 10 ; i++ ){
            stack.push(i);
            LOG("(deque) size", stack.top());
        }
    }
}

void test_stack_pop() {
    {
        ft::stack<int> stack;

        for ( int i = 0 ; i < 10 ; i++ ){
            stack.push(i);
        }

        while ( !stack.empty() ){
            stack.pop();
        }
        LOG("size", stack.size());
    }
    {
        ft::stack<int, std::deque<int> > stack;

        for ( int i = 0 ; i < 10 ; i++ ){
            stack.push(i);
        }

        while ( !stack.empty() ){
            stack.pop();
        }
        LOG("(deque) size", stack.size());
    }
}

void test_vector(){
    test_vector_default_constructor();
    test_vector_fill_constructor();
    test_vector_range_constructor();
    test_vector_copy_constructor();
    test_vector_assignment_operator();
    test_vector_iterator();
    test_vector_reverse_iterator();
    test_vector_max_size();
    test_vector_capacity();
    test_vector_resize();
    test_vector_access();
    test_vector_at();
    test_vector_assign();
    test_vector_pop_back();
    test_vector_insert();
    test_vector_erase();
    test_vector_swap();
    test_vector_clear();
}

void test_stack(){
    test_stack_push();
	test_stack_empty();
	test_stack_size();
	test_stack_top();
	test_stack_pop();
}

void test_map_default_constructor(){
    {
        ft::map<int, int> vec;

        LOG("empty", vec.empty());
        LOG("size", vec.size());
    }
    {
        ft::map<int, int, Greater<int> > vec;

        LOG("empty", vec.empty());
        LOG("size", vec.size());
    }
}

void test_map_copy_constructor(){
    // Lower empty
    {
        ft::map<int, int>	map;
        ft::map<int, int>	copy_map(map);

        LOG("size", map.size());
        LOG("copy size", copy_map.size());
        LOG_EACH("iterator", map.begin(), map.end());
        LOG_EACH("copy iterator", copy_map.begin(), copy_map.end());
    }
    // Greater empty
    {
        ft::map<int, int, Greater<int> > map;
        ft::map<int, int, Greater<int> > copy_map(map);

        LOG("size", map.size());
        LOG("copy size", copy_map.size());
        LOG_EACH("iterator", map.begin(), map.end());
        LOG_EACH("copy iterator", copy_map.begin(), copy_map.end());
    }
    // Lower fill
    {
        int keys[13] = { 12, 5, 15, 3, 7, 13, 17, 1, 4, 30, 25, 18, 27 };
        ft::map<int, int> map;

        for ( int index = 0 ; index < 13 ; index++ ){
            map.insert(ft::make_pair(keys[index], 0));
        }
        ft::map<int, int> copy_map(map);

        LOG("size", map.size());
        LOG("copy size", copy_map.size());
        LOG_EACH("iterator", map.begin(), map.end());
        LOG_EACH("copy iterator", copy_map.begin(), copy_map.end());
    }
    // Greater fill
    {
        int keys[13] = { 12, 5, 15, 3, 7, 13, 17, 1, 4, 30, 25, 18, 27 };
        ft::map<int, int, Greater<int> >		map;

        for ( int index = 0 ; index < 13 ; index++ ){
            map.insert(ft::make_pair(keys[index], 0));
        }
        ft::map<int, int, Greater<int> >		copy_map(map);

        LOG("size", map.size());
        LOG("copy size", copy_map.size());
        LOG_EACH("iterator", map.begin(), map.end());
        LOG_EACH("copy iterator", copy_map.begin(), copy_map.end());
    }
}

void test_map_range_constructor(){
    // Lower empty (begin - end)
    {
        ft::map<int, int> map;
        ft::map<int, int> range_map(map.begin(), map.end());

        LOG("size", range_map.size());
        LOG_EACH("iterator", range_map.begin(), range_map.end());
    }
    // Greater empty (begin - end)
    {
        ft::map<int, int, Greater<int> > map;
        ft::map<int, int, Greater<int> > range_map(map.begin(), map.end());

        LOG("greater - size", range_map.size());
        LOG_EACH("greater - iterator", range_map.begin(), range_map.end());
    }
    // Lower full
    {
        int keys[13] = { 12, 5, 15, 3, 7, 13, 17, 1, 4, 30, 25, 18, 27 };
        ft::map<int, int>	map;

        for ( int index = 0 ; index < 13 ; index++ ){
            map.insert(ft::make_pair(keys[index], 0));
        }

        // Begin - end
        {
            ft::map<int, int>	range_map(map.begin(), map.end());

            LOG("greater - size", range_map.size());
            LOG_EACH("greater - iterator", range_map.begin(), range_map.end());
        }
        // Begin - find
        {
            ft::map<int, int>	range_map(map.begin(), map.find(13));

            LOG("greater - size", range_map.size());
            LOG_EACH("greater - iterator", range_map.begin(), range_map.end());
        }
        // Find - end
        {
            ft::map<int, int>	range_map(map.find(13), map.end());

            LOG("greater - size", range_map.size());
            LOG_EACH("greater - iterator", range_map.begin(), range_map.end());
        }
    }
    // Greater full
    {
        int keys[13] = { 12, 5, 15, 3, 7, 13, 17, 1, 4, 30, 25, 18, 27 };
        ft::map<int, int, Greater<int> >		map;

        for ( int index = 0 ; index < 13 ; index++ ){
            map.insert(ft::make_pair(keys[index], 0));
        }

        // Begin - end
        {
            ft::map<int, int, Greater<int> >		range_map(map.begin(), map.end());

            LOG("greater - size", range_map.size());
            LOG_EACH("greater - iterator", range_map.begin(), range_map.end());
        }
        // Begin - find
        {
            ft::map<int, int, Greater<int> >		range_map(map.begin(), map.find(13));

            LOG("greater - size", range_map.size());
            LOG_EACH("greater - iterator", range_map.begin(), range_map.end());
        }
        // Find - end
        {
            ft::map<int, int, Greater<int> >		range_map(map.find(13), map.end());

            LOG("greater - size", range_map.size());
            LOG_EACH("greater - iterator", range_map.begin(), range_map.end());
        }
    }
}

void test_map_assignment_operator(){
    int keys[13] = { 12, 5, 15, 3, 7, 13, 17, 1, 4, 30, 25, 18, 27 };
    // Lower empty
    {
        ft::map<int, int> map;
        ft::map<int, int> assign_map;

        assign_map = map;
        LOG("size", assign_map.size());
        LOG_EACH("iterator", assign_map.begin(), assign_map.end());
    }
    // Greater empty
    {
        ft::map<int, int, Greater<int> > map;
        ft::map<int, int, Greater<int> > assign_map;

        assign_map = map;
        LOG("size", assign_map.size());
        LOG_EACH("iterator", assign_map.begin(), assign_map.end());
    }
    // Lower fill
    {
        ft::map<int, int> map;
        ft::map<int, int> assign_map;

        for ( int index = 0 ; index < 13 ; index++ ){
            map.insert(ft::make_pair(keys[index], 0));
        }

        assign_map = map;
        LOG("size", assign_map.size());
        LOG_EACH("iterator", assign_map.begin(), assign_map.end());
    }
    // Greater fill
    {
        ft::map<int, int, Greater<int> > map;
        ft::map<int, int, Greater<int> > assign_map;

        for ( int index = 0 ; index < 13 ; index++ ){
            map.insert(ft::make_pair(keys[index], 0));
        }

        assign_map = map;
        LOG("size", assign_map.size());
        LOG_EACH("iterator", assign_map.begin(), assign_map.end());
    }
}

void test_map_empty(){
    ft::map<char, int> map;

    LOG("empty", map.empty());
    map.insert(ft::make_pair(1, 1));
    LOG("empty", map.empty());
}

void test_map_max_size(){
    {
        ft::map<int, int> map;

        LOG("max size", map.max_size());
    }
    {
        ft::map<bool, int> map;

        LOG("max size", map.max_size());
    }
    {
        ft::map<char, int> map;

        LOG("max size", map.max_size());
    }
    {
        ft::map<std::string, int> map;

        LOG("max size", map.max_size());
    }
    {
        ft::map<std::string, std::string> map;

        LOG("max size", map.max_size());
    }
    {
        ft::map<ft::pair<int, int>, ft::pair<int, int> > map;

        LOG("max size", map.max_size());
    }
    {
        ft::map<std::pair<int, int>, std::pair<int, int> > map;

        LOG("max size", map.max_size());
    }
}

void test_map(){
    // Constructor
    test_map_default_constructor();
    test_map_copy_constructor();
    test_map_range_constructor();
    test_map_assignment_operator();

    // Capacity
    test_map_empty();
    test_map_max_size();
//
//    test_map_iterator();
//    test_map_reverse_iterator();
//
//    test_map_bracket_operator();
//
//    test_map_insert();
//    test_map_insert_hint();
//    test_map_insert_range();
//    test_map_insert_randomized();
//    test_map_erase_it();
//    test_map_erase_key();
//    test_map_erase_range();
//    test_map_clear();
//    test_map_swap();
//
//    test_map_find();
//    test_map_count();
//    test_map_lower_bound();
//    test_map_upper_bound();
//    test_map_equal_range();
//
//    test_map_key_comp();
//    test_map_val_comp();
}

int     main(){
    test_vector();
    test_stack();
    test_map();
}