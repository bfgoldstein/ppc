#include<vector>
#include<set>
#include<iostream>
#include<cmath>
#define ALPHA 3
using namespace std;

struct job {
    int r, d, w;
};
struct interval {
    int r, d, time;
    double dens;
    mutable vector<job>jobs_inside;
    bool operator<(const interval& inter) const {
        if(r < inter.r) return true;
        if(r == inter.r && d < inter.d) return true; 
        return false;
    }
};

const double energy_consumption(const vector<interval>& sch){
    double energy = 0.0;
    for(size_t i = 0; i < sch.size(); i++){
        double dens = sch[i].dens;
        int inter = sch[i].d - sch[i].r;
        energy += pow(dens, ALPHA)*inter;
    }
    return energy;
}

set<interval> build_intervals(const vector<job> &jobs){
    set<interval> intervals;
    for(size_t i = 0; i < jobs.size(); i++){
        for(size_t j = 0; j < jobs.size(); j++){
            if(jobs[i].r >= jobs[j].d) continue;
            interval inter {jobs[i].r, jobs[i].d, jobs[i].d - jobs[i].r, 0.0};
            intervals.insert(inter);
        }
    }
    return intervals;
}

interval find_maximum_density_interval(const vector<job>& jobs){
    set<interval> intervals = build_intervals(jobs);
    double max_dens = -1.0;
    interval max_interval;
    for(set<interval>::iterator it = intervals.begin(); it!= intervals.end(); ++it){
        int inter_r = it->r, inter_d = it->d;
        double dens = 0.0;
        for(size_t i = 0; i < jobs.size(); i++){
            if(jobs[i].r >= inter_r && jobs[i].d <= inter_d){
                it->jobs_inside.push_back(jobs[i]);
                dens += jobs[i].w;
            }
        }
        dens /= it->time;
        if(dens >= max_dens) {
            max_dens = dens;
            max_interval = *it;
            max_interval.dens = dens;
        }
    }
    return max_interval;
}

void remove_jobs_from_interval(vector<job>& jobs, const interval inter){
    for(size_t i = 0; i < jobs.size(); i++){
        int inter_r = inter.r, inter_d = inter.d;
        if(jobs[i].r >= inter_r && jobs[i].d <= inter_d){
            jobs.erase(jobs.begin() + i);
            i--;
        }
    }
}

void adjust_jobs_given_interval(vector<job>& jobs, const interval inter){
    for(size_t i = 0; i < jobs.size(); i++){
        int inter_r = inter.r, inter_d = inter.d;
        if(jobs[i].r >= inter_r && jobs[i].r <= inter_d && jobs[i].d >= inter_d){
            jobs[i].r = inter_d;
        } else if(jobs[i].r <= inter_r && jobs[i].d >= inter_r && jobs[i].d <= inter_d){
            jobs[i].d = inter_r;
        }
    }
}   

vector<interval> yds(vector<job>jobs){
    vector<interval> schedule;
    while(!jobs.empty()) {
        // find maximum density interval
        interval max_interval = find_maximum_density_interval(jobs);
        
        // put max density interval on the schedule
        schedule.push_back(max_interval);

        // remove max_interval jobs from the total jobs
        remove_jobs_from_interval(jobs, max_interval);
        
        // adjust jobs
        adjust_jobs_given_interval(jobs, max_interval);
    }
    return schedule;
}

int main(){
    int n;
    vector<job>jobs;
    
    cin >> n;
    for(int k = 0; k < n; k++){
        int r, d, w;
        cin >> r >> d >> w;
        job j {r, d, w};
        jobs.push_back(j);
    }
    
    vector<interval> schedule = yds(jobs);     
    cout << energy_consumption(schedule) << endl;
    return 0;
}


