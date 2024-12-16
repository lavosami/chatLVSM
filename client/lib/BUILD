cc_library(
    name = "client_lib",
    srcs = ["Client.cc"],
    hdrs = [
        "Client.h",
        "protocol.h",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//db",
        "@boost//:asio",
    ],
)
