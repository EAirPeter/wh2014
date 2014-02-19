#include <cstdio>

using namespace std;

int P, N, M;
int A[ 100001 ], B[ 100001 ];
int F[ 100001 ];

void fc( int x, int v ) {
	while( x <= N ) {
		F[ x ] += v;
		x += x & -x;
	}
}

int fq( int x ) {
	int v = 0;
	while( x ) {
		v += F[ x ];
		x -= x & -x;
	}
	return v;
}

int main() {
	freopen( "aplusb.in", "r", stdin );
	freopen( "aplusb.out", "w", stdout );
	scanf( "%d%d", &P, &N );
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
			if( A[ a - 1 ] + B[ a - 1 ] != P - 1 ) {
				if( A[ a - 1 ] + B[ a - 1 ] < P )
					printf( "%d\n", ( A[ a ] + B[ a ] ) % P );
				else
					printf( "%d\n", ( A[ a ] + B[ a ] + 1 ) % P );
				continue;
			}
			int l = 1, r = a - 1;
			int m = fq( r );
			while( l < r ) {
				int t = ( l + r ) >> 1;
				int n = fq( t - 1 );
				if( m - n == a - t )
					r = t;
				else
					l = t + 1;
			}
			if( A[ l - 1 ] + B[ l - 1 ] < P )
				printf( "%d\n", ( A[ a ] + B[ a ] ) % P );
			else
				printf( "%d\n", ( A[ a ] + B[ a ] + 1 ) % P );
		}
	}
	return 0;
}

