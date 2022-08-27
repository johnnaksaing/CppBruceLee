```c++
std::vector<std::vector<int>> map(n + 1, std::vector<int>(n + 1,big));

//중간 - 시작 - 끝 순서
for (int k = 1; k <= n; k++)
for (int i = 1; i <= n; i++)
for (int j = 1; j <= n; j++)
    if (map[i][j] > map[i][k] + map[k][j])
        map[i][j] = map[i][k] + map[k][j];
```