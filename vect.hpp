#ifndef STACK_H
#define STACH_H

#include <cstring>
//Дмитрий Дербышев kirikusan@gmail.com

#define err(msg) fprintf(stderr, "in FILE %s; line %d; error %d: %s\n", __FILE__, __LINE__, errno, msg);
#define POISON 666
#define FUNCTION Indent _indent;

#define $DO(stmt)                                                                   \
    fprintf(stderr, "[%02d]%*s %s\n", __LINE__, Level, __PRETTY_FUNCTION__, #stmt); \
    stmt;

#define FUNCTION_PRINT fprintf(stderr, "%*s    [%p]       by func:%s\n", Level, "", this, __PRETTY_FUNCTION__);

const size_t alloc_vector = 1;


int Level = -1; //дерево функций

struct Indent
{
    Indent() { Level = Level + 5; }
    ~Indent() { Level = Level - 5; }
};



typedef int vector_type;
class Vector
{
public:

    typedef int vector_type;
    vector_type *buf;
    std::size_t size;
    std::size_t maxsize;

    Vector  (size_t n);
    ~Vector ();

    void dump() const;
    vector_type& operator[] (const int n);
    void push_back(vector_type val);
    void poison_entry();
    vector_type pop_back();
    Vector operator+(const Vector &that);
    Vector(const Vector &that);
    Vector& operator=(const Vector &that);
    Vector(Vector &&that);
    Vector& operator=(Vector &&that);
};
#endif