cc_library(
    name = "server_lib",
    srcs = ["Server.cc"],
    hdrs = [
        "Server.h",
        "protocol.h",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//db",
        "@boost//:asio",
    ],
)
