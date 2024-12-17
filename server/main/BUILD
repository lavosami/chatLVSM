cc_binary(
    name = "server",
    srcs = ["start_server.cc"],
    visibility = ["//visibility:public"],
    linkopts = ["-lsqlite3"],
    deps = [
        "//db",
        "//server/lib:server_lib",
    ],
)
