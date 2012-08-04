#include <stdlib.h>
#include <string.h>

#include "kmp.h"

struct occurance_list*
kmp_search(char* text_buffer, char* match_pattern,
		int text_buffer_len, int match_pattern_len) {

    if (text_buffer_len < match_pattern_len)
        return NULL;
    
	int pos = 0;
	int i = 0;

	int* table = (int*) malloc(match_pattern_len * sizeof(int));
    
    struct occurance_list* output;
    output = (struct occurance_list*) malloc(sizeof(struct occurance_list));
    init_occurance_list(output);

	kmp_build_table(match_pattern, table, match_pattern_len);

	//while (pos + i < text_buffer_len) {
    // it has no meaning to subtract len of the pattern from txt buffer len
    // since the match_pattern_len is in most of all cases much smaller than
    // the size of the text which results in many unnecessary operations
    while (pos < text_buffer_len) {  
		if (match_pattern[i] == text_buffer[pos]) {
            i++;
            pos++;
            
            if (i == match_pattern_len - 1) { // if the search is complete
                add_occurance(output, pos - i);
                i = table[i - 1];
            }
        } else {
            if (table[i] > 0)
                i = table[i-1];
            else
                pos++;
        }
	}

    free(table);
    
	return output;
}

void 
kmp_build_table(char* pattern, int* out_table, int size) {
    
    int len = 0;
    
    out_table[0] = 0;
    
    for (int i = 1; i < size;) {
        if (pattern[i] == pattern[len]) {
            len++;
            out_table[i] = len;
            i++;
        } else {
            if (len != 0)
                len = out_table[len - 1];
            else {
                out_table[i] = 0;
                i++;
            }
        }
    }
}

void
init_occurance_list(struct occurance_list* list) {
    list->capacity = EXPECTED_OCC_NUM;
    list->size = 0;
    list->list = malloc(sizeof(int) * list->capacity);
    
}

void
release_occurace_list(struct occurance_list* list) {
    free(list->list);
    list->list = NULL;
}

void
add_occurance(struct occurance_list* list, int occurance_idx) {
    if (list->size >= list->capacity) {
        int* old = list->list;
        list->capacity = 2 * list->capacity;
        list->list = (int*) malloc(sizeof(int) * list->capacity);
        memcpy(list->list, old, list->size * sizeof(int));
        free(old);
    }
    
    list->list[list->size] = occurance_idx;
    list->size++;
    
}
