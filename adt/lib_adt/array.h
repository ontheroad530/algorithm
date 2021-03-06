#ifndef ARRAY_H
#define ARRAY_H

#include <stdexcept>

namespace GYH
{

template <typename T>
/**
 * @brief The Array class
 */
class Array
{
public:
    Array();
    Array(unsigned int, unsigned int = 0);
    ~Array();

    Array(Array const &);
    Array& operator = (Array const&);

    T const& operator [] (unsigned int) const;
    T& operator [] (unsigned int);

    T const* data() const;
    unsigned int base() const;
    unsigned int length() const;
    unsigned int size() const;

    void set_base(unsigned int);
    void set_length(unsigned int);

protected:
    T*  _data;
    unsigned int _base;
    unsigned int _length;
};

template <typename T>
Array<T>::Array()
    :_data( new T[0])
    ,_base(0)
    ,_length(0)
{
}

template <typename T>
Array<T>::Array(unsigned int m, unsigned int n)
    :_data(new T[m])
    ,_base(n)
    ,_length(m)
{
}

template <typename T>
Array<T>::~Array()
{
    delete []_data;
}

template <typename T>
Array<T>::Array(const Array &array)
    :_data( new T[array.length()] )
    ,_base( array.base() )
    ,_length( array.length() )
{
    for(int i = 0; i < _length; ++i)
    {
        _data[i] = array[i];
    }
}

template <typename T>
Array<T> &Array<T>::operator =(const Array &array)
{
    if(this != array)
    {
        delete [] _data;
        _data = new T[array.length()];
        _base = array.base();
        _length = array.length();

        for(int i = 0; i < _length; ++i)
        {
            _data[i] = array[i];
        }
    }

    return *this;
}

template <typename T>
const T &Array<T>::operator [](unsigned int n) const
{
    unsigned int pos = n - _base;
    if(pos >= _length)
        throw std::out_of_range("invalid position");

    return  _data[pos];
}

template <typename T>
T &Array<T>::operator [](unsigned int n)
{
    unsigned int pos = n - _base;
    if(pos >= _length)
        throw std::out_of_range("invalid position");

    return  _data[pos];
}

template <typename T>
const T *Array<T>::data() const
{
    return _data;
}

template <typename T>
unsigned int Array<T>::base() const
{
    return _base;
}

template <typename T>
unsigned int Array<T>::length() const
{
    return _length;
}

template <typename T>
unsigned int Array<T>::size() const
{
    return _length - _base;
}

template <typename T>
void Array<T>::set_base(unsigned int base)
{
    //base ????
    //could't understand
#if 0
    T* const new_data = new T[_length];
    if(!new_data)
    {
        throw std::out_of_range("new Array<T> error");
    }

    if(base < _base)
    {
        unsigned int shift = _base - base;
        for(int i = _length; i >= shift; --i)
            new_data[i] = _data[i-shift];
    }
    else
    {
        unsigned int shift = base - _base;
        for(int i = shift; i < _length; ++i)
            new_data[i] = _data[i+shift];
    }

    delete []_data;
    _data = new_data;
#endif
    _base = base;
}


template <typename T>
void Array<T>::set_length(unsigned int len)
{
    T* const new_data = new T[len];
    unsigned int const min =
            _length < len ? _length : len;
    for(unsigned int i = 0; i < min; ++i)
    {
        new_data[i] = _data[i];
    }

    delete []_data;
    _data = new_data;
    _length = len;
}

template<typename T>
/**
 * @brief The Array_2D class
 */
class Array_2D
{
public:
    class Row
    {
    public:
        Row(Array_2D& array_2d, unsigned int row)
            :_array_2d(array_2d)
            ,_row(row)
        {}

        T& operator [](unsigned int column) const
        {
            return _array_2d.select(_row, column);
        }

    private:
        Array_2D&   _array_2d;
        unsigned int const _row;
    };

    Array_2D(unsigned int, unsigned int);
    T& select(unsigned int, unsigned int);
    Row operator [](unsigned int);

protected:
    unsigned int _number_of_rows;
    unsigned int _number_of_columns;
    Array<T>    _array;
};

template<typename T>
Array_2D<T>::Array_2D(unsigned int rows, unsigned int columns)
    :_number_of_rows(rows)
    ,_number_of_columns(columns)
    ,_array(rows * columns)
{
}

template<typename T>
T &Array_2D<T>::select(unsigned int row, unsigned int column)
{
    if(row >= _number_of_rows)
        throw std::out_of_range("invalid row");

    if(column >= _number_of_columns)
        throw std::out_of_range("invalid column");

    return _array[row * _number_of_columns + column];
}

template<typename T>
typename Array_2D<T>::Row Array_2D<T>::operator [](unsigned int row)
{
    return Row(*this, row);
}

}


#endif // ARRAY_H

