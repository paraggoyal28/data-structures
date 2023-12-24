#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using std::cin;
using std::cout;
using std::pair;
using std::priority_queue;
using std::vector;

class Job
{
public:
  int worker;
  long long finishTime;
  Job(int worker, long long finishTime)
  {
    this->worker = worker;
    this->finishTime = finishTime;
  }
};

class CompareJobs
{
public:
  bool operator()(Job *job1, Job *job2)
  {

    return job1->finishTime == job2->finishTime ? job1->worker > job2->worker : job1->finishTime > job2->finishTime;
  }
};

class JobQueue
{
private:
  int num_workers_;
  vector<int> jobs_;

  vector<int> assigned_workers_;
  vector<long long> start_times_;

  void WriteResponse() const
  {
    for (int i = 0; i < jobs_.size(); ++i)
    {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

  void ReadData()
  {
    int m;
    cin >> num_workers_ >> m;
    assigned_workers_.resize(m);
    start_times_.resize(m);
    jobs_.resize(m);
    for (int i = 0; i < m; ++i)
      cin >> jobs_[i];
  }

  void AssignJobs()
  {
    // TODO: replace this code with a faster algorithm.
    priority_queue<Job *, vector<Job *>, CompareJobs> finishedJobs;

    for (int i = 0; i < std::min(num_workers_, (int)jobs_.size()); ++i)
    {
      finishedJobs.push(new Job(i, (long long)jobs_[i]));
      assigned_workers_[i] = i;
      start_times_[i] = 0;
    }

    for (int i = num_workers_; i < (int)jobs_.size(); ++i)
    {
      Job *finishedJob = finishedJobs.top();
      finishedJobs.pop();
      start_times_[i] = finishedJob->finishTime;
      assigned_workers_[i] = finishedJob->worker;
      finishedJobs.push(new Job(finishedJob->worker, 0LL + finishedJob->finishTime + jobs_[i]));
    }
  }

public:
  void Solve()
  {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
};

int main()
{
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}
