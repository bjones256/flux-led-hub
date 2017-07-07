#include <node.h>

namespace demo {

  using v8::FunctionCallbackInfo;
  using v8::Exception;
  using v8::Isolate;
  using v8::Local;
  using v8::Object;
  using v8::String;
  using v8::Value;

  void genAPIKey(const FunctionCallbackInfo<Value>& args) {
    Isolate *isolate = args.GetIsolate();

    if (args.Length() != 1) {
      isolate->ThrowException(Exception::TypeError(
          String::NewFromUtf8(isolate, "Wrong number of arguments")));
      return;
    }
    if (!args[0]->IsNumber()) {
      isolate->ThrowException(Exception::TypeError(
          String::NewFromUtf8(isolate, "Wrong arguments")));
      return;
    }
    int keylen = args[0]->NumberValue();

    char key[keylen];
    char alpha[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    int i;
    for (i = 0; i < keylen-1; i++)
        key[i] = alpha[rand()%62];
    key[keylen-1] = '\0'; // Null terminate

    // Return the keypair as a JS object
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, key));
  }

  void init(Local<Object> exports) {
    NODE_SET_METHOD(exports, "apikey", genAPIKey);
  }

  NODE_MODULE(keygen, init)
}