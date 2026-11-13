#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
#include <cctype>
using namespace std;

const int N = 6;
int adj[N][N] = {0};

void addEdge(char a, char b, int w) {
    adj[a - 'A'][b - 'A'] = w;
    adj[b - 'A'][a - 'A'] = w;
}

void initGraph() {
    addEdge('A', 'B', 4); addEdge('A', 'C', 2);
    addEdge('B', 'C', 1); addEdge('B', 'D', 5); addEdge('B', 'E', 3);
    addEdge('C', 'D', 8); addEdge('C', 'E', 6);
    addEdge('D', 'E', 2); addEdge('D', 'F', 4);
    addEdge('E', 'F', 3);
}

void printMatrix() {
    cout << "\nAdjacency Matrix:\n    ";
    for (int j = 0; j < N; j++) cout << (char)('A' + j) << "  ";
    cout << "\n";
    for (int i = 0; i < N; i++) {
        cout << (char)('A' + i) << " | ";
        for (int j = 0; j < N; j++) cout << adj[i][j] << "  ";
        cout << "\n";
    }
}

void bfs(int s) {
    bool vis[N] = {false};
    queue<int> q;
    q.push(s); vis[s] = true;
    cout << "BFS dari " << (char)('A' + s) << ": ";
    while (!q.empty()) {
        int u = q.front(); q.pop();
        cout << (char)('A' + u) << " ";
        for (int v = 0; v < N; v++)
            if (adj[u][v] && !vis[v]) { vis[v] = true; q.push(v); }
    }
    cout << "\n";
}

void dfsRec(int u, bool vis[]) {
    vis[u] = true;
    cout << (char)('A' + u) << " ";
    for (int v = 0; v < N; v++)
        if (adj[u][v] && !vis[v]) dfsRec(v, vis);
}
void dfs(int s) {
    bool vis[N] = {false};
    cout << "DFS dari " << (char)('A' + s) << ": ";
    dfsRec(s, vis);
    cout << "\n";
}

void dijkstra(int s, int t) {
    int dist[N], par[N];
    bool done[N] = {false};
    for (int i = 0; i < N; i++) { dist[i] = INT_MAX; par[i] = -1; }
    dist[s] = 0;
    for (int it = 0; it < N; it++) {
        int u = -1;
        for (int i = 0; i < N; i++)
            if (!done[i] && dist[i] != INT_MAX && (u == -1 || dist[i] < dist[u])) u = i;
        if (u == -1) break;
        done[u] = true;
        for (int v = 0; v < N; v++)
            if (adj[u][v] && !done[v] && dist[u] + adj[u][v] < dist[v]) {
                dist[v] = dist[u] + adj[u][v];
                par[v] = u;
            }
    }
    if (dist[t] == INT_MAX) { cout << "Tidak ada rute dari " << (char)('A' + s) << " ke " << (char)('A' + t) << ".\n"; return; }
    vector<int> path;
    for (int v = t; v != -1; v = par[v]) path.push_back(v);
    reverse(path.begin(), path.end());
    cout << "Rute terpendek: ";
    for (size_t i = 0; i < path.size(); i++) {
        cout << (char)('A' + path[i]);
        if (i + 1 < path.size()) cout << " -> ";
    }
    cout << "\nTotal jarak   : " << dist[t] << "\n";
}

int bacaVertex(const char* prompt) {
    char c;
    while (true) {
        cout << prompt;
        if (!(cin >> c)) return -1;
        c = toupper(c);
        if (c >= 'A' && c <= 'F') return c - 'A';
        cout << "Vertex tidak valid (A-F).\n";
    }
}

int main() {
    initGraph();
    int pil;
    do {
        cout << "\n===== RUTE KAMPUS =====\n"
             << "1. Tampilkan adjacency matrix\n2. BFS & DFS\n3. Rute terpendek (Dijkstra)\n"
             << "4. Rute terpendek dari A ke vertex tujuan\n0. Keluar\nPilih: ";
        cin >> pil;
        if (pil == 1) printMatrix();
        else if (pil == 2) {
            int s = bacaVertex("Vertex awal (A-F): ");
            if (s < 0) break;
            bfs(s); dfs(s);
        } else if (pil == 3) {
            int s = bacaVertex("Vertex awal (A-F)  : ");
            int t = bacaVertex("Vertex tujuan (A-F): ");
            if (s < 0 || t < 0) break;
            dijkstra(s, t);
        } else if (pil == 4) {
            int t = bacaVertex("Vertex tujuan (A-F): ");
            if (t < 0) break;
            dijkstra(0, t);
        } else if (pil != 0) cout << "Pilihan tidak valid.\n";
    } while (pil != 0 && cin);
    return 0;
}