#include <cstdio>
#include <cstring>

using namespace std;

const int MXN = 1001;
const long long MDN = 1000000007LL;

struct et {
	int H[ MXN ], I[ MXN << 1 ], J[ MXN << 1 ];
	int C;
	void clear() {
		memset( H, 0, sizeof( H ) );
		C = 1;
	}
	void adde( const int a, const int b ) {
		I[ C ] = b;
		J[ C ] = H[ a ];
		H[ a ] = C++;
	}
} A1, B1, A2, B2;

long long C[ MXN ][ MXN ];
long long F1[ MXN ][ MXN ], F2[ MXN ][ MXN ], P[ MXN ];
bool V[ MXN ];
int N;
char sin[ 4 ];
int Z[ MXN ];

void dfs( const int c ) {
	Z[ c ] = 1;
	V[ c ] = true;
	memset( F1[ c ], 0, sizeof( F1[ c ] ) );
	for( int i = A1.H[ c ]; i; i = A1.J[ i ] )
		if( !V[ A1.I[ i ] ] ) {
			dfs( A1.I[ i ] );
			Z[ c ] += Z[ A1.I[ i ] ];
			A2.adde( c, A1.I[ i ] );
		}
	for( int i = B1.H[ c ]; i; i = B1.J[ i ] )
		if( !V[ B1.I[ i ] ] ) {
			dfs( B1.I[ i ] );
			Z[ c ] += Z[ B1.I[ i ] ];
			B2.adde( c, B1.I[ i ] );
		}
	F1[ c ][ 0 ] = 1;
	int d = 0;
	for( int i = A2.H[ c ]; i; i = A2.J[ i ] ) {
		for( int j = 0; j < Z[ c ]; ++j ) {
			P[ j ] = F1[ c ][ j ];
			F1[ c ][ j ] = 0;
		}
		d += Z[ A2.I[ i ] ];
		for( int j = 0; j < Z[ A2.I[ i ] ]; ++j )
			for( int k = j + 1; k <= d; ++k )
				F1[ c ][ k ] = ( F1[ c ][ k ] + P[ k - j - 1 ] * F1[ A2.I[ i ] ][ j ] % MDN * C[ k ][ j + 1 ] % MDN * C[ d - k ][ Z[ A2.I[ i ] ] - j - 1 ] ) % MDN;
	}
	for( int i = B2.H[ c ]; i; i = B2.J[ i ] ) {
		for( int j = 0; j < Z[ c ]; ++j ) {
			P[ j ] = F1[ c ][ j ];
			F1[ c ][ j ] = 0;
		}
		d += Z[ B2.I[ i ] ];
		for( int j = 0; j < Z[ B2.I[ i ] ]; ++j )
			for( int k = j; k <= d; ++k )
				F1[ c ][ k ] = ( F1[ c ][ k ] + P[ k - j ] * F2[ B2.I[ i ] ][ j ] % MDN * C[ k ][ j ] % MDN * C[ d - k ][ Z[ B2.I[ i ] ] - j ] ) % MDN;
	}
	for( int i = 0; i <= Z[ c ]; ++i )
		F2[ c ][ i ] = F1[ c ][ i ];
	for( int i = 1; i <= Z[ c ]; ++i )
		F1[ c ][ i ] = ( F1[ c ][ i ] + F1[ c ][ i - 1 ] ) % MDN;
	for( int i = Z[ c ] - 1; i > -1; --i )
		F2[ c ][ i ] = ( F2[ c ][ i ] + F2[ c ][ i + 1 ] ) % MDN;
}

inline void Main() {
	scanf( "%d", &N );
	for( int a, b, i = N - 1; i; --i ) {
		scanf( "%d%s%d", &a, sin, &b );
		if( sin[ 0 ] == '<' ) {
			A1.adde( a, b );
			B1.adde( b, a );
		}
		else {
			A1.adde( b, a );
			B1.adde( a, b );
		}
	}
	dfs( 0 );
	printf( "%lld\n", F1[ 0 ][ N ] );
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
		A1.clear();
		B1.clear();
		A2.clear();
		B2.clear();
		memset( V, false, sizeof( V ) );
		memset( Z, 0, sizeof( Z ) );
		Main();
	}
}

