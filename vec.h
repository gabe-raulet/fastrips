#ifndef VEC_H_
#define VEC_H_

#include <stdlib.h>

#define vec_t(type) struct { type *a; size_t l, m; }

#define vec_init(v)       ((v).l=(v).m=0, (v).a=0)
#define vec_free(v)       (free((v).a))
#define vec_at(v, i)      ((v).a[(i)])
#define vec_capacity(v)   ((v).m)
#define vec_size(v)       ((v).l)
#define vec_empty(v)      (!(v).l)
#define vec_pop(v)        ((v).a[--(v).l])
#define vec_top(v)        ((v).a[(v).l-1])
#define vec_clear(v)      ((v).l=0)
#define vec_reserve(v, n) (((v).m=( ((n)>=4)? (n) : 4)), (v).a=realloc((v).a, sizeof(*(v).a)*(v).m))
#define vec_pushp(v)      ((((v).l==(v).m)? (((v).m=((v).m? (v).m<<1 : 4)), (v).a=realloc((v).a, sizeof(*(v).a)*(v).m)) : 0), ((v).a + ((v).l++)))
#define vec_release(v)    ((((v).m>(v).l)? ((v).a=realloc((v).a, sizeof(*(v).a)*(v).l)) : 0), (v).l=(v).m=0, (v).a)

#endif
