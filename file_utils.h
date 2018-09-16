#ifndef            __H_FILE_UTILS__
#define            __H_FILE_UTILS__

/*
 * verbose_print - Used in conjunction with a verbose
 *                 flag, when passed a flag and string,
 *                 the string will be printed if the
 *                 flag is true.
 *
 *                 Provided in file_utils as a general helper for
 *                 any program using this library.
 *
 *
 * @param int is_verbose - A boolean, 0 the provided string will
 *                         not be printed, 1 and it will be
 *                         printed
 *
 * @param char* string   - A message to be printed if is_verbose
 *                         evaluates to true
 *
 * @return void
 *
 */
void verbose_print( int is_verbose, char* string);

/*
 * read_file - Overloaded function and defaults is_verbose to 0,
 *             while calling read_file_verbose with all provided
 *             parameters. See read_file_verbose for signature
 *             documentation
 */

int read_file( char* filename, char **buffer);

/*
 * read_file_verbose - Given an allocated memory buffer and
 *                     a filename this will allocate the exact
 *                     amount of memory needed to hold the file
 *                     in memory and assign it to the provided pointer
 *
 * @param char* filename - The name of the file to load
 * @param char **buffer  - The pointer in which to load the file
 * @param int is_verbose - A boolean to instruct the function to
 *                         print out all of its operations
 *
 * @return int - On success returns the file size, if an error
 *               occurs, 0 is returned
 */

int read_file_verbose( char* filename, char **buffer, int is_verbose);

/*
 * write_file - Overloaded function and defaults is_verbose to 0,
 *              while calling write_file_verbose with all provided
 *              parameters See write_file_verbose for signature
 *              documentation
 */

int write_file( char* filename, char *buffer, int size);

/*
 * write_file_verbose - Given an allocated memory buffer and a filename
 *
 * @param char* filename - The name of the file to write to
 * @param char *buffer   - The pointer in which the file is loaded
 * @param int size       - The length of the file in bytes
 * @param int is_verbose - A boolean to instruct the function to
 *                         print out all of its operations
 *
 * @return int - On success returns the file size of the written
 *               file, if an error occurs, 0 is returned
 */

int write_file_verbose( char* filename, char *buffer, int size, int is_verbose);

#endif
