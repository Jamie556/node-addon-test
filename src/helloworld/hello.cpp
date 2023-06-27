# include <node.h>

namespace _hello_ {

using v8::Local;
using v8::Object;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Data;
using v8::String;
using v8::Value;
using v8::Context;

void Method(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  Local<Context> context = isolate->GetCurrentContext();

  Local<String> name = args[0]->ToString(context).ToLocalChecked();
  printf("name is: %s\n", *String::Utf8Value(isolate, name));
  args.GetReturnValue().Set(name);
}

void Init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "hello", Method);
}

NODE_MODULE(hello, Init);

}
