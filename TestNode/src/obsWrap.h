//ASW - 2022/04/12 - A meager attempt at an OBS wrapper
//Object wrap example: https://github.com/nodejs/node-addon-api/blob/main/doc/object_wrap.md
// ------------------------------------------------------------------------------------

#ifndef obsWrapH
#define obsWrapH

//#define NAPI_VERSION 8

#include <napi.h>
#include <string>


namespace ObsWrap
{
//using namespace std;

class ObsTest : public Napi::ObjectWrap<ObsWrap::ObsTest>
{
public:

	// //////////// const statics go here //////////////////////////////////////////////
	static const std::string DEFAULT_LOCALE;

protected:

	// //////////// const statics go here //////////////////////////////////////////////

	//use a constant so that there is only one place to change accessor order for Info[N]
	static const size_t IDX_OBS_STARTED = 0;

	// //////////// inheritable vars go here ///////////////////////////////////////////

	// //////////// functions go here //////////////////////////////////////////////////
		

private:

	// //////////// vars go here ///////////////////////////////////////////////////////

	//Note: Apparently the order of access for info[N] is the order the vars appear...no chance
	//for bugs to happen if someone accidentally screws up the order...nope :)
	bool m_obsStarted; //see IDX_OBS_STARTED
	
	// //////////// functions go here //////////////////////////////////////////////////
	bool Start_P(const char* locale);
	void Shutdown_P();

public:
	ObsTest(const Napi::CallbackInfo& info);
	//~ObsTest();

	// //////////// functions go here //////////////////////////////////////////////////

	//if locale is null, uses default
	//first parameter should contain locale string. If not, uses DEFAULT_LOCALE
	Napi::Value Start(const Napi::CallbackInfo& info);
	Napi::Value Shutdown(const Napi::CallbackInfo& info);
	
	Napi::Value Started(const Napi::CallbackInfo& info);
	Napi::Value Initialized(const Napi::CallbackInfo& info);

	Napi::Value EchoTestStr(const Napi::CallbackInfo& info);
	Napi::Value OBSVersionStr(const Napi::CallbackInfo& info);
	
	// ///////// mysterious node stuff /////////////////////////////////////////////////

	static Napi::Object Init(Napi::Env env, Napi::Object exports);
	static Napi::Value CreateNewItem(const Napi::CallbackInfo& info);

};

//NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init) //no semi colon on purpose
	
} //end namespace obsWrap
#endif
