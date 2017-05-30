#include<iostream>					//Dijkstra's algorithm implementation
#include<vector>
#include<algorithm>
using namespace std;
typedef struct Node
{
	int distance;							//0->datapacket number, 1->no of times demanded
}node;
typedef struct dNode
{
	int distance;					
	bool marked;
}noded;
int threshold=5,no;
bool check(vector<int> v,int j)
{
	for (int i=0;i<v.size();i++)
	{
		if (v[i]==j)
		{
			return true;
		}	
	}
return false;	
};
int dijkstra(vector<node> n[],int des,int source)
{
	vector<int> marked_vertices;
	marked_vertices.push_back(source);
	vector<noded> dijk[no];
	int min1=0;
	for (int i=0;i<no;i++)
	{
		for (int j=0;j<no;j++)
		{	
			noded n1;
			n1.marked=false;
			n1.distance=n[i][j].distance;			
			if (n1.distance>=min1)
			{
				min1=n1.distance;
			}
			dijk[i].push_back(n1);		
		}
	}			
	dijk[source][source].marked=true;					//marking starting point
	int c=0,row=source,distance=0,minind=0;
	while(c!=no)
	{
		min1=10000;
		minind=0;
		int c1=0;
		for (int i=0;i<no;i++)
		{
			if (dijk[row][i].distance>0 && check(marked_vertices,i)==false)
			{
				c1=c1+1;
			}
		}
		if (c1==0)
		{
			row=source;
			distance=0;
		}
		for (int i=0;i<no;i++)
		{	
			if ( check(marked_vertices,i)==false)
			{
			if (dijk[row][i].distance>0)
			{
			dijk[row][i].distance=dijk[row][i].distance+distance; 
			    //updating distance
			    if (dijk[source][i].distance!=-1)
				{dijk[source][i].distance=min(dijk[row][i].distance,dijk[source][i].distance);}
				else
				{
					dijk[source][i].distance=dijk[row][i].distance;
				}
				cout<<i<<" = "<<dijk[source][i].marked<<" "<<endl;
			}
			else
			{
				if (dijk[row][i].distance<0)
				{
					dijk[row][i].distance=dijk[source][i].distance;
				}
			}
			}
		}
		cout<<"Checking updation"<<endl;
		cout<<"source = "<<endl;
		for (int i=0;i<no;i++)
		{
			cout<<dijk[source][i].distance<<" ";						
		}
		cout<<endl;
		cout<<"row = "<<endl;
		for (int i=0;i<no;i++)
		{
			cout<<dijk[row][i].distance<<" ";
		}
		cout<<endl;	
		for (int i=0;i<no;i++)									//finding minimum
		{
			if (check(marked_vertices,i)==false && dijk[row][i].distance>0 && dijk[row][i].distance<min1)
			{
				minind=i;
				min1=dijk[row][i].distance;
			}
		}
		dijk[row][minind].marked==true;
		dijk[source][minind].marked==true;
		cout<<"Marked = "<<minind<<" node"<<endl;
		marked_vertices.push_back(minind);
		c=c+1;		
		row=minind;
		distance=dijk[source][minind].distance;
		cout<<"Distance = "<<distance<<endl;
	}
	return dijk[source][des].distance;
}
int main()
{	
	cout<<"Enter the number of nodes of the graph: ";
	cin>>no;
	vector<node> n[no];
	for (int i=0;i<no;i++)							//graph initialisation
	{
		for (int j=0;j<no;j++)
		{
			node n1;
			n1.distance=0;
			n[i].push_back(n1);
		}
	}
	for (int i=0;i<no;i++)                            //graph creation
	{
		for (int j=i;j<no;j++)
		{
			if (i==j)
			{n[i][j].distance=0;}
			else
			{
				cout<<"enter distance between node"<<i<<" and node "<<j<<"(if not directly connected, give input as -1): ";
				cin>>n[i][j].distance;
				n[j][i].distance=n[i][j].distance;
			}
		}	
	}
	cout<<"Printing the graph"<<endl;
	for (int i=0;i<no;i++)
	{
		for (int j=0;j<no;j++)
		{
			cout<<n[i][j].distance<<" ";
		}
		cout<<endl;
	}	
	int start,end;
	cout<<"Enter the start node number: "<<endl;
	cin>>start;
	cout<<"Enter the last node number: "<<endl;
	cin>>end;
	cout<<"Distance betwenn start and end node is = ";
	cout<<dijkstra(n,start,end);
	return 0;
}



