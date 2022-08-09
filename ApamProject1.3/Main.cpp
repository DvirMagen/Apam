#include <sstream>
#include <vector>
#include "DisjointSet.h"
#include "MinPriorityQueue.h"
#include "VerticalGraph.h"
using namespace std;

#include <cstdlib>
#include <iostream>
#include <ostream>
#include <fstream>
#include <string>

/*Check functions*/
bool isNumber(string s);
bool is_Negative_Number(string s);

/*Graph Functions*/
void createEdgeToGraph(string edgeLine, VerticalGraph &graph, ofstream &output_file);
void edgeToRemove(string edgeLine, VerticalGraph &graph, ofstream &output_file);
void graph_to_array(VerticalGraph graph, Edge* &edges_arr);

/*QuickSort Implement*/
int partition(Edge* &edges_arr, int start, int end);
void quickSort(Edge* &edges_arr, int start, int end);

/*Prim - Kruskal Algorithm*/
int primAlgorithm(VerticalGraph graph, bool& mst, ofstream &output_file);
int kruskalAlgorithm(VerticalGraph graph, bool& mst, ofstream &output_file);


void main(int argc, char* argv[])
{
    string txt;
    int n = 0;
    int m = 0;
    int prim_calc;
    int _kruskal_calc;
    int kruskal_calc;
    bool mst_prim = true;
    bool mst_kruskal = true;
    bool mst_kruskal_b = true;
    VerticalGraph graph;
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " <test_string>" << std::endl;
        return;
    }
    else
    {
        const char* input_filename = argv[1];
        const char* output_filename = argv[2];
    	ifstream read_file;
        ofstream output_file;
        bool ok = false;
        read_file.open(input_filename);
        output_file.open(output_filename);
        if(!(read_file && output_file))
        {
            cout << "Files not exists! " << endl;
            exit(1);
        }
        int i = 0;
        while (getline(read_file, txt)) {
            
            if (i == 0)
            {
                if (!isNumber(txt))
                {
                    output_file << "Invalid input";
                    cout << "Invalid input";
                    output_file.close();
                    read_file.close();
                    exit(1);
                }
                n = stoi(txt);
            }
            else if (i == 1)
            {
                if (!isNumber(txt))
                {
                    output_file << "Invalid input";
                    cout << "Invalid input";
                    output_file.close();
                    read_file.close();
                    exit(1);
                }
                m = stoi(txt);
                graph.makeEmptyGraph(n, m);
            }
            else if (1 < i && i <= m + 1)
            {
                createEdgeToGraph(txt, graph, output_file);
                if (i == m + 1)
                {
                    kruskal_calc = kruskalAlgorithm(graph, mst_kruskal, output_file);
                    prim_calc = primAlgorithm(graph, mst_prim, output_file);
                }
            }
            else if (i > m + 1)
            {
                edgeToRemove(txt, graph, output_file);
               _kruskal_calc = kruskalAlgorithm(graph,mst_kruskal_b, output_file);
               ok = true;
            }
            i++;
        }
        if(i == 0 || !ok)
        {
            cout << "Invalid input" ;
            output_file << "Invalid input";
            read_file.close();
            output_file.close();
            exit(1);
        }
        else
        {
	        if(ok)
	        {
                output_file << "Kruskal ";
                cout << "Kruskal ";
	        	if (mst_kruskal)
                {
                    cout << kruskal_calc << endl;
                    output_file << kruskal_calc << endl;
                }
                else
                {
                    cout << "No MST" << endl;
                    output_file << "No MST" << endl;
                }
                cout << "Prim ";
                output_file << "Prim ";
                if (mst_prim)
                {
                    cout << prim_calc << endl;
                    output_file << prim_calc << endl;
                }
                else
                {
                    cout << "No MST" << endl;
                    output_file << "No MST" << endl;
                }
                cout << "Kruskal2 ";
                output_file << "Kruskal2 ";
                if (mst_kruskal_b) 
                {
                    cout << _kruskal_calc << endl;
                    output_file << _kruskal_calc << endl;
                }
                else
                {
                    cout << "No MST" << endl;
                    output_file << "No MST" << endl;
                }
	        }
        }
        read_file.close();
        output_file.close();
    }
}


/*Check Functions*/
bool isNumber(string s)
{
    unsigned int i = 0;
    while(s[i] == ' ')
    {
        i++;
    }
    for(; i < s.length(); i++)
    {
        if(!isdigit(s[i]) )
        {
            return false;
	    }
    }
    return true;
}
bool is_Negative_Number(string s)
{
    unsigned int i = 0;
    while (s[i] == ' ')
    {
        i++;
    }
	if(s[i] == '-')
	{
        i++;
        for (; i < s.length(); i++)
        {
            if (!isdigit(s[i]))
            {
                return false;
            }
        }
        return true;
	}
    return false;
   
}

/*Graph Updates*/
void createEdgeToGraph(string edgeLine, VerticalGraph& graph, ofstream &output_file)
{
    int edge_from_kodkod = 0;
    int edge_to_kodkod = 0;
    int edge_weight = 0;
    int i = 0;
    string current_str;
    stringstream edge_stream(edgeLine);
    while (getline(edge_stream, current_str, ' '))
    {
        if (i == 0)
        {
            if (!isNumber(current_str))
            {
                output_file << "Invalid input";
                cout << "Invalid input";
                output_file.close();
                output_file.close();
                exit(1);
            }
            edge_from_kodkod = stoi(current_str);
            if(edge_from_kodkod > graph.get_vertex_size())
            {
                output_file << "Invalid input";
                cout << "Invalid input";
                output_file.close();
                output_file.close();
                exit(1);
            }
        }
        else if (i == 1)
        {
            if (!isNumber(current_str))
            {
                output_file << "Invalid input";
                cout << "Invalid input";
                output_file.close();
                output_file.close();
                exit(1);
            }
            edge_to_kodkod = stoi(current_str);
            if (edge_to_kodkod > graph.get_vertex_size())
            {
                output_file << "Invalid input";
                cout << "Invalid input";
                output_file.close();
                output_file.close();
                exit(1);
            }
        }
        else if (i == 2)
        {
            if (!isNumber(current_str) && !is_Negative_Number(current_str))
            {
                output_file << "Invalid input";
                cout << "Invalid input";
                output_file.close();
                output_file.close();
                exit(1);
            }
            edge_weight = stoi(current_str);
        }
        i++;
    }
    if(i != 3)
    {
        output_file << "Invalid input";
        cout << "Invalid input";
        output_file.close();
        output_file.close();
        exit(1);
    }
    if (graph.isAdjacent(edge_from_kodkod, edge_to_kodkod))
    {
        output_file << "Invalid input";
        cout << "Invalid input";
        output_file.close();
        output_file.close();
        exit(1);
    }
    graph.addEdge(edge_from_kodkod, edge_to_kodkod, edge_weight);
    Edge edge = Edge(edge_from_kodkod, edge_to_kodkod, edge_weight);
}
void edgeToRemove(string edgeLine, VerticalGraph& graph, ofstream &output_file)
{
    int edge_from = 0;
    int edge_to = 0;
    int i = 0;
    string current_str;
    stringstream edge_stream(edgeLine);
    while (getline(edge_stream, current_str, ' '))
    {
        if (i == 0)
        {
            if (!isNumber(current_str))
            {
                output_file << "Invalid input";
                cout << "Invalid input";
                output_file.close();
                output_file.close();
                exit(1);
            }
            edge_from = stoi(current_str);
        }
        else if (i == 1)
        {
            if (!isNumber(current_str))
            {
                output_file << "Invalid input";
                cout << "Invalid input";
                output_file.close();
                output_file.close();
                exit(1);
            }
            edge_to = stoi(current_str);
        }
        i++;
    }
    if (i != 2)
    {
        output_file << "Invalid input";
        cout << "Invalid input";
        output_file.close();
        output_file.close();
        exit(1);
    }
    if (graph.isAdjacent(edge_from, edge_to))
    {
        graph.removeEdge(edge_from, edge_to);
    }
    else
    {
        output_file << "Invalid input";
        cout << "Invalid input";
        output_file.close();
        output_file.close();
        exit(1);
    }
    graph.getAdjList(edge_from);
}
void graph_to_array(VerticalGraph graph, Edge* &edges_arr)
{
    int j = 0;
    for (int i = 1; i <= graph.get_vertex_size(); i++)
    {
        List* lst = graph.getAdjList(i);
        Node* node = lst->head;
        while (node != nullptr)
        {
            edges_arr[j].set_source_vertex(node->edge.get_source_vertex());
            edges_arr[j].set_target_vertex(node->edge.get_target_vertex());
            edges_arr[j].set_weight(node->edge.get_weight());
            j++;
            node = node->next;
        }
    }
}

/*QuckSort Implement*/
int partition(Edge* &edges_arr, int start, int end)
{

    int pivot = edges_arr[start].get_weight();

    int count = 0;
    for (int i = start + 1; i <= end; i++) {
        if (edges_arr[i].get_weight() <= pivot)
            count++;
    }
    int pivotIndex = start + count;
    swap(edges_arr[pivotIndex], edges_arr[start]);
    int i = start, j = end;
    while (i < pivotIndex && j > pivotIndex) 
    {
        while (edges_arr[i].get_weight() <= pivot)
        {
            i++;
        }
        while (edges_arr[j].get_weight() > pivot) {
            j--;
        }
        if (i < pivotIndex && j > pivotIndex) {
            swap(edges_arr[i++], edges_arr[j--]);
        }
    }

    return pivotIndex;
}
void quickSort(Edge* &edges_arr, int start, int end)
{
    if (start >= end)
        return;
    int p = partition(edges_arr, start, end);
    quickSort(edges_arr, start, p - 1);
    quickSort(edges_arr, p + 1, end);
}

/*Prim - Kruskal Algorithm*/
int primAlgorithm(VerticalGraph graph, bool& mst, ofstream &output_file)
{
    int n = graph.get_vertex_size();
    MinPriorityQueue queue;
    bool* inT = new bool[n + 1];
    Edge* min_parent_vertex_array = new Edge[n + 1]; /*source_vertex - parent_vertex*/
    min_parent_vertex_array[1].set_weight(0);             /*weight - min_weight*/
    min_parent_vertex_array[1].set_source_vertex(-1); /*target_vertex - vertex_index*/
    min_parent_vertex_array[1].set_target_vertex(1);
    inT[1] = false;
    for (int i = 2; i <= n; i++)
    {
        min_parent_vertex_array[i].set_source_vertex(-1);
        min_parent_vertex_array[i].set_weight(INT_MAX);
        min_parent_vertex_array[i].set_target_vertex(i);
        inT[i] = false;
    }
    queue.BuildHeap(min_parent_vertex_array + 1, n);
    while (!queue.IsEmpty())
    {
        Edge u = queue.DeleteMin(output_file);
        inT[u.get_source_vertex()] = true;
        List* u_lst = graph.getAdjList(u.get_source_vertex());
        Node* v = u_lst->head;
        while (v != nullptr)
        {
            if (!inT[v->edge.get_target_vertex()] && v->edge.get_weight() < min_parent_vertex_array[v->edge.get_target_vertex()].get_weight())
            {
                min_parent_vertex_array[v->edge.get_target_vertex()].set_weight(v->edge.get_weight());
                min_parent_vertex_array[v->edge.get_target_vertex()].set_source_vertex(u.get_source_vertex());
                queue.DecreaseKey(min_parent_vertex_array[v->edge.get_target_vertex()].get_weight(), v->edge.get_target_vertex(), output_file);
            }
            v = v->next;
        }
    }
    int sum = 0;
    int temp = 0;
    for (int j = 1; j <= n; j++)
    {
        if (min_parent_vertex_array[j].get_source_vertex() == -1)
            temp++;
        if (min_parent_vertex_array[j].get_weight() != INT_MAX)
        {
            sum += min_parent_vertex_array[j].get_weight();
        }
    }
    if (temp != 1)
    {
    	mst = false;
    }
    return sum;
}
int kruskalAlgorithm(VerticalGraph graph, bool& mst, ofstream &output_file)
{
    int u_tag;
    int v_tag;
    vector<Edge> edge_set;
    DisjointSet uf_set(graph.get_vertex_size());
    Edge* edge_arr = new Edge[graph.get_edges_size()];
    graph_to_array(graph, edge_arr);
    quickSort(edge_arr, 0, graph.get_edges_size()-1);
    for(int i = 0; i< graph.get_edges_size(); i++)
    {
        u_tag = uf_set.find_P_vertex(edge_arr[i].get_source_vertex());
        v_tag = uf_set.find_P_vertex(edge_arr[i].get_target_vertex());
        if(u_tag != v_tag)
        {
            edge_set.push_back(edge_arr[i]);
            uf_set.union_vertex(u_tag, v_tag);
        }
    }
    int sum = 0;
    for(Edge e : edge_set)
    {
        if(e.get_weight() != INT_MAX)
			sum += e.get_weight();
    }
    if (edge_set.size() != graph.get_vertex_size()-1)
    {
        mst = false;
    }
    return sum;
}
