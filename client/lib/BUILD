cc_library(
    name = "client_lib",
    srcs = ["Client.cc"],
    hdrs = [
        "Client.h",
        "protocol.h",
    ],
    static_library = "libdb.a",
    visibility = ["//visibility:public"],
    deps = ["@boost//:asio"],
)
