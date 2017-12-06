#pragma once

#include <stddef.h>
#include <string.h>
#include <memory.h>
#include <stdlib.h>

struct dynamic_array {
	size_t size;
	size_t allocated_size;
	size_t element_size;
	void* elements;
};

struct dynamic_array* new_dynamic_array(size_t size, size_t element_size);
struct dynamic_array* destroy_dynamic_array(struct dynamic_array* arrayptr);
void* get_element_dynamic_array(size_t index);
int set_element_dynamic_array(size_t index, void* element, struct dynamic_array* arrayptr);
int resize_dynamic_array(size_t newsize, struct dynamic_array* arrayptr);