The simple API is just some static methods modeled after the most common HTTP verbs:

#include "restclient-cpp/restclient.h"

RestClient::Response r = RestClient::get("http://url.com")
RestClient::Response r = RestClient::post("http://url.com/post", "application/json", "{\"foo\": \"bla\"}")
RestClient::Response r = RestClient::put("http://url.com/put", "application/json", "{\"foo\": \"bla\"}")
RestClient::Response r = RestClient::patch("http://url.com/patch", "application/json", "{\"foo\": \"bla\"}")
RestClient::Response r = RestClient::del("http://url.com/delete")
RestClient::Response r = RestClient::head("http://url.com")
RestClient::Response r = RestClient::options("http://url.com")

The response is of type RestClient::Response and has three attributes:
RestClient::Response.code // HTTP response code
RestClient::Response.body // HTTP response body
RestClient::Response.headers // HTTP response headers

However if you want more sophisticated features like connection reuse, timeouts or authentication, there is also a different, more configurable way.
#include "restclient-cpp/connection.h"
#include "restclient-cpp/restclient.h"

// initialize RestClient
RestClient::init();

// get a connection object
RestClient::Connection* conn = new RestClient::Connection("http://url.com");

// configure basic auth
conn->SetBasicAuth("WarMachine68", "WARMACHINEROX");

// set connection timeout to 5s
conn->SetTimeout(5);

// set custom user agent
// (this will result in the UA "foo/cool restclient-cpp/VERSION")
conn->SetUserAgent("foo/cool");

// enable following of redirects (default is off)
conn->FollowRedirects(true);
// and limit the number of redirects (default is -1, unlimited)
conn->FollowRedirects(true, 3);

// set headers
RestClient::HeaderFields headers;
headers["Accept"] = "application/json";
conn->SetHeaders(headers)

// append additional headers
conn->AppendHeader("X-MY-HEADER", "foo")

// if using a non-standard Certificate Authority (CA) trust file
conn->SetCAInfoFilePath("/etc/custom-ca.crt")

RestClient::Response r = conn->get("/get")
RestClient::Response r = conn->head("/get")
RestClient::Response r = conn->del("/delete")
RestClient::Response r = conn->options("/options")

// set different content header for POST, PUT and PATCH
conn->AppendHeader("Content-Type", "application/json")
RestClient::Response r = conn->post("/post", "{\"foo\": \"bla\"}")
RestClient::Response r = conn->put("/put", "application/json", "{\"foo\": \"bla\"}")
RestClient::Response r = conn->patch("/patch", "text/plain", "foobar")

// deinit RestClient. After calling this you have to call RestClient::init()
// again before you can use it
RestClient::disable();

The responses are again of type RestClient::Response and have three attributes:
RestClient::Response.code // HTTP response code
RestClient::Response.body // HTTP response body
RestClient::Response.headers // HTTP response headers

The connection object also provides a simple way to get some diagnostics and metrics information via conn->GetInfo(). The result is a RestClient::Connection::Info struct and looks like this:
typedef struct {
  std::string base_url;
  RestClients::HeaderFields headers;
  int timeout;
  struct {
    std::string username;
    std::string password;
  } basicAuth;

  std::string certPath;
  std::string certType;
  std::string keyPath;
  std::string keyPassword;
  std::string customUserAgent;
  std::string uriProxy;
  struct {
    // total time of the last request in seconds Total time of previous
    // transfer. See CURLINFO_TOTAL_TIME
    int totalTime;
    // time spent in DNS lookup in seconds Time from start until name
    // resolving completed. See CURLINFO_NAMELOOKUP_TIME
    int nameLookupTime;
    // time it took until Time from start until remote host or proxy
    // completed. See CURLINFO_CONNECT_TIME
    int connectTime;
    // Time from start until SSL/SSH handshake completed. See
    // CURLINFO_APPCONNECT_TIME
    int appConnectTime;
    // Time from start until just before the transfer begins. See
    // CURLINFO_PRETRANSFER_TIME
    int preTransferTime;
    // Time from start until just when the first byte is received. See
    // CURLINFO_STARTTRANSFER_TIME
    int startTransferTime;
    // Time taken for all redirect steps before the final transfer. See
    // CURLINFO_REDIRECT_TIME
    int redirectTime;
    // number of redirects followed. See CURLINFO_REDIRECT_COUNT
    int redirectCount;
  } lastRequest;
} Info;

//Calling conn->SetFileProgressCallbackData(data) is optional. This will set the data pointer which is the first parameter fed back to the progress callback - clientp. If this isn't set then clientp will default to the connection object conn.
// set CURLOPT_NOPROGRESS
// set CURLOPT_PROGRESSFUNCTION
conn->SetFileProgressCallback(progressFunc);
// set CURLOPT_PROGRESSDATA
conn->SetFileProgressCallbackData(data);

Here is an example of a write callback function, processing result data line by line.
auto writeCallback = [](void *data, size_t size, size_t nmemb, void *userdata) -> size_t
{
  size_t bytes = size * nmemb;
  try
  {
      // Add to the buffer
      auto res = reinterpret_cast<RestClient::Response *>(userdata);
      res->body.append(static_cast<char*>(data), bytes);
      // If the last character is not a new line, wait for the rest.
      if ('\n' != *(res->body.end() - 1))
      {
          return bytes;
      }
      // Process data one line at a time.
      std::stringstream stream(res->body);
      std::string line;
      while (std::getline(stream, line))
      {
        // Do something with the line here...
      }
      // Done processing the line
      res->body.clear();
  }
  catch(std::exception e)
  {
      // Log caught exception here
      return 0;
  }
  return bytes;
};

Simple wrapper functions are provided to allow clients to authenticate using certificates. Under the hood these wrappers set cURL options, e.g. CURLOPT_SSLCERT, using curl_easy_setopt. Note: currently libcurl compiled with gnutls (e.g. libcurl4-gnutls-dev on ubuntu) is buggy in that it returns a wrong error code when these options are set to invalid values.
// set CURLOPT_SSLCERT
conn->SetCertPath(certPath);
// set CURLOPT_SSLCERTTYPE
conn->SetCertType(type);
// set CURLOPT_SSLKEY
conn->SetKeyPath(keyPath);
// set CURLOPT_KEYPASSWD
conn->SetKeyPassword(keyPassword);

//An HTTP Proxy can be set to use for the upcoming request. To specify a port number, append :[port] to the end of the host name. If not specified, libcurl will default to using port 1080 for proxies. The proxy string may be prefixed with http:// or https://. If no HTTP(S) scheme is specified, the address provided to libcurl will be prefixed with http:// to specify an HTTP proxy. A proxy host string can embedded user + password. The operation will be tunneled through the proxy as curl option CURLOPT_HTTPPROXYTUNNEL is enabled by default. A numerical IPv6 address must be written within [brackets].
// set CURLOPT_PROXY
conn->SetProxy("https://37.187.100.23:3128");
/* or you can set it without the protocol scheme and
http:// will be prefixed by default */
conn->SetProxy("37.187.100.23:3128");
/* the following request will be tunneled through the proxy */
RestClient::Response res = conn->get("/get");


Note that the URL used with a unix socket has only ONE leading forward slash.
RestClient::Connection* conn = new RestClient::Connection("http:/v1.30");
conn->SetUnixSocketPath("/var/run/docker.sock");
RestClient::HeaderFields headers;
headers["Accept"] = "application/json; charset=UTF-8";
headers["Expect"] = "";
conn->SetHeaders(headers);
auto resp = conn->get("/images/json");

There are some packages available for Linux on packagecloud. And for OSX you can get it from the mrtazz/oss homebrew tap:
brew tap mrtazz/oss
brew install restclient-cpp

Otherwise you can do the regular autotools dance:
./autogen.sh
./configure
make install

Alternatively, you can build and install restclient-cpp using vcpkg dependency manager:
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.sh
./vcpkg integrate install
./vcpkg install restclient-cpp

Source: https://github.com/mrtazz/restclient-cpp