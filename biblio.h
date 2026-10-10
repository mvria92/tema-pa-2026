#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct ListaNoduri{
    int cost;
    int vertex_no;
    struct ListaNoduri *next;

}Node;

typedef struct {
    int V, E;
    Node **a;
}Graph;


Graph *creareGraph(int v);
Node *creareNode(int v, int cost);
void addArc(Graph *g, int xi, int xf, int cost);
void adaugaMuchie(Graph *g, int n1, int n2, int cost);
void afisareGraph(Graph *g);
Graph *create_retea();
void afisare_toate_costurile(Graph *g, int cost_server[]);
int dijkstra(Graph *g, int sursa, int destinatie, int distanta[], int predecesor[], int stop);
int dijkstra_cost_server(Graph *g, int sursa, int destinatie, int cost_server[], int distanta[], int predecesor[]);
void afisare_drum(int predecesor[], int sursa, int destinatie);
void afisare_muchii_cost_mic(Graph *g, int predecesor[], int sursa, int destinatie, int cost_maxim);
void eliberare_graph(Graph *g);