#include <algorithm>
#include <cstdio>
#include <functional>

using namespace std;

int N, M, LA, LB;
int FA[ 10001 ], A[ 10001 ], B[ 10001 ];

void Main() {
	scanf( "%d%d%d%d", &N, &M, &LA, &LB );
	for( int i = 1; i <= LA; ++i )
		scanf( "%d", A + i );
	for( int i = 1; i <= LB; ++i )
		scanf( "%d", B + i );
	sort( A + 1, A + LA + 1, greater< int >() );
	sort( B + 1, B + LB + 1, greater< int >() );
	for( int i = 1; i <= LA; ++i )
		FA[ i ] = FA[ i - 1 ] + A[ i ];
	int s = 0, x = 0;
	int k = N * M;
	if( N % 3 == 2 && M % 3 == 2 && ( N == 2 || M == 2 ) )
		k -= 3;
	for( int i = 0; i <= LB && i * 3 <= k; ++i ) {
		s += B[ i ];
		int t = ( N * M - i * 3 ) >> 1;
		if( t > LA )
			t = LA;
		if( s + FA[ t ] > x )
			x = s + FA[ t ];
	}
	printf( "%d\n", x );
}

int main() {
	freopen( "trail.in", "r", stdin );
	freopen( "trail.out", "w", stdout );
	int T;
	scanf( "%d", &T );
	while( T-- )
		Main();
	return 0;
}

