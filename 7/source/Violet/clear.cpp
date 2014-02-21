#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

int N1, N2, N3, N, P, Q;
bool W[ 20 ], V[ 20 ];
int X[ 20 ][ 5000 ], Y[ 20 ][ 5000 ], C[ 20 ];
int H[ 20 ], I[ 1000 ], J[ 1000 ], K[ 20 ][ 20 ], L, R[ 20 ];

inline void addp( const int c, const int x, const int y ) {
	X[ c ][ C[ c ] ] = x;
	Y[ c ][ C[ c ] ] = y;
	++C[ c ];
}

inline void adde( const int a, const int b ) {
	I[ L ] = b;
	J[ L ] = H[ a ];
	H[ a ] = L++;
}

bool dfh( const int c ) {
	for( int i = H[ c ]; i; i = J[ i ] )
		if( !V[ I[ i ] ] ) {
			V[ I[ i ] ] = true;
			if( R[ I[ i ] ] == -1 || dfh( R[ I[ i ] ] ) ) {
				R[ I[ i ] ] = c;
				return true;
			}
		}
	return false;
}

inline int bip() {
	memset( H, 0, sizeof( H ) );
	memset( K, false, sizeof( K ) );
	L = 1;
	for( int i = 0; i < N; ++i )
		if( !W[ i ] )
			for( int j = 0; j < C[ i ]; ++j )
				if( !K[ X[ i ][ j ] ][ Y[ i ][ j ] ] ) {
					K[ X[ i ][ j ] ][ Y[ i ][ j ] ] = true;
					adde( X[ i ][ j ], Y[ i ][ j ] );
				}
	int r = 0;
	memset( R, -1, sizeof( R ) );
	for( int i = 0; i < P; ++i ) {
		memset( V, false, sizeof( V ) );
		if( dfh( i ) )
			++r;
	}
	return r;
}

int dfs( const int c, const int d ) {
	if( c == N )
		return bip() + d;
	int x = dfs( c + 1, d );
	W[ c ] = true;
	x = min( x, dfs( c + 1, d + 1 ) );
	W[ c ] = false;
	return x;
}

void Main() {
	scanf( "%d%d%d", &N1, &N2, &N3 );
	N = min( N1, min( N2, N3 ) );
	if( N == N1 ) {
		P = N2;
		Q = N3;
	}
	else if( N == N2 ) {
		P = N1;
		Q = N3;
	}
	else {
		P = N1;
		Q = N2;
	}
	for( int x, i = 0; i < N1; ++i )
		for( int j = 0; j < N2; ++j )
			for( int k = 0; k < N3; ++k ) {
				scanf( "%d", &x );
				if( x ) {
					if( N == N1 )
						addp( i, j, k );
					else if( N == N2 )
						addp( j, i, k );
					else
						addp( k, i, j );
				}
			}
	printf( "%d\n", dfs( 0, 0 ) );
}

int main() {
	freopen( "clear.in", "r", stdin );
	freopen( "clear.out", "w", stdout );
	int Tn;
	scanf( "%d", &Tn );
	while( Tn-- ) {
		memset( C, 0, sizeof( C ) );
		Main();
	}
}
