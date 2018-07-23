/******************************************************************************
 * NAME:	    heap.h
 *
 * AUTHOR:	    Ethan D. Twardy <edtwardy@mtu.edu>
 *
 * DESCRIPTION:	    Contains the API for manipulating heap objects.
 *
 * CREATED:	    07/21/2018
 *
 * LAST EDITED:	    07/23/2018
 ***/

#ifndef __ET_HEAP__
#define __ET_HEAP__

/******************************************************************************
 * TYPE DEFINITIONS
 ***/

typedef struct {

  int cfg;
  int size;

} heap;

/******************************************************************************
 * MACRO DEFINITIONS
 ***/

#define Heap_size(heap)	    ((heap)->size)
#define Heap_isEmpty(heap)  ((heap)->size == 0 ? 1 : 0)
#define Heap_isMin(heap)    ((heap)->cfg == 0 ? 1 : 0)

/******************************************************************************
 * API FUNCTION PROTOTYPES
 ***/

/* Return the minimum element of the Heap, without destroying the element. The
 * data will remain in the Heap after the call returns.
 */
extern void * Heap_peek(Heap * heap);

/* Insert a new element into the Heap. If the Heap becomes unbalanced after
 * insertion, the Heap will be rebalanced. The argument data is a pointer to
 * the user's data which will be inserted into the Heap.
 */
extern int Heap_push(Heap * heap, void * data);

/* Return the minimum element of the Heap, removing the element from the Heap
 * in the process. The reference data is a pointer to a receptacle where the
 * user's data will be placed upon successful completion of this call.
 */
extern int Heap_pop(Heap * heap, void ** data);

/* Create an empty Min Heap. If an error occurs during the call, NULL is
 * returned. The argument destroy is a pointer to a function which frees user
 * data when it is no longer necessary. It takes a pointer to the user data.
 * The function compare compares two user data (passed as arguments), returning
 * -1 if the first is greater, 0 if they are the same, and 1 if the second is
 * greater. The second prototype will only be compiled if CONFIG_NO_HEAP is
 * defined at compilation time.
 */
#if !defined(CONFIG_NO_HEAP)
extern Heap * Heap_createMin(void (*destroy)(void *),
			     int (*compare)(void *, void *));
#else
extern int Heap_createMin(Heap * heap, void (*destroy)(void *),
			  int (*compare)(void *, void *),
			  size_t len, void * (*workspace)[len]);
#endif

/* Create an empty Max Heap. If an error occurs during the call, NULL is
 * returned. The argument destroy is a pointer to a function which frees user
 * data when it is no longer necessary. It takes a pointer to the user data.
 * The function compare compares two user data (passed as arguments), returning
 * -1 if the first is greater, 0 if they are the same, and 1 if the second is
 * greater. The second prototype will only be compiled if CONFIG_NO_HEAP is
 * defined at compilation time.
 */
#if !defined(CONFIG_NO_HEAP)
extern Heap * Heap_createMax(void (*destroy)(void *),
			     int (*compare)(void *, void *));
#else
extern int Heap_createMax(Heap * heap, void (*destroy)(void *),
			  int (*compare)(void *, void *),
			  size_t len, void * (*workspace)[len]);
#endif

/* Destroys the heap pointed to. This function frees all internally allocated
 * memory (if using the Heap) and, if the member destroy is non-null, it is
 * called on every user datum in the Heap.
 */
extern void Heap_destroy(Heap * heap);

/* Create a new Heap from the array array. The parameter config is one of two
 * values defined in enum Status. The choices are HEAP_MAX and HEAP_MIN. These
 * correspond to creation of a Max Heap and Min Heap, respectively.
 */
extern Heap * Heap_heapify(size_t len, void * (*array)[len],
			   enum Config config);

#endif /* __ET_HEAP__ */

/*****************************************************************************/
