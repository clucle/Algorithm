#include <iostream>

using namespace std;

int arr[1000010];
long long sum[2000010];

long long construct_tree(int idx, int start, int end) {
    if (start == end) {
        sum[idx] = arr[start];
        return sum[idx];
    } else {
        sum[idx] = construct_tree(idx * 2 + 1, start, (start + end) / 2) +
                    construct_tree(idx * 2 + 2, ((start + end) / 2) + 1, end);
        return sum[idx];
    }
}

int find_idx(int idx, int b, int start, int end) {
    if (start == end) {
        return idx;
    }
    if (b <= (start + end) / 2) {
        return find_idx(idx * 2 + 1, b, start, (start + end) / 2);
    } else {
        return find_idx(idx * 2 + 2, b, ((start + end) / 2) + 1, end);
    }
}

long long sum_b_to_c(int idx, int b, int c, int start, int end) {
    if (b == start && c == end) {
        return sum[idx];
    }
    int mid = ((start + end) / 2);
    if (b <= mid && c <= mid) {
        return sum_b_to_c(idx * 2 + 1, b, c, start, mid);
    } else if (b > mid && c > mid) {
        return sum_b_to_c(idx * 2 + 2, b, c, mid + 1, end);
    } else {
        return sum_b_to_c(idx * 2 + 1, b, mid, start, mid) +
                sum_b_to_c(idx * 2 + 2, mid + 1, c, mid + 1, end);
    }

}

void print_tree() {
    for (int i = 0; i < 15; i++) {
        cout << sum[i] << ' ';
    }
    cout << '\n';
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);
    int N, M, K;
    cin >> N >> M >> K;
    for (int i = 1; i <= N; i++) {
        cin >> arr[i];
    }
    construct_tree(0, 1, N);
    int cnt = M + K; 
    int a, b, c;

    for (int i = 0; i < cnt; i++) {
        cin >> a >> b >> c;
        if (a == 1) {
            int idx = find_idx(0, b, 1, N);
            long long diff = c - sum[idx];
            while (idx > 0) {
                sum[idx] += diff;
                idx = (idx - 1) / 2;
            }
            sum[0] += diff;
        } else if (a == 2) {
            cout << sum_b_to_c(0, b, c, 1, N) << '\n';
        }
    }
    return 0;
    
}