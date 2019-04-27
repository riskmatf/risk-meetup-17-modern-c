#ifndef __COMPILER_H__
#define __COMPILER_H__

#include <stddef.h>

/* Optimization: Condition @x is likely */
#define likely(x)	__builtin_expect(!!(x), 1)

/* Optimization: Condition @x is unlikely */
#define unlikely(x)	__builtin_expect(!!(x), 0)

/**
 * container_of - cast a member of a structure out to the containing structure
 *
 * @ptr:	the pointer to the member.
 * @type:	the type of the container struct this is embedded in.
 * @member:	the name of the member within the struct.
 *
 */
#define container_of_portable(ptr, type, member) \
	((type *)(void *)( (char *)(ptr) - offsetof(type,member) ))
#undef container_of

#if defined(__GNUC__)
#define container_of(ptr, type, member) __extension__ ({		\
	const __typeof__( ((type *)0)->member ) *_mptr = (ptr);	\
	container_of_portable(_mptr, type, member);})
#else
#define container_of(ptr, type, member) container_of_portable(ptr, type, member)
#endif

#endif