#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>

#define min(a,b) (a > b ? b : a)
#define max(a,b) (a < b ? b : a)
#define TRUE (0 == 0)
#define FALSE (!TRUE)

struct memory_cells
{
	size_t size;
	int* cells;
};

static void dump_memory(struct memory_cells *mem);
static void read_file(char* name, struct memory_cells *mem);
static void usage();
static void push_to_cell(int value, struct memory_cells *mem);
static void copy(struct memory_cells* dst, struct memory_cells* tgt);
static void redistribute(struct memory_cells *mem);
static size_t history_find(struct memory_cells *needle, struct memory_cells *history, size_t history_size);
static int history_contains(struct memory_cells *needle, struct memory_cells *history, size_t history_size);
static int memory_cell_equals(struct memory_cells *a, struct memory_cells *b);

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		usage(argv[0]);
		return 0;
	}

	struct memory_cells mem = { .size = 0,.cells = NULL };
	struct memory_cells history[4096 * 4];

	printf("Loading memory.\n");
	read_file(argv[1], &mem);
	printf("Initial state:\n");
	dump_memory(&mem);

	memset(history, 0, sizeof(history));

	for (size_t i = 0; i < sizeof(history) / sizeof(struct memory_cells); i++)
	{
		copy(&history[i], &mem);

		redistribute(&mem);
		printf("Iteration: %lu - ", i);
		dump_memory(&(history[i]));

		if (history_contains(&mem, history, i + 1))
		{
			size_t cpyindx = history_find(&mem, history, i + 1);
			printf("Loop found: %lu %lu\n", i + 1, cpyindx);
			printf("Iteration: %lu - ", i + 1);
			dump_memory(&mem);
			printf("Iteration: %lu - ", cpyindx);
			dump_memory(&(history[cpyindx]));
			printf("Distance: %lu", (i + 1) - cpyindx);
			return 0;
		}
	}

	free(mem.cells);
	return 0;
}

static int memory_cell_equals(struct memory_cells *a, struct memory_cells *b)
{
	if (a->size != b->size) return FALSE;
	for (size_t i = 0; i < a->size; i++)
	{
		if (a->cells[i] != b->cells[i])
		{
			return FALSE;
		}
	}

	return TRUE;
}

static size_t history_find(struct memory_cells *needle, struct memory_cells *history, size_t history_size)
{
	for (size_t i = 0; i < history_size; i++)
	{
		if (memory_cell_equals(&(history[i]), needle))
		{
			return i;
		}
	}

	return -1;
}

static int history_contains(struct memory_cells *needle, struct memory_cells *history, size_t history_size)
{
	for (size_t i = 0; i < history_size; i++)
	{
		if (memory_cell_equals(&(history[i]), needle))
		{
			return TRUE;
		}
	}

	return FALSE;
}

static size_t select_highest_cell(struct memory_cells *mem)
{
	int maxv = INT_MIN;
	int maxidx = 0;
	for (size_t i = 0; i < mem->size; i++)
	{
		if (maxv < mem->cells[i])
		{
			maxv = mem->cells[i];
			maxidx = i;
		}
	}

	return maxidx;
}

static void redistribute(struct memory_cells *mem)
{
	int maxidx = select_highest_cell(mem);
	int reservoir = mem->cells[maxidx];
	mem->cells[maxidx] = 0;

	for (size_t i = maxidx + 1; reservoir > 0; i++)
	{
		reservoir--;
		mem->cells[(i % mem->size)]++;
	}
}

static void copy(struct memory_cells* dst, struct memory_cells* src)
{
	dst->size = src->size;
	dst->cells = malloc(src->size * sizeof(int));
	memcpy(dst->cells, src->cells, src->size * sizeof(int));
}

static void dump_memory(struct memory_cells *mem)
{
	printf("Memory[%p](%llu){", (void *)mem, (long long unsigned int)mem->size);
	for (size_t i = 0; i < mem->size; i++)
	{
		printf("%i", mem->cells[i]);

		if (i != mem->size - 1)
		{
			printf(" ");
		}
	}
	printf("}\n");
}

static int is_digit(char value)
{
	return '0' <= value && value <= '9';
}

static void push_to_cell(int value, struct memory_cells *mem)
{
	if (mem->cells != NULL)
	{
		int* values = mem->cells;
		int* newptr = malloc((mem->size + 1) * sizeof(int));
		memcpy(newptr, values, mem->size * sizeof(int));
		mem->size += 1;
		free(values);
		mem->cells = newptr;
		mem->cells[mem->size - 1] = value;
	}
	else
	{
		mem->cells = malloc(sizeof(int));
		mem->size = 1;
		mem->cells[mem->size - 1] = value;
	}
}

static void read_file(char* name, struct memory_cells *mem)
{
	if (mem->cells != NULL) free(mem->cells);

	char readbuf[1024];
	char chr;
	size_t readbufidx = 0;
	memset(readbuf, 0, sizeof readbuf);
	FILE *file;

	file = fopen(name, "r");

	if (file)
	{
		printf("Reading %s.\n", name);

		while (fread(&chr, 1, 1, file))
		{
			if (is_digit(chr))
			{
				readbuf[readbufidx] = chr;
				readbufidx++;
				if (readbufidx >= sizeof readbuf)
				{
					fprintf(stderr, "Buffer overflow.\n");
					return;
				}
			}
			else
			{
				if (readbufidx > 0)
				{
					int value = atoi(readbuf);
					push_to_cell(value, mem);
					readbufidx = 0;
					memset(readbuf, 0, sizeof readbuf);
				}
			}
		}

		fclose(file);
	}
	else
	{
		fprintf(stderr, "Can't open file %s.\n", name);
	}
}

static void usage(char* prgname)
{
	printf("Usage:\n%s <input file>\n", prgname);
}
