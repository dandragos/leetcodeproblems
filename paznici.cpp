#include <stdio.h>
#include <vector>
#include <string>

using namespace std;
#define maxn 30
#define pb push_back

vector <int> a[maxn];
int g[maxn],used[maxn],c[maxn*2],mark[maxn];
int n,m,draw,sol;
char b[maxn];

int DFS(int nod)
{
	if (used[nod]==draw) return 0;

	used[nod]=draw;
	int i;
	
	for (i=0;i<g[nod];i++)
	  if (mark[a[nod][i]]==0) 
	  {
            c[nod]=1;
            mark[a[nod][i]]=nod;
            return 1;
      }

	for (i=0;i<g[nod];i++)
		if ((mark[a[nod][i]]!=0) && (DFS(mark[a[nod][i]])))
		{
			c[nod]=1;
			mark[a[nod][i]]=nod;
			return 1;
		}

	return 0;
}

void cuplaj()
{
	int i;
	for (i=1;i<=n;i++)
	{
		++draw;
		sol+=DFS(i);
	}
}

void DFS2(int nod)
{
	int i;

	for (i=0;i<g[nod];i++)
		if (!c[n+a[nod][i]])
		{
			c[n+a[nod][i]]=1;
			c[mark[a[nod][i]]]=0;
			DFS2(mark[a[nod][i]]);
		}
}

int main()
{
	freopen("paznici.in","r",stdin);
	freopen("paznici.out","w",stdout);

	scanf("%d %d ",&n,&m);
	
	int i,j;

	for (i=1;i<=n;i++) 
	{
		fgets(b,maxn,stdin);
		for (j=0;j<m;j++)
			if (b[j]=='1') a[i].pb(j+1);

		g[i]=a[i].size();
	}

	cuplaj();

	for (i=1;i<=n;i++)
		if (!c[i]) DFS2(i);

	for (i=1;i<=n;i++) 
		if (c[i]) printf("%c",i-1+'A');

	for (i=1;i<=m;i++) 
		 if (c[n+i]) printf("%c",i-1+'a');

	return 0;
}