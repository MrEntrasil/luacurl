extern "C" {
#include <lua5.4/lua.h>
#include <lua5.4/lauxlib.h>
}

#include <curl/curl.h>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

size_t write_cb(void* contents, size_t size, size_t nmemb, void* userp) {
	((std::ostringstream*)userp)->write((char*)contents, size*nmemb);
	return size*nmemb;
}

int luacurl_request(lua_State* L) {
	const char* url = luaL_checkstring(L, 1);
	const char* method = luaL_optstring(L, 2, "GET");
	const char* body = luaL_optstring(L, 3, "");
	std::ostringstream res;
	struct curl_slist* headers;
	CURLcode res_code;
	CURL* curl = curl_easy_init();

	if (!curl) {
		lua_pushnil(L);
		lua_pushstring(L, "curl initializing fail");
		return 0;
	}
	
	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, method);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &write_cb);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &res);
	
	if (body && strlen(body) > 0) {
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body);
	}

	if (lua_istable(L, 4)) {
		lua_pushnil(L);
		while (lua_next(L, 4) != 0) {
			const char* h = lua_tostring(L, -1);
			headers = curl_slist_append(headers, h);
			lua_pop(L, 1);
		}
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
	}

	res_code = curl_easy_perform(curl);
	if (headers) {
		curl_slist_free_all(headers);
	}
	curl_easy_cleanup(curl);

	if (res_code != CURLE_OK) {
		lua_pushnil(L);
		lua_pushstring(L, curl_easy_strerror(res_code));
		return 0;
	}

	lua_pushstring(L, res.str().c_str());
	return 1;
}

int luacurl_downloadfile(lua_State* L) {
	const char* url = luaL_checkstring(L,1);
	const char* filename = luaL_checkstring(L,2);
	std::ofstream outfile(filename, std::ios::binary);
	CURLcode res;
	CURL* curl = curl_easy_init();

	if (!outfile.is_open() || !curl) {
		lua_pushnil(L);
		return 0;
	}

	curl_easy_setopt(curl,CURLOPT_URL,url);
	curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,&write_cb);
	curl_easy_setopt(curl,CURLOPT_WRITEDATA,&outfile);
	res = curl_easy_perform(curl);
	curl_easy_cleanup(curl);

	outfile.close();
    lua_pushboolean(L, 1);
	return 1;
}

extern "C" int luaopen_luacurl(lua_State* L) {
	lua_register(L, "luacurl_request", luacurl_request);
	lua_register(L, "luacurl_downloadfile", luacurl_downloadfile);
	return 0;
}
