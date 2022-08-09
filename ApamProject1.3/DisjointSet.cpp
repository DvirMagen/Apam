#include "DisjointSet.h"

/*Constructor*/
DisjointSet::DisjointSet(int set_size) : set_size(set_size)
{
    s_set = new Edge[set_size];
    for (int i = 0; i < set_size; i++)
    {
        makeSet(i + 1);
    }
}
/*Destructor*/
DisjointSet::~DisjointSet()
{
    delete[] s_set;
}

void DisjointSet::makeSet(int v) const
{
    s_set[v-1].set_source_vertex(v);
    s_set[v-1].set_target_vertex(v);
    s_set[v-1].set_weight(INT_MAX);
}

/*Get index of vertex and return the source vertex index*/
int DisjointSet::find_P_vertex(int v)
{
    if (s_set[v-1].get_source_vertex() != v) {

        s_set[v-1].set_source_vertex(find_P_vertex(s_set[v-1].get_source_vertex()));
    }
    return s_set[v-1].get_source_vertex();
}

/*Union 2 vertex(u,v) according to the minimum weight between u and v*/
void DisjointSet::union_vertex(int u, int v)
{
    int u_source = find_P_vertex(u);
    int v_source = find_P_vertex(v);
    if (u_source == v_source)
        return;
    if (s_set[u_source-1].get_weight() < s_set[v_source-1].get_weight()) {
        s_set[v_source-1].set_source_vertex(u_source);
    }
    else if (s_set[u_source-1].get_weight() > s_set[v_source-1].get_weight()) {
        s_set[u_source-1].set_source_vertex(v_source);
    }

    else {
        s_set[v_source-1].set_source_vertex(u_source);
        s_set[u_source-1].set_weight(s_set[v_source-1].get_weight() + s_set[u_source-1].get_weight());
    }
}
