#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

typedef vector< int > vecint;
typedef vecint::iterator iiter;

ifstream fin( "count.in" );
ofstream fout( "count.out" );

vecint GA, GP, GL, GR;
int N;
bool GM[ 100 ][ 100 ], GV[ 1000001 ], GW[ 100 ];
int GH[ 100 ];

bool argument( const int pc ) {
	for( iiter id = GR.begin(); id < GR.end(); ++id )
		if( !GM[ pc ][ *id ] && !GW[ *id ] ) {
			GW[ *id ] = true;
			if( GH[ *id ] == -1 || argument( GH[ *id ] ) ) {
				GH[ *id ] = pc;
				return true;
			}
		}
	return false;
}

istream & operator >> ( istream & is, vecint & vec ) {
	string str;
	getline( is, str );
	stringstream ss( str );
	while( !ss.eof() ) {
		int tmp;
		ss >> tmp;
		vec.push_back( tmp );
	}
	return is;
}

int main() {
	fin >> GA >> GP;
	for( iiter i = GP.begin(); i < GP.end(); ++i )
		GV[ *i ] = true;
	N = static_cast< int >( GA.size() );
	for( int i = 0; i < N; ++i )
		for( int j = 0; j < N; ++j )
			GM[ i ][ j ] = GM[ j ][ i ] = GV[ abs( GA[ i ] - GA[ j ] ) ];
	int x = 1;
	for( int va = 0; va < N; ++va )
		for( int vb = 0; vb < N; ++vb )
			if( GM[ va ][ vb ] ) {
				GL.clear();
				GR.clear();
				for( int vl = 0; vl < N; ++vl )
					if( GM[ vb ][ vl ] )
						GL.push_back( vl );
				for( int vr = 0; vr < N; ++vr )
					if( GM[ va ][ vr ] )
						GR.push_back( vr );
				int cx = static_cast< int >( GL.size() + GR.size() );
				memset( GH, -1, sizeof( GH ) );
				for( iiter il = GL.begin(); il < GL.end(); ++il ) {
					memset( GW, false, sizeof( GW ) );
					if( argument( *il ) )
						--cx;
				}
				x = max( x, cx );
			}
	fout << x << endl;
	return 0;
}

