#include <cstdio>

using namespace std;

int N;
int D[ 50000 ], L[ 50000 ], R[ 50000 ];

int main() {
	freopen( "alo.in", "r", stdin );
	freopen( "alo.out", "w", stdout );
	scanf( "%d", &N );
	for( int i = 0; i < N; ++i )
		scanf( "%d", D + i );
	for( int i = 0; i < N; ++i ) {
		int j;
		for( j = i - 1; j > -1 && D[ j ] < D[ i ]; --j );
		if( j == -1 )
			L[ i ] = i + 1;
		else {
			for( --j; j > -1 && D[ j ] < D[ i ]; --j );
			L[ i ] = j + 1;
		}
	}
	for( int i = 0; i < N; ++i ) {
		int j;
		for( j = i + 1; j < N && D[ j ] < D[ i ]; ++j );
		if( j == N )
			R[ i ] = i;
		else {
			for( ++j; j < N && D[ j ] < D[ i ]; ++j );
			R[ i ] = j;
		}
	}
	int x = 0;
	for( int i = 0; i < N; ++i )
		for( int j = L[ i ]; j < R[ i ]; ++j )
			if( ( D[ i ] ^ D[ j ] ) > x )
				x = D[ i ] ^ D[ j ];
	printf( "%d\n", x );
	return 0;
}

