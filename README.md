# luacurl
## Dependencies
> curl-dev 8.0.1> (recommended)<br>
> lua-dev 5.4<br>
## Usage
```lua
luacurl_request(url: string, method: string|nil, body: string|nil, headers: table|nil) -> res: string|nil, err: string|nil
```
## Example
```lua
require("luacurl")
local res, err = luacurl_request("http://example.com")

if res then
	print(res)
else
	print("Error:")
	print(err)
end
```
