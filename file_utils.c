#include "file_utils.h"
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>

/*
 * verbose_print entrypoint, see file_utils.h
 * for full signature documentation
 */

void verbose_print(int is_verbose, char* string) {
  if(is_verbose) {
    printf("%s", string);
  }
}


/*
 * read_file entrypoint, see file_utils.h
 * for full signature documentation
 */

int read_file(char* filename, char **buffer) {
  return read_file_verbose(filename, buffer, 0);
}


/*
 * read_file_verbose  entrypoint, see file_utils.h
 * for full signature documentation
 */

int read_file_verbose(char* filename, char **buffer, int is_verbose) {

  verbose_print(is_verbose, "\nLoading file: \n");
  verbose_print(is_verbose, filename);
  verbose_print(is_verbose, "\n");

  // Open File from designated file location
  //
  // Opening process inspired by:
  // stackoverflow.com/a/174552/5806198
  FILE * file = fopen(filename, "r");

  // Check for errors opening the file
  if(!file) {
    fprintf(stderr, "Error loading file: %s\n", filename);
    return 0;
  }

  verbose_print(is_verbose, "\nOpened file\n");

  // Get the file to be pointing to the
  // last character available - SEEK_END
  int fseek_end_ret = fseek(file, 0, SEEK_END);

  verbose_print(is_verbose, "\nFinished seeking file\n");

  // Check return of fseek to the end
  // of the file
  if(fseek_end_ret != 0) {
    fprintf(stderr, "Error seeking the file: %s\n", filename);
    fclose(file);
    return 0;
  }

  // Pull the length from the file
  long length = ftell(file);

  if(is_verbose) {
    printf("\nLength of file loaded: %ld bytes\n", length);
  }



  // Check to make sure the length is not zero
  if(length == 0) {
    fprintf(stderr, "Error reading length of file: %s\n", filename);
    fclose(file);
    return 0;
  }


  // Return the file to be pointing to
  // the beginning of the file again
  int fseek_set_ret = fseek(file, 0, SEEK_SET);

  // Check return of fseek to the
  // beginning of the file
  if(fseek_end_ret != 0) {
    fprintf(stderr, "Error seeking the file: %s\n", filename);
    fclose(file);
    return 0;
  }

  verbose_print(is_verbose, "\nSeeking to beginning of file successful\n");

  // Allocate memory and assign it to the
  // memory pointer passed into this function
  *buffer = (char*)malloc(length);

  // Check if there are problems with allocating
  // memory
  if(!*buffer) {
    fprintf(stderr, "Error allocating memory for file.\n");
    fclose(file);
    return 0;
  }

  verbose_print(is_verbose, "\nAllocated space for file in memory\n");


  // Read contents of file into the allocated buffer
  // with blocks the size of chars and a total of
  // length of chars, and from the file
  int size_of_file = fread(*buffer, sizeof(char), sizeof(char) * length, file);

  // Now that the file is in memory, the file
  // can be closed
  fclose(file);

  // Check if the return from fread is zero, if so
  // there was an error reading the file
  if(size_of_file == 0) {
    fprintf(stderr, "Error inserting file contents into memory buffer\n");
    free(*buffer);
    return 0;
  }

  if(is_verbose) {
    printf("\nSuccessfuly loaded file into buffer of size: %d bytes\n", size_of_file);
  }

  // Communicate back to the caller how big the
  // file loaded into the provided buffer is
  return size_of_file;
}



/*
 * write_file  entrypoint, see file_utils.h
 * for full signature documentation
 */

int write_file(char* filename, char *buffer, int size) {
  return write_file_verbose(filename, buffer, size, 0);
}


/*
 * write_file_verbose  entrypoint, see file_utils.h
 * for full signature documentation
 */

int write_file_verbose(char* filename, char *buffer, int size, int is_verbose) {

  // Create a file of provided filename
  // opening in "w" mode, for writing
  FILE * file = fopen(filename, "w");


  // Check to make sure the file was able
  // to be opened
  if(!file) {
    fprintf(stderr, "Error creating file: %s\n", filename);
    return 0;
  }

  // Use fwrite to write the provided buffer
  // to the created file, with size total bytes
  // each element a char size
  int file_write_size = fwrite(buffer, size, sizeof(char), file);

  // Regardless of success or failier, close
  // the file that is being written to
  fclose(file);

  // Check the written file size, if zero
  // an error occured
  if(file_write_size == 0) {
    fprintf(stderr, "Error writing memory buffer to file\n");
    return 0;
  }

  // Communicate back to the caller how big the
  // file written to disk is, for verification
  // that it is done successfully
  return file_write_size;
}
