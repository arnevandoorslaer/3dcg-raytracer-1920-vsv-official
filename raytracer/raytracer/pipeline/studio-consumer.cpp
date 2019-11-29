#include "pipeline/studio-consumer.h"

using namespace raytracer::pipeline;


namespace
{
	class Studio : public Producer<std::string OUTPUT>
	{
	public:
		
		// geen idee hoe ik dees fix maar bekijk producer


	private:
		std::ostream m_studio;
	};
}

std::shared_ptr<> raytracer::pipeline::studio()
{
	return std::make_shared<Studio>();
}