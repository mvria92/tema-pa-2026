#include "biblio.h"

Graph *creareGraph(int v){
    Graph *g=malloc(sizeof(Graph));
    if (g==NULL){
        printf("nu s a putut aloca memorie\n");
        exit (1);
    }
    g->V=v;
    g->E=0;
    g->a=malloc(g->V*sizeof(Node*));
    if (g->a==NULL){
        printf("nu s a ptut aloca memorie (2)\n");
        exit(1);
    }
    for (int i=0; i<g->V; i++){
        g->a[i]=NULL;
    }
    return g;
}

Graph *create_retea()
{
    Graph *g=creareGraph(10);
    adaugaMuchie(g, 0, 1, 4);
    adaugaMuchie(g, 0, 2, 7);
    adaugaMuchie(g, 1, 3, 2);
    adaugaMuchie(g, 1, 4, 5);
    adaugaMuchie(g, 2, 5, 3);
    adaugaMuchie(g, 3, 6, 8);
    adaugaMuchie(g, 4, 7, 6);
    adaugaMuchie(g, 5, 7, 4);
    adaugaMuchie(g, 5, 8, 1);
    adaugaMuchie(g, 6, 9, 9);
    adaugaMuchie(g, 7, 8, 1);
    adaugaMuchie(g, 7, 9, 5);
    adaugaMuchie(g, 8, 9, 3);
    return g;
}

Node *creareNode(int v, int cost){
    Node *newNode=malloc(sizeof(Node));
    if (newNode==NULL){
         printf("nu s a ptut aloca memorie (3)\n");
        exit(1);
    }
    newNode->vertex_no=v;
    newNode->cost=cost;
    newNode->next=NULL;
    return newNode;
}

void addArc(Graph *g, int xi, int xf, int cost){
    Node *newNode = creareNode(xf, cost);
    if (newNode==NULL){
        printf("nu s a ptut aloca memorie (3)\n");
        exit(1);
    }
    newNode->next=g->a[xi];
    g->a[xi]=newNode;

}

void adaugaMuchie (Graph *g, int n1, int n2, int cost){
    if (g==NULL) // || n1<0 || n2<0 || n1 >=g->V || n2>=g->V)
        return;
    if (n1<g->V && n2<g->V && n1>=0 && n2>=0){
        addArc(g, n1, n2, cost);
        addArc(g, n2, n1, cost);
        g->E++;
    }
    
}

void afisareGraph(Graph *g){
    if (g==NULL)
        return ;
    for (int i=0; i<g->V; i++){
        printf("Server %d: ", i);
        Node *vecin=g->a[i];
        while (vecin !=NULL){
            printf("%d (cost %d)\n", vecin->vertex_no, vecin->cost);
            vecin=vecin->next;
        }
        printf ("\n");
    }
}


int minim_nevizitat(Graph *g, int distanta[], int verificat[]){
    int mini=1000000000;
    int poz=-1;
    for (int i=0; i<g->V; i++) {
        if (verificat[i]==0 && distanta[i]<mini) {
            mini=distanta[i];
            poz=i;
        }
    }
    return poz;
}

void initializare_dijkstra(Graph *g, int sursa, int dist[], int predecesor[], int verificat[]){
    for (int i=0; i<g->V; i++) {
        dist[i]=1000000000;
        predecesor[i]=-1;
        verificat[i]=0;
    }
    dist[sursa]=0;
}

int dijkstra(Graph *g, int sursa, int destinatie, int distanta[], int predecesor[], int stop){
    int *verificat=calloc(g->V, sizeof(int));
    if (verificat==NULL){
        return 0;
    }
    initializare_dijkstra(g, sursa, distanta, predecesor, verificat);
    for (int i=0; i<g->V; i++) {
        int u=minim_nevizitat(g, distanta, verificat);
        if (u==-1){
            break;
        }
        verificat[u]=1;
        if (stop==1 && u==destinatie){
            break;
        }
        Node *p=g->a[u];
        while (p!=NULL) {
            int v=p->vertex_no;
            if (verificat[v]==0 && distanta[v]>distanta[u]+p->cost) {
                distanta[v]=distanta[u]+p->cost;
                predecesor[v]=u;
            }
            p=p->next;
        }
    }
    free(verificat);
    if (distanta[destinatie]==1000000000){
        return 0;
    }
    return 1;
}

int dijkstra_cost_server(Graph *g, int sursa, int destinatie, int cost_server[], int distanta[], int predecesor[]){
    int *verificat=calloc(g->V, sizeof(int));
    if (verificat==NULL)
        return 0;
    initializare_dijkstra(g, sursa, distanta, predecesor, verificat);
    for (int i=0; i<g->V; i++) {
        int u=minim_nevizitat(g, distanta, verificat);
        if (u==-1)
            break;
        verificat[u]=1;
        if (u==destinatie)
            break;
        Node *p=g->a[u];
        while (p!=NULL) {
            int v=p->vertex_no;
            int cost_total=p->cost+cost_server[v];
            if (verificat[v]==0 && distanta[v]>distanta[u]+cost_total) {
                distanta[v]=distanta[u]+cost_total;
                predecesor[v]=u;
            }
            p=p->next;
        }
    }
    free(verificat);
    if (distanta[destinatie]==1000000000)
        return 0;
    return 1;
}

void afisare_drum(int predecesor[], int sursa, int destinatie){
    if (sursa==destinatie) {
        printf("%d", sursa);
        return;
    }
    if (predecesor[destinatie]==-1) {
        printf("nu exista drum");
        return;
    }
    afisare_drum(predecesor, sursa, predecesor[destinatie]);
    printf(" -> %d", destinatie);
}

int cost_muchie(Graph *g, int u, int v){
    Node *p=g->a[u];
    while (p!=NULL) {
        if (p->vertex_no==v)
            return p->cost;
        p=p->next;
    }
    return 1000000000;
}

void afisare_muchii_cost_mic(Graph *g, int predecesor[], int sursa, int destinatie, int cost_maxim){
    if (sursa==destinatie || predecesor[destinatie]==-1)
        return;
    afisare_muchii_cost_mic(g, predecesor, sursa, predecesor[destinatie], cost_maxim);
    int u=predecesor[destinatie];
    int cost=cost_muchie(g, u, destinatie);
    if (cost<cost_maxim)
        printf("(%d, %d) cost %d\n", u, destinatie, cost);
}

void eliberare_graph(Graph *g){
    for (int i=0; i<g->V; i++) {
        Node *p=g->a[i];
        while (p!=NULL) {
            Node *urm=p->next;
            free(p);
            p=urm;
        }
    }
    free(g->a);
    free(g);
}

void afisare_toate_costurile(Graph *g, int cost_server[])
{
    int distanta[10], predecesor[10];
    printf("\ncosturi minime intre oricare doua servere, cu cost de intrare in server:\n");
    for (int i=0; i<g->V; i++) {
        for (int j=0; j<g->V; j++) {
            if (i==j)
                printf("%4d", 0);
            else if (dijkstra_cost_server(g, i, j, cost_server, distanta, predecesor))
                printf("%4d", distanta[j]);
            else
                printf(" INF");
        }
        printf("\n");
    }
}