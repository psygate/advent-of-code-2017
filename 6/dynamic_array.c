#include "dynamic_array.h"

static int inbounds(size_t index, struct dynamic_array* arrayptr)
{
	return arrayptr->allocated_size > 0 && (index >= 0 && index <= arrayptr->size);
}

struct dynamic_array* new_dynamic_array(size_t size, size_t element_size)
{
	struct dynamic_array* arrayptr = (struct dynamic_array*) malloc(sizeof struct dynamic_array);
	arrayptr->size = size;
	arrayptr->allocated_size = size;
	arrayptr->element_size = element_size;
	arrayptr->elements = malloc(arrayptr->allocated_size * arrayptr->element_size);

	return arrayptr;
}

struct dynamic_array* destroy_dynamic_array(struct dynamic_array* arrayptr)
{
	free(arrayptr->elements);
	free(arrayptr);
}

int set_element_dynamic_array(size_t index, void* element, struct dynamic_array* arrayptr)
{
	if (inbounds(index, arrayptr))
	{
		memcpy(arrayptr->elements, element, arrayptr->element_size);
		return 0;
	}
	else
	{
		return ~0;
	}
}

int resize_dynamic_array(size_t newsize, struct dynamic_array* arrayptr)
{
	if (newsize <= arrayptr->allocated_size)
	{
		arrayptr->size = newsize;
	}
	else
	{
		size_t elements_size = arrayptr->element_size;
		size_t amount = arrayptr->size;
		void* elements = arrayptr->elements;
		arrayptr->elements = malloc(newsize * arrayptr->element_size);
		memcpy(arrayptr->elements, elements, elements_size * amount);
	}
}

void* get_element_dynamic_array(size_t index, struct dynamic_array* arrayptr)
{
	if (inbounds(index, arrayptr))
	{
		return arrayptr->elements[index * arrayptr->element_size];
	}
	else
	{
		return NULL;
	}
}