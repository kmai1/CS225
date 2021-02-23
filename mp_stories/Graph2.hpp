#include <queue>
#include <algorithm>
#include <string>
#include <list>

/**
 * Returns an std::list of vertex keys that creates any shortest path between `start` and `end`.
 *
 * This list MUST include the key of the `start` vertex as the first vertex in the list, the key of
 * the `end` vertex as the last element in the list, and an ordered list of all vertices that must
 * be traveled along the shortest path.
 *
 * For example, the path a -> c -> e returns a list with three elements: "a", "c", "e".
 *
 * You should use undirected edges. Hint: There are no edge weights in the Graph.
 *
 * @param start The key for the starting vertex.
 * @param end   The key for the ending vertex.
 */
template <class V, class E>
std::list<std::string> Graph<V,E>::shortestPath(const std::string start, const std::string end) {
  // TODO: Part 3 //mp_mazes? mp_kdtree? mp_traversal?
  std::list<std::string> path;
  queue<std::string> bfs;
  //vertexm aped to net to parent
  std::unordered_map<std::string, std::string> parentVertex;
  std::unordered_map<std::string, bool> visited;
  for (pair<std::string, V_byRef> vertex : vertexMap) {
    visited.insert(std::pair<string, bool>(vertex.first, false));
  }
  visited[start] = true;
  bfs.push(start);
  while (!bfs.empty()) {
    string currVertex = bfs.front();
    bfs.pop();
      //check edge push outedge vertex to bfs ?
    for (edgeListIter e1 : adjList.at(currVertex)) {
      Edge e = *(e1);
      //if i havent been, assign a map value of, dont reaassign too muc
      if (!visited[e.source().key()]) {
        bfs.push(e.source().key());
        parentVertex.insert(std::pair<string, string>(e.source().key(), currVertex));
        visited[e.source().key()] = true;
      } else if (!visited[e.dest().key()]) {
          bfs.push(e.dest().key());
          parentVertex.insert(std::pair<string, string>(e.dest().key(), currVertex));
          visited[e.dest().key()] = true;
      }
    }
  }
  //make  pathway
  string currVertex = end;
  path.push_front(end);
  while(currVertex != start){
    path.push_front(parentVertex[currVertex]);
    currVertex = parentVertex[currVertex];
  }
  return path;
}
