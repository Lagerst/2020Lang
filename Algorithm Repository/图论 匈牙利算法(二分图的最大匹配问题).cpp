#include <cstdio>
#include <string.h>
#include <vector>
using namespace std;
int const MAX = 10000;
vector<int> G[MAX];
int vis[MAX];
int link[MAX];//����ǰ״̬Y����X�����ĵ㣨��d[y] = x��
int n, m;//nΪX���ϵ�����mΪY���ϵ���������Ĭ�ϵ�����ΪX��Y���ε�����
 
int can(int t)//��һ��t��֤����X�еĵ�
{
    for(int i = 0; i < G[t].size(); i++){//��Y�е�ÿһ�㿪ʼ��
        int tmp = G[t][i];
        if(!vis[tmp]){//������û�б�ǰ�漸���ҹ�
            vis[tmp] = 1;
            if(link[tmp] == -1 || can(link[tmp])){//����Ѱ������·���Ľ������������ҵ�Y��δ����Թ��ĵ㣬�����㱻��Թ�����ô�ʹ������Ե�X�еĵ������һ�ֵ�can()
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
            int a, b;//��ʾX�е�a��Y�е�b����
            scanf("%d %d", &a, &b);//��������ĵ�X��Y�ֿ����루���Ǵ�1��ʼ��
            G[a].push_back(b+n);
            G[b+n].push_back(a);//����������ͼ
        }
        printf("%d\n", maxmatch());
    }
    return 0;
}
