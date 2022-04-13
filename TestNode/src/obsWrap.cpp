#include "obsWrap.h"
#include "obs.h"
//#include <iostream>

namespace ObsWrap
{

// /////////////// class statics ////////////////////////////////////////////

const std::string ObsTest::DEFAULT_LOCALE = "en-us";
	

/////////////////////////////////////////////////////////////////////////////
//	    		         ObsTest class
/////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------------------------------------
Napi::Object ObsTest::Init(Napi::Env env, Napi::Object exports)
{
	napi_property_attributes attribs = static_cast<napi_property_attributes>(napi_writable | napi_configurable);

	// This method is used to hook the accessor and method callbacks
	Napi::Function func = DefineClass(env, "ObsTest", {
		//ObsTest::InstanceMethod("Start", &ObsTest::Start),
		InstanceMethod<&ObsTest::Start>("Start", attribs),
		InstanceMethod<&ObsTest::Shutdown>("Shutdown", attribs),
		InstanceMethod<&ObsTest::Started>("Started", attribs),
		InstanceMethod<&ObsTest::Initialized>("Initialized", attribs),
		StaticMethod<&ObsTest::CreateNewItem>("CreateNewItem", static_cast<napi_property_attributes>(napi_writable | napi_configurable)),
		});


	Napi::FunctionReference* constructor = new Napi::FunctionReference();

	// Create a persistent reference to the class constructor. This will allow
	// a function called on a class prototype and a function
	// called on instance of a class to be distinguished from each other.
	*constructor = Napi::Persistent(func);
	exports.Set("ObsTest", func);

	// Store the constructor as the add-on instance data. This will allow this
	// add-on to support multiple instances of itself running on multiple worker
	// threads, as well as multiple instances of itself running in different
	// contexts on the same thread.
	//
	// By default, the value set on the environment here will be destroyed when
	// the add-on is unloaded using the `delete` operator, but it is also
	// possible to supply a custom deleter.
	env.SetInstanceData<Napi::FunctionReference>(constructor);

	return exports;
}
// ------------------------------------------------------------------------------------------------
ObsTest::ObsTest(const Napi::CallbackInfo& info) :
	Napi::ObjectWrap<ObsTest>(info)
{
	Napi::Env env = info.Env();

	//this test may not be necessary for this context?
	if (info.Length() > IDX_OBS_STARTED && info[IDX_OBS_STARTED].IsBoolean())
	{
		Napi::Boolean bVal = info[IDX_OBS_STARTED].As<Napi::Boolean>();
		m_obsStarted = bVal;
	}
	else
	{
		m_obsStarted = false;
	}
}
// ------------------------------------------------------------------------------------------------
//ObsTest::~Obs()
//{
//	Destroy_Private();
//}
// ------------------------------------------------------------------------------------------------
bool ObsTest::Start_P(const char* locale)
{
	if (m_obsStarted)
		return true;

	std::string loc = nullptr == locale ? DEFAULT_LOCALE : locale;

	if (!::obs_startup(loc.c_str(), nullptr, nullptr))
		return false;

	m_obsStarted = true;
}
// ------------------------------------------------------------------------------------------------
void ObsTest::Shutdown_P()
{
	if (!m_obsStarted)
		return;

	::obs_shutdown();
	m_obsStarted = false;
}
// ------------------------------------------------------------------------------------------------
Napi::Value ObsTest::Start(const Napi::CallbackInfo& info)
{
	Napi::Env env = info.Env();

	if (m_obsStarted)
		return Napi::Boolean::New(env, true); //already started

	std::string locale = DEFAULT_LOCALE;
	const size_t idxOfLocale = 0;

	if (info.Length() > idxOfLocale && info[idxOfLocale].IsString())
	{
		Napi::String value = info[idxOfLocale].As<Napi::String>();
		locale = value.Utf8Value();
	}

	bool result = Start_P(locale.c_str());
	return Napi::Boolean::New(env, result);
}
// ------------------------------------------------------------------------------------------------
Napi::Value ObsTest::Shutdown(const Napi::CallbackInfo& info)
{
	Shutdown_P();

	Napi::Env env = info.Env();
	return Napi::Boolean::New(env, true);
}
// ------------------------------------------------------------------------------------------------
Napi::Value ObsTest::Started(const Napi::CallbackInfo& info)
{
	Napi::Env env = info.Env();
	return Napi::Boolean::New(env, m_obsStarted);
}
// ------------------------------------------------------------------------------------------------
Napi::Value ObsTest::Initialized(const Napi::CallbackInfo& info)
{
	bool initialized = ::obs_initialized();
	Napi::Env env = info.Env();
	return Napi::Boolean::New(env, initialized);
}
// ------------------------------------------------------------------------------------------------
// Create a new item using the constructor stored during Init.
Napi::Value ObsTest::CreateNewItem(const Napi::CallbackInfo& info)
{
	Napi::Env env = info.Env();
	//NAPI_VERSION
	// Retrieve the instance data we stored during `Init()`. We only stored the
	// constructor there, so we retrieve it here to create a new instance of the
	// JS class the constructor represents.

	//NOTE!!!! Must define NAPI_VERSION to be 6 or higher or GetInstanceData isn't available (e.g. #define NAPI_VERSION 8)
	//Bleh. See: https://github.com/electron/electron/issues/24248

	Napi::FunctionReference* constructor = env.GetInstanceData<Napi::FunctionReference>();
	//return constructor->New({ Napi::Number::New(env, 42) });
	return constructor->New({ Napi::Boolean::New(env, false) });
}
// ------------------------------------------------------------------------------------------------
	
} //end namespace obsWrap