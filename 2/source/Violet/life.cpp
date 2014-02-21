#include <cstdio>
#include <cstring>

using namespace std;

#ifdef NAVIO
#define LLD "%lld"
#else
#define LLD "%I64d"
#endif

const long long MDN = 1000000009LL;
const int MXP = 1 << 16;

int K, M, T, N;
int B[ 300000 ];
int F[ MXP ][ 30 ], G[ MXP ];
int E[ 20 ][ 30 ][ 30 ];
long long H[ 20 ][ 30 ][ 30 ];

inline int gv( const int x, const int y ) {
	if( x < 0 || y < 0 || x > 3 || y > 3 )
		return 0;
	return 1 << ( ( x << 2 ) + y );
}

inline int gb( const int x, const int y, const int c ) {
	return ( gv( x, y ) & c ) != 0;
}

inline int tran( const int c ) {
	int d = 0;
	for( int i = 0; i < 4; ++i )
		for( int j = 0; j < 4; ++j ) {
			int u = gv( i, j );
			int t = 
				gb( i - 1, j - 1, c )	+ gb( i - 1, j, c )	+ gb( i - 1, j + 1, c ) +
				gb( i, j - 1, c )							+ gb( i, j + 1, c ) +
				gb( i + 1, j - 1, c )	+ gb( i + 1, j, c )	+ gb( i + 1, j + 1, c );
			if( t == 2 )
				d ^= u & c;
			else if( t == 3 )
				d ^= u;
		}
	return d;
}

inline int nart( int v ) {
	for( int x, i = T; i; i ^= x ) {
		x = i & -i;
		v = F[ v ][ B[ x ] ];
	}
	return v;
}

void dfs( const int d, int ( * e )[ 30 ], const int f, const int c ) {
	if( c == MXP ) {
		++e[ f ][ G[ nart( d ) ] ];
		return;
	}
	dfs( d, e, f, c << 1 );
	if( !( d & c ) )
		dfs( d | c, e, f + 1, c << 1 );
}

int main() {
	freopen( "life.in", "r", stdin );
	freopen( "life.out", "w", stdout );
	scanf( "%d%d%d%d", &K, &M, &T, &N );
	for( int i = 0, j = 1; j <= T; ++i, j <<= 1 )
		B[ j ] = i;
	for( int i = 0; i < MXP; ++i )
		F[ i ][ 0 ] = tran( i );
	for( int i = 1, j = 2; j <= T; ++i, j <<= 1 )
		for( int k = 0; k < MXP; ++k )
			F[ k ][ i ] = F[ F[ k ][ i - 1 ] ][ i - 1 ];
	for( int i = 0; i < MXP; ++i )
		for( int x, y = i; y; y ^= x, ++G[ i ] ) x = y & -y;
	for( int x, d, i = 0; i < K; ++i ) {
		d = 0;
		for( int a = 0; a < 4; ++a )
			for( int b = 0; b < 4; ++b ) {
				scanf( "%d", &x );
				if( x )
					d ^= gv( a, b );
			}
		dfs( d, E[ i ], 0, 1 );
	}
	H[ 0 ][ 0 ][ 0 ] = 1;
	long long x = 0;
	for( int i = 1; i <= K; ++i )
		for( int j = 0; j <= M; ++j )
			for( int k = 0; k <= N; ++k )
				for( int l = 0; l <= j; ++l )
					for( int m = 0; m <= k; ++m )
						H[ i ][ j ][ k ] = ( H[ i ][ j ][ k ] + H[ i - 1 ][ j - l ][ k - m ] * E[ i - 1 ][ l ][ m ] ) % MDN;
	for( int i = 0; i <= M; ++i )
		x += H[ K ][ i ][ N ];
	printf( LLD "\n", x % MDN );
	return 0;
}

