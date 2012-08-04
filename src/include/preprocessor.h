
#ifndef PREPROCESSOR_H_
#define PREPROCESSOR_H_

/**
 * 
 * 
 * @param input_buffer
 * @param buffer_size
 * @param out_preprocess_buffer
 * @param out_preprocess_buffer_size
 * @param file Optional parameter. If not NULL the 
 * @param mode The mode of preprocessor's work. Set to 0 works with minimum memory 
 *          requirements. When set to 1 the speed is prefered.
 * @return 
 */
int
preprocess(const char* input_buffer, int buffer_size, char* out_preprocess_buffer,
        int out_preprocess_buffer_size, FILE* file, int mode);

int
piplined_preprocess(const char* input_buffer, int buffer_size, char* out_preprocess_buffer,
        int out_preprocess_buffer_size, FILE* file);

int
full_buffered_preprocess(const char* input_buffer, int buffer_size,
        char* out_preprocess_buffer, int out_preprocess_buffer_size, FILE* file);

#endif /* PREPROCESSOR_H_ */
