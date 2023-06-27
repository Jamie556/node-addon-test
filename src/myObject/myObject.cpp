#include "myObject.h"
#include <node.h>
#include <node_object_wrap.h>

namespace _my_object_addon_ {

using v8::Local;
using v8::Object;
using v8::Isolate;
using v8::String;
using v8::Value;
using v8::Number;
using v8::FunctionCallbackInfo;
using v8::FunctionTemplate;
using v8::Context;


MyObject::MyObject(double value) : value_(value) {}
MyObject::~MyObject() {}

void MyObject::Init(Local<Object> exports)
{
    Isolate* isolate = exports->GetIsolate();
    Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
    tpl->SetClassName(String::NewFromUtf8(isolate, "MyObject").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    NODE_SET_PROTOTYPE_METHOD(tpl, "plusOne", PlusOne);

    Local<Context> context = isolate->GetCurrentContext();
    exports->Set(context, String::NewFromUtf8(isolate, "MyObject").ToLocalChecked(), tpl->GetFunction(context).ToLocalChecked()).FromJust();
}

void MyObject::New(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  Local<Context> context = isolate->GetCurrentContext();
  double value = args[0]->IsUndefined() ? double(0) : args[0]->NumberValue(context).ToChecked();
  MyObject* obj = new MyObject(value);
  obj->Wrap(args.This());
  args.GetReturnValue().Set(args.This());
}

void MyObject::PlusOne(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  MyObject* obj = ObjectWrap::Unwrap<MyObject>(args.Holder());
  obj->value_ += 1;
  args.GetReturnValue().Set(Number::New(isolate, obj->value_));
}

}
