#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>

using namespace std;

struct sts {
	void rea() {
		sort( v, v + v[ 11 ] + 1, greater< int >() );
	}
	int v[ 12 ];
} D;

bool operator < ( const sts & a, const sts & b ) {
	return memcmp( a.v, b.v, sizeof( sts::v ) ) < 0;
}

typedef map< sts, int > mpt;
typedef mpt::iterator mpi;

const int MDN = 1000000007;
int X, N;

mpt M;

int dfs( sts d );
int dfsx( const int c, sts d ) {
	if( c == d.v[ 11 ] ) {
		--d.v[ 11 ];
		return dfs( d );
	}
	int x = 0;
	d.v[ 0 ] -= 3;
	if( d.v[ 0 ] > -1 && d.v[ 0 ] <= ( d.v[ 11 ] - c - 1 ) * 3 && d.v[ c ] > -1 && d.v[ c ] <= ( d.v[ 11 ] - 2 ) * 3 )
		x = ( x + dfsx( c + 1, d ) ) % MDN;
	d.v[ 0 ] += 2;
	--d.v[ c ];
	if( d.v[ 0 ] > -1 && d.v[ 0 ] <= ( d.v[ 11 ] - c - 1 ) * 3 && d.v[ c ] > -1 && d.v[ c ] <= ( d.v[ 11 ] - 2 ) * 3 )
		x = ( x + dfsx( c + 1, d ) ) % MDN;
	++d.v[ 0 ];
	d.v[ c ] -= 2;
	if( d.v[ 0 ] > -1 && d.v[ 0 ] <= ( d.v[ 11 ] - c - 1 ) * 3 && d.v[ c ] > -1 && d.v[ c ] <= ( d.v[ 11 ] - 2 ) * 3 )
		x = ( x + dfsx( c + 1, d ) ) % MDN;
	d.v[ c ] += 3;
	return x;
}

int dfs( sts d ) {
	if( !d.v[ 11 ] )
		return 1;
	d.rea();
	mpi t = M.find( d );
	if( t != M.end() )
		return t->second;
	return M[ d ] = dfsx( 1, d );
}

int main() {
	freopen( "match.in", "r", stdin );
	freopen( "match.out", "w", stdout );
	scanf( "%d", &N );
	for( int i = 0; i < N; ++i )
		scanf( "%d", D.v + i );
	D.v[ 11 ] = N;
	printf( "%d\n", dfs( D ) );
	return 0;
}

