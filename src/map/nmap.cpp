#include <nan.h>

namespace _nan_map_ {

using Nan::FunctionCallbackInfo;
using v8::Value;
using v8::Local;
using v8::Array;
using v8::Function;
using v8::Object;
using v8::Int32;
using v8::Isolate;
using v8::Context;

void Map(const FunctionCallbackInfo<Value>& args)
{
  Isolate* isolate = args.GetIsolate();
  Local<Context> context = isolate->GetCurrentContext();
  Local<Array> array = args[0].As<Array>();
  Local<Function> func = args[1].As<Function>();

  Local<Array> ret = Nan::New<Array>(array->Length());
  Local<Value> null = Nan::Null();
  Local<Value> a[3] = {Nan::New<Object>(), null, array};

  for (uint32_t i = 0; i < array->Length(); i++) {
    a[0] = array->Get(context, i).ToLocalChecked();
    a[1] = Nan::New<Int32>(i);
    Local<Value> v = Nan::Call(func, args.This(), 3, a).ToLocalChecked();
    ret->Set(context, i, v).FromJust();
  }
  args.GetReturnValue().Set(ret);
}

NAN_MODULE_INIT(Init) {
  Nan::Export(target, "nmap", Map);
}

NODE_MODULE(nmap, Init);

}
