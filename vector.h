

#ifndef INC_4_UZDUOTIS_VECTOR_H
#define INC_4_UZDUOTIS_VECTOR_H

#include <cstddef>
#include <stdexcept>
#include <algorithm>
#include <utility>

using std::size_t;
template<typename T> class Vector
        {


public:

    using reference         = T&;
    using const_reference   = T const&;
    using iterator          = T*;
    using const_iterator    = T const*;

            Vector() :sz(0), elem(0), cap(0) {}
            Vector(size_t size, const T & initial);
            explicit Vector(size_t s);
            Vector(const Vector<T> & v);
            Vector( T& first,  T& last);
            Vector(std::initializer_list<T> const& list);
            ~Vector() { delete[] elem; }



    Vector& operator=(const Vector &);
    T& operator[](size_t n);
    const T& operator[](size_t n) const;
    T& at(size_t n);
    const T& at(size_t n) const;

    iterator  begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;
    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;

    iterator erase(iterator first, iterator last);
    iterator erase(iterator position);
    iterator insert(const_iterator it, const T& val);
    iterator insert(const_iterator it, T&& value);
    iterator insert (const_iterator it, std::initializer_list<T> init);
    iterator insert(const_iterator it, size_t n, T& val);
    size_t size() const { return sz; }
    size_t capacity() const { return cap; }
    void reserve(size_t alloc_size);
    void resize(size_t resize_size);
    void push_back(const T& d);
    void swap(Vector<T>& other);
    template <typename ... Args> reference emplace_back(Args&& ... args);
    void pop_back();
    bool empty() const;
private:
    void validateIndex(size_t index) const;
    void resizeIfRequired();
    void move(T * dest, T * from, size_t n);
    T* elem;
    size_t sz;
    size_t cap;



};

template<typename T>
Vector<T>::Vector(const std::initializer_list<T> &list)
        :elem{ new T[list.size()] }, sz{list.size()}, cap{list.size()}

{std::copy(list.begin(), list.end(), elem);}

template<typename T>
Vector<T>::Vector(size_t size, const T& initial)
        :elem{ new T[size] }, sz{size}, cap{size}

{
    for(auto i = 0; i<size; i++)
    {
        elem[i]=initial;
    }
}



template<class T>
void Vector<T>::reserve(size_t alloc_size) {
    if(alloc_size <= cap) return;
    T *p = new T[alloc_size];
    for(int i = 0; i < sz; ++i) p[i] = elem[i];
    delete[] elem;
    elem = p;
    cap = alloc_size;
}

template<class T>
T& Vector<T>::at(size_t n) {
    validateIndex(n);
    return elem[n];
}

template<class T>
const T& Vector<T>::at(size_t n) const {
    validateIndex(n);
    return elem[n];
}

template<class T>
T& Vector<T>::operator[](size_t n) {
    return elem[n];
}

template<class T>
const T& Vector<T>::operator[](size_t n) const {
    return elem[n];
}

template<class T>
Vector<T>& Vector<T>::operator=(const Vector<T> & v) {
    if(this == &v) return *this;

    if(v.sz <= cap) {
        for(int i = 0; i < v.sz; ++i)
            elem[i] = v.elem[i];
        sz = v.sz;
        return *this;
    }

    T *p = new T[v.sz];
    for(int i = 0; i < v.sz; ++i)
        p[i] = v.elem[i];
    delete[] elem;
    cap = sz = v.sz;
    elem = p;
    return *this;
}

template<class T>
void Vector<T>::resize(size_t resize_size) {
    reserve(resize_size);
    for(int i = 0; i < resize_size; ++i) elem[i] = 0;
    sz = resize_size;
}

template<class T>
void Vector<T>::push_back(const T& d){
    resizeIfRequired();
    elem[sz] = d;
    ++sz;
}



template <typename T> void swap(Vector<T> &v1, Vector<T> &v2) { v1.swap(v2); }
template<typename T>
void Vector<T>::swap(Vector<T> &other) {
    std::swap(this->cap, other.cap);
    std::swap(this->sz, other.sz);
    std::swap(this->elem, other.elem);

}
template<typename T>
void Vector<T>::pop_back()
{
    --sz;
    elem[sz].~T();
}

template<typename T>
bool Vector<T>::empty() const {
    return sz == 0;
}

template<typename T>
void Vector<T>::validateIndex(size_t index) const
{
    if (index >= sz)
    {
        throw std::out_of_range("Out of Range");
    }
}

template<typename T>
T& Vector<T>::front() {
    return elem[0];
}

template<typename T>
const T &Vector<T>::front() const {
    return elem[0];
}


template<typename T>
 T &Vector<T>::back() {
    return elem[sz - 1];
}

template<typename T>
const T &Vector<T>::back() const {
    return elem[sz - 1];
}

template<typename T>
const T *Vector<T>::end() const {
    return elem + sz;
}
template<typename T>
 T *Vector<T>::end()  {
    return elem + sz;
}

template<typename T>
const T *Vector<T>::begin() const {
    return elem;
}
template<typename T>
 T *Vector<T>::begin()  {
    return elem;
}

template<typename T>
void Vector<T>::resizeIfRequired() {
    if (sz == cap)
    {
        size_t newCapacity = std::max(2.0, cap * 1.5);
        reserve(newCapacity);
    }

}

template<typename T>
Vector<T>::Vector(const Vector<T> &v) {

        sz = v.sz;
        cap = v.cap;
        elem = new T[sz];
        for (int i = 0; i < sz; i++)
            elem[i] = v.elem[i];
}

template<typename T>
Vector<T>::Vector(T &first, T &last) {

}

template<typename T>
Vector<T>::Vector(size_t s) :sz{s}, cap{s}, elem{new T[s]} {
    for (auto i = 0; i < sz; ++i) elem[i] = 0;
}

template<typename T>
const T *Vector<T>::cbegin() const {return begin();}

template<typename T>
const T *Vector<T>::cend() const {return end();}

template<typename T>
typename Vector<T>::iterator Vector<T>::erase(T* first, T* last) {
    T* temp = new T[sz];
    T* returnit=last+1;
    size_t index{0};

    for(auto it = begin(); it!=first ; ++it,index++){
        temp[index]=*it;
    }
    for (auto it = last; it!=end()-1 ; ++it,index++) {
        temp[index] = *it;
    }
    sz=index;
    elem = temp;
    return returnit;


}
template<typename T>
typename Vector<T>::iterator Vector<T>::erase(T* position) {
    T* returnit=position+1;

sz--;
    T* temp = new T[sz];


    size_t index{0};
    for(auto it = begin(); it!=position; ++it, index++){
        temp[index]=*it;
    }


    for(auto it = returnit; it!=end()+1; ++it, index++){
        temp[index]=*it;
    }

    elem = temp;
    return returnit;
}

template<typename T>
typename Vector<T>::iterator Vector<T>::insert(const T* it, T &&value) {

    size_t index=sz;
     cap++;
    for (auto i = end()-1; i !=it; index--) {

        elem[index] = *i;
        --i;
    }

    sz++;
    resizeIfRequired();
    elem[index]=value;




}
template<typename T>
typename Vector<T>::iterator Vector<T>::insert(const T* it, const T &value) {

    size_t index=sz;
    cap++;
    for (auto i = end()-1; i !=it; index--) {

        elem[index] = *i;
        --i;
    }

    sz++;
    resizeIfRequired();
    elem[index]=value;




}

template<typename T>
void Vector<T>::move(T * dest, T * from, size_t n)
{
    if (dest < from)
    {
        T *_dest = dest, *_from = from;
        for (size_t i = 0; i < n; i++)
            *_dest++ = std::move(*_from++);
    }
    else if (dest > from)
    {
        T *_dest = dest + n - 1, *_from = from + n - 1;
        for (size_t i = n; i > 0; i--)
            *_dest-- = std::move(*_from--);
    }
    else
        return;
}


template<typename T>
typename Vector<T>::iterator Vector<T>::insert(const T* iter, std::initializer_list<T> init)
{
    auto pos = iter - elem;
    iterator _iter = &elem[pos];

    _iter = &elem[pos];
    move(_iter + init.size(), _iter, sz - (_iter - elem));
    sz += init.size();
    for (const T& elem : init)
        *_iter++ = elem;
    return &elem[pos];
}

template<typename T>
template<typename ...Args>
typename Vector<T>::reference Vector<T>::emplace_back(Args && ...args)
{
    resizeIfRequired();
    new (elem + sz) T(std::move<Args&>(args)...);
    ++sz;
}


#endif //INC_4_UZDUOTIS_VECTOR_H
