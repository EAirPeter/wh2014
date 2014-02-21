#include <cstdio>
#include <cstring>

using namespace std;

#ifdef NAVIO
#define LLD "%lld"
#else
#define LLD "%I64d"
#endif

const int MXN = 1004;
const int MDN = 1000000007;

struct et {
	int H[ MXN ], I[ MXN << 1 ], J[ MXN << 1 ], K[ MXN << 1 ];
	int C;
	inline void clear( const int n ) {
		memset( H, 0, sizeof( int ) * n );
		C = 1;
	}
	inline void adde( const int a, const int b, const bool k ) {
		I[ C ] = b;
		K[ C ] = k;
		J[ C ] = H[ a ];
		H[ a ] = C++;
	}
} A;

int C[ MXN ][ MXN ];
int F1[ MXN ][ MXN ], F2[ MXN ][ MXN ], P[ MXN ];
int N, M;
char sin[ 4 ];
int Z[ MXN ];

void dfs( const int c, const int p ) {
	Z[ c ] = 1;
	memset( F1[ c ], 0, sizeof( int ) * M );
	F1[ c ][ 0 ] = 1;
	for( int i = A.H[ c ]; i; i = A.J[ i ] )
		if( A.I[ i ] ^ p ) {
			int d = A.I[ i ];
			dfs( d, c );
			Z[ c ] += Z[ d ];
			memcpy( P, F1[ c ], sizeof( int ) * Z[ c ] );
			memset( F1[ c ], 0, sizeof( int ) * Z[ c ] );
			--Z[ c ];
			if( A.K[ i ] )
				for( register int j = 0; j < Z[ d ]; ++j )
					for( register int k = j + 1; k <= Z[ c ]; ++k )
						F1[ c ][ k ] = ( int ) ( ( F1[ c ][ k ] + ( long long ) P[ k - j - 1 ] * F1[ d ][ j ] % MDN * C[ k ][ j + 1 ] % MDN * C[ Z[ c ] - k ][ Z[ d ] - j - 1 ] ) % MDN );
			else
				for( register int j = 0; j < Z[ d ]; ++j )
					for( register int k = j; k <= Z[ c ]; ++k )
						F1[ c ][ k ] = ( int ) ( ( F1[ c ][ k ] + ( long long ) P[ k - j ] * F2[ d ][ j ] % MDN * C[ k ][ j ] % MDN * C[ Z[ c ] - k ][ Z[ d ] - j ] ) % MDN );
			++Z[ c ];
		}
	memcpy( F2[ c ], F1[ c ], sizeof( int ) * ( Z[ c ] + 1 ) );
	for( int i = 1; i <= Z[ c ]; ++i )
		F1[ c ][ i ] = ( F1[ c ][ i ] + F1[ c ][ i - 1 ] ) % MDN;
	for( int i = Z[ c ] - 1; i > -1; --i )
		F2[ c ][ i ] = ( F2[ c ][ i ] + F2[ c ][ i + 1 ] ) % MDN;
}

int G[ MXN ], S[ MXN ];
int T[ MXN ], U[ MXN ], rr, ss;

inline void bfs() {
	T[ 0 ] = 0;
	G[ 0 ] = -1;
	int qf, ql;
	for( qf = 0, ql = 1; qf < ql; ++qf ) {
		for( int i = A.H[ T[ qf ] ]; i; i = A.J[ i ] )
			if( A.I[ i ] ^ G[ T[ qf ] ] ) {
				G[ A.I[ i ] ] = T[ qf ];
				T[ ql++ ] = A.I[ i ];
			}
	}
	for( int i = ql - 1; i > -1; --i ) {
		S[ i ] = 1;
		for( int j = A.H[ T[ i ] ]; j; j = A.J[ j ] )
			if( A.I[ j ] ^ G[ T[ i ] ] )
				S[ i ] += S[ A.I[ j ] ];
	}
	rr = U[ 0 ] = S[ 0 ];
	ss = 0;
	for( int i = 0; i < ql; ++i ) {
		if( U[ i ] < rr ) {
			rr = U[ i ];
			ss = i;
		}
		for( int j = A.H[ T[ i ] ]; j; j = A.J[ j ] )
			if( A.I[ j ] ^ G[ T[ i ] ] )
				U[ A.I[ j ] ] = U[ i ] + N - ( S[ A.I[ j ] ] << 1 );
	}
}

inline void Main() {
	for( int a, b, i = N - 1; i; --i ) {
		scanf( "%d%s%d", &a, sin, &b );
			A.adde( a, b, sin[ 0 ] == '<' );
			A.adde( b, a, sin[ 0 ] == '>' );
	}
	//bfs();
	dfs( 1, -1 );
	printf( "%d\n", F1[ 1 ][ N ] );
}

int main() {
	freopen( "sao.in", "r", stdin );
	freopen( "sao.out", "w", stdout );
	for( int i = 0; i < MXN; ++i ) {
		C[ i ][ 0 ] = 1;
		for( int j = 1; j <= i; ++j )
			C[ i ][ j ] = ( C[ i - 1 ][ j - 1 ] + C[ i - 1 ][ j ] ) % MDN;
	}
	int Tn;
	scanf( "%d", &Tn );
	while( Tn-- ) {
		scanf( "%d", &N );
		M = N + 1;
		A.clear( N );
		memset( Z, 0, sizeof( int ) * M );
		Main();
	}
}

