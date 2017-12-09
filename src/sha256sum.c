/******************************************************************************/
/*!
\file    sha256sum.c
\author  John Salguero
\par     email: john\@johnsalguero.com
\date    5/29/2013

\brief
  This file contains the following functions which are used to generate
  sha256 sums which can be used to check the integrity of code and programs.

  Functions Include:
  -
  -
  - main

  These allow for full functionality of the sha256sum program which acts
  like the utility that comes with most linux distributions.
 */
/******************************************************************************/
#include <stdlib.h> /* malloc, free */
#include <unistd.h> /* getopt, optarg, optind, optopt                    */
#include <getopt.h> /* getopt  struct option (for get_option_long)       */
#include <stdio.h>  /* printf, stdin, FILE, fopen, fclose */
#include <stdlib.h> /* exit, EXIT_SUCCESS */
#include <stdint.h> /* uint8_t */
#include <dirent.h> /* DIR, opendir, closedir */
#include <errno.h>  /* errno */

/* adding the flags as an enum */
typedef enum
{
  BINARY = 0x01,
  CHECK  = 0x02,
  TAG    = 0x04,
  IGNORE = 0x08,
  QUIET  = 0x10,
  STATUS = 0x20,
  STRICT = 0x40,
  WARN   = 0x80
} CFLAGS;

/* adding bool type to C-Language */
typedef enum { false, true } bool;


/**************************************************************************/
/*!
             process_file 

  \brief     depending on the flags, processes the file and outputs the
             sha256 digest. 

  \param     **pis
             FILE** that points to a stream

  \param     flags 
             holds info about how to process the file

  \return    void 
*/
/**************************************************************************/
void process_file(FILE **pis, CFLAGS flags)
{

}

/**************************************************************************/
/*!
             check_valid_file 

  \brief     Checks if a null terminated string carries a proper file
             location, and returns a pointer to its stream if it does. 

  \param     *file_location
             char * that points to a C-style string

  \param     flags 
             holds whether or not to open in text or binary

  \return    **is 
             Pointer to an open file stream, if the file is valid.
*/
/**************************************************************************/
FILE** check_valid_file(char* file_location, CFLAGS flags)
{
  FILE** is = NULL;
  DIR*  directory = opendir(file_location);

  /* Check to see if the path is a directory */
  if(directory != NULL)
  {
    closedir(directory);
    printf("sha256sum: %s: Is a directory\n", file_location);
    return is;
  }
  if(errno == ENOTDIR) /* Check to see if the path is a file */
  {
    is = malloc(sizeof(FILE*));
    if(flags|BINARY)
     *is = fopen(file_location, "rb");
    else
     *is = fopen(file_location, "rt");
  }
  else
  {
    printf("sha256sum: %s: No such file or directory\n", file_location);
  }



  return is;
}

/**************************************************************************/
/*!
             main

  \brief     Entry-point for the program, reads in the command-line
             arguments, and sets the appropriate flags, then
             executes RunFilter on either the files specified or
             stdin.

  \param     argc
             The amount of command-line arguments

  \param     **argv
             Pointer to a pointer to a char, which has C-style strings
             of the command-line arguments in contiguous memory, that is,
             you can imagine this as an array of strings.

  \return    int
             The exit code of the program.
*/
/**************************************************************************/
int main(int argc, char **argv)
{
  int c;                        /* option on the command line */
  CFLAGS flags = 0;             /* flags that determine how to process input */
  FILE **pis;                   /* pointer to stream that the process uses */
  bool binaryIsSet = false;     /* whether binary or text mode is specified */
  bool fileIsSpecified = false; /* whether a file is specified */

  do
  {
    int option_index = 0; /* index of the long option encountered */
    /* array of structs of the long options available */
    static struct option long_options[] =
    {
      {"binary",         no_argument, NULL, 'b' },
      {"check",          no_argument, NULL, 'c' },
      {"tag",            no_argument, NULL, '0' },
      {"ignore-missing", no_argument, NULL, '0' },
      {"quiet",          no_argument, NULL, '0' },
      {"status",         no_argument, NULL, '0' },
      {"strict",         no_argument, NULL, '0' },
      {"warn",           no_argument, NULL, 'w' },
      {"help",           no_argument, NULL, '0' },
      {"version",        no_argument, NULL, '0' },
      {"text",           no_argument, NULL, 't' }
    };

    c = getopt_long(argc, argv, ":bctw", long_options, &option_index);

    /* Switich of all the options in the program set the appropriate flags */
    switch(c)
    {
      case 'b':
       flags |= BINARY;
       binaryIsSet = true; 
      break;
      case 'c':
        flags |= CHECK;
      break;
      case 't':
        binaryIsSet = true;
      break;
      case 'w':
        flags |= WARN;
      break;
      case 0: /* Long Options without a short option */
       flags |= 1 << option_index; 
      break;
      case '?':
        printf("sha256sum: unknown option -- %c\n", optopt);
	printf("Try \"sha256sum --help\" for more information\n");
      break;
    }
  }while(c != -1);

  if(optind < argc)     /* checks optind to see if there are files to process */
  {
    /* there are files, default method is binary */
    if(binaryIsSet == false)
      flags |= BINARY;

    while(optind < argc)
    {
      pis = check_valid_file(argv[optind++], flags);
      if(pis != NULL)
      {
        process_file(pis, flags);
	fclose(*pis);
	free(pis);
      }
    }
  }
  else
  {
    if(stdin) /* checks if stdin is valid */
    {
      if(flags|BINARY)
        freopen(NULL, "rb", stdin);
      process_file(&stdin, flags);
    }
  }
  return 0;
}
