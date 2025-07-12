require("luacurl")

print(luacurl_request(
	"https://example.com",
	"GET",
	nil,
	{
		"User-Agent: Mozilla/5.0 (Linux; Android 14 AppleWebKit/537.36 (KHTML, like Gecko) brave/136.0.7103.60 Mobile Safari/537.36"
	}
))
