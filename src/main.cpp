extern "C" {
#include <lua5.4/lua.h>
#include <lua5.4/lauxlib.h>
}
#include <curl/curl.h>
#include <string>
#include <sstream>
#include <iostream>

size_t write_cb(void* contents, size_t size, size_t nmemb, void* userp) {
	((std::ostringstream*)userp)->write((char*)contents, size*nmemb);
	return size*nmemb;
}

int luacurl_request(lua_State* L) {
	const char* url = luaL_checkstring(L, 1);
	const char* method = luaL_optstring(L, 2, "GET");
	const char* body = luaL_optstring(L, 3, "");
	CURL* curl = curl_easy_init();

	if (!curl) {
		lua_pushnil(L);
		lua_pushstring(L, "curl initializing fail");
		return 0;
	}
	std::ostringstream res;
	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, method);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_cb);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &res);
	if (body && strlen(body) > 0) {
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body);
	}

	CURLcode res_code = curl_easy_perform(curl);
	curl_easy_cleanup(curl);

	if (res_code != CURLE_OK) {
		lua_pushnil(L);
		lua_pushstring(L, curl_easy_strerror(res_code));
		return 0;
	}

	lua_pushstring(L, res.str().c_str());
	return 1;
}

extern "C" int luaopen_luacurl(lua_State* L) {
	lua_register(L, "luacurl_request", luacurl_request);
	return 0;
}
