

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <ctime>
struct Node {
    double x;
    double y;
	Node(double a, double b) : x(a), y(b) {}
	Node() : x(0), y(0) {}
};
struct Edge {
    int u;
    int v;
    double cost;
	Edge(int a, int b, double c) : u(a), v(b), cost(c) {}
	Edge() : u(-1), v(-1), cost(0.0) {}
};
class Graph {
public:
    std::vector<Node> nodes;
	std::vector<Edge> edges;
	void addNode(const Node& node) {
        nodes.push_back(node);
    }
    void addEdge(const Edge& edge) {
        edges.push_back(edge);
	}
};
bool load(const std::string& path,Graph& g){
    std::ifstream in(path); //plik do czttania
    if (!in) return false;
    int n;
    in >> n;
    if (!in || n <=0) return false;
	g.nodes.clear();
	g.edges.clear();
	g.nodes.resize(n); 
	for (int i = 0; i < n; i++) { //wczytanie wierzcholkow
       in>>g.nodes[i].x >> g.nodes[i].y;
	   if (!in) return false;
    }
	int e; //krawedzie
    in >> e;
    if (!in || e < 0) { return false; }
	g.edges.resize(e);
    for (int k = 0; k < e; k++) { //wczytanie krawedzi
        in >> g.edges[k].u >> g.edges[k].v >> g.edges[k].cost;
        if (!in) return false;
    }
    return true;
}
class UnionFind {
private:
    std::vector<int> parent, rank;
    bool userank = false;
	bool kompresja = false;

public:
    //find call ile razy wywolano find , find count ile razy przeszedl po parent 
    long long findcall = 0;
	long long findcount = 0;
    UnionFind(int n,bool useRank=true,bool compression= true) {
        parent.resize(n);
        rank.resize(n, 0);
        userank=useRank;
		kompresja=compression;
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            rank[i] = 0;
        }

    }
    void Unianorank(int i, int j) {  ///unia bez rangi  
        
        parent[i] = j;
	}
    void Uniabyrank(int i, int j) {  ///unia wg rangi
            if (rank[i] < rank[j]) {
                parent[i] = j;
            }
            else if (rank[j] < rank[i]) {
                parent[j] = i;
            }
            else {
                parent[j] = i;
                rank[i]++;
            }
        
    }
    void Unia(int i, int j) {
        if (userank) {
            Uniabyrank(i, j);
        }
        else {
            Unianorank(i, j);
        }
    }
    int Findbezkompresji(int i) {
        if (i == parent[i]) return i;
        findcount++;
		return Findbezkompresji(parent[i]);
    }
    
    int Findzkompresja(int i){
        if (i == parent[i]) return  i;
        findcount++;
		int root = Findzkompresja(parent[i]);
        if (root != parent[i]) {
            parent[i] = root;
        }
            return root;
        
        }
    int Find(int i) {
        findcall++;
        if (kompresja) {
            return Findzkompresja(i);
        }
        else {
            return Findbezkompresji(i);
        }
    }
};
bool cmp(const Edge& a, const Edge& b) {
    return a.cost < b.cost;
}
int kruskal(const Graph& graph,bool userank,bool kompresja,double& totcost,double& czassortowania,double& czaskruskala,long long& findcount,long long& findcall) {
	totcost = 0.0;
	czaskruskala = 0;
    czassortowania = 0;
    findcount = 0;
    findcall = 0;
    int count = 0;
	size_t n = graph.nodes.size();
    if (n == 0) {
        std::cout << "Graf pusty\n";
        return 0;
    }
	std::vector<Edge> edges=graph.edges;
    clock_t t1 = clock();
	std::sort(edges.begin(), edges.end(), cmp);
    clock_t t2 = clock();
    czassortowania= 1000.0*(double)((t2 - t1)/ (double)CLOCKS_PER_SEC); //msekundy
	//for (int i = 1; i < edges.size(); i++) { //insertion sort
 //       Edge key = edges[i];
 //       int j = i - 1;
 //       while (j >= 0 && edges[j].cost > key.cost) {
	//		.edges[j + 1] = edges[j];
 //           j = j - 1;

 //       }
	//	graph.edges[j + 1] = key;
 //   }
	UnionFind uf(n,userank,kompresja);
    clock_t t3 = clock();
    for(int i=0;i<edges.size();i++){ //dla kazdej krawedzi
        int u_root=uf.Find(edges[i].u);
        int v_root = uf.Find(edges[i].v);
        if(u_root!=v_root){
            uf.Unia(u_root,v_root);
            count++;
			totcost +=edges[i].cost;
			if (count == graph.nodes.size() - 1) break;
        }
	}
    clock_t t4 = clock();
    czaskruskala= 1000.0*(double)((t4 - t3) / (double)CLOCKS_PER_SEC); //msekundy
    findcount = uf.findcount;
    findcall = uf.findcall;
	return count;
}
void testy(const Graph& g) {
    double cost,sortowanie,kruskalczas;
    long long  findcount,findcall;
    int edges;
    //bez rangi i bez kompresji
	edges = kruskal(g, false, false, cost, sortowanie, kruskalczas, findcount,findcall);
	std::cout << "Bez rangi i bez kompresji: \n";
	std::cout << "Liczba krawedzi w MST: " << edges << ", koszt: " << cost << ", czas sortowania: " << sortowanie << "ms, czas petli for Kruskala: " << kruskalczas << "ms, liczba wywolan Find(): " << findcall<<" \nliczba krokow find(liczba przejsc po parent): "<<findcount<< "\n";
	//z rangą i bez kompresji
	edges = kruskal(g, true, false, cost, sortowanie, kruskalczas, findcount,findcall);
	std::cout << "Z ranga i bez kompresji: \n";
	std::cout << "Liczba krawedzi w MST: " << edges << ", koszt: " << cost << ", czas sortowania: " << sortowanie << "ms, czas petli for Kruskala: " << kruskalczas << "ms, liczba wywolan Find(): " << findcall << "\nliczba krokow find(liczba przejsc po parent): " << findcount << "\n";
	//bez rangi i z kompresją
	edges = kruskal(g, false, true, cost, sortowanie, kruskalczas, findcount,findcall);
	std::cout << "Bez rangi i z kompresja: \n";
	std::cout << "Liczba krawedzi w MST: " << edges << ", koszt: " << cost << ", czas sortowania: " << sortowanie << "ms, czas petli for Kruskala: " << kruskalczas << "ms, liczba wywolan Find(): " << findcall << "\nliczba krokow find(liczba przejsc po parent): " << findcount << "\n";
	//z rangą i z kompresją
	edges = kruskal(g, true, true, cost, sortowanie, kruskalczas, findcount,findcall);
	std::cout << "Z ranga i z kompresja: \n";
	std::cout << "Liczba krawedzi w MST: " << edges << ", koszt: " << cost << ", czas sortowania: " << sortowanie << "ms, czas petli for Kruskala: " << kruskalczas << "ms, liczba wywolan Find(): " << findcall << " \nliczba krokow find(liczba przejsc po parent): " << findcount << "\n";
}
//void testJednegoWariantu(const Graph& g, bool ranga, bool kompresja, int REP) {
//    double cost = 0, sortMs = 0, loopMs = 0;
//    long long steps = 0, calls = 0;
//    int mstEdges = 0;
//
//    double sumSort = 0.0, sumLoop = 0.0;
//
//    for (int i = 0; i < REP; i++) {
//        mstEdges = kruskal(g, ranga, kompresja, cost, sortMs, loopMs, steps, calls);
//        sumSort += sortMs;
//        sumLoop += loopMs;
//    }
//
//    std::cout << (ranga ? "RANGA" : "BRAK_RANGI") << ", "
//        << (kompresja ? "KOMPRESJA" : "BRAK_KOMPRESJI") << "\n";
//    std::cout << "MST edges: " << mstEdges << ", koszt: " << cost << "\n";
//    std::cout << "Sredni czas sortowania: " << (sumSort / REP) << " ms\n";
//    std::cout << "Sredni czas petli Kruskala: " << (sumLoop / REP) << " ms\n";
//    std::cout << "findCalls: " << calls << ", findSteps(parent): " << steps << "\n\n";
//}

int main()
{
    int REP = 100;
	Graph g;
   /* if (load("g3.txt", g)) {
        std::cout << "g1\n";
        testJednegoWariantu(g, false, false, REP);
        testJednegoWariantu(g, true, false, REP);
        testJednegoWariantu(g, false, true, REP);
        testJednegoWariantu(g, true, true, REP);
    }
    else {
        std::cout<< "nie mozna wczytac g1.txt";
    }*/
 if (load("g1.txt", g)) {
        std::cout << "g1.txt\n";
        testy(g);
    }
    else {
        std::cout << "nie mozna wczytac g1.txt";
    }
    if (load("g2.txt", g)) {
        std::cout << "g2.txt\n";
        testy(g);
    }
    else {
        std::cout << "nie mozna wczytac g2.txt";
    }
    if (load("g3.txt", g)) {
        std::cout << "g3.txt\n";
        testy(g);
    }
    else {
        std::cout << "nie mozna wczytac g3.txt";
    }
    return 0;
}

