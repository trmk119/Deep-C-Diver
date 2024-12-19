#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>      
#include <limits.h>
#include <string.h>

#define MAX_NODES 20  // 최대 역 개수
#define TIME_PER_WEIGHT 2.24  // 가중치 1당 소요 시간
#define MAX_LINES 2 // 하나의 역에 지나가는 최대 노선 개수

int graph[MAX_NODES][MAX_NODES];  // 인접 행렬로 그래프 표현
int dist[MAX_NODES];  // 출발 노드로부터 각 노드까지의 최단 거리
int prev[MAX_NODES];  // 최단 경로를 추적하기 위한 이전 노드
int visited[MAX_NODES];  // 지나가는 역 표시

typedef struct {
    char name[14];          // 역 이름
    int lines[MAX_LINES];   // 노선 번호들
    int line_count;         // 몇 개의 호선이 이 역을 지나는지
} Station;

Station stations[MAX_NODES];  // 역 목록 저장
int station_count = 0;        // 역 개수

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

    // 역 간의 연결 설정
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
        printf("목적지에 도달할 수 없습니다.\n");
        return;
    }

    printf("추천 경로: ");
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
    printf("\n소요 시간: %.2f분\n", total_time);
}

void show_stations() {
    printf("검색 가능한 역 목록:\n다대포해수욕장(1호선)\n서면(1, 2호선)\n연산(1, 3호선)\n교대(1호선, 동해선)\n동래(1, 4호선)\n노포(1호선)\n양산(2호선)\n덕천(2, 3호선)\n사상(2호선, 부산김해경전철)\n수영(2, 3호선)\n벡스코(2호선, 동해선)\n장산(2호선)\n대저(3, 부산김해경전철)\n미남(3, 4호선)\n거제(3, 동해선)\n안평(4호선)\n가야대(부산김해경전철)\n부전(동해선)\n태화강(동해선)\n");
}

int main() {
    // 역 목록 초기화
    strcpy(stations[station_count].name, "다대포해수욕장"); stations[station_count].lines[0] = 1; stations[station_count++].line_count = 1;
    strcpy(stations[station_count].name, "서면"); stations[station_count].lines[0] = 1; stations[station_count].lines[1] = 2; stations[station_count++].line_count = 2;
    strcpy(stations[station_count].name, "연산"); stations[station_count].lines[0] = 1; stations[station_count].lines[1] = 3; stations[station_count++].line_count = 2;
    strcpy(stations[station_count].name, "교대"); stations[station_count].lines[0] = 1; stations[station_count].lines[1] = 4; stations[station_count++].line_count = 2;
    strcpy(stations[station_count].name, "동래"); stations[station_count].lines[0] = 1; stations[station_count].lines[1] = 5; stations[station_count++].line_count = 2;
    strcpy(stations[station_count].name, "노포"); stations[station_count].lines[0] = 1; stations[station_count++].line_count = 1;
    strcpy(stations[station_count].name, "양산"); stations[station_count].lines[0] = 2; stations[station_count++].line_count = 1;
    strcpy(stations[station_count].name, "덕천"); stations[station_count].lines[0] = 2; stations[station_count].lines[1] = 3; stations[station_count++].line_count = 2;
    strcpy(stations[station_count].name, "사상"); stations[station_count].lines[0] = 2; stations[station_count].lines[1] = 5; stations[station_count++].line_count = 2;
    strcpy(stations[station_count].name, "수영"); stations[station_count].lines[0] = 2; stations[station_count].lines[1] = 3; stations[station_count++].line_count = 2;
    strcpy(stations[station_count].name, "벡스코"); stations[station_count].lines[0] = 2; stations[station_count].lines[1] = 4; stations[station_count++].line_count = 2;
    strcpy(stations[station_count].name, "장산"); stations[station_count].lines[0] = 2; stations[station_count++].line_count = 1;
    strcpy(stations[station_count].name, "대저"); stations[station_count].lines[0] = 3; stations[station_count].lines[1] = 4; stations[station_count++].line_count = 2;
    strcpy(stations[station_count].name, "미남"); stations[station_count].lines[0] = 3; stations[station_count].lines[1] = 4; stations[station_count++].line_count = 2;
    strcpy(stations[station_count].name, "거제"); stations[station_count].lines[0] = 3; stations[station_count].lines[1] = 5; stations[station_count++].line_count = 2;
    strcpy(stations[station_count].name, "안평"); stations[station_count].lines[0] = 4; stations[station_count++].line_count = 1;
    strcpy(stations[station_count].name, "가야대"); stations[station_count].lines[0] = 4; stations[station_count++].line_count = 1;
    strcpy(stations[station_count].name, "부전"); stations[station_count].lines[0] = 5; stations[station_count++].line_count = 1;
    strcpy(stations[station_count].name, "태화강"); stations[station_count].lines[0] = 5; stations[station_count++].line_count = 1;


    init_graph();
    show_stations();

    char start_name[14], end_name[14];
    printf("출발역을 입력하세요: ");
    scanf("%s", start_name);
    printf("도착역을 입력하세요: ");
    scanf("%s", end_name);

    int start = get_station_index(start_name);
    int end = get_station_index(end_name);

    if (start == -1 || end == -1) {
        printf("죄송합니다. 지원하지 않는 역입니다.\n");
        return 0;
    }

    dijkstra(start);
    print_shortest_path(start, end);

    return 0;
}