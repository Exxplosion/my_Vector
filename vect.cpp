#include "stack.hpp"
#include <cstdlib>
#include <iostream>
#include <cassert>

Vector::Vector(size_t n):
    buf((vector_type *)calloc(n, sizeof(buf))),
    size(n),
    maxsize(n + alloc_vector)
    {
        FUNCTION
        poison_entry();
        FUNCTION_PRINT
    };

Vector::~Vector()
{
    FUNCTION
    free(buf);
    size = 0;
    maxsize = 0;
    buf = nullptr;
    FUNCTION_PRINT
}

Vector::Vector(const Vector& that) : // copy constructor
    buf(new vector_type[that.maxsize]),
    size(that.size),
    maxsize(that.maxsize)
    {
        std::copy(that.buf, that.buf + that.size, this->buf);
        FUNCTION
        FUNCTION_PRINT
    }


Vector& Vector::operator=(const Vector& that)// copy assignment operator
{
    this->~Vector();
    buf = new vector_type[that.maxsize];
    size = that.size;
    maxsize = that.maxsize;
    std::copy(that.buf, that.buf + that.size, this->buf); //deep copy
    FUNCTION
    FUNCTION_PRINT
}

Vector::Vector(Vector&& that) : //move constructor
    buf(that.buf), //robbed
    size(that.size),
    maxsize(that.maxsize)
    {
        FUNCTION
        that.size = 0;
        that.maxsize = 0;
        that.buf = nullptr;
        FUNCTION_PRINT
    }

Vector &Vector::operator=(Vector &&that) //move assignment
{
        FUNCTION
        buf = that.buf;
        size = that.size;
        maxsize = that.maxsize;
        that.size = 0;
        that.maxsize = 0;
        that.buf = nullptr;
        FUNCTION_PRINT
}


void Vector::dump() const
{
    int i;
    for(i = -3; i < (int) this->maxsize + 2; i++)
    {
        std::cout << i << ' ' << "[" << buf + i << "]" << ' ' << *(buf + i) << std::endl;
    }

    std::cout << " size: " << this->size << ' ' << &(this->size) <<  "  end" << std::endl;
    std::cout << " maxsize: " << this->maxsize << ' ' << &(this->maxsize) <<  "  end" << std::endl;
}

vector_type& Vector::operator[] (const int n)
{
    if (!(0 <= n <= size) )
    {
        err("The addressing abroad the array!")
    }
    return buf[n];
}

void Vector::poison_entry()
{
    for(int i = size; i < maxsize; i++)
    {
        *(buf + i) = POISON;
    }
} 


void Vector::push_back(vector_type val)
{
    if (maxsize > size)
    {
        *(buf + size) = val;
        size++;
    }
    else
    {
        vector_type* supp = buf;
        if ( (supp = (vector_type*) realloc(supp, (maxsize + alloc_vector) * sizeof(vector_type))) == NULL)
        {
            err("NOPE_MEM"); //throw bad_alloc :)
            exit(1);
        }
        buf = supp;
        supp = NULL;
        maxsize += alloc_vector;
        *(buf + size) = val;
        size++;
    }
}

vector_type Vector::pop_back()
{
    if (size > 0)
    {
        size--;
        vector_type supp = *(buf + size);
        *(buf + size) = POISON;
        return supp;
        ;
    }
    else
    {
        err("vector have zero size!") return POISON;
    }
}


Vector Vector::operator+(const Vector &that) // "-"" optional
{
    size_t max_vec = std::max(this->size, that.size);
    Vector supp(max_vec);
    int i = 0;
    for (i; i < std::min(this->size, that.size); i++)
    {
        *(supp.buf + i) = *(that.buf + i) + *(this->buf + i);
    }
    if (max_vec == that.size)
    {
        for (i; i < std::max(this->size, that.size); i++)
        {
            *(supp.buf + i) = *(that.buf + i);
        }
    }
    else
    {
        for (i; i < std::max(this->size, that.size); i++)
        {
            *(supp.buf + i) = *(this->buf + i);
        }
    }
    return supp;
}





int main()
{
    $DO ( Vector a(3); )
    a[0] = 5;
    $DO ( Vector b(1); )
    //b[1] = 3;
    $DO ( Vector b(a); )//calls copy constructor 
    // $DO( b = a; ) //calls copy assignment
    //$DO ( Vector b(std::move(a)); ) //calls move constructor
    $DO ( b = std::move(a); ) //calls move assignment
    b.dump();
}