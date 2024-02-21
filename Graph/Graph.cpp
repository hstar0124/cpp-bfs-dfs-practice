#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// 정점이 100개
// - 지하철 노선도 : 서로 드문 드문 연결
// - 페이스북 친구 : 서로 빽빽하게 연결


// 인접 리스트 : 실제 연결된 애들만 넣어준다.
void CreateGraph_1()
{
    struct Vertex
    {
        int data;
    };

    vector<Vertex> v(6);

    vector<vector<int>> adjacent;
    adjacent.resize(6);

    /*adjacent[0].push_back(1);
    adjacent[0].push_back(3);*/
    adjacent[0] = { 1, 3 };
    adjacent[1] = { 0, 2, 3 };
    adjacent[3] = { 4 };
    adjacent[5] = { 4 };

    // Q) 0번 -> 3번 연결되어 있나요?
    bool coonnected = false;

    int size = adjacent[0].size();
    for (int i = 0; i < size; i++)
    {
        if (adjacent[0][i] == 3)
            coonnected = true;
    }
}


// 인접 행렬
void CreateGraph_2()
{
    struct Vertex
    {
        int data;
    };

    vector<Vertex> v(6);

    // 연결된 목록을 행렬로 관리
    // [x][0][x][0][x][x]
    // [0][x][0][0][x][x]
    // [x][x][x][x][0][x]
    // [x][x][x][x][x][x]
    // [x][x][x][x][0][x]

    // adjacent[from][to]
    // 행렬을 이용한 그래프 표현
    // 메모리 소모는 심하지만, 빠른 접근
    vector<vector<bool>> adjacent(6, vector<bool>(6, false));
    adjacent[0][1] = true;
    adjacent[0][3] = true;
    adjacent[1][0] = true;
    adjacent[1][2] = true;
    adjacent[1][3] = true;
    adjacent[3][4] = true;
    adjacent[5][4] = true;

    // Q) 0번 -> 3번 연결되어 있나요?
    bool connected = adjacent[0][3];
    
}

// DFS : 재귀 함수 = stack
// BFS : 큐

struct Vertex
{
    int data;
};

vector<Vertex> vertices;
vector<vector<int>> adjacent;

void CreateGraph()
{
    vertices.resize(6);

    // 인접 리스트
    adjacent = vector<vector<int>>(6);
    adjacent[0] = { 1, 3 };
    adjacent[1] = { 0, 2, 3 };
    adjacent[3] = { 4 };
    adjacent[5] = { 4 };

    // 인접 행렬
    //adjacent = vector<vector<int>>
    //{
    //    {0, 1, 0, 1, 0, 0},
    //    {1, 0, 1, 1, 0, 0},
    //    {0, 0, 0, 0, 0, 0},
    //    {0, 0, 0, 0, 1, 0},
    //    {0, 0, 0, 0, 0, 0},
    //    {0, 0, 0, 0, 1, 0},
    //};

}


// ========================================================================
// DFS (Depth First Search)

// 내가 방문한 목록
vector<bool> visited;

void Dfs(int here)
{
    // 방문 도장
    visited[here] = true;
    cout << "Visited : " << here << endl;

    // 인접한길 체크
    
    // 인접 리스트 버전
    /*
        O(V+E) - V:vertex E : edge
        
        모든 vertex 가 연결되어 있으면 E는 제곱이 될수 있기 때문에
        무조건 인접 리스트가 빠른건 아니다.
    */ 
    const int size = adjacent[here].size();
    for (int i = 0; i < size; i++)
    {
        int there = adjacent[here][i];
        if (visited[there] == false)
            Dfs(there);
    }

    // 인접행렬 버전
    // O(V^2) - V : vertex
    //for (int there = 0; there < 6; there++)
    //{
    //    if (adjacent[here][there] == 0)
    //        continue;

    //    if (visited[there] == false)
    //        Dfs(there);
    //}

}

void DfsAll()
{
    visited = vector<bool>(6, false);

    for(int i = 0; i < 6; i++)
        if(visited[i] == false)
            Dfs(i);
}


// ========================================================================
// BFS (Breath First Search)

// 발견한 목록
vector<bool> discovered;

void Bfs(int here)
{
    // ex) 누구에 의해서 발견되었는지?
    vector<int> parent(6, -1);

    // ex) 시작점에서 얼만큼 떨어져 있는지?
    vector<int> dist(6, -1);

    queue<int> q;
    q.push(here);
    discovered[here] = true;

    parent[here] = here;
    dist[here] = 0;

    while (q.empty() == false)
    {
        here = q.front();
        q.pop();

        // 방문
        cout << "Visited : " << here << endl;

        // 인접 리스트
        int size = adjacent[here].size();
        for (int i = 0; i < size; i++)
        {
            int there = adjacent[here][i];
            if (discovered[there])
                continue;

            q.push(there);
            discovered[there] = true;

            parent[there] = here;
            dist[there] = dist[here] + 1;
        }

        // 인접 행렬
        //for (int there = 0; there < 6; there++) {
        //    if (adjacent[here][there] == 0)
        //        continue;
        //    if (discovered[there])
        //        continue;

        //    q.push(there);
        //    discovered[there] = true;
        //}

    }
}


void BfsAll()
{
    discovered = vector<bool>(6, false);

    for (int i = 0; i < 6; i++)
        if (discovered[i] == false)
            Bfs(i);
}


// ========================================================================
// Dijikstra (다익스트라) = BFS + 양념
// Priority_queue

void CreateGraphForDijikstra()
{
    vertices.resize(6);

    adjacent = vector<vector<int>>(6, vector<int>(6, -1));
    adjacent[0][1] = adjacent[1][0] = 15;
    adjacent[0][3] = adjacent[3][0] = 35;
    adjacent[1][2] = adjacent[2][1] = 5;
    adjacent[1][3] = adjacent[3][1] = 10;
    adjacent[3][4] = adjacent[4][3] = 5;
    adjacent[5][4] = adjacent[4][5] = 5;

}

struct VertexCost
{
    VertexCost(int cost, int vertex) : cost(cost), vertex(vertex) {}

    bool operator<(const VertexCost& other) const
    {
        return cost < other.cost;
    }

    bool operator>(const VertexCost& other) const
    {
        return cost > other.cost;
    }

    int cost;
    int vertex;
};

void Dijikstra(int here)
{
    priority_queue<VertexCost, vector<VertexCost>, greater<VertexCost>> pq;
    vector<int> best(6, INT32_MAX);
    vector<int> parent(6, -1);

    pq.push(VertexCost(0, here));
    best[here] = 0;
    parent[here] = here;

    while (pq.empty() == false)
    {
        VertexCost v = pq.top();
        pq.pop();

        int cost = v.cost;
        here = v.vertex;

        if (best[here] < cost)
            continue;

        cout << "방문!" << here << endl;

        for (int there = 0; there < 6; there++)
        {
            if (adjacent[here][there] == -1)
                continue;

            int nextCost = best[here] + adjacent[here][there];
            if (nextCost >= best[there])
                continue;

            best[there] = nextCost;
            parent[there] = here;

            pq.push(VertexCost(nextCost, there));
        }
    }

}



int main()
{
    /*CreateGraph();
    cout << "========== DFS ==========" << endl;
    DfsAll();
    cout << "========== BFS ==========" << endl;
    BfsAll();*/

    cout << "========== Dijikstra ==========" << endl;
    CreateGraphForDijikstra();
    Dijikstra(0);

}