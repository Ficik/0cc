#ifndef KMP_H_
#define KMP_H_

#define EXPECTED_OCC_NUM 40

struct occurance_list {
    int* list;
    int size;
    int capacity;
};

/**
 * Knuth-Morris-Pratt search algorithm
 *
 * @param text_buffer The text in which the pattern is to be searched.
 * @param match_pattern The searched pattern.
 * @param text_buffer_len The length of the text in which the search occurs.
 * @param match_pattern_len The length of the searched pattern.
 * @return Returns the indices of all occurances of the patterin in the text if
 *          they exist. NULL otherwise.
 */
struct occurance_list*
kmp_search(char* text_buffer, char* match_pattern,
		int text_buffer_len, int searched_text_len);


void 
kmp_build_table(char* pattern, int* out_table, int out_size);

/**
 * This function initializes and allocate necessary memory for all fields
 * of occurance_list instance. It shouldn't be used with already initialized
 * instances as it causes a memory leak.
 * 
 * @param list An instance of the occurance_list structure.
 */
void
init_occurance_list(struct occurance_list* list);

/**
 * Releases allocated resources of instance which is given as parameter.
 * The pointer to the list is then set to NULL so it is safe to invoke this
 * method again.
 * 
 * @param list An instance of the occurance_list structure.
 */
void
release_occurace_list(struct occurance_list* list);

/**
 * 
 * @param list An initialized instance of the occurance_list structure.
 * @param occurance_idx The index which is to be added into the list.
 */
void
add_occurance(struct occurance_list* list, int occurance_idx);

#endif /* KMP_H_ */
