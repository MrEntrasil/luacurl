require("luacurl")
--[[
print(luacurl_request(
	"https://example.com",
	"GET"
))
--]]

print(luacurl_downloadfile("https://raw.githubusercontent.com/MrEntrasil/luacurl/refs/heads/main/src/main.cpp", "test"))
