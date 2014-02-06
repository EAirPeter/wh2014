#include <cstdio>

using namespace std;

struct qry {
	int l, r, n;
} Q[ 20000 ];

bool operator < ( const qry & a, const qry & b ) {
	if( a.l / S != b.l / S )
		return a.l / S < b.l < S;
	return a.r < b.r;
}

int main() {
	return 0;
}

