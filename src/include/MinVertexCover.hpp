/*
 * MinVertexCover.hpp
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
#include <set>
#include <sstream>
#include <unordered_map>
#include <algorithm> 
#include <cmath>

#include <Graph.hpp>

using namespace std;
/*!  @brief Vertex cover namespace
 */
namespace vex{
/*!  @brief Vertex cover class 
 */
template <typename Tobj,typename Tint>
class VexCov : protected Graph<Tobj,Tint>{
   
   vector<Tobj> MVC;
   Tint Approx;
   void CompVexCov();
   
   public:
/*!  Class constructor
 */
   VexCov();
/*!  Class constructor overload
 * 
 * @param parent [const vector<Tobj>&]
 * @param child  [const vector<Tobj>&]  
 */
   VexCov(const vector<Tobj>& parent, const vector<Tobj>& child);
/*!  Class destructor 
 */
   ~VexCov();
/*!  Class explicite constructor
 * 
 * @param parent [const vector<Tobj>&]
 * @param child  [const vector<Tobj>&]  
 */
   void            Make(const vector<Tobj>& parent, const vector<Tobj>& child);
/*!  Class explicite destructor 
 */
   void            Purge();
/*!  Function returns a vector of objects (vertices) defining the minimum 
 *   vertex cover set 
 */
   vector<Tobj>    GetMinVexCov();
/*!  Function computes the approximation ratio for here implemented list 
 *   heuristic 
 */
   Tint            GetError();
};

template <typename Tobj,typename Tint>
VexCov<Tobj, Tint>::VexCov(const vector<Tobj>&  parent,const vector<Tobj>&  child): Graph<Tobj,Tint>(parent,child){
   CompVexCov();
}

template <typename Tobj,typename Tint>
Tint VexCov<Tobj, Tint>::GetError(){
   return Approx;
}

template <typename Tobj,typename Tint>
void VexCov<Tobj, Tint>::Make(const vector<Tobj>&  parent,const vector<Tobj>&  child){
   Graph<Tobj,Tint>::Make(parent,child);
   Approx = 0;
   CompVexCov();
}

template <typename Tobj,typename Tint>
void VexCov<Tobj, Tint>::Purge(){
   Graph<Tobj,Tint>::Purge();
   MVC.clear();
   Approx = 0;
}

template <typename Tobj,typename Tint>
VexCov<Tobj, Tint>::~VexCov(){
   Purge();
}


template <typename Tobj,typename Tint>
vector<Tobj> VexCov<Tobj, Tint>::GetMinVexCov(){
   return MVC;
}


template <typename Tobj,typename Tint>
void VexCov<Tobj, Tint>::CompVexCov(){
   
   unordered_map<string,bool> TotSet;
   unordered_map<Tobj,bool> MinVecCov;
   
   vector<pair<Tobj,Tint>> svec;
   
   for ( auto it = this->GraphMap.begin(); it != this->GraphMap.end(); ++it )
      svec.push_back(pair<Tobj,Tint>(it->first,it->second.size()));
   
    
   sort(svec.begin(), svec.end(), 
   [](const pair<Tobj, Tint> &p1, const pair<Tobj, Tint> &p2 ) -> bool
   {   return p1.second > p2.second; }); 
   
   auto it = svec.begin();
   Approx = sqrt(it->second)/2 + 3/2;
   
   for ( auto it = svec.begin(); it != svec.end(); it++ ){
         for(auto xt = this->GraphMap[it->first].begin(); xt!= this->GraphMap[it->first].end(); xt++){
            stringstream ssa, ssb;
            ssa<< *xt << "-" << it->first;
            if(TotSet.find(ssa.str())==TotSet.end())
               MinVecCov[it->first] = true;
            ssb << it->first << "-" << *xt;
            TotSet[ssb.str()] = true;
             
         }
   }
   for ( auto it = MinVecCov.begin(); it != MinVecCov.end(); it++ ){
      MVC.push_back(it->first);
   }
}

}
