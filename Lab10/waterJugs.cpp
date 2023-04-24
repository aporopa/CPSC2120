/*
 * Name: Abigail Poropatich
 * Date Submitted: 23 April 2023
 * Lab Section: 003
 * Assignment Name: Using Breadth-First Search to Solve Puzzles
 */

#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;

// Reflects what each node represents...
// First value units of water in A, second units of water in B
typedef pair<int,int> state;

// Each string in edge_label must be one of the following:
const string actions[] = {"Fill A",
                          "Fill B",
                          "Empty A",
                          "Empty B",
                          "Pour A->B",
                          "Pour B->A"};

// GENERIC -- these shouldn't need to be changed...
map<state, bool> visited;         // have we queued up this state for visitation?
map<state, state> pred;           // predecessor state we came from
map<state, int> dist;             // distance (# of hops) from source node
map<state, vector<state>> nbrs;   // vector of neighboring states

map<pair<state,state>, string> edge_label;

// GENERIC (breadth-first search, outward from source_node)
void search(state source_node)
{
  queue<state> to_visit;
  to_visit.push(source_node);
  visited[source_node] = true;
  dist[source_node] = 0;
  
  while (!to_visit.empty()) {
    state curnode = to_visit.front();
    to_visit.pop();
    for (state n : nbrs[curnode])
      if (!visited[n]) {
	pred[n] = curnode;
	dist[n] = 1 + dist[curnode];
	visited[n] = true;
	to_visit.push(n);
      }
  }
}

// GENERIC
void print_path(state s, state t)
{
  if (s != t) {
    print_path(s, pred[t]);
    cout << edge_label[make_pair(pred[t], t)] << ": " << "[" << t.first << "," << t.second << "]\n";
  } else {
    cout << "Initial state: " << "[" << s.first << "," << s.second << "]\n";
  }
}

//jug A filled
void fill_A(const state& currentNode){
  if(currentNode.first < 3){
    state nextNode = make_pair(3, currentNode.second);
    nbrs[currentNode].push_back(nextNode);
    edge_label[make_pair(currentNode, nextNode)] = actions[0];
  }
}

//jug B filled
void fill_B(const state& currentNode){
  if(currentNode.second < 4){
    state nextNode = make_pair(currentNode.first, 4);
    nbrs[currentNode].push_back(nextNode);
    edge_label[make_pair(currentNode, nextNode)] = actions[1];
  }
}

//jug A emptied
void empty_A(const state& currentNode){
  if(currentNode.first > 0){
    state nextNode = make_pair(0, currentNode.second);
    nbrs[currentNode].push_back(nextNode);
    edge_label[make_pair(currentNode, nextNode)] = actions[2];
  }
}

//jug B emptied
void empty_B(const state& currentNode){
  if(currentNode.second > 0){
    state nextNode = make_pair(currentNode.first, 0);
    nbrs[currentNode].push_back(nextNode);
    edge_label[make_pair(currentNode, nextNode)] = actions[3];
  }
}

//creates a state when contents of A are poured into B
void A_to_B(const state& currentNode){
  if(currentNode.second > 0 && currentNode.first < 3){
    int amount = min(currentNode.second, 3 - currentNode.first);
    state nextNode = make_pair(currentNode.first + amount, currentNode.second - amount);
    nbrs[currentNode].push_back(nextNode);
    edge_label[make_pair(currentNode, nextNode)] = actions[5];
  }
}

//creates a state when contents of B are poured into A
void B_to_A(const state& currentNode){
  if(currentNode.second > 0 && currentNode.first < 3){
    int amount = min(currentNode.second, 3 - currentNode.first);
    state nextNode = make_pair(currentNode.first + amount, currentNode.second - amount);
    nbrs[currentNode].push_back(nextNode);
    edge_label[make_pair(currentNode, nextNode)] = actions[5];
  }
}

void build_graph(void){
  int a = 3;
  int b = 4;

  for(int i = 0; i <= a; i++){
    for(int j = 0; j <= b; j++){
      state currentNode = make_pair(i,j);
      nbrs[currentNode] = vector<state>();

      //add new states and edges
      fill_A(currentNode);
      fill_B(currentNode);
      empty_A(currentNode);
      empty_A(currentNode);
      A_to_B(currentNode);
      B_to_A(currentNode);
    }
  }
}