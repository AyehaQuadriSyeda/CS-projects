// application.cpp
// <Ayesha Quadri Syeda>
//
// University of Illinois at Chicago
// CS 251: Fall 2021
// Project #7 - Openstreet Maps
//
// References:
// TinyXML: https://github.com/leethomason/tinyxml2
// OpenStreetMap: https://www.openstreetmap.org
// OpenStreetMap docs:
//   https://wiki.openstreetmap.org/wiki/Main_Page
//   https://wiki.openstreetmap.org/wiki/Map_Features
//   https://wiki.openstreetmap.org/wiki/Node
//   https://wiki.openstreetmap.org/wiki/Way
//   https://wiki.openstreetmap.org/wiki/Relation
//
//  The creative function performs all the standard 
//  functions execpt it finds a building closer to person 
//  1 instead of the center of the two people.
//  
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <iomanip>   //setprecision
#include <iostream>
#include <limits>   //numeric_limits
#include <map>
#include <stack>
#include <string>
#include <vector>

#include "dist.h"
#include "graph.h"
#include "osm.h"
#include "queue"
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

// class for the priority queue
class prioritize {
  public:
  bool operator()(const pair<long long, double> &p1,
                  const pair<long long, double> &p2) const {
    return p1.second > p2.second;
  }
};

//
// Implement your creative component application here
// TO DO: add arguments
//
BuildingInfo closertoP1(Coordinates coord1, vector<BuildingInfo> buildings) {
  double min;
  BuildingInfo dbuilding;

  // initializing min
  min = distBetween2Points(coord1.Lat, coord1.Lon,
                           buildings[0].Coords.Lat, 
                           buildings[0].Coords.Lon);
  dbuilding.Coords.Lat = buildings[0].Coords.Lat;
  dbuilding.Coords.Lon = buildings[0].Coords.Lon;
  dbuilding.Fullname = buildings[0].Fullname;

  // look for the closest building to the center
  for (size_t i = 1; i < buildings.size(); i++) {
    double min1 = distBetween2Points(
        coord1.Lat, coord1.Lon, buildings[i].Coords.Lat, 
        buildings[i].Coords.Lon);
    if (min1 < min && buildings[i].Coords.Lat != coord1.Lat
        && buildings[i].Coords.Lon != coord1.Lon) {
      min = min1;
      dbuilding.Coords.Lat = buildings[i].Coords.Lat;
      dbuilding.Coords.Lon = buildings[i].Coords.Lon;
      dbuilding.Fullname = buildings[i].Fullname;
    }
  }
  return dbuilding;
}

// Finds the location (Building) of a person according to user input
bool personlocation(string personBuilding, vector<BuildingInfo> Buildings,
                    BuildingInfo &building) {
  for (size_t i = 0; i < Buildings.size(); i++) {

    // look for abbreviation first
    if (Buildings[i].Abbrev == personBuilding) {
      building.Abbrev = Buildings[i].Abbrev;
      building.Fullname = Buildings[i].Fullname;
      building.Coords.ID = Buildings[i].Coords.ID;
      building.Coords.Lat = Buildings[i].Coords.Lat;
      building.Coords.Lon = Buildings[i].Coords.Lon;
      return true;
    }else  if (Buildings[i].Fullname.find(personBuilding) != string::npos) {
        building.Abbrev = Buildings[i].Abbrev;
        building.Fullname = Buildings[i].Fullname;
        building.Coords.ID = Buildings[i].Coords.ID;
        building.Coords.Lat = Buildings[i].Coords.Lat;
        building.Coords.Lon = Buildings[i].Coords.Lon;
        return true;
      }
  }
  return false;
}

// Finds the destination building
BuildingInfo Destbuilding(Coordinates coord1, Coordinates coord2,
                          vector<BuildingInfo> buildings) {
  Coordinates dest;
  dest = centerBetween2Points(coord1.Lat, coord1.Lon, coord2.Lat, coord2.Lon);
  double min;
  BuildingInfo dbuilding;

  // initializing min
  min = distBetween2Points(dest.Lat, dest.Lon, buildings[0].Coords.Lat,
                           buildings[0].Coords.Lon);
  dbuilding.Coords.Lat = buildings[0].Coords.Lat;
  dbuilding.Coords.Lon = buildings[0].Coords.Lon;
  dbuilding.Fullname = buildings[0].Fullname;

  // look for the closest building to the center
  for (size_t i = 1; i < buildings.size(); i++) {
    double min1 = distBetween2Points(
        dest.Lat, dest.Lon, buildings[i].Coords.Lat, buildings[i].Coords.Lon);
    if (min1 < min) {
      min = min1;
      dbuilding.Coords.Lat = buildings[i].Coords.Lat;
      dbuilding.Coords.Lon = buildings[i].Coords.Lon;
      dbuilding.Fullname = buildings[i].Fullname;
    }
  }
  return dbuilding;
}

// Finds the closest footway
long long ClosestFootway(Coordinates coord, map<long long, 
                         Coordinates> Nodes, 
                         vector<FootwayInfo> Footways) {
  double distance = 0.0;

  // initializing min
  double min = distBetween2Points(coord.Lat, coord.Lon, 
                                  Nodes[Footways[0].Nodes[0]].Lat, 
                                  Nodes[Footways[0].Nodes[0]].Lon);

  // look for the closest footway to a given building
  long long node = Footways[0].Nodes[0];
  for (size_t j = 0; j < Footways.size(); j++) {
    for (size_t i = 0; i < Footways[j].Nodes.size(); i++) {
      distance = distBetween2Points(coord.Lat, coord.Lon,
                                    Nodes[Footways[j].Nodes[i]].Lat,
                                    Nodes[Footways[j].Nodes[i]].Lon);
      if (distance < min) {
        min = distance;
        node = Footways[j].Nodes[i];
      }
    }
  }
  return node;
}
// Dijkstra's algorithm
map<long long, long long> Dijkstra(graph<long long, double> &G,
                                   long long startV,
                                   map<long long, double> &distances) {

  map<long long, long long> predecessor;
  set<long long> visited_set;
  double INF = numeric_limits<double>::max();

  priority_queue<pair<long long, double>, vector<pair<long long, double>>,
                 prioritize>
      unvisitedQueue;

  // initialize the distances and predecessor map
  for (auto &a : G.getVertices()) {
    distances[a] = INF;
    predecessor[a] = -1;
    unvisitedQueue.push(make_pair(a, INF));
  }

  // initialize the start node distance and add the unvisited queue
  distances[startV] = 0;
  unvisitedQueue.push(make_pair(startV, 0));

  long long currentV;

  // Go through the queue
  while (!unvisitedQueue.empty()) {
    currentV = unvisitedQueue.top().first;
    unvisitedQueue.pop();

    if (distances[currentV] == INF)
      break;
    else if (visited_set.count(currentV))
      continue;
    else
      visited_set.insert(currentV);

    double alternativePath = 0.0;
    for (auto g : G.neighbors(currentV)) {
      double weight = 0.0;
      G.getWeight(currentV, g, weight);
      alternativePath = distances[currentV] + weight;

      // change any distances if necessary
      if (alternativePath < distances[g]) {
        distances[g] = alternativePath;
        predecessor[g] = currentV;
        unvisitedQueue.push(make_pair(g, alternativePath));
      }
    }
  }
  return predecessor;
}

// Uses a map of predecessors to find a path
double path(map<long long, long long> pred, stack<long long> &path,
            long long endV, map<long long, Coordinates> Nodes,
            map<long long, double> &distances) {
  long long currentV;
  double distance = 0.0;
  currentV = endV;
  double INF = numeric_limits<double>::max();
  while (currentV != -1) {
    path.push(currentV);
    // check if the node after the start node is valid
    if (pred[currentV] == -1) {
      if (distances[currentV] >= INF) {
        cout << "Sorry, destination unreachable." << endl;
        return -1;
      }
    }
    currentV = pred[currentV]; 
  }
  return distance;
}
// Finds the next closest building to the center
BuildingInfo nextbuilding(Coordinates coord1, Coordinates coord2,
                          vector<BuildingInfo> buildings,
                          vector<BuildingInfo> skipbuilding) {
  Coordinates dest;
  dest = centerBetween2Points(coord1.Lat, coord1.Lon, coord2.Lat, coord2.Lon);
  double min;
  BuildingInfo dbuilding;

  // initialize min
  min = distBetween2Points(dest.Lat, dest.Lon, buildings[0].Coords.Lat,
                           buildings[0].Coords.Lon);
  dbuilding.Coords.Lat = buildings[0].Coords.Lat;
  dbuilding.Coords.Lon = buildings[0].Coords.Lon;
  dbuilding.Fullname = buildings[0].Fullname;

  int count = 0;

  // find the closest building
  for (size_t i = 1; i < buildings.size(); i++) {
    double min1 = distBetween2Points(
        dest.Lat, dest.Lon, buildings[i].Coords.Lat, buildings[i].Coords.Lon);

    // check if it's a building to be skipped
    for (size_t k = 0; k < skipbuilding.size(); k++) {
      if (buildings[i].Fullname == skipbuilding[k].Fullname) {
        count++;
      }
    }
    if (min1 < min && count == 0) {
      min = min1;
      dbuilding.Coords.Lat = buildings[i].Coords.Lat;
      dbuilding.Coords.Lon = buildings[i].Coords.Lon;
      dbuilding.Fullname = buildings[i].Fullname;
    }
    count = 0;
  }
  return dbuilding;
}

// Prints the path
void printpath(stack<long long> path, double distance, string person,
               map<long long, double> distances, long long endv) {
  cout << endl;
  cout << person << " distance to dest: ";
  cout << distances[endv] << " miles" << endl;
  cout << "Path: ";
  cout << path.top();
  path.pop();
  while (!path.empty()) {
    cout << "->" << path.top();
    path.pop();
  }
}

// Applies the Dijstra's algorithm and prints out alot of the results
void application(map<long long, Coordinates> &Nodes,
                 vector<FootwayInfo> &Footways, vector<BuildingInfo> &Buildings,
                 graph<long long, double> G) {
  string person1Building, person2Building;
  double INF = numeric_limits<double>::max();

  cout << endl;
  cout << "Enter person 1's building (partial name or abbreviation), or #> ";
  getline(cin, person1Building);

  while (person1Building != "#") {
    cout << "Enter person 2's building (partial name or abbreviation)> ";
    getline(cin, person2Building);
    BuildingInfo building1, building2, destbuilding;

    // if person 1's or 2's building is not found
    if (!personlocation(person1Building, Buildings, building1)) {
      cout << "Person 1's building not found" << endl;
      cout << endl;
      cout
          << "Enter person 1's building (partial name or abbreviation), or #> ";
      getline(cin, person1Building);
      continue;
    } else if (!personlocation(person2Building, Buildings, building1)) {
      cout << "Person 2's building not found" << endl;
      cout << endl;
      cout
          << "Enter person 1's building (partial name or abbreviation), or #> ";
      getline(cin, person1Building);
      continue;
    }

    // output the locations of the people
    if (personlocation(person1Building, Buildings, building1)) {
      cout << endl;
      cout << "Person 1's point:" << endl;
      cout << " " << building1.Fullname << endl;
      cout << " (" << building1.Coords.Lat << ", ";
      cout << building1.Coords.Lon << ")" << endl;
    }
    if (personlocation(person2Building, Buildings, building2)) {
      cout << "Person 2's point:" << endl;
      cout << " " << building2.Fullname << endl;
      cout << " (" << building2.Coords.Lat << ", ";
      cout << building2.Coords.Lon << ")" << endl;
    } else {
      cout << "Person 2's building not found" << endl;
      cout << endl;
      cout << "Enter person 2's building (partial name or abbreviation), or "
              "#> ";
      getline(cin, person2Building);
      continue;
    }

    // output the location of the destination building
    destbuilding = Destbuilding(building1.Coords, building2.Coords, Buildings);
    cout << "Destination Building: " << endl;
    cout << " " << destbuilding.Fullname << endl;
    cout << " (" << destbuilding.Coords.Lat << ", " << destbuilding.Coords.Lon
         << ")" << endl;

    // output the nearest footway to person 1, 2 and destination building
    long long node1, node2, node3;
    cout << endl;
    cout << "Nearest P1 node:" << endl;
    node1 = ClosestFootway(building1.Coords, Nodes, Footways);
    cout << " " << Nodes[node1].ID << endl;
    cout << " (" << Nodes[node1].Lat << ", " << Nodes[node1].Lon << ")" << endl;

    cout << "Nearest P2 node:" << endl;
    node2 = ClosestFootway(building2.Coords, Nodes, Footways);
    cout << " " << Nodes[node2].ID << endl;
    cout << " (" << Nodes[node2].Lat << ", " << Nodes[node2].Lon << ")" << endl;

    cout << "Nearest destination node:" << endl;
    node3 = ClosestFootway(destbuilding.Coords, Nodes, Footways);
    cout << " " << Nodes[node3].ID << endl;
    cout << " (" << Nodes[node3].Lat << ", " << Nodes[node3].Lon << ")" << endl;

    // find the shortest path to the destination building from person 1 and
    // person 2
    map<long long, long long> pred1;
    map<long long, long long> pred2;
    map<long long, double> distances1;
    map<long long, double> distances2;
    pred1 = Dijkstra(G, node1, distances1);
    pred2 = Dijkstra(G, node2, distances2);
    stack<long long> path1, path2;
    double distance1, distance2;

    vector<BuildingInfo> skipBuildings;

    distance1 = path(pred1, path1, node3, Nodes, distances1);

    // output the paths
    if (distance1 >= 0) {
      printpath(path1, distance1, "Person 1's", distances1, node3);
    }
    if (distance1 == -1) {
      cout << endl;
  cout << "Enter person 1's building (partial name or abbreviation), or #> ";
  getline(cin, person1Building);
      continue;
    }

    distance2 = path(pred2, path2, node3, Nodes, distances2);
    if (distance2 >= 0) {
      cout << endl;
      printpath(path2, distance2, "Person 2's", distances2, node3);
      cout << endl;
    }
    if (distance2 == -1) {
      cout << endl;
      cout << "Enter person 1's building (partial";
      cout << "name or abbreviation), or #>" << endl;
      getline(cin, person1Building);
      continue;
    }

    // If the building is unreachable
    while (distances1[node3] >= INF || distances2[node3] >= INF) {
      skipBuildings.push_back(destbuilding);
      cout << "At least one person was unable to reach the destination "
              "building. Finding next closest building..."
           << endl;
      destbuilding = nextbuilding(building1.Coords, building2.Coords,
      Buildings,
                                  skipBuildings);
      node3 = ClosestFootway(destbuilding.Coords, Nodes, Footways);

      cout << "New destination Building: " << endl;
      cout << " " << destbuilding.Fullname << endl;
      cout << " (" << destbuilding.Coords.Lat << ", " <<
      destbuilding.Coords.Lon
           << ")" << endl;

      cout << "Nearest destination node:" << endl;
      cout << " " << Nodes[node3].ID << endl;
      cout << " (" << Nodes[node3].Lat << ", " << Nodes[node3].Lon << ")"
           << endl;
    }

    cout << endl;
    cout << "Enter person 1's building (partial";
    cout << "name or abbreviation), or #>" << endl;
    getline(cin, person1Building);
  }
}
// creative component
void creative(map<long long, Coordinates> &Nodes, 
              vector<FootwayInfo> &Footways, 
              vector<BuildingInfo> &Buildings, 
              graph<long long, double> G) {
  string person1Building, person2Building;

  cout << endl;
  cout << "Enter person 1's building (partial";
  cout << "name or abbreviation), or #>" << endl;
  getline(cin, person1Building);

  while (person1Building != "#") {
    cout << "Enter person 2's building (partial name or abbreviation)> ";
    getline(cin, person2Building);
    BuildingInfo building1, building2, destbuilding;

    // if person 1's or 2's building is not found
    if (!personlocation(person1Building, Buildings, building1)) {
      cout << "Person 1's building not found" << endl;
      cout << endl;
      cout
          << "Enter person 1's building (partial name or abbreviation), or #> ";
      getline(cin, person1Building);
      continue;
    } else if (!personlocation(person2Building, Buildings, building1)) {
      cout << "Person 2's building not found" << endl;
      cout << endl;
      cout
          << "Enter person 1's building (partial name or abbreviation), or #> ";
      getline(cin, person1Building);
      continue;
    }

    // output the locations of the people
    if (personlocation(person1Building, Buildings, building1)) {
      cout << endl;
      cout << "Person 1's point:" << endl;
      cout << " " << building1.Fullname << endl;
      cout << " (" << building1.Coords.Lat << ", ";
      cout << building1.Coords.Lon << ")" << endl;
    }
    if (personlocation(person2Building, Buildings, building2)) {
      cout << "Person 2's point:" << endl;
      cout << " " << building2.Fullname << endl;
      cout << " (" << building2.Coords.Lat << ", ";
      cout << building2.Coords.Lon << ")" << endl;
    } else {
      cout << "Person 2's building not found" << endl;
      cout << endl;
      cout << "Enter person 2's building (partial name or abbreviation), or "
              "#> ";
      getline(cin, person2Building);
      continue;
    }

    // output the location of the destination building
    destbuilding = closertoP1(building1.Coords, Buildings);
    cout << "Destination Building: " << endl;
    cout << " " << destbuilding.Fullname << endl;
    cout << " (" << destbuilding.Coords.Lat << ", " << destbuilding.Coords.Lon
         << ")" << endl;

    // output the nearest footway to person 1, 2 and destination building
    long long node1, node2, node3;
    cout << endl;
    cout << "Nearest P1 node:" << endl;
    node1 = ClosestFootway(building1.Coords, Nodes, Footways);
    cout << " " << Nodes[node1].ID << endl;
    cout << " (" << Nodes[node1].Lat << ", " << Nodes[node1].Lon << ")" << endl;

    cout << "Nearest P2 node:" << endl;
    node2 = ClosestFootway(building2.Coords, Nodes, Footways);
    cout << " " << Nodes[node2].ID << endl;
    cout << " (" << Nodes[node2].Lat << ", " << Nodes[node2].Lon << ")" << endl;

    cout << "Nearest destination node:" << endl;
    node3 = ClosestFootway(destbuilding.Coords, Nodes, Footways);
    cout << " " << Nodes[node3].ID << endl;
    cout << " (" << Nodes[node3].Lat << ", " << Nodes[node3].Lon << ")" << endl;

    // find the shortest path to the destination building from person 1 and
    // person 2
    map<long long, long long> pred1;
    map<long long, long long> pred2;
    map<long long, double> distances1;
    map<long long, double> distances2;
    pred1 = Dijkstra(G, node1, distances1);
    pred2 = Dijkstra(G, node2, distances2);
    stack<long long> path1, path2;
    double distance1, distance2;

    distance1 = path(pred1, path1, node3, Nodes, distances1);

    // output the paths
    if (distance1 >= 0) {
      printpath(path1, distance1, "Person 1's", distances1, node3);
    }
    if (distance1 == -1) {
      cout << endl;
      cout << "Enter person 1's building (partial";
      cout << "name or abbreviation), or #>" << endl;
      getline(cin, person1Building);
      continue;
    }

    distance2 = path(pred2, path2, node3, Nodes, distances2);
    if (distance2 >= 0) {
      printpath(path2, distance2, "Person 2's", distances2, node3);
    }
    if (distance2 == -1) {
      cout << endl;
      cout << "Enter person 1's building (partial";
      cout << "name or abbreviation), or #>" << endl;
      getline(cin, person1Building);
      continue;
    }
    cout << endl;
    cout << "Enter person 1's building (partial";
    cout << "name or abbreviation), or #>" << endl;
    getline(cin, person1Building);
  }
}
int main() {
  // maps a Node ID to it's coordinates (lat, lon)
  map<long long, Coordinates> Nodes;
  // info about each footway, in no particular order
  vector<FootwayInfo> Footways;
  // info about each building, in no particular order
  vector<BuildingInfo> Buildings;
  XMLDocument xmldoc;

  cout << "** Navigating UIC open street map **" << endl;
  cout << endl;
  cout << std::setprecision(8);

  string def_filename = "map.osm";
  string filename;

  cout << "Enter map filename> ";
  getline(cin, filename);

  if (filename == "") {
    filename = def_filename;
  }

  //
  // Load XML-based map file
  //
  if (!LoadOpenStreetMap(filename, xmldoc)) {
    cout << "**Error: unable to load open street map." << endl;
    cout << endl;
    return 0;
  }

  //
  // Read the nodes, which are the various known positions on the map:
  //
  int nodeCount = ReadMapNodes(xmldoc, Nodes);

  //
  // Read the footways, which are the walking paths:
  //
  int footwayCount = ReadFootways(xmldoc, Footways);

  //
  // Read the university buildings:
  //
  int buildingCount = ReadUniversityBuildings(xmldoc, Nodes, Buildings);

  //
  // Stats
  //
  assert(nodeCount == (int)Nodes.size());
  assert(footwayCount == (int)Footways.size());
  assert(buildingCount == (int)Buildings.size());

  cout << endl;
  cout << "# of nodes: " << Nodes.size() << endl;
  cout << "# of footways: " << Footways.size() << endl;
  cout << "# of buildings: " << Buildings.size() << endl;

  //
  // TO DO: build the graph, output stats:
  //
  graph<long long, double> G;

  // add nodes as vertices
  for (auto a : Nodes) {
    G.addVertex(a.first);
  }

  // add edges
  for (auto &a : Footways) {
    for (size_t i = 0; i < a.Nodes.size() - 1; i++) {
      double weight = 0.0;
      weight = distBetween2Points(Nodes[a.Nodes[i]].Lat, 
                                  Nodes[a.Nodes[i]].Lon, 
                                  Nodes[a.Nodes[i + 1]].Lat, 
                                  Nodes[a.Nodes[i + 1]].Lon);
      G.addEdge(a.Nodes[i], a.Nodes[i + 1], weight);
      G.addEdge(a.Nodes[i + 1], a.Nodes[i], weight);
    }
  }
  cout << "# of vertices: " << G.NumVertices() << endl;
  cout << "# of edges: " << G.NumEdges() << endl;
  cout << endl;

  //
  // Menu
  //
  string userInput;
  cout << "Enter \"a\" for the standard application or "
       << "\"c\" for the creative component application> ";
  getline(cin, userInput);
  if (userInput == "a") {
    application(Nodes, Footways, Buildings, G);
  } else if (userInput == "c") {
    // TO DO: add arguments
    creative(Nodes, Footways, Buildings, G);
  }
  //
  // done:
  //
  cout << "** Done **" << endl;
  return 0;
}
