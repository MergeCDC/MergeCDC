#include "fileDIstribution.hh"
#include "combination.hh"

using namespace std;

int main() {
    srand(time(0));
    int k = 3, r = 2, nodeNum = 9, fileNum = 30, rackNum = 3;
    // int k = 4, r = 2, nodeNum = 15, fileNum = 36, rackNum = 3;
    // int k = 4, r = 2, nodeNum = 12, fileNum = 36, rackNum = 3;
    // int k = 5, r = 3, nodeNum = 25, fileNum = 100, rackNum = 3;
    // int k = 5, r = 3, nodeNum = 30, fileNum = 100, rackNum = 3;
    // int k = 7, r = 3, nodeNum = 39, fileNum = 105, rackNum = 5;
    // int k = 7, r = 3, nodeNum = 39, fileNum = 105, rackNum = 2;
    // int k = 5, r = 3, nodeNum = 39, fileNum = 100, rackNum = 3;
    // int k = 7, r = 3, nodeNum = 39, fileNum = 105, rackNum = 3;
    // int k = 7, r = 3, nodeNum = 49, fileNum = 105, rackNum = 3;
    FileDistGenerator *fd = new FileDistGenerator(fileNum, nodeNum, k, r, rackNum);
    Graph *g = new Graph(fd);
    g->Convert2Graph();
    METISCombiner *mc = new METISCombiner(g, k, r);
    cout << endl << "METIS combination: " << endl;
    mc->CombineNodes();
    mc->ShowResult();
    mc->SearchForGroups();
    cout << endl << "brute force distribution: " << endl;
    mc->GenDFSCombinationDist();
    mc->SearchForGroups();
    cout << endl << "my combination distribution: " << endl;
    mc->GenMyCombinationDist();
    mc->SearchForGroups();
}