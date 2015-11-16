/*
 * Graph.hpp
 * 
 * Copyright 2015 Robert Bakaric <rbakaric@irb.hr>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <vector>
#include <unordered_map>

using namespace std;
/*!  @brief Vertex cover namespace
 */
namespace vex{

/*!  @brief Graph class 
 */

template <typename Tobj,typename Tint>
class Graph{

  protected:
/* Data Container */
  unordered_map<Tobj, vector<Tobj>> GraphMap;
  Tint Max;

/*!  Function creates a simple map-of-vectors data structure which 
 *   contians a parent-child relationships of vertices for a given 
 *   graph
 * 
 * @param parent [const vector<Tobj>&]
 * @param child  [const vector<Tobj>&]  
 */
  void MakeGraph(const vector<Tobj>& parent, const vector<Tobj>& child);
  
  public:

/*!  Class constructor
 * 
 * @param parent [const vector<Tobj>&]
 * @param child  [const vector<Tobj>&]  
 */
   Graph(const vector<Tobj>& parent, const vector<Tobj>& child);
/*!  Class destructor 
 */
  ~Graph();
/*!  Class explicite constructor
 * 
 * @param parent [const vector<Tobj>&]
 * @param child  [const vector<Tobj>&]  
 */
   void Make(const vector<Tobj>& parent, const vector<Tobj>& child);
/*!  Class explicite destructor
 */
   void Purge();
  
/*!  Function converts a map-of-vectors back into two vector format 
 *   containing a set of predecessors and their corresponding successor 
 *   vertices
 * 
 * @param parent [const vector<Tobj>&]
 * @param child  [const vector<Tobj>&]  
 */
   void GetGraph(vector<Tobj>& parent, vector<Tobj>& child);
};


template <typename Tobj,typename Tint>
Graph<Tobj,Tint>::Graph(const vector<Tobj>& parent, const vector<Tobj>& child){
  Make(parent,child);
}

template <typename Tobj,typename Tint>
void Graph<Tobj,Tint>::Make(const vector<Tobj>& parent, const vector<Tobj>& child){
  Max = 0;
  MakeGraph(parent, child);
}

/* Destructors */

template <typename Tobj,typename Tint>
Graph<Tobj,Tint>::~Graph(){
  Purge();
}

template <typename Tobj,typename Tint>
void Graph<Tobj,Tint>::Purge(){
  GraphMap.clear();
}


/* Functions */

template <typename Tobj,typename Tint>
void Graph<Tobj,Tint>::GetGraph(vector<Tobj>& parent, vector<Tobj>& child){
  Tint i = 0;
  for ( auto it = GraphMap.begin(); it != GraphMap.end(); ++it ){  
    for(Tint j = 0; j< GraphMap[it->first].size();j++){
      if(parent.size() == i){
        parent.resize((parent.size()+1) * 2);
        child.resize((child.size()+1) * 2);
      }
      parent[i] = it->first;
      child[i++]  = GraphMap[it->first][j];
    }
  }
  parent.resize(i);
  child.resize(i);
}

template <typename Tobj,typename Tint>
void Graph<Tobj,Tint>::MakeGraph(const vector<Tobj>& parent, const vector<Tobj>& child){
   
  for (Tint i = 0; i< parent.size(); i++){
    GraphMap[parent[i]].push_back(child[i]);
    GraphMap[child[i]].push_back(parent[i]);
  }

}

}
