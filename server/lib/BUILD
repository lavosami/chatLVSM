cc_library(
    name = "server_lib",
    srcs = ["Server.cc"],
    hdrs = [
        "Server.h",
        "protocol.h",
    ],
    static_library = "libdb.a",
    visibility = ["//visibility:public"],
    deps = ["@boost//:asio"],
)
