#include <node.h>

namespace _add_ {

using v8::Object;
using v8::FunctionCallbackInfo;
using v8::Exception;
using v8::String;
using v8::Isolate;
using v8::Number;
using v8::Value;
using v8::Context;
using v8::Local;

void Add(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  Local<Context> context = isolate->GetCurrentContext();

  if (args.Length() < 2) {
    isolate->ThrowException(Exception::TypeError(
      String::NewFromUtf8(isolate, "wrong number of arguments").ToLocalChecked()
    ));
    return;
  }

  if (!args[0]->IsNumber() || !args[1]->IsNumber()) {
    isolate->ThrowException(Exception::TypeError(
      String::NewFromUtf8(isolate, "wrong argument type").ToLocalChecked()
    ));
    return;
  }

  double value = args[0]->NumberValue(context).FromJust() + args[1]->NumberValue(context).FromJust();
  Local<Number> num = Number::New(isolate, value);
  args.GetReturnValue().Set(num);

}

void Init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "add", Add);
}

NODE_MODULE(add, Init);

}
