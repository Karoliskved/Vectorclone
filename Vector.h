//#ifndef VECTOR_H_INCLUDED
//#define VECTOR_H_INCLUDED

#include <algorithm>
#include <memory>
using namespace std;
template <class T>
class Vector
{
public:
    typedef T *iterator;
    typedef const T *const_iterator;
    typedef size_t size_type;
    typedef T value_type;
    typedef T &reference;
    typedef const T &const_reference;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    Vector()
    {
        create();
    }

    explicit Vector(size_type n, const T &val = T{})
    {
        create(n, val);
    }

    template <class InputIterator>
    Vector(InputIterator first, InputIterator last)
    {
        create(first, last);
    }

    Vector(const Vector &v)
    { // copy konstruktorius
        create(v.begin(), v.end());
    }
    Vector(initializer_list<value_type> il){
        create(il.begin(), il.end());
    }

    // priskyrimo operatorius
    Vector &operator=(const Vector &rhs)
    {
        if (&rhs != this)
        {
            uncreate();
            create(rhs.begin(), rhs.end());
        }
        return *this;
    }
    //destruktorius
    ~Vector()
    {
        uncreate();
    }

    // iterators

    iterator begin() noexcept
    {
        return data;
    }

    const_iterator begin() const noexcept
    {
        return data;
    }

    const_iterator cbegin() const noexcept
    {
        return data;
    }

    reverse_iterator rbegin() noexcept
    {
        return reverse_iterator(end());
    }

    const_reverse_iterator rbegin() const noexcept
    {
        return const_reverse_iterator(end());
    }

    const_reverse_iterator crbegin() const noexcept
    {
        return rbegin();
    }

    iterator end() noexcept
    {
        return avail;
    }

    const_iterator end() const noexcept
    {
        return avail;
    }

    const_iterator cend() const noexcept
    {
        return avail;
    }

    reverse_iterator rend() noexcept
    {
        return reverse_iterator(begin());
    }

    const_reverse_iterator rend() const noexcept
    {
        return const_reverse_iterator(begin());
    }

    const_reverse_iterator crend() const noexcept
    {
        return rend();
    }

    //capacity
    size_type size() const
    {
        return avail - data;
    } // size funkcija

    size_type max_size() const noexcept
    {
        return alloc.max_size();
    }

    void resize(size_type n)
    {
        if (n < size())
        {
            avail = data + n;
            erase(begin()+n, end());
            /* iterator it=limit;
            while (it!=avail){
                alloc.destroy(--it);
            }*/
        }
        else if (n > capacity())
        {
            grow();
            resize(n);
        }
        else if (n > size())
        {
            avail += n - size();
        }
    }

    void resize(size_type n, const value_type &a)
    {
        if (n < size())
        {
            avail = data + n;
            iterator it = limit;
            /*while (it!=avail){
                alloc.destroy(--it);
            }*/
        }
        else if (n > capacity())
        {
            grow();
            resize(n, a);
        }
        else if (n > size())
        {
            size_type b = size();
            avail += n - size();
            for (size_type i = b; i < n; i++)
            {
                data[i] = a;
            }
        }
    }

    size_type capacity() const
    {
        return limit - data;
    }

    bool empty() const noexcept
    {
        return size() == 0;
    }

    T &operator[](size_type i)
    {
        return data[i];
    }

    void reserve(size_type n)
    {
        if (n > capacity())
        {
            grow();
            reserve(n);
        }
    }

    void shrink_to_fit()
    {
        if (limit > avail)
        {
            iterator it = limit;
            while (it != avail)
            {
                alloc.destroy(--it);
            }
            limit = avail;
        }
    }

    //elemeent access

    const T &operator[](size_type i) const
    {
        return data[i];
    }

    reference at(size_type i)
    {
        return data[i];
    }

    const_reference at(size_type i) const
    {
        return data[i];
    }

    reference front()
    {
        return data[0];
    }

    const_reference front() const
    {
        return data[0];
    }

    reference back()
    {
        return data[size() - 1];
    }

    const_reference back() const
    {
        return data[size() - 1];
    }

    T *Data() noexcept;
    const T *Data() const noexcept;

    // modifiers
    template <class InputIterator>
    void assign(InputIterator first, InputIterator last)
    {
        uncreate();
        create(first, last);
    }

    void assign(size_type n, const value_type &val)
    {
        uncreate();
        create(n, val);
    }

    void assign(initializer_list<value_type> il)
    {
        uncreate();
        create(il.begin(), il.end());
    }

    void push_back(const T &val)
    { //push_back()
        if (avail == limit)
            grow();
        unchecked_append(val);
    }

    void pop_back()
    {
        iterator new_avail = avail;
        alloc.destroy(--new_avail);
        avail = new_avail;
    }

    /*iterator insert(terator position, const value_type &val)
    {
    }*/

    iterator erase(iterator position)
    {
        
        alloc.destroy(position);
        avail=(position+1, end(), position);
        return position;
    }
    iterator erase(iterator fposition, iterator lposition)
    {
        iterator it=lposition;
        while(it!=fposition){
            alloc.destroy(--it);
        }
        avail=uninitialized_copy(lposition, end(), fposition);
        return lposition;
    }

    void swap(Vector &x)
    {
        std::swap(data, x.data);
        std::swap(avail, x.avail);
        std::swap(limit, x.limit);
    }
    /*void swap(Vector<T> &lhs, Vector<T> &rhs){
        std::swap(x,y);
    }*/

    void clear()
    {
        uncreate();
    }

    // bool operators
    bool operator==(const Vector<T> &rhs)
    {
        return size() == rhs.size() && std::equal(begin(), end(), rhs.begin());
    }
    bool operator!=(const Vector<T> &rhs)
    {
        return !(*this == rhs);
    }
    bool operator>(const Vector<T> &rhs)
    {
        return std::lexicographical_compare(rhs.begin(), rhs.end(), begin(), end());
    }
    bool operator<(const Vector<T> &rhs)
    {
        return rhs > *this;
    }
    bool operator>=(const Vector<T> &rhs)
    {
        return !(*this < rhs);
    }
    bool operator<=(const Vector<T> &rhs)
    {
        return !(rhs < *this);
    }

private:
    iterator data;
    iterator avail;
    iterator limit;

    allocator<T> alloc;
    void create()
    {
        data = avail = limit = nullptr;
    }
    void create(size_type n, const T &val)
    {
        data = alloc.allocate(n);
        limit = avail = data + n;
        uninitialized_fill(data, limit, val);
    }
    void create(const_iterator i, const_iterator j)
    {
        data = alloc.allocate(j - i);
        limit = avail = uninitialized_copy(i, j, data);
    }

    void uncreate()
    {
        if (data)
        {
            iterator it = avail;
            while (it != data)
                alloc.destroy(--it);
            alloc.deallocate(data, limit - data);
        }
        data = limit = avail = nullptr;
    }

    void grow()
    {
        // dvigubai daugiau vietos, nei buvo
        size_type new_size = max(2 * (limit - data), ptrdiff_t(1));
        iterator new_data = alloc.allocate(new_size);
        iterator new_avail = uninitialized_copy(data, avail, new_data);

        uncreate();

        data = new_data;
        avail = new_avail;
        limit = data + new_size;
    }
    void unchecked_append(const T &val)
    {
        alloc.construct(avail++, val);
    }
};

template <typename T>
inline T *Vector<T>::Data() noexcept
{
    return data;
}

template <typename T>
inline const T *Vector<T>::Data() const noexcept
{
    return data;
}
//#endif