/////////////// DISABLE C4251 //////////////
#pragma warning(push)
#pragma warning(disable: 4251)
#include "v8.h"
#pragma warning(pop)
///////////////    RESTORE    //////////////

#include "node.h"

#include <uv.h>
#include "platform/dll.h"
#include "platform/filesystem.h"
#include "utils/string.h"
#include "simple-worker.h"

#include <memory>

static std::shared_ptr<Worker> worker1;
static std::shared_ptr<Worker> worker2;

void CreateWorkersCallback(const v8::FunctionCallbackInfo<v8::Value>& args) {
    worker1 = std::make_shared<Worker>();
    worker2 = std::make_shared<Worker>();

    uv_thread_create(&worker1->tId, [](void* arg) {
        Worker* worker = static_cast<Worker*>(arg);
        worker->WorkerThreadFunc();
    }, worker1.get());

    uv_thread_create(&worker2->tId, [](void* arg) {
        Worker* worker = static_cast<Worker*>(arg);
        worker->WorkerThreadFunc();
    }, worker2.get());
}

void HelloCallback(const v8::FunctionCallbackInfo<v8::Value>& args) {
    printf("HelloCallback() !\n");
}

void InitAll(v8::Local<v8::Object> exports, v8::Local<v8::Object> module) {
    NODE_SET_METHOD(exports, "createWorkers", CreateWorkersCallback);
    NODE_SET_METHOD(exports, "hello", HelloCallback);
    //NODE_SET_METHOD(exports, "now", Now);
}

NODE_MODULE(addon, InitAll)
