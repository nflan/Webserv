The following code demonstrates how to run a simple HTTP request asynchronously, using the co-routine support in boost::asio behind the scenes.
1
#include <iostream>
2
#include "restc-cpp/restc-cpp.h"
3
​
4
using namespace std;
5
using namespace restc_cpp;
6
​
7
void DoSomethingInteresting(Context& ctx) {
8
    // Here we are in a co-routine, running in a worker-thread.
9
​
10
    // Asynchronously connect to a server and fetch some data.
11
    auto reply = ctx.Get("http://jsonplaceholder.typicode.com/posts/1");
12
​
13
    // Asynchronously fetch the entire data-set and return it as a string.
14
    auto json = reply->GetBodyAsString();
15
​
16
    // Just dump the data.
17
    cout << "Received data: " << json << endl;
18
}
19
​
20
int main() {
21
    auto rest_client = RestClient::Create();
22
​
23
    // Call DoSomethingInteresting as a co-routine in a worker-thread.
24
    rest_client->Process(DoSomethingInteresting);
25
​
26
    // Wait for the coroutine to finish, then close the client.
27
    rest_client->CloseWhenReady(true);
28
}
And here is the output you could expect
1
Received data: {
2
  "userId": 1,
3
  "id": 1,
4
  "title": "sunt aut facere repellat provident occaecati excepturi optio reprehenderit",
5
  "body": "quia et suscipit\nsuscipit recusandae consequuntur expedita et cum\nreprehenderit molestiae ut ut quas totam\nnostrum rerum est autem sunt rem eveniet architecto"
6
}
Here is a sightly more interesting example, using JSON serialization, and some modern C++ features.
1
#include <iostream>
2
​
3
#include <boost/lexical_cast.hpp>
4
#include <boost/fusion/adapted.hpp>
5
​
6
#include "restc-cpp/restc-cpp.h"
7
#include "restc-cpp/RequestBuilder.h"
8
​
9
using namespace std;
10
using namespace restc_cpp;
11
​
12
// C++ structure that match the JSON entries received
13
// from http://jsonplaceholder.typicode.com/posts/{id}
14
struct Post {
15
    int userId = 0;
16
    int id = 0;
17
    string title;
18
    string body;
19
};
20
​
21
// Since C++ does not (yet) offer reflection, we need to tell the library how
22
// to map json members to a type. We are doing this by declaring the
23
// structs/classes with BOOST_FUSION_ADAPT_STRUCT from the boost libraries.
24
// This allows us to convert the C++ classes to and from JSON.
25
​
26
BOOST_FUSION_ADAPT_STRUCT(
27
    Post,
28
    (int, userId)
29
    (int, id)
30
    (string, title)
31
    (string, body)
32
)
33
​
34
// The C++ main function - the place where any adventure starts
35
int main() {
36
    // Create an instance of the rest client
37
    auto rest_client = RestClient::Create();
38
​
39
    // Create and instantiate a Post from data received from the server.
40
    Post my_post = rest_client->ProcessWithPromiseT<Post>([&](Context& ctx) {
41
        // This is a co-routine, running in a worker-thread
42
​
43
        // Instantiate a Post structure.
44
        Post post;
45
​
46
        // Serialize it asynchronously. The asynchronously part does not really matter
47
        // here, but it may if you receive huge data structures.
48
        SerializeFromJson(post,
49
​
50
            // Construct a request to the server
51
            RequestBuilder(ctx)
52
                .Get("http://jsonplaceholder.typicode.com/posts/1")
53
​
54
                // Add some headers for good taste
55
                .Header("X-Client", "RESTC_CPP")
56
                .Header("X-Client-Purpose", "Testing")
57
​
58
                // Send the request
59
                .Execute());
60
​
61
        // Return the post instance trough a C++ future<>
62
        return post;
63
    })
64
​
65
    // Get the Post instance from the future<>, or any C++ exception thrown
66
    // within the lambda.
67
    .get();
68
​
69
    // Print the result for everyone to see.
70
    cout << "Received post# " << my_post.id << ", title: " << my_post.title;
71
}
The code above should return something like:
Received post# 1, title: sunt aut facere repellat provident occaecati excepturi optio reprehenderit
1
Received post# 1, title: sunt aut facere repellat provident occaecati excepturi optio reprehenderit
Source: https://github.com/C-And-Cpp-Libraries/restc-cpp-http