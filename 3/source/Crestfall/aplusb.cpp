#include <cstdio>

using namespace std;

int P, N, M, S;
int A[ 100001 ], B[ 100001 ];
int F[ 400001 ];

void fc( int x, const int v ) {
	for( x += S; x; x >>= 1 )
		F[ x ] += v;
}

int fq( int x ) {
	x += S;
	int v = 1;
	while( v ) {
		if( v == F[ x ] ) {
			x >>= 1;
			v <<= 1;
		}
		else {
			x <<= 1;
			v >>= 1;
			if( F[ x + 1 ] ^ v )
				++x;
		}
	}
	return ( x >> 1 ) - S;
}

int main() {
	freopen( "aplusb.in", "r", stdin );
	freopen( "aplusb.out", "w", stdout );
	scanf( "%d%d", &P, &N );
	for( S = 1; S <= N; S <<= 1 );
	S = ( S >> 1 ) - 1;
	for( int i = N; i; --i )
		scanf( "%d", A + i );
	for( int i = N; i; --i )
		scanf( "%d", B + i );
	for( int i = 1; i <= N; ++i )
		if( A[ i ] + B[ i ] == P - 1 )
			fc( i, 1 );
	scanf( "%d", &M );
	char s[ 4 ];
	int a, b;
	while( M-- ) {
		scanf( "%s", s );
		if( s[ 0 ] == 'C' ) {
			scanf( "%s%d%d", s, &a, &b );
			++a;
			if( A[ a ] + B[ a ] == P - 1 )
				fc( a, -1 );
			if( s[ 0 ] == 'A' )
				A[ a ] = b;
			else
				B[ a ] = b;
			if( A[ a ] + B[ a ] == P - 1 )
				fc( a, 1 );
		}
		else {
			scanf( "%d", &a );
			++a;
			if( a == 1 ) {
				printf( "%d\n", ( A[ a ] + B[ a ] ) % P );
				continue;
			}
			/*if( A[ a - 1 ] + B[ a - 1 ] != P - 1 ) {
				if( A[ a - 1 ] + B[ a - 1 ] < P )
					printf( "%d\n", ( A[ a ] + B[ a ] ) % P );
				else
					printf( "%d\n", ( A[ a ] + B[ a ] + 1 ) % P );
				continue;
			}*/
			int l = fq( a - 1 );
			if( A[ l ] + B[ l ] < P )
				printf( "%d\n", ( A[ a ] + B[ a ] ) % P );
			else
				printf( "%d\n", ( A[ a ] + B[ a ] + 1 ) % P );
		}
	}
	return 0;
}

