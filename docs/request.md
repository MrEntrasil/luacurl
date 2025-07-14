# luacurl_request

## Usage

```lua
luacurl_request(url, method, body, headers)
-> res, err
```
- **url** -> string
- **method** -> string || nil
- **body** -> string || nil
- **headers** -> table || nil

## Example

```lua
require("luacurl")

local res, err = luacurl_request("http://example.com")
assert(not err, err)

print(res)
```
