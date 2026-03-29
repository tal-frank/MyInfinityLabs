#ifndef __DYNAMIC_VECTOR_H__
#define __DYNAMIC_VECTOR_H__


typedef struct Dynamic_vector dvector_t;


/**
* Description:    Creates dynamic vector 
* 
* Arguments:      capacity     - initial capacity of vector must me grater than 0.
*                 element_size - the size of type of element in bytes , grater than 0.
* 
* Return:         Pointer to vector or NULL on fail .
* 
* Complexity:     time:   O(1)
*                 space:  O(1)
*/
dvector_t* DvectorCreate(size_t capacity, size_t element_size);

/**
* Description:    destroys recived vector 
* 
* Arguments:      vector - pointer to dvector_t
*  
* Complexity:     time:   O(1)
*                 space:  O(1)
*/
void DvectorDestroy(dvector_t* vector);


/**
* Description:    pushing element to end of the vector.
*                 If at full capacity, Doubles the capacity.
* 
* Arguments:      vector - Valid pointer to dvector_t, 
*                 element- Valid pointer to data that user wants to insert 
* 
* Return:         0 - on success, non zero otherwise
* 
* Complexity:     time:   O(1) amortized
*                 space:  O(1)
*/
int DvectorPush(dvector_t* vector, const void* element);


/**
* Description:    Getting pointer to the element data at index in vector.
*                
* Arguments:      vector -    Valid pointer to dvector_t, 
*                 index  -    index should not exceed vector's size  
*                
* 
* Return:         0 - on success, non zero otherwise
* 
* Complexity:     time:   O(1)
*                 space:  O(1)
*/
void* DvectorGetAccessToElement(dvector_t* vector, size_t index);

/**
* Description:    poping element from the end of the vector.
*                 If size is 25% of capacity, will shrink capacity to half.
* 
* Arguments:      vector - Valid pointer to dvector_t.
* 
* Return:         0 - on success, non zero otherwise
* 
* Complexity:     time:   O(1)
*                 space:  O(1)
*/
int DvectorPop(dvector_t* vector);

/**
* Description:    poping element from the end of the vector.
* 
* Arguments:      vector - Valid pointer to dvector_t.
* 
* Return:         0 - on success, non zero otherwise
* 
* Complexity:     time:   O(1)
*                 space:  O(1)
*/

void DvectorSafePop(dvector_t* vector);



size_t DvectorSize(const dvector_t* vector);

size_t DvectorCapacity(const dvector_t* vector);

/**
* Description:  updates and expaneds capacity to a new bigger capacity
* 
* Arguments:    vector     - Valid pointer to dvector_t.
*               new_amount - the new capacity size to replace the old one  
*                            must be bigger than current capacity 
* 
* Return:       0 - on success
* 
* Complexity:   time:   O(n)
*               space:  O(1)
*/
int DvectorExpand(dvector_t* vector, size_t new_amount);


/**
* Description:  shrinks the vector to half of the capacity,
*               if the size is bigger than half of capacity, shrinks to size,
*               so no data is loss.
* 
* Arguments:    vector - Valid pointer to dvector_t.
* 
* Return:       0 - on success
* 
* Complexity:   time:   O(n)
*               space:  O(n)
*/
int DvectorShrink(dvector_t* vector);


#endif /* End of  __DYNAMIC_VECTOR_H__ */


