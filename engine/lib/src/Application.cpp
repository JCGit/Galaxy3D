#include "Application.h"
#include "GTString.h"

#ifdef IOS
#import <Foundation/Foundation.h>
#endif

#ifdef WIN32
#include <Windows.h>
#endif

#ifdef WINPHONE
#include <wrl/client.h>
#endif

namespace Galaxy3D
{
    std::string Application::GetDataPath()
    {
		static std::string s_data_path;

#ifdef WINPC
		if(s_data_path.empty())
		{
			char buffer[MAX_PATH];
			GetModuleFileNameA(0, buffer, MAX_PATH);
			GTString path = GTString(buffer).Replace("\\", "/");
			s_data_path = path.str;
			s_data_path = s_data_path.substr(0, path.str.rfind('/'));
		}
#endif

#ifdef WINPHONE
		if(s_data_path.empty())
		{
			char buffer[MAX_PATH];
			Platform::String^ path_name = Windows::ApplicationModel::Package::Current->InstalledLocation->Path;
			const wchar_t *wpath = path_name->Data();
			WideCharToMultiByte(CP_ACP, 0, wpath, -1, buffer, MAX_PATH, NULL, NULL);
			GTString path = GTString(buffer).Replace("\\", "/");
			s_data_path = path.str;
		}
#endif

#ifdef IOS
		if(s_data_path.empty())
		{
			s_data_path = [[[NSBundle mainBundle] resourcePath] UTF8String];
		}
#endif

#ifdef ANDROID
		if(s_data_path.empty())
		{
			s_data_path = "/sdcard/com.dj.galaxy3d";
		}
#endif

		return s_data_path;
    }
}