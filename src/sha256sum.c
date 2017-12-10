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
  - verify_checksums
  - process_file
  - main
  - display_help
  - display_version
  - display_tag_support
  - print_hash

  These allow for full functionality of the sha256sum program which acts
  like the utility that comes with most linux distributions.
 */
/******************************************************************************/
#include <stdlib.h> /* malloc, free */
#include <unistd.h> /* getopt, optarg, optind, optopt                    */
#include <getopt.h> /* getopt  struct option (for get_option_long)       */
#include <stdio.h>  /* fprintf, printf, stdin, FILE, fopen, fclose */
#include <stdlib.h> /* exit, EXIT_SUCCESS */
#include <stdint.h> /* uint8_t */
#include <dirent.h> /* DIR, opendir, closedir */
#include <errno.h>  /* errno */

/* adding the flags as an enum */
typedef enum
{
  BINARY  = 0x01,
  CHECK   = 0x02,
  TAG     = 0x04,
  IGNORE  = 0x08,
  QUIET   = 0x10,
  STATUS  = 0x20,
  STRICT  = 0x40,
  WARN    = 0x80,
  ALL     = 0xFF,
  HELP    = 0x100,
  VERSION = 0x200
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

  \param     out
             char* that holds the Hash Digest

  \return    void 
*/
/**************************************************************************/
void process_file(FILE **pis, CFLAGS flags, char* out)
{
  
}

/**************************************************************************/
/*!
             print_hash 

  \brief     prints out the hash in the format depending on the flags.

  \param     file_path
             C-style string that points to the file

  \param     hash 
             C-style string that holds the Digest

  \param     flags 
             holds info about how to process the file

  \return    void 
*/
/**************************************************************************/

void print_hash(char* file_path, char* hash, CFLAGS flags)
{
  char c = ' ';

  if(flags&TAG)
  {
    printf("SHA256 (%s) = %s", file_path, hash);
    return;
  }

  if(flags&BINARY)
    c = '*';

  printf("%s %c%s", hash, c, file_path);
}
/**************************************************************************/
/*!
             display_version

  \brief     tells the user what version of the program they are running. 

  \return    void 
*/
/**************************************************************************/
void display_version()
{
  printf("sha256sum (John Salguero's haphazard attempt) 0.0.1a\n");
  printf("Not to be confused with the one in GNU coreutils, also it does\n");
  printf("not have a GPL license, instead it's BSD.\n\n");
  printf("Oh, yeah, there's absolutely no warranty with this software.");
  exit(EXIT_SUCCESS);
}

/**************************************************************************/
/*!
             display_tag_support

  \brief     tells the user what version of the program they are running. 

  \return    void 
*/
/**************************************************************************/
void display_tag_support()
{
  printf("sha256sum: --tag does not support --text mode\n");
  printf("Try \"sha256 --help\" for more information.\n");
  exit(EXIT_SUCCESS);
}

/**************************************************************************/
/*!
             display_help 

  \brief     shows the user the proper command-line options and the use
             of the program. 

  \return    void 
*/
/**************************************************************************/
void display_help()
{
  printf("Usage: sha256sum [OPTION]... [FILE]...\n");
  printf("Print or check SHA256 (256-bit) checksums.\n\n");
  printf("With no FILE, or when FILE is -, read standard input.\n\n");  
  printf("  -b, --binary         read in binary mode (default unless reading tty stdin)\n");
  printf("  -c, --check          read SHA256 sums from the FILEs and check them\n");
  printf("      --tag            create a BSD-style checksum\n");
  printf("  -t, --text           read in text mode (default if reading tty stdin)\n\n");
  printf("The following five options are useful only when verifying checksums(Not Yet Implemented):\n");
  printf("      --ignore-missing  don't fail or report status for missing files\n");
  printf("      --quiet          don't print OK for each successfully verified file\n");
  printf("      --status         don't output anything, status code shows success\n");
  printf("      --strict         exit non-zero for improperly formatted checksum lines\n");
  printf("  -w, --warn           warn about improperly formatted checksum lines\n\n");
  printf("      --help     display this help and exit\n");
  printf("      --version  output version information and exit\n\n");
  printf("The sums are computed as described in FIPS-180-2.  When checking, the input\n");
  printf("should be a former output of this program.  The default mode is to print a\n");
  printf("line with checksum, a space, a character indicating input mode ('*' for binary,\n");
  printf("' ' for text or where binary is insignificant), and name for each FILE.\n\n");
  printf("There is no help or documentation for this tool - thanks :)");

  exit(EXIT_SUCCESS);
}

/**************************************************************************/
/*!
             verify_checksums 

  \brief     reads filenames and checksum information from a file and
             outputs data about it depening on the flags. 

  \param     *file_path
             char* points to the file path

  \param     flags 
             holds info about how to process the file

  \return    void 
*/
/**************************************************************************/
void verify_checksums(char *file_path, CFLAGS flags)
{
  FILE **pis = malloc(sizeof(FILE*));
  if( pis == NULL)
  {
    fprintf(stderr, "could not allocate memory for input stream\n");
    exit(EXIT_FAILURE);
  }

  /* open the file, go through each file and check them */
  *pis = fopen(file_path, "rt");
  /* unfinished business */
  printf("Not fully implemented\n");
  fclose(*pis);
  free(pis);
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
    if(is == NULL)
    {
      fprintf(stderr, "could not allocate memory for input stream\n");
      exit(EXIT_FAILURE);
    }
    if(flags&BINARY)
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
  char hash[65] = {};           /* the hash of the current file */
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
      {"tag",            no_argument, NULL,  0 },
      {"ignore-missing", no_argument, NULL,  0 },
      {"quiet",          no_argument, NULL,  0 },
      {"status",         no_argument, NULL,  0 },
      {"strict",         no_argument, NULL,  0 },
      {"warn",           no_argument, NULL, 'w' },
      {"help",           no_argument, NULL,  0 },
      {"version",        no_argument, NULL,  0 },
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
       flags |= (1 << option_index);
       if(flags&HELP)
         display_help();
       else if(flags&VERSION)
         display_version();
      break;
      case '?':
        printf("sha256sum: unknown option -- %c\n", optopt);
        printf("Try \"sha256sum --help\" for more information\n");
        exit(EXIT_SUCCESS);
      break;
    }
  }while(c != -1);

  if(!binaryIsSet && flags&TAG)
    flags |= BINARY;

  if(flags&TAG && !(flags&BINARY))
    display_tag_support();

  if(optind < argc)     /* checks optind to see if there are files to process */
  {
    /* there are files, default method is binary */
    if(binaryIsSet == false)
      flags |= BINARY;

    /* While there are files to run through - go through them all */
    while(optind < argc)
    {
      /* If the check option is selected, use files as list of files to check */
      if(flags&CHECK)
        verify_checksums(argv[optind++], flags);
      /* if the check option isn't selected, directly check each file */
      else
      {
        pis = check_valid_file(argv[optind], flags);
        if(pis != NULL)
        {
          process_file(pis, flags, hash);
          fclose(*pis);
          free(pis);
	  print_hash(argv[optind++], hash, flags);
        }
      }
    }
  }
  else
  {
    if(stdin) /* checks if stdin is valid */
    {
      if(flags&BINARY)
        freopen(NULL, "rb", stdin);
      process_file(&stdin, flags, hash);
    }
  }
  return 0;
}
