#pragma once

#ifndef EXCLUDE_SCRIPTING

#include <chaiscript/chaiscript.hpp>


namespace raytracer
{
    namespace scripting
    {
        namespace _private_
        {
            chaiscript::ModulePtr create_samplers_module();
        }
    }
}

#endif
