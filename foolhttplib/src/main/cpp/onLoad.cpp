#include <jni.h>
#include <string>
#include <curl/curl.h>
#include <android/log.h>

size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string *) userp)->append((char *) contents, size * nmemb);
    return size * nmemb;
}

static int curl_debug_callback2(CURL *handle, curl_infotype type,
                                char *data, size_t size, void *userptr) {
    std::string msg(data, size);
    __android_log_print(ANDROID_LOG_DEBUG, "CURL", "%s", msg.c_str());
    return 0;
}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_github_tony_foolhttp_core_client_HttpCilent_httpGetRequest(JNIEnv *env, jobject /* this */,
                                                                    jstring jurl) {
    const char *url = env->GetStringUTFChars(jurl, nullptr);
    std::string response;
    int code = -1;
    curl_global_init(CURL_GLOBAL_DEFAULT);  // 一次性初始化，可以在 JNI_OnLoad 中做
    CURL *curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback); // 设置写入回调
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);         // 设置写入目标
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);           // 自动跟随重定向（如 301）
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, curl_debug_callback2);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);
        CURLcode res = curl_easy_perform(curl);                       // 发起请求
        if (res == CURLE_OK) {
            long http_code = 0;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
            code = static_cast<int>(http_code);
        } else {
            response = curl_easy_strerror(res);
        }

        curl_easy_cleanup(curl);
    } else {
        response = "curl_easy_init failed";
    }

    env->ReleaseStringUTFChars(jurl, url);

    jclass responseClass = env->FindClass("com/github/tony/foolhttp/core/Response");
    jmethodID constructor = env->GetMethodID(responseClass, "<init>", "(ILjava/lang/String;)V");

    jstring jBody = env->NewStringUTF(response.c_str());

    jobject responseObj = env->NewObject(responseClass, constructor, code, jBody);

    return responseObj;
}
