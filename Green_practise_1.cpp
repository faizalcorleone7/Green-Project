#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int threshold=5,Distance=0,no,source,sum=0;
typedef struct Node
{
	int distance;
	int number;
	vector<int> datapacket;							//set of datapackets already with the node
	vector<int> demand[2];							//0->datapacket number, 1->no of times demanded
}node;
typedef struct dNode				//for dijkstra's algorithm
{
	int distance;					
	bool marked;
}noded;
bool check(vector<int> v,int j)				//for dijkstra's algorithm
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
			if (check(marked_vertices,i)==false)
			{
			if (dijk[row][i].distance>0)
			{
			dijk[row][i].distance=dijk[row][i].distance+distance; 			    
			    if (dijk[source][i].distance!=-1)
				{dijk[source][i].distance=min(dijk[row][i].distance,dijk[source][i].distance);}
				else
				{
					dijk[source][i].distance=dijk[row][i].distance;
				}		
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
		marked_vertices.push_back(minind);
		c=c+1;		
		row=minind;
		distance=dijk[source][minind].distance;
	}
	return dijk[source][des].distance;
}
node update(node n,vector<int> metadata[])													//dynamic updation
{
	int data;
	for (int i=0;i<n.demand[0].size();i++)
	{
		if (n.demand[1][i]==threshold)
		{
			data=n.demand[0][i];
			n.demand[0].erase(n.demand[0].begin()+i);
			n.demand[1].erase(n.demand[1].begin()+i);
			n.datapacket.push_back(data);
			i--;
		}
	}	
	metadata[data][n.number]=1;
	return n;
};
int transfer(vector<node> n[],int arr[2],vector<int> metadata[])
{	
	vector<int> v[2]; // indexing - 0->node number, 1->distance   ---- for the set of nodes that alredy have the demanded datapacket
	for (int i=0;i<n[arr[0]][arr[0]].datapacket.size();i++)
	{
		if (arr[1]==n[arr[0]][arr[0]].datapacket[i])			//checking if datapacket is already there at the destination node
		{
			cout<<"Already exists"<<endl;
			return 0;
		}
	}
	int exists=0;
	for (int i=0;i<n[arr[0]][arr[0]].demand[0].size();i++)			//checking if node had made an earlier demand for the same datapacket
	{
		if (arr[1]==n[arr[0]][arr[0]].demand[0][i])
		{
			cout<<"Old request"<<endl;
			exists=1;
			n[arr[0]][arr[0]].demand[1][i]++;	
			break;
		}
	}
	if (exists==0)												//if the datapacket has been called for the first time by the node
	{
	cout<<"New request"<<endl;
	n[arr[0]][arr[0]].demand[0].push_back(arr[1]);
	n[arr[0]][arr[0]].demand[1].push_back(1);
	}
	for (int j=0;j<no;j++)									//checking for the closest source of the datapacket
	{		
			if (metadata[arr[1]][j]==1)
			{
				cout<<"Updating vector v"<<endl;
				v[0].push_back(j);
				cout<<"Node "<<j<<" contains the requested datapacket"<<endl;
				v[1].push_back(dijkstra(n,arr[0],j));                  //arr[0] - destination node number, j - potential source node number
				cout<<"Distance from destination node = "<<dijkstra(n,arr[0],j)<<endl;
				n[arr[0]][j].distance=dijkstra(n,arr[0],j);
				n[j][arr[0]].distance=n[arr[0]][j].distance;
			}		
	}
	cout<<"Size of v = "<<v[0].size()<<endl;
	sort(v[1].begin(),v[1].end());
	if (exists==1)
	{
		n[arr[0]][arr[0]]=update(n[arr[0]][arr[0]],metadata);
	}
	return v[1][0];
};
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
			n1.number=j;
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
				cout<<"enter distance between node"<<i<<" and node "<<j<<": ";
				cin>>n[i][j].distance;
				n[j][i].distance=n[i][j].distance;
			}
		}	
	}
	vector<int> meta;
	for (int i=0;i<no;i++)								//calculating number of datapackets
	{
		int n1;
		cout<<"Enter the number of data packets generated at "<<i<<" node: ";
		cin>>n1;
		meta.push_back(n1);
		sum=sum+n1;
	}	
	vector<int> metadata[sum];
	for (int i=0;i<sum;i++)				//metadata initialisation
	{
		for (int j=0;j<sum;j++)
		{			
			metadata[i].push_back(0);
		}
	};
	for (int nodeno=0;nodeno<no;nodeno++)								//entering datapackets that have been generated at each node of the database
	{
		for (int j=0;j<meta[nodeno];j++)
		{
			int datapacketno;
			cout<<"Enter datapacket: "<<endl;
			cin>>datapacketno;
			n[nodeno][nodeno].datapacket.push_back(datapacketno);
			metadata[datapacketno][nodeno]=1;
		}
	}
	int number;
	cout<<"Enter the number of requests: ";
	cin>>number;
	for (int i=0;i<number;i++)
	{
		int arr[2];
		cout<<"Enter destination node number and datapacket respectively: "<<endl;
		cin>>arr[0];  //destination node number
		cin>>arr[1];  //datapacket
		Distance=Distance+transfer(n,arr,metadata); //func1 transfer of datapacket		
		cout<<"Distance covered uptill now = "<<Distance<<endl;
	}
	cout<<"Total distance covered by data transmissions: "<<Distance<<endl;
	return 0;
}
