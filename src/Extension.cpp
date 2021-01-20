#include "../cpp-httplib/httplib.h"
#include "../json/single_include/nlohmann/json.hpp"
#include "../md5/src/md5.h"
#include "Extension.h"
#include <codecvt>
#include <random>
#include <string>

BOOL WINAPI DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) { return TRUE; }

bool ProcessSentence(std::wstring& x, SentenceInfo jb) {
    const static std::string appID = "";
    const static std::string appKey = "";
    if (jb["current select"]) {
        using content_t = wchar_t;
        std::wstring_convert<std::codecvt_utf8<content_t>, content_t> converter;
        std::string purgeBytes = converter.to_bytes(x);

        httplib::Client cli("http://fanyi-api.baidu.com");
        std::string salt = std::to_string(std::mt19937_64(std::random_device{}())());
        std::string toHash = appID + purgeBytes + salt + appKey;
        auto sign = MD5(toHash).toStr();
        std::stringstream ss;
        ss << "q=" << purgeBytes << "&";
        ss << "from=jp&";
        ss << "to=zh&";
        ss << "appid=" << appID << "&";
        ss << "salt=" << salt << "&";
        ss << "sign=" << sign;

        std::string js = cli.Post("/api/trans/vip/translate", ss.str(), "application/x-www-form-urlencoded")->body;
        try {
            std::wstring res = converter.from_bytes(nlohmann::json::parse(js).at("trans_result").at(0).at("dst").dump());
            x += L"\r\n";
            x += res;
            return true;
        }
        catch (std::exception&) {
            return false;
        }
    }
    else {
        return false;
    }
}
