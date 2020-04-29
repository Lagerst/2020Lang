#include <cstdio>
#include <string.h>
#include <vector>
using namespace std;
int const MAX = 10000;
vector<int> G[MAX];
int vis[MAX];
int link[MAX];//代表当前状态Y中与X相连的点（即d[y] = x）
int n, m;//n为X集合点数，m为Y集合点数（这里默认点的序号为X到Y依次递增）
 
int can(int t)//这一个t保证它是X中的点
{
    for(int i = 0; i < G[t].size(); i++){//从Y中的每一点开始找
        int tmp = G[t][i];
        if(!vis[tmp]){//如果这点没有被前面几次找过
            vis[tmp] = 1;
            if(link[tmp] == -1 || can(link[tmp])){//这里寻找增广路径的结束条件就是找到Y中未被配对过的点，如果这点被配对过，那么就从这点配对的X中的点进行新一轮的can()
               link[tmp] = t;
               return 1;
            }
        }
    }
    return 0;
}
 
int maxmatch()
{
    int num = 0;
    for(int i = 1; i <= n; i++){
        memset(vis, 0, sizeof(vis));
        if(can(i)){
            num++;
        }
    }
    return num;
}
 
int main()
{
    while(scanf("%d %d", &n, &m) != EOF){
        for(int i = 1; i <= n; i++)
            G[i].clear();
        memset(link, -1, sizeof(link));
        int s;
        scanf("%d", &s);
        while(s--){
            int a, b;//表示X中的a与Y中的b相连
            scanf("%d %d", &a, &b);//假设输入的点X和Y分开输入（都是从1开始）
            G[a].push_back(b+n);
            G[b+n].push_back(a);//由于是无向图
        }
        printf("%d\n", maxmatch());
    }
    return 0;
}
