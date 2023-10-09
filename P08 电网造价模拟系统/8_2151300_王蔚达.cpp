#define _CRT_SECURE_NO_WARNINGS
#include "8_2151300_王蔚达.h"
using namespace std;

int main()
{
    Graph graph;

    cout << "==================================================" << endl;
    cout << "**\t\t 电网造价模拟系统\t\t**" << endl;
    cout << "==================================================" << endl;
    cout << "**\t\tA --- 创建电网顶点\t\t**" << endl;
    cout << "**\t\tB --- 添加电网的边\t\t**" << endl;
    cout << "**\t\tC --- 构建最小生成树\t\t**" << endl;
    cout << "**\t\tD --- 显示最小生成树\t\t**" << endl;
    cout << "**\t\tE --- 退出   程序\t\t**" << endl;
    cout << "==================================================" << endl;

    bool quit = false;
    char option;
    while (!quit)
    {
        cout << endl
             << "请选择操作：";
        cin >> option;
        switch (option)
        {
        case 'a':
        case 'A':
            graph.CreateVertex();
            break;
        case 'b':
        case 'B':
            graph.AddEdge();
            break;
        case 'c':
        case 'C':
            graph.BuildMST();
            break;
        case 'd':
        case 'D':
            graph.PrintMST();
            break;
        case 'e':
        case 'E':
            quit = true;
            cout << "Press any key to continue... " << endl;
            break;

        default:
            cout << "输入有误，请重新输入！" << endl;
            cin.clear();
            cin.ignore(1024, '\n');
            break;
        }
    }
    return 0;
}
