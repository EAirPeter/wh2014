#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

class hint {
	friend ostream & operator << ( ostream & os, const hint & hp );
public:
	hint( const long long pv = 0 ) {
		memset( v, 0, sizeof( v ) );
		v[ ( c = 0 )++ ] = pv;
	}
	hint & operator += ( const hint & p ) {
		c = max( c, p.c );
		long long t = 0;
		for( int i = 0; i < c; ++i ) {
			v[ i ] += t + p.v[ i ];
			t = v[ i ] / s;
			v[ i ] %= s;
		}
		if( t )
			v[ c++ ] = t;
		return *this;
	}
	hint & operator *= ( const long long p ) {
		long long t = 0;
		for( int i = 0; i < c; ++i ) {
			t += v[ i ] * p;
			v[ i ] = ( long long ) ( t % s );
			t /= s;
		}
		if( t )
			v[ c++ ] = ( long long ) t;
		return *this;
	}
	hint & operator /= ( const long long p ) {
		long long t = 0;
		for( int i = c - 1; i > -1; --i ) {
			v[ i ] += t * s;
			t = v[ i ] % p;
			v[ i ] /= p;
		}
		if( !v[ c - 1 ] )
			--c;
		return *this;
	}
	hint operator - ( const hint & p ) const {
		hint r;
		r.c = max( c, p.c );
		long long t = 0;
		for( int i = 0; i < r.c; ++i ) {
			r.v[ i ] = v[ i ] - p.v[ i ] - t;
			if( r.v[ i ] < 0 ) {
				r.v[ i ] += s;
				t = 1;
			}
			else
				t = 0;
		}
		for( --r.c; r.c > 0 && !r.v[ r.c ]; --r.c );
		++r.c;
		return r;
	}
private:
	long long v[ 228 ];
	int c;
	static const long long s = 100000000;
};

ostream & operator << ( ostream & os, const hint & hp ) {
	os << hp.v[ hp.c - 1 ];
	for( int i = hp.c - 2; i > -1; --i )
		os << setfill( '0' ) << setw( 8 ) << hp.v[ i ];
	return os;
}

ifstream fin( "dinner.in" );
ofstream fout( "dinner.out" );

int N, M, S, T = 1;
int L[ 8 ], R[ 8 ];
hint XA, XB;

int Main() {
	fin >> N;
	hint x( 1 );
	for( int i = 1; i < 21; ++i ) {
		x *= i;
		fout << x << endl;
	}
	x /= N;
	fout << x << endl;
	return 0;
}

int main() {
	fin >> N >> M;
	for( int i = 2; i < N; ++i )
		T *= i;
	S = 1 << N;
	for( int i = 0; i < N; ++i )
		fin >> L[ i ] >> R[ i ];
	for( int u, c, s = 0; s < S; ++s ) {
		c = M;
		u = 1;
		for( int i = 0, j = 1; i < N; ++i, j <<= 1 )
			if( s & j ) {
				c -= R[ i ];
				u ^= 1;
			}
			else
				c -= L[ i ] - 1;
		if( c < N )
			continue;
		hint m = 1;
		for( int i = c - N + 1; i < c; ++i )
			m *= i;
		m /= T;
		if( u )
			XA += m;
		else
			XB += m;
	}
	fout << ( XA - XB ) << endl;
	return 0;
}

