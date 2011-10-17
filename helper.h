/* Define the helper file */
#ifndef _HELPER_H
#define _HELPER_H


/* Define interesting macro's */
#define BUILD_BUG_ON(condition) ((void)sizeof(char[1 - 2*!!(condition)]))
#define offset_of(element, member) &(((struct element *)0)->member)


void matrix_mul();
void stackoverflow();
#endif
