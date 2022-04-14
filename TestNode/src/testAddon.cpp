#include "testAddon.h"
#include "obsWrap.h"

namespace testAddon
{
//using namespace std;
	
// ------------------------------------------------------------------------------------------------
int echoNum(int num)
{
	return num;
}

// ------------------------------------------------------------------------------------------------
Napi::Number API_echoNum(const Napi::CallbackInfo& info)
{
	Napi::Env env = info.Env();
	
	//ensure that at least one parameter exists and that it is an integer
	if(info.Length() < 1 || !info[0].IsNumber())
	{
		Napi::TypeError::New(env, "Error: expected a number.").ThrowAsJavaScriptException();
	}
	
	//convert js datatype to c++
	Napi::Number napiNumIn = info[0].As<Napi::Number>();
	
	//run c++ function return value and return it in javascript
	Napi::Number returnValue = Napi::Number::New(env, echoNum(napiNumIn.Int32Value()));

	return returnValue;
}

// ------------------------------------------------------------------------------------------------
Napi::Object Init(Napi::Env env, Napi::Object exports) 
{
	//export Napi function
	exports.Set("echoNum", Napi::Function::New(env, API_echoNum));
	ObsWrap::ObsTest::Init(env, exports);
	return exports;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
	
} //end namespace testAddon