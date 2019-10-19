#include <stdio.h>
#include <curl/curl.h>
#include <pthread.h>
#include <string>

int maxCount =10;

size_t write_cb(char* content,size_t size,size_t nemb,void* data){
  printf("receive data:%s",content);
  return (size_t)size*nemb;
}

void init(int threadCount){
  maxCount = threadCount;
  curl_global_init(CURL_GLOBAL_ALL);
}

void destroy(){
  curl_global_cleanup();
}

void *requestInner(void *url){
  CURL *curl;
  CURLcode res;
 
  /* In windows, this will init the winsock stuff */ 
  curl_global_init(CURL_GLOBAL_ALL);
 
  /* get a curl handle */ 
  curl = curl_easy_init();
  if(curl) {
    /* First set the URL that is about to receive our POST. This URL can
       just as well be a https:// URL if that is what should receive the
       data. */ 
    curl_easy_setopt(curl, CURLOPT_URL, reinterpret_cast<char*>(url));
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_cb);
    /* Now specify the POST data */ 
    // curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "name=daniel&project=curl");
 
    /* Perform the request, res will get the return code */ 
    res = curl_easy_perform(curl);
    /* Check for errors */ 
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
 
    /* always cleanup */ 
    curl_easy_cleanup(curl);
  }
  return NULL;
}

pthread_t requestInThread(char* url){
    int error;
    pthread_t tid;
    error = pthread_create(&tid, NULL, requestInner,url);
    return tid;
}
