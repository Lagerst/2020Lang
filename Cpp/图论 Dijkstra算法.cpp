void Dijkstra(int k) {
	for (int i=1;i<=n;i++) {
		dis[i]=2147483647/2;
		vis[i]=0;
	}
	dis[k]=0;
	slack.push(node{k,dis[k]});
	while (!slack.empty())
	{
		node x=slack.top();slack.pop();

		if (vis[x.next]) continue;
		vis[x.next]=1;
		for (int i=0;i<s[x.next].size();i++)
		{
			node y=s[x.next][i];
			if (!vis[y.next]) {
				if (y.data<=1) {
					int cost=1-y.data;
					if (dis[y.next]>x.data+cost)
					{
						dis[y.next]=x.data+cost;
						slack.push(node{y.next,dis[y.next]});
					}
				}
			}
		}
	}
}