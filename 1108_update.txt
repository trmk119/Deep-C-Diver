#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <limits.h>
#include <string.h>

#define MAX_NODES 100  // 최대 역 개수

// 각 역의 정보를 저장할 구조체 정의
typedef struct {
    char name[30];    // 역 이름
    int line;         // 노선 번호
} Station;

// 역 목록 배열
Station stations[MAX_NODES];  // 최대 역 개수만큼 저장할 배열
int station_count = 0;        // 현재 등록된 역 개수

// 인접 행렬을 사용해 각 역 간의 거리를 나타내는 그래프 초기화
int graph[MAX_NODES][MAX_NODES];  // 인접 행렬로 그래프 표현

// 각 역 간의 연결 상태 및 거리 초기화
void init_graph() {
    for (int i = 0; i < MAX_NODES; i++) {
        for (int j = 0; j < MAX_NODES; j++) {
            if (i == j) {
                graph[i][j] = 0;  // 자기 자신과의 거리는 0
            }
            else {
                graph[i][j] = INT_MAX;  // 연결되지 않은 노드는 무한대로 설정
            }
        }
    }

    // 예시로 1호선의 일부 역 간 가중치 설정
    graph[0][1] = 10; graph[1][0] = 10;
    graph[1][2] = 5;  graph[2][1] = 5;
    graph[2][3] = 7;  graph[3][2] = 7;
    graph[3][4] = 8;  graph[4][3] = 8;
}

int main() {
    // 역 목록 정의 (1호선 일부 역)
    strcpy(stations[station_count].name, "다대포해수욕장"); stations[station_count++].line = 1;
    strcpy(stations[station_count].name, "서면"); stations[station_count++].line = 1;
    strcpy(stations[station_count].name, "연산"); stations[station_count++].line = 1;
    strcpy(stations[station_count].name, "교대"); stations[station_count++].line = 1;
    strcpy(stations[station_count].name, "동래"); stations[station_count++].line = 1;

    init_graph();  // 그래프 초기화

    printf("1주 차 코드 실행 완료: 역 목록 정의와 노선 초기화가 완료되었습니다.\n");

    return 0;
}


