#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>      
#include <limits.h>
#include <string.h>

#define MAX_NODES 20  // �ִ� �� ����
#define TIME_PER_WEIGHT 2.24  // ����ġ 1�� �ҿ� �ð�
#define MAX_LINES 2 // �ϳ��� ���� �������� �ִ� �뼱 ����

int graph[MAX_NODES][MAX_NODES];  // ���� ��ķ� �׷��� ǥ��
int dist[MAX_NODES];  // ��� ���κ��� �� �������� �ִ� �Ÿ�
int prev[MAX_NODES];  // �ִ� ��θ� �����ϱ� ���� ���� ���
int visited[MAX_NODES];  // �������� �� ǥ��

typedef struct {
    char name[14];          // �� �̸�
    int lines[MAX_LINES];   // �뼱 ��ȣ��
    int line_count;         // �� ���� ȣ���� �� ���� ��������
} Station;

Station stations[MAX_NODES];  // �� ��� ����
int station_count = 0;        // �� ����

void init_graph() {
    for (int i = 0; i < MAX_NODES; i++) {
        for (int j = 0; j < MAX_NODES; j++) {
            if (i == j) {
                graph[i][j] = 0;
            }
            else {
                graph[i][j] = INT_MAX;
            }
        }
    }

    // �� ���� ���� ����
    graph[0][1] = 24; graph[1][0] = 24;
    graph[1][2] = 4; graph[2][1] = 4;
    graph[2][3] = 1; graph[3][2] = 1;
    graph[3][4] = 9; graph[4][3] = 9;
    graph[4][5] = 1; graph[5][4] = 1;
    graph[6][7] = 10; graph[7][6] = 10;
    graph[7][8] = 6; graph[8][7] = 6;
    graph[8][1] = 8; graph[1][8] = 8;
    graph[1][9] = 11; graph[9][1] = 11;
    graph[9][10] = 3; graph[10][9] = 3;
    graph[10][11] = 4; graph[11][10] = 4;
    graph[12][7] = 4; graph[7][12] = 4;
    graph[7][13] = 4; graph[13][7] = 4;
    graph[13][14] = 3; graph[14][13] = 3;
    graph[14][2] = 1; graph[2][14] = 1;
    graph[2][9] = 4; graph[9][2] = 4;
    graph[13][4] = 12; graph[4][13] = 12;
    graph[4][15] = 1; graph[15][4] = 1;
    graph[16][12] = 14; graph[12][16] = 14;
    graph[12][8] = 6; graph[8][12] = 6;
    graph[17][14] = 2; graph[14][17] = 2;
    graph[14][3] = 3; graph[3][14] = 3;
    graph[3][10] = 6; graph[10][3] = 6;
    graph[10][18] = 13; graph[18][10] = 13;
}

void dijkstra(int start) {
    for (int i = 0; i < MAX_NODES; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
        prev[i] = -1;
    }

    dist[start] = 0;
    for (int count = 0; count < MAX_NODES; count++) {
        int u = -1;

        for (int i = 0; i < MAX_NODES; i++) {
            if (!visited[i] && (u == -1 || dist[i] < dist[u])) {
                u = i;
            }
        }

        visited[u] = 1;

        for (int v = 0; v < MAX_NODES; v++) {
            if (graph[u][v] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                prev[v] = u;
            }
        }
    }
}

int get_station_index(char station_name[14]) {
    for (int i = 0; i < station_count; i++) {
        if (strcmp(station_name, stations[i].name) == 0) {
            return i;
        }
    }
    return -1;
}

void print_shortest_path(int start, int end) {
    if (dist[end] == INT_MAX) {
        printf("�������� ������ �� �����ϴ�.\n");
        return;
    }

    printf("��õ ���: ");
    int path[MAX_NODES];
    int path_length = 0;

    for (int v = end; v != -1; v = prev[v]) {
        path[path_length++] = v;
    }

    double total_time = 0;

    for (int i = path_length - 1; i >= 0; i--) {
        printf("%s ", stations[path[i]].name);
        if (i > 0) {
            int travel_time = graph[path[i]][path[i - 1]];
            total_time += travel_time * TIME_PER_WEIGHT;
        }
    }
    printf("\n�ҿ� �ð�: %.2f��\n", total_time);
}

void show_stations() {
    printf("�˻� ������ �� ���:\n�ٴ����ؼ�����(1ȣ��)\n����(1, 2ȣ��)\n����(1, 3ȣ��)\n����(1ȣ��, ���ؼ�)\n����(1, 4ȣ��)\n����(1ȣ��)\n���(2ȣ��)\n��õ(2, 3ȣ��)\n���(2ȣ��, �λ���ذ���ö)\n����(2, 3ȣ��)\n������(2ȣ��, ���ؼ�)\n���(2ȣ��)\n����(3, �λ���ذ���ö)\n�̳�(3, 4ȣ��)\n����(3, ���ؼ�)\n����(4ȣ��)\n���ߴ�(�λ���ذ���ö)\n����(���ؼ�)\n��ȭ��(���ؼ�)\n");
}

int main() {
    // �� ��� �ʱ�ȭ
    strcpy(stations[station_count].name, "�ٴ����ؼ�����"); stations[station_count].lines[0] = 1; stations[station_count++].line_count = 1;
    strcpy(stations[station_count].name, "����"); stations[station_count].lines[0] = 1; stations[station_count].lines[1] = 2; stations[station_count++].line_count = 2;
    strcpy(stations[station_count].name, "����"); stations[station_count].lines[0] = 1; stations[station_count].lines[1] = 3; stations[station_count++].line_count = 2;
    strcpy(stations[station_count].name, "����"); stations[station_count].lines[0] = 1; stations[station_count].lines[1] = 4; stations[station_count++].line_count = 2;
    strcpy(stations[station_count].name, "����"); stations[station_count].lines[0] = 1; stations[station_count].lines[1] = 5; stations[station_count++].line_count = 2;
    strcpy(stations[station_count].name, "����"); stations[station_count].lines[0] = 1; stations[station_count++].line_count = 1;
    strcpy(stations[station_count].name, "���"); stations[station_count].lines[0] = 2; stations[station_count++].line_count = 1;
    strcpy(stations[station_count].name, "��õ"); stations[station_count].lines[0] = 2; stations[station_count].lines[1] = 3; stations[station_count++].line_count = 2;
    strcpy(stations[station_count].name, "���"); stations[station_count].lines[0] = 2; stations[station_count].lines[1] = 5; stations[station_count++].line_count = 2;
    strcpy(stations[station_count].name, "����"); stations[station_count].lines[0] = 2; stations[station_count].lines[1] = 3; stations[station_count++].line_count = 2;
    strcpy(stations[station_count].name, "������"); stations[station_count].lines[0] = 2; stations[station_count].lines[1] = 4; stations[station_count++].line_count = 2;
    strcpy(stations[station_count].name, "���"); stations[station_count].lines[0] = 2; stations[station_count++].line_count = 1;
    strcpy(stations[station_count].name, "����"); stations[station_count].lines[0] = 3; stations[station_count].lines[1] = 4; stations[station_count++].line_count = 2;
    strcpy(stations[station_count].name, "�̳�"); stations[station_count].lines[0] = 3; stations[station_count].lines[1] = 4; stations[station_count++].line_count = 2;
    strcpy(stations[station_count].name, "����"); stations[station_count].lines[0] = 3; stations[station_count].lines[1] = 5; stations[station_count++].line_count = 2;
    strcpy(stations[station_count].name, "����"); stations[station_count].lines[0] = 4; stations[station_count++].line_count = 1;
    strcpy(stations[station_count].name, "���ߴ�"); stations[station_count].lines[0] = 4; stations[station_count++].line_count = 1;
    strcpy(stations[station_count].name, "����"); stations[station_count].lines[0] = 5; stations[station_count++].line_count = 1;
    strcpy(stations[station_count].name, "��ȭ��"); stations[station_count].lines[0] = 5; stations[station_count++].line_count = 1;


    init_graph();
    show_stations();

    char start_name[14], end_name[14];
    printf("��߿��� �Է��ϼ���: ");
    scanf("%s", start_name);
    printf("�������� �Է��ϼ���: ");
    scanf("%s", end_name);

    int start = get_station_index(start_name);
    int end = get_station_index(end_name);

    if (start == -1 || end == -1) {
        printf("�˼��մϴ�. �������� �ʴ� ���Դϴ�.\n");
        return 0;
    }

    dijkstra(start);
    print_shortest_path(start, end);

    return 0;
}