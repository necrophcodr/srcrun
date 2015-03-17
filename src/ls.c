#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>

int main( int argc, char ** argv ) {
	if( argc == 1 ) {
		printf( "%s: [directory]\n", argv[0] );
		return EXIT_SUCCESS;
	}
	DIR *dp;
	struct dirent *de;

	dp = opendir( argv[1] );
	if( !dp ) {
		perror( argv[0] );
		return EXIT_FAILURE;
	}
	while( ( de = readdir( dp ) ) ) {
		printf( "%s\n", de->d_name );
	}
	closedir( dp );
	return EXIT_SUCCESS;
}
