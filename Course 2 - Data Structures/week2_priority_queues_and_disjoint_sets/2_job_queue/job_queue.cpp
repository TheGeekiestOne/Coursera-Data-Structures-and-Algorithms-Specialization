#include <iostream>
#include <vector>
#include <algorithm>

/*********************************
******                      ******
***        Ayran Olckers       ***
**                              **
**            08/2019           **
******                      ******
**********************************/

using std::vector;
using std::cin;
using std::cout;
using std::pair;
using std::make_pair;
using std::swap;


/**************Priority queue implementation******************************/

class Threads
{
	public:
		long long int start_time;
		int thread_id;

		Threads()
		{
			this->start_time = 0;
		}
};

int leftchild(int i)
{
  return (2*i) + 1;
}

int rightchild(int i)
{
  return (2*i)+2;
}

void Siftdown(int i, vector <Threads> &mythreads)
{
	int minindex = i;
	int left = leftchild(i);

	if(left < static_cast<int>(mythreads.size()) && mythreads[left].start_time == mythreads[minindex].start_time)
	{
		int temp_original_id = mythreads[minindex].thread_id;
		int temp_left_id = mythreads[left].thread_id;

		if(temp_original_id > temp_left_id)
			minindex = left;
	}

	else if(left < static_cast<int>(mythreads.size()) && mythreads[left].start_time < mythreads[minindex].start_time)
		minindex = left;

	int right = rightchild(i);

	if(right < static_cast<int>(mythreads.size()) && mythreads[right].start_time == mythreads[minindex].start_time)
	{
		int left_id = mythreads[minindex].thread_id;
		int right_id = mythreads[right].thread_id;

		if(left_id > right_id)
			minindex = right;
	}

	else if(right < static_cast<int>(mythreads.size()) && mythreads[right].start_time< mythreads[minindex].start_time)
	  minindex = right;

	if(i!=minindex)
	{
	  swap(mythreads[i], mythreads[minindex]);
	  Siftdown(minindex,mythreads);
	}
}

void ChangePriority(int i, long long int new_priority, vector <Threads> &mythreads)
{
	mythreads[0].start_time = new_priority;

	Siftdown(0,mythreads);
}

void start(vector <long long int> &jobs_list, vector <Threads> &mythreads)
{
	vector <pair <int ,long long int> > results;
	results.resize(jobs_list.size());

	for(int i=0; i<jobs_list.size(); i++)
	{
		results[i] = make_pair(mythreads[0].thread_id, mythreads[0].start_time);
		if(jobs_list[i] != 0)
			ChangePriority((int)0,mythreads[0].start_time + jobs_list[i], mythreads);
	}

	//writing response
	for(int i=0; i<results.size(); i++)
		cout << results[i].first << " " << results[i].second << std::endl;
}


int main()
{
	int n,m;
	cin >> n >> m;

	vector <long long int> jobs_list;
	jobs_list.resize(m);

	for(int i=0; i<m; i++)
		cin >> jobs_list[i];

	vector <Threads> mythreads;
	mythreads.resize(n);

	for(int i=0; i<n; i++)
		mythreads[i].thread_id = i;

	start(jobs_list,mythreads);
	return 0;
}


/***********************Another slower implementation*********************
long int time_counter = 0;
class Threads
{
	public:
		int thread_id;
		long int completion_time;

		Threads()
		{
			this->completion_time = 0;
		}

	void setid(int i)
	{
		thread_id = i;
	}
};
void start(vector <long int> &jobs_list, vector <Threads> &mythreads)
{
	vector < pair <int, long int> > results;
	vector <Threads *> address_buffer;
	int thread_matching_counter;

	while(jobs_list.size()!=0)
	{
		thread_matching_counter=0;
		address_buffer.clear();

		for(int i=0; i<static_cast<int>(mythreads.size()); i++)
			if(mythreads[i].completion_time == time_counter)
			{
				thread_matching_counter++;
				address_buffer.push_back(&mythreads[i]);

				if(thread_matching_counter==static_cast<int>(jobs_list.size()))
					break;
			}

		for(int i=0; i<thread_matching_counter; i++)
		{
			if(jobs_list.size()==0 || address_buffer.size()==0)
				break;
			int tempid = address_buffer[0]->thread_id;
			long int temp_completion_time = address_buffer[0]->completion_time;

			results.push_back(make_pair(tempid,temp_completion_time));
			address_buffer[0]->completion_time += jobs_list[0];

			jobs_list.erase(jobs_list.begin());
			address_buffer.erase(address_buffer.begin());
		}

		time_counter++;
	}

	//writing response
	for(int i=0; i<results.size(); i++)
		cout << results[i].first << " " << results[i].second << std::endl;
}
int main()
{
	int n,m;
	cin >> n >> m;

	vector <Threads> mythreads;
	mythreads.resize(n);

	vector <long int> jobs_list;
	jobs_list.resize(m);

	for(int i=0;i<m;i++)
		cin >> jobs_list[i];

	for(int i=0; i<n; i++)
		mythreads[i].setid(i);

	start(jobs_list, mythreads);
	return 0;
}*/

/***************Slower default implementation******************************/
/*
class JobQueue {
 private:
  int num_workers_;
  vector<int> jobs_;
  vector<int> assigned_workers_;
  vector<long long> start_times_;
  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }
  void ReadData() {
    int m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for(int i = 0; i < m; ++i)
      cin >> jobs_[i];
  }
  void AssignJobs() {
    // TODO: replace this code with a faster algorithm.
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());
    vector<long long> next_free_time(num_workers_, 0);
    for (int i = 0; i < jobs_.size(); ++i) {
      int duration = jobs_[i];
      int next_worker = 0;
      for (int j = 0; j < num_workers_; ++j) {
        if (next_free_time[j] < next_free_time[next_worker])
          next_worker = j;
      }
      assigned_workers_[i] = next_worker;
      start_times_[i] = next_free_time[next_worker];
      next_free_time[next_worker] += duration;
    }
  }
 public:
  void Solve() {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
};
int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}
*/
