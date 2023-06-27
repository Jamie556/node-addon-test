#include <node.h>
#include <iostream>
// #include <string>
// #include <stdio.h>


namespace _map_ {

using v8::FunctionCallbackInfo;
using v8::Value;
using v8::Array;
using v8::Number;
using v8::Context;
using v8::Function;
using v8::Local;
using v8::Object;
using v8::Int32;
using v8::MaybeLocal;
using v8::Isolate;
using v8::HandleScope;
using v8::FunctionTemplate;
using v8::String;
using std::string;

// using namespace std;




void Map(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  Local<Context> context = isolate->GetCurrentContext();

  Local<Array> array = args[0].As<Array>();
  Local<Function> func = args[1].As<Function>();

  Local<Array> ret = Array::New(isolate, array->Length());

  Local<Value> null = v8::Null(isolate);
  Local<Value> a[3] = { Local<Object>(), null, array };
  for (uint32_t i = 0; i < array->Length(); i++) {

    String::Utf8Value strTemp(isolate, array->Get(context, i).ToLocalChecked());
    string str = string(*strTemp);
    str = "[ " + str + " ]";
    // a[0] = array->Get(context, i).ToLocalChecked();
    a[0] = String::NewFromUtf8(isolate, (char*)str.data()).ToLocalChecked();
    a[1] = Int32::New(isolate, i);
    MaybeLocal<Value> v = func->Call(context, null, 3, a);
    ret->Set(context, Number::New(isolate, i), v.ToLocalChecked()).FromJust();
  }
  args.GetReturnValue().Set(ret);
}

void Init(Local<Object> exports, Local<Object> module) {
  Isolate* isolate = Isolate::GetCurrent();
  Local<Context> context = isolate->GetCurrentContext();
  HandleScope scope(isolate);

  module->Set(
    context,
    String::NewFromUtf8(isolate, "exports").ToLocalChecked(),
    FunctionTemplate::New(isolate, Map)->GetFunction(context).ToLocalChecked()
  ).FromJust();
}

NODE_MODULE(map, Init);


}
