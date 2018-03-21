#pragma once

#include "node.h"

#include <uv.h>

#include <assert.h>

using namespace napa;

static const std::string INIT_SCRIPT_FULLPATH = utils::string::ReplaceAllCopy(
                            (filesystem::Path(dll::ThisLineLocation()).Dirname() / "../../main.js").Normalize().String(),
                            "\\", "\\\\");

class Worker
{
  public:
    uv_thread_t tId;
    uv_loop_t loop;

    void WorkerThreadFunc() {
        auto res = uv_loop_init(&loop);
        assert(res == 0);

        int main_argc;
        char** main_argv;
        int main_exec_argc;
        const char** main_exec_argv;
        node::GetNodeMainArgments(main_argc, main_argv, main_exec_argc, main_exec_argv);

        // Setup worker after isolate creation.
        //_impl->setupCallback(_impl->id);

        const char* worker_argv[2];
        worker_argv[0] = "node";
        worker_argv[1] = INIT_SCRIPT_FULLPATH.c_str();
        node::Start(static_cast<void*>(&loop), 2, worker_argv, main_exec_argc, main_exec_argv);
    }
};
