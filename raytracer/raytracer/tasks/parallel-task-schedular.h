#pragma once
#include "tasks/task-scheduler.h"

namespace tasks
{
	namespace schedulers
	{
		void doTask(std::shared_ptr<Task>);
		TaskScheduler parallel();
	}
}