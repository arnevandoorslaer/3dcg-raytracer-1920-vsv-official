#include "parallel-task-schedular.h"
#include "thread"
#include <algorithm>
#include <atomic>
#include "easylogging++.h"

using namespace tasks;

namespace
{

	class ParallelTaskScheduler : public tasks::schedulers::_private_::TaskSchedulerImplementation
	{
	public:
		void perform(std::vector<std::shared_ptr<Task>> tasks) const
		{	
			std::atomic<int> i(0);
			int aantalThreads = 20;
			std::vector<std::thread> threads;
			
			for (int a = 0; a < aantalThreads; a++) {
				std::thread t([&i, &tasks]() {
					while (true)
					{
						int j = i++;
						if (j >= tasks.size()) return;
						tasks[j]->perform();
					}
				});
				threads.push_back(std::move(t));
			}
			for (auto &t : threads) {
				t.join();
			}
		}
	};
}

TaskScheduler tasks::schedulers::parallel()
{
	return TaskScheduler(std::make_shared<ParallelTaskScheduler>());
}
