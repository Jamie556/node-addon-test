#include <node.h>

namespace _try_catch_ {

using v8::FunctionCallbackInfo;
using v8::Context;
using v8::Local;
using v8::Value;
using v8::Object;
using v8::String;
using v8::TryCatch;
using v8::FunctionTemplate;
using v8::HandleScope;
using v8::Isolate;
using v8::MaybeLocal;
using v8::Int32;
using v8::Exception;



void Get(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  Local<Context> context = isolate->GetCurrentContext();
  TryCatch trycatch(isolate);

  MaybeLocal<Object> maybe_obj = args[0]->ToObject(context);
  MaybeLocal<String> maybe_key = args[1]->ToString(context);

  if (maybe_obj.IsEmpty() || maybe_key.IsEmpty()) {
    if (trycatch.HasCaught()) {
      trycatch.ReThrow();
    } else {
      args.GetReturnValue().Set(v8::Undefined(isolate));
    }
    return;
  }

  Local<Object> obj = maybe_obj.ToLocalChecked();
  Local<String> key = maybe_key.ToLocalChecked();

  Local<Value> value = obj->Get(context, key).ToLocalChecked();
  args.GetReturnValue().Set(value);
}

void Div(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  Local<Context> context = isolate->GetCurrentContext();

  Local<Int32> a = args[0]->ToInt32(context).ToLocalChecked().As<Int32>();
  Local<Int32> b = args[1]->ToInt32(context).ToLocalChecked().As<Int32>();

  int32_t av = a->Value();
  int32_t bv = b->Value();

  if (bv == 0) {
    isolate->ThrowException(Exception::Error(String::NewFromUtf8(isolate, "除数不能为 0。").ToLocalChecked()));
    return;
  }

  args.GetReturnValue().Set(av / bv);
}


void Init(Local<Object> exports, Local<Object> module){
  Isolate* isolate = Isolate::GetCurrent();
  Local<Context> context = isolate->GetCurrentContext();
  HandleScope scope(isolate);

  module->Set(
    context,
    String::NewFromUtf8(isolate, "exports").ToLocalChecked(),
    Object::New(isolate)
  ).FromJust();

  Local<Object> exp = module->Get(context, String::NewFromUtf8(isolate, "exports").ToLocalChecked()).ToLocalChecked().As<Object>();

  exp->Set(
    context,
    String::NewFromUtf8(isolate, "get").ToLocalChecked(),
    FunctionTemplate::New(isolate, Get)->GetFunction(context).ToLocalChecked()
  ).FromJust();

  // module->Set(
  //   context,
  //   String::NewFromUtf8(isolate, "exports").ToLocalChecked(),
  //   FunctionTemplate::New(isolate, Get)->GetFunction(context).ToLocalChecked()
  // ).FromJust();


  exp->Set(
    context,
    String::NewFromUtf8(isolate, "div").ToLocalChecked(),
    FunctionTemplate::New(isolate, Div)->GetFunction(context).ToLocalChecked()
  ).FromJust();
}

NODE_MODULE(Get, Init);

}
