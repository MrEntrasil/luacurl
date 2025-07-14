require("luacurl")
--[[
print(luacurl_request(
	"https://example.com",
	"GET"
))
--]]

luacurl_downloadfile("https://raw.githubusercontent.com/MrEntrasil/luacurl/refs/heads/main/src/main.cpp", "test");
