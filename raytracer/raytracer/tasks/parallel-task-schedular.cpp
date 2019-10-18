#include "parallel-task-schedular.h"
#include "thread"
#include <algorithm>

using namespace tasks;

namespace
{

	class ParallelTaskScheduler : public tasks::schedulers::_private_::TaskSchedulerImplementation
	{
	public:
		void perform(std::vector<std::shared_ptr<Task>> tasks) const
		{	
			int count = tasks.size();
			while (count > 0) {
				std::vector<std::thread *> threads(std::min(4, count));
				for (size_t i = 0; i < threads.size(); ++i) 
				{ // Start appropriate number of threads
					threads[i] = new std::thread(tasks::schedulers::doTask, tasks[i]);
				}
				for (size_t i = 0; i < threads.size(); ++i) 
				{ // Wait for all threads to finish
					threads[i]->join();
					delete threads[i];
					--count;
				}
			}

		}
	};
}
void tasks::schedulers::doTask(std::shared_ptr<Task> t)
{
	t->perform();
}

TaskScheduler tasks::schedulers::parallel()
{
	return TaskScheduler();
}
