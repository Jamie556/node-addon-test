#ifndef _MYOBJECT_H__
#define _MYOBJECT_H__


#include <node.h>
#include <node_object_wrap.h>

namespace _my_object_addon_ {

using node::ObjectWrap;
using v8::Local;
using v8::Object;
using v8::Value;
using v8::FunctionCallbackInfo;

class MyObject : public ObjectWrap {

public:
  static void Init(Local<Object> exports);

private:
  explicit MyObject(double value = 0);
  ~MyObject();

  static void New(const FunctionCallbackInfo<Value>& args);
  static void PlusOne(const FunctionCallbackInfo<Value>& args);

  double value_;
};

}

#endif
