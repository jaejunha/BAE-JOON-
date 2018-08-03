#include <iostream>
#include <algorithm>
using namespace std;

int n;
int dp[40001];
int p[40001];
int s;

int main() {
	scanf("%d", &n);
	for (int i = 0, x, j; i < n; i++) {
		scanf("%d", &x);
		dp[i] = 2147483647;
		j = lower_bound(dp, dp + i, x) - dp;
		dp[j] = x;
		p[i] = j;
	}
	for (int i = 0; i < n; i++)
		s = max(s, p[i]);
	printf("%d", s + 1);
	return 0;
}