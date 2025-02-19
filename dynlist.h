#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/// =============================================================================
/// ============================== STRUCTS ======================================
/// =============================================================================

typedef struct 
{
    uint8_t* data;
    uint8_t* itr;
    size_t element_size;
    size_t size;
    size_t count;
} __dynamic_list;

typedef __dynamic_list dlist;

/// =============================================================================
/// ============================== MACROS =======================================
/// =============================================================================

#define DLIST_PUSH(p_dlist, data_type, value) \
{\
    data_type tmp = value; \
    __push_dlist(p_dlist, &tmp); \
}

#define DLIST_PUSH_PTR(p_dlist, data_type_ptr, value) \
{\
    data_type_ptr tmp = value; \
    __push_dlist(p_dlist, tmp); \
}

#define DLIST_CREATE(data_type, count) \
__make_dlist(sizeof(data_type) * count, sizeof(data_type));

#define DLIST_GET(p_dlist, index) \
__get_data(p_dlist, index);\

/// =============================================================================
/// ============================== PUBLIC =======================================
/// =============================================================================

/// @brief Frees the dynamic list memory allocations and safely sets it to unused
void 
free_dlist(dlist* list) 
{
    if (list != NULL && list->data != NULL) 
    {
        free(list->data);
        list->data = NULL;
        list->size = 0;
        list->count = 0;
    }
}

/// =============================================================================
/// ============================== PRIVATE ======================================
/// =============================================================================

/// @brief Creates a stack allocated dynamic list
/// @param size size in bytes for amount of memory you want to allocate
/// @param element_size size of each element that will be pushed
/// @note Use DLIST_CREATE macro instead
/// @return a stack allocated list
dlist 
__make_dlist(size_t size, size_t element_size) 
{
    dlist list;
    list.data = (uint8_t*)malloc(size);
    memset(list.data, 0, size);
    list.itr = list.data;
    list.size = size;
    list.element_size = element_size;
    list.count = 0;
    return list;
}

/// @brief Checks if the dynamic list is full
/// @return 0 if true else -1
int 
__is_full(dlist* list) 
{
    return (list->itr == list->data + list->size) ? 0 : -1;
}

/// @brief Copies the contents of memory into the list
/// @param list The list to copy to
/// @param data The destination memory region from where data will be copied
/// @note Use DLIST_PUSH / DLIST_PUSH_PTR macros instead
/// @return 0 if succeeds else -1
int 
__push_dlist(dlist* list, void* data) 
{
    if (__is_full(list) == 0)
    {
        fprintf(stderr, "trying to write out of band, returning\n");
        return -1;
    }
    memcpy(list->itr, data, list->element_size);
    list->itr += list->element_size;
    list->count++;
    return 0;
}

/// @brief Gets the data at specified index into the dlist
/// @param list The list from where data will be fetched
/// @param index The index number of the data we want to get from the list
/// @note Use DLIST_GET macro instead
/// @return Data from the list (this needs to be casted back to the type you want)
void* 
__get_data(dlist* list, int index) 
{
    return list->data + (list->element_size * index);
}
