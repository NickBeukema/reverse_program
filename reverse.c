/*
 * program.c
 * Nick Beukema
 * 
 * Takes two command line arguments, the first
 * being an input file, and the second an output.
 * The input file will be completely reversed
 * byte by byte into the designated output file.
 *
 * Usage:
 *
 * ./reverse [-vfh] <input-file> <output-file>
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "file_utils.h"

/*
 *
 * General usage function, used to display to user
 * how to use the program
 *
 */
void usage() {
  printf("\n\nUsage:\n\n");
  printf("\t./reverse [-fvh] <input-file> <output-file>\n");
  printf("\nOptions:\n\n");
  printf("\t-f - Force mode to allow destination file overwrites\n");
  printf("\t-v - Verbose mode to print out steps of the process\n");
  printf("\t-h - Help to see this menu\n\n");
}

/*
 * check_flags - Used to pass in a flag along with
 *               all command line arguments, and
 *               will determine if the flag is
 *               present
 *
 * @param char flag   - The character being checked for in arguments
 * @param int argc    - The total count of command line arguments
 * @param char** argv - The character array of all command line arguments
 *
 * @return int - Returns the position of the agument in
 *               the array of all arguments if it exists,
 *               otherwise returns 0.
 *
 */

int check_flags(char flag, int argc, char** argv) {

  // Loop over command line arguments
  for(int i = 0; i < argc; i++) {

    // If the first portion of the argument
    // includes the character '-', it is
    // an option flag
    if(argv[i][0] == '-') {

      // Loop through until we hit the null
      // character terminating the string
      for(int j = 0; argv[i][j] != '\0'; j++) {

        // If the provided flag character
        // equals the current character,
        // return the index in which it
        // is found
        if(flag == argv[i][j]) {
          return i;
        }

      }
    }
  }

  return 0;
}

/*
 *
 * Main function, entrypoint to reverse program
 * See above for usage, or run with the -h flag
 *
 */
int main(int argc, char** argv){

  // Check for help before counting arguments
  int is_help = check_flags('h', argc, argv);

  if(is_help) {
    usage();
    return 0;
  }

  // Assure that there are at least three arguments
  // passed into the program. At miniumum, the first
  // one being the program name, the next two being
  // the input and output filenames
  if(argc < 3) {
    fprintf(stderr, "Wrong number of arguments\n");
    usage();
    return 1;
  }

  // Check for command line arguments
  int is_verbose = check_flags('v', argc, argv);
  int is_forced = check_flags('f', argc, argv);

  // Program does not support passing in
  // command line options after the provided
  // filenames, must come before. Check for this
  // and exit if any arguments are passed in after
  // filenames (Except help, if you need help, we
  // should help)
  if(is_verbose == argc - 1 ||
     is_forced == argc - 1) {
    fprintf(stderr, "Cannot pass in command line options before filenames\n");
    usage();
    return 1;
  }


  if(is_verbose) {
    printf("Running in verbose mode\n");
  }

  if(is_forced) {
    printf("Running in forced mode\n");
  }

  // Instantiate both input and output filenames
  // from command-line arguments
  char* file_name = argv[argc - 2];
  char* destination_file_name = argv[argc - 1];

  verbose_print(is_verbose, "\nChecking for existing destination file\n");

  // If destination file exists and the program
  // is not running in forced mode
  //
  // https://stackoverflow.com/a/34184922/5806198
  if(!access(destination_file_name, F_OK ) && !is_forced){
    fprintf(
        stderr,
        "\nThe provided destination already exists: %s\nIn order to force an overwrite, pass in\nthe command line argument '-f'\n",
        destination_file_name
    );
    return 1;
  }

  // Allocate the file buffer for the file to be
  // placed into memory. Created with enough space
  // to hold a char pointer
  char** file_buffer = (char**)malloc(sizeof(char*));

  verbose_print(is_verbose, "\nAllocated initial double pointer for loading file in memory\n");

  // Call into the file_utils library and read the
  // file, capture the return value of file size
  int file_size = read_file_verbose(file_name, file_buffer, is_verbose);

  // Check if file size is 0 and return the program
  // early if so
  if(file_size == 0) {
    free(file_buffer);
    return 1;
  }

  // Allocate another block of memory to hold the
  // reversed string, which we build below
  char* reverse_buffer = (char*)malloc(file_size * sizeof(char));

  // Check if there was an error allocating the
  // buffer
  if(!reverse_buffer){
    fprintf(stderr, "Error allocating memory for the reversed string");
    return 1;
  }

  verbose_print(is_verbose, "\nSuccessfuly allocated reverse buffer\n");

  // Loop the number of characters in the file
  for (int i = 0; i < file_size; i++) {

    // Determine the corresponding reversed
    // character index, correcting for zero based
    // index (subtracting 1 from file_size)
    int reverse_character_index = (file_size - 1) - i;

    // Pull the reverse character off of the
    // loaded file
    char character = file_buffer[0][reverse_character_index];

    // Assign the reverse character to the
    // position at index of i
    reverse_buffer[i] = character;
  }

  verbose_print(is_verbose, "\nReversed input file in memory\n");

  // Pass the destination file name, the
  // reversed string in memory, and the
  // size of the string into the file_utils
  // library
  int written_file_size = write_file_verbose(destination_file_name, reverse_buffer, file_size, is_verbose);

  // Regardless of how the write function
  // went, free the memory
  free(*file_buffer);
  free(file_buffer);
  free(reverse_buffer);

  verbose_print(is_verbose, "\nMemory freed\n");

  // Check the size of the written file,
  // if zero is given, an error has occured
  if(written_file_size == 0) {
    return 1;
  }

  verbose_print(is_verbose, "\nSuccessfully finished reversing file:\n");
  verbose_print(is_verbose, destination_file_name);
  verbose_print(is_verbose, "\n");

  return 0;
}

