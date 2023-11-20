#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

//FROM CLASS
//FEATURES:
//start programs with argument list
//input and output redirection
    // > foo   in the command line means stdout will be foo
    // < foo   in the command line means stdin will be foo
//piping
    //arg0 arg1 arg2 | argA argB argC    --- WE ONLY NEED TO HAVE 2 WE DONT NEED MORE THAN THAT
// wildcards
    //before*after    use opendir search every file that contains before and after
    //ls *.c
    //echo *.c

    //  path/to/some/file*name
//Conditional execution: then, else
    //mysh> make program
    //mysh> then ./program

    //mysh> some_program
    //mysh> then echo Success!

//Major componenets:
    //command-line parser
        //wildcard expansion
    //program launcher
        //create child process
        //change stdin/stdout in child
        //gather exit status
//exit
    //terminates the shell

//there is more info on the 11/15 txt doccument in files on canvas about the assignment
//he put also a full structure of how the assignment should look in the txt doccument. it should be really helpful

//finally we need to create our own testing file again

void mysh(size_t job){

    return NULL;
}