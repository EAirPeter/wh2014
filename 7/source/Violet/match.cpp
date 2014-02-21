#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>

using namespace std;

inline void sort( int * A, const int L ) {
	for( int i = 1; i < L; ++i ) {
		for( int j = i - 1; j < L - 1; ++j )
			if( A[ j ] < A[ i ] )
				swap( A[ j ], A[ i ] );
	}
}

struct sts {
	inline void rea() {
		int c;
		if( v[ 10 ] < 10 )
			c = v[ 10 ] + 1;
		else
			c = v[ 10 ];
		for( int i = 0; i < c; ++i )
			for( int j = c - 1; j > i; --j )
				if( v[ j - 1 ] < v[ j ] )
					swap( v[ j - 1 ], v[ j ] );
	}
	inline long long hash() const {
		long long r = 0;
		for( int i = 0; i < 11; ++i )
			r = r * 40 + v[ i ];
		return r;
	}
	int v[ 11 ];
} D;

typedef map< long long, int > mpt;
typedef mpt::iterator mpi;

const int MDN = 1000000007;
int X, N;

mpt M;

int dfs( sts d );
int dfsx( const int c, sts d ) {
	if( c == d.v[ 10 ] ) {
		--d.v[ 10 ];
		return dfs( d );
	}
	int x = 0;
	d.v[ 0 ] -= 3;
	if( d.v[ 0 ] > -1 && d.v[ 0 ] <= ( d.v[ 10 ] - c - 1 ) * 3 && d.v[ c ] > -1 && d.v[ c ] <= ( d.v[ 10 ] - 2 ) * 3 )
		x = ( x + dfsx( c + 1, d ) ) % MDN;
	d.v[ 0 ] += 2;
	--d.v[ c ];
	if( d.v[ 0 ] > -1 && d.v[ 0 ] <= ( d.v[ 10 ] - c - 1 ) * 3 && d.v[ c ] > -1 && d.v[ c ] <= ( d.v[ 10 ] - 2 ) * 3 )
		x = ( x + dfsx( c + 1, d ) ) % MDN;
	++d.v[ 0 ];
	d.v[ c ] -= 2;
	if( d.v[ 0 ] > -1 && d.v[ 0 ] <= ( d.v[ 10 ] - c - 1 ) * 3 && d.v[ c ] > -1 && d.v[ c ] <= ( d.v[ 10 ] - 2 ) * 3 )
		x = ( x + dfsx( c + 1, d ) ) % MDN;
	d.v[ c ] += 3;
	return x;
}

int dfs( sts d ) {
	if( !d.v[ 10 ] )
		return 1;
	d.rea();
	long long x = d.hash();
	mpi t = M.find( x );
	if( t != M.end() )
		return t->second;
	return M[ x ] = dfsx( 1, d );
}

int main() {
	freopen( "match.in", "r", stdin );
	freopen( "match.out", "w", stdout );
	scanf( "%d", &N );
	for( int i = 0; i < N; ++i )
		scanf( "%d", D.v + i );
	D.v[ 10 ] = N;
	printf( "%d\n", dfs( D ) );
	return 0;
}

