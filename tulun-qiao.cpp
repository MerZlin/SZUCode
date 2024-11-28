#include <ctime>
#include <fstream>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
<<<<<<< HEAD

int flag;
=======
//1111212
>>>>>>> 30f22ab9f4f3fc3d3835c6739252bacbf84516a5
/*基准算法*/
struct graph {
    int pointnum;
    int edgenum;
    int** linkgraph;
    int** edge;
};

void DFS(graph G, bool visit[], int i)
{
    visit[i] = true;
    for (int j = 0; j < G.pointnum; j++)
        if (G.linkgraph[i][j] == 1 && !visit[j])
            DFS(G, visit, j);
}

int DFS_graph(graph G, bool visit[])
{
    int i = 0, sum = 0;
    for (i = 0; i < G.pointnum; i++)
        visit[i] = false;

    for (i = 0; i < G.pointnum; i++)
        if (!visit[i])   //计算连通分量数
        {
            DFS(G, visit, i);
            sum++;
        }
    return sum;
}

int jizhun(graph& G, bool visit[])
{
    int sum = 0;
    for (int i = 0; i < G.edgenum; i++)
    {
        int sum1 = DFS_graph(G, visit);
        G.linkgraph[G.edge[i][0]][G.edge[i][1]] = 0;
        G.linkgraph[G.edge[i][1]][G.edge[i][0]] = 0;
        int sum2 = DFS_graph(G, visit);
        if (sum1 != sum2)   //是桥
        {
            cout << "桥：" << G.edge[i][0] << "-----" << G.edge[i][1] << endl;
            sum++;
        }
        G.linkgraph[G.edge[i][0]][G.edge[i][1]] = 1;
        G.linkgraph[G.edge[i][1]][G.edge[i][0]] = 1;
    }
    return sum;
}

int main()
{
    clock_t start_time, end_time;
    graph G;
    G.pointnum = 0; G.edgenum = 0;
    int pointnum = 0, edgenum = 0;
    int firstpoint = 0, secondpoint = 0, i = 0, j = 0, sum = 0;
    const char* ffile = "E:/BaiduNetdisk/算法/实验5/1.txt";
    //const char* ffile = "E:/BaiduNetdisk/mediumDG.txt";
    ifstream file(ffile);
    file >> G.pointnum >> G.edgenum;
    //file >> pointnum >> edgenum;
    
    /*相关变量初始化*/
    
    G.linkgraph = new int* [G.pointnum];    //记录邻接矩阵
    for (i = 0; i < G.pointnum; i++)
        G.linkgraph[i] = new int[G.pointnum];
    for (i = 0; i < G.pointnum; i++)
        for (j = 0; j < G.pointnum; j++)
            G.linkgraph[i][j] = 0;

    G.edge = new int* [G.edgenum];  //记录边情况
    for (i = 0; i < G.edgenum; i++)
        G.edge[i] = new int[2];
    for (i = 0; i < G.edgenum; i++)
        for (j = 0; j < 2; j++)
            G.edge[i][j] = 0;

    bool* visit = new bool[G.pointnum];
    for (i = 0; i < G.pointnum; i++)
        visit[i] = false;

    //读入数据
    i = 0;
    while (file >> firstpoint >> secondpoint)
    {
        G.edge[i][0] = firstpoint;
        G.edge[i][1] = secondpoint;
        //cout << G.edge[i][0] << " " << G.edge[i][1] << endl;
        i++;
        G.linkgraph[firstpoint][secondpoint] = 1;
        G.linkgraph[secondpoint][firstpoint] = 1;
    }
    
   
    start_time = clock();
    sum = jizhun(G, visit); 
    end_time = clock();

    cout << "桥的个数：" << sum << endl;
    cout << "总耗时为:" << (double)(end_time - start_time) / CLOCKS_PER_SEC << "s" << endl;
    return 0;
}