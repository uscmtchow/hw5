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
bool solver(
		const AvailabilityMatrix& avail, 
		const size_t dailyNeed, 
		const size_t maxShifts, 
		DailySchedule& sched,
		unsigned int row,
		unsigned int col
);

bool isValid(
		const Worker_T ID,
		const size_t maxShifts, 
		DailySchedule& sched,
		unsigned int row
);

// Add your implementation of schedule() and other helper functions here

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

		std::vector<Worker_T> IDs;
		IDs.resize(dailyNeed, INVALID_ID);
		sched.resize(avail.size(), IDs);

		return solver(avail, dailyNeed, maxShifts, sched, 0, 0);
}

bool scheduleSolver(
		const AvailabilityMatrix& avail, 
		const size_t dailyNeed, 
		const size_t maxShifts, 
		DailySchedule& sched,
		unsigned int row,
		unsigned int col
) {
	if (row == avail.size()) return true;
	if (col == dailyNeed) return solver(avail, dailyNeed, maxShifts, sched, row+1, 0);

	for (unsigned int i = 0; i < avail[row].size(); i++) {
		if (avail[row][i] == 1) {
			if (find(sched[row].begin(), sched[row].end(), i) != sched[row].end()) continue;
			sched[row][col] = i;
			if (isValid(sched[row][col], maxShifts, sched, row)) {
				if (scheduleSolver(avail, dailyNeed, maxShifts, sched, row, col+1)) return true;
			}
			sched[row][col] = INVALID_ID;
		}
	}
	return false;
}

bool isValid(
		const Worker_T ID,
		const size_t maxShifts, 
		DailySchedule& sched,
		unsigned int row
) {
	unsigned int shift_count = 0;
	for (unsigned int i = 0; i <= row; i++) {
		if (find(sched[i].begin(), sched[i].end(), ID) != sched[i].end()) shift_count++;
	}
	if (shift_count <= maxShifts) reutrn true;
	return false;
}

