# reverse_program

Reverses an `input_file`, character-by-character, to the provided `output_file`.

Usage:

    ./reverse [-fvh] <input-file> <output-file>

Options:

    -f - Force mode to allow destination file overwrites
    -v - Verbose mode to print out steps of the process
    -h - Help to see this menu
    
## Docker Usage

Utilizing [auto-compile-c-programs](https://github.com/NickBeukema/auto-compile-c-programs) ([Original](https://github.com/mavieth/auto-compile-c-programs) forked for Docker usage), this provides an auto compiling development environment, watching changes to all `*.c` files and compiling. Keep in mind this all happens in a Linux "VM", so in order to run the executable, we must jump through a hoop of running it inside the same "VM". Follow these instructions for success.

1. Install Docker and Docker Compose
1. Pull repo

        git clone git@github.com:NickBeukema/reverse_program.git
        cd reverse_program

1. Run the following to pull and create images (this will take a while):

        docker-compose up
        
 1. A running docker container holds our code, and is syncing between our host machine and the container. Any changes we make in our own IDE of choice will be reflected in the container, and will trigger an auto-compile. To run our program, open a new terminal/tab and run the following:
 
         source .environment
         run ./reverse reverse.c reverse-reversed.not-c
         
  1. Viola! Our C-Container compiled and ran inside of the container, but synced the reversed file to our host machine.
  
         cat reverse-reversed.not-c
         
## Developer Notes

If you're having issues updating the pulled Gulp setup in the Dockerfile, run the following to rebuild the image without cache:

    docker-compose build --no-cache
    
And then run:

    docker-compose up
