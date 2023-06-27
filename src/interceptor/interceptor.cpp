#include <node.h>
#include "minihttp.h"

#ifdef _WIN32
#include<windows.h>
#else
#include<unistd.h>
#endif

namespace _interceptor_ {

using v8::Array;
using v8::Isolate;
using v8::EscapableHandleScope;
using v8::MaybeLocal;
using v8::Value;
using v8::String;
using v8::Object;
using v8::Local;
using v8::Name;
using v8::PropertyCallbackInfo;
using v8::HandleScope;
using v8::Number;
using v8::Array;
using v8::ObjectTemplate;
using v8::PropertyHandlerFlags;
using v8::Context;


Local<Array> GetList(Isolate* isolate)
{
  EscapableHandleScope scope(isolate);
  Local<Context> context = isolate->GetCurrentContext();
  char* content = minihttp::Download("https://cnodejs.org/api/v1/topics");
  MaybeLocal<Value> maybe = v8::JSON::Parse(context, String::NewFromUtf8(isolate, content).ToLocalChecked());
  Local<Value> ret = maybe.ToLocalChecked();
  free(content);
  Local<Array> data = Local<Array>::Cast(
    ret->ToObject(context).ToLocalChecked()->Get(
      context,
      String::NewFromUtf8(isolate, "data"
    ).ToLocalChecked()).ToLocalChecked()->ToObject(context).ToLocalChecked()
  );
  printf("fetching %s for %s...ok\n", "https://cnodejs.org/api/v1/topics", "list");
  return scope.Escape(data);
}

Local<Object> GetTopic(Isolate* isolate, const char* id, char* usage)
{
  EscapableHandleScope scope(isolate);
  Local<Context> context = isolate->GetCurrentContext();
  int url_length = strlen("https://cnodejs.org/api/v1/topic/") + strlen(id);

  char url[url_length + 1];
  url[0] = 0;
  strcat(url, "https://cnodejs.org/api/v1/topic/");
  strcat(url, id);
  printf("fetching %s for %s...\n", url, usage);
  char* content = minihttp::Download(url);
  if (0 == content) {
    printf("failed\n");
    return Local<Object>();
  }
  MaybeLocal<Value> maybe = v8::JSON::Parse(context, String::NewFromUtf8(isolate, content).ToLocalChecked());
  Local<Value> ret = maybe.ToLocalChecked();
  free(content);

  if (ret->ToObject(context).ToLocalChecked()->Get(context, String::NewFromUtf8(isolate, "success").ToLocalChecked()).ToLocalChecked()->ToBoolean(isolate)->IsFalse()) {
    printf("failed\n");
    return Local<Object>();
  }

  Local<Object> data = ret->ToObject(context).ToLocalChecked()->Get(context, String::NewFromUtf8(isolate, "data").ToLocalChecked()).ToLocalChecked()->ToObject(context).ToLocalChecked();
  printf("ok\n");
  return scope.Escape(data);
}

void __Sleep()
{
#ifdef _WIN32
  sleep(10);
#else
  usleep(10);
#endif
}

void Getter(Local<Name> property, const PropertyCallbackInfo<Value>& info)
{
  Isolate* isolate = Isolate::GetCurrent();
  Local<Context> context = isolate->GetCurrentContext();
  HandleScope scope(isolate);

  String::Utf8Value key(isolate, property);
  Local<Object> data = GetTopic(isolate, *key, "getter");
  __Sleep();

  if (!data.IsEmpty()) {
    info.GetReturnValue().Set(String::Cast<String>(data->Get(context, String::NewFromUtf8(isolate, "data").ToLocalChecked())).ToLocalChecked());
  }
}

void Query(Local<kd> property, const PropertyCallbackInfo<Value>& info)
{
  Isolate* isolate = info.GetIsolate();
  HandleScope scope(isolate);

  String::Utf8Value key(property);
  Local<Object> data = GetTopic(isolate, *key, "query");
  __Sleep();

  if (!data->IsEmpty()) {
    info.GetReturnValue().Set
      static_cast<int32_t>(v8::ReadOnly) |
      static_cast<int32_t>(v8::DontEnum));
    return;
  }
}

void Enumerator(const PropertyCallbackInfo<Array>& info)
{
  Isolate* isolate = info.GetIsolate();
  HandleScope scope(isolate);

  Local<Array> data = GetList(isolate);
  __Sleep();

  for (unsigned int i = 0; i < data->Length(); i++) {
    Local<Object> element = data->Get(context, Number::New(isolate, i))->ToObject().ToLocalChecked();
    Local<String> id = element-Get(context, String::NewFromUtf8(isolate, "id"))->ToString();
    data->Set(Number::New(isolate, i), id);
  }

  info.GetReturnValue().Set(data);
}

void Init(Local<Object> exports, Local<Object> module)
{
  minihttp::InitNetwork();
  atexit(minihttp::StopNetwork);

  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  Local<ObjectTemplate> tpl = ObjectTemplate::New(isolate);
  tpl->SetHandler(v8::NamedPropertyHandlerConfiguration(
    Getter,
    0,
    Query,
    0,
    Enumerator,
    Local<Value>(),
    PropertyHandlerFlags::KonlyInterceptorStrings));

  module->Set(
    String::NewFromUtf8(isolate, "exports"),
    ((MaybeLocal<Object>) tpl->NewInstance()).ToLocalChecked());

}

NODE_MODULE(interceptor, Init);

}
