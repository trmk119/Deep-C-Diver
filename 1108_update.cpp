#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <limits.h>
#include <string.h>

#define MAX_NODES 100  // �ִ� �� ����

// �� ���� ������ ������ ����ü ����
typedef struct {
    char name[30];    // �� �̸�
    int line;         // �뼱 ��ȣ
} Station;

// �� ��� �迭
Station stations[MAX_NODES];  // �ִ� �� ������ŭ ������ �迭
int station_count = 0;        // ���� ��ϵ� �� ����

// ���� ����� ����� �� �� ���� �Ÿ��� ��Ÿ���� �׷��� �ʱ�ȭ
int graph[MAX_NODES][MAX_NODES];  // ���� ��ķ� �׷��� ǥ��

// �� �� ���� ���� ���� �� �Ÿ� �ʱ�ȭ
void init_graph() {
    for (int i = 0; i < MAX_NODES; i++) {
        for (int j = 0; j < MAX_NODES; j++) {
            if (i == j) {
                graph[i][j] = 0;  // �ڱ� �ڽŰ��� �Ÿ��� 0
            }
            else {
                graph[i][j] = INT_MAX;  // ������� ���� ���� ���Ѵ�� ����
            }
        }
    }

    // ���÷� 1ȣ���� �Ϻ� �� �� ����ġ ����
    graph[0][1] = 10; graph[1][0] = 10;
    graph[1][2] = 5;  graph[2][1] = 5;
    graph[2][3] = 7;  graph[3][2] = 7;
    graph[3][4] = 8;  graph[4][3] = 8;
}

int main() {
    // �� ��� ���� (1ȣ�� �Ϻ� ��)
    strcpy(stations[station_count].name, "�ٴ����ؼ�����"); stations[station_count++].line = 1;
    strcpy(stations[station_count].name, "����"); stations[station_count++].line = 1;
    strcpy(stations[station_count].name, "����"); stations[station_count++].line = 1;
    strcpy(stations[station_count].name, "����"); stations[station_count++].line = 1;
    strcpy(stations[station_count].name, "����"); stations[station_count++].line = 1;

    init_graph();  // �׷��� �ʱ�ȭ

    printf("1�� �� �ڵ� ���� �Ϸ�: �� ��� ���ǿ� �뼱 �ʱ�ȭ�� �Ϸ�Ǿ����ϴ�.\n");

    return 0;
}


