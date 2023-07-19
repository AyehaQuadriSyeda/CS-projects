// graph.h
// < Ayesha Quadri Syeda>
//
// Basic graph class using adjacency matrix representation.  Currently
// limited to a graph with at most 100 vertices.
//
// University of Illinois at Chicago
// CS 251: Fall 2021
// Project #7 - Openstreet Maps
//
#pragma once

#include <iostream>
#include <map>
#include <set>
#include <stdexcept>
#include <vector>

using namespace std;

template <typename VertexT, typename WeightT> class graph {
    private:
// structure for the adjacency list
  struct NodeData {
    WeightT Weight;
    VertexT Vertex;
    bool operator=(const NodeData& other){
      Vertex = other.Vertex;
      Weight = other.Weight;
      return true;
    }
  };

// The adjcency list is made with a map
// Key being VertextT and the element
// being a vector of Nodes, which represent it's neigbhors

  map<VertexT, vector<NodeData>> Vertices;
  vector<VertexT> vertices;

  //
  // _LookupVertex
  //
  // checks if the vertex is found in the map and returns 0 if true, -1 if false
  //
  int _LookupVertex(VertexT v) const {
    if (Vertices.count(v) == 1) {
      return 0;
    }
    // if get here, not found:
    return -1;
  }

    public:
  //
  // default constructor:
  //
  //
  graph() {}

  // copy constructor
  graph(const graph<VertexT, WeightT> &other) {
    this->vertices = other.vertices;
    this->Vertices = other.Vertices;
  }

  // copy operator
  graph &operator=(const graph &other) {
    this->Vertices.clear();
    this->vertices.clear();

    this->vertices = other.vertices;
    this->Vertices = other.Vertices;

    return *this;
  }

  //
  // NumVertices
  //
  // Returns the # of vertices currently in the graph.
  //
  int NumVertices() const { return static_cast<int>(this->Vertices.size()); }

  //
  // NumEdges
  //
  // Returns the # of edges currently in the graph.
  //
  int NumEdges() const {
    int count = 0;

    // loop through each list
    for (auto &a : this->Vertices) {
      count += a.second.size();
    }
    return (count);
  }

  //
  // addVertex
  //
  // Adds the vertex v to the graph. If the vertex already
  // exists in the graph, then false is returned.
  //
  bool addVertex(VertexT v) {
    //
    // is the vertex already in the graph?  If so, we do not
    // insert again otherwise Vertices may fill with duplicates:
    //
    if (_LookupVertex(v) >= 0) {
      return false;
    }

    //
    // if we get here, vertex does not exist 
    // so insert. A new key in the map
    // with an empty vector of NodeData
    // is created.
    //
    this->vertices.push_back(v);
    vector<NodeData> V;
    this->Vertices[v] = V;

    return true;
  }

  //
  // addEdge
  //
  // Adds the edge (from, to, weight) to the graph, and returns
  // true.  If the vertices do not exist false is returned.
  //
  // NOTE: if the edge already exists, the existing edge weight
  // is overwritten with the new edge weight.
  bool addEdge(VertexT from, VertexT to, WeightT weight) {

    // checks if the vertices exist in the map
    if (_LookupVertex(from) < 0) {  // not found:
      return false;
    }
    if (_LookupVertex(to) < 0) {  // not found:
      return false;
    }
    // if the vertices exist and if the edge already exists, 
    // it overwrites and returns true
    NodeData v1;
    for (size_t i = 0; i < this->Vertices.at(from).size(); i++) {
      if (this->Vertices.at(from)[i].Vertex == to) {
        this->Vertices.at(from)[i].Weight = weight;
        return true;
      }
    }

    // if edge doesn't exist, creates a new one and returns true
    v1.Vertex = to;
    v1.Weight = weight;
    this->Vertices[from].push_back(v1);

    return true;
  }

  //
  // getWeight
  //
  // Returns the weight associated with a given edge.  If
  // the edge exists, the weight is returned via the reference
  // parameter and true is returned.  If the edge does not
  // exist, the weight parameter is unchanged and false is
  // returned.
  //
  bool getWeight(VertexT from, VertexT to, WeightT &weight) const {
    if (_LookupVertex(from) < 0) {  // not found:
      return false;
    }
    if (_LookupVertex(to) < 0) {  // not found:
      return false;
    }
    vector<NodeData> n = this->Vertices.at(from);
    for (size_t i = 0; i < n.size(); i++) {
      if (n[i].Vertex == to) {
        weight = n[i].Weight;
        return true;
      }
    }
    return false;
  }

  //
  // neighbors
  //
  // Returns a set containing the neighbors of v, i.e. all
  // vertices that can be reached from v along one edge.
  // Since a set is returned, the neighbors are returned in
  // sorted order; use foreach to iterate through the set.
  //
  set<VertexT> neighbors(VertexT v) const {
    set<VertexT> S;

    if (_LookupVertex(v) < 0) {  // not found:
      return S;
    }

    for (size_t i = 0; i < this->Vertices.at(v).size(); i++) {
      VertexT dest = this->Vertices.at(v)[i].Vertex;
      S.insert(dest);
    }
    return S;
  }

  //
  // getVertices
  //
  // Returns a vector containing all the vertices currently in
  // the graph.
  //
  vector<VertexT> getVertices() const {
    return this->vertices;  // returns a copy:
  }

  //
  // dump
  //
  // Dumps the internal state of the graph for debugging purposes.
  //
  // Example:
  //    graph<string,int>  G(26);
  //    ...
  //    G.dump(cout);  // dump to console

  void dump(ostream &output) const {
    output << "***************************************************" << endl;
    output << "********************* GRAPH ***********************" << endl;

    output << "**Num vertices: " << this->NumVertices() << endl;
    output << "**Num edges: " << this->NumEdges() << endl;

    output << endl;
    output << "**Vertices:" << endl;
    for (int i = 0; i < this->NumVertices(); ++i) {
      output << " " << i << ". " << this->vertices[i] << endl;
    }

    output << endl;
    output << "**Edges:" << endl;
    for (auto a : this->Vertices) {
      output << a.first << ": ";
      for (size_t i = 0; i < a.second.size(); i++) {
        output << "(" << a.first << ", ";
        output << a.second[i].Vertex << ", ";
        output << a.second[i].Weight << ") \t";
      }
      output << endl;
    }
    output << endl;
    output << "**************************************************" << endl;
  }
};
