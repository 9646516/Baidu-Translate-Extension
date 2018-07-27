#include "stdafx.h"

extern "C"
{
	/**
	* Param sentence: wstring of the sentence received by NextHooker
	* Param info: map containing additional info about the sentence
	* Return value: wstring of the sentence that NextHooker should transform the original into
	* THIS FUNCTION MAY BE RUN SEVERAL TIMES CONCURRENTLY: PLEASE ENSURE THAT IT IS THREAD SAFE!
	*/
	std::wstring __declspec(dllexport) OnNewSentence(std::wstring sentence, std::unordered_map<std::string, int>& info)
	{
		// This example extension does nothing except place sentences from the hook currently selected by the user into the clipboard
		if (info["current select"])
		{
			HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, (sentence.size() + 1) * sizeof(wchar_t));
			memcpy(GlobalLock(hMem), sentence.c_str(), (sentence.size() + 1) * sizeof(wchar_t));
			GlobalUnlock(hMem);
			OpenClipboard(0);
			EmptyClipboard();
			SetClipboardData(CF_UNICODETEXT, hMem);
			CloseClipboard();
		}
		return sentence; // Unless you want to change the sentence, please return the original!
	}
}
