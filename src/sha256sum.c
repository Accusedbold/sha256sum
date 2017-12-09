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
#include <unistd.h> /* getopt, optarg, optind, optopt                    */
#include <getopt.h> /* getopt  struct option (for get_option_long)       */
#include <stdio.h>  /* printf, stdin, FILE */
#include <stdlib.h> /* exit, EXIT_SUCCESS */
#include <stdint.h> /* uint8_t */

/*! defined BINARY flag */
#define BINARY 0x01;
/*! defined CHECK flag */
#define CHECK 0x02;
/*! defined TAG flag */
#define TAG 0x04;
/*! defined IGNORE flag */
#define IGNORE 0x08;
/*! defined QUIET flag */
#define QUIET 0x10;
/*! defined STATUS flag */
#define STATUS 0x20;
/*! defined STRICT flag */
#define STRICT 0x40;
/*! defined WARN flag */
#define WARN 0x80;


/* adding bool type to C-Language */
typedef enum { false, true } bool;

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
  int index;                    /* temporary index for checking valid files */
  int c;                        /* option on the command line */
  uint8_t flags = 0;            /* flags that determine how to process input */
  FILE *fp;                     /* stream that the process uses */
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
      {"text",           no_argument, NULL, 't' },
      {"ignore-missing", no_argument, NULL, '0' },
      {"quiet",          no_argument, NULL, '0' },
      {"status",         no_argument, NULL, '0' },
      {"strict",         no_argument, NULL, '0' },
      {"warn",           no_argument, NULL, 'w' },
      {"help",           no_argument, NULL, '0' },
      {"version",        no_argument, NULL, '0' }
    };

    c = getopt_long(argc, argv, ":bctw", long_options, &option_index);

    /* Switich of all the options in the program */
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
      case 0:
        
      break;
      case '?':
        printf("sha256sum: unknown option -- %c\n", optopt);
	printf("Try \"sha256sum --help\" for more information\n");
      break;
    }
  }while(c != -1);

  return 0;
}
