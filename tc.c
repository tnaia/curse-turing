/*
  Copyright Tássio Naia dos Santos 2013.

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <stdio.h>
#include <stdlib.h>

#define MAX_STATES 1000
#define MAX_TRANSITIONS 1000
#define MAX_TAPE 1000
#define LEFT -1
#define RIGHT 1

int main( int argc, char **argv ) {
  FILE *file = NULL;
  int c, current_state = 0, current_position = 0, transition = 0, i, tape_size;
  char c1[ MAX_TRANSITIONS ], s1[ MAX_TRANSITIONS ], c2[ MAX_TRANSITIONS ], s2[ MAX_TRANSITIONS ], dir[ MAX_TRANSITIONS ], tape[ MAX_TAPE ];
  if( argc != 3 ) {
    fprintf( stderr,
             " Usage: %s file tape\n"
             " where  file is the file with machine description,\n"
             " and    tape is the input.\n\n"
             " file format c1,s1,c2,s2,direction\n"
             " where\n"
             "      c1 is the character read\n"
             "      s1 is the current state\n"
             "      c2 is the character to write\n"
             "      s2 is the next state\n"
             "      d  is the direction, R (right) or L (left).\n"
             " The tape is infinite to the right (only), filled with blanks.\n"
             " The machine starts at state 0 halts when tries to go to the left.\n"
             " States can be numbers smaller than %d, no checking is done.\n",
             argv[ 0 ], MAX_STATES );
    exit( 1 );
  }

  /*  Can we open the file?  ------------------------------*/
  if( (file = fopen( argv[ 1 ], "r") ) == NULL) {
    fprintf( stderr, "Couldn't open file: %s\n", argv[ 1 ] );
    exit( 1 );
  }

  /* Read the machine */
  printf( "[ Reading the machine... ]\n" );
  c = fgetc( file );
  while( c != EOF ) {
    if( c == EOF ) break;
    c1[ transition ] = c;
    fgetc( file );
    s1[ transition ] = fgetc( file ) - '0';
    while( ( c = fgetc( file ) ) != ',' )
      s1[ transition ] = s1[ transition ] * 10 + c - '0';
    c2[ transition ] = fgetc( file );
    fgetc( file );
    s2[ transition ] = fgetc( file ) - '0';
    while( ( c = fgetc( file ) ) != ',' )
      s2[ transition ] = s2[ transition ] * 10 + c - '0';
    if( ( c = fgetc( file ) ) == 'L' ) {
      dir[ transition ] = LEFT;
    } else {
      dir[ transition ] = RIGHT;
    }
    printf( " got transition %d:  (%c,%d) --> (%c,%d,%c)\n",
            transition,
            c1[ transition ],
            s1[ transition ],
            c2[ transition ],
            s2[ transition ],
            dir[ transition ] == LEFT ? 'L' : 'R' );
    while( ( c = fgetc( file ) ) != '\n' && c != EOF );
    while( c == '\n' && c != EOF ) c = fgetc( file );
    ++transition;
  }
  printf( "[ Done reading machine ]\n" );

  fclose( file );

  /* Initiate tape */
  tape_size = 0;
  while( argv[ 2 ][ tape_size ] != '\0' ) {
    tape[ tape_size ] = argv[ 2 ][ tape_size ];
    ++tape_size;
  }
  tape[ tape_size ] = '\0';
/*   printf ("Tape (original): %s\n" */
/*           "Tape     (copy): %s\n" */
/*           "Tape       size: %d\n", */
/*           argv[ 2 ], tape, tape_size ); */

  /* Simulate */
  printf( "[ Simulating machine on tape ]\n" );

  while( 1 ) {
    /* Print state */
    printf( "tape: " ); fflush( stdout );
    for( i = 0; i < tape_size; ++i )
      printf( "%c", tape[ i ] );
    printf( "\n" );
    printf( "s%3d ", current_state ); fflush( stdout );
    for( i = -1; i < current_position; ++i )
      printf( " " );
    printf( "^\n" );
    if( current_position == -1 ) break;

    /* Find transition and make it */
    for( i = 0; i < MAX_TRANSITIONS; ++i ) {
      if( ( tape[ current_position ] == c1[ i ]
            || ( current_position == tape_size && c1[ i ] == ' ' ) )
          && current_state == s1[ i ] ) {
/*         printf( "next transition %d:  (%c,%d) --> (%c,%d,%c)\n",  */
/*             i, */
/*             c1[ i ], */
/*             s1[ i ], */
/*             c2[ i ], */
/*             s2[ i ], */
/*             dir[ i ] == LEFT ? 'L' : 'R' ); */

        if ( current_position == tape_size ) ++tape_size;
        tape[ current_position ] = c2[ i ];
        current_position += dir[ i ];
        current_state = s2[ i ];
        break;
      }
    }
    if( i == MAX_TRANSITIONS ) {
      fprintf( stderr, "No transition for current state and tape symbol! Aborting.\n" );
      exit( 1 );
    }
  }

  printf( "[ Machine halted ]\n" );
  return 0;
}
