/*
 * Copyright (C) 2016 Baidu, Inc. All Rights Reserved.
 */
package com.github.tony.foolhttp.core.client

import com.github.tony.foolhttp.core.Request
import com.github.tony.foolhttp.core.Response
import java.net.HttpURLConnection
import java.net.URLConnection
import java.util.zip.GZIPInputStream


/**
 * Created by sanyinchen on 16/4/21.
 */
class HttpCilent : Client {
    companion object {
        init {
            System.loadLibrary("native-http")
        }
    }

    override fun executeRequest(request: Request): Response {
        System.out.println("executeRequest----");
        return httpGetRequest(request.url.toString())
    }


    external fun httpGetRequest(url: String): Response
}