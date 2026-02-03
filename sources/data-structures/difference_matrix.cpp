#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> matrix(n, vector<int>(m));
vector<vector<int>> differenceMatrix(n + 1, vector<int>(m + 1));

void update(int x1, int y1, int x2, int y2, int val) {
    differenceMatrix[x1][y1] += val;
    differenceMatrix[x1][y2 + 1] -= val;
    differenceMatrix[x2 + 1][y1] -= val;
    differenceMatrix[x2 + 1][y2 + 1] += val;
}

void rebuild() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i > 0) { differenceMatrix[i][j] += differenceMatrix[i - 1][j]; }
            if (j > 0) { differenceMatrix[i][j] += differenceMatrix[i][j - 1]; }
            if (i > 0 && j > 0) {
                differenceMatrix[i][j] -= differenceMatrix[i - 1][j - 1];
            }
            matrix[i][j] += differenceMatrix[i][j];
        }
    }
    differenceMatrix.assign(n + 1, vector<int>(m + 1, 0));
}

int main() {
    matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    n = matrix.size(), m = matrix[0].size();
    differenceMatrix.assign(n + 1, vector<int>(m + 1, 0));

    update(0, 0, 1, 1, 3);
    update(1, 1, 2, 2, 1);
    rebuild();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) { cout << matrix[i][j] << ' '; }
        cout << endl;
    }
}
