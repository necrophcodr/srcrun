#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

// magic number for reading. ought to be something smarter.
const READ_SIZE = 4096;

void
print_file_size( FILE *fd, size_t size, size_t bytes, char *buf ) {
	size_t cur = ftell( fd );
	size_t read_bytes = (size - cur) > bytes ? bytes : (size - cur) ;
	if(read_bytes <= 1) { return; }
	fread( buf, sizeof buf[0], read_bytes-1, fd );
	buf[read_bytes] = '\0'; // ensure null termination.
	printf( "%s", buf );
	return print_file_size( fd, size, read_bytes, buf );
}

int
main( int argc, char **argv ) {
	if( argc == 1 ) {
		printf( "%s: [file]\n", argv[0] );
		return EXIT_SUCCESS;
	}
	char *buf = malloc( READ_SIZE );
	for( int files = 1; files < argc; files++ ) {
		FILE *file = fopen( argv[files], "r" );
		int seek = fseek( file, 0, SEEK_END );
		size_t size = ftell( file );
		fseek( file, 0, SEEK_SET );
		if( seek != 0 ) {
			perror( argv[0] );
			return EXIT_FAILURE;
		}
		print_file_size( file, size, READ_SIZE, buf );
		fclose( file );
		fflush( stdout );
	}
	free(buf);
	return EXIT_SUCCESS;
}
