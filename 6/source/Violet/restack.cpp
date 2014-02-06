#include <algorithm>
#include <cstdio>
#include <cstdlib>

using namespace std;

int N;
long long A[ 100000 ], B[ 100000 ], C[ 100000 ];

int main() {
	freopen( "restack.in", "r", stdin );
	freopen( "restack.out", "w", stdout );
	scanf( "%d", &N );
	for( int i = 0; i < N; ++i )
		scanf( "%lld%lld", A + i, B + i ); 
	for( int i = 1; i < N; ++i )
		C[ i ] = B[ i ] - A[ i ] + C[ i - 1 ];
	sort( C, C + N );
	long long d = 0, c = C[ N >> 1 ];
	for( int i = 0; i < N; ++i )
		d += abs( C[ i ] - c );
	printf( "%lld\n", d );
	return 0;
}

