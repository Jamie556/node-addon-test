#include <node.h>
#include "myObject.h"

namespace _my_object_addon_ {

using v8::Local;
using v8::Object;

void InitAll(Local<Object> exports) {
  MyObject::Init(exports);
}

NODE_MODULE(myObject, InitAll);

}
