#ifndef _COMBINATION_HH_
#define _COMBINATION_HH_

#include "metis.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <set>
#include <cmath>
#include <climits>
#include "fileDIstribution.hh"
#include "dfsCombiner.hh"

using namespace std;

class Graph {
public:
    FileDistGenerator *fileDist;
    vector<vector<int> > blockInfo; // node -> block list
    vector<int> networkTopology;
    vector<idx_t> xadj; // nodes
    vector<idx_t> adjncy; // edges
    vector<idx_t> adjwgt; // weight of edges
    vector<idx_t> vwgt; // weight of nodes
    Graph(FileDistGenerator *fd) : fileDist(fd) {};
    ~Graph() {};
    void Convert2Graph();
};

class METISCombiner {
private:
    Graph *graph;
    idx_t nParts; // number of subgraph
    int replicaNum; // number of replicas
    vector<idx_t> parts; // result of metis
    vector<vector<int> > combinedDist; // result of node combination
    vector<map<int, vector<int>> > fileRealNodeTab; // idx: combined node id -> element: fileid -> real node id list
public:
    METISCombiner(Graph *g, idx_t p, int r) : graph(g), nParts(p), replicaNum(r) { combinedDist.resize(nParts); fileRealNodeTab.resize(nParts); };
    ~METISCombiner() { delete graph; };
    void CombineNodes();
    void GenRandomDist();
    void GenMyCombinationDist();
    void GenDFSCombinationDist();
    void SearchForGroups();
    void ShowResult();
    int CalCombination(int m, int n);
};

#endif