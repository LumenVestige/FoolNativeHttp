# FoolHttp

An Android lightweight network library built on libcurl, designed for simple HTTP communication.

### Demo of using
+ API: ```fun get(path: String, parameters: List<Pair<String, Any?>>? = null, successCallBack: (response: Response) -> Unit = null!!, failCallBack: (response: Response, request: Request) ->Unit = null!!) ```  
+ Demo:
```
	 test1.setOnClickListener { view ->

            FoolHttp.get("$url", null, { response ->
                runOnUiThread {
                    codeText.text = "status:" + response.httpStateCode.toString();
                    webview.loadData(response.toString(), "text/html", response.httpEncode);

                }

            }, { response, request ->
                runOnUiThread {
                    codeText.text = "failed:" + response.httpStateCode.toString();

                }

            });

        }
```

### framework
structure![foolhttp.png](foolhttp.png)

### preview
<img src="source/img.png" alt="demo"   style="height: 480px;">
