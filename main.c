#include "biblio.h"

int main()
{
    Graph *g=create_retea();
    int distanta[10], predecesor[10];
    int sursa= 0, destinatie=9;
    if (g==NULL)
        return 1;
    printf("liste de adiacenta pentru reteaua de servere:\n");
    afisareGraph(g);
    if (dijkstra(g, sursa, destinatie, distanta, predecesor, 1)) {
        printf("\ndrumul minim de la serverul %d la serverul %d are costul %d\n",
               sursa, destinatie, distanta[destinatie]);
        afisare_drum(predecesor, sursa, destinatie);
        printf("\n");
        printf("\nmuchiile de pe drumul minim cu cost mai mic de 3:\n");
        afisare_muchii_cost_mic(g, predecesor, sursa, destinatie, 3);
    }
    srand((unsigned int)time(NULL));
    int cost_server[10];
    printf("\ncosturi generate pentru intrarea in servere:\n");
    for (int i=0; i<g->V; i++) {
        cost_server[i]=rand()%11;
        printf("server %d: %d\n", i, cost_server[i]);
    }

    afisare_toate_costurile(g, cost_server);
    eliberare_graph(g);
    return 0;
}