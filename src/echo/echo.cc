#include<nan.h>

namespace _nanl_echo_ {

using v8::String;
using v8::FunctionTemplate;
using v8::Local;

NAN_METHOD(Echo) {
  if (info.Length() < 1) {
    Nan::ThrowError("wrong number of arguments. ");
    return;
  }

  Local<String> handle = Nan::To<String>(info[0]).ToLocalChecked();
  Nan::Utf8String val(handle);
  std::string str(*val);
  printf("\n%s\n", str.c_str());
  info.GetReturnValue().Set(info[0]);
}

NAN_MODULE_INIT(Init) {
  Nan::Set(target, Nan::New<String>("Echo").ToLocalChecked(),
    Nan::GetFunction(Nan::New<FunctionTemplate>(Echo)).ToLocalChecked());
}

NODE_MODULE(echo, Init);

}
