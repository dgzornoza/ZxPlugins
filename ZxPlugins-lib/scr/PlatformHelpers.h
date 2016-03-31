#ifndef __ZXPLUGIN_PLATFORM_HELPERS_H__
#define __ZXPLUGIN_PLATFORM_HELPERS_H__

#include <codecvt>

namespace cocos2d {
	namespace zxplugin {

		/** function for convert c++ string to platform native string
		* @param _string c++ std:string for convert to platform string
		* @result platform string converted
		* @remarks http://stackoverflow.com/questions/2573834/c-convert-string-or-char-to-wstring-or-wchar-t
		*/
		inline Platform::String^ convertToPlatformString(const std::string& _string)
		{
			// create converter and convert
			std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
			std::wstring wstr = converter.from_bytes(_string);

			// create platform string and return result
			Platform::String^ result = ref new Platform::String(wstr.c_str());
			return result;
		}

		/** function for convert platform native string to c++ string
		* @param _string platform string for convert to c++ std:string
		* @result std::string converted
		* @remarks http://stackoverflow.com/questions/2573834/c-convert-string-or-char-to-wstring-or-wchar-t
		*/
		inline std::string convertFromPlatformString(Platform::String^ _string)
		{
			// create converter and convert
			std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
			std::string result = converter.to_bytes(_string->Data());
			return result;
		}

		/** function for wrap c++ std:function to platform native pointer function
		* @param _callback c++ std::function for wrap into platform native pointer function
		* @result platform native pointer function
		*/
		inline CocosAppWinRT::ZxPlugin::CompletedFunc^ wrapPlatformCallback(std::function<void(const std::string&)> _callback)
		{
			return ref new CocosAppWinRT::ZxPlugin::CompletedFunc([=](Platform::String^ _param)
			{
				_callback(convertFromPlatformString(_param));
			});
		}

	} // namespace cocos2d 
} // namespace zxplugin

#endif /* __ZXPLUGIN_PLATFORM_HELPERS_H__ */