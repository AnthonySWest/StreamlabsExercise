#include <napi.h>
#include <iostream>

//modifed example from:
//https://gauriatiq.medium.com/c-native-addon-independent-of-node-js-version-using-napi-node-addon-api-and-cmake-53315582cbd1

using namespace std;

namespace testAddon
{
	//echo number test
	int echoNum(int num);
 
	//expose the call through an API wrapper
	Napi::Number API_echoNum(const Napi::CallbackInfo& info);
 
	//node api init stuff
	Napi::Object Init(Napi::Env env, Napi::Object exports);
	NODE_API_MODULE(addon, Init) //no semi colon on purpose
}