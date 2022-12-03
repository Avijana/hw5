

#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here


// Add your implementation of schedule() and other helper functions here



bool sHelper(size_t cols, size_t rows, const AvailabilityMatrix& avail, const size_t dailyNeed, DailySchedule& sched, std::map<Worker_T, int>& workers)
{
   if(rows == sched.size()){
       return true;
   }
   else{
       for(unsigned int i = 0; i < avail[rows].size(); i++){ //double loop goes through sched inner vectors to see if id exists
           for(unsigned int j = 0; j < sched[rows].size(); j++){
               if(sched[rows].begin()[j] == i){
                   continue;
                }
            }
            if(workers[i] > 0 && avail[rows][i] == true){ //if worker has available shifts and open spots
               workers[i]--;
               sched[rows][cols] = i;
               bool check = false;
               unsigned int sizeCheck = sched[rows].size()-1;
               if(sizeCheck != cols){ //if not full cols
                   check = sHelper(cols+1, rows, avail, dailyNeed, sched, workers); //stay in row but check next col
               }
               else{
                   check = sHelper(0, rows+1, avail, dailyNeed, sched, workers); //recurse by goint to col zero but next row
               }
               if(check){
                   return true;
               }
               workers[i]++;
               sched[rows][cols] = INVALID_ID;
           }
       }
       return false;
   }
 
}


bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below

    vector<Worker_T> id;
    map<Worker_T, int> workers; //map of worker and shifts available
    
    
    for(unsigned int i = 0; i < dailyNeed; i++){
        id.push_back(INVALID_ID);
    }

    for(unsigned int i = 0; i < avail[0].size(); i++){ //fill map with appropriate pairs
        workers.insert(make_pair(i, maxShifts));
    }

    for(unsigned int i = 0; i < avail.size(); i++){ //put vectors into sched vector made up of workers id based on dailyNeed
        sched.push_back(id);
    }
    
    return sHelper(0, 0, avail, dailyNeed, sched, workers);
}

