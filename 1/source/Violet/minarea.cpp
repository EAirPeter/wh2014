#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>

using namespace std;

struct pnt {
	pnt() : x(), y() {
	}
	pnt( const double a, const double b ) : x( a ), y( b ) {
	}
	pnt & operator *= ( const double f ) {
		x *= f;
		y *= f;
		return *this;
	}
	double x, y;
} D[ 50 ];

int N, C;
bool V[ 50 ];
int S[ 50 ], p;
double X = 1e12;

bool operator < ( const pnt & a, const pnt & b ) {
	if( a.x != b.x )
		return a.x < b.x;
	return a.y < b.y;
}

pnt operator + ( pnt a, const pnt & b ) {
	a.x += b.x;
	a.y += b.y;
	return a;
}

pnt operator - ( pnt a, const pnt & b ) {
	a.x -= b.x;
	a.y -= b.y;
	return a;
}

double operator * ( const pnt & a, const pnt  & b ) {
	return a.x * b.y - b.x * a.y;
}

inline double cx( const pnt & a, const pnt & b, const pnt & c ) {
	return ( b - a ) * ( c - a );
}

inline double cx( const int a, const int b, const int c ) {
	return cx( D[ a ], D[ b ], D[ c ] );
}

double f1( const int a, const int b ) {
	memset( V, false, sizeof( V ) );
	int i;
	for( i = 0; i < N && cx( a, b, i ) < 0; ++i );
	V[ S[ ( p = 0 )++ ] = i ] = true;
	for( ++i; i < N; ++i )
		if( cx( a, b, i ) >= 0 ) {
			while( p > 1 ) {
				if( cx( S[ p - 2 ], S[ p - 1 ], i ) > 0)
					break;
				else
					V[ S[ --p ] ] = false;
			}
			V[ S[ p++ ] = i ] = true;
		}
	V[ S[ 0 ] ] = false;
	int k = p;
	for( int i = N - 1; i > -1; --i )
		if( cx( a, b, i ) >= 0 && !V[ i ] ) {
			while( p > k ) {
				if( cx( S[ p - 2 ], S[ p - 1 ], i ) > 0 )
					break;
				else
					V[ S[ --p ] ] = false;
			}
			V[ S[ p++ ] = i ] = true;
		}
	--p;
	double s = 0;
	for( int i = 2; i < p; ++i )
		s += cx( S[ 0 ], S[ i - 1 ], S[ i ] );
	return fabs( s ) / 2;
}

double f2( const int a, const int b ) {
	memset( V, false, sizeof( V ) );
	int i;
	for( i = 0; i < N && cx( a, b, i ) >= 0; ++i );
	V[ S[ ( p = 0 )++ ] = i ] = true;
	for( ++i; i < N; ++i )
		if( cx( a, b, i ) < 0 ) {
			while( p > 1 ) {
				if( cx( S[ p - 2 ], S[ p - 1 ], i ) > 0)
					break;
				else
					V[ S[ --p ] ] = false;
			}
			V[ S[ p++ ] = i ] = true;
		}
	V[ S[ 0 ] ] = false;
	int k = p;
	for( int i = N - 1; i > -1; --i )
		if( cx( a, b, i ) < 0 && !V[ i ] ) {
			while( p > k ) {
				if( cx( S[ p - 2 ], S[ p - 1 ], i ) > 0 )
					break;
				else
					V[ S[ --p ] ] = false;
			}
			V[ S[ p++ ] = i ] = true;
		}
	--p;
	double s = 0;
	for( int i = 2; i < p; ++i )
		s += cx( S[ 0 ], S[ i - 1 ], S[ i ] );
	return fabs( s ) / 2;
}

int main() {
	freopen( "minarea.in", "r", stdin );
	freopen( "minarea.out", "w", stdout );
	scanf( "%d", &N );
	for( int i = 0; i < N; ++i )
		scanf( "%lf%lf", &D[ i ].x, &D[ i ].y );
	sort( D, D + N );
	for( int i = 0; i < N; ++i )
		for( int j = 0; j < N; ++j )
			if( i ^ j ){
				double y = max( f1( i, j ), f2( i, j ) );
				X = min( X, y );
			}
	printf( "%.6lf\n", X );
	return 0;
}

