#include <node.h>

namespace _create_func_ {

using v8::FunctionCallbackInfo;
using v8::Value;
using v8::Isolate;
using v8::String;
using v8::Context;
using v8::Local;
using v8::FunctionTemplate;
using v8::Function;
using v8::Object;

void MyFunction(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  args.GetReturnValue().Set(String::NewFromUtf8(isolate, "hello world!").ToLocalChecked());
}

void CreateFunction(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  Local<Context> context = isolate->GetCurrentContext();
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, MyFunction);
  Local<Function> fn = tpl->GetFunction(context).ToLocalChecked();
  fn->SetName(String::NewFromUtf8(isolate, "myFunction").ToLocalChecked());
  args.GetReturnValue().Set(fn);
}

void Init(Local<Object> exports, Local<Object> module) {
  NODE_SET_METHOD(exports, "createFunc", CreateFunction);
}

NODE_MODULE(createFunc, Init);


}
