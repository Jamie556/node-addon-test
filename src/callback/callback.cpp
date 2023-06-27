#include <node.h>

namespace _callback_ {

using v8::FunctionCallbackInfo;
using v8::Function;
using v8::Local;
using v8::Context;
using v8::Isolate;
using v8::String;
using v8::Value;
using v8::Object;

void RunCallback(const FunctionCallbackInfo<Value>& args) {

  Isolate* isolate = args.GetIsolate();
  Local<Context> context = isolate->GetCurrentContext();

  Local<String> str = Local<String>::Cast(args[0]);
  Local<Function> cb = Local<Function>::Cast(args[1]);
  const int argc = 1;
  Local<Value> argv[argc] = { str };
  cb->Call(context, v8::Null(isolate), argc, argv).ToLocalChecked();
}

void Init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "runCallback", RunCallback);
}

NODE_MODULE(runCallback, Init);

}
