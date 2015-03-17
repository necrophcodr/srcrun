#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

int
main( int argc, char **argv ) {
	if( argc == 1 ) {
		printf( "%s: [file]\n", argv[0] );
		return EXIT_SUCCESS;
	}
	int file = open( argv[1], 'r' );
	size_t size = lseek( file, 0, SEEK_END );
	lseek( file, 0, SEEK_SET );
	if( size == -1 ) {
		perror( argv[0] );
		return EXIT_FAILURE;
	}
	char *contents = malloc( size );
	read( file, contents, size );
	close( file );
	printf( "%s\n", contents );
	fflush( stdout );
	return EXIT_SUCCESS;
}
