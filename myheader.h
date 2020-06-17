#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define INFINITY 9999
#define MAX 10

int pathDJK[MAX]={-1};



typedef struct hor_graph
{
    int data;
    int weight;
    struct hor_graph *hgnext;
}hg;

typedef struct ver_graph
{
    int data;
    int count;
    int status;
    int countspan;
    struct ver_graph *down;
    struct hor_graph *vgnext;
}vg;




vg *vptr = NULL; //points to starting vertex of list;
vg *sptr = NULL; //pointer to spanning tree;

vg* createVGnode(int n)
{

    vg *nptr;
    nptr = (vg*)malloc(sizeof(vg));
    if(nptr)
    {
        nptr->data = n;
        nptr->count = 0;
        nptr->status = 1;
        nptr->countspan = 0;
        nptr->down = NULL;
        nptr->vgnext = NULL;
    }

    return nptr;
}


hg* createHGnode(int n , int w)
{
    hg *nptr;
    nptr = (hg*)malloc(sizeof(hg));
    if(nptr)
    {
        nptr->data = n;
        nptr->weight = w;
        nptr->hgnext  = NULL;
    }

    return nptr;
}



vg* insert(vg* vptr , vg *nptr) //insert at starting
{
    if(vptr == NULL)
    {
        vptr = nptr;
    }
    else
    {
        nptr->down = vptr;
        vptr = nptr;
    }
    return vptr;
}

vg* insertSpan(vg* sptr , vg *nptr)
{
    vg *ptr = sptr;
    if(sptr == NULL)
    {
        sptr = nptr;
    }
    else
    {
        while(ptr->down != NULL)
        {
            ptr = ptr->down;
        }
        ptr->down = nptr;
    }
    return sptr;
}

void addEdgeSpan(int s , int e , int w , vg* sptr)
{
    hg *hptr;
    vg *temp;

    temp = sptr;
    int flag = 0;
        while(temp != NULL && flag == 0)
        {
            if(temp->data == s)
            {
                flag = 1;
            }
            else
            {
                temp = temp->down;
            }
        }

        hptr = createHGnode(e , w);
        if(temp->countspan == 0)
        {
            temp->vgnext = hptr;
            temp->countspan = 1;
            temp->count = 1;
        }
        else
        {
            hptr->hgnext = temp->vgnext;
            temp->vgnext = hptr;
        }
}

void displaySpan(vg*sptr)
{
    vg *ptr = sptr;
    hg *p;
    while(ptr!=NULL)
    {
        printf("\n%d -> ",ptr->data);
        p = ptr->vgnext;
        while(p!=NULL)
        {
            printf("%d , ",p->data);
            p = p->hgnext;
        }
        ptr = ptr->down;
        printf("\n");
    }
}



void listfromfile()
{
    int u , v , i = 0 , c = 0 , min , flag = 0 , pos , pp , count ,w;

    vg *ptr , *nptr;
    //hg *hptr , *minptr;


    //sptr = NULL;

    int n;
    FILE *fp;
   // ptrthis = malloc(sizeof(struct medlem));
    //ptrfirst = ptrthis;
    if( (fp = fopen("file.txt", "r")) == NULL)
    {
        printf("No such file\n");
        exit(1);
    }

   rewind(fp);
   //int num = getw(fp);
   int num;
   fscanf(fp,"%d",&num);
   int fl=0;
   while(num != -9876)
    {
        //int u = n;
            nptr = createVGnode(num);
            sptr = insertSpan(sptr , nptr);

            //num = getw(fp);
            fscanf(fp,"%d",&num);


        //fscanf(fp,"%d",&n);

    }
    ptr = sptr;
    while(fscanf(fp,"%d",&num) != EOF)
    {
            int u = num;
            fscanf(fp,"%d",&num);
            while(num != -9876)
            {
                    int v = num;
                    fscanf(fp,"%d",&num);
                    int w = num;
                    addEdgeSpan(u , v , w , sptr);
                    //addEdgeSpan(v , u , w , sptr);
                    fscanf(fp,"%d",&num);
            }



    }  // printf("%d\n", n);


    fclose(fp);
    displaySpan(sptr);
    vptr = sptr;
    displaySpan(vptr);
}


void writeINfile()
{
    vg *ptr = vptr;
    hg *p;
    FILE *fp;
    int endOfInt = -9876;
   // ptrthis = malloc(sizeof(struct medlem));
    //ptrfirst = ptrthis;
    if( (fp = fopen("file.txt", "w")) == NULL)
    {
        printf("No such file\n");
        exit(1);
    }
    if(ptr == NULL)
    {
        printf("NULL\n");
        exit(1);
    }
    while(ptr!=NULL)
    {
        //fwrite(ptr, sizeof(*ptr), 1, fp);
        fprintf(fp," %d",ptr->data);
        //putw(ptr->data,fp);
        ptr=ptr->down;

    }
    fprintf(fp,"%d",-9876);
    //putw(endOfInt , fp);
    ptr = vptr;
    while(ptr!=NULL)
    {
        fprintf(fp," %d",ptr->data);
        //putw(ptr->data,fp);
        p = ptr->vgnext;
        while(p!=NULL)
        {
            fprintf(fp," %d",p->data);
            //putw(p->data,fp);
            fprintf(fp," %d",p->weight);
            //putw(p->weight,fp);
            p = p->hgnext;
        }
        fprintf(fp,"%d",-9876);
         //putw(endOfInt , fp);
        ptr = ptr->down;

    }

    fclose(fp);
}

void addNode()
{
    int n=0;
    vg *nptr;

    printf("enter node/(s)->(integers) in graph\n  -1 to stop\n");
    while(n!=-1)
    {
        scanf("%d",&n);
        if(n!=-1)
        {
            nptr = createVGnode(n);
            vptr = insert(vptr,nptr);
        }
    }
}

void addEdge(int s , int e , int w , vg* vptr)
{
    hg *hptr;
    vg *temp;
    temp = vptr;
    int flag = 0;
        while(temp != NULL && flag == 0)
        {
            if(temp->data == s)
            {
                flag = 1;
            }
            else
            {
                temp = temp->down;
            }
        }

        flag =0;
        hg *hgtemp = temp->vgnext;
        while(hgtemp != NULL && flag == 0)
        {
            if(hgtemp->data == e)
            {
                flag = 1;
            }
            else
            {
                hgtemp = hgtemp->hgnext;
            }
        }
        if(flag)
        {
            printf("\n edge between %d and %d already exists\n",s,e);
        }

        else
        {
            hptr = createHGnode(e , w);
            if(temp->count == 0)
            {
                temp->vgnext = hptr;
                temp->count = 1;
            }
            else
            {
                hptr->hgnext = temp->vgnext;
                temp->vgnext = hptr;
            }
        }



}

void changeWeight(int s , int e , int w , vg* sptr)
{
    hg *hptr;
    vg *temp;

    temp = sptr;
    int flag = 0;
        while(temp != NULL && flag == 0)
        {
            if(temp->data == s)
            {
                flag = 1;
            }
            else
            {
                temp = temp->down;
            }
        }

        flag =0;
        hg *hgtemp = temp->vgnext;
        while(hgtemp != NULL && flag == 0)
        {
            if(hgtemp->data == e)
            {
                hgtemp->weight = w;
                flag = 1;
            }
            else
            {
                hgtemp = hgtemp->hgnext;
            }
        }
}


void display(vg*vptr)
{
    vg *ptr = vptr;
    hg *p;
    while(ptr!=NULL)
    {
        printf("\n%d -> ",ptr->data);
        p = ptr->vgnext;
        while(p!=NULL)
        {
            printf("%d , ",p->data);
            p = p->hgnext;
        }
        ptr = ptr->down;
        printf("\n");
    }
}


void deleteEdge(int start , int end)
{
    int flag = 0;
    vg *vtemp;
    hg *htemp , *prevhtemp;

    vtemp = vptr;
    while(vtemp != NULL && flag == 0)
    {
        if(vtemp->data == start)
        {
            flag = 1;
        }
        else
        {
            vtemp = vtemp->down;
        }
    }

    htemp = vtemp->vgnext;
    prevhtemp = htemp;
    while(htemp != NULL && flag == 1)
    {
        if(htemp->data == end)
        {
            if(htemp == vtemp->vgnext)
            {
                vtemp->vgnext = htemp->hgnext;
                free(htemp);
                flag = 0;
            }

            else
            {
                prevhtemp->hgnext = htemp->hgnext;
                free(htemp);
                flag = 0;
            }
        }

        else
        {
            prevhtemp = htemp;
            htemp = htemp->hgnext;
        }
    }

    if(flag == 1)
    {
        printf("\n no edge exists between %d and %d\n",start,end);
    }
}

vg* deleteNode()
{
    int n , flag = 0;
    vg *vtemp , *prevvtemp;
    printf("enter the node to delete\n");
    scanf("%d",&n);

    vtemp = vptr;
    prevvtemp = vtemp;

    while(vtemp != NULL && flag == 0)
    {
        if(vtemp->data == n)
        {
            flag = 1;
        }

        else
        {
            prevvtemp = vtemp;
            vtemp = vtemp->down;
        }
    }

    if(flag == 1)
    {
        while(vtemp->vgnext != NULL)
        {
            deleteEdge(n , (vtemp->vgnext)->data);
        }
        if(vtemp == vptr)
        {
            vptr = vtemp->down;
        }
        else
        {
             prevvtemp->down = vtemp->down;
        }

        free(vtemp);
        vtemp = vptr;
        while(vtemp != NULL)
        {
            deleteEdge(vtemp->data,n);
            vtemp = vtemp->down;
        }
    }

    if(flag == 0)
    {
        printf("No Node %d exists\n",n);
    }

    return vptr;
}


int countNodes()
{
    vg *ptr = vptr;
    int count = 0;
    while(ptr != NULL)
    {
        count++;
        ptr = ptr->down;
    }
    return count;
}

int findCost(int s , int d)
{
    vg *ptr = vptr;
    int flag=0;
    int retVal = 0;
    while(ptr != NULL && flag==0)
    {
        if(ptr->data == s)
        {
            flag = 1;
        }

        else
        {
            ptr = ptr->down;
        }
    }

    flag = 0;
    if(ptr != NULL)
    {
        hg *hptr = ptr->vgnext;
        while(hptr != NULL &&flag == 0)
        {
            if(hptr->data == d)
            {
                retVal = hptr->weight;
                flag = 1;
            }

            else
            {
                hptr = hptr->hgnext;
            }
        }
    }
    return retVal;
}

int dijkstra(int startnode,int targetNode)
{
    int n=countNodes();
    int cost[MAX][MAX],distance[MAX],pred[MAX];
    int visited[MAX],count,mindistance,nextnode,i,j;
    int costEdge;
    int ret=0;

    //pred[] stores the predecessor of each node
    //count gives the number of nodes seen so far
    //create the cost matrix
    /*for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            if(G[i][j]==0)
                cost[i][j]=INFINITY;
            else
                cost[i][j]=G[i][j];*/

    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            costEdge = findCost(i , j);
            if(costEdge == 0)
            {
                //printf("\nCostEdge value = 0\n");
                cost[i][j]=INFINITY;
            }
            else
            {
                cost[i][j]=costEdge;
            }
        }
    }

    //initialize pred[],distance[] and visited[]
    for(i=0;i<n;i++)
    {
        distance[i]=cost[startnode][i];
        pred[i]=startnode;
        visited[i]=0;
    }

    distance[startnode]=0;
    visited[startnode]=1;
    count=1;

    while(count<n-1)
    {
        mindistance=INFINITY;

        //nextnode gives the node at minimum distance
        for(i=0;i<n;i++)
            if(distance[i]<mindistance&&!visited[i])
            {
                mindistance=distance[i];
                nextnode=i;
            }

            //check if a better path exists through nextnode
            visited[nextnode]=1;
            for(i=0;i<n;i++)
                if(!visited[i])
                    if(mindistance+cost[nextnode][i]<distance[i])
                    {
                        distance[i]=mindistance+cost[nextnode][i];
                        pred[i]=nextnode;
                    }
        count++;
    }

    //print the path and distance of each node
    for(i=0;i<n;i++)
        if(i!=startnode)
        {
           // printf("\nDistance of node%d=%d",i,distance[i]);
            //printf("\nPath=%d",i);

            j=i;
            do
            {
                j=pred[j];
                //printf("<-%d",j);
            }while(j!=startnode);
      }

    count=1;

    while(count<n-1)
    {
        mindistance=INFINITY;

        //nextnode gives the node at minimum distance
        for(i=0;i<n;i++)
            if(distance[i]<mindistance&&!visited[i])
            {
                mindistance=distance[i];
                nextnode=i;
            }

            //check if a better path exists through nextnode
            visited[nextnode]=1;
            for(i=0;i<n;i++)
                if(!visited[i])
                    if(mindistance+cost[nextnode][i]<distance[i])
                    {
                        distance[i]=mindistance+cost[nextnode][i];
                        pred[i]=nextnode;
                    }
        count++;
    }

    int k=0;
    //print the path and distance of each node
    for(i=0;i<n;i++)
    {
        if(i!=startnode)
        {
            if(i == targetNode)
            {
                ret = distance[i];
                printf("\nDistance of node%d=%d",i,distance[i]);
                printf("\nPath=%d",i);

                j=i;
                do
                {
                    j=pred[j];
                    pathDJK[k++]=j;
                    printf("<-%d",j);
                }while(j!=startnode);
            }

        }
    }
    return ret;
}

