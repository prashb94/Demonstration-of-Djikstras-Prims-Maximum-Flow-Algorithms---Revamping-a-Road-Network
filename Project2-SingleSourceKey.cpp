#include <iostream>
using namespace std;
#include <conio.h>
#include <limits.h>
#include <string.h>
#include <queue>
#define ROW 10
#define COL 10
#define infi 5000 

int graph[ROW][COL],source,minspantree[ROW][COL],mstcost,p[10],d[10],nodes;

class prims
{
   public:
   prims();
   void primsAlgo();
};

// Initialise everything to 0 with a constructor
prims :: prims()
{
     for(int i=0;i<ROW;i++)
       for(int j=0;j<COL;j++)
     {
	 graph[i][j]=0;
	 minspantree[i][j] =0;
	}
}

void createGraph()
{
    int i,j;
    cout<<"Enter Total number of Points : ";
    cin>>nodes;
    cout<<"\n\nEnter Cost Matrix : \n";
    for(i=0;i<nodes;i++)
        for(j=0;j<nodes;j++)
        cin>>graph[i][j];

	for(i=0;i<nodes;i++){
        for(j=0;j<nodes;j++){
           if(graph[i][j]==0)
          graph[i][j]=infi;
        }
    }
}

//Prim's Algorithm
void prims :: primsAlgo()
{
    int selected[ROW],i,j,ne,min,x,y,c1=0,c2=0;
    mstcost = 0;
    for(i=0;i<nodes;i++)
       selected[i]=false;

    selected[0]=true;
    
    ne=0;

    while(ne < nodes-1)
	{
       min=infi;

       for(i=0;i<nodes;i++)
       {
          if(selected[i]==true)
		  {
         	for(j=0;j<nodes;j++)
		 	{
            if(selected[j]==false)
			{
               if(min > graph[i][j])
               {
               min=graph[i][j];
               x=i;
			   y=j;
               }
            }
         	}
          }
       }
       selected[y]=true;
       cout << "\n" << x+1 << " --> " << y+1 << " Cost = " << graph[x][y];
        minspantree[x][y] = graph[x][y];
        minspantree[y][x] = graph[y][x];
        mstcost += graph[x][y];
       ne=ne+1;
    }
    cout << "\nMinimum Total Cost to Revamp the Road Network(Using Prim's Algorithm) : " << mstcost << endl ;

}

class Djikstra
	{
    
        bool mark[10]; 
    public:
        void setval();
        int gtnode();
        void caldist(int graph[ROW][COL]);
        void output();
        void printPath(int);
        friend void KeyRevamp(int*,int,int);
	};

// Initialisation for Djikstra's
void Djikstra::setval()
{
    for(int i = 0 ; i < nodes ; i++) 
	{
        mark[i] = false;
        p[i] = -1;
        d[i] = infi;
    }
    d[source]= 0;
}


int Djikstra::gtnode()
{
    int mindist = infi;
    int n;
    for(int i = 0 ; i < nodes ; i++)
	 {
        if((!mark[i]) && ( mindist >= d[i]))
	    {
            mindist = d[i];
            n = i;
        }
    }
    return n;
}


void Djikstra::caldist(int graph[ROW][COL])
{
    setval();
    int mindist = infi;
    int n;
    int count = 0;
    while(count < nodes) 
	{
        n = gtnode();
        mark[n] = true;
        for(int i = 0 ; i < nodes ; i++)
		 {
            if((!mark[i]) && (graph[n][i]>0) )
			 {
                if(d[i] > d[n]+graph[n][i]) 
				{
                    d[i] = d[n]+graph[n][i];
                    p[i] = n;
                }
            }
        }
        count++;
    } 
}


void Djikstra::printPath(int node)
{
    if(node == source)
        cout << node+1 << " --> ";
    else if(p[node] == -1)
        cout << "No path from " << source+1 << " to " << node+1 << endl;
    else 
	{
        printPath(p[node]);
        cout << node+1 << " --> ";
    }
}


void Djikstra::output()
{
	for(int i = 0; i < nodes; i++)
	 {
        if(i == source)
            cout << source+1 << " --> " << source+1;
        else
            printPath(i);
        cout << " Cost = " << d[i] << endl;
    }
}

/*void AllPairShortestPath(int graph[ROW][COL],int a[ROW][COL])
{
	
	for(int i = 0 ; i < nodes ; i++)
	for(int j = 0 ; j < nodes ; j++)
	{
		a[i][j]=graph[i][j];
		if(a[i][j]==0)
		a[i][j]=infi;
	}
	
	int i,j,k;
	
	for(k = 0 ; k < nodes ; k++)
	for(i = 0 ; i < nodes ; i++)
	for(j = 0 ; j < nodes ; j++)
	if(a[i][j]>a[i][k]+a[k][j])
	a[i][j]=a[i][k]+a[k][j];
	
  cout << "\nAll Pairs Shortest Path Matrix : \n";
	for(int i = 0 ; i < nodes ; i++)
	{
		cout << endl;
	for(int j = 0 ; j < nodes ; j++)
		{
		if(a[i][j]==infi)
		a[i][j]=0;
		cout << a[i][j] << "  ";
		}
	} 

}
*/
void KeyRevamp(int*key,int max,int n)
{
	if(max>=mstcost)
	{
		cout << "\nTotal cost Of Revamping Road Network with a Minimum Spanning Tree is Cheaper!\n";
		return;
	}
	Djikstra*SSSP;
	
	SSSP = new Djikstra;

	int sum = 0;
	
	source = key[0];
	
	SSSP->caldist(minspantree);
	
	SSSP->output();
	
	for(int i = 0 ; i < n ; i++)
      sum+=d[key[i]];
      
	cout << "\nTotal Sum Of Cost Of Shortest Possible Path Between Key Points With the New Revamped road Network = " << sum << endl ;
	int sum1 = sum;
	
	if(sum<=max)
	{
		cout << "\nNo New Roads need to be Revamped between Key points!\n";
		return;
	}
	
	else if(sum>max)
	{
	cout << "\nNew Roads may have to be Revamped to Reduce Total Cost\nHere are all possible combinations of Cheapest paths that can be taken to achieve Cheapest Total Cost :\n";
	
	sum = 0;
	
	SSSP->caldist(graph);
	
	SSSP->output();
	
	for(int i = 0 ; i < n ; i++)
      sum+=d[key[i]];
	
	cout << "\nTotal Sum Of Cost Of Shortest Possible Path Between Key Points(Original Road Network)  = " << sum << endl ;
	
	if(sum1==sum)
	{
		cout << "\nSame Cost!\n";
		return;
	}

	int j;
	
	//Traverse the Path Found by Djikstra's and add every new edge to the minimum spanning tree cost matrix , which connects the key points
	for(int i = 0 ; i < n ; i++)
	{	
	    j = key[i];
		while(p[j]!=source)
		{

				minspantree[p[j]][j] = graph[p[j]][j];
				minspantree[j][p[j]] = graph[j][p[j]];
				
			
			j = p[j];
			
		}
	}
	cout << "\nRoads Revamped ! \n" ;

	}
}

bool bfs(int rGraph[ROW][COL], int s, int t, int parent[])
{
    // Create a visited array and mark all vertices as not visited
    bool visited[nodes];
    memset(visited, 0, sizeof(visited));
 
    // Create a queue, enqueue source vertex and mark source vertex
    // as visited
    queue <int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;
 
    // Standard BFS Loop
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
 
        for (int v=0; v<nodes; v++)
        {
            if (visited[v]==false && rGraph[u][v] > 0)
            {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
 
    // If we reached sink in BFS starting from source, then return
    // true, else false
    return (visited[t] == true);
}
 

int fordFulkerson(int graph1[ROW][COL], int s, int t)
{
    int u, v;
    int rGraph[ROW][COL]; 
    for (u = 0; u < nodes; u++)
        for (v = 0; v < nodes; v++)
             rGraph[u][v] = graph1[u][v];
 
    int parent[nodes];  
 
    int max_flow = 0;  
 
    // Augment the flow while tere is path from source to sink
    while (bfs(rGraph, s, t, parent))
    {
        // Find minimum residual capacity of the edges along the
        // path filled by BFS. Or we can say find the maximum flow
        // through the path found.
        int path_flow = INT_MAX;
        for (v=t; v!=s; v=parent[v])
        {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }
 
        // update residual capacities of the edges and reverse edges
        // along the path
        for (v=t; v != s; v=parent[v])
        {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }
 
        // Add path flow to overall flow
        max_flow += path_flow;
    }
 
    // Return the overall flow
    return max_flow;
}
 

int main()
{
    prims MST;
    createGraph();
    MST.primsAlgo();
    int n,key[5],max,source,sink;
    cout << "\nEnter Number Of Key Points In the City : \n";
    cin >> n;
    cout << "\nEnter Key Points(>=1 and <=" << nodes << ")\nEnter Source Vertex First : \n";
    for(int i = 0 ; i < n ; i++)
    {
	cin >> key[i]; key[i]--;
	}
	cout << "Enter Maximum Amount that Can be Spent On Revamping between Key Points : \n";
	cin >> max;
	KeyRevamp(key,max,n);
	cout << "\nEnter Source And Sink For finding Maximum Flow :\n";
	cin >> source >> sink;
	cout << "\nMaximum Flow for The New Revamped Road Network Shown Above = " << fordFulkerson(minspantree,source-1,sink-1);
	getch();
    return 0;
}
