#include <node.h>

namespace _create_obj_ {

using v8::FunctionCallbackInfo;
using v8::Value;
using v8::Isolate;
using v8::Object;
using v8::Local;
using v8::String;
using v8::Context;

void CreateObject(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  Local<Context> context = isolate->GetCurrentContext();

  Local<Object> obj = Object::New(isolate);
  obj->Set(context, String::NewFromUtf8(isolate, "msg").ToLocalChecked(), args[0]->ToString(context).ToLocalChecked()).FromJust();
  args.GetReturnValue().Set(obj);
}

void Init(Local<Object> exports, Local<Object> module) {
  NODE_SET_METHOD(exports, "createObj", CreateObject);
}

NODE_MODULE(createObj, Init);

}
