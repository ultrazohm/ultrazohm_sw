// #include "uz_circular_buf.h"

// #include <stdint.h>
// #define EXAMPLE_BUFFER_SIZE 10

// int main(){
// uint8_t * buffer  = malloc(EXAMPLE_BUFFER_SIZE * sizeof(uint8_t));
// cbuf_handle_t cbuf = circular_buf_init(buffer, 
// 	EXAMPLE_BUFFER_SIZE);
//    bool full = circular_buf_full(cbuf);
// bool empty = circular_buf_empty(cbuf);
// printf("Current buffer size: %zu\n", circular_buf_size(cbuf);

// free(buffer);
// circular_buf_free(cbuf);

//     return 1;
// };
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <assert.h>

#include "uz_circular_buf.h"

#define EXAMPLE_BUFFER_SIZE 10

void print_buffer_status(cbuf_handle_t cbuf);

int main(void)
{
	uint8_t * buffer  = malloc(EXAMPLE_BUFFER_SIZE * sizeof(uint8_t));

	printf("\n=== C Circular Buffer Check ===\n");

	cbuf_handle_t cbuf = circular_buf_init(buffer, EXAMPLE_BUFFER_SIZE);

	printf("Buffer initialized. ");
	print_buffer_status(cbuf);

	printf("\n******\nAdding %d values\n", EXAMPLE_BUFFER_SIZE - 1);
	for(uint8_t i = 0; i < (EXAMPLE_BUFFER_SIZE - 1); i++)
	{
		circular_buf_put(cbuf, i);
		printf("Added %u, Size now: %zu\n", i, circular_buf_size(cbuf));
	}

	print_buffer_status(cbuf);

	printf("\n******\nAdding %d values\n", EXAMPLE_BUFFER_SIZE);
	for(uint8_t i = 0; i < EXAMPLE_BUFFER_SIZE; i++)
	{
		circular_buf_put(cbuf, i);
		printf("Added %u, Size now: %zu\n", i, circular_buf_size(cbuf));
	}

	print_buffer_status(cbuf);

	printf("\n******\nReading back values: ");
	while(!circular_buf_empty(cbuf))
	{
		uint8_t data;
		circular_buf_get(cbuf, &data);
		printf("%u ", data);
	}
	printf("\n");

	print_buffer_status(cbuf);

	printf("\n******\nAdding %d values\n", EXAMPLE_BUFFER_SIZE + 5);
	for(uint8_t i = 0; i < EXAMPLE_BUFFER_SIZE + 5; i++)
	{
		circular_buf_put(cbuf, i);
		printf("Added %u, Size now: %zu\n", i, circular_buf_size(cbuf));
	}

	print_buffer_status(cbuf);

	printf("\n******\nReading back values: ");
	while(!circular_buf_empty(cbuf))
	{
		uint8_t data;
		circular_buf_get(cbuf, &data);
		printf("%u ", data);
	}
	printf("\n");

	printf("\n******\nAdding %d values using non-overwrite version\n", EXAMPLE_BUFFER_SIZE + 5);
	for(uint8_t i = 0; i < EXAMPLE_BUFFER_SIZE + 5; i++)
	{
		circular_buf_put(cbuf, i);
	}

	print_buffer_status(cbuf);

	printf("\n******\nReading back values: ");
	while(!circular_buf_empty(cbuf))
	{
		uint8_t data;
		circular_buf_get(cbuf, &data);
		printf("%u ", data);
	}
	printf("\n");

	free(buffer);
	circular_buf_free(cbuf);

	return 0;
}

void print_buffer_status(cbuf_handle_t cbuf)
{
	printf("Full: %d, empty: %d, size: %zu\n",
		circular_buf_full(cbuf),
		circular_buf_empty(cbuf),
		circular_buf_size(cbuf));
}