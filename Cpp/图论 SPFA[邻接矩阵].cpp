scanf("%d%d", &s, &t);
memset(used, 0, sizeof(used));
used[s] = 1;
f[s] = 0;
slack.push(s);
while (1) {
  int j = slack.front();
  for (vector<int>::iterator iter = p[j].begin(); iter != p[j].end(); iter++) {
    if (f[(*iter)] > f[j] + l[j][*iter] + wait(f[j], a[j])) {
      f[(*iter)] = f[j] + l[j][*iter] + wait(f[j], a[j]);
      if (!used[(*iter)]) {
        slack.push((*iter));
        used[(*iter)] = 1;
      }
    }
  }
  used[j] = 0;
  slack.pop();
  if (slack.empty())
    break;
}
ans = f[t];
cout << f[t] << endl;