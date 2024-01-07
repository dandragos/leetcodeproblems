#include<fstream>
#include<algorithm>
#include<vector>
#include<queue>
#define INF 2000000000
using namespace std;
ifstream f("cc.in");
ofstream g("cc.out");
struct nod
{
    int x,poz;
};
vector<nod>a[205];
nod tata[205];
int n,s,d,flux,sol,r[20402],z[20402],dist[205],dist2[205],realdist[205];
bool inq[205];
queue<int>q;
struct elem
{
    int x,dist;
    inline bool operator < (const elem &a) const
    {
        return dist>a.dist;
    }
};
priority_queue<elem>pq;

inline bool dijkstra()
{
    int i,l,Z;
    elem p;
    for(i=1;i<=n;i++)
        dist[i]=INF,tata[i]={0,0};
    pq.push({s,0});
    dist[s]=0;
    dist2[s]=0;
    while(!pq.empty())
    {
        p=pq.top();
        pq.pop();
        if(p.dist==dist[p.x])
        {
            l=a[p.x].size();
            for(i=0;i<l;i++)
            {
                Z=realdist[p.x]-realdist[a[p.x][i].x]+z[a[p.x][i].poz];
                if(r[a[p.x][i].poz]>0&&dist[a[p.x][i].x]>dist[p.x]+Z)
                {
                    dist[a[p.x][i].x]=dist[p.x]+Z;
                    dist2[a[p.x][i].x]=dist2[p.x]+z[a[p.x][i].poz];
                    tata[a[p.x][i].x].x=p.x;
                    tata[a[p.x][i].x].poz=a[p.x][i].poz;
                    pq.push({a[p.x][i].x,dist[a[p.x][i].x]});
                }
            }
        }
    }
    for(i=1;i<=n;i++)
        realdist[i]=dist2[i];
    return dist[d]!=INF;
}

inline void bellman_ford()
{
    int i,l,p;
    for(i=1;i<=n;i++)
        realdist[i]=INF;
    realdist[s]=0;
    q.push(s);
    inq[s]=1;
    while(!q.empty())
    {
        p=q.front();
        q.pop();
        inq[p]=0;
        l=a[p].size();
        for(i=0;i<l;i++)
        if(r[a[p][i].poz]>0&&realdist[a[p][i].x]>realdist[p]+z[a[p][i].poz])
        {
            realdist[a[p][i].x]=realdist[p]+z[a[p][i].poz];
            if(inq[a[p][i].x]==0)
            {
                q.push(a[p][i].x);
                inq[a[p][i].x]=1;
            }
        }
    }
}

inline void fmcm()
{
    int i,flow,cost;
    bellman_ford();
    while(dijkstra()!=0)
    {
        flow=INF;
        for(i=d;i!=s;i=tata[i].x)
        {
            flow=min(flow,r[tata[i].poz]);
            if(flow==0)
                break;
        }
        if(flow!=0&&flow!=INF)
        {
            cost=0;
            for(i=d;i!=s;i=tata[i].x)
            {
                r[tata[i].poz]-=flow;
                r[tata[i].poz^1]+=flow;
                cost+=z[tata[i].poz];
            }
            flux+=flow;
            sol+=flow*cost;
        }
    }
}

int main()
{
    int i,x,k=0,j;
    f>>n;
    s=2*n+1;
    d=2*n+2;
    for(i=1;i<=n;i++)
    for(j=1;j<=n;j++)
    {
        f>>x;
        r[k]=1;
        z[k]=x;
        a[i].push_back({j+n,k});
        k++;
        r[k]=0;
        z[k]=-x;
        a[j+n].push_back({i,k});
        k++;
    }
    for(i=1;i<=n;i++)
    {
        r[k]=1;
        z[k]=0;
        a[s].push_back({i,k});
        k++;
        r[k]=0;
        z[k]=0;
        a[i].push_back({s,k});
        k++;
        r[k]=1;
        z[k]=0;
        a[i+n].push_back({d,k});
        k++;
        r[k]=0;
        z[k]=0;
        a[d].push_back({i+n,k});
        k++;
    }
    n=n*2+2;
    fmcm();
    g<<sol;
    return 0;
}
