#include <fstream>
#include <list>
#include <string.h>
using namespace std;
ifstream f1("senat.in");
ofstream f2("senat.out");
#define MX 204
#define NIL 0
#define INF 0x0fffffff
#define FOR_LI(v,G) for (list<int>::iterator v=G.begin(); v!=G.end(); v++ )

int n,m;

list<int> Graf[MX];

int dist[MX], Pair[MX], match;


bool BFS()
{
    int u;
    list<int> Q;

    for (u=1; u<=n; u++)
        if ( Pair[u] == NIL )
        {
            Q.push_back(u);
            dist[u]= 0;
        }
        else
            dist[u]= INF;

    dist[NIL]= INF;

    while ( !Q.empty() )
    {
        u= *Q.begin();
        Q.pop_front();

        if ( dist[u] < dist[NIL] )
            FOR_LI(v,Graf[u])
                if ( dist[ Pair[*v] ] == INF )
                {
                    dist[ Pair[*v] ]= dist[u]+1;
                    Q.push_back( Pair[*v] );
                }
    }

    return dist[NIL] != INF;
}

bool DFS(int nod)
{
    if ( nod != NIL)
    {
        FOR_LI(v,Graf[nod])
            if ( dist[ Pair[*v] ] == dist[nod]+1 )
                if ( DFS( Pair[*v] ) )
                {
                    Pair[*v]= nod;
                    Pair[nod]= *v;
                    return true;
                }
            dist[nod]= INF;
        return false;
    }

    return true;
}

void Hopfkropf_Karp()
{
    int u;

    while ( BFS() )
        for (u=1; u<=n; u++)
            if ( Pair[u] == NIL && DFS(u) ) // u can be paired
                match++;
}

int main()
{
    int i,x;
    char linie[3*MX], c= ' ';

    f1>>n>>m;

    while ( c != '\n' )
        f1.get(c);

    for (i=1; i<=m; i++)
    {
        f1.getline(linie, sizeof(linie));
        char *l= linie;

        while (*l)
        {
            for (x=0; *l >= '0' && *l <= '9'; l++ )
                x= x*10+ *l - '0';

            Graf[ n+i ].push_back(x);
            Graf[x].push_back(n+i);

            while (*l && *l==' ')
                l++;
        }
    }

    Hopfkropf_Karp();

    if ( match == m)
        for (i=n+1; i<=n+m; i++)
            f2<< Pair[i] <<"\n";
    else
        f2<<"0";

    f2.close();
    return 0;
}