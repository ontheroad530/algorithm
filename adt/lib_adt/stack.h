#ifndef STACK_H
#define STACK_H

#include "container.h"
#include "array.h"

namespace GYH
{



class Stack: public virtual Container
{
public:
    virtual Object& top() const = 0;
    virtual void push(Object& ) = 0;
    virtual Object& pop() = 0;
};


class Stack_As_Array: public Stack
{
    class Iter;
    friend class Iter;
public:
    Stack_As_Array(unsigned int);
    virtual ~Stack_As_Array();

    void purge();
    void accept(Visitor &) const;

    void push(Object &);
    Object& top() const;
    Object& pop();

    Iterator& new_iterator() const;

protected:
    int compare_to(const Object &) const;

private:
    Array<Object*>  _array;

};

class Stack_As_Array::Iter : public Iterator
{
public:
    Iter(Stack_As_Array const&);

    void reset();
    bool is_done() const;

    Object& operator *() const;
    void operator ++();

private:
    unsigned int            _position;
    Stack_As_Array const&   _stack;
};

}

#endif // STACK_H
