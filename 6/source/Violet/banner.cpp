#include <algorithm>
#include <cstdio>

using namespace std;

#ifdef NAVIO
#define LLD "%lld"
#else
#define LLD "%I64d"
#endif

int D[ 100001 ][ 6 ];
int E[ 100001 ];

long long M, N, L, H, B, X;

long long sum( long long a, long long b, long long c ) {
	b = b / c;
	a = ( a + c - 1 ) / c;
	return ( ( b - a + 1 ) * ( M + 1 ) - c * ( ( b * ( b + 1 ) - ( a - 1 ) * a ) / 2 ) ) % B;
}

int main(  ) {
	freopen( "banner.in", "r", stdin );
	freopen( "banner.out", "w", stdout );
	scanf( LLD LLD LLD LLD LLD, &M, &N, &L, &H, &B );
	for( int i = 2; i <= N; i++ )
		if( E[ i ] == 0 )
			for( int j = i; j <= N; j += i )
				D[ j ][ E[ j ]++ ] = i;
	long long l = L, h = H;
	long long mh = min( N, H );
	for( long long i = 1; i <= mh; ++i ) {
		while( l > 1 && L * L - i * i <= ( l - 1 ) * ( l - 1 ) )
			--l;
		while( H * H - i * i < h * h )
			--h;
		if( l <= h && l <= M ) {
			long long x = 0;
			int p = 1 << E[ i ];
			for( int j = 0; j < p; ++j ) {
				int t = j;
				long long prod = 1;
				int parity = 1;
				for( int k = 0; k < E[ i ]; ++k ) {
					if( t & 1 ) {
						prod *= D[ i ][ k ];
						parity *= -1;
					}
					t >>= 1;
				}
				x += parity * sum( l, min( h, M ), prod );
			}
			X = ( X + x * ( N - i + 1 ) ) % B;
			if( X < 0 ) X += B;
		}
	}
	if( L <= 1 && 1 <= H )
		X = ( X * 2 + N * ( M + 1 ) + M * ( N + 1 ) ) % B;
	else
		X = ( X * 2 ) % B;
	printf( LLD "\n", X );
}

