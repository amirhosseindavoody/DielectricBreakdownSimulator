cc_library(
    name = "constants",
    hdrs = ["constants.h"],
)

cc_library(
    name = "Node",
    hdrs = ["Node.h"],
    srcs = ["Node.cc"],
    deps = [":constants"]
)

cc_library(
    name = "RandomPositionGenerator",
    hdrs = ["RandomPositionGenerator.h"],
    deps = [
        ":constants",
        ":Node",
    ]
)

cc_binary(
    name = "main",
    srcs = ["main.cc"],
    deps=[
        ":Node",
        ":constants",
        ":RandomPositionGenerator",
    ],
)